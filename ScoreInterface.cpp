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
**      @file       ScoreInterface.cpp
**/

#include    "StdAfx.h"

#include    "ScoreInterface.h"

#include    "ConvertManageType.h"
#include    "Score4Types.h"

namespace  Score4Wrapper  {
namespace  Common  {

}   //  End of namespace  Common


//----------------------------------------------------------------
//    アンマネージ型をマネージ型に変換する。
//

Score4Wrapper::Common::WinsForBeatList^
copyToManageType(
        const  Score4Core::Common::WinsForBeatList &wbSrc)
{
    const  int  num = static_cast<int>(wbSrc.size());

    Score4Wrapper::Common::WinsForBeatList^
            wbDest  = gcnew Score4Wrapper::Common::WinsForBeatList(num);

    for ( int i = 0; i < num; ++ i ) {
        wbDest[i]   = gcnew Score4Wrapper::Common::NumWinsForBeat;
        wbDest[i]->filterType   =
                static_cast<Score4Wrapper::MagicFilter>(wbSrc[i].filterType);
        wbDest[i]->numNeedWins  = wbSrc[i].numNeedWins;
        wbDest[i]->numRestGame  = wbSrc[i].numRestGame;
        wbDest[i]->numWinsSelf  = wbSrc[i].numWinsSelf;
        wbDest[i]->numWinsDiff  = wbSrc[i].numWinsDiff;
    }

    return ( wbDest );
}

//----------------------------------------------------------------
/**   アンマネージ型をマネージ型に変換する。
**
**/

Score4Wrapper::Common::MagicInfo^
copyToManageType(
        const  Score4Core::Common::MagicInfo  & miSrc)
{
    Score4Wrapper::Common::MagicInfo^
            miTrg   = gcnew Score4Wrapper::Common::MagicInfo;
    miTrg->rankLow  = miSrc.rankLow;
    miTrg->rankHigh = miSrc.rankHigh;

    miTrg->magicFlags   = castArrayToManage<MagicInfoFlags>(miSrc.magicFlags);
    miTrg->magicNumber  = copyArrayToManage(miSrc.magicNumber);

    return ( miTrg );
}

//----------------------------------------------------------------
//    アンマネージ型をマネージ型に変換する。
//

ErrCode
copyToManageType(
        const  Score4Core::Common::CountedScores  & csSrc,
        Score4Wrapper::Common::CountedScores      ^ csTrg)
{
    csTrg->numWons      = copyArrayToManage(csSrc.numWons);
    csTrg->numLost      = copyArrayToManage(csSrc.numLost);
    csTrg->numDraw      = copyArrayToManage(csSrc.numDraw);
    csTrg->numGames     = copyArrayToManage(csSrc.numGames);
    csTrg->vsWons       = toManageFromTable(csSrc.vsWons);
    csTrg->vsLost       = toManageFromTable(csSrc.vsLost);
    csTrg->vsDraw       = toManageFromTable(csSrc.vsDraw);
    csTrg->restGames    = toManageFromTable(csSrc.restGames);

    csTrg->numLeagueRestGames
            = copyArrayToManage(csSrc.numLeagueRestGames);
    csTrg->numInterRestGames
            = copyArrayToManage(csSrc.numInterRestGames);
    csTrg->numTotalRestGames
            = copyArrayToManage(csSrc.numTotalRestGames);

    csTrg->totalMagicInfo   = copyToManageType(csSrc.totalMagic);
    csTrg->currentRank      = csSrc.currentRank;
    csTrg->numWinsForBeat   = copyToManageType(csSrc.numWinsForBeat);

    csTrg->totalGotScores   = copyArrayToManage(csSrc.totalGotScores);
    csTrg->totalLostScores  = copyArrayToManage(csSrc.totalLostScores);
    csTrg->vsGotScores      = toManageFromTable(csSrc.vsGotScores);
    csTrg->vsLostScores     = toManageFromTable(csSrc.vsLostScores);

    return ( ErrCode::ERR_SUCCESS );
}

}   //  End of namespace  Score4Wrapper
