// Lan-diags.cpp : 定義主控台應用程式的進入點。
//
/*
Lan-diags, Copyright by Pegatron Corp.
-------------------------------------------------------------------------------------------------
Lan-diags.exe Rev 1.00: Oct 3, 2008: Gracie Kuo
	1. Create
-------------------------------------------------------------------------------------------------
*/

#include "stdafx.h"
#include <conio.h>
#include "Lan-diags.h"
#include "global.h"

#define sProgramDescription "Windows Lan Utility"
#define sBuildDate "2008-12-02"
#define sRevision "1.00"

// 僅有的一個應用程式物件
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
	PrintStr(0, 2, "Diagnostics ", LOC_RIGHT, 0X08);
	PrintCh(SCREEN_LEFT, 3, '=', DEFAULT_COLOR, SCREEN_RIGHT);
	return;
}
//-------------------------------------------------------------------------------------------------
void ReadMe(void)
{	
	Logo();

	int y = wherey();

	if(!blNoLogo)
		y = 3;

	for(int i = 1; i <= 19; i++)
		PrintCh(40, y + i, '|', 0x08, 1); // middle line
	PrintCh(SCREEN_LEFT, y + 20, '-', 0x08, SCREEN_RIGHT); // bottom line
	PrintCh(40, y + 20, '+', 0x08, 1); // intersection of bottom line and middle line

	gotoxy(SCREEN_LEFT, y + 1);
	//textattr(0x08); 
	// Basic function	
	textattr(0x07);
	_cprintf("/?: Readme\n\r");
	textattr(0x08);	
	_cprintf("Basic----------------------------------\n\r"); 
	textattr(0x07);
	_cprintf("-nl: no display the logo and no clear\n\r");
	_cprintf("     the screen\n\r");
	_cprintf("-nc: no clear the screen\n\r");
	_cprintf("-erv <ErrorLevel>: Return Error Code\n\r");

	textattr(0x08); 
	// Add other function descriptions here
	_cprintf("Test-----------------------------------\n\r");	
	textattr(0x07);
	_cprintf("/I: Get Network Cards Info.\n\r");
	_cprintf("/MAC <Mac>: Check Mac Address.\n\r");
	_cprintf("/S <Mbps>: Check Link Speed.\n\r");
	_cprintf("/C: Check Link Connected.\n\r");	
	_cprintf("/SS <dBm>: Check Wireless Signal\n\r");
	_cprintf("    Strength. 0 ~ <dBm> (for XP)\n\r");	
	_cprintf("/SQ <min> [<MAX>]:Check Wireless Signal\n\r");
	_cprintf("    Quality. 0%c ~ 100%c (for Vista)\n\r", '%', '%');	
	_cprintf(" -n <NO>: Select by NO.\n\r");
	_cprintf(" -d <des>: Select by Description.\n\r");
	_cprintf(" -s <sn>: Select by Service Name.\n\r");
	_cprintf(" -m <Mac>: Select by Mac Address.\n\r");
	textattr(0x08);
	//_cprintf(" -f <file>: Write Data to <file>.\n\r");
	textattr(0x07);
	//RightWindow
	PrintCh(41, y + 1, '-', 0x08, SCREEN_RIGHT - 40);

	gotoxy(SCREEN_LEFT, y + 20);
	End(nErrorLevel);
	return;
}
//-------------------------------------------------------------------------------------------------
void End(int nReturnCode)
{
	if(!blNoLogo)
	{
		int y = wherey();
		if(y < 24)
			y = 24;

		char sRetCode[20];
		sprintf_s(sRetCode, "Return Code = %d",nReturnCode);
		PrintStr(0, y, sRetCode, LOC_MIDDLE, 0x08);
	}
	Cursor(true);
	exit(nReturnCode);
	return;
}
//--------------------------------------------------------------------------
void _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	// 初始化 MFC 並於失敗時列印錯誤
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
		// TODO: 配合您的需要變更錯誤碼
		_tprintf(_T("嚴重錯誤: MFC 初始化失敗\n"));
	else
	{
		for(int i = 0; i < (argc - 1); i++) 
		{
			if(_stricmp(argv[i + 1], "-nl") == 0) 
			{
				blNoLogo = TRUE;
				blClearScreen = FALSE;
				continue;
			}
			// No clear the screen
			else if(_stricmp(argv[i + 1], "-nc") == 0) 
			{
				blClearScreen = FALSE;
				continue;
			}			
			else if(_stricmp(argv[i + 1], "-erv") == 0) 
			{
				if(argc > i+2)
				{
					nErrorLevel = atoi(argv[i+2]);
					if(nErrorLevel == 0 || nErrorLevel > 99999 || nErrorLevel < -9999)
						nErrorLevel = 255;
				}	
				continue;
			}
		}

		if(!blNoLogo)
			Logo();
				
		BOOL blSelected = false;
		// Add other parameters here
		for(int i = 0; i < (argc - 1); i++) 
		{
			if(_stricmp(argv[i + 1], "-d") == 0) 
			{				
				if(argc > i+2)
				{
					if(blParameter(argv[i + 2]))
					{
						g_sDescription = argv[i + 2];
						g_sDescription = g_sDescription.MakeUpper();
						blSelected = true;
					}
				}					
				continue;
			}
			if(_stricmp(argv[i + 1], "-n") == 0) 
			{
				if(argc > i+2)
				{
					if(blParameter(argv[i + 2]))
					{
						g_nDevNO = atoi(argv[i + 2]);						
						blSelected = true;
					}
				}					
				continue;		
			}
			if(_stricmp(argv[i + 1], "-s") == 0) 
			{
				if(argc > i+2)
				{
					if(blParameter(argv[i + 2]))
					{
						g_sServiceName = argv[i + 2];
						g_sServiceName = g_sServiceName.MakeUpper();
						blSelected = true;
					}
				}					
				continue;		
			}
			if(_stricmp(argv[i + 1], "-m") == 0) 
			{
				if(argc > i+2)
				{
					if(blParameter(argv[i + 2]))
					{
						g_sMacAddress = argv[i + 2];
						g_sMacAddress = g_sMacAddress.MakeUpper();
						blSelected = true;
					}
				}					
				continue;		
			}
		}

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
			// Add other function here
			if(_stricmp(argv[i + 1], "/I") == 0) 
			{
				blParameterOK = TRUE;
				blSelected = true;
				blGetNetworkCards(Chk_Info);
				continue;
			}
			if(_stricmp(argv[i + 1], "/S") == 0) 
			{
				blParameterOK = TRUE;
				if(argc > i+2)
				{
					if(blParameter(argv[i + 2]))		
					{
						g_dSpeed = atol(argv[i + 2]);						
					}
				}

				if(blSelected)				
					blResult = blGetNetworkCards(Chk_Speed);				

				continue;
			}
			if(_stricmp(argv[i + 1], "/MAC") == 0) 
			{
				blParameterOK = TRUE;
				if(argc > i+2)
				{
					if(blParameter(argv[i + 2]))					
						g_sChkMacAddress = argv[i + 2];											
				}

				if(blSelected)				
					blResult = blGetNetworkCards(Chk_MAC);				

				continue;
			}
			if(_stricmp(argv[i + 1], "/C") == 0) 
			{
				blParameterOK = TRUE;
				if(blSelected)				
					blResult = blGetNetworkCards(Chk_Status);
				
				continue;
			}
			if(_stricmp(argv[i + 1], "/SS") == 0) 
			{
				blParameterOK = TRUE;
				if(argc > i+2)									
					g_lSignalStrength = atol(argv[i + 2]);					
				
				if(blSelected)				
					blResult = blGetNetworkCards(Chk_SignalS);

				continue;
			}

			if(_stricmp(argv[i + 1], "/SQ") == 0) 
			{
				blParameterOK = TRUE;
				if(argc > i+2)		
					if(blParameter(argv[i + 2]))
					{					
						g_nSignalQLower = atoi(argv[i + 2]);		
						if(argc > i+3)									
						{
							if(blParameter(argv[i + 3]))
								g_nSignalQUpper = atoi(argv[i + 3]);					
							else
								g_nSignalQUpper = 100;			
						}else
							g_nSignalQUpper = 100;		
					}

				if(blSelected)				
					blResult = blGetNetworkCards(Chk_SignalQ);

				continue;
			}
		}

		if(!blParameterOK) 
			ReadMe();
		else if(!blSelected)
			_cprintf("Please Select a Network Card to Check!!!");

		if ((blParameterOK & blResult) == TRUE)
			End(0);
		else 
			End(nErrorLevel);
	}    
}