// include the header file
#include "cmos.h"
//#include "resource.h"
#include <io.h>
#include <fcntl.h>



#define ReadSize		10240

#define _wATFunctionNo	10
#define _wATParaMAX		3
#define _wATStringMAX	8192

// declare the procedure name
void ReadMe(void);
void Logo(void);
void End(int ReturnCode);

BOOL blWork(void);
DWORD dwTransferNowDateTime2GMT(void);
DWORD dwGetFileSize(char *fn);
void DisplayTxtFile(char *filename, int x, int y, BYTE attr); // add at 2000-11-23, KC
void CP(char *fn1, char *fn2);
BOOL blFileCompare(char *fn1, char *fn2, BOOL blignore); // add at 2000-12-28, KC
BOOL blFileCheckSum(char *fn1, WORD wUserCheckSum);
BOOL Process_ini_File(int,int,int,char **,char *);
BOOL Process_ini_File2(int,int,char **);
BOOL CheckChar(char Filename[80],int ReadBit,char ch);
BOOL Transfer_Barcode_Format(char *);
BOOL Set_Barcode_Environment(char DataFilename[80],char iniFilename[80]);
BOOL Transfer_String(char File[50],char str1[50],char str2[50]);
BOOL GetString(char File1[50]);
BOOL Set_Environment_Variable(char str3[80],char EnvirVar[80],char In_File[20]/*,char Out_File[20]*/);
BOOL WlFileIntoCertainPosition(char *fn1, char *fn2, char *fn3, char *place);//add at 2004-03-23, Yushih//StrFuc.cpp
void textattr(int _attr);
void textcolor(int color);
void textbackground(int color);
void gotoxy(int x, int y);
void clrscr();
void printstr(int x, int y, char *s, int type);
void puttext (int left, int top, int right, int bottom, char *str);

char *  __cdecl SmartStrcpy(char *, const char *);
void vExist_EXE(BOOL , char *);
int  iStringSeek(int iCurrentBufPtr,char S1[_wATStringMAX],char S2[_wATStringMAX]);
void vDelay838ns(WORD wInterval);
BOOL blOBWSN(char *fn);
BOOL blCreateRandom(const unsigned int);
int atoh(const char*);
BOOL blCheckLines(const char*);
BOOL blCmpData(char str[20],char file1[20],char file2[20]);
BOOL blCopyData(char sstr[50],char tstr[50],char s_File[20],char t_File[20]);
void PrintCh(int x, int y, char c, BYTE color, int count);
void PrintStr(int x, int y, char *s, int location, BYTE color);
int wherey ();
void Cursor(BOOL type);
BOOL blDisplayBigWord(const char *lpfilename);
BOOL blCopyData(char str4[],char str5[],char s_File[],char t_File[]);
BOOL blTransferHex2Dec(char *file);
BOOL blCheckString(char *szFile, char *szValue);