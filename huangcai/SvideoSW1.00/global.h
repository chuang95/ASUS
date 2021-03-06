#define Boolean BOOL

enum Loc
{
	LOC_X,
	LOC_LEFT,
	LOC_MIDDLE,
	LOC_RIGHT	
};

#define SCREEN_TOP 1  
#define SCREEN_LEFT 1
#define SCREEN_BOTTOM 25
#define SCREEN_RIGHT 80

#define DEFAULT_COLOR 0x0007

void End(int ReturnCode);
void gotoxy(int x, int y);
void clrscr ();
void clreol ();
void delline();
int _conio_gettext (int left, int top, int right, int bottom,char *str);
void puttext (int left, int top, int right, int bottom, char *str);
void _setcursortype (int type);
void textattr (int _attr);
void textbackground (int color);
void textcolor (int color);
int wherex ();
int wherey ();
void PrintStr(int x, int y, char *s, int location, BYTE color);
void PrintCh(int x, int y, char c, BYTE color, int count);
void Cursor(BOOL type);
BOOL blDesciption=false;
int NO=0;
LONG64 l64ExecTime = 30;
LONG64 l64Timer = 0;
Boolean blNoLogo = FALSE;
Boolean blClearScreen = TRUE;
Boolean blParameterOK = FALSE; // record the user parameter is proper or not
Boolean blResult = FALSE; // record the test result is OK or ERROR
BOOL blexit=false;
//char DevN[102400]={0};
//char szTem[100];
BOOL blCPUexit = false;
BOOL blMemoryexit = false;
int nErrorLevel = 255;
HWND wndHandle = FindWindow("Shell_TrayWnd", NULL); 


BOOL blParameter(char *s);
LONG64 l64AddTime(DWORD dwSecond, DWORD dwMSecond);
LONG64 l64GetTime();

HWND g_hwnd[4] = {NULL};
