#pragma once

#include "Resource.h"
// cmemory ��Ԓ���K

class cmemory : public CDialog
{
	DECLARE_DYNAMIC(cmemory)

public:
	cmemory(CWnd* pParent = NULL,int x=0,int y=0,int iwidth=0,int iheight=0);   // �˜ʽ�����ʽ
	virtual ~cmemory();
	static void blShowMemory(cmemory *p);
	void vPrintMemory(char *str);

// ��Ԓ���K�Y��
	enum { IDD = IDD_DIALOG2 };

public:
	int m_iWidth;
	int m_iHeight;
	int m_iPositionX;
	int m_iPositionY;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧Ԯ

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
