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

extern void End(int ReturnCode);
extern void gotoxy(int x, int y);
extern void clrscr ();
extern void clreol ();
extern void delline();
extern int _conio_gettext (int left, int top, int right, int bottom,char *str);
extern void puttext (int left, int top, int right, int bottom, char *str);
extern void _setcursortype (int type);
extern void textattr (int _attr);
extern void textbackground (int color);
extern void textcolor (int color);
extern int wherex ();
extern int wherey ();
extern void PrintStr(int x, int y, char *s, int location, BYTE color);
extern void PrintCh(int x, int y, char c, BYTE color, int count);
extern void Cursor(BOOL type);
extern BOOL blDesciption;
extern int NO;

extern Boolean blNoLogo;
extern Boolean blClearScreen;
extern Boolean blParameterOK;
extern Boolean blResult;
extern bool g_blExit;
extern long gUploadspeed;
extern int g_T;
extern char *ip;