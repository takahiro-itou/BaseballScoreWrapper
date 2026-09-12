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
**      @file       ScoreInterface.cpp
**/

#include    "PreCompile.h"

#include    "ScoreInterface.h"

#include    "ConvertManageType.h"


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
        wbDest[i]->FilterType   =
                static_cast<Score4Wrapper::MagicFilter>(wbSrc[i].filterType);
        wbDest[i]->NumNeedWins  = wbSrc[i].numNeedWins;
        wbDest[i]->NumRestGame  = wbSrc[i].numRestGame;
        wbDest[i]->NumWinsSelf  = wbSrc[i].numWinsSelf;
        wbDest[i]->NumWinsDiff  = wbSrc[i].numWinsDiff;
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
    miTrg->RankLow  = miSrc.rankLow;
    miTrg->RankHigh = miSrc.rankHigh;

    miTrg->MagicFlags   = castArrayToManage<MagicInfoFlags>(miSrc.magicFlags);
    miTrg->MagicNumber  = copyArrayToManage(miSrc.magicNumber);

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
    csTrg->NumWons      = copyArrayToManage(csSrc.numWons);
    csTrg->NumLost      = copyArrayToManage(csSrc.numLost);
    csTrg->NumDraw      = copyArrayToManage(csSrc.numDraw);
    csTrg->NumGames     = copyArrayToManage(csSrc.numGames);
    csTrg->VsWons       = toManageFromTable(csSrc.vsWons);
    csTrg->VsLost       = toManageFromTable(csSrc.vsLost);
    csTrg->VsDraw       = toManageFromTable(csSrc.vsDraw);
    csTrg->RestGames    = toManageFromTable(csSrc.restGames);

    csTrg->NumLeagueRestGames
            = copyArrayToManage(csSrc.numLeagueRestGames);
    csTrg->NumInterRestGames
            = copyArrayToManage(csSrc.numInterRestGames);
    csTrg->NumTotalRestGames
            = copyArrayToManage(csSrc.numTotalRestGames);

    csTrg->TotalMagicInfo   = copyToManageType(csSrc.totalMagic);
    csTrg->CurrentRank      = csSrc.currentRank;
    csTrg->NumWinsForBeat   = copyToManageType(csSrc.numWinsForBeat);

    csTrg->TotalGotScores   = copyArrayToManage(csSrc.totalGotScores);
    csTrg->TotalLostScores  = copyArrayToManage(csSrc.totalLostScores);
    csTrg->VsGotScores      = toManageFromTable(csSrc.vsGotScores);
    csTrg->VsLostScores     = toManageFromTable(csSrc.vsLostScores);

    return ( ErrCode::ERR_SUCCESS );
}

}   //  End of namespace  Score4Wrapper
