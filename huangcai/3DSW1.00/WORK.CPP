#include "video.h"
#include "Extern.h"


struct
{
 char  VESASignature[4];        /* 'VESA' 4 byte signature 4 */
 short VESAVersion; 		/* VBE version number 2 */
 char far *OEMStringPtr; 	/* Pointer to OEM string 4*/
 long  Capabilities; 		/* Capabilities of video card 4*/
 unsigned far *VideoModePtr; 	/* Pointer to supported modes 4*/
 short TotalMemory; 		/* Number of 64kb memory blocks 2*/

 short OEMSoftwareRev; 		/* VBE version number 2 */
 char far *OEMVendorNamePtr; 	/* Pointer to supported modes 4*/
 char far *OEMProductNamePtr; 	/* Pointer to supported modes 4*/
 char far *OEMProductRevPtr; 	/* Pointer to supported modes 4*/

// char  reserved[236]; 		/* Pad to 256 byte block size */
 char  reserved[222]; 		/* Pad to 256 byte block size */
 char  reserved1[256]; 		/* Pad to 256 byte block size */
} VbeInfoBlock;  		/* SuperVGA mode information block */

struct
{
 unsigned short ModeAttributes;  /* Mode attributes */
 unsigned char WinAAttributes; 	 /* Window A attributes */
 unsigned char WinBAttributes; 	 /* Window B attributes */
 unsigned short WinGranularity;  /* Window granularity in k */
 unsigned short WinSize; 	 /* Window size in k */
 unsigned short WinASegment; 	 /* Window A segment */
 unsigned short WinBSegment; 	 /* Window B segment */
 void (far *WinFuncPtr)(void); 	 /* Pointer to window function */
 unsigned short BytesPerScanLine;/* Bytes per scanline */
 unsigned short XResolution; 	 /* Horizontal resolution */
 unsigned short YResolution; 	 /* Vertical resolution */
 unsigned char XCharSize; 	 /* Character cell width */
 unsigned char YCharSize; 	 /* Character cell height */
 unsigned char NumberOfPlanes; 	 /* Number of memory planes */
 unsigned char BitsPerPixel; 	 /* Bits per pixel */
 unsigned char NumberOfBanks; 	 /* Number of CGA style banks */
 unsigned char MemoryModel; 	 /* Memory model type */
 unsigned char BankSize; 	 /* Size of CGA style banks */
 unsigned char NumberOfImagePages; /* Number of images pages */
 unsigned char res1; 		 /* Reserved */
 unsigned char RedMaskSize; 	 /* Size of direct color red mask */
 unsigned char RedFieldPosition; /* Bit posn of lsb of red mask */
 unsigned char GreenMaskSize; 	 /* Size of direct color green mask */
 unsigned char GreenFieldPosition; /* Bit posn of lsb of green mask */
 unsigned char BlueMaskSize; 	 /* Size of direct color blue mask */
 unsigned char BlueFieldPosition;/* Bit posn of lsb of blue mask */
 unsigned char RsvdMaskSize; 	 /* Size of direct color res mask */
 unsigned char RsvdFieldPosition;/* Bit posn of lsb of res mask */
 unsigned char DirectColorModeInfo; /* Direct color mode attributes */
 void (far *PhyBasePtr)(void); 	 /* Pointer to window function */
 unsigned char res2[212]; 	/* Pad to 256 byte block size */
} ModeInfoBlock;


//  DDC define struct is below
/*
struct {
 uChar Header[8];
 uChar ManufacturerName[2];
 uChar ProductCode[2];
 uChar SerialNumber[4];
 uChar WeekOfManufacture;
 uChar YearOfManufacture;
 uChar EDIDVersion;
 uChar EDIDRevision;
 uChar VideoInputDefinition;
 uChar MaxHorizontalImageSize;
 uChar MaxVerticalImageSize;
 uChar DisplayTransferChar;
 uChar FeatureSupport;
 uChar RedGreenLowBits;
 uChar BlueWhiteLowBits;
 uChar RedX;
 uChar RedY;
 uChar GreenX;
 uChar GreenY;
 uChar BlueX;
 uChar BlueY;
 uChar WhiteX;
 uChar WhiteY;
 uChar EstablishedTimings[3];
 uChar StandardTimingID[16];
 uChar DetailedTimingDescriptions[72];
 uChar ExtensionFlag;
 uChar CheckSum;
} EDIDInfoBlock128;

struct {
 uChar EDIDStructureVersion;
 uChar ManufacturerName[2];
 uChar ProductCode[2];
 uChar WeekOfManufacture;
 uChar YearOfManufacture[2];
 uChar ManufacturerString[32];
 uChar SerialNumber[16];
 uChar reserved[8];
 uChar PhysicalInterfaceType;
 uChar VideoInterfaceType;
 uChar InterfaceDataFormat[8];
 uChar InterfaceColor[5];
 uChar DisplayTechnologyType;
 uChar MajorDisplayChar;
 uChar FeaturesSupport;
 uChar DisplayResponseTime[2];
 uChar DisplayTransferChar[4];
 uChar MaxLuminanceOffset[4];
 uChar ColorimetryWhitePoint[20];
 uChar MaxImageSize[4];
 uChar MaxAddressibility[4];
 uChar DotPixelPitch[2];
 uChar reserved1;
 uChar GTFSupportInfo;
 uChar MapOfTimingInfo[2];
 uChar LuminanceTableTimingDescriptions[127];
 uChar CheckSum;
} EDIDInfoBlock256;
*/
uChar EDIDBuf[256];

//typedef enum
//{
// memPL = 3, 	/* Planar memory model */
// memPK = 4, 	/* Packed pixel memory model */
// memRGB = 6, 	/* Direct color RGB memory model */
// memYUV = 7, 	/* Direct color YUV memory model */
//} memModels;

typedef struct
{
 unsigned char Red;
 unsigned char Green;
 unsigned char Blue;
} palette;

typedef struct
{
 Boolean mask;
 int modeNo;
 uLong memsize;
}modesize;

uLong dwBaseAddress,memsize,ulTestPattern[0x100],LastMemAddr;
uInt wSize_Mega,Mode_Num[256];
palette pal[256];
modesize ms[100];
char far *key_buf=(char far*) 0x00400;
char far *keybuffer=(char far*) 0x00400017;
char far *keybuffer1=(char far*) 0x00400018;
int textm[5]={0,1,2,3,7};
int textmindex=5;
int oldMode; 	     // Old video mode number
int DDCmode=0;       // 1:a0 3:a2 4:a3
			 //          1         2         3         4         5
			 // 123456789012345678901234567890123456789012345678901234567890
char  DisplayItem[12][81]={
	    /*0*/	  "ษออออออออออออหอออออออออออออออหออออออออออออหออออออออออออป",
	    /*1*/         "?Total Size ? Test  Range  ?Err Address?Err Data   ?,
	    /*2*/         "วฤฤฤฤฤฤฤฤฤฤฤฤืฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤืฤฤฤฤฤฤฤฤฤฤฤฤืฤฤฤฤฤฤฤฤฤฤฤฤถ",
	    /*3*/         "?           ?              ?---------- ?---------- ?,
	    /*4*/         "ฬออออออออออออฮอออออออออออออออฮออออออออออออสออออออออออออน",
	    /*5*/         "?Test  Size ? Test Pattern ?  Test Address Range    ?,
	    /*6*/         "วฤฤฤฤฤฤฤฤฤฤฤฤืฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤืฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ",
	    /*7*/         "?           ?              ?                        ?,
//	    /*8*/         "ฬออออออออออออสอออออออออออออออสอออออออออออออออออออออออออน",
//	    /*9*/         "?0%                      25%                      100%?,
//	    /*10*/	  "? ฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐ  ?,
//	    /*11*/	  "ศออออออออออออออออออออออออออออออออออออออออออออออออออออออผ"};
	    /*8*/	  "ศออออออออออออสอออออออออออออออสอออออออออออออออออออออออออผ"};

char InfoItem[5][81]={
 "ษอออออัอออออออออออออออออออหอออออัอออออออออออออออออออหอออออัออออออออออออออออออออป",
 "?mode?Resolution& Colors?mode?Resolution& Colors?mode?Resolution& Colors ?,
 "ฬอออออุอออออออออออออออออออฮอออออุอออออออออออออออออออฮอออออุออออออออออออออออออออน",
 "?    ?                  ?    ?                  ?    ?                   ?,
 "ศอออออฯอออออออออออออออออออสอออออฯอออออออออออออออออออสอออออฯออออออออออออออออออออผ"};



Boolean blWork(void)
{
  return TRUE;
}


/*------------------------ VBE Interface Functions ------------------------*/
/* Get SuperVGA information, returning true if VBE found */
Boolean getVbeInfo(void)
{
union REGS in,out;
struct SREGS segs;
in.x.ax = 0x4F00;
in.x.di = FP_OFF(&VbeInfoBlock);
segs.es = FP_SEG(&VbeInfoBlock);
int86x(0x10, &in, &out, &segs);
if (out.x.ax != 0x4F) return FALSE;
return TRUE;
}


Boolean getModeInfo(int mode)
{
union REGS in,out;
struct SREGS segs;
if (mode < 0x100) return FALSE; /* Ignore non-VBE modes */
in.x.ax = 0x4F01;
in.x.cx = mode;
in.x.di = FP_OFF(&ModeInfoBlock);
segs.es = FP_SEG(&ModeInfoBlock);
int86x(0x10, &in, &out, &segs);
if (out.x.ax != 0x4F) return FALSE;
return TRUE;
}

/* Set a VBE video mode */
Boolean setVBEMode(int mode)
{
  union REGS in,out;
  in.x.ax = 0x4F02;
  in.x.bx = mode|0x4000;
  int86(0x10,&in,&out);
  if (out.x.ax != 0x4F) return FALSE;
  return TRUE;
}

Boolean ReportDDC(void)
{
  union REGS in,out;
  struct SREGS segregs;

  in.x.ax = 0x4F15;
  in.x.bx = 0;
  in.x.cx = 0;
  segregs.es=0;
  in.x.di=0;
  int86x(0x10,&in,&out,&segregs);

  if (out.x.ax != 0x4F) return FALSE;

  if((out.x.bx & 0x02) == 0x02) DDCmode = 1;
  else if((out.x.bx & 0x08) == 0x08) DDCmode = 3;
  else if((out.x.bx & 0x10) == 0x10) DDCmode = 4;
  else return FALSE;
  return TRUE;
}

Boolean ReadEDID(int mode)
{
  union REGS in,out;
  struct SREGS segregs;

  in.x.ax = 0x4F15;
  in.x.bx = mode;
  in.x.cx = 0;

  if(mode==1) in.x.dx = 0;
  else in.x.dx = 1;

  in.x.di = FP_OFF(&EDIDBuf);
  segregs.es = FP_SEG(&EDIDBuf);
  int86x(0x10,&in,&out,&segregs);
  if (out.x.ax != 0x4F) return FALSE;
  return TRUE;
}

Boolean Detect_DDC(void)
{
 int i=0,j=1,count;
 asus.PrintStr(1,4,"***** DDC data *****",-1,0x17);
 if(ReportDDC()) {
   if(DDCmode==1)  { count=128;
   }else count=256;
   gotoxy(1,5); printf("%dbytes",count);

   if(ReadEDID(DDCmode)) {
     gotoxy(1,6);
     for(i=0;i<count;i++) {
      printf("%02X ",EDIDBuf[i]);
      if(j%16==0) printf("\n");
      j++;
     }
   }

 }else {
   asus.PrintStr(1,6,"Can't read DDC data !!!",-1,0x0C);
   return FALSE;
 }
 return TRUE;
}





Boolean set6BitPalette(void)
{
 REGS  regs;

 regs.x.ax = 0x4F08;
 regs.x.bx = 0x0600;
 int86(0x10,&regs,&regs);	/* Restore to 6 bit DAC               */
 if (regs.x.ax != 0x004F) return TRUE;
 if (regs.h.bh != 6)      return FALSE;
 return TRUE;
}

Boolean set8BitPalette(void)
{
 REGS regs;

 regs.x.ax = 0x4F08;         /* Set DAC service                      */
 regs.x.bx = 0x0800;         /* BH := 8, BL := 0 (set DAC width)     */
 int86(0x10,&regs,&regs);
 if((regs.h.bh == 6)&&(regs.x.ax != 0x004F))
   return FALSE;           /* Function failed, no wide dac         */

 regs.x.ax = 0x4F08;
 regs.x.bx = 0x0001;         /* Get DAC width (should now be 8)      */
 int86(0x10,&regs,&regs);
 if((regs.h.bh != 8) &&(regs.x.ax != 0x004F))
   return FALSE;

 return TRUE;
}


void setPalette(int start, int num, palette *palbuf)
{
 REGS	regs;
 SREGS	sregs;
 regs.x.ax = 0x1012;
 regs.x.bx = start;
 regs.x.cx = num;
 sregs.es = FP_SEG(palbuf);
 regs.x.dx = FP_OFF(palbuf);
 int86x(0x10, &regs, &regs, &sregs);
}

void getPalette(int start, int num, palette *palbuf)
{
 REGS	regs;
 SREGS	sregs;
 regs.x.ax = 0x1017;
 regs.x.bx = start;
 regs.x.cx = num;
 sregs.es = FP_SEG(palbuf);
 regs.x.dx = FP_OFF(palbuf);
 int86x(0x10, &regs, &regs, &sregs);
}


Boolean setSpecialpalette(int method,uLong *color)
{
 int i;
 uChar a;

 if (!set8BitPalette()) return FALSE;

 memset(pal,0,256*3);

 if(method==0) {
   pal[1].Red=(*color>>16)&0xFF;
   pal[1].Green=(*color>>8)&0xFF;
   pal[1].Blue=*color&0xFF;
   *color=1;
 }else if(method==1) {
   pal[1].Red=*color&0xFF;
   pal[2].Green=*color&0xFF;
   pal[3].Blue=*color&0xFF;

   pal[4].Red=*color&0xFF;
   pal[4].Green=*color&0xFF;
   pal[4].Blue=*color&0xFF;
 }
 setPalette(0,256,pal);
 return TRUE;
}



Boolean setDACpalette(void)
{
 int i;
 uChar a;

 if (!set8BitPalette()) return FALSE;
 memset(pal,0,256*3);

 a=0xFF;
 for (i = 64; i < 96; i++) {
    pal[i].Red = a;
    pal[i].Green = a;
    pal[i].Blue = a;
    a-=0x8;
   }
 a=0x87;
 for (i = 16; i < 20; i++) {
    pal[i].Red = a;
    a+=0x28;
   }
 a=0x87;
 for (i = 20; i < 24; i++) {
    pal[i].Green = a;
    a+=0x28;
   }
 a=0x87;
 for (i = 24; i < 28; i++) {
    pal[i].Blue = a;
    a+=0x28;
   }
 a=0x87;
 for (i = 28; i < 32; i++) {
    pal[i].Red = a;
    pal[i].Green = a;
    pal[i].Blue = a;
    a+=0x28;
   }
 a=0x3f;
 for (i = 32; i < 34; i++) {
    pal[i].Red = a;
    pal[i].Green = a;
    pal[i].Blue = a;
    a+=0x40;
   }
 a=0x3f;
 for (i = 34; i < 36; i++) {
    pal[i].Red = a;
    a+=0x40;
   }
 a=0x3f;
 for (i = 36; i < 38; i++) {
    pal[i].Green = a;
    a+=0x40;
   }
 a=0x3f;
 for (i = 38; i < 40; i++) {
    pal[i].Blue = a;
    a+=0x40;
   }
 pal[41].Green = 0x7f;
 pal[41].Blue = 0x7f;
 setPalette(0,256,pal);
 return TRUE;
}

/* Return the current VBE video mode */
int getVBEMode(void)
{
  union REGS in,out;
  in.x.ax = 0x4F03;
  int86(0x10,&in,&out);
  return out.x.bx;
}

void PutPixel(uLong x, uLong y, uLong Pattern)
{
  uLong dwAddress;
  switch(ModeInfoBlock.BitsPerPixel) {
  case 8:
  dwAddress=dwBaseAddress+((y*ModeInfoBlock.BytesPerScanLine)+x);
  MM.PokeB(dwAddress,Pattern);
  break;
  case 15:
  case 16:
  dwAddress=dwBaseAddress+((y*ModeInfoBlock.BytesPerScanLine)+(x*2));
  MM.PokeW(dwAddress,Pattern);
  break;
  case 24:
  dwAddress=dwBaseAddress+((y*ModeInfoBlock.BytesPerScanLine)+(x*3));
  MM.PokeW(dwAddress,(Pattern&0x0000FFFFl));
  MM.PokeB(dwAddress+2,(Pattern&0x00FF0000l)>>16);
  break;
  case 32:
  dwAddress=dwBaseAddress+((y*ModeInfoBlock.BytesPerScanLine)+(x*4));
  MM.PokeDW(dwAddress,Pattern);
  break;
  }
}

Boolean blMemorySizing()
{
  uInt i;
  uInt j,data1,data2,data3;
  Boolean blSizing_OK=FALSE;

  for(i=0;;i++) {
    data1=MM.wPeek(dwBaseAddress+(i*0x100000l)+0xFFFFEl);
    data2=MM.wPeek(dwBaseAddress+(i*0x100000l)+0xFFFFCl);
    data3=MM.wPeek(dwBaseAddress+(i*0x100000l)+0xFFFFAl);
    MM.PokeW(dwBaseAddress+(i*0x100000l)+0xFFFFEl, 0x55AA);
    MM.PokeW(dwBaseAddress+(i*0x100000l)+0xFFFFCl, 0xAA55);
    MM.PokeW(dwBaseAddress+(i*0x100000l)+0xFFFFAl, 0x5A5A);
    if(MM.wPeek(dwBaseAddress+(i*0x100000l)+0xFFFFEl)!=0x55AA ||
       MM.wPeek(dwBaseAddress+(i*0x100000l)+0xFFFFCl)!=0xAA55 ||
       MM.wPeek(dwBaseAddress+(i*0x100000l)+0xFFFFAl)!=0x5A5A) {
       blSizing_OK=TRUE;
      }
    if(blSizing_OK || i==0xFF) break;
    MM.PokeW(dwBaseAddress+(i*0x100000l)+0xFFFFEl, data1);
    MM.PokeW(dwBaseAddress+(i*0x100000l)+0xFFFFCl, data2);
    MM.PokeW(dwBaseAddress+(i*0x100000l)+0xFFFFAl, data3);
  }
  wSize_Mega=i-1;
//  gotoxy(1,24);
//  printf("%ld",wSize_Mega);
//  printf("%lX",i);
  return TRUE;
}

void Display(int x,int y)
{
 int i,j;
// textattr(0x09);
 asus.PrintStr(1,y-1,"*** Video Memory Test ***",0,0x09);
 textattr(0x0F);
 for(i=0;i<12-3;i++){
  gotoxy(x,y+i);
  cputs(DisplayItem[i]);
 }

 gotoxy(x+5,y+3);  printf("%d MB",(VbeInfoBlock.TotalMemory*64l)/1024);

}

void ProductTestPattern()
{
  ulTestPattern[0]=0x5A5A5A5Al;
  ulTestPattern[1]=0xA5A5A5A5l;
  ulTestPattern[2]=0x55AA55AAl;
  ulTestPattern[3]=0xAA55AA55l;
}

Boolean blMemoryTest(int MemSize)
{
  char ch1,ch2;
  long StartTime,NowTime;
  uLong ErrAddr[20],ErrData[20],ErrIndex=0;
  uInt i,m,Start=0,End,DisplayX=13,DisplayY=6,ErrX=1,ErrY=9;
  uInt j=0,data1,data2,data3,k,barno,TotalMemSize;
  DWORD dwPosition,dwSrcData;//,TestPattern=0x5A5A5A5A;
  Boolean blBreak=FALSE,blFoundErr=FALSE,blF5=FALSE,blTimeOut=FALSE;
//  float BarSpace;
//  uInt testa,testb;

  if(MM.blSet()==FALSE) return FALSE;
  MM.EnableA20();

  if (!getVbeInfo())  {
   printf("No VESA VBE detected\n");
   return FALSE;
  }else if(getModeInfo(0x111)) {
   dwBaseAddress=FP_SEG(ModeInfoBlock.PhyBasePtr)*0x10000l;
   TotalMemSize=(VbeInfoBlock.TotalMemory*64l)/1024;

   if((MemSize==0)|| (MemSize>TotalMemSize)) MemSize=TotalMemSize;

   if(blMemoryTestRange) {
     if(iMemoryEnd < iMemoryStart) {
       End=iMemoryStart; Start=iMemoryEnd;
     }else {
       End=iMemoryEnd;   Start=iMemoryStart;
     }
     if(End>TotalMemSize) End=TotalMemSize;
     if(Start>=1 && Start<=TotalMemSize) Start-=1;
     MemSize=End-Start;
   }else {
    if(blTestTimerOK) {
      if(LastMemAddr>0)  Start=(LastMemAddr-dwBaseAddress)/0x100000l;
//      else Start=0;
      time(&StartTime);
    }
    End=MemSize;
   }
   ProductTestPattern();

//   BarSpace=(float) 50/(End-Start);
   oldMode = getVBEMode();
   Display(DisplayX,DisplayY);
   gotoxy(DisplayX+16,DisplayY+7);   printf("0x%08lX(%d)",ulTestPattern[1],j+1);
   gotoxy(DisplayX+15,DisplayY+3);   printf("%3dMB - %3dMB",Start+1,End);


   for(i=Start;i<End;i++) {
     m=i;
     if(blTestTimerOK) {
       time(&NowTime);
       textattr(0x02);
       gotoxy(65,11); cprintf("%2d",(StartTime+iTestTimer)-NowTime);
       textattr(0x07);
       if(NowTime>=StartTime+iTestTimer) {
	 blTimeOut=TRUE;
	 SaveFile(dwBaseAddress+(m*0x100000l));
	 break;
       }
     }
     if(((*keybuffer&0x09)==0x09) && ((*keybuffer1&0x02)==0x02) && blF5){  //Left_Alt+Right_Shift
	 *(key_buf+0x1A)=0x1E;  *(key_buf+0x1C)=0x1E;
	 blBreak=FALSE;
	 break;
     }
     if(kbhit()) {
       ch1=getch();
       if(ch1==0) {
	ch2=getch();
	if((ch2==63)&& !blF5) {
	   blF5=TRUE; textattr(0x1E);
	   gotoxy(15,5); cprintf("F5");
	   textattr(0x07);
	}else if((ch2==63)&& blF5){
	   blF5=FALSE; textattr(0x00);
	   gotoxy(15,5); cprintf("F5");
	   textattr(0x07);
	}
       }else if(ch1==27) {
	 blBreak=TRUE;
	 break;
       }
     }
     for(j=0;j<2;j++) {
     MM.FillDW(dwBaseAddress+(m*0x100000l),ulTestPattern[j],0xFFFFFl);
     if(!MM.blComparePatternDW(dwBaseAddress+(m*0x100000l) ,0xFFFFFl ,ulTestPattern[j], &dwPosition, &dwSrcData)) {
      if(((MM.bPeek(dwBaseAddress)==0x55) || (MM.bPeek(dwBaseAddress)==0x5A) ||
	  (MM.bPeek(dwBaseAddress)==0xA5) || (MM.bPeek(dwBaseAddress)==0xAA))||
	 ((MM.bPeek(dwBaseAddress+10)==0x55) || (MM.bPeek(dwBaseAddress+10)==0x5A) ||
	  (MM.bPeek(dwBaseAddress+10)==0xA5) || (MM.bPeek(dwBaseAddress+10)==0xAA)) ) {
	 setVBEMode(oldMode);
	 Logo();
       }
       Display(DisplayX,DisplayY);
       gotoxy(DisplayX+16,DisplayY+7);   printf("0x%08lX(%d)",ulTestPattern[j],j+1);
       gotoxy(DisplayX+5,DisplayY+7);    printf("%d MB",i+1);
       gotoxy(DisplayX+15,DisplayY+3);   cprintf("%3dMB - %3dMB",Start+1,End);
       textattr(0x0C);
       gotoxy(DisplayX+31,DisplayY+3);   cprintf("0x%08lX",dwPosition-dwBaseAddress);
       gotoxy(DisplayX+44,DisplayY+3);   cprintf("0x%08lX",dwSrcData);
       gotoxy(DisplayX+ErrX,DisplayY+ErrY++);
       cprintf("0x%08lX 0x%08lX",dwPosition-dwBaseAddress,dwSrcData);
       ErrAddr[ErrIndex]=dwPosition-dwBaseAddress;
       ErrData[ErrIndex++]=dwSrcData;
       if(ErrY==16) { ErrX+=25; ErrY=9; }
       if(blF5) {
	 textattr(0x1E);
	 gotoxy(15,5); cprintf("F5");
	 textattr(0x07);
       }else {
	 textattr(0x00);
	 gotoxy(15,5); cprintf("F5");
	 textattr(0x07);
       }
       textattr(0x0F);
       gotoxy(DisplayX+31,DisplayY+7);
       printf("0x%08lX - 0x%08lX",m*0x100000l,m*0x100000l+0xFFFFFl);
       asus.PrintStr(1,22,"Video Memory Test Fail !!!",0,0x8C);
       blFoundErr=TRUE;
       if(ErrIndex>13) return FALSE;
       if(blTestContinue) break;
       return FALSE;
     }else {
      if(((MM.bPeek(dwBaseAddress)==0x55) || (MM.bPeek(dwBaseAddress)==0x5A) ||
	  (MM.bPeek(dwBaseAddress)==0xA5) || (MM.bPeek(dwBaseAddress)==0xAA))||
	 ((MM.bPeek(dwBaseAddress+10)==0x55) || (MM.bPeek(dwBaseAddress+10)==0x5A) ||
	  (MM.bPeek(dwBaseAddress+10)==0xA5) || (MM.bPeek(dwBaseAddress+10)==0xAA)) ) {
	 setVBEMode(oldMode);
	 Logo();
	 Display(DisplayX,DisplayY);
	 gotoxy(DisplayX+15,DisplayY+3);   cprintf("%3dMB - %3dMB",Start+1,End);
      }
      if(blMemoryTestRange) {
	gotoxy(DisplayX+15,DisplayY+3);   cprintf("%3dMB - %3dMB",Start+1,End);
      }
      if(blTestTimerOK) {
       time(&NowTime);
       textattr(0x02);
       gotoxy(65,11); cprintf("%2d",(StartTime+iTestTimer)-NowTime);
       textattr(0x07);
       if(NowTime>=StartTime+iTestTimer) {
	 blTimeOut=TRUE;
	 SaveFile(dwBaseAddress+(m*0x100000l));
	 break;
       }
      }
      if(blFoundErr) {
	int ErX=1,ErY=9;
	textattr(0x0C);
	for(int d=0;d<ErrIndex;d++) {
	  gotoxy(DisplayX+ErX,DisplayY+ErY++);
	  cprintf("0x%08lX 0x%08lX",ErrAddr[d],ErrData[d]);
	  if(ErY==16) { ErX+=25; ErY=9; }
	}
	textattr(0x0C);
      }
      gotoxy(DisplayX+16,DisplayY+7);   printf("0x%08lX(%d)",ulTestPattern[j],j+1);
      gotoxy(DisplayX+5,DisplayY+7);    printf("%d MB",i+1);
      gotoxy(DisplayX+31,DisplayY+7);
      printf("0x%08lX - 0x%08lX",m*0x100000l,m*0x100000l+0xFFFFFl);
      if(blF5) {
	 textattr(0x1E);
	 gotoxy(15,5); cprintf("F5");
	 textattr(0x07);
      }else {
	 textattr(0x00);
	 gotoxy(15,5); cprintf("F5");
	 textattr(0x07);
      }
//      textattr(0x03);
//      for(k=0;k<(i+1)*BarSpace;k++) {
//	gotoxy(DisplayX+3+k,DisplayY+10);    cprintf("?);
//      }
//      textattr(0x0F);

     }
    }
   }
  }
  setVBEMode(oldMode);
  Logo();
//  if(blBreak) barno=(i+1)*BarSpace;
//  else barno=50;
  Display(DisplayX,DisplayY);
  gotoxy(DisplayX+5,DisplayY+7);    printf("%d MB",i);
  gotoxy(DisplayX+16,DisplayY+7);   printf("0x%08lX(%d)",ulTestPattern[j-1],j);
  gotoxy(DisplayX+15,DisplayY+3);   cprintf("%3dMB - %3dMB",Start+1,End);
  gotoxy(DisplayX+31,DisplayY+7);
  printf("0x%08lX - 0x%08lX",m*0x100000l,m*0x100000l+0xFFFFFl);

  if(blF5) {
     textattr(0x1E);
     gotoxy(15,5); cprintf("F5");
     textattr(0x07);
  }else {
     textattr(0x00);
     gotoxy(15,5); cprintf("F5");
     textattr(0x07);
  }
  if(blTestTimerOK) {
    textattr(0x02);
    gotoxy(65,11); cprintf("%2d",(StartTime+iTestTimer)-NowTime);
    textattr(0x07);
  }
  if(blFoundErr) {
    ErrX=1; ErrY=9;
    textattr(0x0C);
    for(int d=0;d<ErrIndex;d++) {
       gotoxy(DisplayX+ErrX,DisplayY+ErrY++);
       cprintf("0x%08lX 0x%08lX",ErrAddr[d],ErrData[d]);
       if(ErrY==16) { ErrX+=25; ErrY=9; }
    }
    textattr(0x0C);
  }
//  textattr(0x03);
//  for(k=0;k<barno;k++) {
//    gotoxy(DisplayX+3+k,DisplayY+10);    cprintf("?);
//  }
//  textattr(0x0F);
  if(blBreak) {
    asus.PrintStr(1,22,"User Break !!!",0,0x0C);
    return FALSE;
  }else if(blTimeOut) {
    asus.PrintStr(1,22,"Time Out !!!",0,0x0C);
    return TRUE;
  }else if(blF5) {
    asus.PrintStr(1,22,"User Break !!!",0,0x0C);
    return TRUE;
  }else if(blFoundErr) {
    asus.PrintStr(1,22,"Video Memory Test Fail !!!",0,0x0C);
    return FALSE;
  }else {
   asus.PrintStr(1,22,"Video Memory Test OK !!!",0,0x0A);
   if(blTestTimerOK) SaveFile(0);
  }

  return TRUE;
}

void ClearScreen(uLong Pattern)
{
 uLong dwAddress;
 switch(ModeInfoBlock.BitsPerPixel) {
 case  8:
	 MM.FillB(dwBaseAddress,Pattern,memsize);
	 break;
 case 15:
 case 16:
	 MM.FillW(dwBaseAddress,Pattern,memsize);
	 break;
 case 24:
	 for(dwAddress=dwBaseAddress;dwAddress<=dwBaseAddress+memsize;dwAddress+=3) {
	   MM.PokeW(dwAddress,(Pattern&0x0000FFFFl));
	   MM.PokeB(dwAddress+2,(Pattern&0x00FF0000l)>>16);
	 }
	 break;
 case 32:
	 MM.FillDW(dwBaseAddress,Pattern,memsize);
	 break;
 }
}

Boolean test(int mode)
{
  int x,y,col,i,j;
  char ch1,ch2;
  uLong color=0xFFFFFF;

//  MemoryBar(1,10,0,20);

  if(MM.blSet()==FALSE) return FALSE;
  MM.EnableA20();


  if (!getVbeInfo())  {
   printf("No VESA VBE detected\n");
   return FALSE;
  }else if(getModeInfo(mode))  {
   if(ModeInfoBlock.BitsPerPixel>=8) {
      memsize=(uLong)(ModeInfoBlock.BytesPerScanLine) *
	      (uLong)(ModeInfoBlock.YResolution);
      dwBaseAddress=FP_SEG(ModeInfoBlock.PhyBasePtr)*0x10000l;
      oldMode = getVBEMode();
      blMemorySizing();
      if(setVBEMode(mode)==TRUE) {
	if(ModeInfoBlock.BitsPerPixel==8)
	  if(setSpecialpalette(0,&color)) {
	  }

	do{
//	   ClearScreen(color);
//	   PutPixel(ModeInfoBlock.XResolution-1, ModeInfoBlock.YResolution-1,rgbColor(0xFF,0xFF,0xFF));
	   line(0,0,ModeInfoBlock.XResolution-1, ModeInfoBlock.YResolution-1,rgbColor(0xFF,0xFF,0xFF));
	   line(ModeInfoBlock.XResolution-1,0,0,ModeInfoBlock.YResolution-1,rgbColor(0xFF,0xFF,0xFF));
	   ch1=getch();
	   if(ch1==0) {
	      ch2=getch();
	   }else if(ch1==27) break;
	}while(ch2!=45);
	setVBEMode(oldMode);
//	gotoxy(1,24);
	printf("%d",wSize_Mega);
      }
    }
  }else return FALSE;
  return TRUE;
}


Boolean blFillColor(uInt mode,uLong color)
{
  unsigned far* p;
  uLong max;
  int x,y,col,index,i;
  char ch1,ch2,str[20];
  Boolean blPressKey=FALSE,blF5=FALSE;

  if(MM.blSet()==FALSE) return FALSE;
  MM.EnableA20();

  if(delaytime <= 0) delaytime=0;
  else blDelayTime=TRUE;

  if (!getVbeInfo())  {
   printf("No VESA VBE detected\n");
   return FALSE;
  }

  if(mode<=0x99) {       // Auto Detect Max Memory Size request Mode function
    //record now support mode
    for (p = VbeInfoBlock.VideoModePtr; *p !=(unsigned)-1; p++)    {
      if(getModeInfo(*p)==TRUE)  {
	if(ModeInfoBlock.BitsPerPixel>=8) {
	 ms[index].modeNo=*p;
	 ms[index].mask=FALSE;
	 ms[index++].memsize=(uLong)(ModeInfoBlock.BytesPerScanLine) *
			   (uLong)(ModeInfoBlock.YResolution);
	}
	if(index==100) break;
      }
    }

    do{  // search can display mode for dos
      if((max!=0) && (mode!=0x99)) ms[i].mask=TRUE;
      max=ms[0].memsize;
      for(i=0;i<index;i++) {
	if((max < ms[i].memsize)&&(!ms[i].mask)) {
	  max=ms[i].memsize;  i=0;
	}
      }
      for(i=0;i<index;i++) {
	if(max == ms[i].memsize) {
	  mode=ms[i].modeNo; break;
	}
      }
      oldMode = getVBEMode();
    }while(!setVBEMode(mode));
    setVBEMode(oldMode);
  }

  if(getModeInfo(mode))  {
   if(ModeInfoBlock.BitsPerPixel>=8) {
      memsize=(uLong)(ModeInfoBlock.BytesPerScanLine) *
	      (uLong)(ModeInfoBlock.YResolution);
      dwBaseAddress=FP_SEG(ModeInfoBlock.PhyBasePtr)*0x10000l;
      oldMode = getVBEMode();
      if(setVBEMode(mode)==TRUE) {
	if(ModeInfoBlock.BitsPerPixel==8) {
	  if(!setSpecialpalette(0,&color)) {
	    setVBEMode(oldMode);
	    return FALSE;
	  }
	}
	do{
	   ClearScreen(color);
//  uLong dwAddress=dwBaseAddress+0x47e4;
//  MM.PokeW(dwAddress,color);
//  sprintf(str,"%lx",MM.bPeek(dwAddress));
//  writeText(100,200,str,0xffffffl);
	   if(blShow) {
	      sprintf(str,"%d*%d*%d",ModeInfoBlock.XResolution,
	      ModeInfoBlock.YResolution,ModeInfoBlock.BitsPerPixel);
	      writeText((ModeInfoBlock.XResolution/16)*7,(ModeInfoBlock.YResolution/16)*14,
			 str,rgbColor(0xFF,0xFF,0xFF));
	   }
	   if(blDelayTime) {
	     delay(delaytime*1000);
	     break;
	   }
	   if(blSpecialKey) {
	     while(((*keybuffer&0x09)!=0x09) || ((*keybuffer1&0x02)!=0x02));  //Left_Alt+Right_Shift
	     *(key_buf+0x1A)=0x1E;  *(key_buf+0x1C)=0x1E;
	     blPressKey=TRUE;
	     break;
	   }else {
	     ch1=getch();
	     if(ch1==0) {
	       ch2=getch();
	       if(ch2==63 && !blF5) {
		  blF5=TRUE;
	       }else if(ch2==63 && blF5) {
		  blF5=FALSE;
	       }
	     }else if(ch1==27) {
	      blPressKey=FALSE;
	      break;
	     }
	     if(blF5) {
	      while((((*keybuffer&0x09)!=0x09) || ((*keybuffer1&0x02)!=0x02)));
		 *(key_buf+0x1A)=0x1E;  *(key_buf+0x1C)=0x1E;
		 blPressKey=TRUE;
		 break;
	     }
	    }
	}while(ch2!=45);
	  setVBEMode(oldMode);
      }
    }
  }
  return blPressKey;
}


Boolean Display_Pattern(uInt mode,int pattern)
{
  unsigned far* p;
  uLong max=0;
  uChar r,g,b;
  int i,j,k,x,y,col,index=0,mindex=1,maxx,maxy,oldcol,lastrow,row;
  int ax,bx,cx,dx,ay,by,cy,dy,TotalPattern=23;
  char ch1,ch2,str[20];
  Boolean blShowAllContinue=FALSE,blTextmode=FALSE,blAutoLoop=FALSE;
  Boolean blPressKey=FALSE,blF5=FALSE;

  if(MM.blSet()==FALSE) return FALSE;
  MM.EnableA20();

  if(pattern==99 || pattern==98) {
    if(pattern==98) blShowAllContinue=TRUE;
    pattern=1;  blShowAllPattern=TRUE;
    if(!blDelayTime) {
      blDelayTime=TRUE; delaytime=1000;
    }
  }else if(pattern > 27 || pattern <= 0)   pattern=1;


  if(delaytime <= 0) delaytime=0;
//  else { delay(delaytime); }

  if (!getVbeInfo())  {
   printf("No VESA VBE detected\n");
   return FALSE;
  }

  oldMode = getVBEMode();

  if(mode==0x97|| mode <= 3 || mode==0x07) {
     blTextmode=TRUE;
     if(mode==0x97) { blAutoLoop=TRUE; mode=0; }
     if(delaytime==0) delaytime=3000;
  }

  if(mode==0x99) {       // Auto Detect Max Memory Size request Mode function
    //record now support mode
    for (p = VbeInfoBlock.VideoModePtr; *p !=(unsigned)-1; p++)    {
      if(getModeInfo(*p)==TRUE)  {
	if(ModeInfoBlock.BitsPerPixel>=8) {
	 ms[index].modeNo=*p;
	 ms[index].mask=FALSE;
	 ms[index++].memsize=(uLong)(ModeInfoBlock.BytesPerScanLine) *
			   (uLong)(ModeInfoBlock.YResolution);
	}
	if(index==100) break;
      }
    }
    j=0;
    do{  // search can display mode for dos
      max=ms[0].memsize;
      for(i=0;i<index;i++) {
	if((max < ms[i].memsize)&&(!ms[i].mask)) {
	  max=ms[i].memsize;  i=0;
	}
      }
      for(i=0;i<index;i++) {
	if((max == ms[i].memsize) && (!ms[i].mask) ) {
	  mode=ms[i].modeNo;
	  ms[i].mask=TRUE;
	  break;
	}
      }
      oldMode = getVBEMode();
    }while(!setVBEMode(mode));
    setVBEMode(oldMode);
  }

  if(getModeInfo(mode))  {      //Graphics mode test function
   if(ModeInfoBlock.BitsPerPixel>=8) {
      memsize=(uLong)(ModeInfoBlock.BytesPerScanLine) *
	      (uLong)(ModeInfoBlock.YResolution);
      dwBaseAddress=FP_SEG(ModeInfoBlock.PhyBasePtr)*0x10000l;
      if(setVBEMode(mode)==TRUE) {
	if(ModeInfoBlock.BitsPerPixel==8) {
	  if(!setDACpalette()) {
	    setVBEMode(oldMode);
	    return FALSE;
	  }
	}
	do {
	    switch (pattern) {
	    case 1:
	    ClearScreen(0);
	    for(x=0; x<ModeInfoBlock.XResolution; x++) {
		PutPixel(x,0,rgbColor(0xFF,0xFF,0xFF));
		PutPixel(x,ModeInfoBlock.YResolution-1,rgbColor(0xFF,0xFF,0xFF));
	    }
	    for(y=0; y<ModeInfoBlock.YResolution; y++) {
		PutPixel(0,y,rgbColor(0xFF,0,0));
		PutPixel(ModeInfoBlock.XResolution-1,y,rgbColor(0,0,0xFF));
	    }
	    break;

	    case 2:
	    ClearScreen(rgbColor(0xFF,0xFF,0xFF)); break;

	    case 3:
	    ClearScreen(rgbColor(0xFF,0,0)); break;

	    case 4:
	    ClearScreen(rgbColor(0,0xFF,0)); break;

	    case 5: ClearScreen(rgbColor(0,0,0xFF)); break;

	    case 6: ClearScreen(rgbColor(0x7F,0,0)); break;

	    case 7: ClearScreen(rgbColor(0,0x7F,0)); break;

	    case 8: ClearScreen(rgbColor(0,0,0x7F)); break;

	    case 9: ClearScreen(rgbColor(0x7F,0x7F,0x7F)); break;

	    case 10:ClearScreen(rgbColor(0x3F,0x3F,0x3F)); break;

	    case 11:
		    ClearScreen(0);
		    col=ModeInfoBlock.XResolution/16;
		    for(x=0; x < col; x++)
		    for(y=0; y < ModeInfoBlock.YResolution; y++) {
			PutPixel(x,y,rgbColor(0xFF,0,0));
			PutPixel(x+col,y,rgbColor(0xD7,0,0));
			PutPixel(x+(col*2),y,rgbColor(0xAF,0,0));
			PutPixel(x+(col*3),y,rgbColor(0x87,0,0));
			PutPixel(x+(col*4),y,rgbColor(0,0xFF,0));
			PutPixel(x+(col*5),y,rgbColor(0,0xD7,0));
			PutPixel(x+(col*6),y,rgbColor(0,0xAF,0));
			PutPixel(x+(col*7),y,rgbColor(0,0x87,0));
			PutPixel(x+(col*8),y,rgbColor(0,0,0xFF));
			PutPixel(x+(col*9),y,rgbColor(0,0,0xD7));
			PutPixel(x+(col*10),y,rgbColor(0,0,0xAF));
			PutPixel(x+(col*11),y,rgbColor(0,0,0x87));
			PutPixel(x+(col*12),y,rgbColor(0xFF,0xFF,0xFF));
			PutPixel(x+(col*13),y,rgbColor(0xD7,0xD7,0xD7));
			PutPixel(x+(col*14),y,rgbColor(0xAF,0xAF,0xAF));
			PutPixel(x+(col*15),y,rgbColor(0x87,0x87,0x87));
		    }

		    break;
	    case 12:
		    ClearScreen(0);
		    for(y=0; y<(ModeInfoBlock.YResolution/2); y++)
		      for(x=0; x<(ModeInfoBlock.XResolution/2); x++) {
			PutPixel(x,y,rgbColor(0xFF,0xFF,0xFF));
			PutPixel(x+(ModeInfoBlock.XResolution/2),ModeInfoBlock.YResolution-y-1,rgbColor(0xFF,0xFF,0xFF));
		      }
		    break;

	    case 13:
		    ClearScreen(0);
		    for(y=0; y<(ModeInfoBlock.YResolution/2); y++)
		      for(x=0; x<(ModeInfoBlock.XResolution/2); x++) {
			PutPixel(x+(ModeInfoBlock.XResolution/2),y,rgbColor(0xFF,0xFF,0xFF));
			PutPixel(x,ModeInfoBlock.YResolution-y-1,rgbColor(0xFF,0xFF,0xFF));
		      }
		    break;

	    case 14:
		    ClearScreen(0);
		    break;

	    case 15:
		    ClearScreen(0);
		    for(x=0; x<ModeInfoBlock.XResolution; x+=4) {
		      for(y=0; y<ModeInfoBlock.YResolution; y++) {
			PutPixel(x,y,rgbColor(0xFF,0xFF,0xFF));
			PutPixel(x+1,y,rgbColor(0xFF,0xFF,0xFF));
		      }
		    }
		    break;

	    case 16:
		    ClearScreen(0x00);
		    for(x=(ModeInfoBlock.XResolution/3); x<=(ModeInfoBlock.XResolution*2)/3; x++)
		      for(y=(ModeInfoBlock.YResolution/3); y<(ModeInfoBlock.YResolution*2/3); y++)
			PutPixel(x,y,rgbColor(0xFF,0xFF,0xFF));
		    break;

	    case 17:
		    ClearScreen(rgbColor(0x7F,0x7F,0x7F));
		    for(x=(ModeInfoBlock.XResolution/3); x<=(ModeInfoBlock.XResolution*2)/3; x++)
		    for(y=(ModeInfoBlock.YResolution/3); y<(ModeInfoBlock.YResolution*2/3); y++)
			PutPixel(x,y,rgbColor(0,0,0));
		    break;

	    case 18:
		    r=0xFF,g=0xFF,b=0xFF;
		    ClearScreen(0);
		    for(y=0; y<ModeInfoBlock.YResolution; y++) {
		      if(y!=0 && (y%(ModeInfoBlock.YResolution/32))==0) {
			if(r < 8) {
			  r=g=b=0;
			}else {
			  r-=8;  g-=8; b-=8;
			}
		      }
		      for(x=0; x<ModeInfoBlock.XResolution; x++) {
			PutPixel(x,y,rgbColor(r,g,b));
		      }
		    }
//		    sprintf(str,"%d %d %d",r,g,b);   debug
//		    writeText(200,100,str,0xFFFFFFl);
		    break;

	    case 19:
		    ClearScreen(0);
		    for(y=0; y<ModeInfoBlock.YResolution; y++)
		      for(x=0; x<ModeInfoBlock.XResolution; x++)
			if(((x+y)%2)==0) PutPixel(x,y,rgbColor(0,0x7F,0x7F));
		    break;
	    case 20:
		    r=0xFF,g=0xFF,b=0xFF;
		    ClearScreen(0);
		    for(x=0; x<ModeInfoBlock.XResolution; x++) {
		      if(x!=0 && (x%(ModeInfoBlock.XResolution/32))==0) {
			if(r < 8) {
			  r=g=b=0;
			}else {
			  r-=8;  g-=8;  b-=8;
			}
		      }
		      for(y=0; y<ModeInfoBlock.YResolution; y++) {
			PutPixel(x,y,rgbColor(r,g,b));
		      }
		    }
		    break;
	    case 21:
		    r=0xFF,g=0xFF,b=0xFF;
		    ClearScreen(0);
		    for(x = ModeInfoBlock.XResolution-1; x > 0; x--) {
		      if((x!=ModeInfoBlock.XResolution-1) && ((x%(ModeInfoBlock.XResolution/32)) == 0)) {
			if(r < 8) {
			  r=g=b=0;
			}else {
			  r-=8;  g-=8;  b-=8;
			}
		      }
		      for(y=0; y < ModeInfoBlock.YResolution ; y++) {
			PutPixel(x,y,rgbColor(r,g,b));
		      }
		    }
		    break;
	    case 22:
		    r=0xFF,g=0xFF,b=0xFF;
		    ClearScreen(0);
		    for(x=0; x<ModeInfoBlock.XResolution; x++) {
		      if(x!=0 && (x%(ModeInfoBlock.XResolution/16))==0) {
			if(r < 16) {
			  r=g=b=0;
			}else {
			  r-=16;  g-=16;  b-=16;
			}
		      }
		      for(y=0; y<ModeInfoBlock.YResolution; y++) {
			PutPixel(x,y,rgbColor(r,g,b));
		      }
		    }
		    break;
	    case 23:
		    r=0xFF,g=0xFF,b=0xFF;
		    ClearScreen(0);
		    for(x = ModeInfoBlock.XResolution-1; x > 0; x--) {
		      if((x!=ModeInfoBlock.XResolution-1) && ((x%(ModeInfoBlock.XResolution/16)) == 0)) {
			if(r < 16) {
			  r=g=b=0;
			}else {
			  r-=16;  g-=16;  b-=16;
			}
		      }
		      for(y=0; y < ModeInfoBlock.YResolution ; y++) {
			PutPixel(x,y,rgbColor(r,g,b));
		      }
		    }
		    break;
	    case 24:
		    ClearScreen(0);
		    col=ModeInfoBlock.XResolution/7;
		    row=ModeInfoBlock.YResolution/12;
		    for(x=0; x < col; x++)
		    for(y=0; y < (row*8)+1; y++) {
			PutPixel(x,y,rgbColor(0xcc,0xcc,0xcc));
			PutPixel(x+col,y,rgbColor(0xff,0xff,0));
			PutPixel(x+(col*2),y,rgbColor(0,0xff,0xff));
			PutPixel(x+(col*3),y,rgbColor(0,0xff,0));
			PutPixel(x+(col*4),y,rgbColor(0xff,0,0xff));
			PutPixel(x+(col*5),y,rgbColor(0xff,0,0));
			PutPixel(x+(col*6),y,rgbColor(0,0,0xff));
		    }
		    for(x=(col*7); x < ModeInfoBlock.XResolution; x++)
		    for(y=0; y < (row*8)+1; y++) {
			PutPixel(x,y,rgbColor(0,0,0xff));
		    }
		    for(x=0; x < col; x++)
		    for(y=(row*8); y < (row*9)+1; y++) {
			PutPixel(x,y,rgbColor(0,0,0xff));
			PutPixel(x+col,y,rgbColor(0x13,0x13,0x13));
			PutPixel(x+(col*2),y,rgbColor(0xff,0,0xff));
			PutPixel(x+(col*3),y,rgbColor(0x13,0x13,0x13));
			PutPixel(x+(col*4),y,rgbColor(0,0xff,0xff));
			PutPixel(x+(col*5),y,rgbColor(0x13,0x13,0x13));
			PutPixel(x+(col*6),y,rgbColor(0xcc,0xcc,0xcc));
		    }
		    for(x=(col*7); x < ModeInfoBlock.XResolution; x++)
		    for(y=(row*8); y < (row*9)+1; y++) {
			PutPixel(x,y,rgbColor(0xcc,0xcc,0xcc));
		    }
		    oldcol=col;
		    lastrow=col*5;
		    col=(col*5)/4;
		    for(x=0; x < col; x++)
		    for(y=(row*9); y < ModeInfoBlock.YResolution; y++) {
			PutPixel(x,y,rgbColor(0x8,0x3e,0x59));
			PutPixel(x+col,y,rgbColor(0xff,0xff,0xff));
			PutPixel(x+(col*2),y,rgbColor(0x3a,0,0x7e));
			PutPixel(x+(col*3),y,rgbColor(0x13,0x13,0x13));
		    }
		    for(x=(col*4); x < lastrow; x++)
		    for(y=(row*9); y < ModeInfoBlock.YResolution; y++) {
			PutPixel(x,y,rgbColor(0x13,0x13,0x13));
		    }
		    for(x=0; x < (oldcol/3); x++)
		    for(y=(row*9); y < ModeInfoBlock.YResolution; y++) {
			PutPixel(lastrow+x,y,rgbColor(0,0,0));
			PutPixel(lastrow+x+(oldcol/3),y,rgbColor(0x13,0x13,0x13));
			PutPixel(lastrow+x+((oldcol/3)*2),y,rgbColor(0x26,0x26,0x26));
		    }
		    for(x=lastrow+((oldcol/3)*3); x < (oldcol*6); x++)
		    for(y=(row*9); y < ModeInfoBlock.YResolution; y++) {
			PutPixel(x,y,rgbColor(0x26,0x26,0x26));
		    }
		    for(x=(oldcol*6); x < ModeInfoBlock.XResolution; x++)
		    for(y=(row*9); y < ModeInfoBlock.YResolution; y++) {
			PutPixel(x,y,rgbColor(0x13,0x13,0x13));
		    }

		    break;
	    case 25:
		    ClearScreen(0);
		    col=ModeInfoBlock.XResolution/8;
		    for(x=0; x < col; x++)
		    for(y=0; y < ModeInfoBlock.YResolution; y++) {
			PutPixel(x,y,rgbColor(0xff,0xff,0xff));
			PutPixel(x+col,y,rgbColor(0xff,0xff,0));
			PutPixel(x+(col*2),y,rgbColor(0,0xff,0xff));
			PutPixel(x+(col*3),y,rgbColor(0,0xff,0));
			PutPixel(x+(col*4),y,rgbColor(0xff,0,0xff));
			PutPixel(x+(col*5),y,rgbColor(0xff,0,0));
			PutPixel(x+(col*6),y,rgbColor(0,0,0xff));
			PutPixel(x+(col*7),y,rgbColor(0,0,0));
		    }
		    break;
	    case 26:
		    ClearScreen(0);
		    uChar color=0xFF;
		    uLong oldcolor;
		    col=ModeInfoBlock.XResolution/4;
		    for(x=0; x < col; x++) {
		      if(ModeInfoBlock.BitsPerPixel==8){
			oldcolor=color;
			setSpecialpalette(1,&oldcolor);
		      }
		      for(y=0; y < ModeInfoBlock.YResolution; y++) {
			PutPixel(x,y,rgbColor(color,0,0));
			PutPixel(x+col,y,rgbColor(0,color,0));
			PutPixel(x+(col*2),y,rgbColor(0,0,color));
			PutPixel(x+(col*3),y,rgbColor(color,color,color));
		      }
		      color--;
		    }
		    break;
	    case 27:
		    randomize();
		    ClearScreen(0);
		    for(uLong h=0;h<0xFFFFl;h++) {
		     PutPixel(rand()%(ModeInfoBlock.XResolution-1),
		     rand()%(ModeInfoBlock.YResolution-1),
		     rgbColor(rand()%0xFF,rand()%0xFF,rand()%0xFF));
		     delay(1);
		     if(kbhit()) {
		       ch1=getch();
		       if(ch1==27)  break;
		     }
		    }
		    break;
	    }
	    if(blShow) {
	      sprintf(str,"%d*%d*%d",ModeInfoBlock.XResolution,
	      ModeInfoBlock.YResolution,ModeInfoBlock.BitsPerPixel);
	      writeText((ModeInfoBlock.XResolution/16)*7,(ModeInfoBlock.YResolution/16)*14,
			 str,rgbColor(0xFF,0xFF,0xFF));
	    }
	    if(blDelayTime) {
	      delay(delaytime);
	      if(blShowAllPattern) {
		pattern++;
		if(pattern>=TotalPattern+1 && blShowAllContinue==FALSE) break;
		if(blShowAllContinue && pattern>=TotalPattern+1) pattern=1;
		if(((*keybuffer&0x09)==0x09) && ((*keybuffer1&0x02)==0x02)){  //Left_Alt+Right_Shift
		 *(key_buf+0x1A)=0x1E;  *(key_buf+0x1C)=0x1E;
		 blPressKey=TRUE;
		 break;
		}
		if(kbhit()) {
		  ch1=getch();
		  if(ch1==27) {
		    blPressKey=FALSE;
		    break;
		  }
		}
	      }else break;
	    }else if(blSpecialKey) {
	      while(((*keybuffer&0x09)!=0x09) || ((*keybuffer1&0x02)!=0x02));  //Left_Alt+Right_Shift
	      *(key_buf+0x1A)=0x1E;  *(key_buf+0x1C)=0x1E;
	      blPressKey=TRUE;
	      break;
	    }else {

	      ch1=getch();
	      if(ch1==0) {
		ch2=getch();
		if(ch2==72||ch2==75) pattern--;
		if(ch2==80||ch2==77) pattern++;
		if(ch2==63 && !blF5) {
		  blF5=TRUE;
		}else if(ch2==63 && blF5) {
		  blF5=FALSE;
		}
	      }else if(ch1==13||ch1==32) { pattern++;
	      }else if(ch1==27) break;

	      if(blF5) {
	      while((((*keybuffer&0x09)!=0x09) || ((*keybuffer1&0x02)!=0x02)));
		 *(key_buf+0x1A)=0x1E;  *(key_buf+0x1C)=0x1E;
		 blPressKey=TRUE;
		 break;
	      }

	      if(pattern == TotalPattern+1) pattern=1;
	      else if(pattern == 0) pattern=TotalPattern;

	    }
	}while(ch2!=45);
	setVBEMode(oldMode);
      }
   }

  }else if(blTextmode) {
   do{
      if(!setVBEMode(mode)) return FALSE;
      _setcursortype(_NOCURSOR);
      x=ax=dx=6;  y=ay=4;   cx=4; cy=22; bx=40; by=4;
      gotoxy(3,2);
      printf("Character set mode:%02dh",mode);
      switch(mode) {
       case 0:
       case 1:
	      maxx=40; maxy=25;
	      break;
       case 2:
       case 3:
       case 7:
	      maxx=80; maxy=25;
	      for(i=0;i<16;i++) {
		for(j=0;j<10;j++)
		  asus.PrintCh(bx++,by,j+48,(i*0x10)+(0x0f-i),1);
		for(j=0;j<26;j++)
		  asus.PrintCh(bx++,by,j+65,(i*0x10)+(0x0f-i),1);
		bx=40; by++;
	      }
	      break;
      }

      for(k=0;k<2;k++) {    //color pattern
	for(i=0;i<16;i++) {
	  for(j=0;j<2;j++)
	    asus.PrintCh(cx+j,cy,219,i,1);
	  cx=cx+j;
	}
	cy++;  cx=4;
      }

      for(i=1;i<=maxx;i++) {                   //frame
	asus.PrintCh(i,1,223,0x0f,1);
	asus.PrintCh(i,maxy,220,0x0f,1);
      }
      for(i=1;i<=maxy;i++) {
	asus.PrintCh(1,i,219,0x0f,1);
	asus.PrintCh(maxx,i,219,0x0f,1);
      }

      for(i=0 ; i < 16 ;i++)  {
	gotoxy(ax+(i*2),ay-1); printf("%X",i);
	gotoxy(ax+(i*2),ay-1); printf("%X",i);
	gotoxy(ax-3,ay+i); printf("%XX",i);
      }

      for(i=0;i<=0xff;i++) {
	 asus.PrintCh(ax,ay,i,7,1);
	 ax+=2;
	 if(ax>=32+dx) {
	    ax=dx; ay++;
	 }
      }

      delay(delaytime);
      if(blTestConfirm) {
	gotoxy(26,2); printf("Correct? y/n");
	do{
	  ch1=getch();
	  if(ch1=='y' || ch1 =='Y') {
	    setVBEMode(oldMode);
	    return TRUE;
	  }else if(ch1=='n' || ch1 =='N') {
	    setVBEMode(oldMode);
	    return FALSE;
	  }
	}while(1);
      }else {

       if(((*keybuffer&0x09)==0x09) && ((*keybuffer1&0x02)==0x02)){  //Left_Alt+Right_Shift
	  *(key_buf+0x1A)=0x1E;  *(key_buf+0x1C)=0x1E;
	  blPressKey=TRUE;
	  break;
       }
       if(kbhit()) {
	 ch1=getch();
	 if(ch1==0) {
	  ch2=getch();
	  if((ch2==63)&& !blF5) {
	     blF5=TRUE;
	  }else if((ch2==63)&& blF5){
	     blF5=FALSE;
	  }
	 }else if(ch1==27) {
	   blPressKey=FALSE;
	   break;
	 }
       }
      }

      if(blAutoLoop)  mode=textm[mindex++];
      else break;
   }while(mindex<=textmindex);
   setVBEMode(oldMode);
   if(mindex>textmindex) blPressKey=TRUE;
  }

  return blPressKey;
}


void writeText(uLong x,uLong y,char *str,uLong color)
{
 unsigned char   byte;
 int     i,j,k,length,ch;
 unsigned char   *font;

 if(ModeInfoBlock.XResolution>=1024)
 {
 font = font8x16;
 length = strlen(str);
 for (k = 0; k < length; k++) {
     ch = str[k];
     for (j = 0; j < 16; j++) {
	 byte = *(font + ch * 16 + j);
	 for (i = 0; i < 8; i++) {
	     if ((byte & 0x80) != 0)
		 {
		 PutPixel(x+(i*2),y+(j*2),color);
		 PutPixel(x+(i*2)+1,y+(j*2),color);
		 PutPixel(x+(i*2),y+(j*2)+1,color);
		 PutPixel(x+(i*2)+1,y+(j*2)+1,color);
		 }
	     byte <<= 1;
	     }
	 }
     x += 16;
     }
 }
 else {
 font = font8x16;
 length = strlen(str);
 for (k = 0; k < length; k++) {
     ch = str[k];
     for (j = 0; j < 16; j++) {
	 byte = *(font + ch * 16 + j);
	 for (i = 0; i < 8; i++) {
	     if ((byte & 0x80) != 0)
		 PutPixel(x+i,y+j,color);
	     byte <<= 1;
	     }
	 }
     x += 8;
     }
 }
}



Boolean VESA_Info(int mode)
{
  unsigned far* p;
  int i,x,y,last,next,now,index=0;
  int res,Mode_total,ix=3,iy=8,smode,colorattr;
  char ch1,ch2,str[20],temp[10],temp2[30],temp3[30];
  Boolean blDetectOK=FALSE;

  if(MM.blSet()==FALSE) return FALSE;
  MM.EnableA20();

  if (!getVbeInfo())   {
   printf("No VESA VBE detected\n");
   return FALSE;
  }else  {
   for(p = VbeInfoBlock.VideoModePtr; *p !=(unsigned)-1; p++)	{
       if (getModeInfo(*p)==TRUE)  Mode_Num[index++]=*p;
       if(*p==mode) { now=index-1; next=index; last=index-2; blDetectOK=TRUE; }
   }
   if(!blDetectOK && mode!=0 ) return FALSE;
   Mode_total=index-1;
   if(VbeInfoBlock.Capabilities & 0x1) smode=8;
   else smode=15;

   gotoxy(1,5);

   if(mode<100) {
      if(asus.forRD8UI==FALSE) {
      for(i=0;i<18;i++){
	if(i<3) asus.PrintStr(1,5+i,InfoItem[i],-1,0x07);
	if(i>=3&&i<17) asus.PrintStr(1,5+i,InfoItem[3],-1,0x07);
	if(i==17) asus.PrintStr(1,5+i,InfoItem[4],-1,0x07);
      }
      }
      if(asus.forRD8UI==TRUE)  printf("\n");
      asus.PrintStr(1,4,VbeInfoBlock.OEMStringPtr,0,0x09);
      if(asus.forRD8UI==TRUE) printf("\n");
      asus.PrintStr(1,4,"Support Mode ",-1,0x0a);

      for(i=0;i<=Mode_total;i++) {
	  getModeInfo(Mode_Num[i]);
	  if(asus.forRD8UI==TRUE)  printf("\n");

	  sprintf(temp2,"%X",Mode_Num[i]);
	  asus.PrintStr(ix,iy,temp2,-1,0x0a);
	  if(asus.forRD8UI==TRUE) printf(":");
	  if(ModeInfoBlock.BitsPerPixel < smode)
	  colorattr=0x08;	  //textattr(0x08);
	  else  colorattr=0x0f;  //textattr(0x0F);
	  switch(ModeInfoBlock.BitsPerPixel) {
	    case  4:
		    if(ModeInfoBlock.XResolution<150 && ModeInfoBlock.YResolution<80) {
		      sprintf(temp2,"%-4dx %-4d Text ",ModeInfoBlock.XResolution,
		      ModeInfoBlock.YResolution);
		      asus.PrintStr(ix+6,iy++,temp2,-1,colorattr);
		    }else {
		      sprintf(temp2,"%-4dx %-4dx 16 ",ModeInfoBlock.XResolution,
		      ModeInfoBlock.YResolution);
		      asus.PrintStr(ix+6,iy++,temp2,-1,colorattr);
		    }
		    break;
	    case  8:
		    sprintf(temp2,"%-4dx %-4dx 256 ",ModeInfoBlock.XResolution,
		    ModeInfoBlock.YResolution);
		    asus.PrintStr(ix+6,iy++,temp2,-1,colorattr);
		    break;
	    case 15:
		    sprintf(temp2,"%-4dx %-4dx 32K ",ModeInfoBlock.XResolution,
		    ModeInfoBlock.YResolution);
		    asus.PrintStr(ix+6,iy++,temp2,-1,colorattr);
		    break;
	    case 16:
		    sprintf(temp2,"%-4dx %-4dx 64K ",ModeInfoBlock.XResolution,
		    ModeInfoBlock.YResolution);
		    asus.PrintStr(ix+6,iy++,temp2,-1,colorattr);
		    break;
	    case 24:
		    sprintf(temp2,"%-4dx %-4dx 24bit ",ModeInfoBlock.XResolution,
		    ModeInfoBlock.YResolution);
		    asus.PrintStr(ix+6,iy++,temp2,-1,colorattr);
		    break;
	    case 32:
		    sprintf(temp2,"%-4dx %-4dx 16.8M ",ModeInfoBlock.XResolution,
		    ModeInfoBlock.YResolution);
		    asus.PrintStr(ix+6,iy++,temp2,-1,colorattr);
		    break;
	  }
	  if(iy==22) {
	    if(ix==55) {
	      if(asus.forRD8UI==FALSE) {
	       asus.PrintStr(1,23,"Press any Key chage next page",0,0x87);
	       getch();
	       ix=3; iy=8;
	       clrscr();
	       Logo();

	       for(int i=0;i<18;i++){
		if(i<3) asus.PrintStr(1,5+i,InfoItem[i],-1,0x07);
		if(i>=3&&i<17) asus.PrintStr(1,5+i,InfoItem[3],-1,0x07);
		if(i==17) asus.PrintStr(1,5+i,InfoItem[4],-1,0x07);
	       }
	       asus.PrintStr(1,4,VbeInfoBlock.OEMStringPtr,0,0x09);
	       if(asus.forRD8UI==TRUE) printf("\n");
	       asus.PrintStr(1,4,"Support Mode ",-1,0x0a);
	      }
	    }else {
	      ix+=26; iy=8;
	    }
	  }
      }
    if(asus.forRD8UI==TRUE)  {
      printf("\n");
    }
   }else {
   VBE_Info(1,4);
   do{
    gotoxy(62,4);
    printf(" [Left/Up Key]:");
    gotoxy(62,5);
    printf(" Last Mode.");
    gotoxy(62,7);
    printf(" [Right/Down Key]: ");
    gotoxy(62,8);
    printf(" Next Mode.");
    gotoxy(62,10);
    printf(" [Esc Key]: ");
    gotoxy(62,11);
    printf(" Quit.");
    gotoxy(62,13);
    printf(" [Enter Key]: ");
    gotoxy(62,14);
    printf(" Test Mode.");
    x=1; y=13;
    gotoxy(x,y);
    printf("Mode: %03X\n",mode);
    if (getModeInfo(mode)==TRUE)    {
       dwBaseAddress=FP_SEG(ModeInfoBlock.PhyBasePtr)*0x10000l;
//       blMemorySizing();
       gotoxy(x,y+1);
       printf("ModeAttributes   : %X   ",ModeInfoBlock.ModeAttributes);
       gotoxy(x,y+2);
       printf("WinAAttributes   : %X   ",ModeInfoBlock.WinAAttributes);
       gotoxy(x,y+3);
       printf("WinBAttributes   : %X   ",ModeInfoBlock.WinBAttributes);
       gotoxy(x,y+4);
       printf("WinGranularity   : %d   ",ModeInfoBlock.WinGranularity);
       gotoxy(x,y+5);
       printf("WinSize          : %d   ",ModeInfoBlock.WinSize);
       gotoxy(x,y+6);
       printf("WinASegment      : %X   ",ModeInfoBlock.WinASegment);
       gotoxy(x,y+7);
       printf("WinBSegment      : %X   ",ModeInfoBlock.WinBSegment);
       gotoxy(x,y+8);
//       printf("WinFuncPtr       : %X   ",ModeInfoBlock.WinFuncPtr);
       printf("PhyBasePtr       : %04X   ",FP_SEG(ModeInfoBlock.PhyBasePtr));
       gotoxy(x,y+9);
       printf("BytesPerScanLine : %d   ",ModeInfoBlock.BytesPerScanLine);
       x=35; y=4;
       gotoxy(x,y);
       printf("XResolution        : %d   ",ModeInfoBlock.XResolution);
       gotoxy(x,y+1);
       printf("YResolution        : %d   ",ModeInfoBlock.YResolution);
       gotoxy(x,y+2);
       printf("XCharSize          : %d ",ModeInfoBlock.XCharSize);
       gotoxy(x,y+3);
       printf("YCharSize          : %d ",ModeInfoBlock.YCharSize);
       gotoxy(x,y+4);
       printf("NumberOfPlanes     : %d ",ModeInfoBlock.NumberOfPlanes);
       gotoxy(x,y+5);
       printf("BitsPerPixel       : %d ",ModeInfoBlock.BitsPerPixel);
       if(ModeInfoBlock.BitsPerPixel<smode)
	  asus.PrintStr(1,23,"This mode program not Support !!!",0,0x0C);
       gotoxy(x,y+6);
       printf("NumberOfBanks      : %X ",ModeInfoBlock.NumberOfBanks);
       gotoxy(x,y+7);
       printf("MemoryModel        : %X ",ModeInfoBlock.MemoryModel);
       gotoxy(x,y+8);
       printf("BankSize           : %X ",ModeInfoBlock.BankSize);
       gotoxy(x,y+9);
       printf("NumberOfImagePages : %d ",ModeInfoBlock.NumberOfImagePages);
       gotoxy(x,y+10);
       printf("RedMaskSize        : %d ",ModeInfoBlock.RedMaskSize);
       gotoxy(x,y+11);
       printf("GreenMaskSize      : %d ",ModeInfoBlock.GreenMaskSize);
       gotoxy(x,y+12);
       printf("BlueMaskSize       : %d ",ModeInfoBlock.BlueMaskSize);
       gotoxy(x,y+13);
       printf("RsvdMaskSize       : %d ",ModeInfoBlock.RsvdMaskSize);
       gotoxy(x,y+14);
       printf("RedFieldPosition   : %d ",ModeInfoBlock.RedFieldPosition);
       gotoxy(x,y+15);
       printf("GreenFieldPosition : %d ",ModeInfoBlock.GreenFieldPosition);
       gotoxy(x,y+16);
       printf("BlueFieldPosition  : %d ",ModeInfoBlock.BlueFieldPosition);
       gotoxy(x,y+17);
       printf("RsvdFieldPosition  : %d ",ModeInfoBlock.RsvdFieldPosition);
       gotoxy(x,y+18);
       memsize=(uLong)(ModeInfoBlock.BytesPerScanLine) * (uLong)(ModeInfoBlock.YResolution);
       if(FP_SEG(ModeInfoBlock.PhyBasePtr))
       printf("MemorySize         : %-8lX (%-2.2fMB) ",memsize,(float)memsize/1024/1024);
       else
       printf("MemorySize         :                   ");
    }
    ch1=getch();
    asus.ClearLine(23,0x07);
    if(ch1==0) ch2=getch();
    if(ch1==27) break;

    if(ch1==13) {
       if(ModeInfoBlock.BitsPerPixel>=smode) {
	 oldMode = getVBEMode();
	 if(setVBEMode(mode)==TRUE) {
	  switch(ModeInfoBlock.BitsPerPixel) {
	  case  8:
		  setDACpalette();  //set 8 bit palette
	  case 15:
	  case 16:
	  case 24:
	  case 32:
		  ClearScreen(0);
		  int col=ModeInfoBlock.XResolution/16;
		  for(x=0; x < col; x++)
		    for(y=0; y < ModeInfoBlock.YResolution; y++) {
			PutPixel(x,y,rgbColor(0xFF,0,0));
			PutPixel(x+col,y,rgbColor(0xD7,0,0));
			PutPixel(x+(col*2),y,rgbColor(0xAF,0,0));
			PutPixel(x+(col*3),y,rgbColor(0x87,0,0));
			PutPixel(x+(col*4),y,rgbColor(0,0xFF,0));
			PutPixel(x+(col*5),y,rgbColor(0,0xD7,0));
			PutPixel(x+(col*6),y,rgbColor(0,0xAF,0));
			PutPixel(x+(col*7),y,rgbColor(0,0x87,0));
			PutPixel(x+(col*8),y,rgbColor(0,0,0xFF));
			PutPixel(x+(col*9),y,rgbColor(0,0,0xD7));
			PutPixel(x+(col*10),y,rgbColor(0,0,0xAF));
			PutPixel(x+(col*11),y,rgbColor(0,0,0x87));
			PutPixel(x+(col*12),y,rgbColor(0xFF,0xFF,0xFF));
			PutPixel(x+(col*13),y,rgbColor(0xD7,0xD7,0xD7));
			PutPixel(x+(col*14),y,rgbColor(0xAF,0xAF,0xAF));
			PutPixel(x+(col*15),y,rgbColor(0x87,0x87,0x87));
		    }
		  sprintf(str,"%d*%d*%d",ModeInfoBlock.XResolution,
		  ModeInfoBlock.YResolution,ModeInfoBlock.BitsPerPixel);
		  writeText((ModeInfoBlock.XResolution/16)*7,(ModeInfoBlock.YResolution/16)*14,
			    str,rgbColor(0xFF,0xFF,0xFF));

	  break;
	  }

	  do{
	    ch1=getch();
	    if(ch1==27) {
	    setVBEMode(oldMode);
	    Logo();
	    VBE_Info(1,4);
	    break;
	    }
	    if(ch1==0) ch2=getch();
	  }while(ch2!=45);
	 }else {
	  asus.PrintStr(1,23,"This mode not Support DOS mode !!!",0,0x0C);
	 }
       }
       ch2=0;
       }
       if((ch2==77)||(ch2==80))
	 {
	 if(next<=Mode_total)
	   {
	    last=now;     now=next;     mode=Mode_Num[next];
	    next=next+1;
	   }
	 ch2=0;
	 }
       if((ch2==75)||(ch2==72))
	 {
	 if(last>=0)
	   {
	    next=now;    now=last;    mode=Mode_Num[last];
	    last=last-1;
	   }
	  ch2=0;
	 }
//  printf("%04d %04d ",ch1,ch2);
    }while(ch2!=45);
   }
  }
  return TRUE;
}


Boolean Detect_Mode(int mode,int method)
{
  unsigned far* p;
  int index=0,Mode_total,oldMode;
//  char ch1,ch2;
  Boolean blmodeOK=FALSE;
  char temp[10];


  if(!getVbeInfo())  {
    printf("No VESA VBE detected\n");
    return FALSE;
  }else  {
    for (p = VbeInfoBlock.VideoModePtr; *p !=(unsigned)-1; p++)    {
      if(getModeInfo(*p)==TRUE)  Mode_Num[index++]=*p;
      if(*p==mode) blmodeOK=TRUE;
    }
//  Mode_total=index-1;
    if(mode>=100)  {
      sprintf(temp,"Mode: %03X",mode);
      asus.PrintStr(1,7,temp,0,0x0B);
      if(method) {
	oldMode = getVBEMode();
	MM.blSet();
      }
      if(getModeInfo(mode)==TRUE && blmodeOK==TRUE)      {
	asus.PrintStr(1,10,"This mode is Support !!!",0,0x17);
	if(method==1) {
//	  asus.blSaveScreen(0);
	  if(setVBEMode(mode)) {
	    setVBEMode(oldMode);
//	    asus.RestoreScreen(0);
	    Logo();
	    asus.PrintStr(1,7,temp,0,0x0B);
	    asus.PrintStr(1,10,"This mode is Support !!!",0,0x17);
	    asus.PrintStr(1,12,"Support DOS mode !!!",0,0x17);
	  }else {
	    asus.PrintStr(1,12,"not Support DOS mode !!!",0,0x1C);
	    return FALSE;
	  }
	}
      }else {
	asus.PrintStr(1,10,"This mode not Support !!!",0,0x1C);
	return FALSE;
      }
    }else return FALSE;
  }
  return TRUE;
}




uLong rgbColor(uChar r,uChar g,uChar b)
{
  int i;

  if(ModeInfoBlock.BitsPerPixel==8) {
    for (i = 0; i < 256; i++ ) {
      if(pal[i].Red == r && pal[i].Green == g && pal[i].Blue == b)
	 return i;
    }
    return 15;
  }

  return ((uLong) ((r >>(8-ModeInfoBlock.RedMaskSize) ) &
		  ((1<<ModeInfoBlock.RedMaskSize)-1) ) <<
		  ModeInfoBlock.RedFieldPosition)  |
	 ((uLong) ((g >>(8-ModeInfoBlock.GreenMaskSize) ) &
		  ((1<<ModeInfoBlock.GreenMaskSize)-1) ) <<
		  ModeInfoBlock.GreenFieldPosition) |
	 ((uLong) ((b >>(8-ModeInfoBlock.BlueMaskSize) ) &
		  ((1<<ModeInfoBlock.BlueMaskSize)-1) ) <<
		  ModeInfoBlock.BlueFieldPosition);
}



void VBE_Info(int x,int y)
{
  int i=0,sx=0,sy=0;

  gotoxy(x,y);
//  printf("%s",&VbeInfoBlock.VESASignature);
//  gotoxy(x,++y);
  printf("VBE Version : %04X",VbeInfoBlock.VESAVersion);
  gotoxy(x,++y);
  if(strlen(VbeInfoBlock.OEMStringPtr)<19)
  printf("OEM  String : %s",VbeInfoBlock.OEMStringPtr);
  else {
	printf("OEM  String : ");
	sx=x+14;
	while(i!=strlen(VbeInfoBlock.OEMStringPtr)) {
	 gotoxy(sx++,y);
	 printf("%c",VbeInfoBlock.OEMStringPtr[i++]);
	 if(sx==32) { sx=x+14; ++y; sy++; }
	 if(sy==4) { --y; break; }
	}
  }
  gotoxy(x,++y);
//  printf("%04X\n",VbeInfoBlock.Capabilities);
//  printf("VideoModePtr: %04X\n",VbeInfoBlock.VideoModePtr);
  printf("Video Memory: %ldMB ",(VbeInfoBlock.TotalMemory*64l)/1024);
  gotoxy(x,++y);
  printf("DAC width is: %s ",  (VbeInfoBlock.Capabilities & 0x1)? "8bits" : "6bits");
  gotoxy(x,++y);
  printf("VGA compatible: %s ",  (VbeInfoBlock.Capabilities & 0x2)? "No" : "Yes");
//  gotoxy(x,++y);
//  printf("OEMSoftwareRev: %s\n",&VbeInfoBlock.OEMSoftwareRev);
//  gotoxy(x,++y);
//  printf("OEMVendorNamePtr: %s\n",&VbeInfoBlock.OEMVendorNamePtr);
//  printf("OEMProductNamePtr: %04X\n",&VbeInfoBlock.OEMProductNamePtr);
//  printf("OEMProductRevPtr: %04X\n",&VbeInfoBlock.OEMProductRevPtr);
//  printf("%s\n",  (VbeInfoBlock.Capabilities & 0x4)? "use the blank bit in Function 09h"
//	 : "Normal RAMDAC operation");
//  printf("%s\n",  (VbeInfoBlock.Capabilities & 0x8)? "Hardware stereoscopic signaling supported"
//	 : "No Hardware stereoscopic signaling supported");
//  printf("%s\n",  (VbeInfoBlock.Capabilities & 0x16)? "stereo signaling supported via VESA EVC connector"
//	 : "xstereo signaling supported via external VESA stereo connector");
}


void line(int x1,int y1,int x2,int y2,uLong color)
{
 int d; /* Decision variable */
 int dx,dy; /* Dx and Dy values for the line */
 int Eincr,NEincr; /* Decision variable increments */
 int yincr; /* Increment for y values */
 int t; /* Counters etc. */
 #define ABS(a) ((a) >= 0 ? (a) : -(a))
 dx = ABS(x2 - x1);
 dy = ABS(y2 - y1);
 if (dy <= dx)
 {
  if (x2 < x1)
  {
   t = x2; x2 = x1; x1 = t; /* Swap X coordinates */
   t = y2; y2 = y1; y1 = t; /* Swap Y coordinates */
  }
  if (y2 > y1)   yincr = 1;
  else  yincr = -1;

  d = 2*dy - dx; /* Initial decision variable value */
  Eincr = 2*dy; /* Increment to move to E pixel */
  NEincr = 2*(dy - dx); /* Increment to move to NE pixel */
  PutPixel(x1,y1,color); /* Draw the first point at (x1,y1) */
  for (x1++; x1 <= x2; x1++)
  {
   if (d < 0)   d += Eincr; /* Choose the Eastern Pixel */
   else
   {
    d += NEincr; /* Choose the North Eastern Pixel */
    y1 += yincr; /* (or SE pixel for dx/dy < 0!) */
   }
   PutPixel(x1,y1,color);
//   putPixel(x1,y1,color); /* Draw the point */
  }
 }
 else
 {
  if (y2 < y1)
  {
   t = x2; x2 = x1; x1 = t; /* Swap X coordinates */
   t = y2; y2 = y1; y1 = t; /* Swap Y coordinates */
  }
  if (x2 > x1) yincr = 1;
  else  yincr = -1;
  d = 2*dx - dy; /* Initial decision variable value */
  Eincr = 2*dx; /* Increment to move to E pixel */
  NEincr = 2*(dx - dy); /* Increment to move to NE pixel */
  PutPixel(x1,y1,color); /* Draw the first point at (x1,y1) */
/* Incrementally determine the positions of the remaining pixels */
  for (y1++; y1 <= y2; y1++)
  {
   if (d < 0) d += Eincr; /* Choose the Eastern Pixel */
   else
   {
    d += NEincr; /* Choose the North Eastern Pixel */
    x1 += yincr; /* (or SE pixel for dx/dy < 0!) */
   }
   PutPixel(x1,y1,color); /* Draw the point */
  }
 }
}

Boolean SetOutputDevice(uInt type)
{
  union REGS in,out;
  int i,j=0,ichip=0;
  char OEMString[5][10]={"ATI","NVidia","INTEL","SIS"};

  if(!getVbeInfo())  {
    printf("No VESA VBE detected\n");
    return FALSE;
  }else  {
  asus.PrintStr(1,6,VbeInfoBlock.OEMStringPtr,0,0x09);
  strupr(VbeInfoBlock.OEMStringPtr);
   do{
   j=0;
   for(i=0;i<strlen(VbeInfoBlock.OEMStringPtr);i++) {
     for(;j<strlen(OEMString[ichip]);) {
       if(OEMString[ichip][j] != VbeInfoBlock.OEMStringPtr[i]) {
	   j=0;     break;
       }else{
	   j++;     break;
       }
     }
   }
   if( (j==strlen(OEMString[ichip])) )  break;
   ichip++;
   }while(ichip!=4);
   switch(type)
   {
     case 1: // LCD
     case 2: // CRT
     case 3: // LCD+CRT
     case 8: // DVI
	    if(j == 6 && ichip == 1) {    //NVidia
	      in.x.ax = 0x4F14;
	      in.x.bx = 0x0085;
	      int86(0x10, &in, &out);
	      if(out.x.ax != 0x4F) return FALSE;
	      in.x.ax = 0x4F14;
	      in.x.bx = 0x0185;
	      in.x.cx = type*0x100+type;
	      int86(0x10, &in, &out);
	      if(out.x.ax != 0x4F) return FALSE;
	    }else if(j == 3 && ichip == 0){   //ATI
	      in.x.ax = 0xa084;
	      in.h.bh = 1;
	      in.h.cl = type;
	      int86(0x10, &in, &out);
	      if((out.h.bl& type) != type) return FALSE;
	    }else if(j == 5 && ichip == 2) {     //INTEL
	      if(type == 1) type = 0x08;
	      else if(type == 2) type = 1;
	      else if(type == 3) type = 0x09;
	      else if(type == 8) type = 0x04;
	      in.x.ax = 0x5f64;
	      in.x.bx = 0;
	      in.x.cx = type;
	      int86(0x10, &in, &out);
	      if(out.x.ax != 0x5F) return FALSE;
	    }else if(j == 3 && ichip == 3) {     //SIS
	      if(type == 1) type= 2;
	      else if(type == 2) type= 1;
	      in.x.ax = 0x1402;
	      in.x.bx = type;
	      int86(0x10, &in, &out);
	    }
	    break;
     case 4:  //TVNTSC
     case 5:  //TVPAL
	    if(j == 6 && ichip == 1) {    //NVidia
	      in.x.ax = 0x4F14;
	      in.x.bx = 0x0105;
	      in.x.cx = type - 3;
	      int86(0x10, &in, &out);
	      if(out.x.ax != 0x4F) return FALSE;
	      in.x.ax = 0x4F14;
	      in.x.bx = 0x0185;
	      in.x.cx = 0x0404;
	      int86(0x10, &in, &out);
	      if(out.x.ax != 0x4F) return FALSE;
	    }else if(j == 3 && ichip == 0){    //ATI
	      in.x.ax = 0xa083;
	      in.h.bl = 0xf7;
	      int86(0x10, &in, &out);
	      in.x.ax = 0xa070;
	      in.h.bl = 3;
	      in.h.cl = type - 4;
	      int86(0x10, &in, &out);
	      in.x.ax = 0xa084;
	      in.h.bh = 1;
	      in.h.cl = 4;
	      int86(0x10, &in, &out);
	      if((out.h.bl& type) != type) return FALSE;
	    }else if(j == 5 && ichip == 2) {     //INTEL
	      if(type == 4) type = 1;
	      else if(type == 5) type = 2;
	      in.x.ax = 0x5f36;
	      in.x.bx = type * 0x100;
	      int86(0x10, &in, &out);
	      if(out.x.ax != 0x5F) return FALSE;
	      in.x.ax = 0x5f64;
	      in.x.bx = 0;
	      in.x.cx = 0x02;
	      int86(0x10, &in, &out);
	      if(out.x.ax != 0x5F) return FALSE;
	    }else if(j == 3 && ichip == 3) {     //SIS
	      in.x.ax = 0x1405;
	      in.x.bx = type;
	      int86(0x10, &in, &out);
	      in.x.ax = 0x1402;
	      in.x.bx = 4;
	      int86(0x10, &in, &out);
	    }
	    break;
   }
  }
  return TRUE;
}

void SaveFile(unsigned long LastMemAddr)
{
  FILE *fp;

  if ((fp = fopen ("video.log","w+")) == NULL){
   gotoxy(1,16);
   printf(" file open error !");
   End(-1);
   }
  fprintf(fp, "%lX",LastMemAddr);
  fclose(fp);
}
/**********************************************************************/
void LoadFile(void)
{
  FILE *fp;

  if((fp=fopen("video.log","r+"))==NULL) {
     LastMemAddr=0;
  } else {
    fscanf(fp, "%lX",&LastMemAddr);
  }
  fclose(fp);
}
