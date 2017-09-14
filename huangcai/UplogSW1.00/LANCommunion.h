// LANCommunion.h : main header file for the LANCOMMUNION application
//

#if !defined(AFX_LANCOMMUNION_H__2C815209_06C1_46E9_969F_B17DF3BC133E__INCLUDED_)
#define AFX_LANCOMMUNION_H__2C815209_06C1_46E9_969F_B17DF3BC133E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLANCommunionApp:
// See LANCommunion.cpp for the implementation of this class
//

class CLANCommunionApp : public CWinApp
{
public:
	CLANCommunionApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLANCommunionApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLANCommunionApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LANCOMMUNION_H__2C815209_06C1_46E9_969F_B17DF3BC133E__INCLUDED_)
