#pragma once
#include "resource.h"

// Cdet ��Ԓ���K

class Cdet : public CDialog
{
	DECLARE_DYNAMIC(Cdet)

public:
	Cdet(CWnd* pParent = NULL);   // �˜ʽ�����ʽ
	virtual ~Cdet();

// ��Ԓ���K�Y��
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧Ԯ

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
