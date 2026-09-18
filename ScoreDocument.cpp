//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  Baseball  Score  Wrapper  ---                  **
**                                                                      **
**          Copyright (C), 2017-2026, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
**          License: (See COPYING or LICENSE files)                     **
**          GNU Affero General Public License (AGPL) version 3,         **
**          or (at your option) any later version.                      **
**                                                                      **
*************************************************************************/

/**
**      An Implementation of ScoreDocument class.
**
**      @file       ScoreDocument.cpp
**/

#include    "PreCompile.h"

#include    "ScoreDocument.h"

#include    "ConvertManageType.h"

#include    "BaseballScore/Common/DateTimeFormat.h"


#include    <msclr/marshal_cppstd.h>
using       namespace   msclr::interop;


namespace  ScoreWrapper  {
namespace  Document  {

namespace  {

using       CoreCommon::DateTimeFormat;

inline  System::DateTime
getDateTime(
        const   DateSerial  dsVal)
{
    DateTimeFormat::TDateTime   dtBuf;
    DateTimeFormat::getDateTimeFromSerial(dsVal, &dtBuf);

    System::DateTime    dtWork(dtBuf.year,  dtBuf.month,  dtBuf.day);
    return ( dtWork );
}

inline  DateSerial
getDateSerial(
        System::DateTime    dtVal)
{
    return ( DateTimeFormat::getSerialFromDate(
                     dtVal.Year, dtVal.Month, dtVal.Day)
    );
}

}   //  End of (Unnamed) namespace

//========================================================================
//
//    ScoreDocument  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

ScoreDocument::ScoreDocument()
    : m_ptrObj { new WrapTarget() },
      m_ptrBuf { new WrapCountedScoreList() },
      m_trgDate(0)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

ScoreDocument::~ScoreDocument()
{
    this->!ScoreDocument();
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

ScoreDocument::!ScoreDocument()
{
    if ( this->m_ptrObj ) {
        delete  this->m_ptrObj;
        this->m_ptrObj  = nullptr;
    }
    if ( this->m_ptrBuf ) {
        delete  this->m_ptrBuf;
        this->m_ptrBuf  = nullptr;
    }
}

//========================================================================
//
//    Public Member Functions (Implement Pure Virtual).
//

//========================================================================
//
//    Public Member Functions (Overrides).
//

//========================================================================
//
//    Public Member Functions (Pure Virtual Functions).
//

//========================================================================
//
//    Public Member Functions (Virtual Functions).
//

//========================================================================
//
//    Public Member Functions.
//

//----------------------------------------------------------------
//    ゲームレコードを追加登録する。
//

ErrCode
ScoreDocument::appendGameRecord(
        GameResult^     gameRecord)
{
    CoreCommon::GameResult  umRecord;
    CoreNs::ErrCode         retVal;

    const   RecordFlag  flagRec = gameRecord->GameFlags;

    umRecord.eGameFlags     = static_cast<CoreNs::RecordFlag>(flagRec);
    umRecord.recordDate     = getDateSerial(gameRecord->RecordDate);
    umRecord.visitorTeam    = gameRecord->AwayTeam;
    umRecord.homeTeam       = gameRecord->HomeTeam;
    umRecord.visitorScore   = gameRecord->AwayScore;
    umRecord.homeScore      = gameRecord->HomeScore;

    retVal  = this->m_ptrObj->appendGameRecord(umRecord);
    return ( static_cast<ErrCode>(retVal) );
}

//----------------------------------------------------------------
//    全てのレコードを検査して最終日付を設定する。
//

System::DateTime
ScoreDocument::checkLastDate()
{
    DateSerial  retDate = this->m_ptrObj->checkLastDate();
    return ( getDateTime(retDate) );
}

//----------------------------------------------------------------
//    ドキュメントの内容をクリアする。
//

ErrCode
ScoreDocument::clearDocument()
{
    return ( static_cast<ErrCode>(this->m_ptrObj->clearDocument()) );
}

//----------------------------------------------------------------
//    指定したリーグに属するチームを、成績順にソートする。
//

TeamIndex
ScoreDocument::computeRankOrder(
        LeagueIndex         idxLeague,
        array<TeamIndex>^   bufIndex)
{
    std::vector<TeamIndex>  bufNatv;
    const   TeamIndex   retVal  = this->m_ptrObj->computeRankOrder(
            *(this->m_ptrBuf), idxLeague, bufNatv);
    copyVectorToManage(bufNatv, bufIndex);

    return ( retVal );
}

//----------------------------------------------------------------
//    指定したデータのコピーを作成する。
//

ScoreDocument^
ScoreDocument::copyFrom(
        ScoreDocument^  src)
{
    this->m_ptrObj->copyFrom(*(src->m_ptrObj));
    return ( this );
}

//----------------------------------------------------------------
//    試合結果を集計する。
//

ErrCode
ScoreDocument::countScores(
        System::DateTime    trgLastDate)
{
    CoreNs::ErrCode  retVal;

    DateSerial  dsLast  = getDateSerial(trgLastDate);

    this->m_ptrBuf->clear();
    this->m_ptrBuf->resize(getNumTeams());

    retVal  = this->m_ptrObj->countScores(dsLast, *(this->m_ptrBuf));

    const  LeagueIndex  numLeagues  = getNumLeagues();
    const  TeamIndex    numTeams    = getNumTeams();

    for ( LeagueIndex i = 0; i < numLeagues; ++ i ) {
        this->m_ptrObj->computeCurrentRank(i, *(this->m_ptrBuf));
    }
    this->m_ptrObj->computeRankRange(*(this->m_ptrBuf));

    this->m_csiBuf  = gcnew cli::array<CountedScores^, 1>(numTeams);
    for ( TeamIndex i = 0; i < numTeams; ++ i ) {
        this->m_csiBuf[i]   = gcnew  CountedScores;
        copyToManageType(this->m_ptrBuf->at(i), this->m_csiBuf[i]);
    }

    this->m_trgDate = dsLast;
    return ( static_cast<ErrCode>(retVal) );
}

//----------------------------------------------------------------
//    指定した条件の対戦カードを検索する。
//

RecordIndex
ScoreDocument::findGameRecords(
        System::DateTime            gameDate,
        const   TeamIndex           homeTeam,
        const   TeamIndex           visitorTeam,
        Common::RecordIndexList^%   bufRecord)
{
    DateSerial  targetDate  = getDateSerial(gameDate);
    RecordIndex numRecords;

    WrapTarget::RecordIndexList umBuffer;
    numRecords  = this->m_ptrObj->findGameRecords(
                        targetDate, homeTeam, visitorTeam, umBuffer);

    System::Array::Resize(bufRecord, numRecords);
    copyVectorToManage(umBuffer, bufRecord);

    return ( numRecords );
}

//----------------------------------------------------------------
//    勝率テーブルを作成する。
//

GamesCount
ScoreDocument::makeWinningRateTable(
        const  LeagueIndex  leagueIndex,
        WinningRateTable^%  rateTable)
{
    WrapTarget::WinningRateTable    workRate;

    const   GamesCount
    retVal  = this->m_ptrObj->makeWinningRateTable(
                    *m_ptrBuf, leagueIndex, workRate);
    rateTable = toManageFromTable(workRate);

    return ( retVal );
}

//----------------------------------------------------------------
//    ゲームレコードを最適化する。
//

ErrCode
ScoreDocument::optimizeGameRecords()
{
    CoreNs::ErrCode  retVal;

    retVal  = this->m_ptrObj->optimizeGameRecords();
    return ( static_cast<ErrCode>(retVal) );
}

//----------------------------------------------------------------
//    最終日付を更新する。
//

ErrCode
ScoreDocument::updateLastDate(
        System::Boolean     flgRecordOnly,
        System::DateTime    lastDate)
{
    CoreNs::ErrCode  retVal;
    const   DateSerial  dsLast  = getDateSerial(lastDate);
    const   Boolean     blnFlag = (flgRecordOnly
                                   ? CoreNs::BOOL_TRUE
                                   : CoreNs::BOOL_FALSE);

    retVal  = this->m_ptrObj->updateLastDate(blnFlag, dsLast);
    return ( static_cast<ErrCode>(retVal) );
}

//========================================================================
//
//    Public Member Functions (Static).
//

//----------------------------------------------------------------
//    指定したデータのコピーを作成する。
//

ScoreDocument^
ScoreDocument::createCopy(
        ScoreDocument^  src)
{
    ScoreDocument^  dst = gcnew ScoreDocument;
    dst->m_ptrObj->copyFrom(*(src->m_ptrObj));
    return ( dst );
}

//----------------------------------------------------------------
//    表示桁数リストを作成する。
//

NumOfDigits
ScoreDocument::makeDigitsList(
        WinningRateList^    rateList,
        NumOfDigitsList^%   digitsList)
{
    WrapTarget::WinningRateList workRate;
    WrapTarget::NumOfDigitsList workDigits;

    copyManageArray1ToUnmanageVector(rateList, workRate);
    const   NumOfDigits
        retVal  = WrapTarget::makeDigitsList(workRate, workDigits);
    digitsList  = toManageFromVector(workDigits);

    return ( retVal );
}

//----------------------------------------------------------------
//    表示桁数テーブルを作成する。
//

NumOfDigits
ScoreDocument::makeDigitsTable(
        WinningRateTable^   rateTable,
        NumOfDigitsTable^%  digitsTable)
{
    WrapTarget::WinningRateTable    workRate;
    WrapTarget::NumOfDigitsTable    workDigits;

    copyManageArray2ToUnmanageTable(rateTable, workRate);
    const   NumOfDigits
        retVal  = WrapTarget::makeDigitsTable(workRate, workDigits);
    digitsTable = toManageFromTable(workDigits);

    return ( retVal );
}

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    ゲームレコードを取得する。
//

ScoreDocument::GameResult^
ScoreDocument::getGameRecord(
        const  RecordIndex  idxRecord)
{
    const   CoreCommon::GameResult
        & umRecord  = this->m_ptrObj->getGameRecord(idxRecord);
    Common::GameResult^  managedRecord  = gcnew Common::GameResult;

    managedRecord->GameFlags    = static_cast<RecordFlag>(umRecord.eGameFlags);
    managedRecord->RecordDate   = getDateTime(umRecord.recordDate);
    managedRecord->AwayTeam     = umRecord.visitorTeam;
    managedRecord->HomeTeam     = umRecord.homeTeam;
    managedRecord->AwayScore    = umRecord.visitorScore;
    managedRecord->HomeScore    = umRecord.homeScore;

    return ( managedRecord );
}

//----------------------------------------------------------------
//    ゲームレコードを設定する。
//

ErrCode
ScoreDocument::setGameRecord(
        const  RecordIndex  idxRecord,
        GameResult^         gameRecord)
{
    CoreCommon::GameResult  umRecord;
    CoreNs::ErrCode             retVal;

    const   RecordFlag  flagRec = gameRecord->GameFlags;

    umRecord.eGameFlags     = static_cast<CoreNs::RecordFlag>(flagRec);
    umRecord.recordDate     = getDateSerial(gameRecord->RecordDate);
    umRecord.visitorTeam    = gameRecord->AwayTeam;
    umRecord.homeTeam       = gameRecord->HomeTeam;
    umRecord.visitorScore   = gameRecord->AwayScore;
    umRecord.homeScore      = gameRecord->HomeScore;

    retVal  = this->m_ptrObj->setGameRecord(idxRecord, umRecord);
    return ( static_cast<ErrCode>(retVal) );
}

//----------------------------------------------------------------
//    リーグ情報を取得する。
//

ScoreDocument::LeagueInfo^
ScoreDocument::getLeagueInfo(
        const  LeagueIndex  idxLeague)
{
    const  WrapTarget::LeagueInfo  &
        leagueInfo  = this->m_ptrObj->getLeagueInfo(idxLeague);

    LeagueInfo^     retVal  = gcnew LeagueInfo(idxLeague);

    retVal->LeagueName  = marshal_as<System::String^>(leagueInfo.leagueName);
    retVal->NumPlayOff  = leagueInfo.numPlayOff;

    return ( retVal );
}

//----------------------------------------------------------------
//    リーグ情報を設定する。
//

ErrCode
ScoreDocument::setLeagueInfo(
        const  LeagueIndex  idxLeague,
        LeagueInfo^         leagueInfo)
{
    WrapTarget::LeagueInfo  natvVal;
    CoreNs::ErrCode         retVal;

    System::String^     leagueName  = leagueInfo->LeagueName;

    natvVal.leagueName  = marshal_as<std::string>(leagueName);
    natvVal.numPlayOff  = leagueInfo->NumPlayOff;

    retVal  = this->m_ptrObj->setLeagueInfo(idxLeague, natvVal);
    return ( static_cast<ErrCode>(retVal) );
}


//----------------------------------------------------------------
//    ネイティブのインスタンスを取得する。
//

CoreDocument::ScoreDocument  &
ScoreDocument::toNativeInstance()
{
    return ( *(this->m_ptrObj) );
}

//----------------------------------------------------------------
//    ネイティブのインスタンスを取得する。
//

CoreDocument::ScoreDocument  *
ScoreDocument::toNativePointer()
{
    return ( (this->m_ptrObj) );
}

//----------------------------------------------------------------
//    登録されているリーグ数を取得する。
//

LeagueIndex
ScoreDocument::getNumLeagues()
{
    return ( this->m_ptrObj->getNumLeagues() );
}

//----------------------------------------------------------------
//    記録されているゲームレコード数を取得する。
//

RecordIndex
ScoreDocument::getNumRecords()
{
    return ( this->m_ptrObj->getNumRecords() );
}

//----------------------------------------------------------------
//    登録されているチーム数を取得する。
//

TeamIndex
ScoreDocument::getNumTeams()
{
    return ( this->m_ptrObj->getNumTeams() );
}

//----------------------------------------------------------------
//    最適化済みフラグを取得する。
//

System::Boolean
ScoreDocument::getOptimizedFlag()
{
    CoreNs::Boolean  retVal = this->m_ptrObj->getOptimizedFlag();
    return ( retVal != CoreNs::BOOL_FALSE );
}

//----------------------------------------------------------------
//    チーム情報を取得する。
//

ScoreDocument::TeamInfo^
ScoreDocument::getTeamInfo(
        const   TeamIndex   idxTeam)
{
    const  WrapTarget::TeamInfo  &
        teamInfo    = this->m_ptrObj->getTeamInfo(idxTeam);

    TeamInfo^   retVal  = gcnew TeamInfo;

    retVal->LeagueID    = teamInfo.leagueID;
    retVal->TeamName    = marshal_as<System::String^>(teamInfo.teamName);

    return ( retVal );

}

//----------------------------------------------------------------
//    チーム情報を設定する。
//

ErrCode
ScoreDocument::setTeamInfo(
        const   TeamIndex   idxTeam,
        TeamInfo^           teamInfo)
{
    WrapTarget::TeamInfo    natvVal;
    CoreNs::ErrCode         retVal;

    System::String^     teamName    = teamInfo->TeamName;

    natvVal.leagueID    = teamInfo->LeagueID;
    natvVal.teamName    = marshal_as<std::string>(teamName);

    retVal  = this->m_ptrObj->setTeamInfo(idxTeam, natvVal);
    return ( static_cast<ErrCode>(retVal) );
}


//========================================================================
//
//    Properties.
//

//----------------------------------------------------------------
//    プロパティ  lastActiveDate
//

System::DateTime
ScoreDocument::LastActiveDate::get()
{
    return ( getDateTime(this->m_ptrObj->getLastActiveDate()) );
}

void
ScoreDocument::LastActiveDate::set(
        System::DateTime    dtVal)
{
    this->m_ptrObj->setLastActiveDate(getDateSerial(dtVal));
}

//----------------------------------------------------------------
//    プロパティ  lastImportDate
//

System::DateTime
ScoreDocument::LastImportDate::get()
{
    return ( getDateTime(this->m_ptrObj->getLastImportDate()) );
}

void
ScoreDocument::LastImportDate::set(
        System::DateTime    dtVal)
{
    this->m_ptrObj->setLastImportDate(getDateSerial(dtVal));
}

//----------------------------------------------------------------
//    プロパティ  lastRecordDate
//

System::DateTime
ScoreDocument::LastRecordDate::get()
{
    return ( getDateTime(this->m_ptrObj->getLastRecordDate()) );
}

void
ScoreDocument::LastRecordDate::set(
        System::DateTime    dtVal)
{
    this->m_ptrObj->setLastRecordDate(getDateSerial(dtVal));
}


//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Document
}   //  End of namespace  ScoreWrapper
