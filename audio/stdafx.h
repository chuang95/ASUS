// stdafx.h : 可在此標頭檔中包含標準的系統 Include 檔，
// 或是經常使用卻很少變更的專案專用 Include 檔案
//

#pragma once


#include <iostream>
#include <tchar.h>

// TODO: 在此參考您的程式所需要的其他標頭
/*
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// 明確定義部分的 CString 建構函式

//#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// 從 Windows 標頭排除不常使用的成員
//#endif
*/


#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#endif

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0600	// Change this to the appropriate value to target other versions of Windows.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS



#include <afx.h>
#include <afxwin.h>         // MFC 核心與標準元件
#include <afxext.h>         // MFC 擴充功能
#include <afxdtctl.h>		// MFC 支援的 Internet Explorer 4 通用控制項
#include <afxtempl.h>       // MFC templates
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC 支援的 Windows 通用控制項
#endif // _AFX_NO_AFXCMN_SUPPORT