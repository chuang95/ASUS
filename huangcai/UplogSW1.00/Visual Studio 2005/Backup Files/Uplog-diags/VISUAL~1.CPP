// <Program Name>, Copyright by Pegatron Corp.
//-------------------------------------------------------------------------------------------------
/*
Rev 1.00: Sep 18, 2008: Craige Huang
		1: Order disk letterdisk letter
*/
//-------------------------------------------------------------------------------------------------
#pragma comment (lib,"ws2_32.lib")
#include "stdafx.h"
#include "Uplog-diags.h"
#include "global.h"
#include <time.h>
#include <string.h> 
#include <stdio.h>
#include <sys/types.h>
#include <sys/timeb.h>
//#include "iostream"
//using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define sProgramDescription "Windows Uplog"
#define sBuildDate "2009-01-07"
#define sRevision "1.00a"

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
    _cprintf("/S: Set a server, show the ip of server\n\r");
	_cprintf("    and waiting for clients.\n\r");
	_cprintf("/C: Set a client and send uplog to \n\r");
	_cprintf("    server.\n\r");
	_cprintf(" -ip: the server ip.\n\r");
	textattr(0x08);

	// Add other function descriptions here


	//RightWindow
	PrintCh(41, y + 1, '-', 0x08, SCREEN_RIGHT - 40);
	y=4;
	gotoxy(41, y++);
	_cprintf("- Test --------------------------------\n\r");
	textattr(0x07);
	gotoxy(41, y++);
	_cprintf("Uplog-diags.exe /S\n\r");gotoxy(41, y++);
	_cprintf("  Set a server");gotoxy(41, y++);
	//_cprintf("\n\r");gotoxy(41, y++);
	_cprintf("Uplog-diags.exe -ip 172.24.145.34 /c\n\r");gotoxy(41, y++);
	_cprintf("  Set a client,connect to the server \n\r");gotoxy(41, y++);
	_cprintf("  whoses ip is 172.24.145.34.\n\r");gotoxy(41, y++);
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
	int iT=0;
	BOOL blStringOK=false;
	BOOL blS2=false;
	BOOL blS3=false;
	BOOL blS5=false;
	char szStr[100];
	char szTemp[100][50]={0};/*={"SN.DAT","STATION.DAT","90SN.DAT","MBPPID.DAT","MAC.DAT","BIOSTEMP.DAT","USERCRC.DAT","RECCRC.DAT","CPUMODEL.DAT","CPUTEST.DAT","MEMOK.DAT","1394ID.DAT","USBCHK.DAT","PCICHK.DAT","MOUSECHK.DAT","AUDIOTES.DAT","1394TEST.DAT","JDTEST.DAT","cardvid.dat","HDD1MODE.DAT","CHKREGOK.DAT","LEDCHK.DAT","USBCABLE.DAT","FT0001.OK","rgb.dat","LSCRIBLE.DAT","dvd.dat","cdok.dat","ODDROM.DAT","WLANCHK.DAT","BDTEST.DAT","wrestest.dat","HDMITEST.DAT","IRTEST.DAT","MODEMCHK.DAT","BUTTEST.DAT","TVTEST.DAT","suspend.dat","cardtest.ok","wintest.dat","TESTPASS.DAT"};*/
	char szTemN[100][50]={0};/*={"SN","STATION","90SN","MBPPID","MAC","BIOSTEMP","USERCRC","RECCRC","CPUMODEL","CPUTEST","MEMOK","1394ID","USBCHK","PCICHK","MOUSECHK","AUDIOTEST","1394TEST","JDTEST","CVID","HDD1MODE","CHKREGOK","LEDCHK","USBCABLE","FTOK","RGB","LSCRIBLE","DVDOK","CDOK","ODDROM","WLANCHK","BDTEST","WRESTEST","HDMITEST","IRTEST","MODEMCHK","BUTTEST","TVTEST","SUSPEND","CARDTEST","WINTEST","TESTPASS"};*/
	char tmpbuf[128];
	char szTem[10];
	char szTems[10];
	//char szTime[100];
	struct _timeb tstruct;
	//clrscr();
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
			if(stricmp(argv[i+1],"-ip")==0)
			{
				if(argv[i+2]!=NULL&&stricmp(argv[i+2],"/c")!=0)
				{
					strcpy(szStr,argv[i+2]);
					blStringOK=true;
					i++;
				}
			}
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

			if(_stricmp(argv[i + 1], "/s") == 0 )
			{
				FILE* ins; 
				char sin;
				//char szTemp1[100];
				int nsLines = 0;
				int iN=0;
				if((ins=fopen( "uplogserver.txt", "r"))==NULL) 
				{
					printf("error can not read uplogserver.txt.\npress any key to continue..."); 
					End(255);
				}
				while(!feof(ins)) 
				{
					//fgets(szTemp1,100,ins);
					//iN++;
					sin=fgetc(ins);
					if(sin == '\n')
					{
						iN++;
						continue;
					}

					sprintf(szTems,"%c",sin);
					strcat(szTemN[iN],szTems);
					//printf("%s\n",szTemN[iN]);
				}

				CoInitialize(NULL);
				blParameterOK=true;
				CheckIP();
				WORD wVersionRequested;
				WSADATA wsaData;
				int err;

				wVersionRequested = MAKEWORD( 1, 1 );

				err = WSAStartup( wVersionRequested, &wsaData );
				if ( err != 0 )
				{
					return;
				}

				if ( LOBYTE( wsaData.wVersion ) != 1 ||
					HIBYTE( wsaData.wVersion ) != 1 ) 
				{
					WSACleanup( );
					return;
				}
				SOCKET sockSrv=socket(AF_INET,SOCK_STREAM,0);

				SOCKADDR_IN addrSrv;
				addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
				addrSrv.sin_family=AF_INET;
				addrSrv.sin_port=htons(6000);

				bind(sockSrv,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));

				listen(sockSrv,5);
				SOCKADDR_IN addrClient;
				int len=sizeof(SOCKADDR);
				//char recvBuf1[50],recvBuf2[50],recvBuf3[50],recvBuf4[50],recvBuf5[50],recvBuf6[50],recvBuf7[50],recvBuf8[50],recvBuf9[50],recvBuf10[50],recvBuf11[50],recvBuf12[50],recvBuf13[50],recvBuf14[50],recvBuf15[50];
				char recvBuf[][50]={"0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0",
					                "0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0",
					                "0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0",
					                "0","0","0","0","0","0","0","0","0","0"};
				//char szRe[1024];
				//szRe[0]='\0';
				while(1)
				{
					char szTembuf[10];
					//printf("%d",iT);
					SOCKET sockConn=accept(sockSrv,(SOCKADDR*)&addrClient,&len);
					char sendBuf[50];
					sprintf(sendBuf,"%s Successfully connected",inet_ntoa(addrClient.sin_addr));
					if(iT==0)
					send(sockConn,sendBuf,strlen(sendBuf)+1,0);
					//send(sockConn,szRe,strlen(szRe)+1,0);
					//char recvBuf[50];/*recvBuf2[50],recvBuf3[50],recvBuf4[50],recvBuf5[50],recvBuf6[50],recvBuf7[50],recvBuf8[50],recvBuf9[50],recvBuf10[50],recvBuf11[50],recvBuf12[50],recvBuf13[50],recvBuf14[50],recvBuf15[50];*/
					if(iT>0)
					{
					recv(sockConn,recvBuf[iT-1],50,0);
					//printf("%s\n",recvBuf[iT-1]);

					//strcat(szRe,recvBuf1);
					send(sockConn,recvBuf[iT-1],strlen(recvBuf[iT-1])+1,0);
					}
					//else if(iT==2)
					//{recv(sockConn,recvBuf2,50,0);
					//send(sockConn,recvBuf2,strlen(recvBuf2)+1,0);}
					//else if(iT==3)
					//{recv(sockConn,recvBuf3,50,0);
					//send(sockConn,recvBuf3,strlen(recvBuf3)+1,0);}
					//else if(iT==4)
					//{recv(sockConn,recvBuf4,50,0);
					//send(sockConn,recvBuf4,strlen(recvBuf4)+1,0);}
					//else if(iT==5)
					//{recv(sockConn,recvBuf5,50,0);
					//send(sockConn,recvBuf5,strlen(recvBuf5)+1,0);}
					//else if(iT==6)
					//{recv(sockConn,recvBuf6,50,0);
					//send(sockConn,recvBuf6,strlen(recvBuf6)+1,0);}
					//else if(iT==7)
					//{recv(sockConn,recvBuf7,50,0);
					//send(sockConn,recvBuf7,strlen(recvBuf7)+1,0);}
					//else if(iT==8)
					//{recv(sockConn,recvBuf8,50,0);
					//send(sockConn,recvBuf8,strlen(recvBuf8)+1,0);}
					//else if(iT==9)
					//{recv(sockConn,recvBuf9,50,0);
					//send(sockConn,recvBuf9,strlen(recvBuf9)+1,0);}
					//else if(iT==10)
					//{recv(sockConn,recvBuf10,50,0);
					//send(sockConn,recvBuf10,strlen(recvBuf10)+1,0);}
					//else if(iT==11)
					//{recv(sockConn,recvBuf11,50,0);
					//send(sockConn,recvBuf11,strlen(recvBuf11)+1,0);}
					//else if(iT==12)
					//{recv(sockConn,recvBuf12,50,0);
					//send(sockConn,recvBuf12,strlen(recvBuf12)+1,0);}
					//else if(iT==13)
					//{recv(sockConn,recvBuf13,50,0);
					//send(sockConn,recvBuf13,strlen(recvBuf13)+1,0);}
					//else if(iT==14)
					//{recv(sockConn,recvBuf14,50,0);
					//send(sockConn,recvBuf14,strlen(recvBuf14)+1,0);}
					//else if(iT==15)
					//{recv(sockConn,recvBuf15,50,0);
					//send(sockConn,recvBuf15,strlen(recvBuf15)+1,0);}
					//printf("%s",szRe);
					iT++;
					if(iT==iN+1)
					{
						iT=0;
						//printf("%d",iT);
						_ConnectionPtr	m_pConnection;

						//HRESULT hr;
						//try
						//{
						//	hr = m_pConnection.CreateInstance("ADODB.Connection");
						//		if(SUCCEEDED(hr))
						//		{
						//			//CString szConnstr=_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=uplog.mdb")+_T("")+_T("");

						//			hr = m_pConnection->Open(_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=uplog.mdb"),"","",adModeUnknown);
						//		}
						//}
						//catch(_com_error e)///捕捉异常
						//{
						//	CString errormessage;
						//	errormessage.Format("连接数据库失败!\r\n错误信息:%s",e.ErrorMessage());
						//	AfxMessageBox(errormessage);///显示错误信息
						//} 
						m_pConnection.CreateInstance(__uuidof(Connection));
						try                 
						{	
							m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0; Data Source=uplog.mdb", "", "", adConnectUnspecified);
						}
						catch(_com_error *e)
						{
							printf(/*数据库连接失败，确认数据库uplog.mdb是否在当前路径下!*/"Fail to connect. Please,check the uplog.mdb existent or not!");
							End(255);
						}
						//if(m_pConnection->State)
						//m_pConnection->Close();
						//m_pConnection= NULL;  
						//m_pConnection->put_ConnectionTimeout(long(5));
						////try
						////{
						////	// 写入各字段值
						////	m_pRecordset->AddNew();
						////	m_pRecordset->PutCollect("SN", /*_variant_t(m_Name)*/recvBuf);
						////	m_pRecordset->PutCollect("STATION", /*atol(m_Age)*/recvBuf);
						////	m_pRecordset->Update();

						////	printf("插入成功!");
						////}
						////catch(_com_error *e)
						////{
						////	//AfxMessageBox(e->ErrorMessage());
						////	printf("插入失败!");
						////	End(255);
						////} 
						////_RecordsetPtr m_pRecordset;
						////m_pRecordset.CreateInstance("ADODB.Recordset");
						////m_pRecordset->Open("SELECT * FROM log",_variant_t((IDispatch*)m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
						////m_pRecordset->MoveFirst();///移到首条记录
						////m_pRecordset->AddNew();///添加新记录
						////m_pRecordset->PutCollect("SN",_variant_t(recvBuf));
						////m_pRecordset->PutCollect("STATION",_variant_t("叶利钦"));
						_RecordsetPtr	m_pRecordset;
						m_pRecordset.CreateInstance(__uuidof(Recordset));
						//UINT DayOfWeek[] = {
						//   LOCALE_SDAYNAME7,   // Sunday
						//   LOCALE_SDAYNAME1,   
						//   LOCALE_SDAYNAME2,
						//   LOCALE_SDAYNAME3,
						//   LOCALE_SDAYNAME4, 
						//   LOCALE_SDAYNAME5, 
						//   LOCALE_SDAYNAME6   // Saturday
						//};
						//char strWeekday[256];
						//CTime time(CTime::GetCurrentTime());   // Initialize CTime with current time
						//::GetLocaleInfoA(LOCALE_USER_DEFAULT,   // Get string for day of the week from system
						//   DayOfWeek[time.GetDayOfWeek()-1],   // Get day of week from CTime
						//   strWeekday, sizeof(strWeekday) / sizeof(strWeekday[0]));
						_strdate( tmpbuf );
						int j=0;
						for (int k=0;k<8;k++)
						{
							if(tmpbuf[k]=='/')
								k++;
							szTembuf[j]=tmpbuf[k];
							j++;
						}
						szTembuf[j]='\0';

						time_t timep; 
						time (&timep); 

						  bool   bIsHaveNo   =   FALSE;//是否有表？默认无表   
						    
						  //pConnection:指向数据库   
						  m_pRecordset   =   m_pConnection->OpenSchema(adSchemaTables);//指向所有的表   
						    
						while(!(m_pRecordset->adoEOF))//指针是否已经指向最后一条记录？   
						{   
							_bstr_t  table_name   =   m_pRecordset->Fields->GetItem("TABLE_NAME")->Value;//得到表的名称   
							char sz1[10];
							sz1[0]='\0';
							strncat(sz1,table_name,10);
							if(strcmp(szTembuf,sz1)==0)//表名判断是否相同？   
							{
								bIsHaveNo   =   TRUE;//有表了   
								break;   
							}   
							m_pRecordset->MoveNext();   
						}
						if(bIsHaveNo == FALSE)
						{
							_variant_t RecordsAffected;							
							char szF[600]="CREATE TABLE ";
							char szB[550]="(";/*SN TEXT,STATION TEXT,90SN TEXT,MBPPID TEXT,MAC TEXT,BIOSTEMP TEXT,USERCRC TEXT,RECCRC TEXT,CPUMODEL TEXT,CPUTEST TEXT,MEMOK TEXT,1394ID TEXT,USBCHK TEXT,PCICHK TEXT,MOUSECHK TEXT,AUDIOTEST TEXT,1394TEST TEXT,JDTEST TEXT,CVID TEXT,HDD1MODE TEXT,CHKREGOK TEXT,LEDCHK TEXT,USBCABLE TEXT,FTOK TEXT,RGB TEXT,LSCRIBLE TEXT,DVDOK TEXT,CDOK TEXT,ODDROM TEXT,WLANCHK TEXT,BDTEST TEXT,WRESTEST TEXT,HDMITEST TEXT,IRTEST TEXT,MODEMCHK TEXT,BUTTEST TEXT,TVTEST TEXT,SUSPEND TEXT,CARDTEST TEXT,WINTEST TEXT,TESTPASS TEXT,DT DATETIME*/
							for(int i=0;i<iN;i++)
							{
								strcat(szB,szTemN[i]);
								strcat(szB," TEXT,");
							}
							strcat(szB,"DT TEXT)");
							strcat(szF,szTembuf);
							strcat(szF,szB);
							//printf("%s",szF);
							m_pConnection->Execute(szF,&RecordsAffected,adCmdText);
						}
						m_pRecordset->Close();
						try
						{
							char szFt[50]="SELECT * FROM ";
							strcat(szFt,szTembuf);
							//printf("%s",szFt);
							m_pRecordset->Open(szFt,// 查询表中所有字段
												m_pConnection.GetInterfacePtr(),  // 获取库接库的IDispatch指针
												adOpenDynamic,
												adLockOptimistic,
												adCmdText);
							//m_pRecordset->Open("SELECT * FROM log",_variant_t((IDispatch*)m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdTable);
						}
						catch(_com_error *e)
						{
							AfxMessageBox(e->ErrorMessage());
						}
						//printf("123\n");
						try
						{
							m_pRecordset->AddNew();
							// 写入各字段值
							for(int N=1;N<iN;N++)
							{
								//printf("%s\n",recvBuf[N]);
								m_pRecordset->PutCollect(szTemN[N],_variant_t(recvBuf[N]));
							}
								m_pRecordset->PutCollect("DT",_variant_t(ctime(&timep)));
								char szCount[100]={0};
								strcat(szCount,"SELECT COUNT(*) FROM ");
								strcat(szCount,szTembuf);
								m_pRecordset = m_pConnection->Execute("SELECT COUNT(*) FROM users",&RecordsAffected,adCmdText);

								_variant_t vIndex = (long)0;
								_variant_t vCount = m_pRecordset->GetCollect(vIndex);
								//char szvCount[100];
								//sprintf(szvCount,"%s",vCount);
								//printf("%s",szvCount);
								m_pRecordset->PutCollect("ID",vCount.lVal);
							//m_pRecordset->PutCollect("cardvid",_variant_t(recvBuf2));
							//m_pRecordset->PutCollect("cd",_variant_t(recvBuf3));
							//m_pRecordset->PutCollect("date1",_variant_t(recvBuf4));
							//m_pRecordset->PutCollect("dvd",_variant_t(recvBuf5));
							//m_pRecordset->PutCollect("guid1",_variant_t(recvBuf6));
							//m_pRecordset->PutCollect("hdd1fw",_variant_t(recvBuf7));
							//m_pRecordset->PutCollect("hdd1mode",_variant_t(recvBuf8));
							//m_pRecordset->PutCollect("line",_variant_t(recvBuf9));
							//m_pRecordset->PutCollect("mac1",_variant_t(recvBuf10));
							//m_pRecordset->PutCollect("odd1fw",_variant_t(recvBuf11));
							//m_pRecordset->PutCollect("odd1mode",_variant_t(recvBuf12));
							//m_pRecordset->PutCollect("sn",_variant_t(recvBuf13));
							//m_pRecordset->PutCollect("station",_variant_t(recvBuf14));
							//m_pRecordset->PutCollect("time",_variant_t(recvBuf15));
							m_pRecordset->Update();
							printf("Successfully insert!\n");
						}
						catch(_com_error *e)
						{
							AfxMessageBox(e->ErrorMessage());
						}
						//printf("456");
						//CoUnInitialize();
						m_pRecordset->Close();
						if(m_pConnection->State)
						m_pConnection->Close();
						m_pConnection= NULL;  
						//printf("%s\n",recvBuf);
					}
					//memset(recvBuf1,0,strlen(recvBuf1));
					//memset(recvBuf2,0,strlen(recvBuf2));
					//memset(recvBuf3,0,strlen(recvBuf3));
					//memset(recvBuf4,0,strlen(recvBuf4));
					//memset(recvBuf5,0,strlen(recvBuf5));
					//memset(recvBuf6,0,strlen(recvBuf6));
					//memset(recvBuf7,0,strlen(recvBuf7));
					//memset(recvBuf8,0,strlen(recvBuf8));
					//memset(recvBuf9,0,strlen(recvBuf9));
					//memset(recvBuf10,0,strlen(recvBuf10));
					//memset(recvBuf11,0,strlen(recvBuf11));
					//memset(recvBuf12,0,strlen(recvBuf12));
					//memset(recvBuf13,0,strlen(recvBuf13));
					//memset(recvBuf14,0,strlen(recvBuf14));
					//memset(recvBuf15,0,strlen(recvBuf15));
					closesocket(sockConn);
				}
			}
			else if(_stricmp(argv[i + 1], "/c") == 0 )
			{
				FILE* in; 
				char cin;
				int nLines = 0;
				int iN=0;
				if((in = fopen( "uplogclient.txt", "r"))==NULL) 
				{
					printf("error can not read uplogclient.txt.\npress any key to continue..."); 
					End(255);
				}
				while(!feof(in)) 
				{
					cin=fgetc(in);
					if(cin == '\n')
					{
						iN++;
						continue;
					}

					sprintf(szTem,"%c",cin);
					strcat(szTemp[iN],szTem);
					//printf("%s\n",szTemp[iN]);
				}
				//int iM=strlen(szTemp[iN]);
				//printf("%d\n",iN);
				//szTemp[iN][iM]='\0';
				for(int k=0;k<iN;k++)
				{
					if(PathFileExists(szTemp[k]));
					else
					{
						printf("%s is inexistent!",szTemp[k]);
						End(255);
					}
				}
				if(blStringOK==true)
				{
					for(int j=0;j<20;j++)
					{
						////printf("%d",iT);
						if(iT!=0)
						{
							Sleep(500);
						}
						else
							break;
						if(j==19)
						{
							//printf("Fail to connect!");
							End(255);
						}
					}
					blParameterOK=true;
					for(int i=0;i<iN+1;i++)
					{
						WORD wVersionRequested;
						WSADATA wsaData;
						int err;

						wVersionRequested = MAKEWORD( 1, 1 );

						err = WSAStartup( wVersionRequested, &wsaData );
						if ( err != 0 )
						{
							return;
						}

						if ( LOBYTE( wsaData.wVersion ) != 1 ||
							HIBYTE( wsaData.wVersion ) != 1 ) 
						{
							WSACleanup( );
							return;
						}
						SOCKET sockClient=socket(AF_INET,SOCK_STREAM,0);

						SOCKADDR_IN addrSrv;
						addrSrv.sin_addr.S_un.S_addr=inet_addr(szStr/*"172.24.145.72"*/);
						addrSrv.sin_family=AF_INET;
						addrSrv.sin_port=htons(6000);
						connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
						FILE *f;
						char szUplog[1024];

						if(i<iN+1&&i>0)
						{
							//if(PathFileExists(szTemp[i-1]));
							//else
							//	i+1;
							f=fopen(szTemp[i-1],"r+");
							//fscanf(f, "%s", szUplog);
							fgets(szUplog,100,f);
							//printf("%s\n",szUplog);
							send(sockClient,szUplog,strlen(szUplog)+1,0);
						}
/*==-1)*/
						//{
						//	printf("%s",fail to receive);
						//}
						/*if(i==0)*/
						//printf("%s\n",recvBuf);
						char recvBuf[50];
						recv(sockClient,recvBuf,50,0);	
						if(i==0)
						{

							printf("%s\n",recvBuf);
						}
						if(i>0)
						{
							if(strcmp(recvBuf,szUplog)==0)
							{
								if(i==iN)
									printf("pass");
							}
							else 
							{
								printf("fail to uplog");
								End(255);
							}
						}
						//memset(recvBuf,0,strlen(recvBuf));
						closesocket(sockClient);
						WSACleanup();
					}
				}
			}
		}


		if(!blParameterOK) 
			ReadMe();

		if ((blParameterOK ) == TRUE)
			End(0);
		else 
			End(255);
	}    

}