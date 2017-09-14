//
//#if !defined(AFX_MYADODLG_H__09FD3496_6BEF_4825_89C1_24A599681A2C__INCLUDED_)
//#define AFX_MYADODLG_H__09FD3496_6BEF_4825_89C1_24A599681A2C__INCLUDED_
//
//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000
//
///////////////////////////////////////////////////////////////////////////////
//// CMyAdoDlg dialog
//#include "ado.h"
//
//class CMyAdoDlg : public CDialog
//{
//// Construction
//public:
//	BOOL UpdateRecord(BOOL bLoad = TRUE);
//	CMyAdoDlg(CWnd* pParent = NULL);	// standard constructor
//
//// Dialog Data
//	//{{AFX_DATA(CMyAdoDlg)
//	enum { IDD = IDD_MYADO_DIALOG };
//	CString	m_strTel;
//	CString	m_strName;
//	CString m_strInfo;
//	int		m_nAge;
//	CString	m_strSex;
//	COleCurrency	m_cyMoney;
//	COleDateTime	m_dtDate;
//	CString	m_strOther;
//	float	m_fLength;
//	long	m_lPostion;
//	//}}AFX_DATA
//
//	// ClassWizard generated virtual function overrides
//	//{{AFX_VIRTUAL(CMyAdoDlg)
//	protected:
//	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
//	//}}AFX_VIRTUAL
//
//// Implementation
//protected:
//	HICON m_hIcon;
//	CAdoConnection m_adoConnection;
//	CAdoRecordSet  m_adoRecordSet;
//	CString m_strPathName;
//	CBitmap m_Bitmap;
//	// Generated message map functions
//	//{{AFX_MSG(CMyAdoDlg)
//	virtual BOOL OnInitDialog();
//	afx_msg void OnPaint();
//	afx_msg HCURSOR OnQueryDragIcon();
//	afx_msg void OnButtonBack();
//	afx_msg void OnButtonUpdate();
//	afx_msg void OnButtonForward();
//	virtual void OnOK();
//	afx_msg void OnButtonUpdatephoto();
//	virtual void OnCancel();
//	afx_msg void OnButtonCancelupdate();
//	afx_msg void OnButtonDelete();
//	afx_msg void OnButtonNew();
//	afx_msg void OnButtonBookmark();
//	afx_msg void OnButtonGobookmark();
//	afx_msg void OnPass();
//	afx_msg void OnSort();
//	afx_msg void OnButtonImport();
//	afx_msg void OnButtonExport();
//	afx_msg void OnButtonUpdateinfo();
//	afx_msg void OnButtonBack2();
//	afx_msg void OnButtonForward2();
//	afx_msg void OnButtonUpdatefieldinfo();
//	afx_msg void OnButtonUpdateconnect();
//	afx_msg void OnReset();
//	afx_msg void OnFind();
//	afx_msg void OnFindnext();
//	afx_msg void OnGrid();
//	//}}AFX_MSG
//	DECLARE_MESSAGE_MAP()
//public:
//	afx_msg void OnEnChangeEditName();
//};
//
////{{AFX_INSERT_LOCATION}}
//// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
//
//#endif // !defined(AFX_MYADODLG_H__09FD3496_6BEF_4825_89C1_24A599681A2C__INCLUDED_)
