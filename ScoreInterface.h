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
**      Type Definitions.
**
**      @file       ScoreInterface.h
**/

#pragma     once

#include    "BaseballScore/Document/ScoreDocument.h"

#include    "Score4Types.h"

namespace  Score4Wrapper  {
namespace  Common  {

//========================================================================
//
//    Type Definitions.
//

typedef     cli::array<GamesCount, 1>       GameCountArray;

typedef     cli::array<GamesCount, 2>       GameCountTable;

typedef     cli::array<GamesCount, 1>       GameCountList;

typedef     cli::array<WinningRate, 1>      WinningRateList;
typedef     cli::array<WinningRate, 2>      WinningRateTable;

typedef     cli::array<ScoreValue, 1>       ScoreArray;

typedef     cli::array<ScoreValue, 2>       ScoreTable;

typedef     cli::array<NumOfDigits, 1>      NumOfDigitsList;
typedef     cli::array<NumOfDigits, 2>      NumOfDigitsTable;

typedef     cli::array<GamesCount, 1>       RestGamesArray;

typedef     cli::array<GamesCount, 2>       RestGamesTable;

/**   レコード番号の配列。      **/
typedef     cli::array<RecordIndex, 1>      RecordIndexList;

//----------------------------------------------------------------
/**
**    リーグ情報。
**/

public ref  class   LeagueInfo
{
public:

    /**   リーグ名。    **/
    property    System::String^     LeagueName;

    /**   プレーオフに進出できるチーム数。  **/
    property    TeamIndex           NumPlayOff;
};

//----------------------------------------------------------------
/**
**    チーム情報。
**/

public ref  class   TeamInfo
{
public:

    /**   所属リーグ。          **/
    property    LeagueIndex         LeagueID;

    /**   チーム名。            **/
    property    System::String^     TeamName;

    /**   試合数のリスト。      **/
    property    cli::array<GamesCount>^         GameCounts;
};

//----------------------------------------------------------------
/**
**    ゲーム結果のレコード。
**/

public ref  class   GameResult
{
public:

    property    RecordFlag          GameFlags;
    property    System::DateTime^   RecordDate;
    property    TeamIndex           AwayTeam;
    property    TeamIndex           HomeTeam;
    property    ScoreValue          AwayScore;
    property    ScoreValue          HomeScore;
};

//----------------------------------------------------------------
/**
**
**/

public ref  class   NumWinsForBeat
{
public:

    /**   必要勝利数が示している情報の種類。    **/
    property    MagicFilter     FilterType;

    /**
    **    対象チームを上回るのに必要な勝利数。
    **/
    property    GamesCount      NumNeedWins;

    /**
    **    残り試合数。ただし、マジックが点灯している時は、直接対決を除く。
    **/
    property    GamesCount      NumRestGame;

    /**
    **    対象チームを自力で上回るのに必要な勝利数。
    **/
    property    GamesCount      NumWinsSelf;

    /**
    **    対象チームを自力で上回る可能性ギリギリのラインとのゲーム差。
    **/
    property    GamesCount      NumWinsDiff;

};

typedef     cli::array<NumWinsForBeat^, 1>  WinsForBeatList;

//----------------------------------------------------------------
/**
**    マジックまたは自力での優勝／プレーオフ進出の可能性。
**/

public ref  class   MagicInfo
{
public:

    /**   可能性のある最低順位。    **/
    property    TeamIndex       RankLow;

    /**   可能性のある最高順位。    **/
    property    TeamIndex       RankHigh;

    cli::array<MagicInfoFlags>^ MagicFlags;

    /**   マジック。                **/
    cli::array<GamesCount>^     MagicNumber;
};

//----------------------------------------------------------------
/**
**    集計結果。
**/

public ref  class   CountedScores
{
public:

    /**   勝ち数。      **/
    property    GameCountArray^     NumWons;

    /**   負け数。      **/
    property    GameCountArray^     NumLost;

    /**   引分け。      **/
    property    GameCountArray^     NumDraw;

    /**   消化試合数。  **/
    property    RestGamesArray^     NumGames;

    /**   対チーム毎の勝ち数。  **/
    property    GameCountTable^     VsWons;

    /**   対チーム毎の負け数。  **/
    property    GameCountTable^     VsLost;

    /**   対チーム毎の引分け。  **/
    property    GameCountTable^     VsDraw;

    /**   各チームとの残り試合数。      **/
    property    RestGamesTable^     RestGames;

    /**   所属リーグ内での残り試合数。  **/
    property    RestGamesArray^     NumLeagueRestGames;

    /**   交流戦の残り試合数。          **/
    property    RestGamesArray^     NumInterRestGames;

    /**
    **    リーグ内と交流戦を合わせた残り試合数。
    **/
    property    RestGamesArray^     NumTotalRestGames;

    /**   マジック関連の集計結果。  **/
    property    MagicInfo^          TotalMagicInfo;

    /**   現在の順位。              **/
    property    TeamIndex           CurrentRank;

    /**
    **    必要勝利数等、マジック関連の補助計算データ。
    **/
    property    WinsForBeatList^    NumWinsForBeat;

    /**   総得点。  **/
    property    ScoreArray^         TotalGotScores;

    /**   総失点。  **/
    property    ScoreArray^         TotalLostScores;

    /**  対チーム毎の得点。 **/
    property    ScoreTable^         VsGotScores;

    /**  対チーム毎の失点。 **/
    property    ScoreTable^         VsLostScores;
};

typedef     cli::array<CountedScores^, 1>   CountedScoreList;

}   //  End of namespace  Common

//----------------------------------------------------------------
/**
**    その他の定数。
**/

public enum  class  Consts
{
    MAGIC_NO_PROBABILITY_WONS
        = Score4Core::Common::MAGIC_NO_PROBABILITY_WONS,
    MAGICLIST_NO_DATA_ENTRY
        = Score4Core::Common::MAGICLIST_NO_DATA_ENTRY
};

//========================================================================
//
//    Support Functions.
//

//----------------------------------------------------------------
/**   アンマネージ型をマネージ型に変換する。
**
**/

Score4Wrapper::Common::WinsForBeatList^
copyToManageType(
        const  Score4Core::Common::WinsForBeatList &wbSrc);

//----------------------------------------------------------------
/**   アンマネージ型をマネージ型に変換する。
**
**/

Score4Wrapper::Common::MagicInfo^
copyToManageType(
        const  Score4Core::Common::MagicInfo  & miSrc);

//----------------------------------------------------------------
/**   アンマネージ型をマネージ型に変換する。
**
**/

ErrCode
copyToManageType(
        const  Score4Core::Common::CountedScores  & csSrc,
        Score4Wrapper::Common::CountedScores      ^ csTrg);


}   //  End of namespace  Score4Wrapper
