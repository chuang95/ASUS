// Video-diags.cpp : 定義應用程式的進入點。
//
/*
----------------------------------------------------------------------------------------------
Rev1.00: Feb 24, 2009: Patrick
1. Modified WVideo.exe to be Video-diags.exe_Rev1.00.
2. Fixed issue that use -sf parameter with /3D function cannot save fps infomation to a file.  
----------------------------------------------------------------------------------------------
*/

#include "dxstdafx.h"
#include "stdafx.h"
#include "Video-diags.h"
#include "conio.h"
#include <Shlwapi.h>
#include "iostream"
using namespace std;
#define MAX_LOADSTRING 100
#define VK_RKEY 0x52
#define VK_GKEY 0x47
#define VK_BKEY 0x42
#define VK_YKEY 0x59
#define VK_NKEY 0x4E

// 全域變數:
HINSTANCE hInst;								// 目前執行個體
HANDLE hThread;
TCHAR szTitle[MAX_LOADSTRING];					// 標題列文字
TCHAR szWindowClass[MAX_LOADSTRING];			// 主視窗類別名稱
TCHAR szPictureFile[MAX_PATH];	
char szSpeciaKey[10]={0};
// 這個程式碼模組中所包含之函式的向前宣告:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	Help(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
//LRESULT CALLBACK	KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK	MouseProc(int nCode, WPARAM wParam, LPARAM lParam);
BOOL blBluePress = false;
BOOL blRedPress = false;
BOOL blGreenPress = false;
BOOL blNoPress = false;
BOOL blYNResult = false;
//bool blThread1()
//{
//	for(int i=0;i<100;i++)
//	{
//		keybd_event(VK_RETURN,0,0,0);
//		keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP,0);
//	}
//	return true;
//}
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
BOOL blThread()
{
	LONG64 l64StopTime=l64AddTime(iTestTimer,0);
	LONG64 l64CurrentTime=0;
	while(1)
	{
		l64CurrentTime=l64GetTime();
		if(l64CurrentTime>=l64StopTime)
		{
			blok=true;
			blExit=true;
			break;
		}
	}
	return true;
}
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	//		FILE *fp;
	//fp=fopen("123.txt","a+");
	//fprintf(fp,"%d\n",blok);
 	// TODO: 在此置入程式碼。
	MSG msg;
	HACCEL hAccelTable;
	TCHAR *ptr,en[2]=L" ";
	int count=0;
	wcscpy(szPictureFile, L"Smile.png\0");

	//判斷輸入參數的數量及紀錄字串至陣列
	if((ptr=wcstok(lpCmdLine,en))!=NULL)
	{
		arg_v[count+1]=ptr;
		count++;
		
		while((ptr=wcstok(NULL,en))!=NULL)	{
			arg_v[count+1]=ptr;
			count++;
		}
		arg_c = count;
		arg_v[count+1] = NULL;

		//判斷參數副程式
		BOOL blhelp;
		blhelp=blCheckArgument(arg_c,arg_v);
		if(!blhelp)
			blHelpParaOK=TRUE;
	}
	else 
		blHelpParaOK=TRUE;

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_WVIDEO);

	if(blTest3DFunction == FALSE) 
	{
		// 初始化全域字串
		LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
		LoadString(hInstance, IDC_WVIDEO, szWindowClass, MAX_LOADSTRING);
		MyRegisterClass(hInstance);

		// 執行應用程式初始設定:
		if (!InitInstance (hInstance, nCmdShow)) 
		{
			return FALSE;
		}
		// 主訊息迴圈:
		while (GetMessage(&msg, NULL, 0, 0)) 
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
				if(blSetTimer)
		{
		if(!blok&&blExit)
			return 255;
		else if(blok&&blExit)
			return 0;
		}
		if(blRGBTest)
		{
			if(blRedOK && blBlueOK && blGreenOK) 
				return 0;
			else 
				return 255;
		}
		if(blSetYN)
		{
			if(blYNResult) return 0;
			else return 255;
		}
		return (int) msg.wParam;
	}
	else 
	{
		if(!PathFileExists(szPictureFile))
		{
			TCHAR szMsg[MAX_PATH];
			wsprintf(szMsg, L"NO %s!!!", szPictureFile);
			MessageBox(NULL, szMsg, L"Error", MB_OK);
			return 255;
		}
		DXUTSetCallbackDeviceCreated( OnCreateDevice );
		DXUTSetCallbackDeviceReset( OnResetDevice );
		DXUTSetCallbackDeviceLost( OnLostDevice );
		DXUTSetCallbackDeviceDestroyed( OnDestroyDevice );
		DXUTSetCallbackMsgProc( MsgProc );
		//DXUTSetCallbackKeyboard( KeyboardProc );
		DXUTSetCallbackFrameRender( OnFrameRender );
		DXUTSetCallbackFrameMove( OnFrameMove );

	    DXUTSetCursorSettings( false, true );

		InitApp();

		DXUTInit( true, true, true ); // Parse the command line, handle the default hotkeys, and show msgboxes
		DXUTCreateWindow( L"WVideo 3D Test" );
		DXUTCreateDevice( D3DADAPTER_DEFAULT, true, 800, 600, IsDeviceAcceptable, ModifyDeviceSettings );
		DXUTToggleFullScreen();
		
		//hThread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)blThread1,NULL,0,NULL);
		//if(hThread==NULL)
		//{
		//	printf("Start thread fail.\n");
		//}
		//DXUTToggleREF();
		//DXUTToggleREF();
		//DXUTReset3DEnvironment();

		DXUTMainLoop();

		if(DXUTGetExitCode()!=0)
			return DXUTGetExitCode();
		else
			return iReturnCode;
	}


	//return 255;

}



//
//  函式: MyRegisterClass()
//
//  用途: 登錄視窗類別。
//
//  註解:
//
//  只有當您希望此程式碼能相容比 Windows 95 的 'RegisterClassEx' 函式更早的 Win32 系統時，才會需要
// 加入及使用這個函式。您必須呼叫這個函式，讓應用程式取得與它相關的 '正確格式 (Well Formed)' 圖示。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_WVIDEO);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= NULL;//(HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;//(LPCTSTR)IDC_WVIDEO;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_WVIDEO);

	return RegisterClassEx(&wcex);
}

//
//   函式: InitInstance(HANDLE, int)
//
//   用途: 儲存執行個體控制代碼並且建立主視窗
//
//   註解:
//
//        在這個函式中，我們會將執行個體控制代碼儲存在全域變數中，
//        並且建立和顯示主程式視窗。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
   int	X,Y;

   X = GetSystemMetrics(SM_CXSCREEN);
   Y = GetSystemMetrics(SM_CYSCREEN);

   hInst = hInstance; // 將執行個體控制代碼儲存在全域變數中

   hWnd = CreateWindow(szWindowClass, szTitle, WS_POPUPWINDOW ,
	   -1, -1, X+2, Y+2, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   if(!blHelpParaOK)  {
	   ShowWindow(hWnd, nCmdShow);
	   SetWindowPos(hWnd,HWND_TOPMOST,-1,-1,X+2,Y+2,SWP_SHOWWINDOW);
   }
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函式: WndProc(HWND, unsigned, WORD, LONG)
//
//  用途:  處理主視窗的訊息。
//
//  WM_COMMAND	- 處理應用程式功能表
//  WM_PAINT	- 繪製主視窗
//  WM_DESTROY	- 傳送結束訊息然後返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int		wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC		hdc;
	int		iRand,i,j;


	hwnd=hWnd;

	switch (message) 
	{
	case WM_CREATE:
		ShowCursor(FALSE);

		GetClientRect(hWnd, &rt);

		SetTimer(hWnd, IDT_TIMER1, 500, NULL);
		SetTimer(hWnd, IDT_TIMER2, iTestTimer, NULL);

		// HOOK Keyboard and Mouse
		//HookData[ID_KEYBHOOK].nType = WH_KEYBOARD; 
  //      HookData[ID_KEYBHOOK].hKprc = KeyboardProc;
  //      HookData[ID_KEYBHOOK].hHook = SetWindowsHookEx(HookData[ID_KEYBHOOK].nType,HookData[ID_KEYBHOOK].hKprc,
  //                                    (HINSTANCE) NULL, GetCurrentThreadId()); 
		HookData[ID_KEYBHOOK].nType = WH_KEYBOARD_LL; 
        HookData[ID_KEYBHOOK].hKprc = LowLevelKeyboardProc;
        HookData[ID_KEYBHOOK].hHook = SetWindowsHookEx(HookData[ID_KEYBHOOK].nType,HookData[ID_KEYBHOOK].hKprc,
                                      hInst, 0);//GetCurrentThreadId()); 
		HookData[ID_MOUSEHOOK].nType = WH_MOUSE; 
        HookData[ID_MOUSEHOOK].hKprc = MouseProc; 
        HookData[ID_MOUSEHOOK].hHook = SetWindowsHookEx(HookData[ID_MOUSEHOOK].nType,HookData[ID_MOUSEHOOK].hKprc,
                                      hInst, 0);//GetCurrentThreadId()); 
		

		if (blHelpParaOK) {
			ShowCursor(TRUE);
			iReturnCode=255;
			DialogBox(hInst, (LPCTSTR)IDD_HelpBox, hWnd, (DLGPROC)Help);	
		}

		if(blRGBTest) {

			srand((unsigned)time( NULL ));
			iRand  = rand()%3;	
			if(iRand<3) {
				i=nTestIndex[iRand];
				j=nTestIndex[0];
				nTestIndex[iRand]=j;
				nTestIndex[0]=i;
			}


			iTestIndex=3;
			
		}		

		blPressSpace = TRUE; // first

		break;
	case WM_TIMER:
		if(blPressSpace)  {
			ShowPattern(hWnd,iTestItemIndex);
			blPressSpace = FALSE;
		}

		if((blRGBTest) && (iTestIndex == 3) && (nProcedureIndex<3) && (blNext==FALSE))
		{
			if(nTestIndex[nProcedureIndex]==0) {
				ShowPattern(hWnd,3);
				blRedKey=TRUE; blGreenKey=blBlueKey=FALSE;
			}else if(nTestIndex[nProcedureIndex]==1) {
				ShowPattern(hWnd,4);
				blGreenKey=TRUE; blRedKey=blBlueKey=FALSE;
			}else if(nTestIndex[nProcedureIndex]==2) {
				ShowPattern(hWnd,5); 
				blBlueKey=TRUE; blGreenKey=blRedKey=FALSE;
			}
			nProcedureIndex++; blNext=TRUE;
		}
		
		if((blExit==TRUE) || (blShiftPress && blAltPress) ||
			(nProcedureIndex == 3 && blNext == false)//(blRedOK && blBlueOK && blGreenOK)
			)
			SendMessage(hWnd, WM_CLOSE,0,0);
			

		if(wParam == IDT_TIMER1) {
		}

		if((wParam == IDT_TIMER2) && (blSetAutoLoop == TRUE)) {

			iTestItemIndex++;
			if(iTestItemIndex>23) { 

			  if(blSetLoop==TRUE) iLoopCount++; 

			  iTestItemIndex =1;
			}

			if( (blSetLoop==TRUE) && (iLoopCount >= iLoop))  SendMessage(hWnd, WM_CLOSE,0,0);
			
			ShowPattern(hWnd,iTestItemIndex);
		}


		if((wParam != IDT_TIMER1)&&(wParam != IDT_TIMER2))
			return DefWindowProc(hWnd, message, wParam, lParam);

		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// 剖析功能表選取項目:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		ShowCursor(TRUE);
		UnhookWindowsHookEx(HookData[ID_KEYBHOOK].hHook); 
		UnhookWindowsHookEx(HookData[ID_MOUSEHOOK].hHook); 
		KillTimer(hWnd, IDT_TIMER1);
		KillTimer(hWnd, IDT_TIMER2);
		//printf("%08X %08X",&hStdIn,&hConsoleIn);
		PostQuitMessage(iReturnCode);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


/**************************************************************** 
  WH_KEYBOARD hook procedure 
 ****************************************************************/ 
 
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) 
{ 
	BOOL	blTransitionStatus=FALSE,blAltPress=FALSE,blExtendedKeyFlag=FALSE,blSeqPressOK=FALSE;
	KBDLLHOOKSTRUCT *pKBhook = (KBDLLHOOKSTRUCT *)lParam;
 
	blExtendedKeyFlag	= (pKBhook -> flags)  & 0x01;
	blTransitionStatus	= (pKBhook -> flags >> 7) & 0x01;
	blAltPress			= (pKBhook -> flags >> 5) & 0x01;

    if (blHelpParaOK)  // do not process message 
        return CallNextHookEx(HookData[ID_KEYBHOOK].hHook, nCode, wParam, lParam); 

 	blExitHook = FALSE;

	int szTemp[100]={0};
	//sprintf_s(szTemp,100,"%08X %08X",pKBhook->vkCode,wParam);
	//MessageBoxA(NULL,szTemp,"dsf",0);
	//FILE *fp;
	//fp=fopen("123.txt","a+");
	//fprintf(fp,"%d %d %08X %08X\n",nCode,pKBhook->vkCode,wParam,lParam);
	//fprintf(fp,"%d ",MapVirtualKey(pKBhook->scanCode,0));
	//fprintf(fp,"%d ",MapVirtualKey(pKBhook->scanCode,1));
	//fprintf(fp,"%d \n",MapVirtualKey(pKBhook->scanCode,0x02));
	//fclose(fp);

    //DWORD dwMsg = 1;
    //dwMsg += pKBhook->scanCode << 16;
    //dwMsg += pKBhook->flags << 24;  
	//if (blSpeciaKey==TRUE)
	//{
	//	//sprintf_s(szTemp,100,"%d",szSpeciaKey);
	//	szSpeciaKey[0]='a'
	//	switch(szTemp)
	//}
	switch(pKBhook->vkCode)
	{
	//if(blSetSpeciaKey) break;
	case 0x1B:
		if(!blSetYN && (blSetSpeciaKey==FALSE) && (!blRGBTest))	blExit=TRUE;
		break;
	//case 0x20:
	//case 0x22:
	//case 0x27:
	//case 0x28:
	//case 0x0d:
		//if((blSetSpeciaKey==FALSE)&& (!blRGBTest) && (WORD)(wParam)==WM_KEYDOWN) {
		//	if(!blSetYN /*&& blSetPattern*/ && !blSetLoop && !blSetAutoLoop)
		//	{ 
		//		blExit = true;
		//		break;
		//	}
		//	iOldTestItemIndex = iTestItemIndex;
		//	iTestItemIndex++;
		//	if(iTestItemIndex > MaxPattern) iTestItemIndex=1;
		//	ShowPattern(hwnd,iTestItemIndex);
		//}
		//blPressSpace=TRUE;
		//break;
	case 0x21:
	case 0x25:
	case 0x28:
		if(/*(blSetSpeciaKey==FALSE)&&*/ (!blRGBTest)&& (!blTestCB)&& (WORD)(wParam)==WM_KEYDOWN && blSetK== TRUE) {
			iTestItemIndex--;
			if(iTestItemIndex == 0 ) iTestItemIndex=23;
			ShowPattern(hwnd,iTestItemIndex);
		}
		break;
	case 0x26:
	case 0x27:
		if(/*(blSetSpeciaKey==FALSE)&&*/ (!blRGBTest)&& (!blTestCB) && (WORD)(wParam)==WM_KEYDOWN && blSetK== TRUE) {
			//if(!blSetYN && !blSetSpeciaKey/*blSetPattern*/ && !blSetLoop && !blSetAutoLoop)
			//{ 
			//	blExit = true;
			//	break;
			//}
			iOldTestItemIndex = iTestItemIndex;
			iTestItemIndex++;
			if(iTestItemIndex > MaxPattern) iTestItemIndex=1;
			ShowPattern(hwnd,iTestItemIndex);
		}
		break;
	case 0xa0: //Left-Shift
	case 0xa1: //Right-Shift
		if((blSetSpeciaKey==TRUE)&& (!blRGBTest) && blSpeciaKey==FALSE) {
			blShiftPress=TRUE;
			if(blAltPress) {  //Press Alt Key
				blAltPress=TRUE;
				blExit=TRUE;
			}			
		}
		break;
	case VK_BKEY:	
		if(blTransitionStatus && blRGBTest&& (!blTestCB))
		{
			if(blBlueKey && !blRedPress && !blGreenPress) blBlueOK=TRUE;
			else if(blRedKey) blRedOK=false;
			else if(blGreenKey) blGreenOK=false;
			blNext=FALSE;
		}
		if(blTransitionStatus&& (!blTestCB)) blBluePress = false;
		else blBluePress = true;		
		break;
	case VK_GKEY:	
		if(blTransitionStatus && blRGBTest&& (!blTestCB))
		{
			if(blGreenKey && !blRedPress && !blBluePress) blGreenOK=TRUE;
			else if(blRedKey) blRedOK=false;
			else if(blBlueKey) blBlueOK=false;
			blNext=FALSE;
		}
		if(blTransitionStatus&& (!blTestCB)) blGreenPress = false;
		else blGreenPress = true;		
		break;
	case VK_RKEY:			
		if(blTransitionStatus && blRGBTest&& (!blTestCB))
		{
			if(blRedKey && !blGreenPress && !blBluePress) blRedOK=TRUE;
			else if(blBlueKey) blBlueOK=false;
			else if(blGreenKey) blGreenOK=false;
			blNext=FALSE;
		}
		if(blTransitionStatus&& (!blTestCB)) blRedPress = false;
		else blRedPress = true;		
		break;
	case VK_YKEY:
		if(blSetYN && (blSetSpeciaKey==FALSE)&& (!blRGBTest)) {
			blExit = true;
			blYNResult = true;
			break;
		}
		break;
	case VK_NKEY:
		if(blSetYN && (blSetSpeciaKey==FALSE)&& (!blRGBTest)) 
		{
			blExit = true;
			blYNResult = false;
			break;
		}
		if(blTransitionStatus) blNoPress = false;
		else blNoPress = true;		
		break;
	default:
		if(szSpeciaKey[0]==MapVirtualKey(pKBhook->vkCode,0x02) && blSpeciaKey==TRUE)
		{
			blExit = true;
			break;
		}
		else if(/*(blSetSpeciaKey==FALSE)&&*/ (!blRGBTest)&& (!blTestCB) && (WORD)(wParam)==WM_KEYDOWN && blSetK== TRUE) 
		{
			//if(!blSetYN && !blSetSpeciaKey/*blSetPattern*/  &&!blSetLoop && !blSetAutoLoop)
			//{ 
			//	blExit = true;
			//	break;
			//}
			iOldTestItemIndex = iTestItemIndex;
			iTestItemIndex++;
			if(iTestItemIndex > MaxPattern) iTestItemIndex=1;
			ShowPattern(hwnd,iTestItemIndex);
		}
		break;
	}
	//if(blExitHook==TRUE)  return (LRESULT) 0;
    //return CallNextHookEx(HookData[ID_KEYBHOOK].hHook, nCode, wParam, lParam); 
	//if(blExitHook==FALSE)  
	//if(blSetSpeciaKey==TRUE)
		return (LRESULT) 1;
	//return CallNextHookEx(HookData[ID_KEYBHOOK].hHook, nCode, wParam, lParam);
} 

/**************************************************************** 
  WH_MOUSE hook procedure 
 ****************************************************************/ 
 
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) 
{ 
    if (nCode < 0)  // do not process the message 
        return CallNextHookEx(HookData[ID_MOUSEHOOK].hHook, nCode, wParam, lParam); 
 
    return CallNextHookEx(HookData[ID_MOUSEHOOK].hHook, nCode, wParam, lParam); 
} 

// [關於] 方塊的訊息處理常式。
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}


// 處理參數副程式

BOOL blCheckArgument(int arg_c, TCHAR* arg_v[]) 
{
	int i;

	//InitConsoleDisplay();

//	if(arg_c==1) return true;

	for (i = 0; i <=(arg_c-1); i++)
	{
		if(wcsicmp(arg_v[i+1],L"-x")==0) {
			blx=TRUE;
			if(wcsicmp(arg_v[i+2],L"")!=0) {
				ix = _wtoi(arg_v[i+2]);
			}
			continue;
		}
		if(wcsicmp(arg_v[i+1],L"-y")==0) {
			bly=TRUE;
			if(wcsicmp(arg_v[i+2],L"")!=0) {
				iy= _wtoi(arg_v[i+2]);
			}
			continue;
		}
		if(wcsicmp(arg_v[i+1],L"-bw")==0) {
			blBW=TRUE;
			if(wcsicmp(arg_v[i+2],L"")!=0) {
				ibw = _wtoi(arg_v[i+2]);
				if(ibw>1)
				{
					blHelpParaOK=TRUE;
					break;
				}
			}

			continue;
		}
		if(wcsicmp(arg_v[i+1],L"-a")==0) {
			blSetAutoLoop=TRUE;
			continue;
		}
		if(wcsicmp(arg_v[i+1],L"-c")==0) {
			blSetConfirmCheck=TRUE;
			continue;
		}
		if(wcsicmp(arg_v[i+1],L"-s")==0) {
			blSetSpeciaKey=TRUE;
			if(wcsicmp(arg_v[i+2],L"")!=0 && arg_v[i+2][0]!='/' && arg_v[i+2][0]!='-'/*wcsicmp(arg_v[i+2],L"/t")!=0*/) {
				blSpeciaKey=TRUE;
				CharUpper(arg_v[i+2]);
				memcpy(szSpeciaKey,arg_v[i+2],2);
			}	
			continue;
		}
		if(wcsicmp(arg_v[i+1],L"-sd")==0) {
			blSetSpeciaKey=TRUE;
			iDigits = 2;
			continue;
		}
		if(wcsicmp(arg_v[i+1],L"-sf")==0) {
			blSaveFile=TRUE;
			if(wcsicmp(arg_v[i+2],L"")!=0 ) {
				wcscpy(szLogFile,arg_v[i+2]);
				hFile = CreateFile(szLogFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL, NULL);   
				if (hFile == INVALID_HANDLE_VALUE) 
				{
					MessageBox(NULL, L"Could not open file.", L"ok", MB_OK);
					return false;
					//ErrorHandler("Could not open file.");  
				}
			}
			continue;
		}
		if(wcsicmp(arg_v[i+1],L"-fmax")==0) {
			blSetFPSMax=TRUE;
			if(wcsicmp(arg_v[i+2],L"")!=0) {
				dFmax = _wtof(arg_v[i+2]);
			}
			continue;
		}
		if(wcsicmp(arg_v[i+1],L"-fmin")==0) {
			blSetFPSMin=TRUE;
			if(wcsicmp(arg_v[i+2],L"")!=0) {
				dFmin = _wtof(arg_v[i+2]);
			}
			continue;
		}
		if(wcsicmp(arg_v[i+1],L"-yn")==0) {
			blSetYN=TRUE;			
			continue;
		}
		if(wcsicmp(arg_v[i+1],L"-k")==0) {
			blSetK=TRUE;			
			continue;
		}
		if(wcsicmp(arg_v[i+1],L"-p")==0) {
			blSetPattern=TRUE;
			//if(arg_c >= i+2)	
			if(wcsicmp(arg_v[i+2],L"")!=0) {
				iTestItemIndex = _wtoi(arg_v[i+2]);
			}			
			continue;
		}
		if(wcsicmp(arg_v[i+1],L"-d")==0) {
			
			//if(arg_c >= i+2)	
			if(wcsicmp(arg_v[i+2],L"")!=0) {
				blSetTimer=TRUE;
				iTestTimer = _wtoi(arg_v[i+2]);
			}
			continue;
		}
        if(wcsicmp(arg_v[i+1],L"-loop")==0) {
			blSetLoop=TRUE;
			//if(arg_c >= i+2)	
			if(wcsicmp(arg_v[i+2],L"")!=0) {
				iLoop = _wtoi(arg_v[i+2]);
			}
			continue;
		}
		if(wcsicmp(arg_v[i+1],L"-Red")==0) {
			if(wcsicmp(arg_v[i+2],L"")!=0) {
				iRed = _wtoi(arg_v[i+2]);
			}
			continue;
		}
		if(wcsicmp(arg_v[i+1],L"-Green")==0) {
			if(wcsicmp(arg_v[i+2],L"")!=0) {
				iGreen = _wtoi(arg_v[i+2]);
			}
			continue;
		}
		if(wcsicmp(arg_v[i+1],L"-Blue")==0) {
			if(wcsicmp(arg_v[i+2],L"")!=0) {
				iBlue = _wtoi(arg_v[i+2]);
			}
			continue;
		}
		if(wcsicmp(arg_v[i+1],L"-pic")==0) {
			wsprintf(szPictureFile, L"%s\0", arg_v[i+2]);
			continue;
		}
	}
	for (i = 0; i <= (arg_c-1); i++)
	{
		if (wcsicmp(arg_v[i+1], L"?")==0  || wcsicmp(arg_v[i+1], L"/?")==0 ||
			wcsicmp(arg_v[i+1], L"/H")==0 || wcsicmp(arg_v[i+1], L"/HELP")==0)		{
				iReturnCode=255;
				blHelpParaOK=TRUE;
				break;
		}
		if(wcsicmp(arg_v[i+1], L"/T")==0) {

			if(iTestItemIndex==0) iTestItemIndex=1;
			if(iTestTimer == 0) iTestTimer = 1000;
			//if(blSetPattern)	iTestItemIndex = iTestNo;
			if(blSetTimer)
				hThread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)blThread,NULL,0,NULL);
			return TRUE;
			break;
		}
		if(wcsicmp(arg_v[i+1], L"/RGB")==0) {
			blRGBTest=TRUE;	
			return TRUE;
			break;
		}
		if(wcsicmp(arg_v[i+1], L"/3D")==0) {
			blTest3DFunction=TRUE;	
			return TRUE;
			break;
		}
		if(wcsicmp(arg_v[i+1], L"/CB")==0) {
			blTestCB=TRUE;
			if(blBW)
			{
				if(ibw==0)
					iTestItemIndex=26;
				if(ibw==1)
					iTestItemIndex=27;
			}
			else
				iTestItemIndex=26;
			if(blSetTimer)
				hThread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)blThread,NULL,0,NULL);
			return TRUE;
			break;
		}
		
		if(wcsicmp(arg_v[i+1], L"/version")==0) {
			blversion=TRUE;		
			printf("%s",sRevision);
			AttachConsole(ATTACH_PARENT_PROCESS); // 
            freopen( "CONOUT$", "w+t", stdout );// 扠③迡
			clrscr();
            printf("%s",sRevision);          // 迡杅擂
			keybd_event(VK_RETURN,0,0,0);
			keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP,0);
            FreeConsole();
			exit(255);
			return TRUE;
			break;
		}
	}

	return FALSE;
}


// Help 方塊的訊息處理常式。
LRESULT CALLBACK Help(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{	
	HDC hDlgdc;
	int x=5,y=5,i;

	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_PAINT:
		hDlgdc=GetDC(hDlg);
		SetBkMode(hDlgdc, TRANSPARENT);

		//if(blversion/*&&!blvert*/)
		//{
		//	for(i=0;i<1;i++)
		//	{
		//		y+=180;
		//		x+=280;
		//		TextOut(hDlgdc,x,y,wcVersion[i],(int)wcslen(wcVersion[i]));
		//	}
		//}
		//if(!blversion)
		//{
		for(i=0;i<22;i++)
		{
			TextOut(hDlgdc,x,y,wcText[i],(int)wcslen(wcText[i]));
			y+=19;
		}
		//}
		ReleaseDC(hDlg,hDlgdc);
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
		{
			EndDialog(hDlg, LOWORD(wParam));
			blExit=TRUE;
			//return TRUE;
		}
		break;
	case WM_CLOSE:
		blExit=TRUE;
		break;

	}
	return FALSE;
}

void ShowPattern(HWND hWnd,int iPatternNum)
{
	HDC		hdc;
	int		x,y,x1,y1,i,j;
	RECT	XY,xy,xy1;
	HPEN	hPenWhite,hPenRed,hPenGreen,hPenBlue,hPenBlack,hPenCyan;
	//char	*szTemp="yes";


	hdc = GetDC(hWnd);
	XY.bottom	= rt.bottom-1;
	XY.left		= rt.left;
	XY.right	= rt.right-1;
	XY.top		= rt.top;

	hPenWhite	= CreatePen(PS_SOLID, 1, RGB(0xFF,0xFF,0xFF));
	hPenRed		= CreatePen(PS_SOLID, 1, RGB(0xFF,0,0));
	hPenGreen	= CreatePen(PS_SOLID, 1, RGB(0,0xFF,0));
	hPenBlue	= CreatePen(PS_SOLID, 1, RGB(0,0,0xFF));
	hPenBlack	= CreatePen(PS_SOLID, 1, RGB(0,0,0));
	hPenCyan	= CreatePen(PS_SOLID, 1, RGB(0,0x7f,0x7f));


	switch(iPatternNum)
	{
	case 1:

		FillRect(hdc,&rt, CreateSolidBrush(RGB(0,0,0)));
		SelectObject(hdc, hPenWhite);
		MoveToEx(hdc,XY.left,XY.top,NULL);
		LineTo(hdc,XY.right ,XY.top);
		MoveToEx(hdc,XY.left,XY.bottom ,NULL);
		LineTo(hdc,XY.right ,XY.bottom );

		SelectObject(hdc, hPenRed);
		MoveToEx(hdc,XY.left,XY.top,NULL);
		LineTo(hdc,XY.left ,XY.bottom);

		SelectObject(hdc, hPenBlue);
		MoveToEx(hdc,XY.right,XY.top,NULL);
		LineTo(hdc,XY.right ,XY.bottom);	
		
		break;
	case 2:
		FillRect(hdc,&rt, CreateSolidBrush(RGB(0xff,0xff,0xff)));
		break;
	case 3:
		FillRect(hdc,&rt, CreateSolidBrush(RGB(0xff,0,0)));
		break;
	case 4:
		FillRect(hdc,&rt, CreateSolidBrush(RGB(0,0xff,0)));
		break;
	case 5:
		FillRect(hdc,&rt, CreateSolidBrush(RGB(0,0,0xff)));
		break;
	case 6:
		FillRect(hdc,&rt, CreateSolidBrush(RGB(0x7f,0,0)));
		break;
	case 7:
		FillRect(hdc,&rt, CreateSolidBrush(RGB(0,0x7f,0)));
		break;
	case 8:
		FillRect(hdc,&rt, CreateSolidBrush(RGB(0,0,0x7f)));
		break;
	case 9:
		FillRect(hdc,&rt, CreateSolidBrush(RGB(0x7f,0x7f,0x7f)));
		break;
	case 10:
		FillRect(hdc,&rt, CreateSolidBrush(RGB(0x3f,0x3f,0x3f)));
		break;
	case 11:
		FillRect(hdc,&rt, CreateSolidBrush(RGB(0,0,0)));
		xy.bottom = rt.bottom;
		xy.top	= rt.top;
		for(i=0;i<16;i++) {
			xy.right = (rt.right /16)*(i+1);
			xy.left  = (rt.right /16)*i;
			if(i<4)				FillRect(hdc,&xy, CreateSolidBrush( RGB(0xff-(40*i),0,0) ));
			if((i>=4)&&(i<8))	FillRect(hdc,&xy, CreateSolidBrush( RGB(0,0xff-(40*(i-4)),0) ));
			if((i>=8)&&(i<12))	FillRect(hdc,&xy, CreateSolidBrush( RGB(0,0,0xff-(40*(i-8))) ));
			if(i>=12)			FillRect(hdc,&xy, CreateSolidBrush( RGB(0xff-(40*(i-12)),0xff-(40*(i-12)),0xff-(40*(i-12))) ));
		}
		break;
	case 12:
		FillRect(hdc,&rt, CreateSolidBrush(RGB(0,0,0)));
		xy.bottom	= rt.bottom / 2;
		xy.top		= rt.top;
		xy.right	= rt.right / 2;
		xy.left		= rt.left;
		FillRect(hdc,&xy, CreateSolidBrush(RGB(0xff,0xff,0xff)));
		xy.bottom	= rt.bottom ;
		xy.top		= rt.bottom / 2;
		xy.right	= rt.right ;
		xy.left		= rt.right / 2;
		FillRect(hdc,&xy, CreateSolidBrush(RGB(0xff,0xff,0xff)));
		break;
	case 13:
		FillRect(hdc,&rt, CreateSolidBrush(RGB(0,0,0)));
		xy.bottom	= rt.bottom / 2;
		xy.top		= rt.top;
		xy.right	= rt.right ;
		xy.left		= rt.right / 2;
		FillRect(hdc,&xy, CreateSolidBrush(RGB(0xff,0xff,0xff)));
		xy.bottom	= rt.bottom ;
		xy.top		= rt.bottom / 2;
		xy.right	= rt.right / 2;
		xy.left		= rt.left;
		FillRect(hdc,&xy, CreateSolidBrush(RGB(0xff,0xff,0xff)));
		break;
	case 14:
		FillRect(hdc,&rt, CreateSolidBrush(RGB(0,0,0)));
		break;
	case 15:
		FillRect(hdc,&rt, CreateSolidBrush(RGB(0,0,0)));
		for(i=0 ; i<rt.right ; i+=4) {
			SelectObject(hdc, hPenWhite);
			MoveToEx(hdc,XY.left+i,XY.top,NULL);
			LineTo(hdc,XY.left+i ,XY.bottom);
			MoveToEx(hdc,XY.left+i+1,XY.top ,NULL);
			LineTo(hdc,XY.left+i+1 ,XY.bottom );
		}
		break;
	case 16:
		FillRect(hdc,&rt, CreateSolidBrush(RGB(0,0,0)));
		xy.bottom	= (rt.bottom / 3) * 2;
		xy.top		= rt.bottom / 3;
		xy.right	= (rt.right /3) * 2;
		xy.left		= rt.right / 3;
		FillRect(hdc,&xy, CreateSolidBrush(RGB(0xff,0xff,0xff)));
		break;

	case 17:
		FillRect(hdc,&rt, CreateSolidBrush(RGB(0x7f,0x7f,0x7f)));
		xy.bottom	= (rt.bottom / 3) * 2;
		xy.top		= rt.bottom / 3;
		xy.right	= (rt.right /3) * 2;
		xy.left		= rt.right / 3;
		FillRect(hdc,&xy, CreateSolidBrush(RGB(0,0,0)));
		break;
	case 18:
		FillRect(hdc,&rt, CreateSolidBrush(RGB(0,0,0)));
		xy.left		= rt.left;
		xy.right	= rt.right;

		for(i=0;i<32;i++) {
			xy.bottom	= (rt.bottom / 32) * ( i + 1) ;
			xy.top		= (rt.bottom / 32) * i;
			FillRect(hdc,&xy, CreateSolidBrush( RGB(0xff-(8*i),0xff-(8*i),0xff-(8*i)) ));
		}
		break;
	case 19:
		FillRect(hdc,&rt, CreateSolidBrush(RGB(0,0,0)));
		SelectObject(hdc, hPenCyan);

		for(i=0; i < rt.right + rt.bottom ; i+=2) {

			x	=	i;
			y	=	XY.top;
			x1	=	XY.left;
			y1	=	i;

			if( x >= XY.right) {
				x = XY.right;
				y = i - XY.right ;
			}
			if( y1 >= XY.bottom) {
				x1 =  i - XY.bottom ;
				y1 = XY.bottom;
			}

			MoveToEx(hdc,x,y,NULL);
			LineTo(hdc,x1,y1);
		}

		break;
	case 20:
		FillRect(hdc,&rt, CreateSolidBrush(RGB(0,0,0)));
		xy.top		= rt.top;
		xy.bottom	= rt.bottom;

		for(i=0;i<32;i++) {
			xy.right	= (rt.right / 32) * ( i + 1) ;
			xy.left		= (rt.right / 32) * i;
			FillRect(hdc,&xy, CreateSolidBrush( RGB(0xff-(8*i),0xff-(8*i),0xff-(8*i)) ));
		}
		break;
	case 21:
		FillRect(hdc,&rt, CreateSolidBrush(RGB(0,0,0)));
		xy.top		= rt.top;
		xy.bottom	= rt.bottom;

		for(i=0;i<32;i++) {
			xy.right	= (rt.right / 32) * ( i + 1) ;
			xy.left		= (rt.right / 32) * i;
			FillRect(hdc,&xy, CreateSolidBrush( RGB(0xff-(0xff-(8*i)),0xff-(0xff-(8*i)),0xff-(0xff-(8*i))) ));
		}
		break;
	case 22:
		FillRect(hdc,&rt, CreateSolidBrush(RGB(0,0,0)));
		xy.top		= rt.top;
		xy.bottom	= rt.bottom;

		for(i=0;i<16;i++) {
			xy.right	= (rt.right / 16) * ( i + 1) ;
			xy.left		= (rt.right / 16) * i;
			FillRect(hdc,&xy, CreateSolidBrush( RGB(0xff-(16*i),0xff-(16*i),0xff-(16*i)) ));
		}
		break;
	case 23:
		FillRect(hdc,&rt, CreateSolidBrush(RGB(0,0,0)));
		xy.top		= rt.top;
		xy.bottom	= rt.bottom;

		for(i=0;i<16;i++) {
			xy.right	= (rt.right / 16) * ( i + 1) ;
			xy.left		= (rt.right / 16) * i;
			FillRect(hdc,&xy, CreateSolidBrush( RGB(0xff-(0xff-(16*i)),0xff-(0xff-(16*i)),0xff-(0xff-(16*i))) ));
		}
		break;
	case 24:
		FillRect(hdc,&rt, CreateSolidBrush(RGB(0,0,0)));
		xy.bottom = rt.bottom;
		xy.top	= rt.top;
		for(i=0;i<7;i++) {
			xy.right = (rt.right /7)*(i+1);
			xy.left  = (rt.right /7)*i;
			if(i==0)	FillRect(hdc,&xy, CreateSolidBrush( RGB(0xff,0xff,0xff) ));
			if(i==1)	FillRect(hdc,&xy, CreateSolidBrush( RGB(0xff,0xff,0) ));
			if(i==2)	FillRect(hdc,&xy, CreateSolidBrush( RGB(0,0xff,0xff) ));
			if(i==3)	FillRect(hdc,&xy, CreateSolidBrush( RGB(0,0xff,0) ));
			if(i==4)	FillRect(hdc,&xy, CreateSolidBrush( RGB(0xff,0,0xff) ));
			if(i==5)	FillRect(hdc,&xy, CreateSolidBrush( RGB(0xff,0,0) ));
			if(i==6)	FillRect(hdc,&xy, CreateSolidBrush( RGB(0,0,0xff) ));
		}
		break;
	case 25:
		FillRect(hdc,&rt, CreateSolidBrush(RGB(0,0,0)));
		xy.bottom = rt.bottom - ((rt.bottom /12)*4);
		xy.top	= rt.top;
		for(i=0;i<7;i++) {
			xy.right = (rt.right /7)*(i+1);
			xy.left  = (rt.right /7)*i;
			if(i==0)	FillRect(hdc,&xy, CreateSolidBrush( RGB(0xbf,0xbf,0xbf) ));
			if(i==1)	FillRect(hdc,&xy, CreateSolidBrush( RGB(0xbf,0xbf,0) ));
			if(i==2)	FillRect(hdc,&xy, CreateSolidBrush( RGB(0,0xbf,0xbf) ));
			if(i==3)	FillRect(hdc,&xy, CreateSolidBrush( RGB(0,0xbf,0) ));
			if(i==4)	FillRect(hdc,&xy, CreateSolidBrush( RGB(0xbf,0,0xbf) ));
			if(i==5)	FillRect(hdc,&xy, CreateSolidBrush( RGB(0xbf,0,0) ));
			if(i==6)	FillRect(hdc,&xy, CreateSolidBrush( RGB(0,0,0xbf) ));
		}
		xy.bottom = rt.bottom - ((rt.bottom /12)*3);
		xy.top	= rt.bottom - ((rt.bottom /12)*4);
		for(i=0;i<7;i++) {
			xy.right = (rt.right /7)*(i+1);
			xy.left  = (rt.right /7)*i;
			if(i==0)	FillRect(hdc,&xy, CreateSolidBrush( RGB(0,0,0xbf) ));
			if(i==1)	FillRect(hdc,&xy, CreateSolidBrush( RGB(16,16,16) ));
			if(i==2)	FillRect(hdc,&xy, CreateSolidBrush( RGB(0xbf,0,0xbf) ));
			if(i==3)	FillRect(hdc,&xy, CreateSolidBrush( RGB(16,16,16) ));
			if(i==4)	FillRect(hdc,&xy, CreateSolidBrush( RGB(0,0xbf,0xbf) ));
			if(i==5)	FillRect(hdc,&xy, CreateSolidBrush( RGB(16,16,16) ));
			if(i==6)	FillRect(hdc,&xy, CreateSolidBrush( RGB(0xbf,0xbf,0xbf) ));
		}
		xy.bottom = rt.bottom;
		xy.top	= rt.bottom - ((rt.bottom /12)*3);
		xy1.bottom = rt.bottom;
		xy1.top	= rt.bottom - ((rt.bottom /12)*3);
		for(i=0;i<6;i++) {
			xy.right = (rt.right /6)*(i+1);
			xy.left  = (rt.right /6)*i;
			if(i==0)	FillRect(hdc,&xy, CreateSolidBrush( RGB(0,0x1d,0x42) ));
			if(i==1)	FillRect(hdc,&xy, CreateSolidBrush( RGB(0xff,0xff,0xff) ));
			if(i==2)	FillRect(hdc,&xy, CreateSolidBrush( RGB(44,0,92) ));
			if(i==3)	FillRect(hdc,&xy, CreateSolidBrush( RGB(16,16,16) ));
			if(i==4)	{
				for(j=0;j<3;j++) {
					xy1.right = xy.left+(((xy.right-xy.left) /3)*(j+1))+2;
					xy1.left  = xy.left+(((xy.right-xy.left) /3)*j);
					if(j==0) FillRect(hdc,&xy1, CreateSolidBrush( RGB(7,7,7) ));
					if(j==1) FillRect(hdc,&xy1, CreateSolidBrush( RGB(16,16,16) ));
					if(j==2) FillRect(hdc,&xy1, CreateSolidBrush( RGB(24,24,24) ));
				}
			}
			if(i==5)	FillRect(hdc,&xy, CreateSolidBrush( RGB(16,16,16) ));
		}

		break;
	case 26:
		FillRect(hdc,&rt, CreateSolidBrush(RGB(0,0,0)));
		//xy.bottom = rt.bottom;
		//xy.top	= rt.top;
		for(i=0;i<(ix/2);i++)
		{
			xy.right=(rt.right /ix)*(2*i+2);
			xy.left=(rt.right /ix)*(2*i+1);
			for(j=0;j<((iy/2)+(iy%2));j++)
			{
				xy.top = (rt.bottom /iy)*(2*j);
				xy.bottom = (rt.bottom /iy)*(2*j+1);
				FillRect(hdc,&xy, CreateSolidBrush(RGB(0xff,0xff,0xff)));
			}
		}
		for(i=0;i<((ix/2)+(ix%2));i++)
		{
			xy.right=(rt.right /ix)*(2*i+1);
			xy.left=(rt.right /ix)*(2*i);
			for(j=0;j<(iy/2);j++)
			{
				xy.top = (rt.bottom /iy)*(2*j+1);
				xy.bottom = (rt.bottom /iy)*(2*j+2);
				FillRect(hdc,&xy, CreateSolidBrush(RGB(0xff,0xff,0xff)));
			}
		}
		break;
	case 27:
		FillRect(hdc,&rt, CreateSolidBrush(RGB(0xff,0xff,0xff)));
		for(i=0;i<(ix/2);i++)
		{
			xy.right=(rt.right /ix)*(2*i+2);
			xy.left=(rt.right /ix)*(2*i+1);
			for(j=0;j<((iy/2)+(iy%2));j++)
			{
				xy.top = (rt.bottom /iy)*(2*j);
				xy.bottom = (rt.bottom /iy)*(2*j+1);
				FillRect(hdc,&xy, CreateSolidBrush(RGB(0,0,0)));
			}
		}
		for(i=0;i<((ix/2)+(ix%2));i++)
		{
			xy.right=(rt.right /ix)*(2*i+1);
			xy.left=(rt.right /ix)*(2*i);
			for(j=0;j<(iy/2);j++)
			{
				xy.top = (rt.bottom /iy)*(2*j+1);
				xy.bottom = (rt.bottom /iy)*(2*j+2);
				FillRect(hdc,&xy, CreateSolidBrush(RGB(0,0,0)));
			}
		}
		break;
	default:
		break;
	}

	
	DeleteObject(hPenWhite);
	DeleteObject(hPenRed);
	DeleteObject(hPenGreen);
	DeleteObject(hPenBlue);
	DeleteObject(hPenBlack);

	ReleaseDC(hWnd,hdc);
	
}

bool CALLBACK IsDeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, 
                                  D3DFORMAT BackBufferFormat, bool bWindowed )
{
    // Skip backbuffer formats that don't support alpha blending
    IDirect3D9* pD3D = DXUTGetD3DObject(); 
    if( FAILED( pD3D->CheckDeviceFormat( pCaps->AdapterOrdinal, pCaps->DeviceType,
                    AdapterFormat, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING, 
                    D3DRTYPE_TEXTURE, BackBufferFormat ) ) )
        return false;

    return true;
}



void CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, const D3DCAPS9* pCaps )
{
    // If device doesn't support HW T&L or doesn't support 1.1 vertex shaders in HW 
    // then switch to SWVP.
    if( (pCaps->DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 ||
         pCaps->VertexShaderVersion < D3DVS_VERSION(1,1) )
    {
        pDeviceSettings->BehaviorFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
    }
    else
    {
        pDeviceSettings->BehaviorFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING;
    }

    // This application is designed to work on a pure device by not using 
    // IDirect3D9::Get*() methods, so create a pure device if supported and using HWVP.
    if ((pCaps->DevCaps & D3DDEVCAPS_PUREDEVICE) != 0 && 
        (pDeviceSettings->BehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING) != 0 )
        pDeviceSettings->BehaviorFlags |= D3DCREATE_PUREDEVICE;

    // Debugging vertex shaders requires either REF or software vertex processing 
    // and debugging pixel shaders requires REF.  
//#ifdef DEBUG_VS
//    if( pDeviceSettings->DeviceType != D3DDEVTYPE_REF )
//    {
//        pDeviceSettings->BehaviorFlags &= ~D3DCREATE_HARDWARE_VERTEXPROCESSING;
//        pDeviceSettings->BehaviorFlags &= ~D3DCREATE_PUREDEVICE;
//        pDeviceSettings->BehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
//    }
//#endif
//#ifdef DEBUG_PS
//    pDeviceSettings->DeviceType = D3DDEVTYPE_REF;
//#endif
}



HRESULT CALLBACK OnCreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc )
{
    HRESULT hr;

    // Initialize the font
    V_RETURN( D3DXCreateFont( pd3dDevice, 15, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, 
                         OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, 
                         L"Arial", &g_pFont ) );

    DWORD dwShaderFlags = 0;
    //#ifdef DEBUG_VS
    //    dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
    //#endif
    //#ifdef DEBUG_PS
    //    dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
    //#endif

    //// Read the D3DX effect file
    WCHAR str[MAX_PATH];
    V_RETURN( DXUTFindDXSDKMediaFileCch( str, MAX_PATH, L"Video-diags.fx" ) );

    // If this fails, there should be debug output as to 
    // they the .fx file failed to compile
    V_RETURN( D3DXCreateEffectFromFile( pd3dDevice, str, NULL, NULL, dwShaderFlags, 
                                        NULL, &g_pEffect, NULL ) );

    // Setup the camera's view parameters
    D3DXVECTOR3 vecEye(0.0f, 0.0f, -5.0f);
    D3DXVECTOR3 vecAt (0.0f, 0.0f, -0.0f);
    g_Camera.SetViewParams( &vecEye, &vecAt );

	// Create the vertex buffer用來開啟一個Vertex Buffer,並設定其相關的值
	for(int i=0;i<6;i++) {
    V_RETURN( pd3dDevice->CreateVertexBuffer( 4*sizeof(CUSTOMVERTEX),
                                                  0, D3DFVF_CUSTOMVERTEX,
                                                  D3DPOOL_MANAGED, &g_pVB[i], NULL ) );
	}

    // Fill the vertex buffer with 2 triangles
    CUSTOMVERTEX* pVertices;		//宣告一個型態為CUSTOMVERTEX的pointer變數,以方便填入相關的頂點資料

    V_RETURN( g_pVB[0]->Lock( 0, 0, (VOID**)&pVertices, 0 ) );		//必須先將這塊buffer鎖住才方便將資料填入
        
    // Front triangle(頂點順序為逆時針方向)
    pVertices[0].position = D3DXVECTOR3( -1.0f,  1.0f,  1.0f );	
    pVertices[0].normal   = D3DXVECTOR3(  0.0f,  0.0f,  1.0f );	
	pVertices[0].tu		  = 0;
	pVertices[0].tv		  = 0;
    pVertices[1].position = D3DXVECTOR3( -1.0f, -1.0f,  1.0f );	
    pVertices[1].normal   = D3DXVECTOR3(  0.0f,  0.0f,  1.0f );	
	pVertices[1].tu		  = 0;
	pVertices[1].tv		  = 1;
    pVertices[2].position = D3DXVECTOR3(  1.0f, -1.0f,  1.0f );	
    pVertices[2].normal   = D3DXVECTOR3(  0.0f,  0.0f,  1.0f );	
	pVertices[2].tu		  = 1;
	pVertices[2].tv		  = 1;
    pVertices[3].position = D3DXVECTOR3(  1.0f,  1.0f,  1.0f );	
    pVertices[3].normal   = D3DXVECTOR3(  0.0f,  0.0f,  1.0f );	
	pVertices[3].tu		  = 1;
	pVertices[3].tv		  = 0;

	g_pVB[0]->Unlock();	//填寫完相關頂點資料後,記得將此塊buffer解除鎖定,交還給系統去管理
//=======================================================================================================================
    V_RETURN( g_pVB[1]->Lock( 0, 0, (VOID**)&pVertices, 0 ) );		//必須先將這塊buffer鎖住才方便將資料填入
        
    // Front triangle(頂點順序為逆時針方向)
    pVertices[0].position = D3DXVECTOR3(  1.0f,  1.0f, -1.0f );	
    pVertices[0].normal   = D3DXVECTOR3(  0.0f,  0.0f, -1.0f );	
	pVertices[0].tu		  = 0;
	pVertices[0].tv		  = 0;
    pVertices[1].position = D3DXVECTOR3(  1.0f, -1.0f, -1.0f );	
    pVertices[1].normal   = D3DXVECTOR3(  0.0f,  0.0f, -1.0f );	
	pVertices[1].tu		  = 0;
	pVertices[1].tv		  = 1;
    pVertices[2].position = D3DXVECTOR3( -1.0f, -1.0f, -1.0f );	
    pVertices[2].normal   = D3DXVECTOR3(  0.0f,  0.0f, -1.0f );	
	pVertices[2].tu		  = 1;
	pVertices[2].tv		  = 1;
    pVertices[3].position = D3DXVECTOR3( -1.0f,  1.0f, -1.0f );	
    pVertices[3].normal   = D3DXVECTOR3(  0.0f,  0.0f, -1.0f );	
	pVertices[3].tu		  = 1;
	pVertices[3].tv		  = 0;

	g_pVB[1]->Unlock();	//填寫完相關頂點資料後,記得將此塊buffer解除鎖定,交還給系統去管理
//=======================================================================================================================
    V_RETURN( g_pVB[2]->Lock( 0, 0, (VOID**)&pVertices, 0 ) );		//必須先將這塊buffer鎖住才方便將資料填入
        
    // Front triangle(頂點順序為逆時針方向)
    pVertices[0].position = D3DXVECTOR3( -1.0f,  1.0f, -1.0f );	
    pVertices[0].normal   = D3DXVECTOR3( -1.0f,  0.0f,  0.0f );	
	pVertices[0].tu		  = 0;
	pVertices[0].tv		  = 0;
    pVertices[1].position = D3DXVECTOR3( -1.0f, -1.0f, -1.0f );	
    pVertices[1].normal   = D3DXVECTOR3( -1.0f,  0.0f,  0.0f );	
	pVertices[1].tu		  = 0;
	pVertices[1].tv		  = 1;
    pVertices[2].position = D3DXVECTOR3( -1.0f, -1.0f,  1.0f );	
    pVertices[2].normal   = D3DXVECTOR3( -1.0f,  0.0f,  0.0f );	
	pVertices[2].tu		  = 1;
	pVertices[2].tv		  = 1;
    pVertices[3].position = D3DXVECTOR3( -1.0f,  1.0f,  1.0f );	
    pVertices[3].normal   = D3DXVECTOR3( -1.0f,  0.0f,  0.0f );	
	pVertices[3].tu		  = 1;
	pVertices[3].tv		  = 0;

	g_pVB[2]->Unlock();	//填寫完相關頂點資料後,記得將此塊buffer解除鎖定,交還給系統去管理
//=======================================================================================================================
    V_RETURN( g_pVB[3]->Lock( 0, 0, (VOID**)&pVertices, 0 ) );		//必須先將這塊buffer鎖住才方便將資料填入
        
    // Front triangle(頂點順序為逆時針方向)
    pVertices[0].position = D3DXVECTOR3(  1.0f,  1.0f,  1.0f );	
    pVertices[0].normal   = D3DXVECTOR3(  1.0f,  0.0f,  0.0f );	
	pVertices[0].tu		  = 0;
	pVertices[0].tv		  = 0;
    pVertices[1].position = D3DXVECTOR3(  1.0f, -1.0f,  1.0f );	
    pVertices[1].normal   = D3DXVECTOR3(  1.0f,  0.0f,  0.0f );	
	pVertices[1].tu		  = 0;
	pVertices[1].tv		  = 1;
    pVertices[2].position = D3DXVECTOR3(  1.0f, -1.0f, -1.0f );	
    pVertices[2].normal   = D3DXVECTOR3(  1.0f,  0.0f,  0.0f );	
	pVertices[2].tu		  = 1;
	pVertices[2].tv		  = 1;
    pVertices[3].position = D3DXVECTOR3(  1.0f,  1.0f, -1.0f );	
    pVertices[3].normal   = D3DXVECTOR3(  1.0f,  0.0f,  0.0f );	
	pVertices[3].tu		  = 1;
	pVertices[3].tv		  = 0;

	g_pVB[3]->Unlock();	//填寫完相關頂點資料後,記得將此塊buffer解除鎖定,交還給系統去管理
//=======================================================================================================================
    V_RETURN( g_pVB[4]->Lock( 0, 0, (VOID**)&pVertices, 0 ) );		//必須先將這塊buffer鎖住才方便將資料填入
        
    // Front triangle(頂點順序為逆時針方向)
    pVertices[0].position = D3DXVECTOR3( -1.0f,  1.0f, -1.0f );	
    pVertices[0].normal   = D3DXVECTOR3(  0.0f,  1.0f,  0.0f );	
	pVertices[0].tu		  = 0;
	pVertices[0].tv		  = 0;
    pVertices[1].position = D3DXVECTOR3( -1.0f,  1.0f,  1.0f );	
    pVertices[1].normal   = D3DXVECTOR3(  0.0f,  1.0f,  0.0f );	
	pVertices[1].tu		  = 0;
	pVertices[1].tv		  = 1;
    pVertices[2].position = D3DXVECTOR3(  1.0f,  1.0f,  1.0f );	
    pVertices[2].normal   = D3DXVECTOR3(  0.0f,  1.0f,  0.0f );	
	pVertices[2].tu		  = 1;
	pVertices[2].tv		  = 1;
    pVertices[3].position = D3DXVECTOR3(  1.0f,  1.0f, -1.0f );	
    pVertices[3].normal   = D3DXVECTOR3(  0.0f,  1.0f,  0.0f );	
	pVertices[3].tu		  = 1;
	pVertices[3].tv		  = 0;

	g_pVB[4]->Unlock();	//填寫完相關頂點資料後,記得將此塊buffer解除鎖定,交還給系統去管理
//=======================================================================================================================
    V_RETURN( g_pVB[5]->Lock( 0, 0, (VOID**)&pVertices, 0 ) );		//必須先將這塊buffer鎖住才方便將資料填入
        
    // Front triangle(頂點順序為逆時針方向)
    pVertices[0].position = D3DXVECTOR3( -1.0f, -1.0f,  1.0f );	
    pVertices[0].normal   = D3DXVECTOR3(  0.0f, -1.0f,  0.0f );	
	pVertices[0].tu		  = 0;
	pVertices[0].tv		  = 0;
    pVertices[1].position = D3DXVECTOR3( -1.0f, -1.0f, -1.0f );	
    pVertices[1].normal   = D3DXVECTOR3(  0.0f, -1.0f,  0.0f );	
	pVertices[1].tu		  = 0;
	pVertices[1].tv		  = 1;
    pVertices[2].position = D3DXVECTOR3(  1.0f, -1.0f, -1.0f );	
    pVertices[2].normal   = D3DXVECTOR3(  0.0f, -1.0f,  0.0f );	
	pVertices[2].tu		  = 1;
	pVertices[2].tv		  = 1;
    pVertices[3].position = D3DXVECTOR3(  1.0f, -1.0f,  1.0f );	
    pVertices[3].normal   = D3DXVECTOR3(  0.0f, -1.0f,  0.0f );	
	pVertices[3].tu		  = 1;
	pVertices[3].tv		  = 0;

	g_pVB[5]->Unlock();	//填寫完相關頂點資料後,記得將此塊buffer解除鎖定,交還給系統去管理

	V_RETURN(pd3dDevice->CreateIndexBuffer( 6*sizeof(WORD),0,D3DFMT_INDEX16,D3DPOOL_MANAGED,&g_pIB,NULL));

	WORD*	pIndices;

	V_RETURN( g_pIB->Lock(0,0,(VOID**)&pIndices,0));

	pIndices[0]	=	0;
	pIndices[1]	=	1;
	pIndices[2]	=	2;
	pIndices[3]	=	0;
	pIndices[4]	=	2;
	pIndices[5]	=	3;

    g_pIB->Unlock();	//填寫完相關頂點資料後,記得將此塊buffer解除鎖定,交還給系統去管理

	for(int i=0;i<6;i++) {		
		V_RETURN(D3DXCreateTextureFromFile(pd3dDevice,szPictureFile,&g_pTexture[i]));
	}
	D3DXCreateMatrixStack(0, &g_pWorldMat);	


    return S_OK;
}


//--------------------------------------------------------------------------------------
// This function loads the mesh and ensures the mesh has normals; it also optimizes the 
// mesh for the graphics card's vertex cache, which improves performance by organizing 
// the internal triangle list for less cache misses.
//--------------------------------------------------------------------------------------
HRESULT LoadMesh( IDirect3DDevice9* pd3dDevice, WCHAR* strFileName, ID3DXMesh** ppMesh )
{
    ID3DXMesh* pMesh = NULL;
    WCHAR str[MAX_PATH];
    HRESULT hr;

    V_RETURN( DXUTFindDXSDKMediaFileCch( str, MAX_PATH, strFileName ) );

    V_RETURN( D3DXLoadMeshFromX(str, D3DXMESH_MANAGED, pd3dDevice, NULL, NULL, NULL, NULL, &pMesh) );

    DWORD *rgdwAdjacency = NULL;

    // Make sure there are normals which are required for lighting
    if( !(pMesh->GetFVF() & D3DFVF_NORMAL) )
    {
        ID3DXMesh* pTempMesh;
        V( pMesh->CloneMeshFVF( pMesh->GetOptions(), 
                                  pMesh->GetFVF() | D3DFVF_NORMAL, 
                                  pd3dDevice, &pTempMesh ) );
        V( D3DXComputeNormals( pTempMesh, NULL ) );

        SAFE_RELEASE( pMesh );
        pMesh = pTempMesh;
    }

    rgdwAdjacency = new DWORD[pMesh->GetNumFaces() * 3];
    if( rgdwAdjacency == NULL )
        return E_OUTOFMEMORY;
    V( pMesh->ConvertPointRepsToAdjacency(NULL, rgdwAdjacency) );
    V( pMesh->OptimizeInplace(D3DXMESHOPT_VERTEXCACHE, rgdwAdjacency, NULL, NULL, NULL) );
    delete []rgdwAdjacency;

    *ppMesh = pMesh;

    return S_OK;
}


HRESULT CALLBACK OnResetDevice( IDirect3DDevice9* pd3dDevice, 
                                const D3DSURFACE_DESC* pBackBufferSurfaceDesc )
{
    HRESULT hr;

    if( g_pFont )
        V_RETURN( g_pFont->OnResetDevice() );
    if( g_pEffect )
        V_RETURN( g_pEffect->OnResetDevice() );

    // Create a sprite to help batch calls when drawing many lines of text
    V_RETURN( D3DXCreateSprite( pd3dDevice, &g_pTextSprite ) );

    // Setup the camera's projection parameters
    float fAspectRatio = pBackBufferSurfaceDesc->Width / (FLOAT)pBackBufferSurfaceDesc->Height;
    g_Camera.SetProjParams( D3DX_PI/4, fAspectRatio, 0.1f, 1000.0f );
    g_Camera.SetWindow( pBackBufferSurfaceDesc->Width, pBackBufferSurfaceDesc->Height );

    g_HUD.SetLocation( pBackBufferSurfaceDesc->Width-170, 0 );
    g_HUD.SetSize( 170, 170 );
    g_SampleUI.SetLocation( pBackBufferSurfaceDesc->Width-170, pBackBufferSurfaceDesc->Height-350 );
    g_SampleUI.SetSize( 170, 300 );

	// Setup a material設定場景內的Material值
    D3DMATERIAL9 mtrl;
	ZeroMemory( &mtrl, sizeof(D3DMATERIAL9) );
    mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
    mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
    mtrl.Diffuse.b = mtrl.Ambient.b = 1.0f;
    mtrl.Diffuse.a = mtrl.Ambient.a = 0.0f;
    pd3dDevice->SetMaterial( &mtrl );

    // Set up the textures

	pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
    pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
    pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

     // Set miscellaneous render states設定場景內的著色狀態
    pd3dDevice->SetRenderState( D3DRS_DITHERENABLE,   FALSE );	//是否需要啟動顏色補差法來著色
    pd3dDevice->SetRenderState( D3DRS_SPECULARENABLE, FALSE );	//是否開啟Specular的光源效果,也就是當物體被光源直射時,是否產生反射的光亮效果
    pd3dDevice->SetRenderState( D3DRS_ZENABLE,        TRUE );		//是否啟動頂點座標深度值的判斷功能
    pd3dDevice->SetRenderState( D3DRS_AMBIENT,        0x000F0F0F );	//設定環境光源的顏色值

    // Set the world matrix設定World Matrix及初始化
    D3DXMATRIX matIdentity;
    D3DXMatrixIdentity( &matIdentity );
    pd3dDevice->SetTransform( D3DTS_WORLD,  &matIdentity );

    D3DXMATRIX matView;
    D3DXVECTOR3 vFromPt   = D3DXVECTOR3( 0.0f, 0.0f, 5.0f );
    D3DXVECTOR3 vLookatPt = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec    = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
    D3DXMatrixLookAtRH( &matView, &vFromPt, &vLookatPt, &vUpVec );
    pd3dDevice->SetTransform( D3DTS_VIEW, &matView );

    // Set the projection matrix設定投影的相關資訊,以決定觀景窗的視野範圍
    D3DXMATRIX matProj;
    FLOAT fAspect = ((FLOAT)pBackBufferSurfaceDesc->Width) / pBackBufferSurfaceDesc->Height;
    D3DXMatrixPerspectiveFovRH( &matProj, D3DX_PI/4, fAspect, 1.0f, 100.0f );
    pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );

    // Set up lighting states
    D3DLIGHT9 light;
	D3DXVECTOR3 vecLightDirUnnormalized(-1.0f, -1.0f, -2.0f);
    ZeroMemory( &light, sizeof(D3DLIGHT9) );
    light.Type        = D3DLIGHT_DIRECTIONAL;
    light.Diffuse.r   = 1.0f;
    light.Diffuse.g   = 1.0f;
    light.Diffuse.b   = 1.0f;
    D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecLightDirUnnormalized );
    pd3dDevice->SetLight( 0, &light );
    pd3dDevice->LightEnable( 0, TRUE );
    pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
    
	pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);	//剔除不計算順時針方向的面


    return S_OK;
}


void CALLBACK OnFrameMove( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime )
{
    // Update the camera's position based on user input 
    g_Camera.FrameMove( fElapsedTime );

	// Update user input state
    //UpdateInput( &g_UserInput );

    // Update the world state according to user input
    D3DXMATRIX matWorld;
    D3DXMATRIX matRotY;
    D3DXMATRIX matRotX;

    //if( g_UserInput.bRotateLeft && !g_UserInput.bRotateRight )
    //    g_fWorldRotY += fElapsedTime;
    //else if( g_UserInput.bRotateRight && !g_UserInput.bRotateLeft )
    //    g_fWorldRotY -= fElapsedTime;

    //if( g_UserInput.bRotateUp && !g_UserInput.bRotateDown )
    //    g_fWorldRotX += fElapsedTime;
    //else if( g_UserInput.bRotateDown && !g_UserInput.bRotateUp )
    //    g_fWorldRotX -= fElapsedTime;

    D3DXMatrixRotationX( &matRotX, g_fWorldRotX );
    D3DXMatrixRotationY( &matRotY, g_fWorldRotY );

    D3DXMatrixMultiply( &matWorld, &matRotX, &matRotY );
	g_pWorldMat->LoadIdentity();
	g_pWorldMat->RotateYawPitchRoll(g_fWorldRotY += fElapsedTime, g_fWorldRotX += fElapsedTime,0);
    pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
	//pd3dDevice->SetTransform( D3DTS_WORLD, g_pWorldMat->GetTop() );
}

void CALLBACK OnFrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime )
{
    HRESULT hr;
    D3DXMATRIXA16 mWorld;
    D3DXMATRIXA16 mView;
    D3DXMATRIXA16 mProj;
    D3DXMATRIXA16 mWorldViewProjection;
    
    // Clear the render target and the zbuffer 清除需要使用的記憶體,填上初始值
//    V( pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 45, 50, 170), 1.0f, 0) );
    V( pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, iRed, iGreen, iBlue), 1.0f, 0) );

    // Render the scene
    if( SUCCEEDED( pd3dDevice->BeginScene() ) )	//讓D3D的系統設定一些著色前的初始工作
    {
        // Get the projection & view matrix from the camera class
        mWorld = *g_Camera.GetWorldMatrix();
        mProj = *g_Camera.GetProjMatrix();
        mView = *g_Camera.GetViewMatrix();

        mWorldViewProjection = mWorld * mView * mProj;

        // Update the effect's variables.  Instead of using strings, it would 
        // be more efficient to cache a handle to the parameter by calling 
        // ID3DXEffect::GetParameterByName
        V( g_pEffect->SetMatrix( "g_mWorldViewProjection", &mWorldViewProjection ) );
        V( g_pEffect->SetMatrix( "g_mWorld", &mWorld ) );
        V( g_pEffect->SetFloat( "g_fTime", (float)fTime ) );

        DXUT_BeginPerfEvent( DXUT_PERFEVENTCOLOR, L"HUD / Stats" ); // These events are to help PIX identify what the code is doing
        RenderText();			//輸出一些訊息到3D畫面上做註解
        V( g_HUD.OnRender( fElapsedTime ) );
        V( g_SampleUI.OnRender( fElapsedTime ) );
        DXUT_EndPerfEvent();

		// Render the vertex buffer contents
        pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );							//告訴D3D系統我們的頂點資料結構(Vertex Format)裡包含了哪些資料項目
		pd3dDevice->SetIndices( g_pIB );
		for(int i=0;i<6;i++)	{ 
			pd3dDevice->SetStreamSource( 0, g_pVB[i], 0, sizeof(CUSTOMVERTEX) );	//將Vertex Buffer的資料送進資料流處理
			pd3dDevice->SetTexture(0, g_pTexture[i]);
			pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2 );				//告訴系統，我們所送進去的這些頂點是要以怎麼樣的幾何型態來呈現
		}

        V( pd3dDevice->EndScene() );										//完成著色工作後再Restore回一些設定值
    }
}


void RenderText()
{
	LPCWSTR lpFrameStatus;
    const	D3DSURFACE_DESC* pd3dsdBackBuffer = DXUTGetBackBufferSurfaceDesc();
    CDXUTTextHelper txtHelper( g_pFont, g_pTextSprite, 15 );

    // Output statistics
    txtHelper.Begin();
    txtHelper.SetInsertionPos( 5, 5 );
    txtHelper.SetForegroundColor( D3DXCOLOR( 1.0f, 1.0f, 0.0f, 1.0f ) );
    txtHelper.DrawTextLine( DXUTGetFrameStats() );
    txtHelper.DrawTextLine( DXUTGetDeviceStats() );

    txtHelper.SetForegroundColor( D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    lpFrameStatus=DXUTGetFrameStats();
	swscanf(lpFrameStatus,L"%8s",Temp);
	dFps=_wtof(Temp);

	if(blSetTimer==TRUE) {
		wsprintf(Tmp,L"Test Timer: %02d",iTestTimer-nTimer);
		txtHelper.DrawTextLine(Tmp);
	}
    
    // Draw help
    if( g_bShowHelp )
    {
        txtHelper.SetInsertionPos( 10, pd3dsdBackBuffer->Height-15*6 );
        txtHelper.SetForegroundColor( D3DXCOLOR( 1.0f, 0.75f, 0.0f, 1.0f ) );
        txtHelper.DrawTextLine( L"Controls (F1 to hide):" );

        txtHelper.SetInsertionPos( 40, pd3dsdBackBuffer->Height-15*5 );
        txtHelper.DrawTextLine( L"Blah: X\n"
                                L"Quit: ESC" );
    }
    else
    {
        txtHelper.SetInsertionPos( 10, pd3dsdBackBuffer->Height-15*2 );
        txtHelper.SetForegroundColor( D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
        //txtHelper.DrawTextLine( L"Press F1 for help" );
    }
    txtHelper.End();
}

//void UpdateInput( UserInput* pUserInput )
//{
//    pUserInput->bRotateUp    = (GetAsyncKeyState( VK_UP )    & 0x8000) == 0x8000;
//    pUserInput->bRotateDown  = (GetAsyncKeyState( VK_DOWN )  & 0x8000) == 0x8000;
//    pUserInput->bRotateLeft  = (GetAsyncKeyState( VK_LEFT )  & 0x8000) == 0x8000;
//    pUserInput->bRotateRight = (GetAsyncKeyState( VK_RIGHT ) & 0x8000) == 0x8000;
//}

LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing )
{

	switch (uMsg) 
	{
	case WM_CREATE:
		SetTimer(hWnd, IDT_TIMER1, 1000, NULL);
		/*
		if(blSaveFile) {
			hFile = CreateFile(szLogFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
             FILE_ATTRIBUTE_NORMAL, NULL);   
			//if (hFile == INVALID_HANDLE_VALUE) {
			//	ErrorHandler("Could not open file.");  
			//}
		}
		*/
		break;

	case WM_TIMER:

		if(wParam == IDT_TIMER1) {
			nTimer++;
			if(nTimer > iTestTimer)	{
				iReturnCode=0;
				DestroyWindow(hWnd);
			}

			if(blSaveFile) {
				LPCWSTR lpFrameStatus;
				lpFrameStatus=DXUTGetFrameStats();
				swscanf(lpFrameStatus,L"%8s",Temp);
				dFps=_wtof(Temp);
				_gcvt(dFps,iDigits,szStr);
				WriteFile(hFile,szStr,strlen(szStr),&dwAccBytes,NULL);
				WriteFile(hFile,"\n",1,&dwAccBytes,NULL);
			}

			if(blSetFPSMax || blSetFPSMin) {
				if(!blSetFPSMax) dFmax = dFps; 
				if(!blSetFPSMin) dFmin = dFps; 

				if((dFps < dFmin) || (dFps > dFmax)) {
					iRetry++;
					if(iRetry>3) {
						iReturnCode=255;
						//SendMessage(hWnd,WM_CLOSE,0,0);
					    DestroyWindow(hWnd);
					}
				}else iRetry = 0 ;
			}
			
		}
		break;
	case WM_DESTROY:
		KillTimer(hWnd, IDT_TIMER1);
		if(blSaveFile) {
			CloseHandle(hFile);
		}
		PostQuitMessage(iReturnCode);
		break;
	}
    // Give the dialogs a chance to handle the message first
    *pbNoFurtherProcessing = g_HUD.MsgProc( hWnd, uMsg, wParam, lParam );
    if( *pbNoFurtherProcessing )
        return 0;
    *pbNoFurtherProcessing = g_SampleUI.MsgProc( hWnd, uMsg, wParam, lParam );
    if( *pbNoFurtherProcessing )
        return 0;

    // Pass all remaining windows messages to camera so it can respond to user input
    g_Camera.HandleMessages( hWnd, uMsg, wParam, lParam );



    return 0;
}


//void CALLBACK KeyboardProc( UINT nChar, bool bKeyDown, bool bAltDown )
//{
//    if( bKeyDown )
//    {
//        switch( nChar )
//        {
//            case VK_F1: //g_bShowHelp = !g_bShowHelp; 
//				break;
//        }
//    }
//}


//--------------------------------------------------------------------------------------
// Handles the GUI events
//--------------------------------------------------------------------------------------
void CALLBACK OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl )
{
    switch( nControlID )
    {
        case IDC_TOGGLEFULLSCREEN: DXUTToggleFullScreen(); break;
        case IDC_TOGGLEREF:        DXUTToggleREF(); break;
        case IDC_CHANGEDEVICE:     DXUTSetShowSettingsDialog( !DXUTGetShowSettingsDialog() ); break;
    }
}


void CALLBACK OnLostDevice()
{
    if( g_pFont )
        g_pFont->OnLostDevice();
    if( g_pEffect )
        g_pEffect->OnLostDevice();
    SAFE_RELEASE( g_pTextSprite );
}


void CALLBACK OnDestroyDevice()
{
    SAFE_RELEASE( g_pEffect );
    SAFE_RELEASE( g_pFont );

	SAFE_RELEASE( g_pIB );	//釋放掉g_pIB的資源
	for(int i=0;i<6;i++)	{
		SAFE_RELEASE( g_pVB[i] );	//釋放掉g_pVB的資源
		SAFE_RELEASE( g_pTexture[i]);
	}
	SAFE_RELEASE( g_pWorldMat );	//將g_pWorldMat釋放掉


}

void InitApp()
{

	for (int i=0;i<6;i++)	{
		g_pVB[i] = NULL;
		g_pTexture[6] = NULL;
	}


	//ZeroMemory( &g_UserInput, sizeof(g_UserInput) );	
    g_fWorldRotX                = 0.0f;
    g_fWorldRotY                = 0.0f;
}

