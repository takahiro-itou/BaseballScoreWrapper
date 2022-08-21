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
**      @file       Score4Types.h
**/

#pragma     once

#include    "Score4Core/Common/Score4Types.h"


namespace  Score4Wrapper  {

public enum  class  ErrCode
{
    ERR_SUCCESS             = Score4Core::ERR_SUCCESS,
    ERR_FAILURE             = Score4Core::ERR_FAILURE,
    ERR_FILE_OPEN_ERROR     = Score4Core::ERR_FILE_OPEN_ERROR,
    ERR_FILE_IO_ERROR       = Score4Core::ERR_FILE_IO_ERROR,
    ERR_INDEX_OUT_OF_RANGE  = Score4Core::ERR_INDEX_OUT_OF_RANGE
};

typedef     Score4Core::Boolean         Boolean;

//----------------------------------------------------------------
/**
**    レコードフラグ。
**/

public enum  class  RecordFlag
{
    GAME_EMPTY          = Score4Core::GAME_EMPTY,
    GAME_SCHEDULE       = Score4Core::GAME_SCHEDULE,
    GAME_CANCEL         = Score4Core::GAME_CANCEL,
    GAME_RESULT         = Score4Core::GAME_RESULT,
    GAME_REGULAR        = Score4Core::GAME_REGULAR,
    GAME_NOT_REGULAR    = Score4Core::GAME_NOT_REGULAR
};

//----------------------------------------------------------------
/**
**    ゲームフィルタフラグ。
**/

public enum  class  GameFilter
{
    FILTER_HOME_GAMES   = Score4Core::FILTER_HOME_GAMES,
    FILTER_AWAY_GAMES   = Score4Core::FILTER_AWAY_GAMES,
    FILTER_ALL_GAMES    = Score4Core::FILTER_ALL_GAMES,

    FILTER_SCHEDULE     = Score4Core::FILTER_SCHEDULE,
    FILTER_SCDL_HOMES   = Score4Core::FILTER_SCDL_HOMES,
    FILTER_SCDL_AWAYS   = Score4Core::FILTER_SCDL_AWAYS,
    FILTER_SCDL_ALLS    = Score4Core::FILTER_SCDL_ALLS,

    FILTER_GAMES_FIRST  = Score4Core::FILTER_GAMES_FIRST,
    FILTER_GAMES_END    = Score4Core::FILTER_GAMES_END,
    FILTER_SCDL_FIRST   = Score4Core::FILTER_SCDL_FIRST,
    FILTER_SCDL_END     = Score4Core::FILTER_SCDL_END
};

//----------------------------------------------------------------
/**
**    マジック等の状態を示すフィルタフラグ。
**/

public enum  class  MagicFilter
{
    MF_ON_MAGIC             = Score4Core::MF_ON_MAGIC,
    MF_BEAT_IF_WIN_DIRECT   = Score4Core::MF_BEAT_IF_WIN_DIRECT,
    MF_CANNOT_BEAT_BY_SELF  = Score4Core::MF_CANNOT_BEAT_BY_SELF,
    MF_NEVER_BEAT           = Score4Core::MF_NEVER_BEAT
};

typedef     Score4Core::DateSerial      DateSerial;
typedef     Score4Core::TeamIndex       TeamIndex;
typedef     Score4Core::LeagueIndex     LeagueIndex;
typedef     Score4Core::GamesCount      GamesCount;
typedef     Score4Core::RecordIndex     RecordIndex;
typedef     Score4Core::ScoreValue      ScoreValue;
typedef     Score4Core::FileLength      FileLength;

}   //  End of namespace  Score4Wrapper
