// declare Global variables, always called by main program
// -------------------------------------------------------------------------

obj_Function pega;
obj_CMOS RTC;
//obj_DiagsKey DK;
#define DEFAULT_COLOR 0x0007
Boolean blUseBit=FALSE;
//int StartBit,EndBit;
Boolean blUseAddress=FALSE,blUseStartAddress=FALSE,blUseEndAddress=FALSE;
uLong dwStartAddress=1, dwEndAddress=0xFFFFFFFFl, LL;
Boolean blUseLine=FALSE,blUseStartLine=FALSE,blUseEndLine=FALSE;
uLong dwStartLine=1, dwEndLine=0xFFFFFFFFl;
Boolean blignore=FALSE, blTransfer=FALSE, blLastBit=FALSE, blDivideBy36=FALSE,blL2u=FALSE,blmask=FALSE;
char buf[80],Filename[80],Prmpt[80]="\0";
//char buf1[ReadSize], buf2[ReadSize];
//BYTE buf3[ReadSize];
int  FileNumber,LastBit,imask;
char str2[50];
//char str3[80],EnvirVar[80];
char szStr[1024]="\0";
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
Boolean blSetStr1 = FALSE;      // set string for copy data
Boolean bldiv=FALSE;
Boolean blSetStr2 = FALSE;
Boolean blComma = FALSE;  	// searching string by comma
Boolean blBackSearch =FALSE;    // search back line stop by meeting comma,
unsigned int  nSmsk = 0,   	// begining number of comma
	      nEmsk = 0,   	// ending number of comma
	      nSln = 0,    	// start line
	      nEln = 0,    	// end line
	      nSlctn = 0,  	// start character
	      nElctn = 0,  	// end character
	      nBck = 0;         // searching line stop by meeting comma number
Boolean blDiff = FALSE;
float nDiffValue = 0.0;
uInt nLength = 0;
int idiv=0;
Boolean blRandom = FALSE;

unsigned int nLine = 0;

Boolean blLogo = TRUE;
Boolean blClearScreen = TRUE;
int nErrorLevel = -1;
Boolean blNoDisplay = FALSE;
char Code[64]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D',
		  'E','F','G','H','I','J','K','L','M','N','O','P','Q','R',
		  'S','T','U','V','W','X','Y','Z','a','b','c','d',
		  'e','f','g','h','i','j','k','l','m','n','o','p','q','r',
		  's','t','u','v','w','x','y','z'};