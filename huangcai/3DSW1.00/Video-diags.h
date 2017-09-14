#pragma once

#include "resource.h"
#include <time.h>
#include <stdio.h>
//#include "display.h"
//#include "winuser.h"
#define WH_KEYBOARD_LL	13
#define NUMHOOKS	2
#define MaxPattern	23

//#pragma comment (lib,L"d3dx9.lib");
//#pragma comment (lib,L"d3d9.lib");
//#pragma comment (lib,L"dxerr9.lib");
//#pragma comment (lib,L"dxguid.lib");

BOOL	blCheckArgument(int arg_c, TCHAR* arg_v[]);
void	ShowPattern(HWND hWnd,int iPatternNum);
LRESULT CALLBACK	LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam); 

HWND	hwnd;
int		arg_c,iKeyNum,iTestTimer=1000,iTestNo,iLoop=0,iLoopCount=0;
int		iReturnCode=255,iSetDelayTime=1000;
BOOL	blHelpParaOK=FALSE,	blok,blExit=FALSE, blSetFileNameOK=FALSE, blTestAllKeyQuit=FALSE,blSetTimer=FALSE;
BOOL	blSetAutoLoop=FALSE, blSetConfirmCheck=FALSE, blSetSpeciaKey=FALSE,blSetPattern=FALSE,blSetLoop=FALSE, blSetYN = FALSE, blSetK= FALSE, blSpeciaKey=FALSE ; 
BOOL	blPressSpace=FALSE,blAltPress=FALSE,blShiftPress=FALSE,blExitHook=FALSE;
BOOL	blTest3DFunction=FALSE;
RECT	rt;
TCHAR	*arg_v[30],temp[80],szLogFile[80];
WCHAR   Tmp[80],Temp[80];
char    szStr[80];
UINT	nTimer=0,iRetry=0;
double  dFps,dFmax,dFmin;
BOOL	blSetFPSMax=FALSE,blSetFPSMin=FALSE,blSaveFile=FALSE,blRGBTest=FALSE;
HANDLE  hFile;
DWORD	dwAccBytes;
int		iDigits=5,iRed=45,iGreen=50,iBlue=170;
BOOL	blRedKey=FALSE,blGreenKey=FALSE,blBlueKey=FALSE;
int		nTestIndex[3]={0,1,2},iTestIndex=0;
int		nProcedureIndex=0;
BOOL	blRedOK=FALSE,blBlueOK=FALSE,blGreenOK=FALSE,blNext=FALSE;
int     ix=0,iy=0,ibw=0;
BOOL    blx=FALSE,bly=FALSE,blBW=FALSE,blTestCB=FALSE,blversion=FALSE,blvert=FALSE;



WCHAR	wcText[][160]=
{L"Video-diags.EXE <-Sw1> <...> [/Command1] [...] ... <Parameter1> <...> ...",
 L"  /?: This help screen.",
 L"  -d <sec>: set delay time.",
 L"  /T: begin to test .",
 L"    -a : set auto loop. default delay time: 1000 ms.    -loop : set loop. ",
 L"    -p <no>: set pattern number. <no>: 1-25.",
 L"    -s <key>: set special key. default [Alt+Shift] -> exit program.", 
 L"    -yn: Press Y/N to return 0/255.",
 L"    -k : set any key, except [Alt+Shift] and y/n, to show next pattern.",
 L"  /CB:  Show a Checker Board pattern.",
 L"    -bw <n>: set color of the first gird, n=0 color is black, n=1 color is white, default color is black.",
 L"    -y <number>: set rows number.",
 L"    -x <number>: set columns number.",
 L"  /3D: test 3D function.",
 //L"    -red <num>: set background red color.",
 //L"    -green <num>: set background green color.",
 //L"    -blue <num>: set background blue color.",
 L"    -sd : set save fps number is integer.",
 L"    -sf <filename>: set log file name.",
 L"    -fmax <no>: set fps max value.",
 L"    -fmin <no>: set fps min value.",
 L"    -pic <filename>: set picture file.",
 L"  /RGB: Random display Red,Green,Blue screen, press r,b,g key to exit.",
 L"  ReturnCode: OK(0),Error(255).",
};

typedef struct _HOOKDATA 
{ 
    int			nType; 
    HOOKPROC	hKprc; 
    HHOOK		hHook;
	BOOL		blEn;
} HOOKDATA; 
 
HOOKDATA	HookData[NUMHOOKS]; 

//typedef struct {
//    DWORD vkCode;
//    DWORD scanCode;
//    DWORD flags;
//    DWORD time;
//    ULONG_PTR dwExtraInfo;
//} KBDLLHOOKSTRUCT, *PKBDLLHOOKSTRUCT;

int		iTestItemIndex=1,iOldTestItemIndex=0;
DWORD	dwKeepKeyCode;
WORD	wKeyLo,wKeyHi;

struct CUSTOMVERTEX
{
    D3DXVECTOR3 position;       // vertex position定義頂點座標位置的欄位
    D3DXVECTOR3 normal;         // vertex normal定義頂點的法向量
	FLOAT	tu,tv;
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)


// Struct to store the current input state
struct UserInput
{
    // TODO: change as needed
    BOOL bRotateUp;		//記錄上鍵
    BOOL bRotateDown;	//記錄下鍵
    BOOL bRotateLeft;	//記錄左鍵
    BOOL bRotateRight;	//記錄右鍵
};

//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------
ID3DXFont*              g_pFont = NULL;         // Font for drawing text
ID3DXSprite*            g_pTextSprite = NULL;   // Sprite for batching draw text calls
ID3DXEffect*            g_pEffect = NULL;       // D3DX effect interface
CModelViewerCamera      g_Camera;               // A model viewing camera
bool                    g_bShowHelp = false;     // If true, it renders the UI control text
CDXUTDialog             g_HUD;                  // dialog for standard controls
CDXUTDialog             g_SampleUI;             // dialog for sample specific controls

LPDIRECT3DVERTEXBUFFER9 g_pVB[6];               // Vextex buffer
LPDIRECT3DINDEXBUFFER9	g_pIB;                  // Index buffer
FLOAT                   g_fWorldRotX;           // World rotation state X-axis
FLOAT                   g_fWorldRotY;           // World rotation state Y-axis
//UserInput               g_UserInput;            // Struct for storing user input

LPDIRECT3DTEXTURE9		g_pTexture[6];

ID3DXMatrixStack*		g_pWorldMat;			//記錄關於世界座標系的MatrixStack


UINT	TimerCount=0;


//--------------------------------------------------------------------------------------
// UI control IDs
//--------------------------------------------------------------------------------------
#define IDC_TOGGLEFULLSCREEN    1
#define IDC_TOGGLEREF           2
#define IDC_CHANGEDEVICE        3
#define sRevision						"1.01ac"

bool    CALLBACK IsDeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, bool bWindowed );
void    CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, const D3DCAPS9* pCaps );
HRESULT CALLBACK OnCreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc );
HRESULT CALLBACK OnResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc );
void    CALLBACK OnFrameMove( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime );
void    CALLBACK OnFrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime );
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing );
void    CALLBACK KeyboardProc( UINT nChar, bool bKeyDown, bool bAltDown  );
void    CALLBACK OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl );
void    CALLBACK OnLostDevice();
void    CALLBACK OnDestroyDevice();
char    szi[20]={0};


void    InitApp();
HRESULT LoadMesh( IDirect3DDevice9* pd3dDevice, WCHAR* strFileName, ID3DXMesh** ppMesh );
void    RenderText();

//void    UpdateInput( UserInput* pUserInput );
static int __BACKGROUND = 0;
static int __FOREGROUND = 7;
void gotoxy(int x, int y)
{
  COORD c;
 
  c.X = x - 1;
  c.Y = y - 1;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void clrscr ()
{
  DWORD written;
  COORD coord;
 
  coord.X =0;
  coord.Y =0;
  FillConsoleOutputAttribute (GetStdHandle (STD_OUTPUT_HANDLE),__FOREGROUND + (__BACKGROUND << 4), 8000, coord,&written);
  FillConsoleOutputCharacter (GetStdHandle(STD_OUTPUT_HANDLE), ' ',8000, coord, &written);
  gotoxy (1, 1);
}