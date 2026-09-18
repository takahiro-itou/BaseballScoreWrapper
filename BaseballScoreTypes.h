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

#if !defined( BASEBALLSCORE_COMMON_INCLUDED_BASEBALL_SCORE_TYPES_H )
#    include    "BaseballScore/Common/BaseballScoreTypes.h"
#endif

#if !defined( BASEBALLSCORE_WRAPPER_INCLUDED_WRAPPER_NAMESPACE_H )
#    include    "WrapperNameSpace.h"
#endif


namespace  ScoreWrapper  {

//----------------------------------------------------------------
/**
**    エラーコード。
**/

public enum  class  ErrCode
{
    ERR_SUCCESS             = CoreNs::ERR_SUCCESS,
    ERR_FAILURE             = CoreNs::ERR_FAILURE,
    ERR_FILE_OPEN_ERROR     = CoreNs::ERR_FILE_OPEN_ERROR,
    ERR_FILE_IO_ERROR       = CoreNs::ERR_FILE_IO_ERROR,
    ERR_INDEX_OUT_OF_RANGE  = CoreNs::ERR_INDEX_OUT_OF_RANGE
};

typedef     CoreNs::Boolean         Boolean;

//----------------------------------------------------------------
/**
**    レコードフラグ。
**/

public enum  class  RecordFlag
{
    GAME_EMPTY          = CoreNs::GAME_EMPTY,
    GAME_SCHEDULE       = CoreNs::GAME_SCHEDULE,
    GAME_CANCEL         = CoreNs::GAME_CANCEL,
    GAME_RESULT         = CoreNs::GAME_RESULT,
    GAME_REGULAR        = CoreNs::GAME_REGULAR,
    GAME_NOT_REGULAR    = CoreNs::GAME_NOT_REGULAR
};

//----------------------------------------------------------------
/**
**    ゲームフィルタフラグ。
**/

[System::Flags]
public enum  class  GameFilter : System::Int32
{
    FILTER_HOME_GAMES   = CoreNs::FILTER_HOME_GAMES,
    FILTER_AWAY_GAMES   = CoreNs::FILTER_AWAY_GAMES,
    FILTER_ALL_GAMES    = CoreNs::FILTER_ALL_GAMES,

    FILTER_SCHEDULE     = CoreNs::FILTER_SCHEDULE,
    FILTER_SCDL_HOMES   = CoreNs::FILTER_SCDL_HOMES,
    FILTER_SCDL_AWAYS   = CoreNs::FILTER_SCDL_AWAYS,
    FILTER_SCDL_ALLS    = CoreNs::FILTER_SCDL_ALLS,

    FILTER_GAMES_FIRST  = CoreNs::FILTER_GAMES_FIRST,
    FILTER_GAMES_END    = CoreNs::FILTER_GAMES_END,
    FILTER_SCDL_FIRST   = CoreNs::FILTER_SCDL_FIRST,
    FILTER_SCDL_END     = CoreNs::FILTER_SCDL_END
};

//----------------------------------------------------------------
/**
**    マジック等の状態を示すフィルタフラグ。
**/

public enum  class  MagicFilter
{
    MF_DIFFERENT_LEAGUE     = CoreNs::MF_DIFFERENT_LEAGUE,
    MF_ON_MAGIC             = CoreNs::MF_ON_MAGIC,
    MF_MAGIC_IF_RIVAL_LOSE  = CoreNs::MF_MAGIC_IF_RIVAL_LOSE,
    MF_BEAT_IF_WIN_DIRECT   = CoreNs::MF_BEAT_IF_WIN_DIRECT,
    MF_CANNOT_BEAT_BY_SELF  = CoreNs::MF_CANNOT_BEAT_BY_SELF,
    MF_NEVER_BEAT           = CoreNs::MF_NEVER_BEAT
};

//----------------------------------------------------------------
/**
**    マジックの計算対象の種類を示す列挙型。
**/

public enum  class  MagicNumberMode
{
    MAGIC_VICTORY       = CoreNs::MAGIC_VICTORY,
    MAGIC_PLAYOFF       = CoreNs::MAGIC_PLAYOFF,
    NUM_MAGIC_MODES     = CoreNs::NUM_MAGIC_MODES
};

public enum  class  MagicInfoFlags
{
    MIF_WINS_DIFF       = CoreNs::MIF_WINS_DIFF,
    MIF_ON_MAGIC        = CoreNs::MIF_ON_MAGIC
};

//========================================================================

typedef     CoreNs::DateSerial      DateSerial;
typedef     CoreNs::TeamIndex       TeamIndex;
typedef     CoreNs::LeagueIndex     LeagueIndex;
typedef     CoreNs::GamesCount      GamesCount;
typedef     CoreNs::WinningRate     WinningRate;
typedef     CoreNs::RecordIndex     RecordIndex;
typedef     CoreNs::ScoreValue      ScoreValue;
typedef     CoreNs::NumOfDigits     NumOfDigits;
typedef     CoreNs::FileLength      FileLength;

}   //  End of namespace  ScoreWrapper
