// <Program Name>, Copyright by Pegatron Corp.
//-------------------------------------------------------------------------------------------------
/*
Rev 1.00: Sep 18, 2008: Craige Huang
		1: Order disk letterdisk letter
*/
//-------------------------------------------------------------------------------------------------
//#pragma comment (lib,"ws2_32.lib")
 // #pragma   comment(lib,"Wininet.lib ")   
 // #pragma   comment(lib,"Sensapi.LIB")   
#include "stdafx.h"
#include "HWD-diags.h"
#include "global.h"
#include "det.h"
#include "ks.h"
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <Devicetopology.h>
#include <KsMedia.h>
#include <functiondiscoverykeys.h>
#include <tchar.h>
#include <conio.h> 
#include "Audioclient.h"
#include <MMSystem.h>
#include "atlstr.h"
#include "resource.h"
#include "windows.h"
#include<stdio.h> 
#include "iostream"
using namespace std;


#define SERVER_SOCKET_ERROR 1
#define SOCKET_OK 0
#define CS_ERROR 1
#define CS_OK 0
int iCN=0,iSum=0,iAu=0,iAd=0,iAds=0;

#pragma comment(lib, "wsock32.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define sProgramDescription "Windows Hardware detect"
#define sBuildDate "2009-07-28"
#define sRevision "1.00a"

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
	PrintStr(0, 2, "Copyright by Pegatron, Build Date:" sBuildDate " Rev" sRevision, LOC_MIDDLE, DEFAULT_COLOR);
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
    _cprintf("/test: Run the progrem, detect HW.\n\r");
	_cprintf(" -usb: detect usb \n\r");
	_cprintf(" -cd: detect cd\n\r");
	_cprintf(" -audio: detect audio for vista|win7\n\r");
	_cprintf(" -lan: detect lan connection\n\r");
	_cprintf(" -card: detect cardreader\n\r");
	textattr(0x08);

	// Add other function descriptions here


	//RightWindow
	PrintCh(41, y + 1, '-', 0x08, SCREEN_RIGHT - 40);
	y=4;
	gotoxy(41, y++);
	_cprintf("- Test --------------------------------\n\r");
	textattr(0x07);
	gotoxy(41, y++);
	//_cprintf("Flan-diags.exe /Test\n\r");gotoxy(41, y++);
	//_cprintf("  Run the test");gotoxy(41, y++);
	//_cprintf("\n\r");gotoxy(41, y++);
	//_cprintf("Flan-diags.exe -100M -t 10 /Test \n\r");gotoxy(41, y++);
	//_cprintf("  Transmit data for 10seconds and \n\r");gotoxy(41, y++);
	//_cprintf("  test whether the speed of network \n\r");gotoxy(41, y++);
	//_cprintf("  card is higher than 10Mbps\n\r");gotoxy(41, y++);
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
BOOL blDetectThread()
{
	Cdet usb;
	usb.DoModal();	
	return TRUE;
}

//--------------------------------------------------------------------------
#define SAFE_RELEASE(punk)   if ((punk) != NULL) { (punk)->Release(); (punk) = NULL; }

//-----------------------------------------------------------
// Print (raw) jack information
//-----------------------------------------------------------
void printJack(UINT index, KSJACK_DESCRIPTION *ksjack)
{
  if (ksjack != NULL) {
    //printf("\n");
    //printf("\tJack[%d]->ChannelMapping = %d\n", index, ksjack->ChannelMapping);
    //printf("\tJack[%d]->Color = %08x\n", index, ksjack->Color);
    //printf("\tJack[%d]->ConnectionType = %d\n", index, ksjack->ConnectionType);
    //printf("\tJack[%d]->GeoLocation = %d\n", index, ksjack->GeoLocation);
    //printf("\tJack[%d]->GenLocation = %d\n", index, ksjack->GenLocation);
    //printf("\tJack[%d]->PortConnection  = %d\n", index, ksjack->PortConnection);
    //printf("\tJack[%d]->IsConnected = %d\n", index, ksjack->IsConnected);
	//getch();
	//exit(0);
  }
  Sleep(100);
  if(!blDetectAudioR)
  {
	  if((ksjack->Color==8421504||ksjack->Color==12632256/*00c0c0c0*/||ksjack->Color==255/*000000ff*/||ksjack->Color==16744640/*00ff80c0*/)&&ksjack->IsConnected==1)
	  {
		  printf("Audio test ready.\n");
		  blDetectAudioR=true;
	  }
	  if(ksjack->Color==11782540&&ksjack->ChannelMapping==-2147483648)
	  {
		  printf("Audio test ready.\n");
		  blDetectAudioR=true;
	  }
	  if(ksjack->Color==65280/*0000ff00*/&&ksjack->ChannelMapping==3&&ksjack->GeoLocation==2&&ksjack->IsConnected==1)
	  {
		  //printf("Audio test ready.\n");
		  //blDetectAudioR=true;
		  iAd++;
	  }
	  else if((ksjack->Color==16744448&&ksjack->IsConnected==1)||(ksjack->Color==0&&ksjack->IsConnected==1))
		  iCN++;
  }
  //char szColor[10]={0};
  //sprintf(szColor,"%08x",ksjack->Color);
  //if((szColor=="0000ff00"||szColor=="00c0c0c0"||szColor=="000000ff"||szColor=="00ff80c0")&&ksjack->IsConnected==1)
  //{
	 // printf("Audio test ready.");
	 // blDetectAudioR=true;
  //}
  //else if((ksjack->Color==16744448&&ksjack->IsConnected==1)||(ksjack->Color==0&&ksjack->IsConnected==1))
	 // iCN++;
  //if(iCN>1)
  //{
	 // printf("Audio test ready.");
	 // blDetectAudioR=true;
  //}
}

//-----------------------------------------------------------
// Get the IKsJackDescription interface that describes the
// audio jack or jacks that the endpoint device plugs into.
//-----------------------------------------------------------
HRESULT GetJackInfo(IMMDevice *pDevice, IKsJackDescription **ppJackDesc)
{
  HRESULT hr = S_OK;
  IDeviceTopology *pDeviceTopology = NULL;
  IConnector *pConnFrom = NULL;
  IConnector *pConnTo = NULL;
  IPart *pPart = NULL;
  IKsJackDescription *pJackDesc = NULL;

  if (NULL != ppJackDesc)
      *ppJackDesc = NULL;

  if (NULL == pDevice || NULL == ppJackDesc)
      return E_POINTER;

  // Get the endpoint device's IDeviceTopology interface.
  hr = pDevice->Activate(__uuidof(IDeviceTopology), CLSCTX_ALL,
    NULL, (void**)&pDeviceTopology);
  if (hr != S_OK) {
    SAFE_RELEASE(pDeviceTopology);
    return hr;
  }

  // The device topology for an endpoint device always
  // contains just one connector (connector number 0).
  hr = pDeviceTopology->GetConnector(0, &pConnFrom);
  if (hr != S_OK) {
    SAFE_RELEASE(pDeviceTopology);
    SAFE_RELEASE(pConnFrom);
    return hr;
  }

  // Step across the connection to the jack on the adapter.
  hr = pConnFrom->GetConnectedTo(&pConnTo);
  if (HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND) == hr)
    {
      // The adapter device is not currently active.
      hr = E_NOINTERFACE;
      //hr = S_OK;
    }
  if (hr != S_OK) {
    SAFE_RELEASE(pDeviceTopology);
    SAFE_RELEASE(pConnFrom);
    SAFE_RELEASE(pConnTo);
    return hr;
  }

  // Get the connector's IPart interface.
  hr = pConnTo->QueryInterface(__uuidof(IPart), (void**)&pPart);
  if (hr != S_OK) {
    SAFE_RELEASE(pDeviceTopology);
    SAFE_RELEASE(pConnFrom);
    SAFE_RELEASE(pConnTo);
    SAFE_RELEASE(pPart);
    return hr;
  }

  // Activate the connector's IKsJackDescription interface.
  hr = pPart->Activate(CLSCTX_INPROC_SERVER,
         __uuidof(IKsJackDescription), (void**)&pJackDesc);
   //printf("hr = %x (%d)\n", hr, (int)hr);
  if (hr != S_OK) {
    if (hr == E_INVALIDARG) {
      //printf("\tCouldn't activate IKsJackDescription because E_INVALIDARG\n");
    } else if (hr == E_POINTER) {
      //printf("\tCouldn't activate IKsJackDescription because E_POINTER\n");
    } else if (hr == E_NOINTERFACE) {
      //printf("\tCouldn't activate IKsJackDescription because E_NOINTERFACE\n");
    } else {
      //printf("\tCouldn't activate IKsJackDescription because UNKNOWN ERROR\n");
    }
  }
  if (hr != S_OK) {
    SAFE_RELEASE(pDeviceTopology);
    SAFE_RELEASE(pConnFrom);
    SAFE_RELEASE(pConnTo);
    SAFE_RELEASE(pPart);
    return hr;
  }

  //printf("\tGot jack description...\n");
  if (NULL != ppJackDesc)
    *ppJackDesc = pJackDesc;

  SAFE_RELEASE(pDeviceTopology);
  SAFE_RELEASE(pConnFrom);
  SAFE_RELEASE(pConnTo);
  SAFE_RELEASE(pPart);
  return hr;
}

//-----------------------------------------------------------
// This function enumerates all active (plugged in) audio
// rendering endpoint devices. It prints the friendly name
// and endpoint ID string of each endpoint device.
//-----------------------------------------------------------

const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);

void PrintEndpointNames(EDataFlow dataFlow, DWORD dwState)
{
  HRESULT hr = S_OK;
  IMMDeviceEnumerator *pEnumerator = NULL;
  IMMDeviceCollection *pCollection = NULL;
  IMMDevice *pEndpoint = NULL;
  IPropertyStore *pProps = NULL;
  LPWSTR pwszID = NULL;

  hr = CoCreateInstance(CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL, IID_IMMDeviceEnumerator, (void**)&pEnumerator);
  if (hr != S_OK) {
    SAFE_RELEASE(pEnumerator);
    return;
  }

  // DEVICE_STATE_ACTIVE, DEVICE_STATEMASK_ALL
  hr = pEnumerator->EnumAudioEndpoints(dataFlow, dwState, &pCollection);
  if (hr != S_OK) {
    SAFE_RELEASE(pEnumerator);
    SAFE_RELEASE(pCollection);
    return;
  }

  UINT  count;
  hr = pCollection->GetCount(&count);
  if (hr != S_OK) {
    SAFE_RELEASE(pEnumerator);
    SAFE_RELEASE(pCollection);
    return;
  }

  // Each loop prints the name of an endpoint device.
  for (ULONG i = 0; i < count; i++)
    {
      // Get pointer to endpoint number i.
      hr = pCollection->Item(i, &pEndpoint);
      if (hr != S_OK) {
 SAFE_RELEASE(pEndpoint);
 continue;
      }

      // Get the endpoint ID string.
      hr = pEndpoint->GetId(&pwszID);
      if (hr != S_OK) {
 CoTaskMemFree(pwszID);
 SAFE_RELEASE(pEndpoint);
 continue;
      }
        
      hr = pEndpoint->OpenPropertyStore(STGM_READ, &pProps);
      if (hr != S_OK) {
 CoTaskMemFree(pwszID);
 SAFE_RELEASE(pEndpoint);
 SAFE_RELEASE(pProps);
 continue;
      }

      PROPVARIANT varName;
      // Initialize container for property value.
      PropVariantInit(&varName);

      CoTaskMemFree(pwszID);
      pwszID = NULL;
      PropVariantClear(&varName);
      SAFE_RELEASE(pProps);

      // Got an endpoint now, so do the following:
      // 1.  Get/print the state
      // 2.  Get/print the jack description

      // now that I have the device, I can use a subset of the
      // PrintEndpointNames() function below....  I can also call:
      // Activate, GetId, GetState, and OpenPropertyStore.  For
      // examples of GetId and OpenPropertyStore, see
      // PrintEndpointNames().
      DWORD deviceState = 0;
      hr = pEndpoint->GetState(&deviceState);
      if (hr != S_OK) {
 SAFE_RELEASE(pEndpoint);
 continue;
      }
 
      //printf("\n\tInput device state = %x (%d), ", 
      //deviceState, (int)deviceState);
      if (deviceState & DEVICE_STATE_ACTIVE) { /*printf("Device is active!\n");*/ }
      if (deviceState & DEVICE_STATE_DISABLED) { /*printf("Device is disabled!\n");*/ }
      if (deviceState & DEVICE_STATE_NOTPRESENT) {/* printf("Device is not present!\n");*/ }
      if (deviceState & DEVICE_STATE_UNPLUGGED) { /*printf("Device is unplugged!\n"); */}

      IKsJackDescription *pJackDesc = NULL;
      hr =  GetJackInfo(pEndpoint, &pJackDesc);
      if (hr != S_OK) {
 SAFE_RELEASE(pJackDesc);
 SAFE_RELEASE(pEndpoint);
 continue;
      }	
  
      // now print the information in the KSJACK_DESCRIPTION,
      // especially IsConnected().
      UINT nJacks = 1;
      hr = pJackDesc->GetJackCount(&nJacks);
      if (hr != S_OK) {
 SAFE_RELEASE(pJackDesc);
 SAFE_RELEASE(pEndpoint);
 continue;
      }
      
     //printf("\tFound %d jacks\n", nJacks);
      KSJACK_DESCRIPTION ksjack;
      for (UINT i = 0; i < nJacks; i++) {
 hr = pJackDesc->GetJackDescription(i, &ksjack);
 if (hr != S_OK) {
   SAFE_RELEASE(pEndpoint);
   continue;
 }
 printJack(i, &ksjack);
      }

      SAFE_RELEASE(pJackDesc);
      SAFE_RELEASE(pEndpoint);
    }

  SAFE_RELEASE(pEnumerator);
  SAFE_RELEASE(pCollection);
  return;
}

//--------------------------------------------------------------------------
void _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{


	//BOOL blStringTime=false;
	//BOOL blStringN=false;
	//BOOL blS2=false;
	//BOOL blS3=false;
	//BOOL blS5=false;
	
	//int T=0;
	HANDLE hThread[3]={0};
	//HANDLE hThread;
	//HANDLE hThread1;
	//HANDLE hThread2;
	//HANDLE hThread3;
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
			if(_stricmp(CharUpper(argv[i+1]),"-usb")==0)
			{
				blDetectUSB=true;
				//T++;
				continue;
			}
			if(_stricmp(CharUpper(argv[i+1]),"-audio")==0)
			{
				blDetectAudio=true;
				continue;
			}
			if(_stricmp(CharUpper(argv[i+1]),"-lan")==0)
			{
				blDetectLan=true;
				//T++;
				continue;
			}
			if(_stricmp(CharUpper(argv[i+1]),"-cd")==0)
			{
				blDetectCD=true;
				//T++;
				continue;
			}
			if(_stricmp(CharUpper(argv[i+1]),"-card")==0)
			{
				blDetectCardReader=true;
				//T++;
				continue;
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
				TCHAR szOS[BUFSIZE];

				if( GetOSDisplayString( szOS ) )
				_tprintf( TEXT("\n%s\n"), szOS );
				if(strstr(szOS,"Vista")!=0||strstr(szOS,"Windows 7")!=0)
					blOSok=true;
				//HANDLE hThread;
				///*hThread = */;
				if(CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)blDetectThread,NULL,0,NULL)==NULL)
				{
					printf("Start thread fail.\n");
				}
				if(blDetectCD==true||!blDetectUSB&&!blDetectAudio&&!blDetectCD&&!blDetectLan&&!blDetectCardReader)
				{
					hThread[0] = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)blDetectCDThread,NULL,0,NULL);
					if(hThread[0]==NULL)
					{
						printf("Start thread fail.\n");
					}
				}
				if(blDetectUSB==true||!blDetectUSB&&!blDetectAudio&&!blDetectCD&&!blDetectLan&&!blDetectCardReader)
				{
					
					hThread[1] = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)blDetectUSBThread,NULL,0,NULL);
					if(hThread[1]==NULL)
					{
						printf("Start thread1 fail.\n");
					}
				}

				if(blDetectLan==true||!blDetectUSB&&!blDetectAudio&&!blDetectCD&&!blDetectLan&&!blDetectCardReader)
				{
					hThread[2] = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)blDetectlanThread,NULL,0,NULL);
					if(hThread[2]==NULL)
					{
						printf("Start thread2 fail.\n");
					}
				}
				if(blDetectCardReader==true||!blDetectUSB&&!blDetectAudio&&!blDetectCD&&!blDetectLan&&!blDetectCardReader)
				{
					hThread[3] = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)blDetectCarReaderThread,NULL,0,NULL);
					if(hThread[3]==NULL)
					{
						printf("Start thread3 fail.\n");
					}
				}
				if(blDetectAudio==true||!blDetectUSB&&!blDetectAudio&&!blDetectCD&&!blDetectLan&&!blDetectCardReader)
				{
					if(!blOSok)
					{
						printf("this audio detective for Vista and Win7 only\n");
						break;
					}

					// CoInitializeEx(NULL, COINIT_MULTITHREADED);

					// try the print function
					do
					{
						UINT nDevices,nC1;
						WAVEINCAPS stWIC={0};
						MMRESULT mRes;

						nDevices=waveInGetNumDevs();
						for(nC1 = 0;nC1 < nDevices;++nC1)
						{
							ZeroMemory(&stWIC,sizeof(WAVEINCAPS));
							mRes = waveInGetDevCaps(nC1,&stWIC,sizeof(WAVEINCAPS));
							//device[nC1] = stWIC.szPname;
							if (strstr(stWIC.szPname,"Line")||strstr(stWIC.szPname,"怀��"))
							{
								printf("Audio test ready.\n");
								blDetectAudioR=true;
								break;
							}
						}
						if(blDetectAudioR)
						{
							//WinExec("audio.bat",SW_SHOW);
							break;
						}
						HRESULT hr = S_OK;
						CoInitialize(NULL);
						//printf("Printing active eRender endpoints:\n\n");
						//PrintEndpointNames(eRender, DEVICE_STATE_ACTIVE);
						//printf("\nPrinting active eCapture endpoints:\n\n");
						PrintEndpointNames(eCapture, DEVICE_STATE_ACTIVE);

						//printf("\n\nPrinting all eRender endpoints:\n\n");
						PrintEndpointNames(eRender, DEVICE_STATEMASK_ALL);
						//printf("\nPrinting all eCapture endpoints:\n\n");

						//PrintEndpointNames(eCapture, DEVICE_STATEMASK_ALL);
						//printf("\n");
						if(iAu==0)
							iSum=iCN;
							iAds=iAd;
						if(iCN>iSum||iAd>iSum)
						{
							printf("Audio test ready.\n");
							//WinExec("audio.bat",SW_SHOW);
							break;//break;
						}
						iCN=0;
						iAd=0;
						CoUninitialize();
						Sleep(100);
					}while(++iAu);
				}
			}


		}
		if(!blDetectUSB&&!blDetectAudio&&!blDetectCD&&!blDetectLan&&!blDetectCardReader)
		WaitForMultipleObjects(4,hThread,1,INFINITE);
		if(blDetectCD)
		WaitForSingleObject(hThread[0],INFINITE);
		if(blDetectUSB)
		WaitForSingleObject(hThread[1],INFINITE);
		if(blDetectLan)
		WaitForSingleObject(hThread[2],INFINITE);
		if(blDetectCardReader)
		WaitForSingleObject(hThread[3],INFINITE);
		if(!blParameterOK) 
			ReadMe();

		if ((blParameterOK ) == TRUE)
		{
			if(blDetectUSB&&blDetectUSBR||blDetectCD&&blDetectCDR||blDetectLan&&blDetectLanR||blDetectAudio&&blDetectAudioR||blDetectCardReader&&blDetectCardR)
				End(0);
			else if(!blDetectUSB&&!blDetectCD&&!blDetectLan&&!blDetectAudio&&!blDetectCardReader&&blDetectUSBR&&blDetectCDR&&blDetectLanR&&blDetectAudioR&&blDetectCardR)
				End(0);
			else
				End(255);
		}
		else 
			End(255);
	}

}