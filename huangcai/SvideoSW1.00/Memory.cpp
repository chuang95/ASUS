// memory.cpp : ?作檔
//

#include "stdafx.h"
#include "memory.h"
#include "Whiteboard.h"
#include "extern.h"

// cmemory 對?方塊

IMPLEMENT_DYNAMIC(cmemory, CDialog)

cmemory::cmemory(CWnd* pParent /*=NULL*/,int x,int y,int iwidth,int iheight)
	: CDialog(cmemory::IDD, pParent)
{
	m_iPositionX=x;
	m_iPositionY=y;
	m_iHeight=iheight;
	m_iWidth=iwidth;
}

cmemory::~cmemory()
{
}

void cmemory::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(cmemory, CDialog)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// cmemory ?息?理常式

void cmemory::OnPaint()
{
	CPaintDC dc(this); 
}

void cmemory::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, SW_PARENTCLOSING);
	HANDLE m_hMemory=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)blShowMemory,this,0,NULL);
	MoveWindow(m_iPositionX,m_iPositionY,m_iWidth,m_iHeight,TRUE);
	g_hwnd[2] = m_hWnd;
	// TODO: 在此加入您的?息?理常式程式碼
}

void cmemory::vPrintMemory(char *str)
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
void cmemory::blShowMemory(cmemory *p)
{
	while(true)
	{
		//if(blMemoryexit)
		//	break;
		char szMemory[100] = "";
		MEMORYSTATUSEX statex;
		statex.dwLength = sizeof (statex);
		GlobalMemoryStatusEx (&statex);
		sprintf (szMemory, "memory %ld%%", statex.dwMemoryLoad);		
		p->vPrintMemory(szMemory);
		Sleep(1000);
	}


}

void cmemory::OnOK()
{
	// TODO: 在此加入特定的程式碼和 (或) 呼叫基底?別

	::SendMessage(::GetParent(m_hWnd),WM_CLOSE,0,0);
	CDialog::OnOK();
}

void cmemory::OnCancel()
{
	// TODO: 在此加入特定的程式碼和 (或) 呼叫基底?別
	::SendMessage(g_hwnd[0],WM_CLOSE,0,0);
	::SendMessage(g_hwnd[1],WM_CLOSE,0,0);
	::SendMessage(g_hwnd[3],WM_CLOSE,0,0);
	CDialog::OnCancel();
}
