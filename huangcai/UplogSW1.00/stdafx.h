// stdafx.h : �i�b�����Y�ɤ��]�t�зǪ��t�� Include �ɡA
// �άO�g�`�ϥΫo�ܤ��ܧ󪺱M�ױM�� Include �ɮ�

#pragma once
// ������б�횃����xȡ��ƽ̨��Ո�޸����ж��x��
// ���� MSDN ȡ�ò�ͬƽ̨����ֵ�������YӍ��
#ifndef WINVER				// ���Sʹ�� Windows XP (��) ����汾���ض����ܡ�
#define WINVER 0x0501		// ����׃����ᘌ� Windows �����汾���m��ֵ��
#endif

#ifndef _WIN32_WINNT		// ���Sʹ�� Windows XP (��) ����汾���ض����ܡ�
#define _WIN32_WINNT 0x0501	// ����׃����ᘌ� Windows �����汾���m��ֵ��
#endif						

#ifndef _WIN32_WINDOWS		// ���Sʹ�� Windows 98 (��) ����汾���ض����ܡ�
#define _WIN32_WINDOWS 0x0410 // ����׃����ᘌ� Windows Me (��) ����汾���m��ֵ��
#endif

#ifndef _WIN32_IE			// ���Sʹ�� IE 6.0 (��) ����汾���ض����ܡ�
#define _WIN32_IE 0x0600	// ����׃����ᘌ� IE �����汾���m��ֵ��
#endif

#define WIN32_LEAN_AND_MEAN		// �� Windows ���^�ų�����ʹ�õĳɆT
#include <stdio.h>

#include <iostream>
#include <tchar.h>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// ���T�w�q������ CString �غc�禡

#ifndef VC_EXTRALEAN
  #define VC_EXTRALEAN		// �q Windows ���Y�ư����`�ϥΪ�����
#endif

#include <afx.h>
#include <afxwin.h>         // MFC �֤߻P�зǤ���
#include <afxext.h>         // MFC �X�R�\��
#include <afxdtctl.h>		// MFC �䴩�� Internet Explorer 4 �q�α��
#ifndef _AFX_NO_AFXCMN_SUPPORT
  #include <afxcmn.h>			// MFC �䴩�� Windows �q�α��
#endif // _AFX_NO_AFXCMN_SUPPORT

// TODO: �b���Ѧұz���{���һݭn����L���Y
#import "c:\program files\common files\system\ado\msado15.dll" \
	no_namespace \
	rename ("EOF", "adoEOF")
//#import "C:\Program Files\Common Files\System\ADO\msado15.dll" rename_namespace("ADOCG") rename("EOF", "EndOfFile") 
//using namespace ADOCG;