#pragma once

#include "Resource.h"
// CCpu 對話方塊

class CCpu : public CDialog
{
	DECLARE_DYNAMIC(CCpu)

	#define SystemBasicInformation       0
	#define SystemPerformanceInformation 2
	#define SystemTimeInformation        3
	#define Li2Double(x) ((double)((x).HighPart) * 4.294967296E9 + (double)((x).LowPart))
	public:

	typedef struct
	{
		DWORD   dwUnknown1;
		ULONG   uKeMaximumIncrement;
		ULONG   uPageSize;
		ULONG   uMmNumberOfPhysicalPages;
		ULONG   uMmLowestPhysicalPage;
		ULONG   uMmHighestPhysicalPage;
		ULONG   uAllocationGranularity;
		PVOID   pLowestUserAddress;
		PVOID   pMmHighestUserAddress;
		ULONG   uKeActiveProcessors;
		BYTE    bKeNumberProcessors;
		BYTE    bUnknown2;
		WORD    wUnknown3;
	} SYSTEM_BASIC_INFORMATION;
	typedef struct
	{
		LARGE_INTEGER   liIdleTime;
		DWORD           dwSpare[76];
	} SYSTEM_PERFORMANCE_INFORMATION;
	typedef struct
	{
		LARGE_INTEGER liKeBootTime;
		LARGE_INTEGER liKeSystemTime;
		LARGE_INTEGER liExpTimeZoneBias;
		ULONG         uCurrentTimeZoneId;
		DWORD         dwReserved;
	} SYSTEM_TIME_INFORMATION;
	typedef LONG (WINAPI *PROCNTQSI)(UINT,PVOID,ULONG,PULONG);
	PROCNTQSI NtQuerySystemInformation;

public:
	CCpu(CWnd* pParent = NULL,int x=0,int y=0,int iwidth=0,int iheight=0);   // 標準建構函式
	virtual ~CCpu();
	static void blShowCPU(CCpu *p);
	void vPrintCPU(char *str);
// 對話方塊資料
	enum { IDD = IDD_DIALOG3 };

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
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	virtual void OnOK();
	virtual void OnCancel();
};
