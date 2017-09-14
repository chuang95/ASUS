// <Program Name>, Copyright by Pegatron Corp.
//-------------------------------------------------------------------------------------------------
/*
Rev 1.00: Sep 18, 2008: Craige Huang
		1: Order disk letterdisk letter
*/
//-------------------------------------------------------------------------------------------------

#include <conio.h>
#include "stdafx.h"
#include "Orderdisk-diags.h"
#include "global.h"
//#include "iostream"
//using namespace std;

#define sProgramDescription "Windows OrderDisk utility"
#define sBuildDate "2008-10-31"
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
    _cprintf("/R: Run the program, order disks.\n    Default order is D: HDD, E: ODD, F:\n    Card reader, if these partitions\n    exist\n\r");
	_cprintf(" -o <number>: Order disks as you want,\n\r");
	_cprintf("              Number: 1 inexistent, 2\n\r");
	_cprintf("              Card reader, 3 HDD, 5 ODD\n\r");
	textattr(0x08);

	// Add other function descriptions here


	//RightWindow
	PrintCh(41, y + 1, '-', 0x08, SCREEN_RIGHT - 40);
	y=4;
	gotoxy(41, y++);
	_cprintf("- Test --------------------------------\n\r");
	textattr(0x07);
	gotoxy(41, y++);
	_cprintf("Orderdisk-diags.exe /R\n\r");gotoxy(41, y++);
	_cprintf("order as D: HDD E: ODD F: Card reader\n\r");gotoxy(41, y++);
	_cprintf("\n\r");gotoxy(41, y++);
	_cprintf("Orderdisk-diags.exe -o 33215 /R\n\r");gotoxy(41, y++);
	_cprintf("order as D: HDD E: HDD F: Card reader G:");gotoxy(41, y++);
	_cprintf("inexistent H: ODD\n\r");gotoxy(41, y++);
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
	UINT uzGetType[26];
	UINT iGetType;
	int iTemp2[26],iTemp3[26],iTemp5[26];
	int Tempname=100;
	int iTempj[26];
	BOOL blStringOK=false;
	BOOL blS2=false;
	BOOL blS3=false;
	BOOL blS5=false;
	char szNewOrder[10];
	char szOldOrder[10];
	char szStr[100];
	//clrscr();
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
			if(stricmp(argv[i+1],"-o")==0)
			{
				if(argv[i+2]!=NULL&&stricmp(argv[i+2],"/r")!=0)
				{
					strcpy(szStr,argv[i+2]);
					blStringOK=true;
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
				break;
			}

			// Add other function here
			else if(stricmp(argv[i+1],"/r")==0)
			{
				blParameterOK=TRUE;
				if(blStringOK==true);
				else
				{
					char szTemp[]="352";
					strcpy(szStr,szTemp);
				}
					char szRootPath[]="A:\\";
					for(int name=0;name<strlen(szStr);name++)
					{
						szRootPath[0]='D'+name;
						uzGetType[name]= GetDriveTypeA(szRootPath); //Get disk drive type. iGetType==0 unknown partition;iGetType==1 inexistent;iGetType==2 DRIVE_REMOTE;iGetType==3 DRIVE_FIXED;iGetType==4 DRIVE_REMOVABLE;iGetType==5 DRIVE_CDROM	
					}
					szOldOrder[0]='\0';
					char szStr1[10]={0};
					for(int i=0;i<strlen(szStr);i++)
					{
						sprintf(szStr1,"%d",uzGetType[i]);
						strcat(szOldOrder,szStr1);
					}
					if(stricmp(szOldOrder,szStr)==0)
						printf("The partitions are ordered.");
					else 
					{

						int	ii=0,ij=0,ik=0,ji=0,jj=0,jk=0;
						int iTemp2[26],iTemp3[26],iTemp5[26];
						for(int ordername=0;ordername<strlen(szStr);ordername++)
						{
							if(szStr[ordername]=='2')
							{
								iTemp2[ii]=ordername;
								ii++;
							}
							else if(szStr[ordername]=='3')
							{
								iTemp3[ij]=ordername;
								ij++;
							}
							else if(szStr[ordername]=='5')
							{
								iTemp5[ik]=ordername;
								ik++;
							}
							else if(szStr[ordername]=='1');
							else
							{
								if(!blNoLogo)
									Logo();
								printf("Your command is wrong, you have no such partitions. Please check ReadMe.\n");

								End(255);
							}
							if(uzGetType[ordername]==2)
							{
								ji++;
							}
							else if(uzGetType[ordername]==3)
							{
								jj++;
							}
							else if(uzGetType[ordername]==5)
							{
								jk++;
							}
						}
						if(ii!=ji||ij!=jj||ik!=jk/*&&ii!=0&&ij!=0&&ik!=0&&ji!=0&&jj!=0&&jk*/)
						{
							if(!blNoLogo)
								Logo();
							printf("Your command does not accord with your partitions, please check it out.\n");

							End(255);
						}
						int il=0;
						int im=0;
						int in=strlen(szStr);
						for(int name=0,name1=0;name<in;name++)
						{
							szRootPath[0]='Z'-name;
							int iTempi=GetDriveTypeA(szRootPath);
							if(iTempi==1)
								vChangeDisk(3+name1,25-name);//change disk letter to Z Y X.....
							else
							{
								iTempj[il]=name;
								il++;
								in++;
								name1--;
							}
							name1++;
						}
						for(int name=0,ii=0,ij=0,ik=0;name<in;name++)
						{
							if(name!=iTempj[im])
							{
								szRootPath[0]='Z'-name;
								uzGetType[0]= GetDriveTypeA(szRootPath);						
								if(uzGetType[0]==2)
								{
									vChangeDisk(25-name,3+iTemp2[ii]);
									ii++;
								}
								if(uzGetType[0]==3)
								{
									vChangeDisk(25-name,3+iTemp3[ij]);
									ij++;
								}
								if(uzGetType[0]==5)
								{
									vChangeDisk(25-name,3+iTemp5[ik]);
									ik++;
								}
							}
							else
								im++;
						}
						char szRootPath[]="A:\\";
						for(int name=0;name<strlen(szStr);name++)
						{
							szRootPath[0]='D'+name;
							uzGetType[name]= GetDriveTypeA(szRootPath);
						}
						szOldOrder[0]='\0';
						char szStr1[10]={0};
						for(int i=0;i<strlen(szStr);i++)
						{
							sprintf(szStr1,"%d",uzGetType[i]);
							strcat(szOldOrder,szStr1);
						}
						if(stricmp(szOldOrder,szStr)==0)
							printf("Your partitions are ordered as you want.");
						else
						{
							if(!blNoLogo)
								Logo();
							printf("Failed to order your disk letter.");
							End(255);
						}
					}					
				blResult=TRUE;
			}                           						
		}


		if(!blParameterOK) 
			ReadMe();

		if ((blParameterOK & blResult) == TRUE)
			End(0);
		else 
			End(255);
	}    

}