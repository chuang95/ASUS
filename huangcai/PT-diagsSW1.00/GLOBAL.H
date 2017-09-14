// declare Global variables, always called by main program
// -------------------------------------------------------------------------
#include "PT-diags.h"
#define SCREEN_TOP 1  
#define SCREEN_LEFT 1
#define SCREEN_BOTTOM 25
#define SCREEN_RIGHT 80
enum Loc
{
	LOC_X,
	LOC_LEFT,
	LOC_MIDDLE,
	LOC_RIGHT	
};

obj_CMOS RTC;

HINSTANCE hDll;
DWORD ( * dwVersionOfTdeIODriver)(...);	
DWORD ( * dwVersionOfObjTdeIo)(...);	

// 這些函數是從 TDEIO.dll 匯入的
// IO Read Function					// IO Write Function
DWORD	( * IOR)(...);				void ( * IOW)(...);		
BYTE	( * bIOR)(...);				void ( * IOWB)(...);		
WORD	( * wIOR)(...);				void ( * IOWW)(...);		
DWORD	( * dwIOR)(...);			void ( * IOWD)(...);		
BYTE	( * bitIOR)(...);			void ( * IOWBit)(...);		

BOOL blUseBit=FALSE;
BOOL blClearScreen = TRUE;
BOOL blSetStr1 = FALSE;      // set string for copy data
BOOL blSetStr2 = FALSE;
//int StartBit,EndBit;
BOOL blUseAddress=FALSE,blUseStartAddress=FALSE,blUseEndAddress=FALSE;
DWORD dwStartAddress=1, dwEndAddress=0xFFFFFFFFl, LL;
BOOL blUseLine=FALSE,blUseStartLine=FALSE,blUseEndLine=FALSE;
DWORD dwStartLine=1, dwEndLine=0xFFFFFFFFl;
BOOL blignore=FALSE, blTransfer=FALSE, blLastBit=FALSE,blNoLogo = FALSE;
char buf[80],Filename[80],Prmpt[80];
char buf1[ReadSize], buf2[ReadSize];
unsigned int  FileNumber, LastBit;
char File[50],str1[50],str2[50];
char str3[80],EnvirVar[80];
BOOL blComma = FALSE;  	// searching string by comma
unsigned int  nSmsk = 0,   	// begining number of comma
						  nEmsk = 0;   	// ending number of comma

BOOL blDiff = FALSE;
BOOL blow=FALSE;
BOOL blRandom = FALSE;
double fDiff = 0.0;
unsigned int nLine = 0;
unsigned int nLength = 10;
int nErrorLevel = 255;
#define DEFAULT_COLOR 0x0007
struct stPCIINFO{
	struct stGETINFO0{
		char sVersion[20];
		char sDate[20];
		char sDescription[100];
		char sModuleType[20];
		char sOther[200];
	}stGetInfo0;
	struct stGETINFO1{
		char sLevel[10];
		char sDescription[100];
		char sMED[1024];
		char sVar[4096];
		char sDEF[10];
		char sThisLvlEnd;
		char sAllLvlEnd;
	}stGetInfo1;
	struct stPROCNAME {
		char sRet[10];
		char sMsg[4096];
		char sEnd;
	}stProcName;
} gstPCIInfo;
