/*  PegatronTool Utility, Copyright by Pegatron
------------------------------------------------------------------------------
PT-diags.exe_Rev1.00: May. 21, 2009: Craige
1. Add /CFStr <file1> <file2> to read data from file1 and check in file2.
------------------------------------------------------------------------------
Rev1.07: Aug. 21, 2007: Brian
		1. Fixed the /CV 16-based is incorrect with -diff
------------------------------------------------------------------------------
Rev1.06: Aug. 14, 2007: Brian
	  1. Fixed the String Buffer of GetString from 150 to 2048
		2. added -diff parameter with Command /CV, /CV1, /CF & /CF1 for comparing
		   the file in value and user value if it is in difference?
	  3. Modifed -sl -el & -sa -ea can be used with -start_comma -end_comma together.
-----------------------------------------------------------------------------
Rev1.05: Jul. 24, 2007: Brian
    1. Mixed -i , -sl & -el parameters with /C Command.
		2. New-added /CV1 Command for comparing the floating number.
-----------------------------------------------------------------------------
Rev1.04: Jun 27, 2007: Jackson
	  1. Add /CF1 command to compare two file2 for hex data
-----------------------------------------------------------------------------
Rev1.03:May 08, 2007:Brian
    1. Add -start_comma | -end_comma to searching string by comma location
-----------------------------------------------------------------------------
Rev1.02: Apr 22, 2007: Jackson
	  1. Add -LSB parameter to specify last bit data for /GStr, /GStr1
-----------------------------------------------------------------------------
Rev1.01: Oct 23, 2006: Jackson
	  1. Modify /TStr command to cancel string length limitation
	  2. Add /GStr1 command to have change line function
-----------------------------------------------------------------------------
Rev1.00: Oct 11, 2006: Jackson
	     Windows first release same as DOS rev2.11
-----------------------------------------------------------------------------*/
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <process.h>
#include <math.h>
#include "PT-diags.h"
#include "global.h"

void gotoxy(int x, int y);
void clrscr();
#define sProgramDescription "Windows Pegatron Tool"
#define sBuildDate "2009-08-19"
#define sRevision "1.01ab"

void printstr(int x, int y, char *s, int type)
{
  if(type<0) gotoxy(x,y);
  else if(type==0) gotoxy((int)((80-strlen(s))/2),y);
  else gotoxy(80-(int) strlen(s),y);
  cprintf("%s",s);
}


//---------------------------------------------------------------------------
void Logo(void)
{
	if(blNoLogo)
		return;

	if(blClearScreen)
		clrscr();

	PrintStr(0, 1, sProgramDescription, LOC_MIDDLE, DEFAULT_COLOR);
	PrintStr(0, 2, "Copyright by Pegatron, Build Date:" sBuildDate " Rev" sRevision, LOC_MIDDLE, DEFAULT_COLOR);
	PrintStr(0, 2, "Diagnostics ", LOC_RIGHT, 0x08);	
	PrintCh(SCREEN_LEFT, 3, '=', DEFAULT_COLOR, SCREEN_RIGHT);
	return;
}

//--------------------------------------------------------------------------
void ReadMe(void)
{
	int iNextpage=0;
	for(;;)
	{
		if(!blNoLogo)
		Logo();
	else
		clrscr();

	int y = wherey();

	if(!blNoLogo)
		y = 3;

	for(int i = 1; i <=  19; i++)
		PrintCh(40, y + i, '|', 0x08, 1); // middle line
	PrintCh(SCREEN_LEFT, y + 20, '-', 0x08, SCREEN_RIGHT); // bottom line
	PrintCh(40, y + 20, '+', 0x08, 1); // intersection of bottom line and middle line
	gotoxy(SCREEN_LEFT, y + 1);
	//textattr(0x08); 
	 //Basic function
  //_cprintf("- Basic -------------------------------\n\r");
  //textattr(0x07);
  _cprintf("/?: Show usage\n\r");
  _cprintf("  -nl: No display the logo and clear\n\r");
  _cprintf("       screen\n\r");
  _cprintf("  -nc: No clear screen \n\r");
  _cprintf("  -erv <errorlevel>: Return error code \n\r");
  _cprintf("  -cs on|off: Case sensitive on or off,\n\r");
  _cprintf("  default on\n\r");
  _cprintf("/CF <file1> <file2>: Compare <file1>\n\r");
  _cprintf("  (A) and <file2>(B) for Dec|Hex data\n\r");
  _cprintf("/CV <file> <value>: Compare Dec|Hex|\n\r"); 
  _cprintf("  Float value(A) in file with value(B)\n\r");
  _cprintf("  if A > B return code=2\n\r");
  _cprintf("  if A = B return code=1\n\r");
  _cprintf("  if A < B return code=0\n\r");
  _cprintf("  -diff <value>: diff value in value \n\r");
  _cprintf("  (A) and value(B)\n\r");
  _cprintf("  if A-B > diff value return code=2\n\r");
  _cprintf("  if A-B = diff value return code=1\n\r");
  _cprintf("  if A-B < diff value return code=0\n\r");



  //_cprintf("/CF1 <file1> <file2>: Compare <file1>\n\r");
  //_cprintf("  (A) and <file2>(B) for  data\n\r");

  //_cprintf("/CV1 <file> <value>: Compare floating \n\r");
  //_cprintf("  value(A) in file with value(B)\n\r");

    	gotoxy(41, y++);
  textattr(0x07);gotoxy(41, y++);
  _cprintf("/Random <length>: Create Random Hex| \n\r");gotoxy(41, y++);
  _cprintf("  English letter+Dec, default length is\n\r"); gotoxy(41, y++);
  _cprintf("  10 Byte|10 character\n\r"); gotoxy(41, y++);
  _cprintf("  -low: English lower letter default:\n\r"); gotoxy(41, y++);
  _cprintf("  higher letter\n\r"); gotoxy(41, y++);
  _cprintf("  -type <num>: 1.Dec 2.Hex 3.English \n\r"); gotoxy(41, y++);
  _cprintf("  letter 4.English letter+Dec 5.Float\n\r"); gotoxy(41, y++);
  _cprintf("  for /CF, /CV, /Random\n\r"); gotoxy(41, y++);
  _cprintf("/D <file> <x> <y> <attr>: Display txt\n\r"); gotoxy(41, y++);
  _cprintf("  file\n\r");gotoxy(41, y++);
  _cprintf("/S: Scan barcode and save to barcode.dat\n\r"); gotoxy(41, y++); 
  _cprintf("/TStr <file> <s1> <s2>: Replace string \n\r"); gotoxy(41, y++);
  _cprintf("  s1 by s2 for file, save to update.txt\n\r"); gotoxy(41, y++);
  _cprintf("/TBC <file>: Transfer barcode format\n\r"); gotoxy(41, y++);
  _cprintf("/GMT: Transfer now date & time to \n\r"); gotoxy(41, y++);
  _cprintf("  GMT(seconds)\n\r"); gotoxy(41, y++);
  _cprintf("/H2D <file>: Transfer Hex to Dec value\n\r");gotoxy(41, y++);
  _cprintf("/FS <file> <value>: Get the file \n\r"); gotoxy(41, y++);
  _cprintf("  size(A) & compare with value(B)\n"); gotoxy(41, y++);

    PrintStr(1,24,"       Press any key to view next page or press ESC to exit",0,0x07);
    PrintStr(75,24,"1/3",0,0x0D);
	iNextpage=getch();
	 if(iNextpage==0x1B){
      textbackground(0);
      cprintf("\r                                                           ");
	  break;}
	if(iNextpage == 224)
	{
	   getch();
	}

	if(!blNoLogo)
		Logo();
	else
		clrscr();

	y = wherey();

	if(!blNoLogo)
		y = 3;

	for(int i = 1; i <=  19; i++)
		PrintCh(40, y + i, '|', 0x08, 1); // middle line
	PrintCh(SCREEN_LEFT, y + 20, '-', 0x08, SCREEN_RIGHT); // bottom line
	PrintCh(40, y + 20, '+', 0x08, 1); // intersection of bottom line and middle line
	gotoxy(SCREEN_LEFT, y + 1);
  textattr(0x07);
  _cprintf("/ChkChar <file> <bit> <char>: Read a \n\r");
  _cprintf("  data from file and check with char\n\r");
  _cprintf("/ChkStr <file> <string>: Read data from\n\r");
  _cprintf("  file and check with string\n\r");
  _cprintf("/GStr <file>: Get string from file\n\r");
  _cprintf("  -cl: change line\n\r");
  _cprintf("  -LSB <n>: specify last <n> bit data\n\r");
  _cprintf("  for /GStr|/GStr1\n\r");
  _cprintf("  -start_comma | -end_comma <n>: set\n\r"); 
  _cprintf("  the range of searching string by\n\r");
  _cprintf("  comma\n\r");
  _cprintf("/C <file1> <file2>: file1 & file2 \n\r");
  _cprintf("  compare content, default range is 1\n\r");
  _cprintf("  to end\n\r");
  _cprintf("  -in: file2 include file1 for /C\n\r");
  _cprintf("/CSum <file> <checksum>: Calculate the\n\r");
  _cprintf("  checksum of file\n\r");
  _cprintf("  -sl|-el <l>: Set start|end line of\n\r");
  _cprintf("  file for /C, /CSum, /GStr\n\r");
  //_cprintf("/CmpData <file1> <file2>: Check if data\n\r"); 
  //_cprintf("  in file1 is also in file2\n\r");
  //_cprintf("  -str <str>: Get data behind <str>\n\r");
  //_cprintf("/CFStr <file1> <file2>: Read data from\n\r");
  //_cprintf("  file1 and check in file2\n\r");


  	gotoxy(41, y++);
  textattr(0x07);gotoxy(41, y++);
  //_cprintf("  batch & pro files base on N ini \n\r"); gotoxy(41, y++);
  //_cprintf("  files\n\r");gotoxy(41, y++);
  //_cprintf("  -chkbc <N>: Scan barcode N times and\n\r"); gotoxy(41, y++);
  //_cprintf("  compare, N must >= 2\n\r");gotoxy(41, y++);
  //_cprintf("  -del <M>: Delete Mth bit barcode and\n\r"); gotoxy(41, y++);
  //_cprintf("  change 90 code to 80 code\n\r"); gotoxy(41, y++);
  //_cprintf("  -p <string>: Set the prompt string\n\r"); gotoxy(41, y++);
  //_cprintf("/Find <file> <string>: Search string\n\r");  gotoxy(41, y++);
  //_cprintf("  from file\n\r"); gotoxy(41, y++);

  _cprintf("  -sa|-ea <n>: Set start|end byte of \n\r"); gotoxy(41, y++);
  _cprintf("  file for /C, /CSum, /ChkStr,,\n\r"); gotoxy(41, y++);
  _cprintf("  /GStr, /H2D\n\r"); gotoxy(41, y++);
  _cprintf("/Find <file> <string>: Search string\n\r"); gotoxy(41, y++);
  _cprintf("  from file\n\r");  gotoxy(41, y++);

  _cprintf("  -t: Transfer file to normal text\n\r");  gotoxy(41, y++);
  _cprintf("  format for /ChkStr, /Find\n\r"); gotoxy(41, y++);
  _cprintf("/CBC <file1>...<fileN>: Create batch & \n\r");  gotoxy(41, y++);
  _cprintf("  pro file by comparing barcode & ini\n\r"); gotoxy(41, y++);
  _cprintf("  file\n\r"); gotoxy(41, y++);
  _cprintf("/SB <data_file> <ini_file>: Set 90 \n\r"); gotoxy(41, y++);
  _cprintf("  barcode environment variable\n\r"); gotoxy(41, y++);
  _cprintf("/RC <file> <bit>: Return character\n\r");gotoxy(41, y++);
  _cprintf("  (0~9,A~Z) code\n\r");gotoxy(41, y++);
  _cprintf("/SET <file1> <file2>: Set environment\n\r"); gotoxy(41, y++);
  _cprintf("  variable base on file1, then write to\n\r");gotoxy(41, y++);
  //_cprintf("  character, default length is 10\n\r");
  _cprintf("  file2 where file1: input file, file2:\n\r");gotoxy(41, y++);
  _cprintf("  output file\n\r");gotoxy(41, y++);
  _cprintf("  -sstr <str>: Search string\n\r");gotoxy(41, y++);



    PrintStr(1,24,"       Press any key to view next page or press ESC to exit",0,0x07);
    PrintStr(75,24,"2/3",0,0x0D);
	iNextpage=getch();
	 if(iNextpage==0x1B){
      textbackground(0);
      cprintf("\r                                                           ");
	  break;}
	if(iNextpage == 224)
	{
	   getch();
	}

	if(!blNoLogo)
		Logo();
	else
		clrscr();

	y = wherey();

	if(!blNoLogo)
		y = 3;

	for(int i = 1; i <=  19; i++)
		PrintCh(40, y + i, '|', 0x08, 1); // middle line
	PrintCh(SCREEN_LEFT, y + 20, '-', 0x08, SCREEN_RIGHT); // bottom line
	PrintCh(40, y + 20, '+', 0x08, 1); // intersection of bottom line and middle line
	gotoxy(SCREEN_LEFT, y + 1);
  textattr(0x07);


  _cprintf("  -sev <str>: Set environment variable\n\r");
  _cprintf("  base on string\n\r");
  _cprintf("/TIB <F1.BIN> <F2.TXT> <F.BIN> <place>:\n\r");
  _cprintf("  Write F2.TXT into certain position in\n\r"); 
  _cprintf("  F1.BIN, and save as F.BIN\n\r");
  //_cprintf("  \n\r");
  _cprintf("/OBWSN <file>: Check OBW Serial Number\n\r");
  _cprintf("  rule\n\r");
  _cprintf("/CLS <file>: Show each line status in a\n\r"); 
  _cprintf("  file\n\r");
  _cprintf("  -line <n>: Set the estimated number\n\r"); 
  _cprintf("  of line in a file\n\r");
  //_cprintf("/BigWord <file>: Display the Hex or\n\r");
  //_cprintf("  Dec number in file with Big Size\n\r"); 
  _cprintf("/CopyData <file1> <file2>: Copy data \n\r");
  _cprintf("  from file1 to file2\n\r");
  _cprintf("  -str1 <str>: Copy data behind <str>\n\r");
  _cprintf("  -str2 <str>: Paste data behind <str>\n\r");


  	gotoxy(41, y++);
  textattr(0x07);gotoxy(41, y++);


 // _cprintf("/R1|/R2 <fn> <char>: Set environment\n\r"); gotoxy(41, y++); 
  //_cprintf("  variable (for 14 & 15 bit)\n\r"); gotoxy(41, y++);
 // _cprintf("/R3 <fn> <bit> <char>: Set environment\n\r");  gotoxy(41, y++);
  //_cprintf("  variable and file name\n\r"); gotoxy(41, y++);
  //_cprintf("  (for 14,15 bit)\n\r"); gotoxy(41, y++);
 // _cprintf("/R4 <fn1> <char> <fn2>: Set environment\n\r");  gotoxy(41, y++);
 // _cprintf("  variable and file name \n\r"); gotoxy(41, y++);
 // _cprintf("  (for 19 bit)\n\r"); gotoxy(41, y++);
 // _cprintf("/R5|/R6 <fn> <bit1> <bit2> <env_var>:\n\r"); gotoxy(41, y++);
 // _cprintf("  Set environment variable for\n\r"); gotoxy(41, y++);
  //_cprintf("  barcode\n\r");gotoxy(41, y++);
  //_cprintf("/R7 <fn> <bit> <char1> <char2>: Set\n\r"); gotoxy(41, y++);
  //_cprintf("  environment variable and file\n\r"); gotoxy(41, y++);
 // _cprintf("  name\n\r");gotoxy(41, y++);

    PrintStr(1,24,"       Press any key to view 1st page or press ESC to exit",0,0x07);
    PrintStr(75,24,"3/3",0,0x0D);
	iNextpage=getch();
	 if(iNextpage==0x1B){
      textbackground(0);
      cprintf("\r                                                           ");
	  break;}
	if(iNextpage == 224)
	{
	   getch();
	}
	//if(!blNoLogo)
	//	Logo();
	//else
	//	clrscr();

	//y = wherey();

	//if(!blNoLogo)
	//	y = 3;

	//for(int i = 1; i <=  19; i++)
	//	PrintCh(40, y + i, '|', 0x08, 1); // middle line
	//PrintCh(SCREEN_LEFT, y + 20, '-', 0x08, SCREEN_RIGHT); // bottom line
	//PrintCh(40, y + 20, '+', 0x08, 1); // intersection of bottom line and middle line
	//gotoxy(SCREEN_LEFT, y + 1);
 // textattr(0x07);


 // 	gotoxy(41, y++);
	//textattr(0x08);
 //   PrintStr(1,24,"ESC: exit this help... Press any key to next page ...",0,0x07);
 //   PrintStr(75,24,"4/4",0,0x0D);
	//iNextpage=getch();
	// if(iNextpage==0x1B){
 //     textbackground(0);
 //     cprintf("\r                                                           ");
	//  break;}
	//if(iNextpage == 224)
	//{
	//   getch();
	//}
	}
	textattr(0x07);
	gotoxy(SCREEN_LEFT, 24 );
	End(nErrorLevel);
	return;
  //printf("PT-diags.EXE <-Sw1> <...> [/Command1] [...] ... <Parameter1> <...> ... \n");
  //printf("  /?: Show usage.\n\r");
  //printf("    -nl: Do not show Pegatron Logo, for all commands.\n"); 
  //printf("    -erv <errorlevel>: Return error code.\n\r");
  //printf("  /VERSION: Show program version.\n\r");
  //printf("  /FS <file> <value>: Get the file size(A) & compare with value(B)\n");
  //printf("  /GMT: Transfer now date & time to GMT(seconds)\n");
  //printf("  /CF  <file1> <file2>: Compare <file1>(A) and <file2>(B) Dec. data\n");
  //printf("  /CF1 <file1> <file2>: Compare <file1>(A) and <file2>(B) Hex. data\n");
  //printf("  /CV  <file> <value>: Compare Dec|Hex value(A) in file with value(B)\n");
  //printf("  /CV1 <file> <value>: Compare floating value(A) in file with value(B)\n");
  //printf("    if A > B return code=2; if A = B return code=1; if A < B return code=0\n");  
  //printf("    -diff <value>: diff value in value (A) and value (B)\n");
  //printf("      if A-B > diff value return code=2\n");
  //printf("      if A-B = diff value return code=1\n"); 
  //printf("      if A-B < diff value return code=0\n");
  //printf("  /CH <file> <value(Hex)>: Compare value(A) in file with value(B) for Hex\n");
  //printf("    if A > B return code=2; if A = B return code=1; if A < B return code=0\n");
  //printf("  /D <file> <x> <y> <attr>: Display txt file\n");
  //printf("  /S : Scan barcode and save to barcode.dat\n");
  //printf("  /TBC <file>: Transfer barcode format\n");
  //printf("  /TStr <file> <s1> <s2>: Replace string s1 by s2 for file, save to update.txt\n");
  //printf("  /ChkChar <file> <bit> <char>: Read a data from file and check with char\n");
  //printf("  /ChkStr <file> <string>: Read data from file and check with string\n");
  //printf("  /CFStr <file1> <file2>: Read data from file1 and check in file2\n");
  //printf("  /Find <file> <string>: Search string from file\n");
  //printf("    -t: Transfer file to normal text format for /ChkStr, /Find\n");
  //printf("  /H2D <file>: Transfer Hex to Dec value\n");
  //printf("  /GStr|/GStr1 <fn>: Get string from file, /GStr1 will change line\n");
  //printf("    -LSB <n>: specify last <n> bit data for /GStr|/GStr1\n");
  //printf("    -start_comma | -end_comma <n>: set the range of searching string by comma\n");
  //printf("  /C <fn1> <fn2>: file(fn1 & fn2) compare content, default range is 1 to end\n");
  //printf("    -i: Ignore case-sensitive for /C\n");
  //printf("  /CSum <fn> <checksum>: Calculate the checksum of file(fn)\n");
  //printf("    -sl|-el <l>: Set the start|end line of file for /C, /CSum, \n");  
  //printf("    -sa|-ea <n>: Set start|end byte of file for /C,/CSum,/ChkStr,/CFStr,/H2D,\n");
  //printf("  /CB <fn1> <fn2> ... <fnN> : Create N batch & pro files base on N ini files\n");
  //printf("    -chkbc <N>: Scan barcode N times and compare, N must >= 2\n");
  //printf("    -del <M>: Delete Mth bit barcode and change 90 code to 80 code\n");
  //printf("    -p <string>: Set the prompt string\n");
  //printf("  /CBC <fn1>...<fnN>: Create batch & pro file by comparing barcode & ini file\n");
  //printf("  /SB <data_file> <ini_file>: Set 90 barcode environment variable\n");
  //printf("  /RC <file> <bit>: Return character(0~9,A~Z) code\n");
  //printf("  /SET <f1> <f2>: Set environment variable base on f1, then write to f2\n");
  //printf("                  where f1: input file  ,  f2: output file\n");
  //printf("    -sstr <str>: Search string\n");
  //printf("    -sev <str>: Set environment variable base on string\n");
  //printf("  /Random : Create Random Number based on 16\n");
  //printf("    -length <value> : Set the length <value> of Random number in Byte Unit\n");
  //printf("  /Random1 : Produce random character\n");
  //printf("    -length1 <value> : Set random character length\n");
  //printf("  /TIB <F1.BIN> <F2.TXT> <F.BIN> <place>: Write F2.TXT into certain position\n");
  //printf("					  in F1.BIN, and save as F.BIN.\n");
  //printf("  /OBWSN <file>: Check OBW Serial Number rule\n");
  //printf("  /R1|/R2 <fn> <char>: Set environment variable (for 14 & 15 bit)\n");
  //printf("  /R3 <fn> <bit> <char>: Set environment variable and file name (for 14,15 bit)\n");
  //printf("  /R4 <fn1> <char> <fn2>: Set environment variable and file name (for 19 bit)\n");
  //printf("  /R5|/R6 <fn> <bit1> <bit2> <env_var>: Set environment variable for barcode\n");
  //printf("  /R7 <fn> <bit> <char1> <char2>: Set environment variable and file name\n");
  //printf("  /CLS <file> : Show each Line status in a File\n");
  //printf("    -line <n> : Set the estimated number of line in a file\n");
  //printf("Return Code: OK(0), ERROR(nErrorLevel)\n");
  End(nErrorLevel);
}


//--------------------------------------------------------------------------
void End(int iReturnCode)
{
	if(!blNoLogo)
	{
		int y = wherey();
		if((y < 24)&&(blClearScreen==true))
			y = 24;

		char sRetCode[20];
		sprintf_s(sRetCode, "Return Code = %d",iReturnCode);
		PrintStr(0, y, sRetCode, LOC_MIDDLE, 0x08);
	}
	Cursor(true);
  	exit(iReturnCode);
	return;
}

//--------------------------------------------------------------------------
BOOL blStartOBJTdeIO(void)   
{		
  BOOL blFlag=TRUE;  
	hDll = LoadLibraryEx("ObjTdeIo", NULL, 0);
	if(hDll == NULL){

	  FreeLibrary(hDll);
	  return FALSE;
	}

	dwVersionOfTdeIODriver	= (DWORD (*)(...))GetProcAddress(hDll, "dwVersionOfTdeIODriver");
	dwVersionOfObjTdeIo		= (DWORD (*)(...))GetProcAddress(hDll, "dwVersionOfObjTdeIo");

	IOR		= (DWORD (*)(...))GetProcAddress(hDll, "IOR");
	bIOR	= (BYTE  (*)(...))GetProcAddress(hDll, "bIOR");
	wIOR	= (WORD  (*)(...))GetProcAddress(hDll, "wIOR");
	dwIOR	= (DWORD (*)(...))GetProcAddress(hDll, "dwIOR");
	bitIOR	= (BYTE  (*)(...))GetProcAddress(hDll, "bitIOR");

	IOW		= (void (*)(...))GetProcAddress(hDll, "IOW");
	IOWB	= (void (*)(...))GetProcAddress(hDll, "IOWB");
	IOWW	= (void (*)(...))GetProcAddress(hDll, "IOWW");
	IOWD	= (void (*)(...))GetProcAddress(hDll, "IOWD");
	IOWBit	= (void (*)(...))GetProcAddress(hDll, "IOWBit");

	if (IOR	==NULL)		blFlag=FALSE;
	if (bIOR==NULL) 	blFlag=FALSE;
	if (wIOR==NULL) 	blFlag=FALSE;
	if (dwIOR==NULL) 	blFlag=FALSE;
	if (bitIOR==NULL) 	blFlag=FALSE;
	if (IOW==NULL)		blFlag=FALSE;
	if (IOWB==NULL) 	blFlag=FALSE;
	if (IOWW==NULL) 	blFlag=FALSE;
	if (IOWD==NULL) 	blFlag=FALSE;
	if (IOWBit==NULL) 	blFlag=FALSE;

	if (dwVersionOfTdeIODriver==NULL) {
		SmartStrcpy(gstPCIInfo.stProcName.sMsg,"dwVersionOfTdeIODriver functtion not in objTDEIO.dll\n");
		blFlag=FALSE;
	}
	if (dwVersionOfObjTdeIo==NULL) {
		SmartStrcpy(gstPCIInfo.stProcName.sMsg,"dwVersionOfObjTdeIo functtion not in objTDEIO.dll\n");
		blFlag=FALSE;
	}
	if (bIOR==NULL) {		
		//fprintf(stdout,"dwIOR function not in ObjTdeIo.dll.\n2.請輸入次數代表離開:"); 
		//fscanf( stdin, "%ld", &dwTemp) ;
		FreeLibrary(hDll); 
		blFlag=FALSE;
	}
	if (IOWB==NULL) {		
		//fprintf(stdout,"dwIOR function not in ObjTdeIo.dll.\n2.請輸入次數代表離開:"); 
		//fscanf( stdin, "%ld", &dwTemp) ;
		FreeLibrary(hDll); 
		blFlag=FALSE;
	}
	if (blFlag==FALSE) {
		fprintf(stdout,"some fnuctions can not be loaded in ObjTDEIO.dll.\n"); 
		FreeLibrary(hDll); 
		return FALSE;
	}
	return TRUE;
}

char	Code[36]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H',
	              'I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

int atoh(const char* pStr){
  int ah = 0;
  int pp=0;
	unsigned int sl = strlen(pStr);
	for(unsigned int p = 0 ; p < sl ; p++){ // pow & index of pStr
	  for(; pp < 16 ; pp++){	// index of code for 0 ~ E
			if((pStr[sl - 1 - p]) == Code[pp]) break;
		}
		ah = ah + pp * (int) pow(16,(double)p);
	}
	return ah;
}

//--------------------------------------------------------------------------
void main(int argc, char *argv[])
{
  FILE  *f1,*f2,*fBar,*f3,*f4,*f,*ff;
  int   i,ReadBit,ChkTimes=0,Del_Bit=0,m,n,BitNo=0,value = 0,x,y;
  WORD  j, k, p;
  DWORD sum=0, dwTemp;
  char  ch,**iniFile,Prmpt[80]="\0",BarCode[100],s[100],szACS[100],d[80],str2[100]="\0",s3[100]="\0",EnvirVar[80]="\0",str3[80]="\0", sINI1[80]="",str4[50],str5[50];
  char szTems[10]={0};

  BOOL blParameterOK=FALSE;
  BOOL blResultOK=FALSE;
  BOOL blPrompt=FALSE;
  BOOL blignore=FALSE;
  BOOL blCaseSensitive=FALSE;
  BOOL blDEC=FALSE;
  BOOL blHEX=FALSE;
  BOOL blENG=FALSE;
  BOOL blENGDEC=FALSE;
  BOOL blFLOAT=FALSE;
  BOOL blchangeline=FALSE;
  BOOL blinclude=FALSE;

	for(int a = 0; a < (argc - 1); a++) 
	{
		//if(stricmp(argv[a+1] , "-c") == 0)
		//{
		//	blCaseSensitive=TRUE;
		//	continue;
		//}
		if(stricmp(argv[a+1] , "-in") == 0)
		{
			blinclude=TRUE;
			continue;
		}
		if(stricmp(argv[a+1] , "-low") == 0)
		{
			blow=TRUE;
			continue;
		}
		if(stricmp(argv[a+1] , "-cl") == 0)
		{
			blchangeline=TRUE;
			continue;
		}
		if(stricmp(argv[a+1], "-type") == 0)
		{
			if(stricmp(argv[a+2], "1") == 0)
				{
					blDEC = true;
				}
			else if(stricmp(argv[a+2], "2") == 0)
				{
					blHEX  = true;
				}
			else if(stricmp(argv[a+2], "3") == 0)
				{
					blENG = true;
				}
			else if(stricmp(argv[a+2], "4") == 0)
				{
					blENGDEC = true;
				}
			else if(stricmp(argv[a+2], "5") == 0)
				{
					blFLOAT = true;
				}
			else
				ReadMe();
			continue;
		}
		if(stricmp(argv[a+1], "-cs") == 0)
		{
			if(stricmp(argv[a+2], "on") == 0)
				{
					blCaseSensitive = true;
				}
			else if(stricmp(argv[a+2], "off") == 0)
				{
					blCaseSensitive = false;
				}
			else
				ReadMe();
			continue;
		}
		if(stricmp(argv[a + 1], "-erv") == 0) 
		{
			if(argv[a + 2]!=NULL)
			{
				if(!isdigit(*argv[a+2]))
				{
					blParameterOK = FALSE;
					break;
				}
			
				nErrorLevel= atoi(argv[a + 2]);
				if(nErrorLevel>255||nErrorLevel<0)
				{
					blParameterOK = FALSE;
					nErrorLevel=255;
					break;
				}
			}
			continue;
		}
		if(stricmp(argv[a+1], "-str1")==0){
		  strcpy(str4,argv[a+2]);
		  blSetStr1=TRUE;
		  continue;
		}
		if(stricmp(argv[a+1], "-str2")==0){
		  strcpy(str5,argv[a+2]);
		  blSetStr2=TRUE;
		  continue;
		}
		if(stricmp(argv[a+1], "-str")==0){
		  strcpy(str4,argv[a+2]);
		  blSetStr1=TRUE;
		  continue;
		}
		if(stricmp(argv[a+1], "-LSB")==0) {
		  blLastBit=TRUE;
		  LastBit=atoi(argv[a+2]);
		  continue;
		}
		if (stricmp(argv[a+1] , "-line") == 0) {
		  if (argv[a+2] != NULL)
		  {
			if(isdigit(*argv[a+2]))
			{
				nLine = atoi(argv[a+2]);
				if (nLine == 0) ReadMe();
				continue;
			}
			else
				ReadMe();
		  }
		  else
			  ReadMe();
		}
	}
  // begin handle the user interface
  for(i=0; i<(argc-1); i++) {
    if(stricmp(argv[i+1], "?")==0  ||\
       stricmp(argv[i+1], "/?")==0 ||\
       stricmp(argv[i+1], "/h")==0 ||\
       stricmp(argv[i+1], "/help")==0) {
	   blParameterOK=TRUE;
	   ReadMe();
	   continue;
    }
	 if(stricmp(argv[i + 1], "-nc") == 0) 
	{
		blClearScreen = false;
		continue;
	}

    if(stricmp(argv[i+1], "-nl") ==0){
      blNoLogo = TRUE;
      continue;
    }

	if(_stricmp(argv[i + 1], "/version")  ==  0 )
	{
		if(!blNoLogo)Logo();
		blParameterOK = true;
		printf("%s\n",sRevision);
		continue;
	}

    if (stricmp(argv[i+1] , "/CLS") == 0) {
      if (argv[i+2] == NULL) break;
      blParameterOK = TRUE;
      if(!blNoLogo) Logo();
      if (blCheckLines (argv[i+2])) blResultOK = TRUE;
      break;
    }



    if(stricmp(argv[i+1], "/GMT")==0) {
      blParameterOK=TRUE;
      blResultOK=TRUE;
      if(!blNoLogo)Logo();
      printf("%ld", dwTransferNowDateTime2GMT());
	  cprintf("\n");
      continue;
    } 

    if(stricmp(argv[i+1], "/CF")==0)
	{
		if(!blNoLogo)Logo();
		if(blDEC)
		{
			if(argc>(i+3)) 
			{
				blParameterOK=TRUE;
				DWORD dwValue1;
				if((f1=fopen(argv[i+2],"r+"))!=NULL)
				{
					fscanf(f1, "%ld", &dwValue1);
					fclose(f1);
					if((f1=fopen(argv[i+2],"r+"))!=NULL)
					{
						fscanf(f1, "%s", szACS);
						for(int j=0;j<strlen(szACS);j++)
						{
							int iACS=0;
							iACS=(int)szACS[j];

							if(iACS<48||iACS>57)
							{
								printf("data in file %s is not dec.\n",argv[i+2]);
								End(nErrorLevel);
							}
						}
						fclose(f1);
						if((f2=fopen(argv[i+3],"r+"))!=NULL) 
						{
							DWORD dwValue2;
							fscanf(f2, "%ld", &dwValue2);
							fscanf(f2, "%s", szACS);
							for(int j=0;j<strlen(szACS);j++)
							{
								int iACS=0;
								iACS=(int)szACS[j];

								if(iACS<48||iACS>57)
								{
									printf("data in file %s is not dec.\n",argv[i+3]);
									End(nErrorLevel);
								}
							}
							fclose(f2);
							cprintf("value in file(%s) = %ld\n\r", argv[i+2], dwValue1);
							cprintf("value in file(%s) = %ld\n\r", argv[i+3], dwValue2);
							cprintf("the difference = ");
							printf("%ld\n", dwValue1-dwValue2);
							if(blDiff)
							{
								cprintf("Value in Difference range = %ld\n\r", (int)fDiff);
								if(abs((int)dwValue1-(int)dwValue2) > (int)fDiff)
								{
									cprintf("the Difference in %ld and %ld is %d > %d\n\r", 
										dwValue1, dwValue2, abs((int)dwValue1-(int)dwValue2), int(fDiff));
									fcloseall();
									End(2);
								}
								else if(abs((int)dwValue1-(int)dwValue2) == (int)fDiff)
								{
									cprintf("the Difference in %ld and %ld is %d = %d\n\r", 
										dwValue1, dwValue2, abs((int)dwValue1-(int)dwValue2), int(fDiff));
									fcloseall();
									End(1);
								}
								else if(abs((int)dwValue1-(int)dwValue2) < (int)fDiff)
								{
									cprintf("the Difference in %ld and %ld is %d < %d\n\r", 
										dwValue1, dwValue2, abs((int)dwValue1-(int)dwValue2), int(fDiff));
									fcloseall();
									End(0);
								}
							}
							else
							{
								if(dwValue1>dwValue2) 
								{
									cprintf("%ld > %ld\n\r", dwValue1, dwValue2);
									fcloseall();
									End(2);
								}
								if(dwValue1==dwValue2) 
								{
									cprintf("%ld = %ld\n\r", dwValue1, dwValue2);
									fcloseall();
									End(1);
								}
								if(dwValue1<dwValue2)
								{
									cprintf("%ld < %ld\n\r", dwValue1, dwValue2);
									fcloseall();
									End(0);
								}
							}
						} 
						else cprintf("open %s ERROR...\n\r", argv[i+3]);
					} 	
				}else cprintf("open %s ERROR...\n\r", argv[i+2]);	
			}
		}
		//continue;
	//}

 //   if(stricmp(argv[i+1], "/CF1")==0)
	//{
      //if(!blNoLogo)Logo();
		else if(blHEX)
		{
		  if(argc>(i+3))
		  {
				blParameterOK=TRUE;
				DWORD dwValue1;
				if((f1=fopen(argv[i+2],"r+"))!=NULL) 	
				{
					fscanf(f1, "%lX", &dwValue1);
					fclose(f1);
				}
				if((f1=fopen(argv[i+2],"r+"))!=NULL)
				{
					fscanf(f1, "%s", szACS);
					for(int j=0;j<strlen(szACS);j++)
					{
						int iACS=0;
							iACS=(int)szACS[j];
						if(iACS<48||(57<iACS&&iACS<65)||(79<iACS&&iACS<97)||iACS>102)
						{
							printf("data in file %s is not Hex.\n",argv[i+2]);
							End(nErrorLevel);
						}
					}
					fclose(f1);
					if((f2=fopen(argv[i+3],"r+"))!=NULL) 
					{
						DWORD dwValue2;
						fscanf(f2, "%lX", &dwValue2);
						fscanf(f2, "%s", szACS);
						for(int j=0;j<strlen(szACS);j++)
						{
							int iACS=0;
							iACS=(int)szACS[j];
							if(iACS<48||(57<iACS&&iACS<65)||(79<iACS&&iACS<97)||iACS>102)
							{
								printf("data in file %s is not Hex.\n",argv[i+3]);
								End(nErrorLevel);
							}
						}
						fclose(f2);
						cprintf("value in file(%s) = %lX\n\r", argv[i+2], dwValue1);
						cprintf("value in file(%s) = %lX\n\r", argv[i+3], dwValue2);
						cprintf("the difference = ");
						if(blDiff)
						{
							cprintf("Value in Difference range = %ld\n\r", (int)fDiff);
							if(abs((int)dwValue1-(int)dwValue2) > (int)fDiff)
							{
							cprintf("the Difference in %ld and %ld is %d > %d\n\r", 
							dwValue1, dwValue2, abs((int)dwValue1-(int)dwValue2), int(fDiff));
							fcloseall();
							End(2);
							}
							else if(abs((int)dwValue1-(int)dwValue2) == (int)fDiff)
							{
								cprintf("the Difference in %ld and %ld is %d = %d\n\r", 
								dwValue1, dwValue2, abs((int)dwValue1-(int)dwValue2), int(fDiff));
								fcloseall();
								End(1);
							}
							else if(abs((int)dwValue1-(int)dwValue2) < (int)fDiff)
							{
								cprintf("the Difference in %ld and %ld is %d < %d\n\r", 
								dwValue1, dwValue2, abs((int)dwValue1-(int)dwValue2), int(fDiff));
								fcloseall();
								End(0);
							}
						}
						else
						{
							if(dwValue1 >= dwValue2) printf("%ld\n", dwValue1-dwValue2);
							else printf("%ld\n", dwValue2-dwValue1);
							if(dwValue1>dwValue2) 
							{
								cprintf("%lX > %lX\n\r", dwValue1, dwValue2);
								fcloseall();
								End(2);
							}
							if(dwValue1==dwValue2)
							{
								cprintf("%lX = %lX\n\r", dwValue1, dwValue2);
								fcloseall();
								End(1);
							}
							if(dwValue1<dwValue2)
							{
								cprintf("%lX < %lX\n\r", dwValue1, dwValue2);
								fcloseall();
								End(0);
							}
						}
					} else cprintf("open %s ERROR...\n\r", argv[i+3]);
				} else cprintf("open %s ERROR...\n\r", argv[i+2]);
		  }
		}
      continue;
    }

    if(stricmp(argv[i+1], "/CV")==0)
	{

		if(!blNoLogo)Logo();
		if(blHEX){
		if(argc>(i+3))
		{
			blParameterOK=TRUE;
			p=0;
			int m1 = 0,
				  n1 = 0,
					sub = 0;
			BOOL blHex = FALSE;
			if((f1=fopen(argv[i+2],"r+"))!=NULL) 
			{
				fgets(s,100,f1);//add by Jackson, 2003-08-15
				strcpy(s3,argv[i+3]);
				for(j=0;j<strlen(s);j++)
				{
					if(s[j]==' ' || s[j]=='\n')
					{
						s[j]='\0';
						break;
					}
				  s[j]=toupper(s[j]);
				}
				for(j=0;j<strlen(s3);j++) s3[j]=toupper(s3[j]);
				for(j=0;j<strlen(s);j++)
				{
				  for(m=0;m<36;m++)
					if(s[j]==Code[m]) break;
					if(m>15)
					{
						textcolor(15);
						textbackground(4);
						cprintf("\n\r ERROR !! %s='%s' Is Not Hex Data !! ",argv[i+2],s);
						fcloseall();
						textattr(7);
						End(nErrorLevel);
					}
						if( m > 9 && m < 16) blHex = TRUE;
				}
				for(j=0;j<strlen(s3);j++)
				{
				  for(n=0;n<36;n++)
				  if(s3[j]==Code[n]) break;
				  if(n>15)
				  {
					textcolor(15);
					textbackground(4);
					cprintf("\n\r ERROR !! '%s' Is Not Hex Data !! ",s3);
					fcloseall();
					textattr(7);
					End(nErrorLevel);
				  }
				  if( n > 9 && n < 16) blHex = TRUE;
				}							
				if(strlen(s)==strlen(s3)){
					for(j=0;j<strlen(s);j++){
						for(m=0;m<36;m++)
							if(s[j]==Code[m]) break;
						for(n=0;n<36;n++)
							if(s3[j]==Code[n]) break;
						if(blDiff){
							if(blHex){
								m1 = atoh(s); n1 = atoh(s3);
							}else{
								m1 = atoi(s);	n1 = atoi(s3);
							}								
							sub = abs(m1-n1);
							if(sub > fDiff){
								value = 2;
								break;
							}else if(sub < fDiff){
								value = 0;
								break;
							}else if(sub == fDiff){									
								value = 1;
								break;
							}
						}
						else{
							if(m>n){
							  value=2;
							  break;
						  }
						  else if(m<n){
  							value=0;
							  break;
						  }
						  else if(m==n){
							  p++;
							  if(p<strlen(s)) continue;
							  value=1;
						  }
						}							
					}
				}
				else if(strlen(s)>strlen(s3)){
					if(blDiff){
						if(blHex){ 
							m1 = atoh(s); n1 = atoh(s3);
						}	else{ m1 = atoi(s); n1 = atoi(s3);}							
						sub = abs(m1-n1);							
						if(sub > fDiff) value = 2;
						else if(sub < fDiff) value = 0;
						else if(sub == fDiff) value = 1;
					}else value=2;
				}
				else if(strlen(s)<strlen(s3)){
					if(blDiff){
						if(blHex){
							m1 = atoh(s); n1 = atoh(s3);
						}else{ m1 = atoi(s); n1 = atoi(s3);}				
						sub = abs(m1-n1);							
						if(sub > fDiff)	value = 2;					
						else if(sub < fDiff) value = 0;								
						else if(sub == fDiff) value = 1;
					}else value=0;
				}
				if(value==2) {
					cprintf("value in file(%s) = %s\n\r",argv[i+2],s);
					cprintf("value in parameter = %s\n\r",s3);
					if(blDiff)
						cprintf("value in Difference = %d\n\r", int(fDiff));
					textcolor(15);
					textbackground(1);
					if(blDiff)
						cprintf("the Difference in %s and %s is %d > %d\n\r", s, s3, abs(m1-n1), int(fDiff));
					else cprintf("%s > %s\n\r",s,s3);						
					fcloseall();
					textattr(7);
					End(2);
				} 
				if(value==1) {
					cprintf("value in file(%s) = %s\n\r",argv[i+2],s);
					cprintf("value in parameter = %s\n\r",s3);
					if(blDiff)
						cprintf("value in Difference = %d\n\r", int(fDiff));
					textcolor(15);
					textbackground(1);
					if(blDiff)
						cprintf("the Difference in %s and %s is %d = %d\n\r", s, s3, abs(m1-n1), int(fDiff));
					else cprintf("%s = %s\n\r",s,s3);				
					fcloseall();
					textattr(7);
					End(1);
				}
				if(value==0) {
					cprintf("value in file(%s) = %s\n\r",argv[i+2],s);
					cprintf("value in parameter = %s\n\r",s3);
					if(blDiff)
						cprintf("value in Difference = %d\n\r", int(fDiff));
					textcolor(15);
					textbackground(1);
					if(blDiff)
						cprintf("the Difference in %s and %s is %d < %d\n\r", s, s3, abs(m1-n1), int(fDiff));
					else cprintf("%s < %s\n\r",s,s3);						
					fcloseall();
					textattr(7);
					End(0);
				}
			}
        else{
		      textcolor(15);
		      textbackground(4);
		      cprintf("\n ERROR !! Can't Open '%s' !! \n\r",argv[i+2]);
		      textattr(7);
		      End(nErrorLevel);
		    }
		}
	  }
    /*continue;
	}
	if(stricmp(argv[i+1], "/CV1") == 0){*/
	if(blFLOAT){
    char chFileValue[100] = {"\0"};
    char chFileNumber[100] = {"\0"};
    //char *pStrEnd;
    unsigned int n2e = 0, j = 0, k = 0;
    float nFileValue = 0.0,
					nCompareValue = 0.0,
					SubValue = 0.0;
    //if(!blNoLogo)Logo();
    if(argc > (i+3)){
			blParameterOK = TRUE;
			if((f1 = fopen(argv[i+2], "r+")) != NULL){
				fgets(chFileValue, 100, f1);				
				for(j ; j < 100 ; j++){
					if(chFileValue[j] == 0x00 || chFileValue[j] == 0x20) break;
					chFileNumber[j] = chFileValue[j];
				}
				for(k ; k < strlen(chFileNumber)-1 ; k++){
					if(chFileNumber[k] == 0x2e){
						n2e++;
						if(n2e > 1){
							textcolor(15);
							textbackground(4);
							cprintf("\n\r ERROR 0x2E !! %s = '%s' %d Is Not Numeral Data", argv[i+2], chFileValue, k);
							textattr(7);
							fcloseall();
							End(nErrorLevel);
						}
						continue;
					}else if(!isdigit(chFileNumber[k])){
						textcolor(15);
						textbackground(4);
						cprintf("\n\r ERROR !! %s = '%s' %d Is Not Numeral Data", argv[i+2], chFileValue, k);
						textattr(7);
						fcloseall(); 
						End(nErrorLevel);
					}
				}
				nFileValue = (float)atof(chFileNumber);
				// check input value
				for(unsigned int a = 0 ; a < strlen(argv[i+3]) ; a++){
					if(!isdigit(argv[i+3][a]) && argv[i+3][a] != 0x2e){
						textcolor(15);
						textbackground(4);
						cprintf("\n\r ERROR !! The inputed %s Is Not Numeral Data", argv[i+3]);
						textattr(7);
						fcloseall(); 
						End(nErrorLevel);
					}
				}
				nCompareValue = (float) atof(argv[i+3]);							
				cprintf("Value in File(%s) = %s \n\r", argv[i+2], chFileNumber);
				cprintf("Value in Parameter = %4.3f \n\r", nCompareValue);			
		
				if(blDiff){
					cprintf("Value in Difference = %4.3f \n\r", fDiff);
					SubValue = (float)fabs(nFileValue-nCompareValue);
					if(fabs(SubValue - fDiff) <= 0.0009){
						textcolor(15);
						textbackground(1);
						cprintf("the Difference in %4.3f and %4.3f is %4.3f = %4.3f\n\r", nFileValue, nCompareValue, fabs(nFileValue-nCompareValue), (fDiff));						
						textattr(7);
						fcloseall(); 
						End(1);

					}else if(SubValue < fDiff){
						textcolor(15);
						textbackground(1);
						cprintf("the Difference in %4.3f and %4.3f is %4.3f < %4.3f\n\r", nFileValue, nCompareValue, fabs(nFileValue-nCompareValue), (fDiff));						
						textattr(7);
						fcloseall(); 
						End(0);
					}else if(SubValue > fDiff){
						textcolor(15);
						textbackground(1);
						cprintf("the Difference in %4.3f and %4.3f is %4.3f > %4.3f\n\r", nFileValue, nCompareValue, fabs(nFileValue-nCompareValue), (fDiff));						
						textattr(7);
						fcloseall(); 
						End(2);
					}
				}
				else{
					if(nFileValue > nCompareValue){
						textcolor(15);
						textbackground(1);
						cprintf("%4.3f > %4.3f\n\r", nFileValue, nCompareValue);
						textattr(7);
						fcloseall(); 
						End(2);
					}
					else if(nFileValue < nCompareValue){
						textcolor(15);
						textbackground(1);
						cprintf("%4.3f < %4.3f\n\r", nFileValue, nCompareValue);
						textattr(7);
						fcloseall(); 
						End(0);
					}
					else if(nFileValue == nCompareValue){
						textcolor(15);
						textbackground(1);
						cprintf("%4.3f = %4.3f\n\r", nFileValue, nCompareValue);
						textattr(7);
						fcloseall(); 
						End(1);
					}	
				}
			}
			else{
				textcolor(15);
				textbackground(4);
				cprintf("\n ERROR !! Can't Open %s !!\n\r", argv[i+2]);
				textattr(7);					
				End(nErrorLevel);
			}
		}
	}
    continue;
  }
/*    if(stricmp(argv[i+1], "/CH")==0) {
      DWORD int  Value1,Value2;
      DWORD char Value3[10];
      DWORD char *Value4=argv[i+3];
      Logo();

      if(argc>(i+3)) {
		blParameterOK=TRUE;
		if((f1=fopen(argv[i+2],"r+"))!=NULL) {
		  fgets(Value3,10,f1);
		  fclose(f1);
		  sscanf(Value3,"%x",&Value1);
		  sscanf(argv[i+3],"%x",&Value2);
		  for(j=0;j<strlen(Value3);j++){
			if(Value3[j]=='\n'){
			  Value3[j]='\0';
			  break;
		    }
		  }
		  printf("value in file(%s) = %s\n", argv[i+2], Value3);
		  printf("value in parameter = %s\n", Value4);
		  if(Value1>Value2) {
			printf("%s > %s\n", Value3, Value4);
			fcloseall();
			End(2);
		  }
		  if(Value1==Value2) {
			printf("%s = %s\n", Value3, Value4);
			fcloseall();
			End(1);
		  }
		  if(Value1<Value2) {
			printf("%s < %s\n", Value3, Value4);
			fcloseall();
			End(0);
		  }
		}
      }
      continue;
    }*/
    if(stricmp(argv[i+1], "/FS")==0) {
      if(!blNoLogo)Logo();
      if(argc>(i+2)) 
	  {
		blParameterOK=TRUE;
		DWORD dwValue1, dwValue2;
		dwValue1=dwGetFileSize(argv[i+2]);
		
		cprintf("size of file(%s) = %ld\n\r", argv[i+2], dwValue1);
		if(argc>(i+3)) 
		{
			dwValue2=atol(argv[i+3]);
		  cprintf("value in parameter = %ld\n\r", dwValue2);
		  if(dwValue1>dwValue2)
		  {
			cprintf("%ld > %ld\n\r", dwValue1, dwValue2);
			End(2);
		  }
		  if(dwValue1==dwValue2) 
		  {
			cprintf("%ld = %ld\n\r", dwValue1, dwValue2);
			End(1);
		  }
		  if(dwValue1<dwValue2) 
		  {
			cprintf("%ld <% ld\n\r", dwValue1, dwValue2);
			End(0);
		  }
		} 
		//else End(nErrorLevel);
      }
	  //else End(nErrorLevel);
      continue;
    }
    if(stricmp(argv[i+1], "/D")==0) {
      //if(!blNoLogo)Logo();
	  if(blClearScreen)
		clrscr();
      blParameterOK=TRUE;
      if(argc==(i+3)) {
				clrscr();
				DisplayTxtFile(argv[i+2], 1, 1, 0x07);
      } else if(argc==(i+5)) {
				int x, y;
				x=atoi(argv[i+3]); if(x<1 || x>80) x=1;
				y=atoi(argv[i+4]); if(y<1 || y>24) y=1;
				DisplayTxtFile(argv[i+2], x, y, 0x07);
      } else if(argc==(i+6)) {
			int x, y;
			BYTE attr;
			x=atoi(argv[i+3]); if(x<1 || x>80) x=1;
			y=atoi(argv[i+4]); if(y<1 || y>24) y=1;
				sscanf(argv[i+5], "%lX", &dwTemp);
			attr=(BYTE) dwTemp;
			DisplayTxtFile(argv[i+2], x, y, attr);
	  } else break;
      gotoxy(1,24);
      exit(nErrorLevel);
    }
		if(stricmp(argv[i+1], "-diff") == 0){			
			blDiff = TRUE;			
			fDiff = atof(argv[i+2]);					
			continue;
		}
    if(stricmp(argv[i+1], "-SA")==0) {
      blUseAddress=TRUE;
      blUseStartAddress=TRUE;
	  if(isdigit(*argv[i+2]))
      dwStartAddress=atol(argv[i+2])-1;
      continue;
    }
    if(stricmp(argv[i+1], "-EA")==0) {
      blUseAddress=TRUE;
      blUseEndAddress=TRUE;
	  if(isdigit(*argv[i+2]))
      dwEndAddress=atol(argv[i+2])-1;
      continue;
    }
    if(stricmp(argv[i+1], "-SL")==0) {
      blUseLine=TRUE;
      blUseStartLine=TRUE;
	  if(isdigit(*argv[i+2]))
      dwStartLine=atol(argv[i+2])-1;
      continue;
    }
    if(stricmp(argv[i+1], "-EL")==0) {
      blUseLine=TRUE;
      blUseEndLine=TRUE;
	  if(isdigit(*argv[i+2]))
      dwEndLine=atol(argv[i+2])-1;
      continue;
    }

    //if(stricmp(argv[i+1], "-i")==0) {
     blignore=TRUE;
    //  continue;
   // }

    if(stricmp(argv[i+1], "/CSum")==0) {
      if(!blNoLogo)Logo();
	  if(argc >= 4) sscanf(argv[i+3], "%lX", &dwTemp);
	  else dwTemp=' ';
      if(blFileCheckSum(argv[i+2], (WORD) dwTemp)) End(0);
      End(nErrorLevel);
    }
    if(stricmp(argv[i+1], "-ChkBC")==0) {
      ChkTimes=atoi(argv[i+2]);
      if(ChkTimes<2){
			  printf("\n ERROR !! N Must >= 2 !!\n");
			  End(nErrorLevel);
      }
      blParameterOK=TRUE;
      continue;
    }
    if(stricmp(argv[i+1], "-DEL")==0) {
      Del_Bit=atoi(argv[i+2]);
      blParameterOK=TRUE;
      continue;
    }
    if(stricmp(argv[i+1], "-P")==0) {
      blPrompt=TRUE;
      blParameterOK=TRUE;
      strcpy(Prmpt,argv[i+2]);
      continue;
    }
    if(stricmp(argv[i+1], "-T")==0) {
      blTransfer=TRUE;
      blParameterOK=TRUE;
      continue;
    }
    if(stricmp(argv[i+1], "/CB")==0) {
      if(!blNoLogo)Logo();
      if((iniFile=(char **)malloc(225))==NULL){
		    printf("ERROR !! Not Enough Memory to Allocate Buffer !!\n");
		    End(nErrorLevel);
      }
      if(argc>(i+2)) blParameterOK=TRUE;
      else ReadMe();
      for(j=0;j<argc-i-2;j++) iniFile[j]=argv[i+2+j];
      if(Process_ini_File(Del_Bit,ChkTimes,j,iniFile,Prmpt)) blResultOK=TRUE;
      free(iniFile);
    }
    if(stricmp(argv[i+1], "/CBC")==0) {
      if(!blNoLogo)Logo();
      if((iniFile=(char **)malloc(225))==NULL){
		    printf("ERROR !! Not Enough Memory to Allocate Buffer !!\n");
		    End(nErrorLevel);
      }
      if(argc>(i+2)) blParameterOK=TRUE;
      else ReadMe();
      for(j=0;j<argc-i-2;j++) iniFile[j]=argv[i+2+j];
      if(Process_ini_File2(Del_Bit,j,iniFile)) blResultOK=TRUE;
      free(iniFile);
    }
    if(stricmp(argv[i+1], "/ChkChar")==0) {
      if(!blNoLogo)Logo();
      ReadBit=atoi(argv[i+3]);
      if(argc >= 5) ch=*argv[i+4];
	  else ch=' ';
      blParameterOK=TRUE;
      if(CheckChar(argv[i+2],ReadBit,ch)) blResultOK=TRUE;
    }

    if(stricmp(argv[i+1], "/TBC")==0) {
      if(!blNoLogo)Logo();
      blParameterOK=TRUE;
      if(Transfer_Barcode_Format(Prmpt)) blResultOK=TRUE;
    }
    if(stricmp(argv[i+1], "/S")==0) {
      if(!blNoLogo)Logo();
      blParameterOK=TRUE;
      if((fBar=fopen("barcode.dat","w"))==NULL) {
				cprintf("\n ERROR !! Can't Open Barcode.dat !!\n\r");
				End(nErrorLevel);
      }
      if(blPrompt) printf(" %s : ",Prmpt);
      else printf(" Please Scan Barcode : ");
      system("@echo on");
      scanf("%s",BarCode);
      for(j=0;j<strlen(BarCode);j++) BarCode[j]=toupper(BarCode[j]);
      fprintf(fBar,"%s",BarCode);
      fclose(fBar);
      blResultOK=TRUE;
    }
    if(stricmp(argv[i+1], "/ChkStr")==0) {
      if(!blNoLogo)Logo();
	  if(argc>i+3){
      if(!blUseAddress) ReadMe();
      blParameterOK=TRUE;
	  blResultOK = blCheckString(argv[i+2], argv[i+3]);
	  }
      continue; 
  //    if((f3=fopen(argv[i+2],"r"))==NULL){
		//		cprintf("\n ERROR !! %s Not Found !!\n\r",argv[i+2]);
		//		End(nErrorLevel);
  //    }
  //    strcpy(str2,argv[i+3]);
  //    if(blUseStartLine && blUseEndLine && (dwStartLine==dwStartLine))
		//for(k=0;k<dwStartLine+1;k++) fgets(s,100,f3);
  //    else fgets(s,100,f3);
  //    for(k=0;k<strlen(s);k++){
		//		s[k]=toupper(s[k]);
		//		str2[k]=toupper(str2[k]);
  //    }
  //    if(strlen(str2)==0) ReadMe();
  //    k=0;
  //    for(j=(WORD) dwStartAddress;j<=dwEndAddress;j++){
		//		s3[k]=s[j];
		//		k++;
		//		if(j==dwEndAddress+1) s3[k]='\0';
  //    }
  //    if(stricmp(s3,str2)==0){
		//		printf("\n  Find Data = %s",s3);
		//		printf("\n Check Data = %s\n",str2);
		//		cprintf("\n Compare OK !!\n\r");
		//		blResultOK=TRUE;
  //    }
  //    else{
		//		printf("\n  Find Data = %s",s3);
		//		printf("\n Check Data = %s\n",str2);
		//		cprintf("\n Compare Error !!\n\r");
		//		fcloseall();
		//		End(nErrorLevel);
  //    }
    }



    if(stricmp(argv[i+1], "/Find")==0) {
      char  s1[260]="";
      blParameterOK=TRUE;

      if(!blNoLogo)Logo();
      if((f3=fopen(argv[i+2],"r"))==NULL){
				cprintf("\n ERROR !! %s Not Found !!\n\r",argv[i+2]);
				End(nErrorLevel);
      }
      if(blTransfer){
				sprintf(sINI1, "III.iii");
				CP(argv[i+2], sINI1);
				fclose(f3);
		    if((f3=fopen("III.iii","r"))==NULL){
		      cprintf("\n ... ERROR !! ... III.iii Not Found !! ... \n\r");
		      End(nErrorLevel);
		    }
      }
      strcpy(str2,argv[i+3]);
	  if (blCaseSensitive==FALSE)
	  {
		  for(k=0;k<strlen(str2);k++) str2[k]=toupper(str2[k]);
	  }
      //printf("\nSearch Data = %s\n\n",str2);
      //printf("The Result Is : \n");

      int Line=0;
      while(!feof(f3)){
				Line++;
				fgets(s1,260,f3);
				if (blCaseSensitive==FALSE)
				{
					for(k=0;k<strlen(s1);k++) s1[k]=toupper(s1[k]);
				}
				if(strlen(str2)==0) ReadMe();
				if(strstr(s1, str2) != NULL){
					printf("Line %d = %s",Line,s1);
					blResultOK=TRUE;
				}
      }
    }
    if(stricmp(argv[i+1], "/H2D")==0)
    {
      if(!blNoLogo) Logo();


      if(argc>(i+2))
      {
	      blParameterOK=TRUE;

		  if(blUseStartAddress || blUseEndAddress) /*ReadMe();*/
		  {
			  if((f=fopen(argv[i+2],"r"))==NULL){
						cprintf("\n ERROR !! %s Not Found !!\n\r",argv[i+2]);
						End(nErrorLevel);
			  }
			  if((ff=fopen("H2D.dat","w"))==NULL){
						cprintf("\n ERROR !! Can Not Open H2D.dat !!\n\r");
						End(nErrorLevel);
			  }

			  fgets(s,100,f);
			  k=0;
			  for(j=(WORD) dwStartAddress;j<=dwEndAddress;j++){
						s3[k]=s[j];
						s3[k]=toupper(s3[k]);
						k++;
					if(j==dwEndAddress+1) s3[k]='\0';
			  }
			  if(dwStartAddress>dwEndAddress) {
						printf("\n Byte Set ERROR !! Start Byte= %ld > End Byte= %ld !!\n", dwStartAddress+1, dwEndAddress+1);
						fcloseall();
						End(nErrorLevel);
			  }
			  m=dwEndAddress-dwStartAddress+1;
			  if(m>8){
						printf("\n ERROR !! Byte Amount = %d , Over Range !!\n",m);
						printf("\n The Limit Is 8 Bytes !!\n");
						End(nErrorLevel);
			  }
			  for(k=1;k<=m;k++){
				for(j=0;j<16;j++)
				  if(s3[k-1]==Code[j]) break;
				if(j==16){
					printf("\n ERROR !! The String '%s' Is Not Hex !!\n",s3);
					fcloseall();
					End(nErrorLevel);
				}
				sum=sum+j*((DWORD) pow(16,(double)m-k));
			  }
			  printf("\n String = %s  -->  Dec. Value = %lu\n",s3,sum);
			  fprintf(ff,"%lu\n",sum);
			  blResultOK=TRUE;
		  }
		  else
			  blResultOK = blTransferHex2Dec(argv[i+2]);
      }
      continue;
    }
  //  if(stricmp(argv[i+1], "/H2D")==0) {
  //    if(!blNoLogo)Logo();

  //    blParameterOK=TRUE;
  //    if((f=fopen(argv[i+2],"r"))==NULL){
		//		cprintf("\n ERROR !! %s Not Found !!\n\r",argv[i+2]);
		//		fcloseall();
		//		End(nErrorLevel);
  //    }
  //    if((ff=fopen("H2D.dat","w"))==NULL){
		//		cprintf("\n ERROR !! Can Not Open H2D.dat !!\n\r");
		//		fcloseall();
		//		End(nErrorLevel);
  //    }

  //    fgets(s,100,f);
  //    k=0;
	 // if(!blUseStartAddress || !blUseEndAddress) /*ReadMe();*/
	 // {
  //    for(j=(WORD) dwStartAddress;j<=dwEndAddress;j++){
		//		s3[k]=s[j];
		//		s3[k]=toupper(s3[k]);
		//		k++;
		//    if(j==dwEndAddress+1) s3[k]='\0';
  //    }
  //    if(dwStartAddress>dwEndAddress) {
		//		printf("\n Byte Set ERROR !! Start Byte= %ld > End Byte= %ld !!\n", dwStartAddress, dwEndAddress);
		//		fcloseall();
		//		End(nErrorLevel);
  //    }
  //    m=dwEndAddress-dwStartAddress+1;
  //    if(m>8){
		//		printf("\n ERROR !! Byte Amount = %d , Over Range !!\n",m);
		//		printf("\n The Limit Is 8 Bytes !!\n");
		//		End(nErrorLevel);
  //    }
	 // }
  //    for(k=1;k<=m;k++){
		//for(j=0;j<16;j++)
		//  if(s3[k-1]==Code[j]) break;
		//if(j==16){
		//	printf("\n ERROR !! The String '%s' Is Not Hex !!\n",s3);
		//	fcloseall();
		//	End(nErrorLevel);
		//}
		//sum=sum+j*((DWORD) pow(16,(double)m-k));
  //    }
  //    printf("\n String = %s  -->  Dec. Value = %lu\n",s3,sum);
  //    fprintf(ff,"%lu\n",sum);
  //    blResultOK=TRUE;
  //  }
    if(stricmp(argv[i+1], "/RC")==0) {
      if(!blNoLogo)Logo();
      blParameterOK=TRUE;
      if((f=fopen(argv[i+2],"r"))==NULL){
		cprintf("\n ERROR !! %s Not Found !!\n\r",argv[i+2]);
		End(nErrorLevel);
      }
      BitNo=atoi(argv[i+3]);
      fgets(s,100,f);
      s[BitNo-1]=toupper(s[BitNo-1]);
      for(j=0;j<36;j++){
		if(s[BitNo-1]==Code[j]){
		  printf(" Bit = %d  -->  Data = %c\n",BitNo,s[BitNo-1]);
		  printf("\n Return Code = %d\n",j);
		  fcloseall();
		  End(j);
		}
      }
    }
    if(stricmp(argv[i+1], "/SB")==0) {
      if(!blNoLogo)Logo();
      if(argc>(i+3)) blParameterOK=TRUE;
      else ReadMe();
      if(Set_Barcode_Environment(argv[i+2],argv[i+3])) blResultOK=TRUE;
    }
    if(stricmp(argv[i+1], "/TSTR")==0) {
      if(!blNoLogo)Logo();
//      if(argc==(i+5) && strlen(argv[i+3])==strlen(argv[i+4])) blParameterOK=TRUE;
      if(argc==(i+5)) blParameterOK=TRUE;
      else ReadMe();
      if(Transfer_String(argv[i+2],argv[i+3],argv[i+4])) blResultOK=TRUE;
    }
	if(stricmp(argv[i+1], "-start_comma") == 0) { // start number of searching by comma
      blComma = TRUE;
      nSmsk = atoi(argv[i+2]);
    }
    if(stricmp(argv[i+1], "-end_comma") == 0) {   // end number of searching by comma
      blComma = TRUE;
      nEmsk = atoi(argv[i+2]);
    }
    if(stricmp(argv[i+1], "/GSTR")==0) {
      if(argc<3) ReadMe();
      else blParameterOK=TRUE;
      if(!blNoLogo)Logo();
	  if(!blchangeline)
	  {
		if(GetString(argv[i+2])) blResultOK=TRUE;
	  }
    //}
    //if(stricmp(argv[i+1], "/GSTR1")==0) {


		if(blchangeline){
		  if(argc<3) ReadMe();
		  else blParameterOK=TRUE;
		  if(!blNoLogo)Logo();
		  //printf("jlksd");
				FILE* in; 
				char cin;
				int nLines = 0;
				int iN=0;
				char szTemp[10240]={0};
				char szTem[10];
				char strf[50]={0};
				if((in = fopen( argv[i+2], "r"))==NULL) 
				{
					printf("error can not read uplogclient.txt.\npress any key to continue..."); 
					End(255);
				}
				while(!feof(in)) 
				{
					cin=fgetc(in);
					if(cin == '\n')
					{
						iN++;
						continue;
					}

					sprintf(szTem,"%c",cin);
					strcat(szTemp,szTem);
					
				}
				int iTemp=strlen(szTemp);
				szTemp[iTemp-1]='\0';
				//printf("%s\n",szTemp);
				if(blComma)
				{
					int icomma=0,istr=0,ietr=0;
					for(int is=0;is<strlen(szTemp);is++)
					{
						if(szTemp[is]==',')
							icomma++;
						if(icomma==nSmsk)
							istr=is+1;
						if(icomma==nEmsk)
							ietr=is;
						
					}
					int isv=ietr-istr;
					for(int iv=0;iv<isv;iv++)
					{
						strf[iv]=szTemp[++istr];
					}
					strf[isv]='\0';
				}
				printf("%s",strf);
				blResultOK=TRUE;
		  //if(GetString(argv[i+2])) 
		  printf("\n");
		}
    }

    if(stricmp(argv[i+1], "/SET")==0) {
      if(!blNoLogo)Logo();
      if(argc>4) blParameterOK=TRUE;
      else ReadMe();
      if(Set_Environment_Variable(str3,EnvirVar,argv[i+2]/*argv[i+3]*/)) blResultOK=TRUE;
    }
    if(stricmp(argv[i+1], "-sstr")==0) {
      strcpy(str3,argv[i+2]);
      continue;
    }
    if(stricmp(argv[i+1], "-sev")==0) {
      strcpy(EnvirVar,argv[i+2]);
      continue;
    }

    if(stricmp(argv[i+1], "/random") == 0){
	  if(blHEX)
	  {
		  if(argv[i+2]!=NULL)
		  {
			  if(isdigit(*argv[i+2]))
			  {	
				nLength=atoi(argv[i+2]);
			  }
		  }
		  printf("%d",nLength);
			blRandom = TRUE;
			blParameterOK = TRUE;
			if(!blNoLogo)Logo();
			if(blCreateRandom(nLength)) blResultOK = TRUE;
			else ReadMe();
	  }
 //   }

 //   if(stricmp(argv[i+1], "/random1") == 0)
	//{
	  if(blENGDEC)
	  {
		  if(argv[i+2]!=NULL)
		  {
			if(isdigit(*argv[i+2]))
			{
			  nLength=atoi(argv[i+2]);
			}
		  }
		  char Code[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";/*{'0','1','2','3','4','5','6','7','8','9','_','A','B','C',
				 'D','E','F','G','H','I','J','K','L','M','N','O','P','Q',
				 'R','S','T','U','V','W','X','Y','Z'};*/
		  blRandom = TRUE;
		  blParameterOK = TRUE;
		  if(!blNoLogo)Logo();
		  //randomize();
		  char pStr[1024]={0};
		  for(int ii=0; ii<nLength; ii++) {
		//printf("%c",Code[/*random(37)*/rand()%strlen(Code)]);
			  pStr[ii]=Code[rand()%strlen(Code)];
		  }
		  pStr[1024]='\0';
		  if (blow==true)
		  {
			  for(int k=0;k<strlen(pStr);k++) pStr[k]=tolower(pStr[k]);
		  }
		  else
		  {
			  for(int k=0;k<strlen(pStr);k++) pStr[k]=toupper(pStr[k]);
		  }
		  printf("%s\n",pStr);
		  blResultOK = TRUE;
		  End(0);
	  }

    }

    if(stricmp(argv[i+1], "/TIB")==0) {
      if(!blNoLogo)Logo();
      if(argc==6) blParameterOK=TRUE;
      else ReadMe();
      if(WlFileIntoCertainPosition(argv[i+2], argv[i+3], argv[i+4], argv[i+5])) blResultOK=TRUE;
    }
    if(stricmp(argv[i+1], "/R1")==0) {
      if(!blNoLogo)Logo();
      if(argc==4) blParameterOK=TRUE;
      else ReadMe();
      textcolor(15);
      if((f1=fopen(argv[i+2],"r"))==NULL) {
				textbackground(4);
				cprintf("\n\rERROR !! %s Not Found !!\n\r",argv[i+2]);
				End(nErrorLevel);
      }
      for(j=0;j<14;j++){
				ch=fgetc(f1);
				printf("set %s0%d=%c\n",argv[3],j,ch);
//		blResult=TRUE;
      }
    }
    if(stricmp(argv[i+1], "/R2")==0) {
      if(!blNoLogo)Logo();
      if(argc==4) blParameterOK=TRUE;
      else ReadMe();
      if((f1=fopen(argv[i+2],"r"))==NULL) {
				textbackground(4);
				cprintf("\n\rERROR !! %s Not Found !!\n\r",argv[i+2]);
				End(nErrorLevel);
      }
      while(fgets(d,80,f1)!=NULL){
		if(strlen(d)==14 || strlen(d)==15 || strlen(d)==19) printf("set %s=%s",argv[i+3],d);
		else{
		  textbackground(4);
		  cprintf("\n\rERROR !!  %s Length=%d !!\n\r",argv[i+2],strlen(d));
		  End(nErrorLevel);
		}
//      blResult=TRUE;
      }
    }
    if(stricmp(argv[i+1], "/R3")==0) {
      if(!blNoLogo)Logo();
      if(argc==5) blParameterOK=TRUE;
      else ReadMe();
      if((f1=fopen(argv[i+2],"r"))==NULL) {
				textbackground(4);
				cprintf("\n\rERROR !! %s Not Found !!\n\r",argv[i+2]);
				End(nErrorLevel);
      }
      x=atoi(argv[i+3]);
      fseek(f1,x,0);
      printf("set %s%d=",argv[i+4],x);
      for(j=0;j<12;j++){
				d[j]=fgetc(f1);
				if(j==8) d[j]='.';
				printf("%c",d[j]);
//		blResult=TRUE;
      }
      d[15-x]='\0';
      if((f=fopen(d,"w"))==NULL){
				textbackground(4);
				cprintf("\n Write File ERROR !! \n\r");
				End(nErrorLevel);
      }
    }
    if(stricmp(argv[i+1], "/R4")==0){
      if(!blNoLogo)Logo();
      if(argc==5) blParameterOK=TRUE;
      else ReadMe();
      if((f1=fopen(argv[i+2],"r"))==NULL) {
				textbackground(4);
				cprintf("\n\rERROR !! %s Not Found !!\n\r",argv[i+2]);
				End(nErrorLevel);
      }
      fgets(s,100,f1);
      if(strlen(s)==19){
		    printf("set %s=",argv[i+3]);
		    strcpy(d,argv[i+4]);
		    for(j=0;j<20;j++) d[j]=toupper(d[j]);
		    for(i=0;i<12;i++){
		      if(d[i]=='.'){
			      str3[i]=d[i];
			      printf("%c",d[i]);
			      continue;
		      }
		      for(j=0;j<20;j++){
			      if(d[i]==Code[j]){
			      str3[i]=s[j-1];
			      printf("%c",s[j-1]);
			      break;
			   }
			   if(j==19 && d[i]!=Code[j]){
			     textbackground(4);
			     cprintf("\n\n\r%s Name Is ERROR !! \n\r",d);
			     End(nErrorLevel);
			  }
		  }
		  if(i==19){
			str3[i]='\0';
			printf("\0");
		  }
//		  blResult=TRUE;
		}
		if((f=fopen(str3,"w"))==NULL){
		  textbackground(4);
		  cprintf("\n Write File ERROR !! \n\r");
		  End(nErrorLevel);
		}
      }
      else{
				textbackground(4);
				cprintf("\n\rERROR !!  %s Length=%d !!\n\r",argv[i+2],strlen(s));
				End(nErrorLevel);
      }
    }
    if(stricmp(argv[i+1], "/R5")==0) {
      if(!blNoLogo)Logo();
      k=0;
      if(argc==6) blParameterOK=TRUE;
      else ReadMe();
      if((f1=fopen(argv[i+2],"r"))==NULL) {
				textbackground(4);
				cprintf("\n\rERROR !! %s Not Found !!\n\r",argv[i+2]);
				End(nErrorLevel);
      }
      x=atoi(argv[i+3]);
      y=atoi(argv[i+4]);
      fseek(f1,x,0);
      printf("set %s%d=",argv[i+5],x);
      for(j=0;j<12;j++){
				k++;
		  if(y<=9 && k==y){
		    fgetc(f1);
		    j--;
		    continue;
		  } else if(y>9 && k==(y+1)){
		    fgetc(f1);
		    j--;
		  continue;
		}

		if(y<=9 && k==10){
		  d[j]='.';
		  printf("%c",d[j]);
		  continue;
		} else if(y>9 && k==9){
		  d[j]='.';
		  printf("%c",d[j]);
		  continue;
		} else d[j]=fgetc(f1);

		printf("%c",d[j]);
      }
      d[12]='\0';
      if((f=fopen(d,"w"))==NULL){
				textbackground(4);
				cprintf("\n Write File ERROR !! \n\r");
				End(nErrorLevel);
      }
    }
    if(stricmp(argv[i+1], "/R6")==0){
      if(!blNoLogo)Logo();
      k=0;
      if(argc==6) blParameterOK=TRUE;
      else ReadMe();
      if((f1=fopen(argv[i+2],"r"))==NULL) {
				textbackground(4);
				cprintf("\n\rERROR !! %s Not Found !!\n\r",argv[i+2]);
				End(nErrorLevel);
      }
      x=atoi(argv[i+3]);
      y=atoi(argv[i+4]);
      fseek(f1,x,0); //remove first 3 digits
      printf("set %s=",argv[i+5]);

      for(j=0;j<100;j++){
		    if(7<=j && (j<=(7+y-1))) fgetc(f1); //remove middle y digits
		    else{
		      if(k==8){
			      d[k]='.';
			      k++;
		      }
		      if(k==12){
			      d[k]='\0';
			      break;
		      }
		      else{
			      d[k]=fgetc(f1);
			      k++;
		      }
		    }
      }
      printf("%s",d);

      if((f=fopen(d,"w"))==NULL){
				textbackground(4);
				cprintf("\n Write File ERROR !! \n\r");
				End(nErrorLevel);
      }
    }
    if(stricmp(argv[i+1], "/R7")==0) {
      if(!blNoLogo)Logo();
      if(argc==6) blParameterOK=TRUE;
      else ReadMe();
      if((f1=fopen(argv[i+2],"r"))==NULL) {
				textbackground(4);
				cprintf("\n\rERROR !! %s Not Found !!\n\r",argv[i+2]);
				End(nErrorLevel);
      }
      x=atoi(argv[i+3]);
      d[0]=*argv[i+4];
      fseek(f1,x,0);
      printf("set %s%d=",argv[i+5],x);
      printf("%c",d[0]);
      for(j=1;j<9;j++){
				if(j==8) d[j]='.';
				else d[j]=fgetc(f1);
				printf("%c",d[j]);
      }
      for(j=9;j<12;j++){
				d[j]=fgetc(f1);
				printf("%c",d[j]);
      }
      d[16-x]='\0';
      if((f=fopen(d,"w"))==NULL){
				textbackground(4);
				cprintf("\n Write File ERROR !! \n\r");
				End(nErrorLevel);
      }
    }
    if(stricmp(argv[i+1], "/OBWSN")==0){
      if(!blNoLogo)Logo();
      if(argc<3) ReadMe();
      if(blOBWSN(argv[i+2])) End(0);
      End(nErrorLevel);
    }
    //if(stricmp(argv[i+1], "/BigWord") == 0){
    //  if(!blNoLogo) Logo();
    //  if(argv[i+2] == NULL) ReadMe();
    //  blParameterOK = TRUE;
    //  if(!blDisplayBigWord(argv[i+2])) End(nErrorLevel);
    //  blResultOK = TRUE;
    //  break;
    //}
 
      if(stricmp(argv[i+1], "/CopyData")==0){
      if(!blNoLogo) Logo();
	  if(argc<4)ReadMe();
	  blParameterOK=TRUE;
      if((argc<8)||(!blSetStr1)||(!blSetStr2)) /*ReadMe();*/{
	    FILE *ins,*inu; 
		char sin;
		char szTems[10]={0};
		char szTempN[100]={0};
		int iN=0,iM=0;
		if((ins=fopen(argv[i+2], "rb+"))==NULL) 
		{
			printf("error can not open %s.\n",argv[i+2]); 
			End(nErrorLevel);
		}
		while(!feof(ins)) 
		{
			sin=fgetc(ins);
			sprintf(szTems,"%c",sin);
			strcat(szTempN,szTems);
			iN++;
		}
		szTempN[iN]='\0';
		char szTemt[10]={0};
		char szTempM[100]={0};
		if((inu=fopen(argv[i+3], "rb+"))==NULL) 
		{
			printf("error can not open %s.\n",argv[i+3]); 
			End(nErrorLevel);
		}
		while(!feof(inu)) 
		{
			sin=fgetc(inu);
			sprintf(szTemt,"%c",sin);
			strcat(szTempM,szTemt);	
			iM++;
		}
		szTempM[iM]='\0';
		strcat(szTempM,szTempN);
			char sz[100] = {0};
			for (int i = 0; i < strlen(szTempN) - 1; i++)
			{
				sz[i] = szTempN[i];
			}
		if(fputs(sz,inu)==EOF){
			printf("Copy Fail\n");
			End(nErrorLevel);
		}
		else
			blResultOK=TRUE;
	  }
      else 
      if(blCopyData(str4,str5,argv[i+2],argv[i+3])) blResultOK=TRUE;
    }

    if(stricmp(argv[i+1], "/C")==0) {
      if(!blNoLogo)Logo();
	  if(argc<4) ReadMe();
      else if(blFileCompare(argv[i+2], argv[i+3], !blCaseSensitive)) End(0);
      End(nErrorLevel);
    //}

    //if(stricmp(argv[i+1], "/CFStr")==0) {
	  if(blinclude&&blUseAddress){
		  //if(!blNoLogo)Logo();
		  if(argc<4)ReadMe();
		  blParameterOK=TRUE;
		  //if(!blUseAddress)/* ReadMe();*/
		  {
			//   FILE* ins;
			//FILE* inu;
			//char sin;
			//char szTems[10]={0};
			//char szTempN[100]={0};
			//int iN=0,iM=0;
			//if((ins=fopen(argv[i+2], "r"))==NULL) 
			//{
			//	printf("error can not open %s.\n",argv[i+2]); 
			//	End(nErrorLevel);
			//}
			//while(!feof(ins)) 
			//{
			//	sin=fgetc(ins);
			//	sprintf(szTems,"%c",sin);
			//	strcat(szTempN,szTems);
			//	iN++;
			//}
			//szTempN[iN]='\0';
			////printf("%s\n",szTempN);
			//char szTemt[10]={0};
			//char szTempM[100]={0};
			//if((inu=fopen(argv[i+3], "r"))==NULL) 
			//{
			//	printf("error can not open %s.\n",argv[i+3]); 
			//	End(nErrorLevel);
			//}
			//while(!feof(inu)) 
			//{
			//	sin=fgetc(inu);
			//	sprintf(szTemt,"%c",sin);
			//	strcat(szTempM,szTemt);	
			//	iM++;
			//}
			//szTempM[iM]='\0';
			////printf("%s\n",szTempM);
			//char sz[100] = {0};
			//for (int i = 0; i < strlen(szTempN) - 1; i++)
			//{
			//	sz[i] = szTempN[i];
			//}
			////getchar();
			//if(strstr(szTempM,sz)!=0)
			//{
			//		printf("\n  Find Data = %s",sz);
			//		printf("\n Check File = %s\n",argv[i+3]);
			//		cprintf("\n Compare OK !!\n\r");
			//		blResultOK=TRUE;
			//		End(0);
	  //    }
	  //    else{
			//		printf("\n  Find Data = %s",sz);
			//		printf("\n Check File = %s\n",argv[i+3]);
			//		cprintf("\n Compare Error !!\n\r");
			//		fcloseall();
			//		End(nErrorLevel);
	  //    }	
		  }
		  if((f3=fopen(argv[i+2],"r"))==NULL){
					cprintf("\n ERROR !! %s Not Found !!\n\r",argv[i+2]);
					End(nErrorLevel);
		  }
		if((f4=fopen(argv[i+3],"r"))==NULL) {
		cprintf("ERROR !! Can't Open %s !!\n\r",Filename);
		End(nErrorLevel);
		}
		char sina;
		while(!feof(f4)) 
		{
			//fgets(szTemp1,100,ins);
			//iN++;
			sina=fgetc(f4);
			if(sina)
			{
				if((sina == '\n')||(sina == ' '))
				{
					//iN++;
					continue;
				}
			}
			else
			{
				printf("Get String Process Happen Error !!");
				fclose(f4);
				End(nErrorLevel);
			}
			sprintf(szTems,"%c",sina);
			strcat(str2,szTems);	
		}
		//printf("%s\n",str2);
		  //strcpy(str2,argv[i+3]);
		  if(blUseStartLine && blUseEndLine && (dwStartLine==dwStartLine))
			for(k=0;k<dwStartLine+1;k++) fgets(s,100,f3);
		  else fgets(s,100,f3);
		  //printf("%s\n",s);
		  for(k=0;k<strlen(s);k++){
					s[k]=toupper(s[k]);
					str2[k]=toupper(str2[k]);
		  }
		  if(strlen(str2)==0) ReadMe();
		  k=0;
		  for(j=(WORD) dwStartAddress;j<=dwEndAddress;j++){
					s3[k]=s[j];
					k++;
					if(j==dwEndAddress+1) s3[k]='\0';
		  }
		  //printf("%s\n",s3);
		  if(strstr(str2,s3)!=0){
					printf("\n  Find Data = %s",s3);
					printf("\n Check File = %s\n",argv[i+3]);
					cprintf("\n Compare OK !!\n\r");
					blResultOK=TRUE;
		  }
		  else{
					printf("\n  Find Data = %s",s3);
					printf("\n Check File = %s\n",argv[i+3]);
					cprintf("\n Compare Error !!\n\r");
					fcloseall();
					End(nErrorLevel);
		  }
    }
	//continue;
  //}


	 // if(stricmp(argv[i+1], "/CmpData")==0){
	else if(blinclude&&blSetStr1)
	{
      //if(!blNoLogo) Logo();
      if(argc<4) ReadMe();
      //else blParameterOK=TRUE; 
	  blParameterOK=TRUE;
	  if((argc>5)/*&&(blSetStr1)*/){
		 
          if(blCmpData(str4,argv[i+2],argv[i+3])) blResultOK=TRUE;
	  }
	}
	else if(blinclude){
	    FILE* ins;
		FILE* inu;
		char sin;
		char szTems[10]={0};
		char szTempN[100]={0};
		int iN=0,iM=0;
		if((ins=fopen(argv[i+2], "r"))==NULL) 
		{
			printf("error can not open %s.\n",argv[i+2]); 
			End(nErrorLevel);
		}
		while(!feof(ins)) 
		{
			sin=fgetc(ins);
			sprintf(szTems,"%c",sin);
			strcat(szTempN,szTems);
			iN++;
		}
		//szTempN[iN]='\0';
		char szTemt[10]={0};
		char szTempM[100]={0};
		if((inu=fopen(argv[i+3], "r"))==NULL) 
		{
			printf("error can not open %s.\n",argv[i+3]); 
			End(nErrorLevel);
		}
		while(!feof(inu)) 
		{
			sin=fgetc(inu);
			sprintf(szTemt,"%c",sin);
			strcat(szTempM,szTemt);	
			iM++;
		}
		//szTempM[iM]='\0';
		char sz[100] = {0};
		for (int i = 0; i < strlen(szTempN) - 1; i++)
		{
			sz[i] = szTempN[i];
		}
		if(strstr(szTempM,sz)!=0)
		{
			blResultOK=TRUE;
			printf("Match!\n");
			printf("The Line Is ==> %s",szTempN);
		}
		else
			printf("no match sting");
	  }
    }
 }
  fcloseall();
  if(blResultOK && blParameterOK) End(0);
  else if(!blParameterOK) ReadMe();
  End(nErrorLevel);
}
