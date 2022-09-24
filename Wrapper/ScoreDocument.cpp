//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  Score4 Wrapper  Library.  ---                  **
**                                                                      **
**          Copyright (C), 2017-2022, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
**          License: (See COPYING and LICENSE files)                    **
**          GNU General Public License (GPL) version 3,                 **
**          or (at your option) any later version.                      **
**                                                                      **
*************************************************************************/

/**
**      An Implementation of ScoreDocument class.
**
**      @file       ScoreDocument.cpp
**/

#include    "StdAfx.h"

#include    "ScoreDocument.h"
#include    "Score4Core/Common/DateTimeFormat.h"

#include    <msclr/marshal_cppstd.h>
using       namespace   msclr::interop;

namespace  Score4Wrapper  {
namespace  Document  {

namespace  {

using       Score4Core::Common::DateTimeFormat;

inline  System::DateTime^
getDateTime(
        const   DateSerial  dsVal)
{
    DateTimeFormat::TDateTime   dtBuf;
    DateTimeFormat::getDateTimeFromSerial(dsVal, &dtBuf);

    System::DateTime^   dtWork  = gcnew  System::DateTime(
            dtBuf.year,  dtBuf.month,  dtBuf.day);
    return ( dtWork );
}

inline  DateSerial
getDateSerial(
        System::DateTime^   dtVal)
{
    return ( DateTimeFormat::getSerialFromDate(
                     dtVal->Year, dtVal->Month, dtVal->Day) );
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
    Score4Core::Common::GameResult  umRecord;
    Score4Core::ErrCode             retVal;

    const   RecordFlag  flagRec = gameRecord->eGameFlags;

    umRecord.eGameFlags     = static_cast<Score4Core::RecordFlag>(flagRec);
    umRecord.recordDate     = getDateSerial(gameRecord->recordDate);
    umRecord.visitorTeam    = gameRecord->awayTeam;
    umRecord.homeTeam       = gameRecord->homeTeam;
    umRecord.visitorScore   = gameRecord->awayScore;
    umRecord.homeScore      = gameRecord->homeScore;

    retVal  = this->m_ptrObj->appendGameRecord(umRecord);
    return ( static_cast<ErrCode>(retVal) );
}

//----------------------------------------------------------------
//    全てのレコードを検査して最終日付を設定する。
//

System::DateTime^
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
        System::DateTime^   trgLastDate)
{
    Score4Core::ErrCode  retVal;

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
        System::DateTime^           gameDate,
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
//    ゲームレコードを最適化する。
//

ErrCode
ScoreDocument::optimizeGameRecords()
{
    Score4Core::ErrCode  retVal;

    retVal  = this->m_ptrObj->optimizeGameRecords();
    return ( static_cast<ErrCode>(retVal) );
}

//----------------------------------------------------------------
//    最終日付を更新する。
//

ErrCode
ScoreDocument::updateLastDate(
        System::Boolean     flgRecordOnly,
        System::DateTime^   lastDate)
{
    Score4Core::ErrCode  retVal;
    const   DateSerial  dsLast  = getDateSerial(lastDate);
    const   Boolean     blnFlag = (flgRecordOnly
                                   ? Score4Core::BOOL_TRUE
                                   : Score4Core::BOOL_FALSE);

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
    const   Score4Core::Common::GameResult
        & umRecord  = this->m_ptrObj->getGameRecord(idxRecord);
    Common::GameResult^  managedRecord  = gcnew Common::GameResult;

    managedRecord->eGameFlags   = static_cast<RecordFlag>(umRecord.eGameFlags);
    managedRecord->recordDate   = getDateTime(umRecord.recordDate);
    managedRecord->awayTeam     = umRecord.visitorTeam;
    managedRecord->homeTeam     = umRecord.homeTeam;
    managedRecord->awayScore    = umRecord.visitorScore;
    managedRecord->homeScore    = umRecord.homeScore;

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
    Score4Core::Common::GameResult  umRecord;
    Score4Core::ErrCode             retVal;

    const   RecordFlag  flagRec = gameRecord->eGameFlags;

    umRecord.eGameFlags     = static_cast<Score4Core::RecordFlag>(flagRec);
    umRecord.recordDate     = getDateSerial(gameRecord->recordDate);
    umRecord.visitorTeam    = gameRecord->awayTeam;
    umRecord.homeTeam       = gameRecord->homeTeam;
    umRecord.visitorScore   = gameRecord->awayScore;
    umRecord.homeScore      = gameRecord->homeScore;

    retVal  = this->m_ptrObj->setGameRecord(idxRecord, umRecord);
    return ( static_cast<ErrCode>(retVal) );
}

//----------------------------------------------------------------
//    ネイティブのインスタンスを取得する。
//

Score4Core::Document::ScoreDocument  &
ScoreDocument::toNativeInstance()
{
    return ( *(this->m_ptrObj) );
}

//----------------------------------------------------------------
//    ネイティブのインスタンスを取得する。
//

Score4Core::Document::ScoreDocument  *
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
    Score4Core::Boolean retVal  = this->m_ptrObj->getOptimizedFlag();
    return ( retVal != Score4Core::BOOL_FALSE );
}

//========================================================================
//
//    Properties.
//

//----------------------------------------------------------------
//    プロパティ  lastActiveDate
//

System::DateTime^
ScoreDocument::lastActiveDate::get()
{
    return ( getDateTime(this->m_ptrObj->getLastActiveDate()) );
}

void
ScoreDocument::lastActiveDate::set(
        System::DateTime^  dtVal)
{
    this->m_ptrObj->setLastActiveDate(getDateSerial(dtVal));
}

//----------------------------------------------------------------
//    プロパティ  lastImportDate
//

System::DateTime^
ScoreDocument::lastImportDate::get()
{
    return ( getDateTime(this->m_ptrObj->getLastImportDate()) );
}

void
ScoreDocument::lastImportDate::set(
        System::DateTime^  dtVal)
{
    this->m_ptrObj->setLastImportDate(getDateSerial(dtVal));
}

//----------------------------------------------------------------
//    プロパティ  lastRecordDate
//

System::DateTime^
ScoreDocument::lastRecordDate::get()
{
    return ( getDateTime(this->m_ptrObj->getLastRecordDate()) );
}

void
ScoreDocument::lastRecordDate::set(
        System::DateTime^  dtVal)
{
    this->m_ptrObj->setLastRecordDate(getDateSerial(dtVal));
}

//----------------------------------------------------------------

Common::LeagueInfo^
ScoreDocument::leagueInfo::get(
        int  idxLeague)
{
    const  WrapTarget::LeagueInfo  &
        leagueInfo  = this->m_ptrObj->getLeagueInfo(idxLeague);

    LeagueInfo^     retVal  = gcnew LeagueInfo;

    retVal->leagueName  = marshal_as<System::String^>(leagueInfo.leagueName);
    retVal->numPlayOff  = leagueInfo.numPlayOff;

    return ( retVal );
}

void
ScoreDocument::leagueInfo::set(
        int  idxLeague,  LeagueInfo^  leagueInfo)
{
    WrapTarget::LeagueInfo  natvVal;

    System::String^     leagueName  = leagueInfo->leagueName;

    natvVal.leagueName  = marshal_as<std::string>(leagueName);
    natvVal.numPlayOff  = leagueInfo->numPlayOff;

    this->m_ptrObj->setLeagueInfo(idxLeague, natvVal);
}

//----------------------------------------------------------------
//    プロパティ  teamInfo
//

//----------------------------------------------------------------

Common::TeamInfo^
ScoreDocument::teamInfo::get(
        int  idxTeam)
{
    const  WrapTarget::TeamInfo  &
        teamInfo    = this->m_ptrObj->getTeamInfo(idxTeam);

    TeamInfo^   retVal  = gcnew TeamInfo;

    retVal->leagueID    = teamInfo.leagueID;
    retVal->teamName    = marshal_as<System::String^>(teamInfo.teamName);

    return ( retVal );
}

void
ScoreDocument::teamInfo::set(
        int  idxTeam,  TeamInfo^  teamInfo)
{
    WrapTarget::TeamInfo    natvVal;

    System::String^     teamName    = teamInfo->teamName;

    natvVal.leagueID    = teamInfo->leagueID;
    natvVal.teamName    = marshal_as<std::string>(teamName);

    this->m_ptrObj->setTeamInfo(idxTeam, natvVal);
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
}   //  End of namespace  Score4Wrapper
