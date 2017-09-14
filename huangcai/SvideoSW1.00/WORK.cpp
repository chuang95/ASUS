#include "stdafx.h"
#include "cfgmgr32.h"
#include "work.h"
#include "SetupAPI.h"
#include "setupapi.h"
#include "Resource.h"
#include "define.h"
#include "wchar.h"
#include "extern.h"
#include "conio.h"
#include "Svideo-diags.h"
#include "Whiteboard.h"
#include "Cpu.h"
#include "Memory.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define REGSTR_VAL_MAX_HCID_LEN		1024 

#ifdef _UNICODE 
#define DeviceProperties_RunDLL  "DeviceProperties_RunDLLW"
typedef void (_stdcall *PDEVICEPROPERTIES)(
										   HWND hwndStub,
										   HINSTANCE hAppInstance,
										   LPWSTR lpCmdLine,
										   int    nCmdShow
										   );

#else
#define DeviceProperties_RunDLL  "DeviceProperties_RunDLLA"
#endif

BOOL blCubeThread(Position *p)
{
	Whiteboard Cube(NULL,100/*p->a*/,100/*p->b*/,g_CubeSize.x, g_CubeSize.y);
	Cube.DoModal();
	return TRUE;
}

LONG64 l64AddTime(DWORD dwSecond, DWORD dwMSecond)
{
	SYSTEMTIME st;
	FILETIME ft;
	LONG64 l64Tmp = 0;
	GetSystemTime(&st);
	SystemTimeToFileTime(&st,&ft);
	l64Tmp = (LONG64)dwSecond*10000000;
	l64Tmp = l64Tmp+(LONG64)dwMSecond*10000;
	return ((LONG64)ft.dwHighDateTime<<32)+ft.dwLowDateTime+l64Tmp;
}

LONG64 l64GetTime()
{
	SYSTEMTIME st;
	FILETIME ft;
	GetSystemTime(&st);
	SystemTimeToFileTime(&st,&ft);
	return ((LONG64)ft.dwHighDateTime<<32)+ft.dwLowDateTime;
}

double dwFactorial(int n)
{
	double f = 1;
	for (int i = 2; i <=  n; ++i)
		f *=  i;
	return f;
}

double dwLogFactorial(int n)
{
	double sum = 0.0;
	for (int i = 2; i <=  n; ++i)
		sum +=  log((double)i);
	return sum;
}

bool blCountThread(int a)
{
	for(;;)
	{ 
		if(blexit)
			break;
		Sleep(100);
		//cout << std::setprecision(a);
		for (int i = 1; i < a; ++i)
		{
			double h = pow(121.123, -i);
			double n = pow(5568.4689,i);
			h = (sin(1.0+log(h)) - sin(1.0))/h*atan(n*h)/exp(tan(h)*log(n/h)) ;
			h = h*h;
			n = h*n;
		}
		for (int i = 1; i <=  a*1000000; ++i)
		{
			double s = pow(121.123, -i);
			double t = pow(5568.4689,i);
			s = (sin(1.0+log(s)) - sin(1.0))/s*atan(t*s)/exp(tan(s)*log(t/s)) ;
			s = s*s;
			t = t*dwFactorial(i);

		}		
	}
	return true;
}
struct node
{
	char data;
	node *next;
};

node *Creat(int iNum)
{
	node *p1, *p2, *head;
	int a=0;
	head=0;

	while(a<iNum*1024*1024*100)
	{
		p1 =new node;
		p1->data = 'M';
		if(head==0)
		{
			head=p1;p2=p1;
		}
		else
		{
			p2->next=p1;p2=p1;
		}

		a++;
	}
		if (head) p2->next=0;

		return(head);
}

void deletchain(node *h)
{
	node *p1;
	while(h)
	{
		p1=h;
		h=h->next;
		delete p1;
	}
}


bool blMUThread(int a)
{
	node *head;
	head=Creat(a);
	//FILE *fp;
	//fp=fopen("123.txt","a+");
	//fprintf(fp,"jk:%d\n",a);
	for(;;)
	{
		if(blexit)
		{
			deletchain(head);
			break;
		}
		//for(int i=0;i<1024;i++)
		//{
		//	for(int j=0;j<1024;j++)
		//	{
		//		for(int k=0;;k<50*a;k++)
		//			szMU[i][j][k]='M';
		//	}	
		//}
	}

	return true;
}
bool blMemoryThread()
{
	cmemory memory(NULL,GetSystemMetrics(SM_CXSCREEN)/2, 0,GetSystemMetrics(SM_CXSCREEN)/2,GetSystemMetrics(SM_CYSCREEN)/18);
	memory.DoModal();
	return TRUE;
}

bool blCPUThread()
{
	CCpu cpu(NULL,0, 0,GetSystemMetrics(SM_CXSCREEN)/2,GetSystemMetrics(SM_CYSCREEN)/18);
	cpu.DoModal();
	return TRUE;
}

bool blCountTime()
{
	//while(!kbhit()&&!blexit)
	//{
	//	///SetForegroundWindow(hwnd);					 					
	//	//SendMessage(hwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
	//	char szHour[100] = "";
	//	char szMinute[100] = "";
	//	char szSecond[100] ="";
	//	char szMh[100] = ":";
	//	char szTime[100] = "";
	//	sprintf(szHour,"%02d",(l64ExecTime-l64Timer)/(60*60));
	//	sprintf(szMinute,"%02d",((l64ExecTime-l64Timer)%(60*60))/60);
	//	sprintf(szSecond,"%02d",((l64ExecTime-l64Timer)%(60*60))%60);
	//	strcat(szTime,szHour);
	//	strcat(szTime,szMh);
	//	strcat(szTime,szMinute);
	//	strcat(szTime,szMh);
	//	strcat(szTime,szSecond);
	//	
	//	//RECT r;
	//	//GetClientRect(g_hTimeWindow, &r); 
	//	//TextOut(m_hDCTimer, r.left+(r.right - r.left)/3, r.top, szTime, strlen(szTime));
	CCountTime Time(NULL,0,17*GetSystemMetrics(SM_CYSCREEN)/18,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN)/18);
	//if(!blexit)
	//Time.vPrintCountTime(szTime);
	Time.DoModal();
	//	if(l64Timer<l64ExecTime)
	//		l64Timer++;
	//	else
	//	{
	//		blexit = TRUE;
	//		blResult==true;
	//		//SendMessage(hwnd, WM_SYSCOMMAND, SC_RESTORE, 0);
	//		//ShowWindow(wndHandle, SW_SHOW); 
	//		ShowWindow(wndHandle, SW_SHOW); 
	//		End(0);
	//	}
	//	Sleep(1000);
	//}
	return TRUE;
}