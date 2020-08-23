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
**      An Implementation of DocumentFile class.
**
**      @file       DocumentFile.cpp
**/

#include    "StdAfx.h"

#include    "DocumentFile.h"

#include    <msclr/marshal_cppstd.h>
using       namespace   msclr::interop;


namespace  Score4Wrapper  {
namespace  Common  {

//========================================================================
//
//    DocumentFile  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

DocumentFile::DocumentFile()
    : m_ptrObj { new WrapTarget() }
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

DocumentFile::~DocumentFile()
{
    this->!DocumentFile();
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

DocumentFile::!DocumentFile()
{
    if ( this->m_ptrObj ) {
        delete  this->m_ptrObj;
        this->m_ptrObj  = nullptr;
    }
}

//========================================================================
//
//    Public Member Functions (Implement Pure Virtual).
//

//========================================================================
//
//    Public Member Functions (Overrides).
//

//========================================================================
//
//    Public Member Functions (Pure Virtual Functions).
//

//========================================================================
//
//    Public Member Functions (Virtual Functions).
//

//========================================================================
//
//    Public Member Functions.
//

//----------------------------------------------------------------
//    バイナリ形式で保存するのに必要な容量を計算する。
//

FileLength
DocumentFile::computeImageSize(
        ScoreDocument^      objDoc,
        BlockSizeInfo^      bsInfo)
{
    WrapTarget::BlockSizeInfo       natvBsInfo;
    FileLength  retVal  = WrapTarget::computeImageSize(
                                objDoc->toNativeInstance(),
                                &natvBsInfo);
    bsInfo->bsFileHead  = natvBsInfo.bsFileHead;
    return ( retVal );
}

//----------------------------------------------------------------
//    データをバイナリファイルから読み込む。
//

ErrCode
DocumentFile::readFromBinaryFile(
        System::String^     fileName,
        ScoreDocument^      ptrDoc)
{
    const   Score4Core::ErrCode
        retVal = WrapTarget::readFromBinaryFile(
                    marshal_as<std::string>(fileName),
                    ptrDoc->toNativePointer());
    return ( static_cast<ErrCode>(retVal) );
}

//----------------------------------------------------------------
//    データをバイナリファイルに書き込む。
//

ErrCode
DocumentFile::saveToBinaryFile(
        ScoreDocument^      objDoc,
        System::String^     fileName)
{
    const   Score4Core::ErrCode
        retVal = WrapTarget::saveToBinaryFile(
                    objDoc->toNativeInstance(),
                    marshal_as<std::string>(fileName));
    return ( static_cast<ErrCode>(retVal) );
}

//========================================================================
//
//    Accessors.
//

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Common
}   //  End of namespace  Score4Wrapper
