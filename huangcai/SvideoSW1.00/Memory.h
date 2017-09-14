#pragma once

#include "Resource.h"
// cmemory 對話方塊

class cmemory : public CDialog
{
	DECLARE_DYNAMIC(cmemory)

public:
	cmemory(CWnd* pParent = NULL,int x=0,int y=0,int iwidth=0,int iheight=0);   // 標準建構函式
	virtual ~cmemory();
	static void blShowMemory(cmemory *p);
	void vPrintMemory(char *str);

// 對話方塊資料
	enum { IDD = IDD_DIALOG2 };

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
public:
//	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
	virtual void OnCancel();
};
