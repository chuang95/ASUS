// declare external variables, same as GLOBAL.H, called by procedure program
// -------------------------------------------------------------------------
extern obj_Function pega;
extern obj_CMOS RTC;
//extern obj_DiagsKey DK;
////extern obj_PCI PCI; //mark by Jackson, 2003/06/12


//extern int StartBit,EndBit;
extern Boolean blUseAddress,blUseStartAddress,blUseEndAddress;
extern uLong dwStartAddress, dwEndAddress, LL;
extern Boolean blUseLine,blUseStartLine,blUseEndLine;
extern uLong dwStartLine, dwEndLine;
extern Boolean blignore, blTransfer, blLastBit, blDivideBy36,blL2u,blmask;
extern char buf[80],Filename[80],Prmpt[80];
//extern char buf1[ReadSize], buf2[ReadSize];
//extern BYTE buf3[ReadSize];
extern int  FileNumber,LastBit,imask;
extern char str2[50];
//extern char str3[80],EnvirVar[80];
extern char szStr[1024];
//start & end mask symbol number
extern unsigned int nSmsk, nEmsk, nSln, nEln, nSlctn, nElctn, nBck;
extern Boolean blComma;  	// searching string by comma symbol
extern Boolean blBackSearch;    // searching string back, stop by meeting indicate number of comma
extern uInt nLength;
extern int idiv;
extern Boolean blRandom;
extern Boolean bldiv;
extern unsigned int nLine;
extern Boolean blLogo;
extern Boolean blClearScreen;
extern int nErrorLevel;
extern Boolean blNoDisplay;

extern Boolean blDiff;
extern float nDiffValue;

extern char Code[36];