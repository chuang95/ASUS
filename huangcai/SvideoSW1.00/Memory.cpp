// memory.cpp : ?���n
//

#include "stdafx.h"
#include "memory.h"
#include "Whiteboard.h"
#include "extern.h"

// cmemory ��?���K

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


// cmemory ?Ϣ?��ʽ

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
	// TODO: �ڴ˼�������?Ϣ?��ʽ��ʽ�a
}

void cmemory::vPrintMemory(char *str)
{
	CClientDC dc(this);
	CFont hFont;
	hFont.CreateFontA (
		GetSystemMetrics(SM_CYSCREEN)/20,      //������߼��߶�
		GetSystemMetrics(SM_CXSCREEN)/30,       //�߼�ƽ���ַ����
		0,           //��ˮƽ�ߵĽǶ�
		0,           //���߷�λ�Ƕ�
		FW_REGULAR,  //���Σ�����
		FALSE,       //���Σ�б��
		FALSE,       //���Σ��»���
		FALSE,       //���Σ�����
		GB2312_CHARSET,          //�ַ���
		OUT_DEFAULT_PRECIS,      //�������
		CLIP_DEFAULT_PRECIS,     //���ؾ���
		PROOF_QUALITY,           //���Ʒ��
		DEFAULT_PITCH | FF_MODERN, //��б��
		"Arial"                   //����
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
	// TODO: �ڴ˼����ض��ĳ�ʽ�a�� (��) ���л���?�e

	::SendMessage(::GetParent(m_hWnd),WM_CLOSE,0,0);
	CDialog::OnOK();
}

void cmemory::OnCancel()
{
	// TODO: �ڴ˼����ض��ĳ�ʽ�a�� (��) ���л���?�e
	::SendMessage(g_hwnd[0],WM_CLOSE,0,0);
	::SendMessage(g_hwnd[1],WM_CLOSE,0,0);
	::SendMessage(g_hwnd[3],WM_CLOSE,0,0);
	CDialog::OnCancel();
}
