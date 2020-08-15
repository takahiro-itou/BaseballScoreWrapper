//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  Score4 Wrapper  Library.  ---                  **
**                                                                      **
**          Copyright (C), 2017-2018, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
*************************************************************************/

/**
**      Type Definitions.
**
**      @file       Score4Types.h
**/

#pragma     once

#include    "Score4Core/Common/Score4Types.h"


namespace  Score4Wrapper  {
namespace  Common  {

public enum  class  ErrCode
{
    ERR_SUCCESS             = Score4Core::Common::ERR_SUCCESS,
    ERR_FAILURE             = Score4Core::Common::ERR_FAILURE,
    ERR_FILE_OPEN_ERROR     = Score4Core::Common::ERR_FILE_OPEN_ERROR,
    ERR_FILE_IO_ERROR       = Score4Core::Common::ERR_FILE_IO_ERROR,
    ERR_INDEX_OUT_OF_RANGE  = Score4Core::Common::ERR_INDEX_OUT_OF_RANGE
};

typedef     Score4Core::Common::Boolean         Boolean;

//----------------------------------------------------------------
/**
**    レコードフラグ。
**/

public enum  class  RecordFlag
{
    GAME_EMPTY          = Score4Core::Common::GAME_EMPTY,
    GAME_SCHEDULE       = Score4Core::Common::GAME_SCHEDULE,
    GAME_CANCEL         = Score4Core::Common::GAME_CANCEL,
    GAME_RESULT         = Score4Core::Common::GAME_RESULT,
    GAME_REGULAR        = Score4Core::Common::GAME_REGULAR,
    GAME_NOT_REGULAR    = Score4Core::Common::GAME_NOT_REGULAR
};

//----------------------------------------------------------------
/**
**    ゲームフィルタフラグ。
**/

enum  GameFilter
{
    FILTER_HOME_GAMES   = Score4Core::Common::FILTER_HOME_GAMES,
    FILTER_AWAY_GAMES   = Score4Core::Common::FILTER_AWAY_GAMES,
    FILTER_ALL_GAMES    = Score4Core::Common::FILTER_ALL_GAMES,

    FILTER_SCHEDULE     = Score4Core::Common::FILTER_SCHEDULE,
    FILTER_SCDL_HOMES   = Score4Core::Common::FILTER_SCDL_HOMES,
    FILTER_SCDL_AWAYS   = Score4Core::Common::FILTER_SCDL_AWAYS,
    FILTER_SCDL_ALLS    = Score4Core::Common::FILTER_SCDL_ALLS,

    FILTER_GAMES_FIRST  = Score4Core::Common::FILTER_GAMES_FIRST,
    FILTER_GAMES_END    = Score4Core::Common::FILTER_GAMES_END,
    FILTER_SCDL_FIRST   = Score4Core::Common::FILTER_SCDL_FIRST,
    FILTER_SCDL_END     = Score4Core::Common::FILTER_SCDL_END
};


typedef     Score4Core::Common::DateSerial      DateSerial;
typedef     Score4Core::Common::TeamIndex       TeamIndex;
typedef     Score4Core::Common::LeagueIndex     LeagueIndex;
typedef     Score4Core::Common::GamesCount      GamesCount;
typedef     Score4Core::Common::RecordIndex     RecordIndex;
typedef     Score4Core::Common::ScoreValue      ScoreValue;
typedef     Score4Core::Common::FileLength      FileLength;

}   //  End of namespace  Common
}   //  End of namespace  Score4Wrapper
