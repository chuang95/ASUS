// Common Tool Utility, Copyright by Pegatron
//---------------------------------------------------------------------------
/*
-----------------------------------------------------------------------------
PT.exe_Rev1.00: Jul 06, 2009 :Craige
      1.Add /version command to show version.
	  2.Fixed /random and /random1 to get correct length.
	  3.Add /Char2ASC command  to change file content from normal text to ASCII code. 
      4.Add -div <value> parameter for /CSum command, to get remainder of checksum divide by <value>.
      5.Add -L2u parameter for /CSum command, to transform the lower case to the upper case of content.
      6.Add -mask <mask_value> parameter for /CV command, to get the numeric data of file and mask with <mask_data>.
-----------------------------------------------------------------------------
Rev2.32: May 15, 2009: Craige
	  1.Fixed /ChkCha to get correct string from files contains blank and enter.
-----------------------------------------------------------------------------
Rev2.31: Apr 28, 2009: Craige
	  1.Fixed /CSum to calculate .BIN files correctly.
-----------------------------------------------------------------------------
Rev2.30: Apr 20, 2009: Craige
      1.Add -c parameter for /Find command to consider case sensitive.
-----------------------------------------------------------------------------
Rev2.29: Feb 3, 2009: Miracle
      1. Add -d36 parameter for /CSum command, to get remainder of checksum
	 divide by 36 (add by Jackson)
      2. Fixed return code of /CF and the bug when <diff value> is equal to
	 zero (add by Miracle)
-----------------------------------------------------------------------------
Rev2.28: Dec 18, 2008: Craige
  1. Fixed /CF, /CF1, and /H2D to support > / >> command of Dos.
  2. Fixed return code of /CF and /CF1 -diff <diff value>.
-----------------------------------------------------------------------------
Rev2.27: Nov 12, 2008: Craige
  1. Fixed /CF, /CF1, and /H2D, to be no limited length of string for file1 and file2.
  2. Fixed /CV to correct the wrong comparison from the length of string.
-----------------------------------------------------------------------------
Rev2.26: Oct 09, 2008: Jackson
	 1. Add /Random1 command to produce random character
-----------------------------------------------------------------------------
Rev2.25: Jun 05, 2008: Miracle
	 1. Added /CopyData, -str1, -str2 to copy data behind <str1> from
	    file1 to file2.
	 2. Added /CmpData, -str to check if the data behind <str> in file1
	    is also in file2.
-----------------------------------------------------------------------------
Rev2.24: Feb 26, 2008: Brian
	 1. Added new parameter (-nologo) to do not show Pegatron Logo.
-----------------------------------------------------------------------------
Rev2.23: Nov. 23, 2007: Brian
	 1. Added New Command (/CLS) & new parameter -line to check line status.
-----------------------------------------------------------------------------
Rev2.22: Sep. 21, 2007: Brian
	 1. Fixed that using -sl with /C command to make read the error number
	    of lines in both files.
------------------------------------------------------------------------------
Rev2.21: Sep. 13, 2007: Brian
	 1.Fixed -LSB of GSTR / GSTR1 cann't support > / >> command of Dos
-----------------------------------------------------------------------------
Rev2.20: Sep. 07, 2007: Brian
	 1.Added /BigWord <file> Command to display big size number of Hex. or
	 Dec. in File.
-----------------------------------------------------------------------------
Rev2.19: Aug. 24, 2007: Brian
	 1.Added /random command with -lenght parameter to create random number
	 based on 16 with Byte unit.
-------------------------------------------------------------------------------
Rev2.18: Aug. 20, 2007: Brian
	 1. Fixed the String Buffer of GetString Function from 150 to 1024
	 2. added -diff parameter with Command /CV, /CV1, /CF & CF1 for comparing
	    the file in value and user value if it is in difference?
	 3. Modified -sl -el & -ea -sa can be used with -start_comma / -end_comma
	    togother.
-----------------------------------------------------------------------------
Rev2.17: Jul. 23, 2007: Brian
	 1. Mixed -sl, -el & -i parameters with /C Command.
	 2. New Added /CV1 Command compare the floating Data in file with value.
-------------------------------------------------------------------------------
Rev2.16: Jun. 28, 2007: Jackson
	 1. Add /CF1 command to compare two files for hex data
-------------------------------------------------------------------------------
Rev2.15: Apr. 18, 2007: Brian
	 1. Add -start_comma | -end_comma to searching string by comma location
-------------------------------------------------------------------------------
Rev2.14: Mar. 25, 2007: Jackson
	 Add -LSB parameter to specify last bit data for /GStr, /GStr1
-------------------------------------------------------------------------------
Rev2.13: Jan. 25, 2007: Jackson
	 1. Modify /GStr command to cancel change line action
	 2. Add /GStr1 command, there is change line action different from
	    /GStr command
-------------------------------------------------------------------------------
Rev2.12: Oct. 20, 2006: Jackson
	 1. Modify /GStr command to add change line action
	 2. Modify /TStr command to cancel string length limitation
-------------------------------------------------------------------------------
Rev2.11: Jul 24, 2006: Jackson
	 Add /R7 command
-------------------------------------------------------------------------------
Rev2.10: Jan 10, 2006: Jackson
	 Modify /R6 command
-------------------------------------------------------------------------------
Rev2.09: Jan 2, 2006: Jackson
	 Add /R6 command to set environment variable for 25 digits barcode
-------------------------------------------------------------------------------
Rev2.08: Oct 31, 2005: Jackson
	 1. Add -T parameter to transfer file to normal text format for sysinfo.ap
	    file
	 2. Add /Find command to search string from file
-------------------------------------------------------------------------------
Rev2.07: Sep 13, 2005: Jackson
	 1. Add /R5 command to set environment variable for barcode
	 2. Add /OBWSN command to check serial number rule for OBW
	    (PE is Magic_Lue)
-------------------------------------------------------------------------------
Rev2.06: Feb 1, 2005: Jackson
	 1. Enlarge /GSTR matrix size from 100 char. to 150 char.
	 2. Fix /CHKSTR bug
-------------------------------------------------------------------------------
Rev2.05: Dec 29, 2004: Jackson
	 1. Add /R1, /R2, /R3 command copy from scan.exe, editor by Yushih
	 2. Modify /R2 command for 19 bit data
	 3. Add /R4 command to set environment variable and file name for 19
	    bit
-------------------------------------------------------------------------------
Rev2.04: May 11, 2004: Jackson
	 1. Modify /TIB command
-------------------------------------------------------------------------------
Rev2.03: March 23, 2004: Yushih
	 1. ADD /TIB function
-----------------------------------------------------------------------------
Rev2.02: Dec 08, 2003: Max
	 1. /SET option ignore 'toupper' function
-----------------------------------------------------------------------------
Rev2.02: Nov 20, 2003: Jackson
	 1. Add -i parameter for ignoring case-sensitive
-----------------------------------------------------------------------------
Rev2.01: Sep 02, 2003: Jackson
	 1. Add /SET, -sstr, -sev parameters for setting environment variable
-----------------------------------------------------------------------------
Rev2.00: Aug 15, 2003: Jackson
	 1. ASUSTool.exe Rev1.15 --> AT.exe Rev2.00
	 2. First Release AT.exe
//---------------------------------------------------------------------------
*/
#include <math.h>
#include "PT.h"
#include "global.h"

// modify this every time
#define sProgramDescription "Pegatron Tool Utility"
#define sBuildDate "2009-07-10"
#define sRevision "1.00"

//---------------------------------------------------------------------------
void Logo(void)
{
  if(blLogo == FALSE)
    return;

  if(blClearScreen)
    pega.cls();

  // print title
  pega.PrintStr(1, 1, sProgramDescription, 0, 0x07);
  pega.PrintStr(1, 2, "Copyright by Pegatron, Build Date:" sBuildDate " Rev" sRevision, 0, 0x07);
  pega.PrintStr(0, 2, "Diagnostics ", LOC_RIGHT, 0x08);	
  pega.PrintCh(1, 3, '=', 0x07, 80);

  gotoxy(1, 4);
  return;
}
//--------------------------------------------------------------------------
void ReadMe(void)
{
  for(;;)
  {
    Logo();
    printf("PT.EXE <-Sw1> <...> [/Command1] [...] ... <Parameter1> <...> ...\n");
    printf("  /FS <file> <value>: Get the file size(A) & compare with value(B)\n");
    printf("  /GMT: Transfer now date & time to GMT(seconds)\n");
    printf("  /CF  <file1> <file2>: Compare <file1> and <file2> for Dec. data\n");
    printf("  /CF1 <file1> <file2>: Compare <file1> and <file2> for Hex. data\n");
    printf("  /CV  <file> <value>: Compare Dec|Hex  value(A) in file with value(B)\n");
	printf("    -mask <mask_data>: Get the numeric data and mask with <mask_data> for /CV\n");
    printf("  /CV1 <file> <value>: Compare floating value(A) in file with value(B)\n");
    printf("    if A > B return code=2; if A = B return code=1; if A < B return code=0\n");
    printf("    -diff <value>: diff value (C) in value (A) and value (B)\n");
    printf("    if A-B > C return code=2\n");
    printf("    if A-B = C return code=1\n");
    printf("    if A-B < C return code=0\n");
    printf("  /ChkChar <file> <bit> <char>: Read a data from file and check with char\n");
    printf("  /Find <file> <string>: Search string from file\n");
	printf("    -c: Case sensitive for /Find\n");
    printf("    -t: Transfer file to normal text format for /ChkStr, /Find\n");
    printf("\nReturn Code: OK(0), ERROR(-1)");
    textcolor(15);
    textbackground(1);
    cprintf("\n\rESC");
    textattr(0x07);
    printf(": exit this help");
    pega.PrintStr(1,24,"... Press any key to next page ...",0,0x07);
    if(getch()==0x1B){
      textbackground(0);
      cprintf("\r                                                           ");
      break;
    }
    clrscr();
    Logo();
    printf("  /TStr <file> <s1> <s2>: Replace string s1 by s2 for file, save to update.txt\n");
    printf("  /OBWSN <file>: Check OBW Serial Number rule\n");
    printf("  /CB <fn1> <fn2> ... <fnN> : Create N batch & pro files base on N ini files\n");
    printf("    -chkbc <N>: Scan barcode N times and compare, N must >= 2\n");
    printf("    -del <M>: Delete Mth bit barcode and change 90 code to 80 code\n");
    printf("    -p <string>: Set the prompt string\n");
    printf("  /CBC <fn1>...<fnN>: Create batch & pro file by comparing barcode & ini file\n");
    printf("  /SB <data_file> <ini_file>: Set 90 barcode environment variable\n");
    printf("  /RC <file> <bit>: Return character(0~9,A~Z) code\n");
    printf("  /SET <f1> <f2>: Set environment variable base on f1, then write to f2\n");
    printf("                  where f1: input file  ,  f2: output file\n");
    printf("    -sstr <str>: Search string\n");
    printf("    -sev <str>: Set environment variable base on string\n");
    printf("  /Random : Create Random Number based on 16\n");
    printf("    -length <value> : Set the length <value> of Random number in Byte Unit\n");
    printf("  /Random1 : Produce random character\n");
    printf("    -length <value> : Set random character length\n");
    printf("\nReturn Code: OK(0), ERROR(-1)");
    textcolor(15);
    textbackground(1);
    cprintf("\n\rESC");
    textattr(0x07);
    printf(": exit this help");
    pega.PrintStr(1,24,"... Press any key to next page ...",0,0x07);
    if(getch()==0x1B){
      textbackground(0);
      cprintf("\r                                                           ");
      break;
    }
    clrscr();
    Logo();
    printf("  /D <file> <x> <y> <attr>: Display txt file\n");
    printf("  /S : Scan barcode and save to barcode.dat\n");
    printf("  /TIB <F1.BIN> <F2.TXT> <F.BIN> <place>: Write F2.TXT into certain position\n");
    printf("					  in F1.BIN, and save as F.BIN.\n");
    printf("  /TBC <file>: Transfer barcode format\n");
    printf("  /C <fn1> <fn2>: File(fn1 & fn2) compare content, default range is 1 to end\n");
    printf("    -i: Ignore case-sensitive for /C\n");
    printf("  /ChkStr <file> <string>: Read data from file and check with string\n");
    printf("  /H2D <file>: Transfer Hex to Dec value\n");
    printf("  /CSum <fn> <checksum>: Calculate the checksum of file(fn)\n");
    printf("    -d36: Divide by 36\n");
	printf("    -div <value>: Divide by value\n");
	printf("    -L2u: Transform the lower case to the upper case for /CSum -d36|-div\n");	
    printf("  /GStr|/GStr1 <fn>: Get string from file, /GStr1 will change line\n");
    printf("    -LSB <n>: Specify last <n> bit data for /GStr|/GStr1\n");
    printf("    -start_comma | -end_comma <n>: Set the range of searching string by comma\n");
    printf("    -sl|-el <l>: Set the start|end line of file for /C, /CSum, /GStr\n");
    printf("    -sa|-ea <n>: Set start|end byte of file for /C,/CSum,/ChkStr,/H2D,/GStr\n");
    printf("\nReturn Code: OK(0), ERROR(-1)");
    textcolor(15);
    textbackground(1);
    cprintf("\n\rESC");
    textattr(0x07);
    printf(": exit this help");
    pega.PrintStr(1,24,"... Press any key to next page ...",0,0x07);
    if(getch()==0x1B){
      textbackground(0);
      cprintf("\r                                                           ");
      break;
    }
    clrscr();
    Logo();
    printf("  /R1|/R2 <fn> <char>: Set environment variable (for 14 & 15 bit)\n");
    printf("  /R3 <fn> <bit> <char>: Set environment variable and file name (for 14,15 bit)\n");
    printf("  /R4 <fn1> <char> <fn2>: Set environment variable and file name (for 19 bit)\n");
    printf("  /R5|/R6 <fn> <bit1> <bit2> <env_var>: Set environment variable for barcode\n");
    printf("  /R7 <fn> <bit> <char1> <char2>: Set environment variable and file name\n");
    printf("  /BigWord <file>: Display the Hex. or Dec. number in file with Big Size\n");
    printf("  /CLS <file> : Show each Line status in a File\n");
    printf("    -line <n> : Set the estimated number of line in a file\n");
    printf("    -nologo: Do not show Pegatron Logo, for all commands.\n");
    printf("  /CopyData <file1> <file2>: Copy data from file1 to file2\n");
    printf("    -str1 <str>: Copy data behind <str>\n");
    printf("    -str2 <str>: Paste data behind <str>\n");
    printf("  /CmpData <file1> <file2>: Check if data in file1 is also in file2\n");
    printf("    -str <str>: Get data behind <str> in file1\n");
	printf("  /Char2ASC <file>: Change content of file from normal text to ASCII code.\n");
    printf("\nReturn Code: OK(0), ERROR(-1)");
    textcolor(15);
    textbackground(1);
    cprintf("\n\rESC");
    textattr(0x07);
    printf(": exit this help");
    pega.PrintStr(1,24,"... Press any key to first page ...",0,0x07);
    if(getch()==0x1B){
      textbackground(0);
      cprintf("\r                                                           ");
      break;
    }
  }
  End(nErrorLevel);
}
//--------------------------------------------------------------------------
void End(int ReturnCode)
{
  char buf[80];

  if(blLogo)
  {
    sprintf(buf, "Return_Code=%d", ReturnCode);
    pega.PrintStr(1, 25,buf, 0, 0x08);
    gotoxy(1, 23);
  }
  if(blNoDisplay)
  {
    pega.RestoreScreen(0);
    pega.RestoreXY();
  }

  pega.CursorOn();
  exit(ReturnCode);
}
int atoh(const char* pStr)
{
  int ah = 0;
  unsigned int sl = strlen(pStr);
  for(unsigned int p = 0 ; p < sl ; p++){
    for(int pp = 0 ; pp <16 ; pp++){ 
      if((pStr[sl - 1 - p]) == Code[pp]) break;
    }
    ah = ah + pp * (int) pow(16, p);
  }
  return ah;
}


//--------------------------------------------------------------------------
void main(int argc, char *argv[])
{
  FILE  *f1,*f2,*fBar,*f3,*f4,*fBar2,*f7,*f,*ff;
  int   i,j,ReadBit,ChkTimes=0,Del_Bit=0,k,m,n,p,BitNo=0,x,y;
  char  str[255],*ptr,ch,**iniFile,BarCode[100],s[100],d[80]="\0",sINI1[80]="",str4[50],str5[50];
  char File[50],str1[50],str2[50];
  char str3[80],EnvirVar[80];


  Boolean blNologo = FALSE;
  Boolean blParameterOK=FALSE;
  Boolean blResultOK=FALSE;
  Boolean blPrompt=FALSE;
  Boolean blCaseSensitive=FALSE;
  // begin handle the user interface
  for(i = 0; i < (argc - 1); i++)
  {
    if(stricmp(argv[i+1] , "-c") == 0)
    {
      blCaseSensitive=TRUE;
      continue;
    }
    if(stricmp(argv[i+1], "-nologo") ==0 ||
      stricmp(argv[i+1], "-nl") == 0)
    {
      blNologo = TRUE;
      blLogo = FALSE;
      continue;
    }

    if(stricmp(argv[i + 1], "-nc") == 0)
    {
      blClearScreen = FALSE;
      continue;
    }

	if(stricmp(argv[i + 1], "-erv") == 0) 
	{
      if(argv[i + 2]!=NULL)
	  {
	    if(!isdigit(*argv[i+2]))
		{
		  blParameterOK = FALSE;
		  break;
		}
		nErrorLevel= atoi(argv[i + 2]);
		if(nErrorLevel>255||nErrorLevel<-1)
		{
		  blParameterOK = FALSE;
		  nErrorLevel=-1;
	      break;
		}
      }
      continue;
	}

    if(stricmp(argv[i + 1], "-nd") == 0)
    {
      blNoDisplay = TRUE;
      pega.blSaveScreen(0);
      pega.SaveXY();
      continue;
    }
	if(stricmp(argv[i + 1], "-L2u") == 0)
    {
      blL2u = TRUE;
      continue;
    }
    if(stricmp(argv[i+1] , "-diff")==0)
    {
      if(argv[i+2]!=NULL)
      {
		strcpy(szStr,argv[i+2]);
		nDiffValue = (float) atof(argv[i+2]);
		blDiff=TRUE;
      }
    }
    if(stricmp(argv[i+1], "-Length") == 0)
	{
      if(!isdigit(*argv[i+2]))
	  {
		blParameterOK = FALSE;
		break;
      }
      nLength = atoi(argv[i+2]);
      blParameterOK = TRUE;
      continue;
    }
	if(stricmp(argv[i+1], "-div") == 0)
	{
      if(!isdigit(*argv[i+2]))
	  {
		blParameterOK = FALSE;
		break;
      }
      idiv = atoi(argv[i+2]);
	  if(idiv>36||idiv<1)
	  {
		  if(!blNologo)Logo();
		  printf("Divide Value out of scope!");
		  blParameterOK = FALSE;
		  End(nErrorLevel);
	  }
      blParameterOK = TRUE;
	  bldiv=TRUE;
      continue;
    }
	if(stricmp(argv[i+1], "-mask") == 0)
	{
      if(!isdigit(*argv[i+2]))
	  {
		blParameterOK = FALSE;
		break;
      }
      imask = atoh(argv[i+2]);
      blParameterOK = TRUE;
	  blmask=TRUE;
      continue;
    }
  }

  for(i=0; i<(argc-1); i++)
  {
    if(stricmp(argv[i+1], "?")==0  ||\
       stricmp(argv[i+1], "/?")==0 ||\
       stricmp(argv[i+1], "/h")==0 ||\
       stricmp(argv[i+1], "/help")==0) {
	 blParameterOK=TRUE;
	 Logo();
	 ReadMe();
	 continue;
    }
	if(stricmp(argv[i + 1], "/version")  ==  0 )
	{
		if(!blNologo)Logo();
		blParameterOK = TRUE;
		printf("%s\n",sRevision);
		continue;
	}

    if (stricmp(argv[i+1] , "/CLS") == 0) 
	{
      if (argv[i+2] == NULL) break;
      blParameterOK = TRUE;

      if(!blNologo) Logo();
      if (blCheckLines (argv[i+2])) blResultOK = TRUE;
      break;
    }

    if (stricmp(argv[i+1] , "-line") == 0) 
	{
      if (argv[i+2] == NULL) break;
      blParameterOK = TRUE;
      nLine = atoi(argv[i+2]);
      if (nLine == 0) ReadMe();
      continue;
    }

    if(stricmp(argv[i+1], "/GMT")==0) 
	{
      blParameterOK=TRUE;
      blResultOK=TRUE;

      if(!blNologo) Logo();
      printf("%ld\n", dwTransferNowDateTime2GMT());
      continue;
    }

    if(stricmp(argv[i+1], "/CF")==0) 
	{
	  if(!blNologo)
	  Logo();
	  if(argc>(i+3))
	  {
        blParameterOK=TRUE;
		if((f1=fopen(argv[i+2],"r+"))!=NULL)
		{
		  char dwValue1[1024]={0};
		  fscanf(f1, "%s", dwValue1);
		  fclose(f1);
		  if((f2=fopen(argv[i+3],"r+"))!=NULL)
		  {
		    char dwValue2[1024]={0};
			fscanf(f2, "%s", dwValue2);
			fclose(f2);
			cprintf("value in file(%s) = %s\n\r", argv[i+2], dwValue1);
			cprintf("value in file(%s) = %s\n\r", argv[i+3], dwValue2);
			if(blDiff)
				cprintf("diff = %s\n\r",szStr);
			DCF(dwValue1,dwValue2);
	      } 
          else cprintf("open %s ERROR...\n\r", argv[i+3]);
        } 
        else cprintf("open %s ERROR...\n\r", argv[i+2]);
      }
      continue;
    }

    if(stricmp(argv[i+1], "/CF1")==0) {
      if(!blNologo) Logo();
      if(argc>(i+3)) {
	blParameterOK=TRUE;
	if((f1=fopen(argv[i+2],"r+"))!=NULL) {
		char dwValue1[1024]={0};
	  fscanf(f1, "%s", dwValue1);
	  fclose(f1);
	  if((f2=fopen(argv[i+3],"r+"))!=NULL) {
		  char dwValue2[1024]={0};
	    fscanf(f2, "%s", dwValue2);
	    fclose(f2);
	    cprintf("value in file(%s) = %s\n\r", argv[i+2], dwValue1);
		cprintf("value in file(%s) = %s\n\r", argv[i+3], dwValue2);
		if(blDiff)
			cprintf("diff = %s\n\r",szStr);
		HCF(dwValue1,dwValue2);
	  } else cprintf("open %s ERROR...\n\r", argv[i+3]);
	} else cprintf("open %s ERROR...\n\r", argv[i+2]);
      }
      continue;
    }
    if(stricmp(argv[i+1], "/CV")==0) {
      if(!blNologo) Logo();
      if(argc>(i+3))
      {
		blParameterOK=TRUE;
		blResultOK = blCompareValueInFile(argv[i+2], argv[i+3]);
      }
      continue;
    }
    if(stricmp(argv[i+1], "/CV1") == 0) {
      if(!blNologo) Logo();
      if(argc > (i+3))
      {
		blParameterOK = TRUE;
		blResultOK = blCompareValueInFile1(argv[i+2], argv[i+3]);
      }
      continue;
    }
    if(stricmp(argv[i+1], "/FS")==0) {
      if(!blNologo) Logo();
      if(argc>(i+2)) {
	blParameterOK=TRUE;


	uLong dwValue1, dwValue2;

	dwValue1=dwGetFileSize(argv[i+2]);
	dwValue2=atol(argv[i+3]);

	cprintf("size of file(%s) = %ld\n\r", argv[i+2], dwValue1);
	if(argc>(i+3)) {
	  cprintf("value in parameter = %ld\n\r", dwValue2);
	  if(dwValue1>dwValue2) {
	    cprintf("%ld > %ld\n\r", dwValue1, dwValue2);
	    End(2);
	  }
	  if(dwValue1==dwValue2) {
	    cprintf("%ld = %ld\n\r", dwValue1, dwValue2);
	    End(1);
	  }
	  if(dwValue1<dwValue2) {
	    cprintf("%ld <% ld\n\r", dwValue1, dwValue2);
	    End(0);
	  }
	} else End(nErrorLevel);
      }
      continue;
    }
    if(stricmp(argv[i+1], "/D")==0) {
      blParameterOK=TRUE;
      if(argc==(i+3)) {
	pega.cls();
	DisplayTxtFile(argv[i+2], 1, 1, 0x07);
      } else if(argc==(i+5)) {
	int x, y;
	x=atoi(argv[i+3]); if(x<1 || x>80) x=1;
	y=atoi(argv[i+4]); if(y<1 || y>24) y=1;
	DisplayTxtFile(argv[i+2], x, y, 0x07);
      } else if(argc==(i+6)) {
	int x, y;
	uChar attr;
	x=atoi(argv[i+3]); if(x<1 || x>80) x=1;
	y=atoi(argv[i+4]); if(y<1 || y>24) y=1;
	attr=pega.atoh(argv[i+5]);
	DisplayTxtFile(argv[i+2], x, y, attr);
      } else break;
      gotoxy(1,24);
      exit(nErrorLevel);
    }
    if(stricmp(argv[i+1], "-SA")==0) {
      blUseAddress=TRUE;
      blUseStartAddress=TRUE;
      dwStartAddress=atol(argv[i+2])-1;
      continue;
    }
    if(stricmp(argv[i+1], "-EA")==0) {
      blUseAddress=TRUE;
      blUseEndAddress=TRUE;
      dwEndAddress=atol(argv[i+2])-1;
      continue;
    }
    if(stricmp(argv[i+1], "-SL")==0) {
      blUseLine=TRUE;
      blUseStartLine=TRUE;
      dwStartLine=atol(argv[i+2])-1;
      continue;
    }
    if(stricmp(argv[i+1], "-EL")==0) {
      blUseLine=TRUE;
      blUseEndLine=TRUE;
      dwEndLine=atol(argv[i+2])-1;
      continue;
    }
    if(stricmp(argv[i+1], "/C")==0) {
      if(!blNologo) Logo();


      if(blFileCompare(argv[i+2], argv[i+3], blignore)) End(0);
      End(nErrorLevel);
    }
    if(stricmp(argv[i+1], "-i")==0) {
      blignore=TRUE;
      continue;
    }
    if(stricmp(argv[i+1], "/CSum")==0) {
      if(!blNologo) Logo();


      if(blFileCheckSum(argv[i+2], pega.atoh(argv[i+3]))) End(0);
      End(nErrorLevel);
    }
    if(stricmp(argv[i+1], "-d36")==0) {
      blDivideBy36=TRUE;
      continue;
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
      if(!blNologo) Logo();


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
      if(!blNologo) Logo();


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
      if(!blNologo) Logo();


      ReadBit=atoi(argv[i+3]);
      ch=*argv[i+4];
      blParameterOK=TRUE;
      if(CheckChar(argv[i+2],ReadBit,ch)) blResultOK=TRUE;
    }
    if(stricmp(argv[i+1], "/TBC")==0) {
      if(!blNologo) Logo();


      blParameterOK=TRUE;
      if(Transfer_Barcode_Format(Prmpt)) blResultOK=TRUE;
    }
    if(stricmp(argv[i+1], "/S")==0) {
      if(!blNologo) Logo();


      blParameterOK=TRUE;
      if((fBar=fopen("barcode.dat","w"))==NULL) {
	cprintf("\n ERROR !! Can't Open Barcode.dat !!\n\r");
	fcloseall();
	End(nErrorLevel);
      }
      if(blPrompt) printf(" %s : ",Prmpt);
      else printf(" Please Scan Barcode : ");
      pega.CursorOn();
      scanf("%s",BarCode);
      for(j=0;j<strlen(BarCode);j++) BarCode[j]=toupper(BarCode[j]);
      fprintf(fBar,"%s",BarCode);
      fclose(fBar);
      blResultOK=TRUE;
      continue;
    }
    if(stricmp(argv[i+1], "/ChkStr")==0) {
      if(!blNologo) Logo();


      if(!blUseAddress) ReadMe();
      blParameterOK=TRUE;
      blResultOK = blCheckString(argv[i+2], argv[i+3]);
      continue;
    }
    if(stricmp(argv[i+1], "/Find")==0) {
      char  s1[260]="";
      blParameterOK=TRUE;


      if(!blNologo) Logo();
      if((f3=fopen(argv[i+2],"r"))==NULL){
	cprintf("\n ERROR !! %s Not Found !!\n\r",argv[i+2]);
	fcloseall();
	End(nErrorLevel);
      }
      if(blTransfer){
	sprintf(sINI1, "III.iii");
	CP(argv[i+2], sINI1);
	fclose(f3);
	if((f3=fopen("III.iii","r"))==NULL){
	  cprintf("\n ... ERROR !! ... III.iii Not Found !! ... \n\r");
	  fcloseall();
	  End(nErrorLevel);
	}
      }
      strcpy(str2,argv[i+3]);
	  if (blCaseSensitive==FALSE)
	  {
		for(k=0;k<strlen(str2);k++) str2[k]=toupper(str2[k]);
	  }
      printf("\nSearch Data = %s\n\n",str2);
      printf("The Result Is : \n");

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
    if(stricmp(argv[i+1], "/BigWord") == 0){
      if(!blNologo) Logo();


      if(argv[i+2] == NULL) ReadMe();
      blParameterOK = TRUE;
      if(!blDisplayBigWord(argv[i+2])) End(nErrorLevel);
      blResultOK = TRUE;
      break;
    }
    if(stricmp(argv[i+1], "/H2D")==0)
    {
      if(!blNologo) Logo();


      if(argc>(i+2))
      {
	blParameterOK=TRUE;
	blResultOK = blTransferHex2Dec(argv[i+2]);
      }
      continue;
    }
    if(stricmp(argv[i+1], "/RC")==0) {
      if(!blNologo) Logo();
      blParameterOK=TRUE;


      if((f=fopen(argv[i+2],"r"))==NULL){
	cprintf("\n ERROR !! %s Not Found !!\n\r",argv[i+2]);
	fcloseall();
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
      if(!blNologo) Logo();


      if(argc>(i+3)) blParameterOK=TRUE;
      else ReadMe();
      if(Set_Barcode_Environment(argv[i+2],argv[i+3])) blResultOK=TRUE;
    }
    if(stricmp(argv[i+1], "/TSTR")==0) {
      if(!blNologo) Logo();

      if(argc==(i+5)) blParameterOK=TRUE;
      else ReadMe();
      if(Transfer_String(argv[i+2],argv[i+3],argv[i+4])) blResultOK=TRUE;
    }

    if(stricmp(argv[i+1], "-start_comma") == 0) { // start number of searching by comma
      blComma = TRUE;
      nSmsk = atoi(argv[i+2]);
      continue;
    }
    if(stricmp(argv[i+1], "-end_comma") == 0) {   // end number of searching by comma
      blComma = TRUE;
      nEmsk = atoi(argv[i+2]);
      continue;
    }

    if(stricmp(argv[i+1], "/GSTR")==0) {
      if(argc<3) ReadMe();
      else blParameterOK=TRUE;


      if(!blNologo) Logo();
      if(GetString(argv[i+2])) blResultOK=TRUE;
    }

    if(stricmp(argv[i+1], "/GSTR1")==0) {
      if(argc<3) ReadMe();
      else blParameterOK=TRUE;


      if(!blNologo) Logo();
      if(GetString(argv[i+2])) blResultOK=TRUE;
      printf("\n");
    }
    if(stricmp(argv[i+1], "-LSB")==0) {
      blLastBit=TRUE;
      LastBit=atoi(argv[i+2]);
      continue;
    }

    if(stricmp(argv[i+1], "/SET")==0) {
      if(!blNologo) Logo();
      if(argc>5) blParameterOK=TRUE;
      else ReadMe();


      if(Set_Environment_Variable(str3,EnvirVar,argv[i+2],argv[i+3])) blResultOK=TRUE;
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
      blRandom = TRUE;
      blParameterOK = TRUE;


      if(!blNologo) Logo();
      if(blCreateRandom(nLength)) blResultOK = TRUE;
      else ReadMe();
    }
    if(stricmp(argv[i+1], "/random1") == 0){
      char Code[37]={'0','1','2','3','4','5','6','7','8','9','_','A','B','C',
		     'D','E','F','G','H','I','J','K','L','M','N','O','P','Q',
		     'R','S','T','U','V','W','X','Y','Z'};
      blRandom = TRUE;
      blParameterOK = TRUE;


      if(!blNologo) Logo();
      randomize();
      for(int ii=0; ii<nLength; ii++) {
	printf("%c",Code[random(37)]);
      }
      printf("\0");
      blResultOK = TRUE;
      End(0);
    }
    if(stricmp(argv[i+1], "/TIB")==0) {
      if(!blNologo) Logo();
      if(argc==6) blParameterOK=TRUE;
      else ReadMe();


      if(WlFileIntoCertainPosition(argv[i+2], argv[i+3], argv[i+4], argv[i+5])) blResultOK=TRUE;
    }
    if(stricmp(argv[i+1], "/R1")==0) {
      if(!blNologo) Logo();
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
      }
    }
    if(stricmp(argv[i+1], "/R2")==0) {
      if(!blNologo) Logo();
      if(argc==4) blParameterOK=TRUE;
      else ReadMe();


      if((f1=fopen(argv[i+2],"r"))==NULL) {
	textbackground(4);
	cprintf("\n\rERROR !! %s Not Found !!\n\r",argv[i+2]);
	End(nErrorLevel);
      }
      while(fgets(d,80,f1)!=NULL){
	if(strlen(d)==14 || strlen(d)==15 || strlen(d)==19)
	  printf("set %s=%s",argv[i+3],d);
	else{
	  textbackground(4);
	  cprintf("\n\rERROR !!  %s Length=%d !!\n\r",argv[i+2],strlen(d));
	  End(nErrorLevel);
	}
      }
    }
    if(stricmp(argv[i+1], "/R3")==0) {
      if(!blNologo) Logo();
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
      }
      d[15-x]='\0';
      if((f=fopen(d,"w"))==NULL){
	textbackground(4);
	cprintf("\n Write File ERROR !! \n\r");
	End(nErrorLevel);
      }
    }
    if(stricmp(argv[i+1], "/R4")==0){
      if(!blNologo) Logo();
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
      if(!blNologo) Logo();
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
      if(!blNologo) Logo();
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
      if(!blNologo) Logo();
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
      if(!blNologo) Logo();
      if(argc<3) ReadMe();


      if(blOBWSN(argv[i+2])) End(0);
      End(nErrorLevel);
    }
    if(stricmp(argv[i+1], "/CopyData")==0){
      if(!blNologo) Logo();

      if((argc<8)||(!blSetStr1)||(!blSetStr2)) ReadMe();
      else blParameterOK=TRUE;
      if(blCopyData(str4,str5,argv[i+2],argv[i+3])) blResultOK=TRUE;
    }
    if(stricmp(argv[i+1], "-str1")==0){
      strcpy(str4,argv[i+2]);
      blSetStr1=TRUE;
      continue;
    }
    if(stricmp(argv[i+1], "-str2")==0){
      strcpy(str5,argv[i+2]);
      blSetStr2=TRUE;
      continue;
    }
    if(stricmp(argv[i+1], "/CmpData")==0){
      if(!blNologo) Logo();
      
      if((argc<6)||(!blSetStr1)) ReadMe();
      else blParameterOK=TRUE;
      if(blCmpData(str4,argv[i+2],argv[i+3])) blResultOK=TRUE;
    }
    if(stricmp(argv[i+1], "/Char2ASC")==0){
      if(!blNologo) Logo();
      
      if((argc<2)) ReadMe();
      else blParameterOK=TRUE;
	  FILE *fASC;
	  char szASC[100]={0};
      if((fASC=fopen(argv[i+2],"r"))==NULL) 
	  {
	    textbackground(4);
	    cprintf("\n\rERROR !! %s Not Found !!\n\r",argv[i+2]);
	    End(nErrorLevel);
	  }
	  fgets(szASC,100,fASC);
	  int len=strlen(szASC);
	  if(szASC[len-1]='\n')
		  szASC[len-1]='\0';
	  for(int iASC=0;iASC<strlen(szASC);iASC++)
	  {
	    printf("%X",szASC[iASC]);
	  }
    }
    if(stricmp(argv[i+1], "-str")==0){
      strcpy(str4,argv[i+2]);
      blSetStr1=TRUE;
      continue;
    }
  }
  fcloseall();
  if(blResultOK && blParameterOK) End(0);
  else if(!blParameterOK) ReadMe();
  End(nErrorLevel);
}
