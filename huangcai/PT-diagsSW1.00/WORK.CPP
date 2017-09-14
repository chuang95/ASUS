#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include<dos.h> 
#include "dir.h"
#include "PT-diags.h"
#include "Extern.h"
#include "work.h"

BOOL blCmpData(char str[],char s_File[],char t_File[])
{
  FILE *fs,*ft;
  char s1[80]="\0";
  char d[80]="\0";
  char ch1;
  BOOL blResultOK=FALSE;
  BOOL blMatch=FALSE;

  textcolor(15);
  if((fs=fopen(s_File,"r"))==NULL){
    textbackground(4);
    cprintf("\n\rERROR !! Can't Open %s !!\n\r",s_File);
	textbackground(0);
    fcloseall();
    return blResultOK;
  }

  int k=0,i=0,j=0;

  if(strlen(str)>1){
    while(((ch1=getc(fs))!=EOF)){
      if(ch1==str[i]){
	i++;
	if(i==(strlen(str))){
	  blMatch=TRUE;
	  j++;
	}
      }
      else if(blMatch){
	if((ch1!='\0') && (ch1!='\n')){
	  d[k]=ch1;
	  k++;
	}
	else{
	  blMatch=FALSE;
	  break;
	}
      }
      else i=0;
    }
    if(j==0){
      printf("String Not Found!!\n");
      return blResultOK;
    }
  }
  fclose(fs);
  if((ft=fopen(t_File,"r"))==NULL){
    textbackground(4);
    cprintf("\n\rERROR !! Can't Open %s !!\n\r",t_File);
	textbackground(0);
    fcloseall();
    return blResultOK;
  }

  if(strlen(d)>0){

    char ch2;
    i=0; k=0;j=0;

    while(!feof(ft)) {
      fgets(s1,80,ft);
      if(s1[0]=='\n'||s1[0]=='\0') break;
      if((strstr(s1,d))!=NULL){
	printf("Match!\n");
	printf("The Line Is ==> %s",s1);
	blResultOK=TRUE;
	break;
      }
    }
    if(!blResultOK) printf("No Match String!!\n");
    fcloseall();
  }
  return blResultOK;
}
//BOOL blCopyData(char str4[],char str5[],char s_File[],char t_File[])
//{
//  FILE *fs,*ft;
//  char s1[80*40]="\0";
//  char d[80]="\0";
//  char ch1;
//  BOOL blResultOK=FALSE;
//  BOOL blMatch=FALSE;
//
//  textcolor(15);
//  if((fs=fopen(s_File,"r"))==NULL){
//    textbackground(4);
//    cprintf("\n\rERROR !! Can't Open %s !!\n\r",s_File);
//    fcloseall();
//    return blResultOK;
//  }
//
//  int k=0,i=0,j=0;
//  if(strlen(str4)>1){
//
//    while(((ch1=getc(fs))!=EOF)){
//      if(ch1==str4[i]){
//	i++;
//	if(i==(strlen(str4))){
//	  blMatch=TRUE;
//	  j++;
//	}
//      }
//      else if(blMatch){
//	if((ch1!='\0') && (ch1!='\n')){
//	  d[k]=ch1;
//	  k++;
//	}
//	else{
//	  blMatch=FALSE;
//	  break;
//	}
//      }
//      else i=0;
//    }
//    if(j==0){
//      printf("String Not Found!!\n");
//      return blResultOK;
//    }
//  }
//  fclose(fs);
//
//  if((ft=fopen(t_File,"rb+"))==NULL){
//    textbackground(4);
//    cprintf("\n\rERROR !! Can't Open %s !!\n\r",t_File);
//    fcloseall();
//    return blResultOK;
//  }
//
//  if(strlen(d)>0){
//
//    char ch2;
//    i=0; k=0;j=0;
//    char tmpc;
//
//    while((tmpc=fgetc(ft))!=EOF) {
//       if(!blMatch){
//	 if(tmpc == str5[j]){
//	   j++;
//	   if(j == (strlen(str5))){
//	     blMatch=TRUE;
//	     j=0;
//	     tmpc=fgetc(ft);
//	   }
//	 } else j=0;
//       } else {
//	 s1[j]=tmpc;
//	 j++;
//       }
//    }
//    if(j==0){
//      printf("Copy Fail!!\nString Not Found!!\n");
//      return blResultOK;
//    }
//    j=0;
//    blMatch=FALSE;
//    fseek(ft,0,SEEK_SET);
//    while((tmpc=fgetc(ft))!=EOF) {
//       if(!blMatch){
//	 if(tmpc == str5[j]){
//	   j++;
//	   if(j == (strlen(str5))){
//	     blMatch=TRUE;
//	     j=0;
//	   }
//	 } else j=0;
//       } else {
//	 fseek(ft,-1,SEEK_CUR);
//
//	 if(fputs(d,ft)==EOF){
//	   printf("Copy Fail\n");
//	   break;
//	 }
//	 if(fputs(s1,ft)==EOF){
//	   printf("Copy Fail\n");
//	   break;
//	 }
//	 break;
//       }
//    }
//    fcloseall();
//    blResultOK=TRUE;
//  }
//  return blResultOK;
//}

BOOL blCheckLines (const char *pfile)
{
  unsigned int nCountLine = 1 , nCountSpaceLine = 0;
  unsigned int nSpaceLineIndex[500] = {0};
  unsigned int nNewLine = 0;
  unsigned int nEOF = 0;

  BOOL blFirstWord = TRUE;
  BOOL blOK = TRUE;
  char chNewLine = '\n';
  FILE *fptr;
  char ch1;

  printf ("Check File : %s\n" , pfile);
  fptr = fopen (pfile , "r+");

  if (fptr == NULL) {

    cprintf ("File Not Found...\n\r" , pfile);
    //fclose (fptr);
    End (nErrorLevel);
  }

  while ((ch1 = getc (fptr)) != EOF) {

    if (ch1 == chNewLine){

      if (nNewLine != 0 || blFirstWord) {

	nSpaceLineIndex[nCountSpaceLine] = nCountLine;
	nCountSpaceLine += 1;
	nNewLine += 1;
      }
      else nNewLine += 1;
      nCountLine += 1;

    }
    else nNewLine = 0;

    blFirstWord = FALSE;
  }

  nEOF = nCountLine;
  if (nNewLine >= 1) nCountLine -= 1;

  fclose (fptr);
  printf ("Total Lines in File = %d\n" , nCountLine);

  if (nLine > 0) {

    printf ("User input the number of file line = %d\n" , nLine);
    if (nLine != (nCountLine)) {
      printf ("the Number of file lines is incorrect !!\n");
      blOK = FALSE;
    }

    if (nCountSpaceLine > 0) {

      printf ("There is any empty line in file !!\n");
      for (unsigned int c = 0 ; c < nCountSpaceLine ; c++)
	printf ("the empty Line at %d line\n" , nSpaceLineIndex[c]);

      blOK = FALSE;
    }
  }
  else {
    printf ("Total Empty Lines in File = %d\n" , nCountSpaceLine);

    if (nCountSpaceLine > 0) {
      for (unsigned int c = 0 ; c < nCountSpaceLine ; c++)
	printf ("Empty Line at %d line\n" , nSpaceLineIndex[c]);
    }
  }
  printf ("EOF at Line %d" , nEOF);

  if (blOK) return TRUE;
  return FALSE;
}

DWORD dwTransferNowDateTime2GMT(void)
{
  int Month, TotalDay=0;
  DWORD sec;
  SYSTEMTIME SystemTime;
  char day[10];

  GetSystemTime(&SystemTime);

  // Determine day of the week.
  switch (SystemTime.wDayOfWeek) {
	case 0:
	  strcpy(day, "Sunday");
	  break;

	case 1:
	  strcpy(day, "Monday");
	  break;

	case 2:
	  strcpy(day, "Tuesday");
	  break;

	case 3:
	  strcpy(day, "Wednesday");
	  break;

	case 4:
	  strcpy(day, "Thursday");
	  break;

	case 5:
	  strcpy(day, "Friday");
	  break;

	case 6:
	  strcpy(day, "Saturday");
	  break;
  }

  sec=(SystemTime.wYear-0x7BC-1)*365*86400; //璸衡眖1981 (ie.1980=0x7BC) 羆计
  sec=sec+(((SystemTime.wYear-1980-1)/4)*86400); //秥ぱ计
  
  for(Month=1; Month<SystemTime.wMonth; Month++) {
	if(Month==2) {
	  if(((SystemTime.wYear-1980)%4)==0) TotalDay=TotalDay+29;
	  else {
		TotalDay=TotalDay+28;
		continue;
	  }
	}
	
	if(Month==4 || Month==6 || Month==9 || Month==11) TotalDay=TotalDay+30;
	else TotalDay=TotalDay+31;
  }

  //璸衡 1981 さ羆计
  sec = sec + (TotalDay*86400) + ((SystemTime.wDay-1)*86400) + ((SystemTime.wHour-1)*3600) + ((SystemTime.wMinute-1)*60) + SystemTime.wSecond;
  return sec;
} 

DWORD dwGetFileSize(char *fn)
{
  int handle;
  DWORD l;

  if((handle=open(fn, O_RDONLY))==-1) {
    cprintf("File not found ...\n\r", fn);
    End(nErrorLevel);
  }

  l=filelength(handle);

  close(handle);

  return l;
} 

void DisplayTxtFile(char *filename, int x, int y, BYTE attr)
{
  FILE *f;
  char c;

  if((f=fopen(filename, "r+"))==NULL) {
    printf("%s file not FOUND.\n", filename);
    End(nErrorLevel);
  } else {
    gotoxy(1,1);
    while (!feof(f)) {
      c=fgetc(f);
      if(feof(f)) break;
      if(c==0x0D) continue;
      if(c==0x0A) {
		x=1;
		y++;
		continue;
      }
      if(x>80) x=80;
      if(y>25) y=25;

//      PrintCh(x++,y,c,attr,1);
	  if(x<1) x=1;
	  if(x>80) x=80;
	  if(y<1) y=1;
	  if(y>25) y=25;
	  gotoxy(x,y);

	  textbackground((attr>>4) & 0x0F);
	  textcolor(attr & 0x0F);
	  printf("%c",c);
	  x++;
    }
	textattr(0x07);
    fclose(f);
  }
} 

BOOL blFileCompare(char *fn1, char *fn2, BOOL blignore)
{
  FILE *tf1, *tf2, *f5, *f6;
  int f1, f2;
  WORD k, kk;
  long fs2;
  DWORD fs1;
  char far *keybuffer=(char far*) 0x00400017;
  char s5[100],s6[100],s7[100]="\0",s8[100]="\0",s9[100]="\0",s10[100]="\0";
  DWORD i,j;
  DWORD ReadLength;
  BYTE d1[1], d2[1];

  // compare all file context
  if(blUseAddress==FALSE && blUseLine==FALSE) {
    if((f1=open(fn1, O_RDONLY))==-1) {
      cprintf("Open %s file error.\n\r", fn1);
      return FALSE;
    } else {
      fs1=filelength(f1);
      close(f1);
    }
    if((f2=open(fn2, O_RDONLY))==-1) {
      cprintf("Open %s file error.\n\r", fn2);
      return FALSE;
    }
    else {
      fs2=filelength(f2);
      close(f2);
    }
    if(fs1!=fs2) {
      cprintf("File compare error with different filesize\n\r");
      return FALSE;
    }
    printf(" ... Compare  %s  &  %s ... \n", fn1, fn2);

    f1=open(fn1, O_RDONLY|O_BINARY);
    f2=open(fn2, O_RDONLY|O_BINARY);
    i=0;
		do{ 
      printf("   %ld/%ld   \n",i,fs1);
      ReadLength=ReadSize;
      if((i+ReadLength)>fs1) ReadLength=fs1-i;
      read(f1,buf1,ReadLength);
      read(f2,buf2,ReadLength);
	  if(blignore)
	  {
		  CharUpper(buf1);
		  CharUpper(buf2);
	  }
      for(j=0; j<ReadLength; j++) {
				if(buf1[j]!=buf2[j]) {
					printf(" ... File Compare ERROR at Byte %ld ... \n", i+j+1);
					close(f1);
					close(f2);
					return FALSE;
				}
				if((*keybuffer&0x02)==0x02) {
					cprintf(" ... User Break ... \n");
					close(f1);
					close(f2);
					return FALSE;
				}
      }
      i+=ReadLength;
    } while(i<fs1);
    close(f1);
    close(f2);
    printf("   %ld/%ld   \n",i,fs1);
    cprintf(" ... File Compare OK ... \n");
    return TRUE;
  }

  // compare partial file context
  if(blUseAddress && blUseLine==FALSE) {
    cprintf("\n\r");
    if(dwStartAddress>dwEndAddress) {
      cprintf("Byte Range ERROR !! Start Byte=%ld > End Byte=%ld !!\n\r", dwStartAddress+1, dwEndAddress+1);
      return FALSE;
    }
//    cprintf("Compare Byte %ld to %ld\n\r", dwStartAddress+1, ((dwEndAddress<(fs1-1)) ? dwEndAddress : (fs1-1))+1); // add by KC
    cprintf("Compare Byte %ld to %ld\n\r", dwStartAddress+1, dwEndAddress+1); // add by jackson
    i=dwStartAddress;

    if(blignore){
      if((f5=fopen(fn1, "r"))==NULL){
		cprintf("\nERROR !! Can't Open %s !!\n\r",fn1);
		fcloseall();
		return FALSE;
      }
      if((f6=fopen(fn2, "r"))==NULL){
		cprintf("\nERROR !! Can't Open %s !!\n\r",fn2);
		fcloseall();
		return FALSE;
      }

      fgets(s5,100,f5);
      fgets(s6,100,f6);
      kk=0;
      for(k=(WORD) dwStartAddress;k<=(WORD) dwEndAddress;k++){
		s7[kk]=s5[k];
		s8[kk]=s6[k];
		kk++;
		if(k==dwEndAddress+1){
		  s7[kk]='\0';
		  s8[kk]='\0';
		}
      }
      printf("\n\n%s Data = %s",fn1,s7);
      printf("\n%s Data = %s\n",fn2,s8);
      for(kk=0;kk<strlen(s7);kk++){
		s9[kk]=toupper(s7[kk]);
		s10[kk]=toupper(s8[kk]);
      }
      if(stricmp(s9,s10)==0){
		cprintf("\nCompare OK !!\n\r");
		fcloseall();
		return TRUE;
      } else {
		for(kk=0;kk<strlen(s9);kk++)
		  if(s9[kk]!=s10[kk]) break;
		cprintf("\nCompare Error at Byte %d !!\n\r", kk+1);
		fcloseall();
		return FALSE;
      }
    }

    if((f1=open(fn1, O_RDONLY|O_BINARY))==NULL){
      cprintf("\nERROR !! Can't Open %s !!\n\r",fn1);
      close(f1);
      return FALSE;
    }
    if((f2=open(fn2, O_RDONLY|O_BINARY))==NULL){
      cprintf("\nERROR !! Can't Open %s !!\n\r",fn2);
      close(f2);
      return FALSE;
    }

    lseek(f1, dwStartAddress, SEEK_SET);
    lseek(f2, dwStartAddress, SEEK_SET);

//    while(i<=dwEndAddress && i<=(fs1-1)) { // add by KC
    while(i<=dwEndAddress) { // add by jackson
      read(f1,d1,1);
      read(f2,d2,1);
      if(*d1!=*d2) {
		cprintf("Compare ERROR at Byte %ld\n\r", i+1);
		close(f1);
		close(f2);
		return FALSE;
      }
      i++;
    }
    close(f1);
    close(f2);
    cprintf("Compare OK\n\r");
    return TRUE;
  }

  // compare partial file context
  if(blUseAddress==FALSE && blUseLine) {
    cprintf("\n\r");
    if(dwStartLine>dwEndLine) {
      cprintf("Line range set ERROR, start line=%ld & end line=%ld\n\r", dwStartLine+1, dwEndLine+1);
      return FALSE;
    }
    if(dwEndLine==0xFFFFFFFFl) cprintf("Compare line %ld to end\n\r", dwStartLine+1);
    else cprintf("Compare line %ld to %ld\n\r", dwStartLine+1, dwEndLine+1);
    tf1=fopen(fn1, "r+");
    tf2=fopen(fn2, "r+");
    i=0;
		unsigned int k = 0, l = 0;
    while(!feof(tf1)) {
      if(i>dwEndLine) break;
      fgets(buf1,1024,tf1);
      fgets(buf2,1024,tf2);
      if(i>=dwStartLine && i<=dwEndLine){
				if(i>=dwStartLine && i<=dwEndLine){
					if(blignore){
						for(k ; k < strlen(buf1) ; k++){
							if(islower(buf1[k])){
								buf1[k] = toupper(buf1[k]);
							}
						}
						if(buf1[k-1] == 0x0a) buf1[k-1] = '\0';
						k = 0;
						for(l ; l < strlen(buf2) ; l++){
							if(islower(buf2[l])){
								buf2[l] = toupper(buf2[l]);
							}
						}
						if(buf2[l-1] == 0x0a) buf2[l-1] = '\0';
						l = 0;
					}
		      if(strcmp(buf1, buf2)){
		        cprintf("\nCompare ERROR at line %ld\n\r", i+1);
		        cprintf("%s --> ",fn1);
		        cprintf("%s\r", buf1);
		        cprintf("%s --> ",fn2);
		        cprintf("%s\n\r", buf2);
		        fclose(tf1);
		        fclose(tf2);
		        return FALSE;
					}
		    }
      }
      i++;
    }
    fclose(tf1);
    fclose(tf2);
    cprintf("Compare OK\n\r");
    return TRUE;
  }

  cprintf("check the parameter\n\r");
  return FALSE;
}

BOOL blFileCheckSum(char *fn1, WORD wUserCheckSum)
{
  FILE *tf1;
  int f1;
  //long fs1;
  DWORD i,j, fs1;
  DWORD ReadLength;
  BYTE d1[1];
  WORD wCheckSum=0;

  if((f1=open(fn1, O_RDONLY))==-1) {
    cprintf("Open %s file error.\n\r", fn1);
    return FALSE;
  } else {
    fs1=filelength(f1);
    close(f1);
  }

  // compare all file context
  if(blUseAddress==FALSE && blUseLine==FALSE) {
    printf(" ... Compute checksum of %s ...", fn1);

    f1=open(fn1, O_RDONLY|O_BINARY);
    i=0;
    do {
      printf("   %ld/%ld   \n",i,fs1);
      ReadLength=ReadSize;
      if((i+ReadLength)>fs1) ReadLength=fs1-i;
      read(f1,buf1,ReadLength);
      for(j=0; j<ReadLength; j++) wCheckSum+=buf1[j];
      i+=ReadLength;
    } while(i<fs1);
    close(f1);
    printf(" CheckSum=%04X   \n",wCheckSum);
    if(wCheckSum==wUserCheckSum) return TRUE;
    else return FALSE;
  }

  // compare partial file context
  if(blUseAddress && blUseLine==FALSE) {
    cprintf("\n\r");
    if(dwStartAddress>dwEndAddress) {
      cprintf("Byte range set ERROR, start byte=%ld > end byte=%ld\n\r", dwStartAddress+1, dwEndAddress+1);
      return FALSE;
    }
    cprintf("Compute checksum from byte %ld to %ld of %s\n\r", dwStartAddress+1, ((dwEndAddress<(fs1-1)) ? dwEndAddress : (fs1-1))+1, fn1);

    f1=open(fn1, O_RDONLY|O_BINARY);
    i=dwStartAddress;

    lseek(f1, dwStartAddress, SEEK_SET);

    while(i<=dwEndAddress && i<=(fs1-1)) {
      read(f1,d1,1);
      wCheckSum+=*d1;
      i++;
    }
    close(f1);
    cprintf("CheckSum=%04X\n", wCheckSum);
    if(wCheckSum==wUserCheckSum) return TRUE;
    else return FALSE;
  }

  // compare partial file context
  if(blUseAddress==FALSE && blUseLine) {
    cprintf("\n\r");
    if(dwStartLine>dwEndLine) {
      cprintf("Line range set ERROR, start line=%ld & end line=%ld\n\r", dwStartLine+1, dwEndLine+1);
      return FALSE;
    }
    if(dwEndLine==0xFFFFFFFFl) cprintf("Compute checksum from line %ld to end of %s\n\r", dwStartLine+1, fn1);
    else cprintf("Compute checksum from line %ld to %ld of %s\n\r", dwStartLine+1, dwEndLine+1, fn1);
    tf1=fopen(fn1, "r+");
    i=0;
    while(!feof(tf1)) {
      if(i>dwEndLine) break;
      fscanf(tf1, "%s\n", buf1);
      for(j=0; j<strlen(buf1); j++) wCheckSum+=buf1[j];
      i++;
    }
    fclose(tf1);
    cprintf("CheckSum=%04X\n", wCheckSum);
    if(wCheckSum==wUserCheckSum) return TRUE;
    else return FALSE;
  }
  cprintf("check the parameter\n\r");
  return FALSE;
}


// --------- Auto Create Test Batch File for NoteBook from ini File ---------
BOOL Process_ini_File(int DelBit,int Chk_Tms,int FileNumber,char **iniFile,char *Prmpt)
{
  FILE *finiFile,*fBatchFile,*fBarcode,*fProFile,*fTxtFile,*fCopyFile,*fChkCode;
  int  jj=0,CompareOK,TotalFileCount,BatchFileCount,ModFileCount,k,Match,Mark,CountLine,mm,n;
  char *ptr,s[100],iniBarCode[100],NBBarCode[100],ss[100],ModMatch,ss2[100],BatchMatch,CH='\0',buffer1[20],
	   buffer2[20],buffer3[20],buffer4[20],buffer5[20],ModelName[100]="\0",New_NBBarCode[100],ChkCode[100],
       New_ChkCode[100],buffer6[20],s1[100]="\0",s2[100]="\0";
  BOOL blResultOK=FALSE;
  WORD ii, j, kk, m;

  if(FileNumber==0) return blResultOK;
  while(jj<FileNumber){
    Mark=0;
    Match=0;
    CountLine=0;
    ModMatch=0;
    BatchMatch=0;
    ModFileCount=0;
    BatchFileCount=0;
    TotalFileCount=0;
    if((finiFile=fopen(iniFile[jj],"r"))==NULL){
      cprintf("\n ERROR !! %s Not Found !!\n\r",iniFile[jj]);
      fcloseall();
      return blResultOK;
    }
    sprintf(buffer1,"NBtest%d.txt",jj+1);
    if((fTxtFile=fopen(buffer1,"w"))==NULL){
      cprintf("\n ERROR !! Can't Open %s !!\n\r",buffer1);
      fcloseall();
      return blResultOK;
    }
    sprintf(buffer2,"barcode%d.dat",jj+1);
    if((fBarcode=fopen(buffer2,"w"))==NULL) {
      cprintf("\n ERROR !! Can't Open %s !!\n\r",buffer2);
      fcloseall();
      return blResultOK;
    }
    if(strlen(Prmpt)!=0) printf(" %s : ",Prmpt);
    else printf(" Please Scan Barcode %d : ",jj+1);
    system("@echo on");
    scanf("%s",NBBarCode);
    if(DelBit>0 && NBBarCode[0]=='9'){ //Change 90 barcode to 80 barcode
      mm=1;
      New_NBBarCode[0]='8';
      for(m=1;m<=strlen(NBBarCode);m++){ //Remove a bit from barcode
		if(m==DelBit-1) continue;
		New_NBBarCode[mm]=NBBarCode[m];
		mm++;
      }
      strcpy(NBBarCode,New_NBBarCode);
    }
    fprintf(fBarcode,"%s\n",NBBarCode);
    fclose(fBarcode);
    sprintf(buffer2,"barcode%d.dat",jj+1);
    if((fBarcode=fopen(buffer2,"r"))==NULL) {
      cprintf("\n ERROR !! Can't Open %s !!\n\r",buffer2);
      fcloseall();
      return blResultOK;
    }
    fgets(s1,100,fBarcode);
    sprintf(buffer6,"chkcode%d.dat",jj+1);
    for(n=Chk_Tms-1;n>0;n--){ //Scan barcode Chk_Tms times and compare
      if((fChkCode=fopen(buffer6,"w")) != NULL) fclose(fChkCode);
      if((fChkCode=fopen(buffer6,"w"))==NULL) {
		cprintf("\n ERROR !! Can't Open %s !!\n\r",buffer6);
		fcloseall();
		return blResultOK;
      }
      if(strlen(Prmpt)!=0) printf(" %s again : ",Prmpt);
      else printf(" Please Scan Barcode %d again : ",jj+1);
	  system("@echo on");
      scanf("%s",ChkCode);
      if(DelBit>0 && ChkCode[0]=='9'){
		mm=1;
		New_ChkCode[0]='8';
		for(m=1;m<=strlen(ChkCode);m++){
		  if(m==DelBit-1) continue;
		  New_ChkCode[mm]=ChkCode[m];
		  mm++;
		}
		strcpy(ChkCode,New_ChkCode);
      }
      fprintf(fChkCode,"%s\n",ChkCode);
      fclose(fChkCode);
      if((fChkCode=fopen(buffer6,"r"))==NULL) {
		cprintf("\n ERROR !! Can't Open %s !!\n\r",buffer6);
		fcloseall();
		return blResultOK;
      }
      fgets(s2,100,fChkCode);
      if(strlen(s1)!=strlen(s2)){
		Logo();
		printf("\n ERROR !! The Barcode Length Is Different !!\n\n");
		printf(" The Original Barcode = %s",s1);
		printf("   The Latest Barcode = %s",s2);
		fcloseall();
		return blResultOK;
      }
      if(stricmp(s1,s2)!=0){
		Logo();
		printf("\n ERROR !! The Barcode Is Different !!\n\n");
		printf(" The Original Barcode = %s",s1);
		printf("   The Latest Barcode = %s",s2);
		fcloseall();
		return blResultOK;
      }
      continue;
    }

    while(!feof(finiFile)) {
      if(fgets(s,100,finiFile)!=NULL){
		if(s[0]=='*'){
		  if((Match==0)&&(Mark<CountLine)){
			printf("\n ERROR !! ''%s'' No Matched Barcode For %s !!\n",ModelName,iniFile[jj]);
			fcloseall();
			return blResultOK;
		  }
		  Mark=0;
		  Match=0;
		  CountLine=0;
		  continue;
		}
		for(ii=0;ii<strlen(s);ii++) s[ii]=toupper(s[ii]);
		if((s[0]==';')&&(0x41<=s[1])&&(s[1]<=0x5A)){
		  for(ii=0;ii<strlen(s);ii++){
			if(s[ii+1]=='\n'){
			  ModelName[ii]='\0';
			  break;
			}
			ModelName[ii]=s[ii+1];
		  }
		  continue;
		}
		if((s[0]==';')&&(0x30<=s[1])&&(s[1]<=0x39)){
		  Mark++;
		  CountLine++;
		  continue;
		}
		if(s[0]==';' || s[0]=='\n') continue;
		for(ii=0;ii<strlen(s);ii++) {  // read barcode setting from NBtest.ini file
		  if(s[ii]!='=') iniBarCode[ii]=s[ii];
		  else {
			iniBarCode[ii]='\0';
			break;
		  }
		}
		if(strlen(iniBarCode)==strlen(NBBarCode)){ // compare barcode with Nbtest.ini file
		  k=0;
		  CompareOK=0;
		  CountLine++;
		  for(ii=0;ii<strlen(iniBarCode);ii++){
			iniBarCode[ii]=toupper(iniBarCode[ii]);
			NBBarCode[ii]=toupper(NBBarCode[ii]);
			if(iniBarCode[ii]!='?') k++;
			if(NBBarCode[ii]==iniBarCode[ii]) CompareOK++;
		  }
		}
/*		else{
		  printf("\n Barcode Format Error !!\n");
		  fcloseall();
		  return blResultOK;
		}*/
		else{
		  CountLine++;
		  continue;
		}
		if((CompareOK!=0)&&(CompareOK==k)){  // copy matched sub-batch file name from NBtest.ini to NBtest.bat
		  if((ptr=strtok(s,"="))!=0)
		  if((ptr=strtok(NULL,"\n"))!=0)
		  fprintf(fTxtFile,"%s\n",ptr);
		  Match++;
		}
      }
      CH=fgetc(finiFile);
      if(CH==EOF) break;
      ungetc(CH,finiFile);
    }
    fclose(fTxtFile);
    if((fTxtFile=fopen(buffer1,"r"))==NULL) {
      cprintf("\n ERROR !! %s Not Found !!\n\r",buffer1);
      fcloseall();
      return blResultOK;
    }
    sprintf(buffer3,"NBtest%d.bat",jj+1);
    if((fBatchFile=fopen(buffer3,"w"))==NULL) {
      cprintf("\n ERROR !! Can't Open %s !!\n\r",buffer3);
      fcloseall();
      return blResultOK;
    }
    sprintf(buffer5,"NBcopy%d.bat",jj+1);
    if((fCopyFile=fopen(buffer5,"w"))==NULL) {
      cprintf("\n ERROR !! Can't Open %s !!\n\r",buffer5);
      fcloseall();
      return blResultOK;
    }
    sprintf(buffer4,"NBtest%d.pro",jj+1);
    if((fProFile=fopen(buffer4,"w"))==NULL) {
      cprintf("\n ERROR !! Can't Open %s !!\n\r",buffer4);
      fcloseall();
      return blResultOK;
    }

    CH='\0';
    while(!feof(fTxtFile)) {
      if(fgets(ss,100,fTxtFile)!=NULL) {
		for(j=0;j<strlen(ss);j++) ss[j]=toupper(ss[j]);
		for(j=0;j<strlen(ss);j++){
		  for(kk=0;kk<strlen(ss);kk++){
			if(ss[kk]=='\n'){
			  ss2[kk]='\0';
			  break;
			}
			ss2[kk]=ss[kk];
		  }
		}
		fprintf(fCopyFile,"%s","COPY ");
		fprintf(fCopyFile,"%s",ss2);
		fprintf(fCopyFile,"%s\n"," %RD%:");
		for(j=0;j<strlen(ss);j++) {
		  if((ss[j]=='.')&&(ss[j+1]=='M')&&(ss[j+2]=='O')&&(ss[j+3]=='D')) {
			ModMatch=1;
			break;
		  }
		}
		if(ModMatch==1) {
		  fprintf(fProFile,"%s",ss);
		  ModFileCount=ModFileCount+1;
		  ModMatch=0;
		}
		for(j=0;j<strlen(ss);j++) {
		  if((ss[j]=='.')&&(ss[j+1]=='B')&&(ss[j+2]=='A')&&(ss[j+3]=='T')) {
			BatchMatch=1;
			break;
		  }
		}
		if(BatchMatch==1) {
		  fprintf(fBatchFile,"%s","CALL ");
		  fprintf(fBatchFile,"%s",ss);
		  BatchFileCount=BatchFileCount+1;
		  BatchMatch=0;
		}
      }
      CH=fgetc(fTxtFile);
      if(CH==EOF) break;
      ungetc(CH,fTxtFile);
    }
    if(ModFileCount>0) {
      fprintf(fBatchFile,"%s","ASUS ");
      fprintf(fBatchFile,"%s",buffer4);
      fprintf(fBatchFile,"%s"," ");
      fprintf(fBatchFile,"%s\n","-PE");
    }
    TotalFileCount=BatchFileCount+ModFileCount;
    printf("\n Mod File   = %d",ModFileCount);
    printf("\n Batch File = %d",BatchFileCount);
    printf("\n Total File = %d\n\n",TotalFileCount);
    if(TotalFileCount==0) {
      printf(" ERROR !! No Matched Barcode !!\n");
      fcloseall();
      return blResultOK;;
    }
    jj++;
  }
  fcloseall();
  blResultOK=TRUE;
  return blResultOK;
}


BOOL Process_ini_File2(int DelBit,int FileNumber,char **iniFile)
{
  FILE *finiFile,*fBatchFile,*fBarcode,*fProFile,*fTxtFile,*fCopyFile;
  int  jj=0,CompareOK,TotalFileCount,BatchFileCount,ModFileCount,k,Match,Mark,CountLine,mm;
  char *ptr,s[100],iniBarCode[100],NBBarCode[100],ss[100],ModMatch,ss2[100],BatchMatch,CH='\0',buffer1[20],
	   buffer2[20],buffer3[20],buffer4[20],buffer5[20],ModelName[100]="\0",New_NBBarCode[100],s1[100]="\0";
  BOOL blResultOK=FALSE;
  WORD ii, j, kk, m;

  if(FileNumber==0) return blResultOK;
  while(jj<FileNumber){
    Mark=0;
    Match=0;
    CountLine=0;
    ModMatch=0;
    BatchMatch=0;
    ModFileCount=0;
    BatchFileCount=0;
    TotalFileCount=0;
    if((finiFile=fopen(iniFile[jj],"r"))==NULL){
      cprintf("\n ERROR !! %s Not Found !!\n\r",iniFile[jj]);
      fcloseall();
      return blResultOK;
    }
    sprintf(buffer1,"NBtest%d.txt",jj+1);
    if((fTxtFile=fopen(buffer1,"w"))==NULL){
      cprintf("\n ERROR !! Can't Open %s !!\n\r",buffer1);
      fcloseall();
      return blResultOK;
    }
    sprintf(buffer2,"barcode%d.dat",jj+1);
    if((fBarcode=fopen(buffer2,"r"))==NULL) {
      cprintf("\n ERROR !! Can't Open %s !!\n\r",buffer2);
      fcloseall();
      return blResultOK;
    }
    fgets(s,100,fBarcode);
    for(j=0;j<strlen(s);j++){
      if(s[j]=='\n'){
		NBBarCode[j]='\0';
		break;
      }
      NBBarCode[j]=s[j];
      if(j==strlen(s)-1){
		NBBarCode[j+1]='\0';
		break;
      }
    }
    if(DelBit>0 && NBBarCode[0]=='9'){ //Change 90 barcode to 80 barcode
      mm=1;
      New_NBBarCode[0]='8';
      for(m=1;m<=strlen(NBBarCode);m++){ //Remove a bit from barcode
		if(m==DelBit-1) continue;
		New_NBBarCode[mm]=NBBarCode[m];
		mm++;
      }
      strcpy(NBBarCode,New_NBBarCode);
    }
    fclose(fBarcode);
    sprintf(buffer2,"barcode%d.dat",jj+1);
    if((fBarcode=fopen(buffer2,"r"))==NULL) {
      cprintf("\n ERROR !! Can't Open %s !!\n\r",buffer2);
      fcloseall();
      return blResultOK;
    }

	fgets(s1,100,fBarcode);
    while(!feof(finiFile)) {
      if(fgets(s,100,finiFile)!=NULL){
		if(s[0]=='*'){
		  if((Match==0)&&(Mark<CountLine)){
			printf("\n ERROR !! ''%s'' No Matched Barcode For %s !!\n",ModelName,iniFile[jj]);
			fcloseall();
			return blResultOK;
		  }
		  Mark=0;
		  Match=0;
		  CountLine=0;
		  continue;
		}
		for(ii=0;ii<strlen(s);ii++) s[ii]=toupper(s[ii]);
		if((s[0]==';')&&(0x41<=s[1])&&(s[1]<=0x5A)){
		  for(ii=0;ii<strlen(s);ii++){
			if(s[ii+1]=='\n'){
			  ModelName[ii]='\0';
			  break;
			}
			ModelName[ii]=s[ii+1];
		  }
		  continue;
		}
		if((s[0]==';')&&(0x30<=s[1])&&(s[1]<=0x39)){
		  Mark++;
		  CountLine++;
		  continue;
		}
		if(s[0]==';' || s[0]=='\n') continue;
		for(ii=0;ii<strlen(s);ii++) {  // read barcode setting from NBtest.ini file
		  if(s[ii]!='=') iniBarCode[ii]=s[ii];
		  else {
			iniBarCode[ii]='\0';
			break;
		  }
		}
		if(strlen(iniBarCode)==strlen(NBBarCode)){ // compare barcode with Nbtest.ini file
		  k=0;
		  CompareOK=0;
		  CountLine++;
		  for(ii=0;ii<strlen(iniBarCode);ii++){
			iniBarCode[ii]=toupper(iniBarCode[ii]);
			NBBarCode[ii]=toupper(NBBarCode[ii]);
			if(iniBarCode[ii]!='?') k++;
			if(NBBarCode[ii]==iniBarCode[ii]) CompareOK++;
		  }
		}
		else{
		  CountLine++;
		  continue;
		}
		if((CompareOK!=0)&&(CompareOK==k)){  // copy matched sub-batch file name from NBtest.ini to NBtest.bat
		  if((ptr=strtok(s,"="))!=0)
		  if((ptr=strtok(NULL,"\n"))!=0)
		  fprintf(fTxtFile,"%s\n",ptr);
		  Match++;
		}
      }
      CH=fgetc(finiFile);
      if(CH==EOF) break;
      ungetc(CH,finiFile);
    }
    fclose(fTxtFile);
    if((fTxtFile=fopen(buffer1,"r"))==NULL) {
      cprintf("\n ERROR !! %s Not Found !!\n\r",buffer1);
      fcloseall();
      return blResultOK;
    }
    sprintf(buffer3,"NBtest%d.bat",jj+1);
    if((fBatchFile=fopen(buffer3,"w"))==NULL) {
      cprintf("\n ERROR !! Can't Open %s !!\n\r",buffer3);
      fcloseall();
      return blResultOK;
    }
    sprintf(buffer5,"NBcopy%d.bat",jj+1);
    if((fCopyFile=fopen(buffer5,"w"))==NULL) {
      cprintf("\n ERROR !! Can't Open %s !!\n\r",buffer5);
      fcloseall();
      return blResultOK;
    }
    sprintf(buffer4,"NBtest%d.pro",jj+1);
    if((fProFile=fopen(buffer4,"w"))==NULL) {
      cprintf("\n ERROR !! Can't Open %s !!\n\r",buffer4);
      fcloseall();
      return blResultOK;
    }

    CH='\0';
    while(!feof(fTxtFile)) {
      if(fgets(ss,100,fTxtFile)!=NULL) {
		for(j=0;j<strlen(ss);j++) ss[j]=toupper(ss[j]);
		for(j=0;j<strlen(ss);j++){
		  for(kk=0;kk<strlen(ss);kk++){
			if(ss[kk]=='\n'){
			  ss2[kk]='\0';
			  break;
			}
			ss2[kk]=ss[kk];
		  }
		}
		fprintf(fCopyFile,"%s","COPY ");
		fprintf(fCopyFile,"%s",ss2);
		fprintf(fCopyFile,"%s\n"," %RD%:");
		for(j=0;j<strlen(ss);j++) {
		  if((ss[j]=='.')&&(ss[j+1]=='M')&&(ss[j+2]=='O')&&(ss[j+3]=='D')) {
			ModMatch=1;
			break;
		  }
		}
		if(ModMatch==1) {
		  fprintf(fProFile,"%s",ss);
		  ModFileCount=ModFileCount+1;
		  ModMatch=0;
		}
		for(j=0;j<strlen(ss);j++) {
		  if((ss[j]=='.')&&(ss[j+1]=='B')&&(ss[j+2]=='A')&&(ss[j+3]=='T')) {
			BatchMatch=1;
			break;
		  }
		}
		if(BatchMatch==1) {
		  fprintf(fBatchFile,"%s","CALL ");
		  fprintf(fBatchFile,"%s",ss);
		  BatchFileCount=BatchFileCount+1;
		  BatchMatch=0;
		}
      }
      CH=fgetc(fTxtFile);
      if(CH==EOF) break;
      ungetc(CH,fTxtFile);
    }
    if(ModFileCount>0) {
      fprintf(fBatchFile,"%s","ASUS ");
      fprintf(fBatchFile,"%s",buffer4);
      fprintf(fBatchFile,"%s"," ");
      fprintf(fBatchFile,"%s\n","-PE");
    }
    TotalFileCount=BatchFileCount+ModFileCount;
    printf("\n Mod File   = %d",ModFileCount);
    printf("\n Batch File = %d",BatchFileCount);
    printf("\n Total File = %d\n\n",TotalFileCount);
    if(TotalFileCount==0) {
      printf(" ERROR !! No Matched Barcode !!\n");
      fcloseall();
      return blResultOK;;
    }
    jj++;
  }
  fcloseall();
  blResultOK=TRUE;
  return blResultOK;
}


// ----------- Read Bit Value from File and Check with Character  -----------
BOOL CheckChar(char Filename[], int ReadBit, char ch)
{
  FILE *fFilename;
  WORD  ii;
  char s[100];
  BOOL blResultOK=FALSE;

  if((fFilename=fopen(Filename,"r"))==NULL) {
    cprintf("ERROR !! Can't Open %s !!\n\r",Filename);
    return blResultOK;
  }
  if(fgets(s,100,fFilename)!=NULL)
    for(ii=0;ii<strlen(s);ii++) s[ii]=toupper(s[ii]);
  else {
    printf("Get String Process Happen Error !!");
    fclose(fFilename);
    return blResultOK;
  }
  ch=toupper(ch);
  if(ReadBit>(int) strlen(s)) {
    cprintf(" ERROR !!  <bit> setting is over range !! \n");
    fclose(fFilename);
    return blResultOK;
  }
  printf("\n Bit %d = %c\n",ReadBit,s[ReadBit-1]);
  printf(" Character = %c\n",ch);
  if(s[ReadBit-1]==ch) blResultOK=TRUE;
  else cprintf(" ERROR !!  No Character Matched !! \n");
  fclose(fFilename);
  return blResultOK;
}

BOOL Transfer_Barcode_Format(char *Prmpt)
{
  FILE *fBar;
  int  k;
  char BarCode1[100]="\0",BarCode2[100]="\0",New_BarCode[100]="\0";
  BOOL blResultOK=FALSE;

  if((fBar=fopen("new_bc.dat","w"))==NULL) {
    cprintf("\n ERROR !! Can't Open New_bc.dat !!\n\r");
    fcloseall();
    return blResultOK;
  }
  system("@echo on");
  if(strlen(Prmpt)!=0) printf(" %s : ",Prmpt);
  else printf(" Please Scan Barcode : ");
  scanf("%s %s",BarCode1,BarCode2);
  if(strlen(BarCode1)!=8){
    printf("\n\n ERROR !! The 1st Block Barcode Isn't 8 Bits !!\n");
    fcloseall();
    return blResultOK;
  }
  if(strlen(BarCode2)!=7){
    printf("\n\n ERROR !! The 2nd Block Barcode Isn't 7 Bits !!\n");
    fcloseall();
    return blResultOK;
  }
  New_BarCode[0]='"';
  for(k=1;k<=8;k++) New_BarCode[k]=BarCode1[k-1];
  New_BarCode[9]='-';
  for(k=10;k<=16;k++) New_BarCode[k]=BarCode2[k-10];
  New_BarCode[17]='"';
  New_BarCode[18]='\0';
  printf("\n New Format : %s\n",New_BarCode);
  if(strlen(New_BarCode)!=18){
    printf("\n\n ERROR !! New Format Isn't 18 Bits !!\n");
    fcloseall();
    return blResultOK;
  }
  fprintf(fBar,"%s\n",New_BarCode);
  blResultOK=TRUE;
  return blResultOK;
}


BOOL Set_Barcode_Environment(char DataFilename[], char iniFilename[])
{
  FILE *fDataFilename,*finiFilename,*fSetBar;
  int  j,k,m=0,CompareOK,Match;
  char s[100],NBBarCode[100],iniBarCode[100],SetBar[100],CH='\0',old_dir[MAXDIR];
  //char new_dir[MAXDIR];
  BOOL blResultOK=FALSE;
  WORD ii;
  TCHAR szBuf[MAX_PATH+1];

  //if(getcurdir(0,old_dir)){
  if(GetCurrentDirectory(MAX_PATH,szBuf)){
    perror("getcurdir()");
    return blResultOK;
  }
  if(chdir("\\")){
    perror("chdir()");
    return blResultOK;
  }

  //if(getcurdir(0,new_dir)){
  if(GetCurrentDirectory(MAX_PATH,szBuf)){
    perror("getcurdir()");
    return blResultOK;
  }
  if((fDataFilename=fopen(DataFilename,"r"))==NULL) {
    cprintf("ERROR !! Can't Open %s !!\n\r",DataFilename);
    fcloseall();
    return blResultOK;
  }
  if(chdir(old_dir)){
    perror("chdir()");
    return blResultOK;
  }
  if((finiFilename=fopen(iniFilename,"r"))==NULL) {
    cprintf("ERROR !! Can't Open %s !!\n\r",iniFilename);
    fcloseall();
    return blResultOK;
  }
  if(system("del SetBar.bat") == -1){
    printf("\n ERROR !!  Can't Delete SetBar.bat !!\n");
    return FALSE;
  }
  Logo();
  if((fSetBar=fopen("SetBar.bat","w"))==NULL) {
    cprintf("ERROR !! Can't Open SetBar.bat !!\n\r");
    fcloseall();
    return blResultOK;
  }
  fgets(NBBarCode,100,fDataFilename);
  m=(int) strlen(NBBarCode);
  if(NBBarCode[m-1]=='\n') NBBarCode[m-1]='\0';
  Match=0;
  while(!feof(finiFilename)) {
    if(fgets(s,100,finiFilename)!=NULL)
      for(ii=0;ii<strlen(s);ii++) s[ii]=toupper(s[ii]);
    else {
      printf("Fgets Function Error !!");
      fclose(finiFilename);
      return blResultOK;
    }
    for(ii=0;ii<strlen(s);ii++) {  // read barcode setting from NBtest.ini file
      if(s[ii]!='=') iniBarCode[ii]=s[ii];
      else {
		iniBarCode[ii]='\0';
		break;
      }
    }
    if(strlen(iniBarCode)==strlen(NBBarCode)){ // compare barcode with Nbtest.ini file
      k=0;
      CompareOK=0;
      for(ii=0;ii<strlen(iniBarCode);ii++){
		iniBarCode[ii]=toupper(iniBarCode[ii]);
		NBBarCode[ii]=toupper(NBBarCode[ii]);
		if(iniBarCode[ii]!='?') k++;
		if(NBBarCode[ii]==iniBarCode[ii]) CompareOK++;
      }
    }
    else{
      printf("\n Barcode Bit Amount Error !!\n");
      fcloseall();
      return blResultOK;
    }
    if(CompareOK!=0 && CompareOK==k){ // copy matched sub-batch file name from NBtest.ini to NBtest.bat
      j=0;
      for(ii=0;ii<strlen(s);ii++){
		if(s[ii]=='='){
		  while(ii<strlen(s)){
			if(s[ii+1]=='\n'){
			  SetBar[j]='\0';
			  break;
			}
			SetBar[j]=s[ii+1];
			ii++;
			j++;
		  }
		}
      }
      fprintf(fSetBar,"%s\n",SetBar);
      Match++;
    }
    CH=fgetc(finiFilename);
    if(CH==EOF) break;
    ungetc(CH,finiFilename);
  }
  if(Match>0) blResultOK=TRUE;
  else cprintf(" ERROR !!  No Matched !! \n");
  fcloseall();
  printf("\n		       ... There Are %d Mached Setting ... \n",Match);
  return blResultOK;
}


BOOL Transfer_String(char File[],char str1[],char str2[])
{
  FILE *fFile,*ff1;
  char ch1;
  int  k,count=0,match;
  BOOL blResultOK=FALSE;
  WORD i;

  if((fFile=fopen(File,"r"))==NULL) {
    cprintf("ERROR !! Can't Open %s !!\n\r",File);
    fcloseall();
    return blResultOK;
  }
  if((ff1=fopen("update.txt","w"))==NULL) {
    cprintf("ERROR !! Can't Open %s !!\n\r",ff1);
    fcloseall();
    return blResultOK;
  }

  while(!feof(fFile)){
    ch1=fgetc(fFile);
    if(ch1==EOF) break;
    if(ch1==str1[0]){
      match=1;
      for(i=1;i<strlen(str1);i++){
		ch1=fgetc(fFile);
		if(str1[i]==ch1) match++;
		else{
		  for(k=0;k<i;k++) fputc(str1[k],ff1);
		  break;
		}
      }
      if(match==strlen(str1)){
		fputs(str2,ff1);
		count++;
		continue;
      }
    }
    ungetc(ch1,fFile);
    fputc(fgetc(fFile),ff1);
  }
  fcloseall();
  if(count>0){
    printf("\n	  	          ... String Change OK ...\n");
    return blResultOK=TRUE;
  }
  printf("\n		    ... ERROR !! No String to Change ...\n");
  system("del update.txt");
  return blResultOK;
}


//BOOL GetString(char File1[])
//{
//  FILE *fFile1;
//	const unsigned int MAX_STRING = 2048;
//  char s1[MAX_STRING]="\0",s2[MAX_STRING]="\0",zero[MAX_STRING]="\0",CH='\0';
//  unsigned int  k;
//  BOOL blResultOK=FALSE;
//  WORD j;
//
//  if((fFile1=fopen(File1,"r"))==NULL) {
//    cprintf("ERROR !! Can't Open %s !!\n\r",File1);
//    fcloseall();
//    return blResultOK;
//  }
//  if(blLastBit){
//    fgets(s1,MAX_STRING,fFile1);
//    if(LastBit>strlen(s1)) LastBit=strlen(s1);
//    for(k=0;k<LastBit;k++) {
//      if(s1[strlen(s1)-1]=='\n' && LastBit<strlen(s1)) s2[k]=s1[strlen(s1)-LastBit+k-1];
//      else s2[k]=s1[strlen(s1)-LastBit+k];
//    }
//    s2[k]='\0';
//    //printf("%s",s2);
//    return blResultOK;
//  }
//  if(blUseLine && !blUseAddress){
//    if(blUseStartLine && !blUseEndLine){
//      for(LL=1;;LL++){
//			for(k=0;k<MAX_STRING;k++) s2[k]='\0';
//			fgets(s1,MAX_STRING+1,fFile1);
//			if(LL<dwStartLine+1){
//					CH=fgetc(fFile1);
//					if(CH==EOF){
//					cprintf("\n");
//					cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
//					break;
//				}
//		  ungetc(CH,fFile1);
//		  strcpy(s1,zero);
//		  continue;
//		}
//		k=0;
//		for(j=0;j<strlen(s1);j++){
//		  if(s1[j]=='\n'){
//			s2[k]='\0';
//			break;
//		  }
//		  s2[k]=s1[j];
//		  k++;
//		}
//		if(LL>dwStartLine+1) printf("\n");
//		//printf("%s",s2);
//		textcolor(15);
//		if(LL<10) cprintf("\rLine  %ld = ",LL);
//		else cprintf("\rLine %ld = ",LL);
//		textbackground(1);
//		cprintf("%s\r",s2);
//		textbackground(0);
//		CH=fgetc(fFile1);
//		if(CH==EOF){
//		  cprintf("\n");
//		  cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
//		  break;
//		}
//		ungetc(CH,fFile1);
//      }
//    }
//    if(!blUseStartLine && blUseEndLine){
//      for(LL=1;LL<=dwEndLine+1;LL++){
//		for(k=0;k<MAX_STRING;k++) s2[k]='\0';
//		fgets(s1,MAX_STRING+1,fFile1);
//		k=0;
//		for(j=0;j<strlen(s1);j++){
//		  if(s1[j]=='\n'){
//			s2[k]='\0';
//			break;
//		  }
//		  s2[k]=s1[j];
//		  k++;
//		}
//		if(LL>1) printf("\n");
//		//printf("%s",s2);
//		textcolor(15);
//		if(LL<10) cprintf("\rLine  %ld = ",LL);
//		else cprintf("\rLine %ld = ",LL);
//		textbackground(1);
//		cprintf("%s\r",s2);
//		textbackground(0);
//		CH=fgetc(fFile1);
//		if(CH==EOF){
//		  cprintf("\n");
//		  cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
//		  break;
//		}
//		ungetc(CH,fFile1);
//      }
//    }
//    if(blUseStartLine && blUseEndLine){
//      for(LL=1;LL<=dwEndLine+1;LL++){
//			for(k=0;k<MAX_STRING;k++) s2[k]='\0';
//			fgets(s1,MAX_STRING+1,fFile1);
//			if(LL<dwStartLine+1){
//					CH=fgetc(fFile1);
//					if(CH==EOF){
//					cprintf("\n");
//					cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
//					break;
//				}
//		  ungetc(CH,fFile1);
//		  strcpy(s1,zero);
//		  continue;
//		}
//		k=0;
//		for(j=0;j<strlen(s1);j++){
//		  if(s1[j]=='\n'){
//			s2[k]='\0';
//			break;
//		  }
//		  s2[k]=s1[j];
//		  k++;
//		}
//		// searching string between commas
//	  if(blComma){
//	    unsigned int ncmmIndx = 0, nSindx = 0;
//	    for(unsigned int si = 0 ; si < strlen(s2) ; si++){
//	      if(s1[si] == 0x2c) ncmmIndx += 1;
//	      if(ncmmIndx >= nSmsk){
//	        s2[nSindx] = s1[si];
//	        nSindx += 1;
//	        if(ncmmIndx == nEmsk){
//						nSindx --;
//						break;
//	        }
//	      }
//	    }
//	    if(ncmmIndx < nSmsk){
//	      Logo();	      
//	      return blResultOK;
//	    }
//	    s2[nSindx] = '\0';
//	    if(nSmsk != 0){ // if there start_comma clear first comma
//			unsigned int nsi = 0 ;
//	      for(; nsi < strlen(s2) ; nsi++)
//	        s2[nsi] = s2[nsi+1];
//	      s2[nsi] = '\0';
//	    }
//	    ncmmIndx = 0;
//	    nSindx = 0;
//	    } // end of blComma
//		if(LL>dwStartLine+1) printf("\n");
//		//printf("%s",s2);
//		textcolor(15);
//		if(LL<10) cprintf("\rLine  %ld = ",LL);
//		else cprintf("\rLine %ld = ",LL);
//		textbackground(1);
//		cprintf("%s\r",s2);
//		textbackground(0);
//		CH=fgetc(fFile1);
//		if(CH==EOF){
//		  cprintf("\n");
//		  cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
//		  break;
//		}
//		ungetc(CH,fFile1);
//      }
//    }
//  }
//  if(!blUseLine && blUseAddress){
//    if(blUseStartAddress && !blUseEndAddress){
//      LL=1;
//      while(!feof(fFile1)){
//		for(k=0;k<MAX_STRING;k++) s2[k]='\0';
//		fgets(s1,MAX_STRING+1,fFile1);
//		k=0;
//		for(j=(WORD) dwStartAddress;;j++){
//		  if(s1[j]=='\n' || j>strlen(s1)){
//			s2[k]='\0';
//			break;
//		  }
//		  s2[k]=s1[j];
//		  k++;
//		}
//		if(LL>1) printf("\n");
//		//printf("%s",s2);
//		textcolor(15);
//		if(LL<10) cprintf("\rLine  %ld (Byte %ld -> End) = ",LL,dwStartAddress+1);
//		else cprintf("\rLine %ld (Byte %ld -> End) = ",LL,dwStartAddress+1);
//		textbackground(1);
//		cprintf("%s\r",s2);
//		textbackground(0);
//		CH=fgetc(fFile1);
//		if(CH==EOF){
//		  cprintf("\n");
//		  cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
//		  break;
//		}
//		ungetc(CH,fFile1);
//		LL++;
//      }
//    }
//    if(!blUseStartAddress && blUseEndAddress){
//      LL=1;
//      while(!feof(fFile1)){
//		for(k=0;k<MAX_STRING;k++) s2[k]='\0';
//		fgets(s1,MAX_STRING+1,fFile1);
//		k=0;
//		for(j=0;j<=dwEndAddress;j++){
//		  if(s1[j]=='\n' || j>strlen(s1)){
//			s2[k]='\0';
//			break;
//		  }
//		  s2[k]=s1[j];
//		  k++;
//		}
//		if(LL>1) printf("\n");
//		//printf("%s",s2);
//		textcolor(15);
//		if(LL<10) cprintf("\rLine  %ld (Byte 1 -> %ld) = ",LL,dwEndAddress+1);
//		else cprintf("\rLine %ld (Byte 1 -> %ld) = ",LL,dwEndAddress+1);
//		textbackground(1);
//		cprintf("%s\r",s2);
//		textbackground(0);
//		CH=fgetc(fFile1);
//		if(CH==EOF){
//		  cprintf("\n");
//		  cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
//		  break;
//		}
//		ungetc(CH,fFile1);
//		LL++;
//      }
//    }
//    if(blUseStartAddress && blUseEndAddress){
//      LL=1;
//      while(!feof(fFile1)){
//				for(k=0;k<MAX_STRING;k++) s2[k]='\0';
//				fgets(s1,MAX_STRING+1,fFile1);
//				k=0;
//				for(j=(WORD) dwStartAddress;j<=(WORD) dwEndAddress;j++){
//					if(s1[j]=='\n' || j>strlen(s1)){
//						s2[k]='\0';
//						break;
//					}
//					s2[k]=s1[j];
//					k++;
//					if(j==dwEndAddress+1) s2[k]='\0';
//				}
//				if(LL>1) printf("\n");
//				//printf("%s",s2);
//				textcolor(15);
//				if(LL<10) cprintf("\rLine  %ld (Byte %ld -> %ld) = ",LL,dwStartAddress+1,dwEndAddress+1);
//				else cprintf("\rLine %ld (Byte %ld -> %ld) = ",LL,dwStartAddress+1,dwEndAddress+1);
//				textbackground(1);
//				cprintf("%s\r",s2);
//				textbackground(0);
//				CH=fgetc(fFile1);
//				if(CH==EOF){
//					cprintf("\n");
//					cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
//					break;
//				}
//				ungetc(CH,fFile1);
//				LL++;
//      }
//    }
//  }
//  if(blUseLine && blUseAddress){
//    if(blUseStartLine && !blUseEndLine && blUseStartAddress && !blUseEndAddress){
//      for(LL=1;;LL++){
//		for(k=0;k<MAX_STRING;k++) s2[k]='\0';
//		fgets(s1,MAX_STRING+1,fFile1);
//		if(LL<dwStartLine+1){
//		  CH=fgetc(fFile1);
//		  if(CH==EOF){
//			cprintf("\n");
//			cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
//			break;
//		  }
//		  ungetc(CH,fFile1);
//		  strcpy(s1,zero);
//		  continue;
//		}
//		k=0;
//		for(j=(WORD) dwStartAddress;;j++){
//		  if(s1[j]=='\n' || j>strlen(s1)){
//			s2[k]='\0';
//			break;
//		  }
//		  s2[k]=s1[j];
//		  k++;
//		}
//		if(LL>dwStartLine+1) printf("\n");
//		//printf("%s",s2);
//		textcolor(15);
//		if(LL<10) cprintf("\rLine  %ld (Byte %ld -> End) = ",LL,dwStartAddress+1);
//		else cprintf("\rLine %ld (Byte %ld -> End) = ",LL,dwStartAddress+1);
//		textbackground(1);
//		cprintf("%s\r",s2);
//		textbackground(0);
//		CH=fgetc(fFile1);
//		if(CH==EOF){
//		  cprintf("\n");
//		  cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
//		  break;
//		}
//		ungetc(CH,fFile1);
//      }
//    }
//    if(blUseStartLine && !blUseEndLine && !blUseStartAddress && blUseEndAddress){
//      for(LL=1;;LL++){
//		for(k=0;k<MAX_STRING;k++) s2[k]='\0';
//		fgets(s1,MAX_STRING+1,fFile1);
//		if(LL<dwStartLine+1){
//		  CH=fgetc(fFile1);
//		  if(CH==EOF){
//			cprintf("\n");
//			cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
//			break;
//		  }
//		  ungetc(CH,fFile1);
//		  strcpy(s1,zero);
//		  continue;
//		}
//		k=0;
//		for(j=0;j<=dwEndAddress;j++){
//		  if(s1[j]=='\n' || j>strlen(s1)){
//			s2[k]='\0';
//			break;
//		  }
//		  s2[k]=s1[j];
//		  k++;
//		  if(j==dwEndAddress+1) s2[k]='\0';
//		}
//		if(LL>dwStartLine+1) printf("\n");
//		//printf("%s",s2);
//		textcolor(15);
//		if(LL<10) cprintf("\rLine  %ld (Byte 1 -> %ld) = ",LL,dwEndAddress+1);
//		else cprintf("\rLine %ld (Byte 1 -> %ld) = ",LL,dwEndAddress+1);
//		textbackground(1);
//		cprintf("%s\r",s2);
//		textbackground(0);
//		CH=fgetc(fFile1);
//		if(CH==EOF){
//		  cprintf("\n");
//		  cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
//		  break;
//		}
//		ungetc(CH,fFile1);
//      }
//    }
//    if(blUseStartLine && !blUseEndLine && blUseStartAddress && blUseEndAddress){
//      for(LL=1;;LL++){
//		for(k=0;k<MAX_STRING;k++) s2[k]='\0';
//		fgets(s1,MAX_STRING+1,fFile1);
//		if(LL<dwStartLine+1){
//		  CH=fgetc(fFile1);
//		  if(CH==EOF){
//			cprintf("\n");
//			cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
//			break;
//		  }
//		  ungetc(CH,fFile1);
//		  strcpy(s1,zero);
//		  continue;
//		}
//		k=0;
//		for(j=(WORD) dwStartAddress;j<=(WORD) dwEndAddress;j++){
//		  if(s1[j]=='\n' || j>strlen(s1)){
//			s2[k]='\0';
//			break;
//		  }
//		  s2[k]=s1[j];
//		  k++;
//		  if(j==dwEndAddress+1) s2[k]='\0';
//		}
//		if(LL>dwStartLine+1) printf("\n");
//		//printf("%s",s2);
//		textcolor(15);
//		if(LL<10) cprintf("\rLine  %ld (Byte %ld -> %ld) = ",LL,dwStartAddress+1,dwEndAddress+1);
//		else cprintf("\rLine %ld (Byte %ld -> %ld) = ",LL,dwStartAddress+1,dwEndAddress+1);
//		textbackground(1);
//		cprintf("%s\r",s2);
//		textbackground(0);
//		CH=fgetc(fFile1);
//		if(CH==EOF){
//		  cprintf("\n");
//		  cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
//		  break;
//		}
//		ungetc(CH,fFile1);
//      }
//    }
//    if(!blUseStartLine && blUseEndLine && blUseStartAddress && !blUseEndAddress){
//      for(LL=1;LL<=dwEndLine+1;LL++){
//		for(k=0;k<MAX_STRING;k++) s2[k]='\0';
//		fgets(s1,MAX_STRING+1,fFile1);
//		k=0;
//		for(j=(WORD) dwStartAddress;;j++){
//		  if(s1[j]=='\n' || j>strlen(s1)){
//			s2[k]='\0';
//			break;
//		  }
//		  s2[k]=s1[j];
//		  k++;
//		}
//		if(LL>1) printf("\n");
//		//printf("%s",s2);
//		textcolor(15);
//		if(LL<10) cprintf("\rLine  %ld (Byte %ld -> End) = ",LL,dwStartAddress+1);
//		else cprintf("\rLine %ld (Byte %ld -> End) = ",LL,dwStartAddress+1);
//		textbackground(1);
//		cprintf("%s\r",s2);
//		textbackground(0);
//		CH=fgetc(fFile1);
//		if(CH==EOF){
//		  cprintf("\n");
//		  cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
//		  break;
//		}
//		ungetc(CH,fFile1);
//      }
//    }
//    if(!blUseStartLine && blUseEndLine && !blUseStartAddress && blUseEndAddress){
//      for(LL=1;LL<=dwEndLine+1;LL++){
//		for(k=0;k<MAX_STRING;k++) s2[k]='\0';
//		fgets(s1,MAX_STRING+1,fFile1);
//		k=0;
//		for(j=0;j<=dwEndAddress;j++){
//		  if(s1[j]=='\n' || j>strlen(s1)){
//			s2[k]='\0';
//			break;
//		  }
//		  s2[k]=s1[j];
//		  k++;
//		  if(j==dwEndAddress+1) s2[k]='\0';
//		}
//		if(LL>1) printf("\n");
//		//printf("%s",s2);
//		textcolor(15);
//		if(LL<10) cprintf("\rLine  %ld (Byte 1 -> %ld) = ",LL,dwEndAddress+1);
//		else cprintf("\rLine %ld (Byte 1 -> %ld) = ",LL,dwEndAddress+1);
//		textbackground(1);
//		cprintf("%s\r",s2);
//		textbackground(0);
//		CH=fgetc(fFile1);
//		if(CH==EOF){
//		  cprintf("\n");
//		  cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
//		  break;
//		}
//		ungetc(CH,fFile1);
//      }
//    }
//    if(!blUseStartLine && blUseEndLine && blUseStartAddress && blUseEndAddress){
//      for(LL=1;LL<=dwEndLine+1;LL++){
//		for(k=0;k<MAX_STRING;k++) s2[k]='\0';
//		fgets(s1,MAX_STRING+1,fFile1);
//		k=0;
//		for(j=(WORD) dwStartAddress;j<=(WORD) dwEndAddress;j++){
//		  if(s1[j]=='\n' || j>strlen(s1)){
//			s2[k]='\0';
//			break;
//		  }
//		  s2[k]=s1[j];
//		  k++;
//		  if(j==dwEndAddress+1) s2[k]='\0';
//		}
//		if(LL>1) printf("\n");
//		//printf("%s",s2);
//		textcolor(15);
//		if(LL<10) cprintf("\rLine  %ld (Byte %ld -> %ld) = ",LL,dwStartAddress+1,dwEndAddress+1);
//		else cprintf("\rLine %ld (Byte %ld -> %ld) = ",LL,dwStartAddress+1,dwEndAddress+1);
//		textbackground(1);
//		cprintf("%s\r",s2);
//		textbackground(0);
//		CH=fgetc(fFile1);
//		if(CH==EOF){
//		  cprintf("\n");
//		  cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
//		  break;
//		}
//		ungetc(CH,fFile1);
//      }
//    }
//    if(blUseStartLine && blUseEndLine && blUseStartAddress && !blUseEndAddress){
//      for(LL=1;LL<=dwEndLine+1;LL++){
//		for(k=0;k<MAX_STRING;k++) s2[k]='\0';
//		fgets(s1,MAX_STRING+1,fFile1);
//		if(LL<dwStartLine+1){
//		  CH=fgetc(fFile1);
//		  if(CH==EOF){
//			cprintf("\n");
//			cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
//			break;
//		  }
//		  ungetc(CH,fFile1);
//		  strcpy(s1,zero);
//		  continue;
//		}
//		k=0;
//		for(j=(WORD) dwStartAddress;;j++){
//		  if(s1[j]=='\n' || j>strlen(s1)){
//			s2[k]='\0';
//			break;
//		  }
//		  s2[k]=s1[j];
//		  k++;
//		}
//		if(LL>dwStartLine+1) printf("\n");
//		//printf("%s",s2);
//		textcolor(15);
//		if(LL<10) cprintf("\rLine  %ld (Byte %ld -> End) = ",LL,dwStartAddress+1);
//		else cprintf("\rLine %ld (Byte %ld -> End) = ",LL,dwStartAddress+1);
//		textbackground(1);
//		cprintf("%s\r",s2);
//		textbackground(0);
//		CH=fgetc(fFile1);
//		if(CH==EOF){
//		  cprintf("\n");
//		  cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
//		  break;
//		}
//		ungetc(CH,fFile1);
//      }
//    }
//    if(blUseStartLine && blUseEndLine && !blUseStartAddress && blUseEndAddress){
//      for(LL=1;LL<=dwEndLine+1;LL++){
//		    for(k=0;k<MAX_STRING;k++) s2[k]='\0';
//		    fgets(s1,MAX_STRING+1,fFile1);
//		    if(LL<dwStartLine+1){
//		     CH=fgetc(fFile1);
//		     if(CH==EOF){
//			    cprintf("\n");
//			    cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
//			    break;
//		     }
//		     ungetc(CH,fFile1);
//		     strcpy(s1,zero);
//		     continue;
//		    }
//		    k=0;
//				for(j=0;j<=dwEndAddress;j++){
//					if(s1[j]=='\n' || j>strlen(s1)){
//						s2[k]='\0';
//						break;
//					}
//					s2[k]=s1[j];
//					k++;
//					if(j==dwEndAddress+1) s2[k]='\0';
//				}
//				if(LL>dwStartLine+1) printf("\n");
//				//printf("%s",s2);
//				textcolor(15);
//				if(LL<10) cprintf("\rLine  %ld (Byte 1 -> %ld) = ",LL,dwEndAddress+1);
//				else cprintf("\rLine %ld (Byte 1 -> %ld) = ",LL,dwEndAddress+1);
//				textbackground(1);
//				cprintf("%s\r",s2);
//				textbackground(0);
//				CH=fgetc(fFile1);
//				if(CH==EOF){
//					cprintf("\n");
//					cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
//				break;
//				}
//				ungetc(CH,fFile1);
//      }
//    }
//    if(blUseStartLine && blUseEndLine && blUseStartAddress && blUseEndAddress){
//      for(LL=1;LL<=dwEndLine+1;LL++){
//				for(k=0;k<MAX_STRING;k++) s2[k]='\0';
//				fgets(s1,MAX_STRING+1,fFile1);
//				if(LL<dwStartLine+1){
//					CH=fgetc(fFile1);
//					if(CH==EOF){
//						cprintf("\n");
//						cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
//						break;
//					}
//					ungetc(CH,fFile1);
//					strcpy(s1,zero);
//					continue;
//				}
//				k=0;
//				if(blComma){ // if comma
//					unsigned int ncmmIndx = 0, nSindx = 0;
//					for(unsigned int si = 0 ; si < strlen(s1) ; si++){
//						if(s1[si] == 0x2c) ncmmIndx += 1;
//						if(ncmmIndx >= nSmsk){
//							s2[nSindx] = s1[si];
//							nSindx += 1;
//							if(ncmmIndx == nEmsk){
//								nSindx --;
//								break;
//							}
//	 					}
//					}
//					if(ncmmIndx < nSmsk){
//						//Logo();
//						//asus.PrintStr(1, 4, " the number of line comma is less than of inputed comma !!", 0, 0x07);
//						//printf(" the number of line comma is less than of inputed comma !!");
//						//return blResultOK;
//					}
//					s2[nSindx] = '\0';
//					if(nSmsk != 0){ // if there start_comma clear first comma
//						unsigned int nsi = 0 ;
//						for(; nsi < strlen(s2) ; nsi++)
//							s2[nsi] = s2[nsi+1];
//						s2[nsi] = '\0';
//					
//					}
//					ZeroMemory(s1, MAX_STRING);
//					memcpy(s1, s2, sizeof(s2));
//					ZeroMemory(s2, MAX_STRING);
//				} // end of blComma
//				for(j=(WORD) dwStartAddress;j<=(WORD) dwEndAddress;j++){
//					if(s1[j]=='\n' || j>strlen(s1)){
//						s2[k]='\0';
//						break;
//					}
//					s2[k]=s1[j];
//					k++;
//					if(j==dwEndAddress+1) s2[k]='\0';
//				}
//				if(LL>dwStartLine+1) printf("\n");
//				//printf("%s",s2);
//				textcolor(15);
//				if(LL<10) cprintf("\rLine  %ld (Byte %ld -> %ld) = ",LL,dwStartAddress+1,dwEndAddress+1);
//				else cprintf("\rLine %ld (Byte %ld -> %ld) = ",LL,dwStartAddress+1,dwEndAddress+1);
//				textbackground(1);
//				cprintf("%s\r",s2);
//				textbackground(0);
//				CH=fgetc(fFile1);
//				if(CH==EOF){
//					cprintf("\n");
//					cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
//					break;
//				}
//				ungetc(CH,fFile1);
//      }
//    }
//  }
//  if(!blUseLine && !blUseAddress){
//    LL=1;
//    while(!feof(fFile1)){
//      for(k=0;k<MAX_STRING;k++) s2[k]='\0';
//      fgets(s1,MAX_STRING+1,fFile1);
//      k=0;
//      for(j=0;j<strlen(s1);j++){
//				if(s1[j]=='\n'){
//					s2[k]='\0';
//					break;
//				}
//				s2[k]=s1[j];
//				k++;
//      }
//			if(blComma){ // if comma
//				unsigned int ncmmIndx = 0, nSindx = 0;
//				for(unsigned int si = 0 ; si < strlen(s1) ; si++){
//					if(s1[si] == 0x2c) ncmmIndx += 1;
//					if(ncmmIndx >= nSmsk){
//						s2[nSindx] = s1[si];
//						nSindx += 1;
//						if(ncmmIndx == nEmsk){
//							nSindx --;
//							break;
//						}
//	 			 }
//				}
//				if(ncmmIndx < nSmsk){
//					//Logo();
//					//asus.PrintStr(1, 4, " the number of line comma is less than of inputed comma !!", 0, 0x07);
//					//printf(" the number of line comma is less than of inputed comma !!");
//					//return blResultOK;
//				}
//				s2[nSindx] = '\0';
//				if(nSmsk != 0){ // if start_comma clear first comma
//					unsigned int nsi = 0 ;
//					for(; nsi < strlen(s2) ; nsi++)
//						s2[nsi] = s2[nsi+1];
//					s2[nsi] = '\0';
//				}
//			} // end of blComma
//			if(LL>1) printf("\n");
//			//printf("%s",s2);
//			textcolor(15);
//			if(LL<10) cprintf("\rLine  %ld = ",LL);
//			else cprintf("\rLine %ld = ",LL);
//			textbackground(1);
//			cprintf("%s\r",s2);
//			textbackground(0);
//			CH=fgetc(fFile1);
//			if(CH==EOF){
//				cprintf("\n");
//				cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
//				break;
//			}
//			ungetc(CH,fFile1);
//			LL++;
//    }
//  }
//  fcloseall();
//  return blResultOK;
//}
//
//

BOOL GetString(char File1[])
{
  FILE *fFile1;
  const unsigned int MAX_STRING = 1024;
  char s1[MAX_STRING]="\0",s2[MAX_STRING]="\0",zero[MAX_STRING]="\0",CH='\0';
  int  j,k,m;
  BOOL blResultOK=FALSE;
  if((fFile1=fopen(File1,"r"))==NULL) {
    cprintf("ERROR !! Can't Open %s !!\n\r",File1);
    fcloseall();
    return blResultOK;
  }




  if(blLastBit){
    fgets(s1,MAX_STRING,fFile1);
    if(LastBit>strlen(s1)) LastBit=strlen(s1);
    for(k=0;k<LastBit;k++) {
      if(s1[strlen(s1)-1]=='\n' && LastBit<strlen(s1)) s2[k]=s1[strlen(s1)-LastBit+k-1];
      else s2[k]=s1[strlen(s1)-LastBit+k];
    }
    s2[k]='\0';
    printf("%s",s2);
    return blResultOK;
  }
  if(blUseLine && !blUseAddress){ // use line
    if(blUseStartLine && !blUseEndLine){  // start line but end line
      for(LL=1;;LL++){
	for(k=0;k<MAX_STRING;k++) s2[k]='\0';
	fgets(s1,MAX_STRING+1,fFile1);
	if(LL<dwStartLine+1){
	  CH=fgetc(fFile1);
	  if(CH==EOF){
	    cprintf("\n");
	    cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
	    break;
	  }
	  ungetc(CH,fFile1);
	  strcpy(s1,zero);
	  continue;
	}
	k=0;
	for(j=0;j<strlen(s1);j++){
	  if(s1[j]=='\n'){
	    s2[k]='\0';
	    break;
	  }
	  s2[k]=s1[j];
	  k++;
	}
	if(LL>dwStartLine+1) printf("\n");
	printf("%s",s2);
	textcolor(15);
	if(LL<10) cprintf("\rLine  %ld = ",LL);
	else cprintf("\rLine %ld = ",LL);
	textbackground(1);
	cprintf("%s\r",s2);
	textbackground(0);
	CH=fgetc(fFile1);
	if(CH==EOF){
	  cprintf("\n");
	  cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
	  break;
	}
	ungetc(CH,fFile1);
      }
    }
    if(!blUseStartLine && blUseEndLine){
      for(LL=1;LL<=dwEndLine+1;LL++){
	for(k=0;k<MAX_STRING;k++) s2[k]='\0';
	fgets(s1,MAX_STRING+1,fFile1);
	k=0;
	for(j=0;j<strlen(s1);j++){
	  if(s1[j]=='\n'){
	    s2[k]='\0';
	    break;
	  }
	  s2[k]=s1[j];
	  k++;
	}
	if(LL>1) printf("\n");
	printf("%s",s2);
	textcolor(15);
	if(LL<10) cprintf("\rLine  %ld = ",LL);
	else cprintf("\rLine %ld = ",LL);
	textbackground(1);
	cprintf("%s\r",s2);
	textbackground(0);
	CH=fgetc(fFile1);
	if(CH==EOF){
	  cprintf("\n");
	  cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
	  break;
	}
	ungetc(CH,fFile1);
      }
    }
    if(blUseStartLine && blUseEndLine){
      for(LL=1;LL<=dwEndLine+1;LL++){
	for(k=0;k<MAX_STRING;k++) s2[k]='\0';
	fgets(s1,MAX_STRING+1,fFile1);
	if(LL<dwStartLine+1){
	  CH=fgetc(fFile1);
	  if(CH==EOF){
	    cprintf("\n");
	    cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
	    break;
	  }
	  ungetc(CH,fFile1);
	  strcpy(s1,zero);
	  continue;
	}
	k=0;
	for(j=0;j<strlen(s1);j++){
	  if(s1[j]=='\n'){
	    s2[k]='\0';
	    break;
	  }
	  s2[k]=s1[j];
	  k++;
	}
	// searching string between commas
	if(blComma){
	  int ncmmIndx = 0, nSindx = 0;
	  int si = 0;
	  for( ; si < strlen(s2) ; si++){
	    if(s1[si] == 0x2c) ncmmIndx += 1;
	    if(ncmmIndx >= nSmsk){
	      s2[nSindx] = s1[si];
	      nSindx += 1;
	      if(ncmmIndx == nEmsk){
		nSindx --;
		break;
	      }
	    }
	  }
	  if(ncmmIndx < nSmsk){
	    Logo();
	    PrintStr(1, 4, " the number of line comma is less than of inputed comma !!", 0, 0x07);
	    return blResultOK;
	  }
	  s2[nSindx] = '\0';
	  if(nSmsk != 0){ // if there start_comma clear first comma
		int nsi = 0;
	    for( ; nsi < strlen(s2) ; nsi++)
	      s2[nsi] = s2[nsi+1];
	    s2[nsi] = '\0';
	  }
	  ncmmIndx = 0;
	  nSindx = 0;
	} // end of blComma

	if(LL>dwStartLine+1) printf("\n");
	printf("%s",s2);
	textcolor(15);
	if(LL<10) cprintf("\rLine  %ld = ",LL);
	else cprintf("\rLine %ld = ",LL);
	textbackground(1);
	cprintf("%s\r",s2);
	textbackground(0);
	CH=fgetc(fFile1);
	if(CH==EOF){
	  cprintf("\n");
	  cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
	  break;
	}
	ungetc(CH,fFile1);

      }
    }
  }
  if(!blUseLine && blUseAddress){
    if(blUseStartAddress && !blUseEndAddress){
      LL=1;
      while(!feof(fFile1)){
	for(k=0;k<MAX_STRING;k++) s2[k]='\0';
	fgets(s1,MAX_STRING+1,fFile1);
	k=0;
	for(j=dwStartAddress;;j++){
	  if(s1[j]=='\n' || j>strlen(s1)){
	    s2[k]='\0';
	    break;
	  }
	  s2[k]=s1[j];
	  k++;
	}
	if(LL>1) printf("\n");
	printf("%s",s2);
	textcolor(15);
	if(LL<10) cprintf("\rLine  %ld (Byte %ld -> End) = ",LL,dwStartAddress+1);
	else cprintf("\rLine %ld (Byte %ld -> End) = ",LL,dwStartAddress+1);
	textbackground(1);
	cprintf("%s\r",s2);
	textbackground(0);
	CH=fgetc(fFile1);
	if(CH==EOF){
	  cprintf("\n");
	  cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
	  break;
	}
	ungetc(CH,fFile1);
	LL++;
      }
    }
    if(!blUseStartAddress && blUseEndAddress){
      LL=1;
      while(!feof(fFile1)){
	for(k=0;k<MAX_STRING;k++) s2[k]='\0';
	fgets(s1,MAX_STRING+1,fFile1);
	k=0;
	for(j=0;j<=dwEndAddress;j++){
	  if(s1[j]=='\n' || j>strlen(s1)){
	    s2[k]='\0';
	    break;
	  }
	  s2[k]=s1[j];
	  k++;
	}
	if(LL>1) printf("\n");
	printf("%s",s2);
	textcolor(15);
	if(LL<10) cprintf("\rLine  %ld (Byte 1 -> %ld) = ",LL,dwEndAddress+1);
	else cprintf("\rLine %ld (Byte 1 -> %ld) = ",LL,dwEndAddress+1);
	textbackground(1);
	cprintf("%s\r",s2);
	textbackground(0);
	CH=fgetc(fFile1);
	if(CH==EOF){
	  cprintf("\n");
	  cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
	  break;
	}
	ungetc(CH,fFile1);
	LL++;
      }
    }
    if(blUseStartAddress && blUseEndAddress){
      LL=1;
      while(!feof(fFile1)){
	for(k=0;k<MAX_STRING;k++) s2[k]='\0';
	fgets(s1,MAX_STRING+1,fFile1);
	k=0;
	for(j=dwStartAddress;j<=dwEndAddress;j++){
	  if(s1[j]=='\n' || j>strlen(s1)){
	    s2[k]='\0';
	    break;
	  }
	  s2[k]=s1[j];
	  k++;
	  if(j==dwEndAddress+1) s2[k]='\0';
	}
	if(LL>1) printf("\n");
	printf("%s",s2);
	textcolor(15);
	if(LL<10) cprintf("\rLine  %ld (Byte %ld -> %ld) = ",LL,dwStartAddress+1,dwEndAddress+1);
	else cprintf("\rLine %ld (Byte %ld -> %ld) = ",LL,dwStartAddress+1,dwEndAddress+1);
	textbackground(1);
	cprintf("%s\r",s2);
	textbackground(0);
	CH=fgetc(fFile1);
	if(CH==EOF){
	  cprintf("\n");
	  cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
	  break;
	}
	ungetc(CH,fFile1);
	LL++;
      }
    }
  }
  if(blUseLine && blUseAddress){
    if(blUseStartLine && !blUseEndLine && blUseStartAddress && !blUseEndAddress){
      for(LL=1;;LL++){
	for(k=0;k<MAX_STRING;k++) s2[k]='\0';
	fgets(s1,MAX_STRING+1,fFile1);
	if(LL<dwStartLine+1){
	  CH=fgetc(fFile1);
	  if(CH==EOF){
	    cprintf("\n");
	    cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
	    break;
	  }
	  ungetc(CH,fFile1);
	  strcpy(s1,zero);
	  continue;
	}
	k=0;
	for(j=dwStartAddress;;j++){
	  if(s1[j]=='\n' || j>strlen(s1)){
	    s2[k]='\0';
	    break;
	  }
	  s2[k]=s1[j];
	  k++;
	}
	if(LL>dwStartLine+1) printf("\n");
	printf("%s",s2);
	textcolor(15);
	if(LL<10) cprintf("\rLine  %ld (Byte %ld -> End) = ",LL,dwStartAddress+1);
	else cprintf("\rLine %ld (Byte %ld -> End) = ",LL,dwStartAddress+1);
	textbackground(1);
	cprintf("%s\r",s2);
	textbackground(0);
	CH=fgetc(fFile1);
	if(CH==EOF){
	  cprintf("\n");
	  cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
	  break;
	}
	ungetc(CH,fFile1);
      }
    }
    if(blUseStartLine && !blUseEndLine && !blUseStartAddress && blUseEndAddress){
      for(LL=1;;LL++){
	for(k=0;k<MAX_STRING;k++) s2[k]='\0';
	fgets(s1,MAX_STRING+1,fFile1);
	if(LL<dwStartLine+1){
	  CH=fgetc(fFile1);
	  if(CH==EOF){
	    cprintf("\n");
	    cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
	    break;
	  }
	  ungetc(CH,fFile1);
	  strcpy(s1,zero);
	  continue;
	}
	k=0;
	for(j=0;j<=dwEndAddress;j++){
	  if(s1[j]=='\n' || j>strlen(s1)){
	    s2[k]='\0';
	    break;
	  }
	  s2[k]=s1[j];
	  k++;
	  if(j==dwEndAddress+1) s2[k]='\0';
	}
	if(LL>dwStartLine+1) printf("\n");
	printf("%s",s2);
	textcolor(15);
	if(LL<10) cprintf("\rLine  %ld (Byte 1 -> %ld) = ",LL,dwEndAddress+1);
	else cprintf("\rLine %ld (Byte 1 -> %ld) = ",LL,dwEndAddress+1);
	textbackground(1);
	cprintf("%s\r",s2);
	textbackground(0);
	CH=fgetc(fFile1);
	if(CH==EOF){
	  cprintf("\n");
	  cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
	  break;
	}
	ungetc(CH,fFile1);
      }
    }
    if(blUseStartLine && !blUseEndLine && blUseStartAddress && blUseEndAddress){
      for(LL=1;;LL++){
	for(k=0;k<MAX_STRING;k++) s2[k]='\0';
	fgets(s1,MAX_STRING+1,fFile1);
	if(LL<dwStartLine+1){
	  CH=fgetc(fFile1);
	  if(CH==EOF){
	    cprintf("\n");
	    cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
	    break;
	  }
	  ungetc(CH,fFile1);
	  strcpy(s1,zero);
	  continue;
	}
	k=0;
	for(j=dwStartAddress;j<=dwEndAddress;j++){
	  if(s1[j]=='\n' || j>strlen(s1)){
	    s2[k]='\0';
	    break;
	  }
	  s2[k]=s1[j];
	  k++;
	  if(j==dwEndAddress+1) s2[k]='\0';
	}
	if(LL>dwStartLine+1) printf("\n");
	printf("%s",s2);
	textcolor(15);
	if(LL<10) cprintf("\rLine  %ld (Byte %ld -> %ld) = ",LL,dwStartAddress+1,dwEndAddress+1);
	else cprintf("\rLine %ld (Byte %ld -> %ld) = ",LL,dwStartAddress+1,dwEndAddress+1);
	textbackground(1);
	cprintf("%s\r",s2);
	textbackground(0);
	CH=fgetc(fFile1);
	if(CH==EOF){
	  cprintf("\n");
	  cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
	  break;
	}
	ungetc(CH,fFile1);
      }
    }
    if(!blUseStartLine && blUseEndLine && blUseStartAddress && !blUseEndAddress){
      for(LL=1;LL<=dwEndLine+1;LL++){
	for(k=0;k<MAX_STRING;k++) s2[k]='\0';
	fgets(s1,MAX_STRING+1,fFile1);
	k=0;
	for(j=dwStartAddress;;j++){
	  if(s1[j]=='\n' || j>strlen(s1)){
	    s2[k]='\0';
	    break;
	  }
	  s2[k]=s1[j];
	  k++;
	}
	if(LL>1) printf("\n");
	printf("%s",s2);
	textcolor(15);
	if(LL<10) cprintf("\rLine  %ld (Byte %ld -> End) = ",LL,dwStartAddress+1);
	else cprintf("\rLine %ld (Byte %ld -> End) = ",LL,dwStartAddress+1);
	textbackground(1);
	cprintf("%s\r",s2);
	textbackground(0);
	CH=fgetc(fFile1);
	if(CH==EOF){
	  cprintf("\n");
	  cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
	  break;
	}
	ungetc(CH,fFile1);
      }
    }
    if(!blUseStartLine && blUseEndLine && !blUseStartAddress && blUseEndAddress){
      for(LL=1;LL<=dwEndLine+1;LL++){
	for(k=0;k<MAX_STRING;k++) s2[k]='\0';
	fgets(s1,MAX_STRING+1,fFile1);
	k=0;
	for(j=0;j<=dwEndAddress;j++){
	  if(s1[j]=='\n' || j>strlen(s1)){
	    s2[k]='\0';
	    break;
	  }
	  s2[k]=s1[j];
	  k++;
	  if(j==dwEndAddress+1) s2[k]='\0';
	}
	if(LL>1) printf("\n");
	printf("%s",s2);
	textcolor(15);
	if(LL<10) cprintf("\rLine  %ld (Byte 1 -> %ld) = ",LL,dwEndAddress+1);
	else cprintf("\rLine %ld (Byte 1 -> %ld) = ",LL,dwEndAddress+1);
	textbackground(1);
	cprintf("%s\r",s2);
	textbackground(0);
	CH=fgetc(fFile1);
	if(CH==EOF){
	  cprintf("\n");
	  cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
	  break;
	}
	ungetc(CH,fFile1);
      }
    }
    if(!blUseStartLine && blUseEndLine && blUseStartAddress && blUseEndAddress){
      for(LL=1;LL<=dwEndLine+1;LL++){
	for(k=0;k<MAX_STRING;k++) s2[k]='\0';
	fgets(s1,MAX_STRING+1,fFile1);
	k=0;
	for(j=dwStartAddress;j<=dwEndAddress;j++){
	  if(s1[j]=='\n' || j>strlen(s1)){
	    s2[k]='\0';
	    break;
	  }
	  s2[k]=s1[j];
	  k++;
	  if(j==dwEndAddress+1) s2[k]='\0';
	}
	if(LL>1) printf("\n");
	printf("%s",s2);
	textcolor(15);
	if(LL<10) cprintf("\rLine  %ld (Byte %ld -> %ld) = ",LL,dwStartAddress+1,dwEndAddress+1);
	else cprintf("\rLine %ld (Byte %ld -> %ld) = ",LL,dwStartAddress+1,dwEndAddress+1);
	textbackground(1);
	cprintf("%s\r",s2);
	textbackground(0);
	CH=fgetc(fFile1);
	if(CH==EOF){
	  cprintf("\n");
	  cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
	  break;
	}
	ungetc(CH,fFile1);
      }
    }
    if(blUseStartLine && blUseEndLine && blUseStartAddress && !blUseEndAddress){
      for(LL=1;LL<=dwEndLine+1;LL++){
	for(k=0;k<MAX_STRING;k++) s2[k]='\0';
	fgets(s1,MAX_STRING+1,fFile1);
	if(LL<dwStartLine+1){
	  CH=fgetc(fFile1);
	  if(CH==EOF){
	    cprintf("\n");
	    cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
	    break;
	  }
	  ungetc(CH,fFile1);
	  strcpy(s1,zero);
	  continue;
	}
	k=0;
	for(j=dwStartAddress;;j++){
	  if(s1[j]=='\n' || j>strlen(s1)){
	    s2[k]='\0';
	    break;
	  }
	  s2[k]=s1[j];
	  k++;
	}
	if(LL>dwStartLine+1) printf("\n");
	printf("%s",s2);
	textcolor(15);
	if(LL<10) cprintf("\rLine  %ld (Byte %ld -> End) = ",LL,dwStartAddress+1);
	else cprintf("\rLine %ld (Byte %ld -> End) = ",LL,dwStartAddress+1);
	textbackground(1);
	cprintf("%s\r",s2);
	textbackground(0);
	CH=fgetc(fFile1);
	if(CH==EOF){
	  cprintf("\n");
	  cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
	  break;
	}
	ungetc(CH,fFile1);
      }
    }
    if(blUseStartLine && blUseEndLine && !blUseStartAddress && blUseEndAddress){
      for(LL=1;LL<=dwEndLine+1;LL++){
	for(k=0;k<MAX_STRING;k++) s2[k]='\0';
	fgets(s1,MAX_STRING+1,fFile1);
	if(LL<dwStartLine+1){
	  CH=fgetc(fFile1);
	  if(CH==EOF){
	    cprintf("\n");
	    cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
	    break;
	  }
	  ungetc(CH,fFile1);
	  strcpy(s1,zero);
	  continue;
	}
	k=0;
	for(j=0;j<=dwEndAddress;j++){
	  if(s1[j]=='\n' || j>strlen(s1)){
	    s2[k]='\0';
	    break;
	  }
	  s2[k]=s1[j];
	  k++;
	  if(j==dwEndAddress+1) s2[k]='\0';
	}
	if(LL>dwStartLine+1) printf("\n");
	printf("%s",s2);
	textcolor(15);
	if(LL<10) cprintf("\rLine  %ld (Byte 1 -> %ld) = ",LL,dwEndAddress+1);
	else cprintf("\rLine %ld (Byte 1 -> %ld) = ",LL,dwEndAddress+1);
	textbackground(1);
	cprintf("%s\r",s2);
	textbackground(0);
	CH=fgetc(fFile1);
	if(CH==EOF){
	  cprintf("\n");
	  cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
	  break;
	}
	ungetc(CH,fFile1);
      }
    }
    if(blUseStartLine && blUseEndLine && blUseStartAddress && blUseEndAddress){
      for(LL=1;LL<=dwEndLine+1;LL++){
	for(k=0;k<MAX_STRING;k++) s2[k]='\0';
	fgets(s1,MAX_STRING+1,fFile1);
	if(LL<dwStartLine+1){
	  CH=fgetc(fFile1);
	  if(CH==EOF){
	    cprintf("\n");
	    cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
	    break;
	  }
	  ungetc(CH,fFile1);
	  strcpy(s1,zero);
	  continue;
	}
	k=0;
	if(blComma){ // if comma
	  int ncmmIndx = 0, nSindx = 0;
	  for(int si = 0 ; si < strlen(s1) ; si++){
	    if(s1[si] == 0x2c) ncmmIndx += 1;
	    if(ncmmIndx >= nSmsk){
	      s2[nSindx] = s1[si];
	      nSindx += 1;
	      if(ncmmIndx == nEmsk){
		nSindx --;
		break;
	      }
	    }
	  }
	  if(ncmmIndx < nSmsk){
	    Logo();
	    PrintStr(1, 4, " the number of line comma is less than of inputed comma !!", 0, 0x07);
	    //printf(" the number of line comma is less than of inputed comma !!");
	    return blResultOK;
	  }
	  s2[nSindx] = '\0';
	  if(nSmsk != 0){ // if there start_comma clear first comma
		  int nsi = 0;
	    for( ; nsi < strlen(s2) ; nsi++)
	      s2[nsi] = s2[nsi+1];
	    s2[nsi] = '\0';
	  }
	  memset(s1, 0x00, MAX_STRING);
	  memcpy(s1, s2, sizeof(s2));
	  memset(s2, 0x00, MAX_STRING);
	} // end of blComma
	for(j=dwStartAddress;j<=dwEndAddress;j++){
	  if(s1[j]=='\n' || j>strlen(s1)){
	    s2[k]='\0';
	    break;
	  }
	  s2[k]=s1[j];
	  k++;
	  if(j==dwEndAddress+1) s2[k]='\0';
	}
	if(LL>dwStartLine+1) printf("\n");
	printf("%s",s2);
	textcolor(15);
	if(LL<10) cprintf("\rLine  %ld (Byte %ld -> %ld) = ",LL,dwStartAddress+1,dwEndAddress+1);
	else cprintf("\rLine %ld (Byte %ld -> %ld) = ",LL,dwStartAddress+1,dwEndAddress+1);
	textbackground(1);
	cprintf("%s\r",s2);
	textbackground(0);
	CH=fgetc(fFile1);
	if(CH==EOF){
	  cprintf("\n");
	  cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
	  break;
	}
	ungetc(CH,fFile1);
      }
    }
  }
  if(!blUseLine && !blUseAddress){
    LL=1;
    while(!feof(fFile1)){
      for(k=0;k<MAX_STRING;k++) s2[k]='\0';
      fgets(s1,MAX_STRING+1,fFile1);
      k=0;
      for(j=0;j<strlen(s1);j++){
	if(s1[j]=='\n'){
	  s2[k]='\0';
	  break;
	}
	s2[k]=s1[j];
	k++;
      }
      if(blComma){ // if comma
	int ncmmIndx = 0, nSindx = 0;
	for(int si = 0 ; si < strlen(s1) ; si++){
	  if(s1[si] == 0x2c) ncmmIndx += 1;
	  if(ncmmIndx >= nSmsk){
	    s2[nSindx] = s1[si];
	    nSindx += 1;
	    if(ncmmIndx == nEmsk){
	      nSindx --;
	      break;
	    }
	  }
	}
	if(ncmmIndx < nSmsk){
	  Logo();
	  PrintStr(1, 4, " the number of line comma is less than of inputed comma !!", 0, 0x07);
	  //printf(" the number of line comma is less than of inputed comma !!");
	  return blResultOK;
	}
	s2[nSindx] = '\0';
	if(nSmsk != 0){ // if there start_comma clear first comma
		int nsi = 0 ;
	  for(; nsi < strlen(s2) ; nsi++)
	    s2[nsi] = s2[nsi+1];
	  s2[nsi] = '\0';
	}
      } // end of blComma
      if(LL>1) printf("\n");
      printf("%s",s2);
      textcolor(15);
      if(LL<10) cprintf("\rLine  %ld = ",LL);
      else cprintf("\rLine %ld = ",LL);
      textbackground(1);
      cprintf("%s\r",s2);
      textbackground(0);
      if(blComma) break;
      CH=fgetc(fFile1);
      if(CH==EOF){
	cprintf("\n");
	cprintf("\rLine %ld Is End of File !!\n\r",LL+1);
	break;
      }
      ungetc(CH,fFile1);
      LL++;
    }
  }

  fcloseall();
  return blResultOK;
}

BOOL Set_Environment_Variable(char str3[],char EnvirVar[],char In_File[]/*char Out_File[]*/)
{
  FILE *fin,*fout;
  int  j,kk,m,mm,line=1,match=0;
  char s[450]="\0",ch1,s1[450]="\0";
  BOOL blResultOK=FALSE;
  WORD jj, k;

  textcolor(15);
  if((fin=fopen(In_File,"r"))==NULL) {
    textbackground(4);
    cprintf("\n\rERROR !! %s Not Found !!\n\r",In_File);
	textbackground(0);
    fcloseall();
    return blResultOK;
  }
 // if((fout=fopen(Out_File,"w"))==NULL) {
 //   textbackground(4);
 //   cprintf("\n\rERROR !! Can't Open %s !!\n\r",Out_File);
	//textbackground(0);
 //   fcloseall();
 //   return blResultOK;
 // }
  if(strlen(EnvirVar)>1){
    for(k=0;k<strlen(EnvirVar);k++) EnvirVar[k]=toupper(EnvirVar[k]);
    fgets(s,450,fin);
    //for(k=0;k<strlen(s);k++) s[k]=toupper(s[k]);
    printf("%s","SET ");
    printf("%s",EnvirVar);
    printf("%s",s);
    //fprintf(fout,"%s","SET ");
    //fprintf(fout,"%s",EnvirVar);
    //fprintf(fout,"%s",s);
    textbackground(1);
    cprintf("\n\rPASS !! Environment Variable File Is OK !!\n\r");
	textbackground(0);
    blResultOK=TRUE;
  }
  if(strlen(str3)>1){
    while(!feof(fin)){
      kk=0;
      fgets(s,450,fin);
      for(k=0;k<strlen(s);k++) s[k]=toupper(s[k]);
      for(k=0;k<strlen(str3);k++) str3[k]=toupper(str3[k]);
      while(match==0){
		j=0;
		for(k=kk;k<strlen(s);k++){
		  if(s[k]=='\n' || s[k]==','){
			s1[j]='\0';
			break;
		  }
		  s1[j]=s[k];
		  j++;
		}
		if(stricmp(s1,str3)==0){
		  match=1;
		  fclose(fin);
		  fin=fopen(In_File,"r");
		  for(m=1;m<=line;m++) fgets(s,450,fin);
		  //for(k=0;k<strlen(s);k++) s[k]=toupper(s[k]);
		  mm=0;
		  for(;;){
			jj=0;
			for(k=mm;k<strlen(s);k++){
			  if(s[k]=='\n' || s[k]==','){
				s1[jj]='\0';
				break;
			  }
			  s1[jj]=s[k];
			  jj++;
			}
			for(jj=0;jj<strlen(s1);jj++){
			  if(s1[jj]=='='){
				fprintf(fout,"%s","SET ");
				fprintf(fout,"%s\n",s1);
				break;
			  }
			}
			if(s[k]=='\n') break;
			else mm=k+1;
		  }
		  textbackground(1);
		  cprintf("\n\rPASS !! Environment Variable File Is OK !!\n\r");
		  textbackground(0);
		  blResultOK=TRUE;
		}
		if(s[k]=='\n') break;
		else kk=k+1;
      }
      if(match==1) break;
      ch1=fgetc(fin);
      if(ch1==EOF) break;
      ungetc(ch1,fin);
      line++;
    }
    if(match==0){
      textbackground(4);
      cprintf("\n\rERROR !! String '%s' Not Found !!\n\r",str3);
	  textbackground(0);
    }
  }
  fcloseall();
  return blResultOK;
}


BOOL WlFileIntoCertainPosition(char *fn1, char *fn2, char *fn3, char *place)
{
  FILE *f,*f1,*f2;
  long int x;
  unsigned char d;
  char *result, s[10];
  BYTE bData;
  BOOL blResultOK=FALSE;
  DWORD dwTemp;

  d=0,s[10]=0;
  textcolor(15);
  sscanf(place, "%lX", &dwTemp);
  x=dwTemp;
  if((f=fopen(fn3,"wb"))==NULL) {
    textbackground(4);
    cprintf("\n\rERROR !! %s Not Found !!\n\r",fn3);
	textbackground(0);
    fcloseall();
    return blResultOK;
  }
  if((f1=fopen(fn1,"rb"))==NULL) {
    textbackground(4);
    cprintf("\n\rERROR !! %s Not Found !!\n\r",fn1);
	textbackground(0);
    fcloseall();
    return blResultOK;
  }
  while(fscanf(f1,"%c",&d)!=EOF) fprintf(f,"%c",d);
  fseek(f,x,0);
  if((f2=fopen(fn2,"rb"))==NULL) {
    textbackground(4);
    cprintf("\n\rERROR !! %s Not Found !!\n\r",fn2);
	textbackground(0);
    fcloseall();
    return blResultOK;
  }
  fseek(f2,40,0);
  for(;;){
    fscanf(f2,"%s",s);
    if((result=strrchr(s,'=')) != NULL) {
      result++;
	  sscanf(result, "%lX", &dwTemp);
      bData=(BYTE) dwTemp;
      fprintf(f,"%c",bData);
      continue;
    }
    if((result=strrchr(s,'[')) != NULL) break;
  }
  fcloseall();
  cprintf(" ... OK ... \n");
  return blResultOK=TRUE;
}

BOOL blOBWSN(char *fn)
{
  FILE *f1;
  char s[50];
  int  k;
  WORD m;


  if((f1=fopen(fn,"r"))==NULL) {
    textbackground(4);
    cprintf("\n\r ERROR !! %s Not Found !! \n\r",fn);
	textbackground(0);
    return FALSE;
  }
  fgets(s,50,f1);
  if(strlen(s)!=10){
    printstr(1,12," Serial Number Length Error !! ",0);
    return FALSE;
  }
  for(m=0; m<strlen(s); m++) s[m]=toupper(s[m]);
  if((s[0]=='2') && (s[1]=='C') && (s[2]=='P')){
    //check year code
    if((s[3]=='5') || (s[3]=='6') || (s[3]=='7') || (s[3]=='8') || (s[3]=='9')){
      //check date code
      if(s[4]=='0'){
	if((s[5]=='1') || (s[5]=='2') || (s[5]=='3') || (s[5]=='4') || (s[5]=='5') ||
	   (s[5]=='6') || (s[5]=='7') || (s[5]=='8') || (s[5]=='9')){
	  for(k=6; k<10; k++){
	    if((s[k]=='A') || (s[k]=='E') || (s[k]=='I') || (s[k]=='O') || (s[k]=='U')){
	      printstr(1,12," Error !! Serial Number Has  A, E, I, O, U  !! ",0);
	      return FALSE;
	    }
	  }
	} else{
	  printstr(1,12," Week Number = 00 !! ",0);
	  return FALSE;
	}
      } else if((s[4]=='1') || (s[4]=='2') || (s[4]=='3') || (s[4]=='4')){
	if((s[5]=='0') || (s[5]=='1') || (s[5]=='2') || (s[5]=='3') || (s[5]=='4') ||
	   (s[5]=='5') || (s[5]=='6') || (s[5]=='7') || (s[5]=='8') || (s[5]=='9')){
	  for(k=6; k<10; k++){
	    if((s[k]=='A') || (s[k]=='E') || (s[k]=='I') || (s[k]=='O') || (s[k]=='U')){
	      printstr(1,12," Error !! Serial Number Has  A, E, I, O, U  !! ",0);
	      return FALSE;
	    }
	  }
	} else{
	  printstr(1,12," Week Number Error !! ",0);
	  return FALSE;
	}
      } else if(s[4]=='5'){
	if((s[5]=='0') || (s[5]=='1') || (s[5]=='2')){
	  //check serial number
	  for(k=6; k<10; k++){
	    if((s[k]=='A') || (s[k]=='E') || (s[k]=='I') || (s[k]=='O') || (s[k]=='U')){
	      printstr(1,12," Error !! Serial Number Has  A, E, I, O, U  !! ",0);
	      return FALSE;
	    }
	  }
	} else{
	  printstr(1,12," Week Number > 52 !! ",0);
	  return FALSE;
	}
      } else{
	printstr(1,12," Week Number Error !! ",0);
	return FALSE;
      }
    } else{
      printstr(1,12," Year Number Error !! ",0);
      return FALSE;
    }
  } else{
    printstr(1,12," First 3 Numbers Not 2CP !! ",0);
    return FALSE;
  }
  printstr(1,12," OBW Serial Number OK !! ",0);
  return TRUE;
}

void CP(char *fn1, char *fn2)
{
  FILE  *f;
  FILE  *f1;
  char  s[260]="";
  int   i=0;
  BYTE  ch;

  if((f=fopen(fn1,"r+"))==NULL){
    printf("\n ... ERROR !! ... %s Not Found ... !! ", fn1);
    End(nErrorLevel);
  } else{
    if((f1=fopen(fn2,"w+"))==NULL){
      printf("\n ... ERROR !! ... %s Can't Open ... !! ", fn2);
      End(nErrorLevel);
    } else{
      while(!feof(f)) {
	ch=fgetc(f);
	if(ch==0xFF || ch==0xFE || ch==0x00) continue;
	else if(ch==0x09){
	  for(int j=0; j<5; j++){
	    s[i]=' ';
	    i++;
	  }
	  continue;
	} else if(ch==0x0D || ch=='\n'){
	  s[i]='\n';
	  fprintf(f1, "%s", s);
	  for(i=0; i<260; i++) s[i]='\0';
	  i=0;
	  continue;
	}
	s[i]=ch;
	i++;
      }
      fclose(f1);
      fclose(f);
    }
    fclose(f);
  }
}
BOOL blCreateRandom(const unsigned int iLength)
{
  if(iLength == 0) return FALSE;
  const unsigned int RADN_RANGE = 255;
  BYTE cBuf = 0x00;
  BYTE *random = new BYTE[iLength];
  BYTE *rBuf = new BYTE[iLength*2];
  memset(random, sizeof(random), 0x00);
  memset(rBuf, sizeof(rBuf), 0x00);
  //delay(600);
  srand((unsigned)time(NULL));
  for(unsigned int i = 0 ; i < iLength ; i++){
    Sleep(10);
    random[i] = rand() % RADN_RANGE;
    cBuf = random[i];
    cBuf >>= 4;
    if((cBuf += 0x30) > 0x39) cBuf += 0x07;
    rBuf[i*2] = cBuf;
    cBuf = random[i];
    cBuf &= 0x0F;
    if((cBuf += 0x30) > 0x39) cBuf += 0x07;
    rBuf[(i*2)+1] = cBuf;
    Sleep (10);
  }
  printf(" Random Length = %d\n", iLength);
  printf(" Random Data = ");
  rBuf[iLength*2] = '\0';
  char szTbuf[255]={0};
  sprintf(szTbuf,"%s",rBuf);
  if (blow==true)
  {
	  for(int k=0;k<strlen(szTbuf);k++) szTbuf[k]=tolower(szTbuf[k]);
  }
  printf("%s", szTbuf);
  delete [] rBuf;
  delete [] random;
  return TRUE;
}

//BOOL blOutPutStr(char *bCharacter,int iColor)
//{
//	char szTemp[10][8];
//	int i,j,k;
// //   for(i=0;i<10;i++)
//	//{
//	//	for(k=0;k<strlen(bCharacter);k++)
//	//	{
//	//		if(bCharacter[k]=='a')
//	//			            memcpy(&szTemp,&bCharacterA,80);
//	//		else if(bCharacter[k]=='b')
//	//			            memcpy(&szTemp,&bCharacterB,80);
// //           else if(bCharacter[k]=='c')
//	//			            memcpy(&szTemp,&bCharacterC,80);
//	//		else if(bCharacter[k]=='d')
//	//			            memcpy(&szTemp,&bCharacterD,80);
// //           else if(bCharacter[k]=='e')
//	//			            memcpy(&szTemp,&bCharacterE,80);
// //           else if(bCharacter[k]=='f')
//	//			            memcpy(&szTemp,&bCharacterF,80);
//	//		if(bCharacter[k]=='A')
//	//			            memcpy(&szTemp,&bCharacterA,80);
//	//		else if(bCharacter[k]=='B')
//	//			            memcpy(&szTemp,&bCharacterB,80);
// //           else if(bCharacter[k]=='C')
//	//			            memcpy(&szTemp,&bCharacterC,80);
//	//		else if(bCharacter[k]=='D')
//	//			            memcpy(&szTemp,&bCharacterD,80);
// //           else if(bCharacter[k]=='E')
//	//			            memcpy(&szTemp,&bCharacterE,80);
// //           else if(bCharacter[k]=='F')
//	//			            memcpy(&szTemp,&bCharacterF,80);
//	//		else if(bCharacter[k]=='1')
//	//						memcpy(&szTemp,&bCharacter1,80);
//	//		else if(bCharacter[k]=='2')
//	//						memcpy(&szTemp,&bCharacter2,80);
//	//		else if(bCharacter[k]=='3')
//	//						memcpy(&szTemp,&bCharacter3,80);
//	//		else if(bCharacter[k]=='4')
//	//						memcpy(&szTemp,&bCharacter4,80);
//	//		else if(bCharacter[k]=='5')
//	//						memcpy(&szTemp,&bCharacter5,80);
//	//		else if(bCharacter[k]=='6')
//	//						memcpy(&szTemp,&bCharacter6,80);
//	//		else if(bCharacter[k]=='7')
//	//						memcpy(&szTemp,&bCharacter7,80);
//	//		else if(bCharacter[k]=='8')
//	//						memcpy(&szTemp,&bCharacter8,80);
//	//		else if(bCharacter[k]=='9')
//	//						memcpy(&szTemp,&bCharacter9,80);
//	//		else if(bCharacter[k]=='0')
//	//						memcpy(&szTemp,&bCharacter0,80);
//	//		else
//	//		{
//	//			printf("Date in file is not HEX or DEC");
//	//			return FALSE;
//	//		}
//	//	}
//	//}
//    for(i=0;i<10;i++)
//	{
//		for(k=0;k<strlen(bCharacter);k++)
//		{
//			if(bCharacter[k]=='a')
//				            memcpy(&szTemp,&bCharacterA,80);
//			else if(bCharacter[k]=='b')
//				            memcpy(&szTemp,&bCharacterB,80);
//            else if(bCharacter[k]=='c')
//				            memcpy(&szTemp,&bCharacterC,80);
//			else if(bCharacter[k]=='d')
//				            memcpy(&szTemp,&bCharacterD,80);
//            else if(bCharacter[k]=='e')
//				            memcpy(&szTemp,&bCharacterE,80);
//            else if(bCharacter[k]=='f')
//				            memcpy(&szTemp,&bCharacterF,80);
//			else if(bCharacter[k]=='A')
//				            memcpy(&szTemp,&bCharacterA,80);
//			else if(bCharacter[k]=='B')
//				            memcpy(&szTemp,&bCharacterB,80);
//            else if(bCharacter[k]=='C')
//				            memcpy(&szTemp,&bCharacterC,80);
//			else if(bCharacter[k]=='D')
//				            memcpy(&szTemp,&bCharacterD,80);
//            else if(bCharacter[k]=='E')
//				            memcpy(&szTemp,&bCharacterE,80);
//            else if(bCharacter[k]=='F')
//				            memcpy(&szTemp,&bCharacterF,80);
//			else if(bCharacter[k]=='1')
//							memcpy(&szTemp,&bCharacter1,80);
//			else if(bCharacter[k]=='2')
//							memcpy(&szTemp,&bCharacter2,80);
//			else if(bCharacter[k]=='3')
//							memcpy(&szTemp,&bCharacter3,80);
//			else if(bCharacter[k]=='4')
//							memcpy(&szTemp,&bCharacter4,80);
//			else if(bCharacter[k]=='5')
//							memcpy(&szTemp,&bCharacter5,80);
//			else if(bCharacter[k]=='6')
//							memcpy(&szTemp,&bCharacter6,80);
//			else if(bCharacter[k]=='7')
//							memcpy(&szTemp,&bCharacter7,80);
//			else if(bCharacter[k]=='8')
//							memcpy(&szTemp,&bCharacter8,80);
//			else if(bCharacter[k]=='9')
//							memcpy(&szTemp,&bCharacter9,80);
//			else if(bCharacter[k]=='0')
//							memcpy(&szTemp,&bCharacter0,80);
//			else
//			{
//				//if(!blNoLogo) Logo();
//				int y = wherey();
//				gotoxy(1, y);
//				printf("Date in file is not HEX or DEC.                         ");
//				return FALSE;
//			}
//
//
//           for(j=0;j<8;j++)
//			{	
//				if(szTemp[i][j]==1)
//					textbackground(iColor); //设置背景为白色
//				else
//					textbackground( 0x00);		 //设置背景为黑色
//				printf(" ");
//			}
//			textbackground( 0x00);
//			printf(" ");
//		}
//		printf("\n");
//	}
//	return TRUE;
//}
//
//BOOL blDisplayBigWord(const char *lpfilename)
//{
//  FILE *lpfileBigWord = NULL;
//  BOOL blOdd = FALSE;
//  char chBigWord[9]={0};
//  char chBW;
//  int nDisplayBigWord = 0;
//
//  unsigned int nCharX = 0,
//	       nIndexX = 40;
//
//  lpfileBigWord = fopen(lpfilename, "r");
//  if(lpfileBigWord == NULL){
//  cprintf("open %s ERROR...\n\r", lpfilename);
//    //fclose(lpfileBigWord);
//    return FALSE;
//  }
//
//  while((chBW = fgetc(lpfileBigWord)) != EOF){
//    if((chBW >= 0x30 && chBW <= 0x39)||
//       (chBW >= 0x41 && chBW <= 0x5A)||
//       (chBW >= 0x61 && chBW <= 0x7a)){
//      chBigWord[nCharX] = chBW;
//      nCharX++;
//      if(nCharX > 8){
//	fclose(lpfileBigWord);
//	printf("Data out of range");
//	End(nErrorLevel);
//      }
//    }
//  }
//  if(nCharX == 0){
//    fclose(lpfileBigWord);
//    End(nErrorLevel); // if file is empty, exit
//  }
//
//  for(int i = 0 ; i <= nCharX-1 ; i++){
//    if(!blOdd){
//      nIndexX -= 4;
//      blOdd = TRUE;
//    }
//    else{
//      nIndexX -= 5;
//      blOdd = FALSE;
//    }
//  }
//  chBigWord[8]='\0';
//	if(blOutPutStr(chBigWord,0x0F))
//		return true;
//	else 
//		return false;
////  for(int s = 0 ; s < nCharX ; s++){
////    if((chBigWord[s] >= 0x30 && chBigWord[s] <= 0x39)){
////      nDisplayBigWord = chBigWord[s] - 0x30;
////      asus.DisplayBigWord(nIndexX, 12, nDisplayBigWord);
////      nIndexX += 9;
////      continue;
////    }else if((chBigWord[s] >= 0x41 && chBigWord[s] <= 0x5A)){
////      nDisplayBigWord = chBigWord[s] - 0x37;
////      if(nDisplayBigWord >= 16) asus.DisplayBigWord(nIndexX, 12, 18);
////      else asus.DisplayBigWord(nIndexX, 12, nDisplayBigWord);
////      nIndexX += 9;
////      continue;
////    }else if((chBigWord[s] >= 0x61 && chBigWord[s] <= 0x7A)){
////      nDisplayBigWord = chBigWord[s] - 0x57;
////      if(nDisplayBigWord >= 16) asus.DisplayBigWord(nIndexX, 12, 18);
////      else asus.DisplayBigWord(nIndexX, 12, nDisplayBigWord);
////      nIndexX += 9;
////      continue;
////    }
////  }
//  fclose(lpfileBigWord);
//  return TRUE;
//}
//
//

BOOL blCopyData(char str4[],char str5[],char s_File[],char t_File[])
{
  FILE *fs,*ft;
  char s1[80*40]="\0";
  char d[80]="\0";
  char ch1;
  BOOL blResultOK=FALSE;
  BOOL blMatch=FALSE;

  textcolor(15);
  if((fs=fopen(s_File,"r"))==NULL){
    textbackground(4);
    cprintf("\n\rERROR !! Can't Open %s !!\n\r",s_File);
	textbackground(0);
    fcloseall();
    return blResultOK;
  }

  int k=0,i=0,j=0;
  if(strlen(str4)>0){

    while(((ch1=getc(fs))!=EOF)){
      if(ch1==str4[i]){
	i++;
	if(i==(strlen(str4))){
	  blMatch=TRUE;
	  j++;
	}
      }
      else if(blMatch){
	if((ch1!='\0') && (ch1!='\n')){
	  d[k]=ch1;
	  k++;
	}
	else{
	  blMatch=FALSE;
	  break;
	}
      }
      else i=0;
    }
    if(j==0){
      printf("String Not Found!!\n");
      return blResultOK;
    }
  }
  fclose(fs);

  if((ft=fopen(t_File,"rb+"))==NULL){
    textbackground(4);
    cprintf("\n\rERROR !! Can't Open %s !!\n\r",t_File);
	textbackground(0);
    fcloseall();
    return blResultOK;
  }

  if(strlen(d)>0){

    char ch2;
    i=0; k=0;j=0;
    char tmpc;

    while((tmpc=fgetc(ft))!=EOF) 
	{
		if(!blMatch)
	    {
			if(tmpc == str5[j])
			{
				j++;
				if(j == (strlen(str5)))
				{
					blMatch=TRUE;
					j=0;
					tmpc=fgetc(ft);
				}
			} 
			else j=0;
		} 
		else
		{
			s1[j]=tmpc;
			j++;
		}
	}
    if(j==0){
      printf("Copy Fail!!\nString Not Found!!\n");
      return blResultOK;
    }
    j=0;
    blMatch=FALSE;
    fseek(ft,0,SEEK_SET);
    while((tmpc=fgetc(ft))!=EOF) {
       if(!blMatch){
	 if(tmpc == str5[j]){
	   j++;
	   if(j == (strlen(str5))){
	     blMatch=TRUE;
	     j=0;
	   }
	 } else j=0;
       } else {
	 fseek(ft,-1,SEEK_CUR);

	 if(fputs(d,ft)==EOF){
	   printf("Copy Fail\n");
	   break;
	 }

	for(int i=0;i<(strlen(s1)-strlen(str5));i++)
	{
		s1[i]=s1[i+strlen(str5)];
	}
	s1[strlen(s1)-strlen(str5)]='\0';

	 if(fputs(s1,ft)==EOF){
	   printf("Copy Fail\n");
	   break;
	 }
	 break;
       }
    }
    fcloseall();
    blResultOK=TRUE;
  }
  return blResultOK;
}
int cXtoD(char T[],int num )
{
  if(T[num]-'0'>=17&&T[num]-'0'<=22)
    return T[num]-'0'-7;
  else if(T[num]-'0'>=49&&T[num]-'0'<=54)
    return T[num]-'0'-39;
  else if(T[num]-'0'>=0&&T[num]-'0'<=9)
    return T[num]-'0';
  else
  {
    cprintf("ERROR !! The String is Not Hex !!");
    End(nErrorLevel);
  }
  return 0;
}

BOOL blTransferHex2Dec(char *file)
{
  BOOL blReturn = FALSE;
  char s[100];

  FILE *f;
	if((f=fopen(file ,"r+"))!=NULL)
	{
	  fscanf(f, "%s", s);
	  fclose(f);
	  cprintf("Value in file = %s\n",s);
	  char szTempi[10],szTemp1[4096];
	  szTemp1[0]='\0';
	  for(int i1=0;i1<strlen(s);i1++)
	  {
	    itoa(cXtoD(s,i1),szTempi,2);
	    int iTz=4-strlen(szTempi);
	    for(int iZn=0;iZn<iTz;iZn++)
	    {
	      char szZ[2]="0";
	      strcat(szTemp1,szZ);
	    }
	    strcat(szTemp1,szTempi);
	  }
	  //cprintf("%s\n",szTemp1);
	  char szTemp2[4096],szTemp3[4096];
	  szTemp2[0]=szTemp1[0];
	  szTemp2[1]='\0';
	  int j2=strlen(szTemp1);
	  for(int i2=1;i2<j2;i2++)
	  {
	    int iTemp1=0,iTemp2=0,i4=0;
	    for(i4=0;i4<strlen(szTemp2);i4++)
	    {
	      if(iTemp1>=10)
	      {
		    iTemp1=(cXtoD(szTemp2,i4))*2+1;
		    if(iTemp1>=10)
		      szTemp2[i4]=iTemp1-10+'0';
		    else
		      szTemp2[i4]=iTemp1+'0';
	      }
	      else
	      {
		    iTemp1=cXtoD(szTemp2,i4)*2;
		    if(iTemp1>=10)
		      szTemp2[i4]=iTemp1-10+'0';
		    else
		      szTemp2[i4]=iTemp1+'0';
	      }
	    }
	    if(iTemp1>=10)
	    {
	      szTemp2[i4]=1+'0';
	      szTemp2[i4+1]='\0';
	    }
	    else
	      szTemp2[i4]='\0';

	    iTemp2=cXtoD(szTemp2,0)+cXtoD(szTemp1,i2);
	    for(int i5=0;i5<strlen(szTemp2);i5++)
	    {
	      if(iTemp2>=10)
	      {
		szTemp2[i5]=iTemp2-10+'0';
		iTemp2=cXtoD(szTemp2,i5+1)+1;
	      }
	      else
	      {
			szTemp2[i5]=iTemp2+'0';
			break;
		  }
		}
		if(iTemp2>=10)
		{
		  szTemp2[strlen(szTemp2)]=1+'0';
		  szTemp2[strlen(szTemp2)+1]='\0';
		}
		  else
			szTemp2[strlen(szTemp2)]='\0';
		}
		for(int i3=0;i3<strlen(szTemp2);i3++)
		{
			szTemp3[i3]=szTemp2[strlen(szTemp2)-i3-1];
			szTemp3[i3+1]='\0';
		}
				  cprintf("\n String = %s  -->  Dec. Value =",s);
				  printf("%s\n",szTemp3);
	   cprintf("\r");
				  //fprintf(ff,"%s\n",szTemp3);
	  blReturn=TRUE;
	}
	else cprintf("open %s ERROR...\n\r", file);
	return blReturn;
}

BOOL blCheckString(char *szFile, char *szValue)
{
  BOOL blReturn = FALSE;
  FILE *f3;
  char sINI1[80]="";
      char  s1[260]="", s4[260]="";

      if((f3=fopen(szFile,"r"))==NULL){
	cprintf("\n ERROR !! %s Not Found !!\n\r",szFile);
	fcloseall();
	End(nErrorLevel);
      }
      if(blTransfer){
	sprintf(sINI1, "III.iii");
	CP(szFile, sINI1);
	fclose(f3);
	if((f3=fopen("III.iii","r"))==NULL){
	  cprintf("\n ... ERROR !! ... III.iii Not Found !! ... \n\r");
	  fcloseall();
	  End(nErrorLevel);
	}
      }
      strcpy(str2, szValue);
      if(blUseStartLine && blUseEndLine && (dwStartLine==dwStartLine))
	for(int k=0;k<dwStartLine+1;k++) fgets(s1,260,f3);
      else fgets(s1,260,f3);
      for(int k=0;k<strlen(s1);k++){
	s1[k]=toupper(s1[k]);
	str2[k]=toupper(str2[k]);
      }
      if(strlen(str2)==0) ReadMe();
      int k=0;
      for(int j=dwStartAddress;j<=dwEndAddress;j++){
	s4[k]=s1[j];
	k++;
	if(j==dwEndAddress+1) s4[k]='\0';
      }
      if(stricmp(s4,str2)==0){
	printf("\n  Find Data = %s",s4);
	printf("\n Check Data = %s\n",str2);
	cprintf("\n Compare OK !!\n\r");
	blReturn = TRUE;
      }
      else{
	printf("\n  Find Data = %s",s4);
	printf("\n Check Data = %s\n",str2);
	cprintf("\n Compare Error !!\n\r");
	fcloseall();
	End(nErrorLevel);
      }
   return blReturn;
}