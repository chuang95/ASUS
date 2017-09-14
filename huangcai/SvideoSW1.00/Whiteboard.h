#pragma once
#include "Windows.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include "conio.h"
#include "Resource.h"
//#include "cpumemory.h"
// Whiteboard 對話方塊

class Whiteboard : public CDialog
{
	DECLARE_DYNAMIC(Whiteboard)

public:
	Whiteboard(CWnd* pParent = NULL,int x=0,int y=0,int iwidth=0,int iheight=0);   // 標準建構函式
	virtual ~Whiteboard();

// 對話方塊資料
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	int m_iWidth;
	int m_iHeight;
	int m_iPositionX;
	int m_iPositionY;
	GLdouble m_xRotate;
	GLdouble m_yRotate;
	float m_fSize;
	HGLRC m_hGLContext;
	int m_GLPixelIndex;
	float m_ScaleX;
	float m_ScaleY;
	float m_ScaleZ;
	//double   m_dbIdleTime;
	//CCpuMemory CpuDlg;
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
	void vBuildList();
	void vInitGL();
	void RenderScene();
	BOOL SetWindowPixelFormat(HDC hDC);
	BOOL CreateViewGLContext(HDC hDC);

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	afx_msg void OnPaint();
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	virtual BOOL OnInitDialog();
//public:
//    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

protected:
//	virtual void OnOK();
//	virtual void OnCancel();
	virtual void OnCancel();
	virtual void OnOK();
};