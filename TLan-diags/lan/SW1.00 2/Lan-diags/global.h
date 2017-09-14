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

void End(int nReturnCode);
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
BOOL blParameter(char *s);

Boolean blNoLogo = FALSE;
Boolean blClearScreen = TRUE;
Boolean blParameterOK = FALSE; // record the user parameter is proper or not
Boolean blResult = FALSE; // record the test result is OK or ERROR

int nErrorLevel = 255;
CString g_sDescription = "";
CString g_sServiceName = "";
CString g_sMacAddress = "";
CString g_sChkMacAddress = "";
int g_nDevNO = -1;
double g_dSpeed = -1;
long g_lSignalStrength = 1;
int g_nSignalQuality = 0;
int g_nSignalQUpper = 0;
int g_nSignalQLower = 100;