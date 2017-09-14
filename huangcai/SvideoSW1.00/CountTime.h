#pragma once
#include "Resource.h"

// CCountTime 對話方塊

class CCountTime : public CDialog
{
	DECLARE_DYNAMIC(CCountTime)

public:
	CCountTime(CWnd* pParent /*= NULL*/,int x=0,int y=0,int iwidth=0,int iheight=0);   // 標準建構函式
	virtual ~CCountTime();
	static void blShowCountTime(CCountTime *p);
	void vPrintCountTime(char *str);

// 對話方塊資料
	enum { IDD = IDD_DIALOG4 };

public:
	int m_iWidth;
	int m_iHeight;
	int m_iPositionX;
	int m_iPositionY;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
protected:
	virtual void OnCancel();
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
};
