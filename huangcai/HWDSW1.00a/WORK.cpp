#include "stdafx.h"
#include "Card.h"
#include "extern.h"
#include <Winbase.h>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include "SetupAPI.h"
#include "setupapi.h"
#include <conio.h>
#include<cfgmgr32.h>
#include "winsock2.h"
#include "conio.h"
#include <iostream>
#include <io.h>
//using namespace std;
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Kernel32.lib")
#define iTimel                          10240000
BOOL bllanc=false;
typedef void (WINAPI *PGNSI)(LPSYSTEM_INFO);
typedef BOOL (WINAPI *PGPI)(DWORD, DWORD, DWORD, DWORD, PDWORD);
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

//CWinApp theApp;

using namespace std;
UINT uzGetType[26]={0};
char szRootPath[]="A:\\";
BOOL ipExist=FALSE;

BOOL GetOSDisplayString( LPTSTR pszOS)
{
   OSVERSIONINFOEX osvi;
   SYSTEM_INFO si;
   PGNSI pGNSI;
   PGPI pGPI;
   BOOL bOsVersionInfoEx;
   DWORD dwType;

   ZeroMemory(&si, sizeof(SYSTEM_INFO));
   ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));

   osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

   if( !(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)) )
      return 1;

   // Call GetNativeSystemInfo if supported or GetSystemInfo otherwise.

   pGNSI = (PGNSI) GetProcAddress(
      GetModuleHandle(TEXT("kernel32.dll")), 
      "GetNativeSystemInfo");
   if(NULL != pGNSI)
      pGNSI(&si);
   else GetSystemInfo(&si);

   if ( VER_PLATFORM_WIN32_NT==osvi.dwPlatformId && 
        osvi.dwMajorVersion > 4 )
   {
      StringCchCopy(pszOS, BUFSIZE, TEXT("Microsoft "));

      // Test for the specific product.

      if ( osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 1 )
      {
         if( osvi.wProductType == VER_NT_WORKSTATION )
             StringCchCat(pszOS, BUFSIZE, TEXT("Windows 7 "));
         else StringCchCat(pszOS, BUFSIZE, TEXT("Windows Server 2008 R2 " ));
      }
      
      if ( osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0 )
      {
         if( osvi.wProductType == VER_NT_WORKSTATION )
             StringCchCat(pszOS, BUFSIZE, TEXT("Windows Vista "));
         else StringCchCat(pszOS, BUFSIZE, TEXT("Windows Server 2008 " ));

         pGPI = (PGPI) GetProcAddress(
            GetModuleHandle(TEXT("kernel32.dll")), 
            "GetProductInfo");

         pGPI( 6, 0, 0, 0, &dwType);

         switch( dwType )
         {
            case PRODUCT_ULTIMATE:
               StringCchCat(pszOS, BUFSIZE, TEXT("Ultimate Edition" ));
               break;
            case PRODUCT_HOME_PREMIUM:
               StringCchCat(pszOS, BUFSIZE, TEXT("Home Premium Edition" ));
               break;
            case PRODUCT_HOME_BASIC:
               StringCchCat(pszOS, BUFSIZE, TEXT("Home Basic Edition" ));
               break;
            case PRODUCT_ENTERPRISE:
               StringCchCat(pszOS, BUFSIZE, TEXT("Enterprise Edition" ));
               break;
            case PRODUCT_BUSINESS:
               StringCchCat(pszOS, BUFSIZE, TEXT("Business Edition" ));
               break;
            case PRODUCT_STARTER:
               StringCchCat(pszOS, BUFSIZE, TEXT("Starter Edition" ));
               break;
            case PRODUCT_CLUSTER_SERVER:
               StringCchCat(pszOS, BUFSIZE, TEXT("Cluster Server Edition" ));
               break;
            case PRODUCT_DATACENTER_SERVER:
               StringCchCat(pszOS, BUFSIZE, TEXT("Datacenter Edition" ));
               break;
            case PRODUCT_DATACENTER_SERVER_CORE:
               StringCchCat(pszOS, BUFSIZE, TEXT("Datacenter Edition (core installation)" ));
               break;
            case PRODUCT_ENTERPRISE_SERVER:
               StringCchCat(pszOS, BUFSIZE, TEXT("Enterprise Edition" ));
               break;
            case PRODUCT_ENTERPRISE_SERVER_CORE:
               StringCchCat(pszOS, BUFSIZE, TEXT("Enterprise Edition (core installation)" ));
               break;
            case PRODUCT_ENTERPRISE_SERVER_IA64:
               StringCchCat(pszOS, BUFSIZE, TEXT("Enterprise Edition for Itanium-based Systems" ));
               break;
            case PRODUCT_SMALLBUSINESS_SERVER:
               StringCchCat(pszOS, BUFSIZE, TEXT("Small Business Server" ));
               break;
            case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM:
               StringCchCat(pszOS, BUFSIZE, TEXT("Small Business Server Premium Edition" ));
               break;
            case PRODUCT_STANDARD_SERVER:
               StringCchCat(pszOS, BUFSIZE, TEXT("Standard Edition" ));
               break;
            case PRODUCT_STANDARD_SERVER_CORE:
               StringCchCat(pszOS, BUFSIZE, TEXT("Standard Edition (core installation)" ));
               break;
            case PRODUCT_WEB_SERVER:
               StringCchCat(pszOS, BUFSIZE, TEXT("Web Server Edition" ));
               break;
         }
         if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64 )
            StringCchCat(pszOS, BUFSIZE, TEXT( ", 64-bit" ));
         else if (si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_INTEL )
            StringCchCat(pszOS, BUFSIZE, TEXT(", 32-bit"));
      }

      if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2 )
      {
         if( GetSystemMetrics(SM_SERVERR2) )
            StringCchCat(pszOS, BUFSIZE, TEXT( "Windows Server 2003 R2, "));
         else if ( osvi.wSuiteMask==VER_SUITE_STORAGE_SERVER )
            StringCchCat(pszOS, BUFSIZE, TEXT( "Windows Storage Server 2003"));
         //else if ( osvi.wSuiteMask==VER_SUITE_WH_SERVER )
         //   StringCchCat(pszOS, BUFSIZE, TEXT( "Windows Home Server"));
         else if( osvi.wProductType == VER_NT_WORKSTATION &&
                  si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64)
         {
            StringCchCat(pszOS, BUFSIZE, TEXT( "Windows XP Professional x64 Edition"));
         }
         else StringCchCat(pszOS, BUFSIZE, TEXT("Windows Server 2003, "));

         // Test for the server type.
         if ( osvi.wProductType != VER_NT_WORKSTATION )
         {
            if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_IA64 )
            {
                if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
                   StringCchCat(pszOS, BUFSIZE, TEXT( "Datacenter Edition for Itanium-based Systems" ));
                else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
                   StringCchCat(pszOS, BUFSIZE, TEXT( "Enterprise Edition for Itanium-based Systems" ));
            }

            else if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64 )
            {
                if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
                   StringCchCat(pszOS, BUFSIZE, TEXT( "Datacenter x64 Edition" ));
                else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
                   StringCchCat(pszOS, BUFSIZE, TEXT( "Enterprise x64 Edition" ));
                else StringCchCat(pszOS, BUFSIZE, TEXT( "Standard x64 Edition" ));
            }

            else
            {
                if ( osvi.wSuiteMask & VER_SUITE_COMPUTE_SERVER )
                   StringCchCat(pszOS, BUFSIZE, TEXT( "Compute Cluster Edition" ));
                else if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
                   StringCchCat(pszOS, BUFSIZE, TEXT( "Datacenter Edition" ));
                else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
                   StringCchCat(pszOS, BUFSIZE, TEXT( "Enterprise Edition" ));
                else if ( osvi.wSuiteMask & VER_SUITE_BLADE )
                   StringCchCat(pszOS, BUFSIZE, TEXT( "Web Edition" ));
                else StringCchCat(pszOS, BUFSIZE, TEXT( "Standard Edition" ));
            }
         }
      }

      if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1 )
      {
         StringCchCat(pszOS, BUFSIZE, TEXT("Windows XP "));
         if( osvi.wSuiteMask & VER_SUITE_PERSONAL )
            StringCchCat(pszOS, BUFSIZE, TEXT( "Home Edition" ));
         else StringCchCat(pszOS, BUFSIZE, TEXT( "Professional" ));
      }

      if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0 )
      {
         StringCchCat(pszOS, BUFSIZE, TEXT("Windows 2000 "));

         if ( osvi.wProductType == VER_NT_WORKSTATION )
         {
            StringCchCat(pszOS, BUFSIZE, TEXT( "Professional" ));
         }
         else 
         {
            if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
               StringCchCat(pszOS, BUFSIZE, TEXT( "Datacenter Server" ));
            else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
               StringCchCat(pszOS, BUFSIZE, TEXT( "Advanced Server" ));
            else StringCchCat(pszOS, BUFSIZE, TEXT( "Server" ));
         }
      }

       // Include service pack (if any) and build number.

      if( _tcslen(osvi.szCSDVersion) > 0 )
      {
          StringCchCat(pszOS, BUFSIZE, TEXT(" ") );
          StringCchCat(pszOS, BUFSIZE, osvi.szCSDVersion);
      }

      TCHAR buf[80];

      StringCchPrintf( buf, 80, TEXT(" (build %d)"), osvi.dwBuildNumber);
      StringCchCat(pszOS, BUFSIZE, buf);

      return TRUE; 
   }

   else
   {  
      printf( "This sample does not support this version of Windows.\n");
      return FALSE;
   }
}
BOOL blDetectLanCThread()
{
	WSADATA wsaData;
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
			} 
		} 
		WSACleanup( );
	}
	while(1)
	{
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
		SOCKET sockClient=socket(AF_INET,SOCK_STREAM,0);

		SOCKADDR_IN addrSrv;
		addrSrv.sin_addr.S_un.S_addr=inet_addr(ip/*"172.24.145.72"*/);
		addrSrv.sin_family=AF_INET;
		addrSrv.sin_port=htons(6000);
		connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));

		char recvBuf[50]={0};
		if(recv(sockClient,recvBuf,50,0)!=NULL)	
		{
			send(sockClient,recvBuf,strlen(recvBuf)+1,0);
			break;
		}
	}
	return true;
}
BOOL blDetectlanThread()
{
	do
	{
		WSADATA wsaData;
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

					//printf("Server ip:%s\n",ip);
				} 
			} 
			WSACleanup( );
			char szIP[]="127.0.0.1";
			if(strcmp(ip,szIP)!=0)
				break;
		}
	}while(1);
			
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
	SOCKET sockSrv=socket(AF_INET,SOCK_STREAM,0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6000);

	bind(sockSrv,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));

	listen(sockSrv,5);
	SOCKADDR_IN addrClient;
	int len=sizeof(SOCKADDR);
	if(CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)blDetectLanCThread,NULL,0,NULL)==NULL)
	{
		printf("Start client thread fail.\n");
	}
	while(1)
	{
		char recvBufs[50]={0};
		char szTembuf[10];
		SOCKET sockConn=accept(sockSrv,(SOCKADDR*)&addrClient,&len);
		char sendBuf[50];
		sprintf(sendBuf,"%s Successfully connected",inet_ntoa(addrClient.sin_addr));
		send(sockConn,sendBuf,strlen(sendBuf)+1,0);
		if(recv(sockConn,recvBufs,50,0)!=NULL)
		{
			if(strcmp(recvBufs,sendBuf)==0)
			{
				printf("Lan test ready\n");
				//WinExec("usb.bat",SW_SHOW);
				blDetectLanR=true;
				break;
			}
		}
	}
	return true;
}
BOOL blDetectUSBThread()
{	
	do
	{
		if(blUSBDet)
		{
			printf("USB test ready.\n");
			blDetectUSBR=true;
			blCDDet=false;
			blUSBDet=false;			
			//WinExec("usb.bat",SW_SHOW);
			break;
			//End(0);
		}

		//else
		//	continue;
		Sleep(100);

	}while(1);
	return true;
}
BOOL blDetectCDThread()
{
	int Mcard[iDiskSum]={0};
	int name=0;
	for(name=0;name<iDiskSum;name++)
	{
		szRootPath[0]='D'+name;
		uzGetType[name]= GetDriveTypeA(szRootPath);
		ipExist=SetCurrentDirectory(szRootPath);
		if(!ipExist&&uzGetType[name]==5)
			Mcard[name]=5;
		else if(ipExist&&uzGetType[name]==5)
		{
			printf("CD test ready.\n");
			blDetectCDR=true;
		}
	}
	do
	{
		if(blDetectCDR)
			break;
		for(name=0;name<iDiskSum;name++)
		{
			if(Mcard[name]==5)
			{
				szRootPath[0]='D'+name;
				ipExist=SetCurrentDirectory(szRootPath);
				if(ipExist)
				{
					printf("CD test ready.\n");
					//WinExec("cd.bat",SW_SHOW);
					blDetectCDR=true;
				}
			}
		}
		//if(!blUSBDet&&blCDDet)
		//{
		//	printf("CD test ready\n");
		//	blDetectCDR=true;
		//	blCDDet=false;
		//	//WinExec("cd.bat",SW_SHOW);
		//	break;
		//	//End(0);
		//}
		Sleep(100);
	}while(1);
	return true;
}
BOOL blDetectCarReaderThread()
{
	int k=0;	
	int iStemN=0;
	int name=0;

	BOOL lpcard=FALSE;
	int Mcard[iDiskSum]={0};
	CDevicePropertySheetDialogDlg a;
	for(;;)
	{
		if(blDetectCardR)
			break;
		iSN=0;
		k++;
		a.EnumDevices();
		if(lpCard)
		{
			if(k==1)
			{
				iStemN=iSN;
				for(name=0;name<iDiskSum;name++)
				{
					szRootPath[0]='D'+name;
					uzGetType[name]= GetDriveTypeA(szRootPath);
					ipExist=SetCurrentDirectory(szRootPath);
					if(!ipExist&&uzGetType[name]==2)
					{
						lpcard=TRUE;
						Mcard[name]=2;
					}
				}
				while(lpcard)
				{
					if(blDetectCardR)
						break;
					for(name=0;name<iDiskSum;name++)
					{
						if(Mcard[name]==2)
						{
							szRootPath[0]='D'+name;
							ipExist=SetCurrentDirectory(szRootPath);
							if(ipExist)
							{
								printf("CardReader test ready.\n");
								//WinExec("cardreader.bat",SW_SHOW);
								blDetectCardR=true;
							}
						}
					}
				}
			}
			else
			{
				if(iStemN!=iSN)
				{
					printf("CardReader test ready.\n");
					//WinExec("cardreader.bat",SW_SHOW);
					blDetectCardR=true;
				}
			}
		}
	}
	return true;
}