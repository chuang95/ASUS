#pragma once
#include "resource.h"

// Cdet 對話方塊

class Cdet : public CDialog
{
	DECLARE_DYNAMIC(Cdet)

public:
	Cdet(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~Cdet();

// 對話方塊資料
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
public:
	virtual BOOL OnInitDialog();
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void OnOK();
	virtual void OnCancel();
public:
//	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
