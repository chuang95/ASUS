// declare external variables, same as GLOBAL.H, called by procedure program
// -------------------------------------------------------------------------
#include "PT-diags.h"

extern obj_CMOS RTC;
//extern obj_PCI PCI; //mark by Jackson, 2003/06/12

extern HINSTANCE hDll;
extern DWORD ( * dwVersionOfTdeIODriver)(...);	
extern DWORD ( * dwVersionOfObjTdeIo)(...);	

// 這些函數是從 TDEIO.dll 匯入的
// IO Read Function					// IO Write Function
extern DWORD ( * IOR)(...);			extern void ( * IOW)(...);		
extern BYTE	 ( * bIOR)(...);		extern void ( * IOWB)(...);		
extern WORD	 ( * wIOR)(...);		extern void ( * IOWW)(...);		
extern DWORD ( * dwIOR)(...);		extern void ( * IOWD)(...);		
extern BYTE	 ( * bitIOR)(...);		extern void ( * IOWBit)(...);		

//extern int StartBit,EndBit;
extern BOOL blUseAddress,blUseStartAddress,blUseEndAddress;
extern DWORD dwStartAddress, dwEndAddress, LL;
extern BOOL blUseLine,blUseStartLine,blUseEndLine;
extern DWORD dwStartLine, dwEndLine;
extern BOOL blignore, blTransfer, blLastBit,blNoLogo;
extern char buf[80],Filename[80],Prmpt[80];
extern char buf1[ReadSize], buf2[ReadSize];
extern unsigned int  FileNumber, LastBit;
extern char File[50],str1[50],str2[50];
extern char str3[80],EnvirVar[80];
extern BOOL blComma;  	// searching string by comma
extern unsigned int  nSmsk, nEmsk;   	// begining number of comma &  ending number of comma
extern unsigned int nLine;
extern unsigned int nLength;
extern int nErrorLevel;
extern BOOL blRandom;
extern BOOL blow;
extern struct stPCIINFO{
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
