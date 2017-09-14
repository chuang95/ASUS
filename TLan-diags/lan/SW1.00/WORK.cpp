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

          //WSADATA   wsaData;                     //指向WinSocket信息结构的指针   
          //SOCKET   sockListener;   
          //SOCKADDR_IN   sin,saUdpServ;   
          //BOOL   fBroadcast   =   TRUE;   
          char   sendBuff[1025];   
          //int   nSize;   
          //int   ncount=0;   
          //if(WSAStartup(MAKEWORD(   1,   1   ),   &wsaData   )!=0)//进行WinSocket的初始化   
          //{   
          //        printf("check the loopback device.\n");//初始化失败返回-1   
          //        return   false;   
          //}   
          //sockListener=socket(PF_INET,SOCK_DGRAM,0);   
          //setsockopt   (   sockListener,SOL_SOCKET,SO_BROADCAST,   
          //        (CHAR   *)&fBroadcast,sizeof   (   BOOL   ));   
    
          //sin.sin_family   =   AF_INET;   
          //sin.sin_port   =   htons(0);   
          //sin.sin_addr.s_addr   =   htonl(INADDR_ANY);   
          //if(bind(   sockListener,   (SOCKADDR   *)&sin,   sizeof(sin))!=0)   
          //{   
          //        printf("check the loopback device.\n");//初始化失败返回-1   
          //        return   false;   
          //}   
          //saUdpServ.sin_family   =   AF_INET;   
          //saUdpServ.sin_addr.s_addr   =   htonl   (   INADDR_BROADCAST   );   
          //saUdpServ.sin_port   =   htons   (7001);//发送用的端口，可以根据需要更改   
          //nSize   =   sizeof   (   SOCKADDR_IN   );  

			//WORD wVersionRequested;
			//WSADATA wsaData;
			//int err;

			//wVersionRequested = MAKEWORD( 1, 1 );

			//err = WSAStartup( wVersionRequested, &wsaData );
			//if ( err != 0 )
			//{
			//	return false;
			//}

			//if ( LOBYTE( wsaData.wVersion ) != 1 ||
			//	HIBYTE( wsaData.wVersion ) != 1 ) 
			//{
			//	WSACleanup( );
			//	return false;
			//}
			//SOCKET sockClient=socket(AF_INET,SOCK_STREAM,0);

			//SOCKADDR_IN addrSrv;
			//addrSrv.sin_addr.S_un.S_addr=inet_addr(    ip    /*"172.24.145.72"*/);
			//addrSrv.sin_family=AF_INET;
			//addrSrv.sin_port=htons(6000);
			//connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
			memset(sendBuff,'A',1024);
			sendBuff[1024]=0;
			//int T=1;
			//if(g_szTime!=NULL)
			//{
			//	T=atoi(g_szTime);
			//}
			LONG64 l64StopTime=l64AddTime(g_T,0);
			LONG64 l64CurrentTime=0;
				long lTime=0;
			  char pStr[1024];
			memset(pStr,0,1024);
			WORD wVersionRequested;
			WSADATA wsaData;
			int err;

			wVersionRequested = MAKEWORD( 1, 1 );

			err = WSAStartup( wVersionRequested, &wsaData );
			if ( err != 0 )
			{
				return false;
			}

			if ( LOBYTE( wsaData.wVersion ) != 1 ||
				HIBYTE( wsaData.wVersion ) != 1 ) 
			{
				WSACleanup( );
				return false;
			}





          while(1)   
          {  	

			  if(g_blExit==true)
				  break;
			  DWORD *p;
			  p=(PDWORD)pStr;
			  (*p)++;
			  //printf("%02X\n",pStrpStr);
			  //vRandomStr(pStr);
 
                  //sendto   (   sockListener,pStr,   
                  //        1024/*lstrlen   (pStr)*/,   
                  //        0,   
                  //        (SOCKADDR   *)   &saUdpServ,   
                  //        sizeof   (   SOCKADDR_IN   ));
			  SOCKET sockClient=socket(AF_INET,SOCK_STREAM,0);
			  SOCKADDR_IN addrSrv;
			addrSrv.sin_addr.S_un.S_addr=inet_addr(    ip   /* "172.24.145.52"*/);
			addrSrv.sin_family=AF_INET;
			addrSrv.sin_port=htons(6000);
			  connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
			  send(sockClient,pStr,strlen(pStr)+1,0);

				  lTime++;
				  l64CurrentTime=l64GetTime();
					if(l64CurrentTime>=l64StopTime)
					{
						//textcolor(7);
						//printf("loopback upload speed is %ld Mbps\n",lTime*8*10/1024/7);
						gUploadspeed=lTime*8/1024/g_T;
						printf("send %d\n",lTime);
						lTime=0;
						l64StopTime=l64AddTime(1024,0);
						//break;
					}

				  //if(l64CurrentTime>=l64StopTime)
				  //{
					 // if(lTime>15)
					 // {
						//  printf("looback fail,check the loopback device."); 
						//  End(255);  
					 // }
				  //}
                  //printf("%s\n",sendBuff);   
          }   
}
