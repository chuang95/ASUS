// <Program Name>, Copyright by Pegatron Corp.
//-------------------------------------------------------------------------------------------------
#include"stdafx.h"
#include "Svideo-diags.h"
#include "WORK.h"
#include "SetupAPI.h"
#include "setupapi.h"
#include "global.h"
#include<iostream>
#include <conio.h>
#include<cfgmgr32.h>
#include <conio.h>
#include <stdio.h> 
#include <string>   
#include <iomanip>  
#include <windows.h>   
#include <cmath>
#include <cfloat>
#include "Whiteboard.h"
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define sProgramDescription "Windows Device management"
#define sBuildDate "2009-08-06"
#define sRevision "1.01c"
#define DIV 1024
#define WIDTH 7
#define MAX_WIDTH_NUMBER 20
#define MAX_HEIGHT_NUMBER 20
#define MAX_FORM 15
// 僅有的一個應用程式物件
CWinApp theApp;

using namespace std;
HWND m_hWindow;
CubeSize g_CubeSize = {0};
int nFormNum = 1;


bool blThread1()
{
	for(int i=0;i<1;i++)
	{
		keybd_event(VK_RETURN,0,0,0);
		keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP,0);
	}
	return true;
}

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
	_cprintf("/?: Show usage.\n\r");
	_cprintf("  -nl: No display the logo and no\n\r");
	_cprintf("       clear screen.\n\r");
	_cprintf("  -nc: No clear screen.\n\r");
	_cprintf("  -erv <errorlevel>: Return error code.\n\r");
    _cprintf("/VERSION: Show program version.\n\r");
    _cprintf("/R: Run the program.\n\r");
	_cprintf("  -num: Set the number of the forms,\n\r");
	_cprintf("        the number < 400.\n\r");
	_cprintf("  -t <h> <m> <s>: Set the time of the \n\r");
	_cprintf("        test, the unit is hour minute \n\r");
	_cprintf("        and second, default is 30s.\n\r");
	//_cprintf("    and waiting for clients.\n\r");
	//_cprintf("/C: Set a client and send uplog to \n\r");
	//_cprintf("    server.\n\r");
	//_cprintf(" -ip: the server ip.\n\r");
	textattr(0x08);

	// Add other function descriptions here


	//RightWindow
	PrintCh(41, y + 1, '-', 0x08, SCREEN_RIGHT - 40);
	y=4;
	gotoxy(41, y++);
	_cprintf("- Test --------------------------------\n\r");
	textattr(0x07);
	gotoxy(41, y++);
	_cprintf("Svideo-diags.exe /?");gotoxy(41, ++y);
	_cprintf(" -Show usage");gotoxy(41, ++y);
	_cprintf("Svideo-diags.exe /R ");gotoxy(41, ++y);
	_cprintf(" -Run 1 forms for 30 seconds");gotoxy(41, ++y);
    //_cprintf("  for 30 seconds");gotoxy(41, ++y);
	_cprintf("Svideo-diags.exe -num 5 /R");gotoxy(41, ++y);
	_cprintf(" -Run 5 forms at the same time for 30 ");gotoxy(41, ++y);
    _cprintf("  seconds");gotoxy(41, ++y);
	_cprintf("Svideo-diags.exe -num 10 -t 2 0 40 /R");gotoxy(41, ++y);
	_cprintf(" -Run 10 forms at the same time for 2 ");gotoxy(41, ++y);
    _cprintf("  hours and 40 seconds");gotoxy(41, ++y);
	////_cprintf("\n\r");gotoxy(41, y++);
	//_cprintf("  Set a client,connect to the server \n\r");gotoxy(41, y++);
	//_cprintf("  whoses ip is 172.24.145.34.\n\r");gotoxy(41, y++);
	gotoxy(SCREEN_LEFT, y + 5);
	End(nErrorLevel);
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
	HWND hwnd = NULL;
    HANDLE hThread;
	BOOL blUSBOK=false;
	BOOL blLanOK=false;
	HANDLE hCPUThread = NULL;
	HANDLE hMemoryThread = NULL;

	char szStr[100];

	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
		// TODO: 配合您的需要變更錯誤碼
		_tprintf(_T("嚴重錯誤: MFC 初始化失敗\n"));
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
			//else if(stricmp(argv[i + 1], "-erv") == 0) 
			//{
			//	if(argv[i + 2]!=NULL)
			//	{
			//		nErrorLevel= atoi(argv[i + 2]);
			//	}
			//	continue;
			//}
			if(_stricmp(argv[i+1], "-num") == 0)
			{					
				if(argc > i+2)
					nFormNum = atoi(argv[i+2]);
				if(nFormNum > MAX_FORM)
					nFormNum = MAX_FORM;			
			}

			else if(stricmp(argv[i + 1], "-erv") == 0) 
			{
				if(argv[i + 2]!=NULL)
				{
					nErrorLevel= atoi(argv[i + 2]);
				}
				continue;
			}
			else if(stricmp(argv[i+1], "-t") == 0)
			{				
				if(argc < (i+2))
					continue;
				if(argc >=(i+4))
				{
					for(int j=2;j<5;j++)
					{
						if(strstr(argv[i+j],"/")==0&&strstr(argv[i+j],"-")==0)
						{
							if(j==2)
								l64ExecTime=0;
							l64ExecTime += atoi(argv[i+j])*(pow((double)60,(4-j)));
								//FILE *fp;
								//fp=fopen("123.txt","a+");
								//fprintf(fp,"%d %d %d\n",l64ExecTime,j,(pow((double)60,(4-j))));
							//printf("%d\n",l64ExecTime);
						}
						else
						{
							l64ExecTime=30;
							break;
						}
					}
					if(l64ExecTime==0)
						l64ExecTime=30;
				}           
			}

			//else if(stricmp(argv[i+1], "-t") == 0)
			//{				
			//	if(argc < (i+2))
			//		continue;
			//	if(argc >=(i+4))
			//	{
			//		for(int j=2;j<5;j++)
			//		{
			//			if(strstr(argv[i+j],"/")==0&&strstr(argv[i+j],"-")==0)
			//			{
			//				if(j==2)
			//					l64ExecTime=0;
			//				l64ExecTime += atoi(argv[i+j])*(pow((double)60,(4-j)));
			//			}
			//			else
			//			{
			//				l64ExecTime=30;
			//				break;
			//			}
			//		}
			//		if(l64ExecTime==0)
			//			l64ExecTime=30;
			//	}          
			//}
			 //Add other parameters here
		//}
		//	if(stricmp(argv[i+1],"-p")==0)
		//	{
		//		if(argv[i+2]!=NULL&&stricmp(argv[i+2],"/r")!=0)
		//		{
		//			strcpy(szStr,argv[i+2]);
		//			blStringOK=true;
		//			i++;
		//		}
		//	}
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
				break;
			}

			else if(_stricmp(argv[i + 1], "/version")  ==  0 )
			{
				blParameterOK = true;
				printf("%s\n",sRevision);
				continue;
			}

			if(_stricmp(argv[i + 1], "/r") == 0 )
			{
				blParameterOK=true;
				//hwnd=GetForegroundWindow();
				ShowWindow(wndHandle, SW_HIDE); 
				Sleep(100);
				HANDLE hCountHandle[MAX_FORM] = {NULL};
				HANDLE hMUHandle[MAX_FORM] = {NULL};

				Position p[MAX_WIDTH_NUMBER][MAX_HEIGHT_NUMBER] = {0};
				g_CubeSize.x = GetSystemMetrics(SM_CXSCREEN);
				g_CubeSize.y = GetSystemMetrics(SM_CYSCREEN);/*-2*GetSystemMetrics(SM_CYSCREEN)/18)*/	
				////p[0][0].x = 0 * g_CubeSize.x;
				////p[0][0].y = GetSystemMetrics(SM_CYSCREEN)/18 + 0 * g_CubeSize.y;	
				//Whiteboard Cube(NULL,0,0,0,0);
				//Cube.DoModal();
				p[1][1].a = 1 * g_CubeSize.x;
				p[1][1].b = GetSystemMetrics(SM_CYSCREEN)/18 + 1 * g_CubeSize.y;
				//printf("%d\n %d\n",g_CubeSize.x,g_CubeSize.y);
				//printf("%d\n %d\n",p->a,p->b);
				HANDLE handle[4]={INVALID_HANDLE_VALUE};

				handle[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)blCubeThread, (LPVOID*)&p[1][1], 0, NULL);
				if(handle[0] == INVALID_HANDLE_VALUE)
					printf("Create Cube Thread .. Fail!!!\n");
				//for(int j = 0; j < nFormNum; j++)
				{						
					//hCountHandle[j] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)blCountThread, (LPVOID*)nFormNum, 0, NULL);	
					//hMUHandle[j] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)blMUThread, (LPVOID*)nFormNum, 0, NULL);	
				}
				handle[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)blCPUThread, NULL, 0, NULL);
				if(handle[1] == INVALID_HANDLE_VALUE)
					printf("Create CPU Thread .. Fail!!!\n");


				handle[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)blMemoryThread, NULL, 0, NULL);
				if(handle[2] == INVALID_HANDLE_VALUE)
					printf("Create Memory Thread .. Fail!!!\n");

				handle[3] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)blCountTime, NULL, 0, NULL);
				if(handle[3] == INVALID_HANDLE_VALUE)
					printf("Create CountTime Thread .. Fail!!!\n");
				

				//while(!kbhit());
				//{
				//if(hCPUThread)
				//	blCPUexit=true;
				//	TerminateThread(hCPUThread, 0);
				//if(hMemoryThread)
				//	blMemoryexit=true;
				//	TerminateThread(hMemoryThread, 0);
				//Sleep(1000);
				//hThread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)blThread1,NULL,0,NULL);
				//if(hThread==NULL)
				//{
				//	printf("Start thread fail.\n");
				//}
				//}
				//


				//ReleaseDC(g_hTimeWindow, m_hDCTimer);
				//SendMessage(hwnd, WM_SYSCOMMAND, SC_RESTORE, 0);
				//ShowWindow(wndHandle, SW_SHOW); 
				//End(255);
				WaitForMultipleObjects(3,&handle[0],TRUE,INFINITE);
				//WaitForSingleObject(Hcube,INFINITE);
					blexit=true;
					//End(0);
				//WaitForMultipleObjects(1,hCountHandle,1,INFINITE);
				//WaitForMultipleObjects(1,hMUHandle,1,INFINITE);
							//if(hCPUThread)
				//if(blexit)
				//{
				//if(hCPUThread)
				//	blCPUexit=true;
				//TerminateThread(hCPUThread, 0);
				//if(hMemoryThread)
				//	blMemoryexit=true;
				//TerminateThread(hMemoryThread, 0);

				//if(hCPUThread)
				//WaitForSingleObject(hCPUThread,INFINITE);
				//if(hMemoryThread)
				//WaitForSingleObject(hMemoryThread,INFINITE);
				////deletchain(head);
				//}
				//Sleep(1000);
			}
		}

		if(!blParameterOK) 
		{
			ShowWindow(wndHandle, SW_SHOW); 
			ReadMe();
		}

		if ((blParameterOK&&blResult ) == TRUE)
		{
			ShowWindow(wndHandle, SW_SHOW); 
			End(0);
		}
		else
		{
			ShowWindow(wndHandle, SW_SHOW); 
			End(nErrorLevel);
		}
	}    

}