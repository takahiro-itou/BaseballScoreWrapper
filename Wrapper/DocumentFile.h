//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  Score4 Wrapper  Library.  ---                  **
**                                                                      ***
**          Copyright (C), 2017-2020, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
**          License: (See COPYING and LICENSE files)                    **
**          GNU General Public License (GPL) version 3,                 **
**          or (at your option) any later version.                      **
**                                                                      **
*************************************************************************/

/**
**      An Interface of DocumentFile class.
**
**      @file       DocumentFile.h
**/

#pragma     once

#include    "Score4Core/Document/DocumentFile.h"

#include    "Score4Types.h"
#include    "ScoreDocument.h"


namespace  Score4Wrapper  {
namespace  Document  {

//========================================================================
//
//    DocumentFile  class.
//

public ref  class  DocumentFile
{

//========================================================================
//
//    Internal Type Definitions.
//
public:

    ref  class   BlockSizeInfo
    {
        public:

        FileLength  bsFileHead;     /**<  ファイルヘッダ領域。  **/
        FileLength  bsExtHead;      /**<  拡張ヘッダ領域。      **/
        FileLength  bsLeagure;      /**<  全リーグ分のサイズ。  **/
        FileLength  bsTeamInfo;     /**<  全チーム分のサイズ。  **/
        FileLength  bsSettings;     /**<  設定領域のサイズ。    **/
        FileLength  bsRecords;      /**<  レコード部のサイズ。  **/
        FileLength  bsFileSize;     /**<  ファイル全体の長さ。  **/

        FileLength  cbLeague;       /**<  壱リーグ分のサイズ。  **/
        FileLength  cbTeamGame;     /**<  試合数テーブル領域。  **/
        FileLength  cbTeamInfo;     /**<  チーム情報のサイズ。  **/
        FileLength  cbTeamRsvd;     /**<  チーム情報予約領域。  **/
        FileLength  cbTeamReqs;     /**<  壱チーム分のサイズ。  **/
        FileLength  cbRecsHead;     /**<  レコード部先頭領域。  **/
        FileLength  cbRecsBody;     /**<  レコード部本体領域。  **/
    };

//========================================================================
//
//    Constructor(s) and Destructor.
//
public:

    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （デフォルトコンストラクタ）。
    **
    **/
    DocumentFile();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    ~DocumentFile();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    !DocumentFile();

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
public:

    //----------------------------------------------------------------
    /**   バイナリ形式で保存するのに必要な容量を計算する。
    **
    **  @param [in] objDoc    ドキュメント。
    **  @param[out] bsInfo    各ブロックのサイズ。
    **  @return     シリアライズに必要なバイト数。
    **/
    static  FileLength
    computeImageSize(
            ScoreDocument^      objDoc,
            BlockSizeInfo^      bsInfo);

    //----------------------------------------------------------------
    /**   データをバイナリファイルから読み込む。
    **
    **  @param [in] fileName    ファイル名。
    **  @param[out] ptrDoc      ドキュメントを格納する変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    readFromBinaryFile(
            System::String^     fileName,
            ScoreDocument^      ptrDoc);

    //----------------------------------------------------------------
    /**   データをバイナリファイルに書き込む。
    **
    **  @param [in] objDoc      ドキュメント。
    **  @param [in] fileName    ファイル名。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    saveToBinaryFile(
            ScoreDocument^      objDoc,
            System::String^     fileName);

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

//========================================================================
//
//    Member Variables.
//
private:

    typedef     Score4Core::Document::DocumentFile      WrapTarget;

    WrapTarget  *       m_ptrObj;

};

}   //  End of namespace  Document
}   //  End of namespace  Score4Wrapper
