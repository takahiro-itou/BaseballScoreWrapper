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
**      マネージ型とアンマネージ型の変換。
**
**      @file       ConvertManageType.h
**/

#pragma     once

#include    "Score4Types.h"

namespace  Score4Wrapper  {

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

//----------------------------------------------------------------
/**   アンマネージ型静的配列をマネージ型配列に変換する。
**
**/

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

//----------------------------------------------------------------
/**   アンマネージ型静的配列をマネージ型配列に変換する。
**
**/

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
toManageFromTable(
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
toManageFromVector(
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
/**   マネージ型配列をアンマネージ型動的配列に変換する。
**
**/

template <typename T>
inline  void
copyManageArray1ToUnmanageVector(
        cli::array<T, 1> ^  arraySrc,
        std::vector<T>   &  vecDest)
{
    const  int  num = arraySrc->Length;
    vecDest.clear();
    vecDest.resize(num);
    for ( int i = 0; i < num; ++ i ) {
        vecDest[i]  = arraySrc[i];
    }
    return;
}

//----------------------------------------------------------------
/**   マネージ型配列をアンマネージ型テーブルに変換する。
**
**/

template <typename T>
inline  void
copyManageArray2ToUnmanageTable(
        cli::array<T, 2> ^              arraySrc,
        std::vector< std::vector<T> > & tblDest)
{
    const  int  numRows = arraySrc->GetLength(0);
    const  int  numCols = arraySrc->GetLength(1);

    tblDest.clear();
    tblDest.resize(numRows);
    for ( int r = 0; r < numRows; ++ r ) {
        std::vector<T> & tblRow = tblDest[r];
        tblRow.clear();
        tblRow.resize(numCols);
        for ( int c = 0; c < numCols; ++ c ) {
            tblRow[c] = arraySrc[r][c];
        }
    }
    return;
}

}   //  End of namespace  Score4Wrapper
