// CountTime.cpp : ?作檔
//

#include "stdafx.h"
#include "CountTime.h"
#include "extern.h"
#include <time.h> 
 
// CCountTime 對?方塊

IMPLEMENT_DYNAMIC(CCountTime, CDialog)

CCountTime::CCountTime(CWnd* pParent /*=NULL*/,int x,int y,int iwidth,int iheight)
	: CDialog(CCountTime::IDD, pParent)
{
	m_iPositionX=x;
	m_iPositionY=y;
	m_iHeight=iheight;
	m_iWidth=iwidth;


}

CCountTime::~CCountTime()
{
}

void CCountTime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCountTime, CDialog)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CCountTime ?息?理常式

void CCountTime::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此加入您的?息?理常式程式碼
	// 不要呼叫圖片?息的 CDialog::OnPaint()
}
void CCountTime::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, SW_FORCEMINIMIZE);
	HANDLE m_hCountTime=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)blShowCountTime,this,0,NULL);
	MoveWindow(m_iPositionX,m_iPositionY,m_iWidth,m_iHeight,TRUE);

	// TODO: 在此加入您的?息?理常式程式碼
}
BOOL CCountTime::OnInitDialog()
{
	this->ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);
	g_hwnd[3] = m_hWnd;
	return CDialog::OnInitDialog();  
}

void CCountTime::vPrintCountTime(char *str)
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
	dc.SetTextColor(RGB(255,0, 0));
	dc.SetBkColor(dc.GetPixel(0,0));


	dc.TextOutA(GetSystemMetrics(SM_CXSCREEN)/3, 17*GetSystemMetrics(SM_CYSCREEN)/18,"          ",10);
    dc.TextOutA(GetSystemMetrics(SM_CXSCREEN)/3, 17*GetSystemMetrics(SM_CYSCREEN)/18,str,(int)strlen(str));
	hFont.DeleteObject();
}
void CCountTime::blShowCountTime(CCountTime *p)
{	
	while(!blexit)
	{
		///SetForegroundWindow(hwnd);					 					
		//SendMessage(hwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
		char szHour[100] = "";
		char szMinute[100] = "";
		char szSecond[100] ="";
		char szMh[100] = ":";
		char szTime[100] = "";
		sprintf(szHour,"%02d",(l64ExecTime - l64Timer)/(60*60));
		sprintf(szMinute,"%02d",((l64ExecTime - l64Timer)%(60*60))/60);
		sprintf(szSecond,"%02d",((l64ExecTime - l64Timer)%(60*60))%60);
		strcat(szTime,szHour);
		strcat(szTime,szMh);
		strcat(szTime,szMinute);
		strcat(szTime,szMh);
		strcat(szTime,szSecond);
		
		//RECT r;
		//GetClientRect(g_hTimeWindow, &r); 
		//TextOut(m_hDCTimer, r.left+(r.right - r.left)/3, r.top, szTime, strlen(szTime));
		CCountTime Time(NULL,0,17*GetSystemMetrics(SM_CYSCREEN)/18,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN)/18);
		if(!blexit)
		    Time.vPrintCountTime(szTime);
		if(l64Timer < l64ExecTime)
			l64Timer++;
		else
		{
			blexit = TRUE;
			blResult==true;
			//SendMessage(hwnd, WM_SYSCOMMAND, SC_RESTORE, 0);
			::ShowWindow(wndHandle, SW_SHOW); 
			End(0);
		}
		Sleep(1000);

		int looptime,looptime1;
		time_t t = time(0); 
        char tmp[64]; 
timetime:      strftime(tmp, sizeof(tmp), "%X",localtime(&t));
		/*puts(tmp);*/
		printf("seconds is %s      ",tmp);
		itoa(looptime, tmp, 12);
		looptime1 = looptime;

		if (looptime >= looptime1 + 1)
			l64Timer++;
		else
			goto timetime;
		printf("zhengshu shi %d\n",l64Timer);
	}
}
void CCountTime::OnOK()
{
	// TODO: 在此加入特定的程式碼和 (或) 呼叫基底?別

	::SendMessage(::GetParent(m_hWnd),WM_CLOSE,0,0);
	CDialog::OnOK();
}
void CCountTime::OnCancel()
{
	// TODO: 在此加入特定的程式碼和 (或) 呼叫基底?別
	::SendMessage(g_hwnd[0],WM_CLOSE,0,0);
	::SendMessage(g_hwnd[2],WM_CLOSE,0,0);
	::SendMessage(g_hwnd[1],WM_CLOSE,0,0);
	CDialog::OnCancel();
}


