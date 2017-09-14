// stdafx.h : 夹繷郎い夹非╰参 Include 郎
// ┪琌竒盽ㄏノ玱ぶ跑盡盡ノ Include 郎

#pragma once
// 如果您有必須優先選取的平台，請修改下列定義。
// 參考 MSDN 取得不同平台對應值的最新資訊。
#ifndef WINVER				// 允許使用 Windows XP (含) 以後版本的特定功能。
#define WINVER 0x0501		// 將它變更為針對 Windows 其他版本的適當值。
#endif

#ifndef _WIN32_WINNT		// 允許使用 Windows XP (含) 以後版本的特定功能。
#define _WIN32_WINNT 0x0501	// 將它變更為針對 Windows 其他版本的適當值。
#endif						

#ifndef _WIN32_WINDOWS		// 允許使用 Windows 98 (含) 以後版本的特定功能。
#define _WIN32_WINDOWS 0x0410 // 將它變更為針對 Windows Me (含) 以後版本的適當值。
#endif

#ifndef _WIN32_IE			// 允許使用 IE 6.0 (含) 以後版本的特定功能。
#define _WIN32_IE 0x0600	// 將它變更為針對 IE 其他版本的適當值。
#endif

#define WIN32_LEAN_AND_MEAN		// 從 Windows 標頭排除不常使用的成員
#include <stdio.h>

#include <iostream>
#include <tchar.h>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// 絋﹚竡场だ CString 篶ㄧΑ

#ifndef VC_EXTRALEAN
  #define VC_EXTRALEAN		// 眖 Windows 夹繷逼埃ぃ盽ㄏノΘ
#endif

#include <afx.h>
#include <afxwin.h>         // MFC み籔夹非じン
#include <afxext.h>         // MFC 耎
#include <afxdtctl.h>		// MFC や穿 Internet Explorer 4 硄ノ北兜
#ifndef _AFX_NO_AFXCMN_SUPPORT
  #include <afxcmn.h>			// MFC や穿 Windows 硄ノ北兜
#endif // _AFX_NO_AFXCMN_SUPPORT

// TODO: 把σ眤祘Α┮惠璶ㄤ夹繷
#import "c:\program files\common files\system\ado\msado15.dll" \
	no_namespace \
	rename ("EOF", "adoEOF")
//#import "C:\Program Files\Common Files\System\ADO\msado15.dll" rename_namespace("ADOCG") rename("EOF", "EndOfFile") 
//using namespace ADOCG;