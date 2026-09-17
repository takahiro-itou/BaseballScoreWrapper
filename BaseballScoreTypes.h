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
**      @file       BaseballScoreTypes.h
**/

#pragma     once

#include    "BaseballScore/Common/BaseballScoreTypes.h"

namespace   WrapCoreNs  = BaseballScore;


namespace  ScoreWrapper  {

//----------------------------------------------------------------
/**
**    エラーコード。
**/

public enum  class  ErrCode
{
    ERR_SUCCESS             = WrapCoreNs::ERR_SUCCESS,
    ERR_FAILURE             = WrapCoreNs::ERR_FAILURE,
    ERR_FILE_OPEN_ERROR     = WrapCoreNs::ERR_FILE_OPEN_ERROR,
    ERR_FILE_IO_ERROR       = WrapCoreNs::ERR_FILE_IO_ERROR,
    ERR_INDEX_OUT_OF_RANGE  = WrapCoreNs::ERR_INDEX_OUT_OF_RANGE
};

typedef     WrapCoreNs::Boolean         Boolean;

//----------------------------------------------------------------
/**
**    レコードフラグ。
**/

public enum  class  RecordFlag
{
    GAME_EMPTY          = WrapCoreNs::GAME_EMPTY,
    GAME_SCHEDULE       = WrapCoreNs::GAME_SCHEDULE,
    GAME_CANCEL         = WrapCoreNs::GAME_CANCEL,
    GAME_RESULT         = WrapCoreNs::GAME_RESULT,
    GAME_REGULAR        = WrapCoreNs::GAME_REGULAR,
    GAME_NOT_REGULAR    = WrapCoreNs::GAME_NOT_REGULAR
};

//----------------------------------------------------------------
/**
**    ゲームフィルタフラグ。
**/

[System::Flags]
public enum  class  GameFilter : System::Int32
{
    FILTER_HOME_GAMES   = WrapCoreNs::FILTER_HOME_GAMES,
    FILTER_AWAY_GAMES   = WrapCoreNs::FILTER_AWAY_GAMES,
    FILTER_ALL_GAMES    = WrapCoreNs::FILTER_ALL_GAMES,

    FILTER_SCHEDULE     = WrapCoreNs::FILTER_SCHEDULE,
    FILTER_SCDL_HOMES   = WrapCoreNs::FILTER_SCDL_HOMES,
    FILTER_SCDL_AWAYS   = WrapCoreNs::FILTER_SCDL_AWAYS,
    FILTER_SCDL_ALLS    = WrapCoreNs::FILTER_SCDL_ALLS,

    FILTER_GAMES_FIRST  = WrapCoreNs::FILTER_GAMES_FIRST,
    FILTER_GAMES_END    = WrapCoreNs::FILTER_GAMES_END,
    FILTER_SCDL_FIRST   = WrapCoreNs::FILTER_SCDL_FIRST,
    FILTER_SCDL_END     = WrapCoreNs::FILTER_SCDL_END
};

//----------------------------------------------------------------
/**
**    マジック等の状態を示すフィルタフラグ。
**/

public enum  class  MagicFilter
{
    MF_DIFFERENT_LEAGUE     = WrapCoreNs::MF_DIFFERENT_LEAGUE,
    MF_ON_MAGIC             = WrapCoreNs::MF_ON_MAGIC,
    MF_MAGIC_IF_RIVAL_LOSE  = WrapCoreNs::MF_MAGIC_IF_RIVAL_LOSE,
    MF_BEAT_IF_WIN_DIRECT   = WrapCoreNs::MF_BEAT_IF_WIN_DIRECT,
    MF_CANNOT_BEAT_BY_SELF  = WrapCoreNs::MF_CANNOT_BEAT_BY_SELF,
    MF_NEVER_BEAT           = WrapCoreNs::MF_NEVER_BEAT
};

//----------------------------------------------------------------
/**
**    マジックの計算対象の種類を示す列挙型。
**/

public enum  class  MagicNumberMode
{
    MAGIC_VICTORY       = WrapCoreNs::MAGIC_VICTORY,
    MAGIC_PLAYOFF       = WrapCoreNs::MAGIC_PLAYOFF,
    NUM_MAGIC_MODES     = WrapCoreNs::NUM_MAGIC_MODES
};

public enum  class  MagicInfoFlags
{
    MIF_WINS_DIFF       = WrapCoreNs::MIF_WINS_DIFF,
    MIF_ON_MAGIC        = WrapCoreNs::MIF_ON_MAGIC
};

//========================================================================

typedef     WrapCoreNs::DateSerial      DateSerial;
typedef     WrapCoreNs::TeamIndex       TeamIndex;
typedef     WrapCoreNs::LeagueIndex     LeagueIndex;
typedef     WrapCoreNs::GamesCount      GamesCount;
typedef     WrapCoreNs::WinningRate     WinningRate;
typedef     WrapCoreNs::RecordIndex     RecordIndex;
typedef     WrapCoreNs::ScoreValue      ScoreValue;
typedef     WrapCoreNs::NumOfDigits     NumOfDigits;
typedef     WrapCoreNs::FileLength      FileLength;

}   //  End of namespace  ScoreWrapper
