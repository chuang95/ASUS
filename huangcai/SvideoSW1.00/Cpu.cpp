
#include "stdafx.h"
#include "Cpu.h"
#include <conio.h>
#include "extern.h"
#include <stdio.h> 
#include <string>   
#include <iomanip>   
#include <iostream>   
#include <windows.h>   
#include <cmath>
#include <cfloat>




#define VK_RKEY 0x52
#define VK_GKEY 0x47
#define VK_BKEY 0x42
#define VK_YKEY 0x59
#define VK_NKEY 0x4E
#define SystemBasicInformation       0
#define SystemPerformanceInformation 2
#define SystemTimeInformation        3
#define Li2Double(x) ((double)((x).HighPart) * 4.294967296E9 + (double)((x).LowPart))

typedef LONG (WINAPI *PROCNTQSI)(UINT,PVOID,ULONG,PULONG);
LONG64 currenttime;
LONG64 stoptime;

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


// CCpu 對?方塊

IMPLEMENT_DYNAMIC(CCpu, CDialog)

CCpu::CCpu(CWnd* pParent /*=NULL*/,int x,int y,int iwidth,int iheight)
	: CDialog(CCpu::IDD, pParent)
{
	m_iPositionX=x;
	m_iPositionY=y;
	m_iHeight=iheight;
	m_iWidth=iwidth;


}

CCpu::~CCpu()
{
}

void CCpu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCpu, CDialog)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CCpu ?息?理常式

void CCpu::OnPaint()
{
}

void CCpu::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow,SW_PARENTCLOSING);
	HANDLE m_hCpu=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)blShowCPU,this,0,NULL);
	MoveWindow(m_iPositionX,m_iPositionY,m_iWidth,m_iHeight,TRUE);
	g_hwnd[1] = m_hWnd;
	// TODO: 在此加入您的?息?理常式程式碼
}


BOOL CCpu::OnInitDialog()
{
	CDialog::OnInitDialog();

	//this->ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);
	//this->SetTimer(1, 10000, NULL);

	return TRUE; 
}

void CCpu::OnTimer(UINT_PTR nIDEvent)
{
	//KillTimer(1);
	//PostQuitMessage(0);

	CDialog::OnTimer(nIDEvent);
}
void CCpu::vPrintCPU(char *str)
{
	CClientDC dc(this);
	CFont hFont;
	hFont.CreateFontA (
		GetSystemMetrics(SM_CYSCREEN)/20,      //字体的逻辑高度
		GetSystemMetrics(SM_CXSCREEN)/30,       //逻辑平均字符宽度
		0,           //与水平线的角度
		0,           //基线方位角度
		FW_REGULAR,  //字形：常规
		FALSE,       //字形：斜体
		FALSE,       //字形：下划线
		FALSE,       //字形：粗体
		GB2312_CHARSET,          //字符集
		OUT_DEFAULT_PRECIS,      //输出精度
		CLIP_DEFAULT_PRECIS,     //剪截精度
		PROOF_QUALITY,           //输出品质
		DEFAULT_PITCH | FF_MODERN, //倾斜度
		"Arial"                   //字体
		); 
	dc.SelectObject(hFont);
	dc.SetTextColor(RGB(0,255, 0));
	dc.SetBkColor(dc.GetPixel(0,0));
	dc.TextOutA(GetSystemMetrics(SM_CXSCREEN)/10, 0,"          ",10);
	dc.TextOutA(GetSystemMetrics(SM_CXSCREEN)/10, 0,str,(int)strlen(str));
	hFont.DeleteObject();
}
void CCpu::blShowCPU(CCpu *p)
{
    SYSTEM_PERFORMANCE_INFORMATION SysPerfInfo;
    SYSTEM_TIME_INFORMATION        SysTimeInfo;
    SYSTEM_BASIC_INFORMATION       SysBaseInfo;
    double                         dbIdleTime;
    double                         dbSystemTime;
    LONG                           status;
    LARGE_INTEGER                  liOldIdleTime = {0,0};
    LARGE_INTEGER                  liOldSystemTime = {0,0};
    p->NtQuerySystemInformation = (PROCNTQSI)GetProcAddress(GetModuleHandle("ntdll"),"NtQuerySystemInformation");
    if (!p->NtQuerySystemInformation)      
		return;
    status = p->NtQuerySystemInformation(SystemBasicInformation,&SysBaseInfo,sizeof(SysBaseInfo),NULL);
    if (status != NO_ERROR)       
		return;

	char szCpu[100]={0};

    while(!_kbhit())
    {

		status = p->NtQuerySystemInformation(SystemTimeInformation,&SysTimeInfo,sizeof(SysTimeInfo),0);
        if (status!=NO_ERROR)      
			return;
        status = p->NtQuerySystemInformation(SystemPerformanceInformation,&SysPerfInfo,sizeof(SysPerfInfo),NULL);
        if (status != NO_ERROR)    
			return;
		if (liOldIdleTime.QuadPart != 0)
		{
			dbIdleTime = Li2Double(SysPerfInfo.liIdleTime) - Li2Double(liOldIdleTime);
			dbSystemTime = Li2Double(SysTimeInfo.liKeSystemTime) - Li2Double(liOldSystemTime);
			dbIdleTime = dbIdleTime / dbSystemTime;
			dbIdleTime = 100.0 - dbIdleTime * 100.0 / (double)SysBaseInfo.bKeNumberProcessors;
			sprintf_s(szCpu,100,"cpu %3d%%",(int)dbIdleTime);
			p->vPrintCPU(szCpu);
		}
        liOldIdleTime = SysPerfInfo.liIdleTime;
        liOldSystemTime = SysTimeInfo.liKeSystemTime;
		Sleep(1000);
    }
}
void CCpu::OnOK()
{
	// TODO: 在此加入特定的程式碼和 (或) 呼叫基底?別

	::SendMessage(::GetParent(m_hWnd),WM_CLOSE,0,0);
	CDialog::OnOK();
}

void CCpu::OnCancel()
{
	// TODO: 在此加入特定的程式碼和 (或) 呼叫基底?別
	::SendMessage(g_hwnd[0],WM_CLOSE,0,0);
	::SendMessage(g_hwnd[2],WM_CLOSE,0,0);
	::SendMessage(g_hwnd[3],WM_CLOSE,0,0);
	CDialog::OnCancel();
}

