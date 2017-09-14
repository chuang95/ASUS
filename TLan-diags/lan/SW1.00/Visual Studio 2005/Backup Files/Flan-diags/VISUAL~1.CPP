// <Program Name>, Copyright by Pegatron Corp.
//-------------------------------------------------------------------------------------------------
/*
Rev 1.00: Sep 18, 2008: Craige Huang
		1: Order disk letterdisk letter
*/
//-------------------------------------------------------------------------------------------------
//#pragma comment (lib,"ws2_32.lib")
  #pragma   comment(lib,"Wininet.lib ")   
  #pragma   comment(lib,"Sensapi.LIB")   
#include "stdafx.h"
#include "Flan-diags.h"
#include "global.h"
#include "Sensapi.h"
#include   <afxinet.h>  
#include <Wininet.h>

//#include "iostream"
//using namespace std;


#define SERVER_SOCKET_ERROR 1
#define SOCKET_OK 0
#define CS_ERROR 1
#define CS_OK 0

#pragma comment(lib, "wsock32.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define sProgramDescription "Windows lantest"
#define sBuildDate "2009-02-13"
#define sRevision "1.00"

// 度Τ莱ノ祘Αン
CWinApp theApp;

using namespace std;

//-------------------------------------------------------------------------------------------------
void Logo(void)
{
	if(blNoLogo)
		return;

	if(blClearScreen)
		clrscr();

	PrintStr(0, 1, sProgramDescription, LOC_MIDDLE, DEFAULT_COLOR);
	PrintStr(0, 2, "Copyright by Pegatron, Build Date:" sBuildDate " Rev " sRevision, LOC_MIDDLE, DEFAULT_COLOR);
	PrintStr(0, 2, "SYS-DIAGS ", LOC_RIGHT, 0X08);
	PrintCh(SCREEN_LEFT, 3, '=', DEFAULT_COLOR, SCREEN_RIGHT);
	return;
}
//-------------------------------------------------------------------------------------------------
void ReadMe(void)
{
	if(!blNoLogo)
		Logo();
	
	int y = wherey();

	if(!blNoLogo)
		y = 3;

	for(int i = 1; i <= 19; i++)
		PrintCh(40, y + i, '|', 0x08, 1); // middle line
	PrintCh(SCREEN_LEFT, y + 20, '-', 0x08, SCREEN_RIGHT); // bottom line
	PrintCh(40, y + 20, '+', 0x08, 1); // intersection of bottom line and middle line

	gotoxy(SCREEN_LEFT, y + 1);
	textattr(0x08); 
	// Basic function
	_cprintf("- Basic -------------------------------\n\r");
	textattr(0x07);
	_cprintf("/?: show usage\n\r");
	_cprintf(" -nl: no display the logo and no\n\r");
	_cprintf("       clear screen\n\r");
	_cprintf(" -nc: no clear screen\n\r");
    _cprintf("/test: Test the speed of network card\n\r");
	_cprintf(" -10M: Test whether the network speed \n\r");
	_cprintf("       is higher than 1Mbps\n\r");
	_cprintf(" -100M: Test whether the network speed \n\r");
	_cprintf("       is higher than 10Mbps\n\r");
	_cprintf(" -1000M: Test whether the network speed \n\r");
	_cprintf("       is higher than 100Mbps\n\r");
	textattr(0x08);

	// Add other function descriptions here


	//RightWindow
	PrintCh(41, y + 1, '-', 0x08, SCREEN_RIGHT - 40);
	y=4;
	gotoxy(41, y++);
	_cprintf("- Test --------------------------------\n\r");
	textattr(0x07);
	gotoxy(41, y++);
	_cprintf("Flan-diags.exe /Test\n\r");gotoxy(41, y++);
	_cprintf("  Run the test");gotoxy(41, y++);
	_cprintf("\n\r");gotoxy(41, y++);
	_cprintf("Flan-diags.exe -100M /Test ");gotoxy(41, y++);
	_cprintf("  Test whether the speed of network \n\r");gotoxy(41, y++);
	_cprintf("  card is higher than 10Mbps\n\r");gotoxy(41, y++);
	gotoxy(SCREEN_LEFT, y + 5);
	End(255);
	return;
}
//-------------------------------------------------------------------------------------------------
void End(int iReturnCode)
{
	if(!blNoLogo)
	{
		int y = wherey();
		if(y < 24)
			y = 24;

		char sRetCode[20];
		sprintf_s(sRetCode, "Return Code = %d",iReturnCode);
		PrintStr(0, y, sRetCode, LOC_MIDDLE, 0x08);
	}
	Cursor(true);
  	exit(iReturnCode);
	return;
}
//--------------------------------------------------------------------------
void _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	BOOL blString10OK=false;
	BOOL blString100OK=false;
    BOOL blString1000OK=false;
	BOOL blresult10=true;
	BOOL blresult100=true;
	BOOL blresult1000=true;
	BOOL blS2=false;
	BOOL blS3=false;
	BOOL blS5=false;
	HANDLE hThread;
	// ﹍て MFC ア毖岿粇

	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
		// TODO: 皌眤惠璶跑岿粇絏
		_tprintf(_T("腨岿粇: MFC ﹍てア毖\n"));
	else
	{


		for(int i = 0; i < (argc - 1); i++) 
		{
			if(_stricmp(argv[i + 1], "-nl") == 0) 
			{
				blNoLogo = true;
				blClearScreen = false;
				continue;
			}
			// No clear the screen
			else if(_stricmp(argv[i + 1], "-nc") == 0) 
			{
				blClearScreen = false;
				continue;
			}
			 //Add other parameters here
			if(_stricmp(argv[i+1],"-10M")==0)
			{
				blString10OK=true;
			}
			if(_stricmp(argv[i+1],"-100M")==0)
			{
				blString100OK=true;
			}
			if(_stricmp(argv[i+1],"-1000M")==0)
			{
				blString1000OK=true;
			}
			if(_stricmp(argv[i+1],"-t")==0)
			{
				blStringTime=true;
				if(argv[i+2]!=NULL)
				{
					strcpy(szStr2,argv[i+2]);
					blStringN=true;
					i++;
				}
			}
		}

		if(!blNoLogo)
			Logo();


		for(int i = 0; i < (argc - 1); i++) 
		{
			if(_stricmp(argv[i + 1], "/?") == 0 ||
			   _stricmp(argv[i + 1], "/??") == 0 ||
		       _stricmp(argv[i + 1], "/h") == 0 ||
		       _stricmp(argv[i + 1], "/help") == 0) 
			{
				blParameterOK = FALSE;
				ReadMe();
			}

			// Add other function here  
			if(_stricmp(argv[i + 1], "/test")== 0)
			{

				blParameterOK=true;
				//WinExec("Server.exe",SW_SHOW);
				
				hThread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)blThread1,NULL,0,NULL);
				if(hThread==NULL)
				{
					printf("Start thread fail.\n");
				}
				WSADATA   wsaData;                     //指向WinSocket信息结构的指针   
				char name[155];
				char *ip;
				PHOSTENT hostinfo; 
				if ( WSAStartup( MAKEWORD(2,0), &wsaData ) == 0 )
				{ 
					if( gethostname ( name, sizeof(name)) == 0) 
					{ 
						if((hostinfo = gethostbyname(name)) != NULL)
						{ //这些就是获得IP的函数
							ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list); 
							char szIP[]="127.0.0.1";
								if(strcmp(ip,szIP)==0)
								{
									printf("check the loopback device");
									End(255);
								}
						} 
					} 
					WSACleanup( );
				}
				SOCKET   sockListener;   
				SOCKADDR_IN   sin,saClient;   
				char   cRecvBuff[1025];   
				int   nSize,nbSize;   
				int   iAddrLen=sizeof(saClient);   
				if(WSAStartup(MAKEWORD(   1,   1   ),   &wsaData   )!=0)//进行WinSocket的初始化   
				{   
					  printf("check the loopback device.\n");//初始化失败返回-1   
					  End(255);   
				}
				sockListener=socket(AF_INET,   SOCK_DGRAM,0);   
				sin.sin_family   =   AF_INET;   
				sin.sin_port   =   htons(7001);//发送端使用的发送端口，可以根据需要更改   
				sin.sin_addr.s_addr   =   htonl(INADDR_ANY);   
				if(bind(   sockListener,   (SOCKADDR   FAR   *)&sin,   sizeof(sin))!=0)   
				{   
					  printf("check the loopback device.\n");//初始化失败返回-1   
					  End(255);   
				}
				LONG64 l64StopTime=l64AddTime(1,0);
				LONG64 l64CurrentTime=0;
				long lTimes=0;
				char cRecvBuffTem[1025];
				DWORD dwLastValue=0;
				memset(cRecvBuffTem,'0',1024);
				cRecvBuffTem[1024]='\0';

				while(1)   
				{   
					  nSize=sizeof(SOCKADDR_IN);   
					  if((nbSize=recvfrom(sockListener,cRecvBuff,1024,0,(SOCKADDR FAR *)&saClient,&nSize))==SOCKET_ERROR)   
					  {   
							  printf("check the loopback device.");   
							  End(255);   
					  }   
					  cRecvBuff[nbSize] = '\0';   


						DWORD *p;
						p=(PDWORD)cRecvBuff;
						if(dwLastValue<*p)
						{	
							dwLastValue=*p;						
							lTimes++;
							//if(*p%0x0F==0)
							//	printf("--%08X\n",*p);

						}
					 // if(_stricmp(cRecvBuffTem, cRecvBuff)==0);
					 // else
						//lTimes++;
						memcpy(cRecvBuffTem,cRecvBuff,4);
					l64CurrentTime=l64GetTime();
					if(l64CurrentTime>=l64StopTime)
					{
						printf("loopback download speed is %ld Mbps\n",lTimes*8/1024);
						if(blString10OK==TRUE||(blString10OK==FALSE&&blString100OK==FALSE&&blString1000OK==FALSE))
						{
							if(lTimes*8/1024>1)
							{
								textcolor(10); 
								printf("test 10M      pass.\n");
								textcolor(7);
							}
							else
							{
								textcolor(12); 
								printf("test 10M      fail.\n");
								blresult10=false;
								textcolor(7);
							}
						}
						if(blString100OK==TRUE||(blString10OK==FALSE&&blString100OK==FALSE&&blString1000OK==FALSE))
						{
							if(lTimes*8/1024>10)
							{
								textcolor(10); 
								printf("test 100M     pass.\n");
								textcolor(7);
							}
							else
							{
								textcolor(12); 
								printf("test 100M     fail.\n");
								textcolor(7);
								blresult100=FALSE;
							}
						}
						if(blString1000OK==TRUE||(blString10OK==FALSE&&blString100OK==FALSE&&blString1000OK==FALSE))
						{
							if(lTimes*8/1024>100)
							{
								textcolor(10); 
								printf("test 1000M    pass.\n");
								textcolor(7);
							}
							else
							{
								textcolor(12); 
								printf("test 1000M    fail.\n");
								textcolor(7);
								blresult1000=FALSE;
							}
						}
						lTimes=0;
						l64StopTime=l64AddTime(1,0);

						break;
					}
				}
				g_blExit=true;
			}
		}

		WaitForSingleObject(hThread,INFINITE);

		if(!blParameterOK) 
			ReadMe();

		if ((blParameterOK ) == TRUE&&(blresult10==TRUE&&blresult100==TRUE&&blresult1000==TRUE))
			End(0);
		else 
			End(255);
	}

}