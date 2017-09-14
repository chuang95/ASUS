#include "stdafx.h"
#include "work.h"
#include "extern.h"
#include <windows.h>
#include <winsock.h>
#include <iostream>
#include "time.h"
#include "conio.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

//CWinApp theApp;

//using namespace std;



LONG64 l64AddTime(DWORD dwSecond, DWORD dwMSecond)
{
	SYSTEMTIME st;
	FILETIME ft;
	LONG64 l64Tmp=0;
	GetSystemTime(&st);
	SystemTimeToFileTime(&st,&ft);
	l64Tmp=(LONG64)dwSecond*10000000;
	l64Tmp=l64Tmp+(LONG64)dwMSecond*10000;
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
void sError(char *str)
{
	MessageBox(NULL, str, "SOCKET ERROR", MB_OK);
	WSACleanup();
}
void vRandomStr(char *pStr)
{
	char szStr[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-=~`!@#$%^&*()_+[]{};':,.<>/?";
				memset(pStr,'A',1024);
			pStr[1024]=0;
	int i=0;
	for(i=0;i<10;i++)
		pStr[i]=szStr[rand()%strlen(szStr)];
	pStr[1024]='\0';
	//DWORD *p;
	//p=(PDWORD)pStr;
	//(*p)++;
}
bool blThread1()
{

	WSADATA   wsaData;                    
	SOCKET   sockListener;   
	SOCKADDR_IN   sin,saUdpServ;   
	BOOL   fBroadcast   =   TRUE;   
	char   sendBuff[1025];   
	int   nSize;   
	int   ncount=0;   

	if(WSAStartup(MAKEWORD( 1, 1 ), &wsaData )!=0)
	{   
		  printf("check the loopback device.\n");
		  return   false;
	}

	sockListener=socket(PF_INET,SOCK_DGRAM,0);   
	setsockopt(sockListener,SOL_SOCKET,SO_BROADCAST,(CHAR  *)&fBroadcast,sizeof(BOOL));   

	sin.sin_family = AF_INET;   
	sin.sin_port = htons(7000);   
	sin.sin_addr.s_addr = htonl(INADDR_ANY);   
	if(bind( sockListener, (SOCKADDR *)&sin, sizeof(sin)) != 0)
	{   
		  printf("check the loopback device.\n");
		  return   false;   
	}   
	saUdpServ.sin_family = AF_INET;   
	saUdpServ.sin_addr.s_addr = /*   inet_addr(  ip );"172.24.145.72"  */ htonl(INADDR_BROADCAST); 
	saUdpServ.sin_port = htons (7001);   
	nSize   =   sizeof   (   SOCKADDR_IN   );  
	//memset(sendBuff,'A',1024);
	//sendBuff[1024]=0;
	//int T=1;
	//if(g_szTime!=NULL)
	//{
	//	T=atoi(g_szTime);
	//}
	LONG64 l64StopTime=l64AddTime(g_T,0);
	LONG64 l64CurrentTime=0;
		long lTime=0;
		BOOL blSleepbreak=false;
	  char pStr[1024];
	memset(pStr,0,1024);

	LONG64 l64BreakTime=l64AddTime(g_T,0);

	for(int i=0;i<g_T*20;i++)
	{
		if((i+1)%2==0)
		{
			Sleep(100);
			continue;
		}

		if(g_blExit==true)
			break;

		l64BreakTime=l64AddTime(0,100);
		while(1)
		{
			l64CurrentTime=l64GetTime();
			if(l64CurrentTime>=l64BreakTime)
				break;
			if(g_blExit==true)
				break;

			DWORD *p;
			p=(PDWORD)pStr;
			(*p)++;
			sendto(sockListener,pStr,1024,0, (SOCKADDR *) &saUdpServ, sizeof(SOCKADDR_IN));
			lTime++;
			l64CurrentTime=l64GetTime();
			if(l64CurrentTime>=l64StopTime)
			{
				gUploadspeed=lTime*8/1024/g_T/*-10*/*2;
				//printf("%d\n",lTime);
				//printf("%d\n",g_T);
				blSleepbreak=true;
				lTime=0;
				l64StopTime=l64AddTime(1024,0);
			}
		}
	}
		  return true;

}
