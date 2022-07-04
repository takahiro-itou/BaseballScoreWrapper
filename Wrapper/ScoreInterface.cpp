//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  Score4 Wrapper  Library.  ---                  **
**                                                                      **
**          Copyright (C), 2017-2020, Takahiro Itou                     **
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
#include    "Score4Types.h"

namespace  Score4Wrapper  {
namespace  Common  {

}   //  End of namespace  Common


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
    csTrg->vsWons       = copyTableToManage(csSrc.vsWons);
    csTrg->vsLost       = copyTableToManage(csSrc.vsLost);
    csTrg->vsDraw       = copyTableToManage(csSrc.vsDraw);
    csTrg->restGames    = copyTableToManage(csSrc.restGames);

    csTrg->numLeagueRestGames
            = copyArrayToManage(csSrc.numLeagueRestGames);
    csTrg->numInterRestGames
            = copyArrayToManage(csSrc.numInterRestGames);
    csTrg->numTotalRestGames
            = copyArrayToManage(csSrc.numTotalRestGames);

    csTrg->currentRank  = csSrc.currentRank;

    csTrg->totalGotScores
            = copyArrayToManage(csSrc.totalGotScores);
    csTrg->totalLostScores
            = copyArrayToManage(csSrc.totalLostScores);
    csTrg->vsGotScores  = copyTableToManage(csSrc.vsGotScores);
    csTrg->vsLostScores = copyTableToManage
            (csSrc.vsLostScores);

    return ( ErrCode::ERR_SUCCESS );
}

}   //  End of namespace  Score4Wrapper
