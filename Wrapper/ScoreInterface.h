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
**      Type Definitions.
**
**      @file       ScoreInterface.h
**/

#pragma     once

#include    "Score4Core/Document/ScoreDocument.h"

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

typedef     cli::array<ScoreValue, 1>       ScoreArray;

typedef     cli::array<ScoreValue, 2>       ScoreTable;

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
    property    System::String^     leagueName;

    /**   プレーオフに進出できるチーム数。  **/
    property    TeamIndex           numPlayOff;
};

//----------------------------------------------------------------
/**
**    チーム情報。
**/

public ref  class   TeamInfo
{
public:

    /**   所属リーグ。          **/
    property    LeagueIndex         leagueID;

    /**   チーム名。            **/
    property    System::String^     teamName;

    /**   試合数のリスト。      **/
    property    cli::array<GamesCount>^         gameCounts;
};

//----------------------------------------------------------------
/**
**    ゲーム結果のレコード。
**/

public ref  class   GameResult
{
public:

    property    RecordFlag      eGameFlags;
    property    DateSerial      recordDate;
    property    TeamIndex       awayTeam;
    property    TeamIndex       homeTeam;
    property    ScoreValue      awayScore;
    property    ScoreValue      homeScore;
};

//----------------------------------------------------------------
/**
**
**/

public ref  class   NumWinsForBeat
{
public:

    /**   必要勝利数が示している情報の種類。    **/
    property    MagicFilter     filterType;

    /**
    **    対象チームを上回るのに必要な勝利数。
    **/
    property    GamesCount      numNeedWins;

    /**
    **    残り試合数。ただし、マジックが点灯している時は、直接対決を除く。
    **/
    property    GamesCount      numRestGame;

    /**
    **    対象チームを自力で上回るのに必要な勝利数。
    **/
    property    GamesCount      numWinsSelf;

    /**
    **    対象チームを自力で上回る可能性ギリギリのラインとのゲーム差。
    **/
    property    GamesCount      numWinsDiff;

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
    property    TeamIndex       rankLow;

    /**   可能性のある最高順位。    **/
    property    TeamIndex       rankHigh;

    cli::array<MagicInfoFlags>^ magicFlags;

    /**   マジック。                **/
    cli::array<GamesCount>^     magicNumber;
};

//----------------------------------------------------------------
/**
**    集計結果。
**/

public ref  class   CountedScores
{
public:

    /**   勝ち数。      **/
    property    GameCountArray^     numWons;

    /**   負け数。      **/
    property    GameCountArray^     numLost;

    /**   引分け。      **/
    property    GameCountArray^     numDraw;

    /**   消化試合数。  **/
    property    RestGamesArray^     numGames;

    /**   対チーム毎の勝ち数。  **/
    property    GameCountTable^     vsWons;

    /**   対チーム毎の負け数。  **/
    property    GameCountTable^     vsLost;

    /**   対チーム毎の引分け。  **/
    property    GameCountTable^     vsDraw;

    /**   各チームとの残り試合数。      **/
    property    RestGamesTable^     restGames;

    /**   所属リーグ内での残り試合数。  **/
    property    RestGamesArray^     numLeagueRestGames;

    /**   交流戦の残り試合数。          **/
    property    RestGamesArray^     numInterRestGames;

    /**
    **    リーグ内と交流戦を合わせた残り試合数。
    **/
    property    RestGamesArray^     numTotalRestGames;

    /**   マジック関連の集計結果。  **/
    property    MagicInfo^          totalMagicInfo;

    /**   現在の順位。              **/
    property    TeamIndex           currentRank;

    /**
    **    必要勝利数等、マジック関連の補助計算データ。
    **/
    property    WinsForBeatList^    numWinsForBeat;

    /**   総得点。  **/
    property    ScoreArray^         totalGotScores;

    /**   総失点。  **/
    property    ScoreArray^         totalLostScores;

    /**  対チーム毎の得点。 **/
    property    ScoreTable^         vsGotScores;

    /**  対チーム毎の失点。 **/
    property    ScoreTable^         vsLostScores;
};

typedef     cli::array<CountedScores^, 1>   CountedScoreList;

}   //  End of namespace  Common


//========================================================================
//
//    Support Functions.
//

//----------------------------------------------------------------
/**   アンマネージ型静的配列をマネージ型配列に変換する。
**
**/

template <typename T, size_t N>
cli::array<T, 1>^
copyArrayToManage(
        const  std::array<T, N>  &  arySrc)
{
    cli::array<T, 1>^   aryDest = gcnew cli::array<T, 1>(N);
    for ( int i = 0; i < N; ++ i ) {
        aryDest[i]  = arySrc[i];
    }

    return ( aryDest );
}

template <typename T, size_t N>
cli::array<T, 1>^
copyArrayToManage(
        const  T (& arySrc)[N])
{
    cli::array<T, 1>^   aryDest = gcnew cli::array<T, 1>(N);
    for ( int i = 0; i < N; ++ i ) {
        aryDest[i]  = arySrc[i];
    }

    return ( aryDest );
}

template <typename TD, typename TS, size_t N>
cli::array<TD, 1>^
castArrayToManage(
        const  TS (& arySrc)[N])
{
    cli::array<TD, 1>^  aryDest = gcnew cli::array<TD, 1>(N);
    for ( int i = 0; i < N; ++ i ) {
        aryDest[i]  = static_cast<TD>(arySrc[i]);
    }

    return ( aryDest );
}

//----------------------------------------------------------------
/**   アンマネージ型テーブルをマネージ型配列に変換する。
**
**/

template <typename T, size_t N>
cli::array<T, 2>^
copyTableToManage(
        const  std::vector< std::array<T, N> >  & tblSrc)
{
    const  int  num = static_cast<int>(tblSrc.size());

    cli::array<T, 2>^   tblDest = gcnew cli::array<T, 2>(num, N);
    for ( int i = 0; i < num; ++ i ) {
        for ( int j = 0; j < N; ++ j ) {
            tblDest[i, j]   = tblSrc[i][j];
        }
    }

    return ( tblDest );
}

//----------------------------------------------------------------
/**   アンマネージ型動的配列をマネージ型配列に変換する。
**
**/

template <typename T>
cli::array<T, 1>^
copyVectorToManage(
        const  std::vector<T> & vecSrc,
        cli::array<T, 1>      ^ vecDest)
{
    const  int  num = static_cast<int>(vecSrc.size());

    for ( int i = 0; i < num; ++ i ) {
        vecDest[i]  = vecSrc[i];
    }

    return ( vecDest );
}

template <typename T>
cli::array<T, 1>^
copyVectorToManage(
        const  std::vector<T> & vecSrc)
{
    const  int  num = static_cast<int>(vecSrc.size());

    cli::array<T, 1>^   vecDest = gcnew cli::array<T, 1>(num);
    for ( int i = 0; i < num; ++ i ) {
        vecDest[i]  = vecSrc[i];
    }

    return ( vecDest );
}

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
