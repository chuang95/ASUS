#include <stdio.h>
#include <stdlib.h>
#include <dir.h>
#include "PT.h"
#include "Extern.h"

Boolean blCmpData(char str[],char s_File[],char t_File[])
{
  FILE *fs,*ft;
  char s1[80]="\0";
  char d[80]="\0";
  char ch1;
  Boolean blResultOK=FALSE;
  Boolean blMatch=FALSE;

  textcolor(15);
  if((fs=fopen(s_File,"r"))==NULL){
    textbackground(4);
    cprintf("\n\rERROR !! Can't Open %s !!\n\r",s_File);
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
Boolean blCopyData(char str4[],char str5[],char s_File[],char t_File[])
{
  FILE *fs,*ft;
  char s1[80*40]="\0";
  char d[80]="\0";
  char ch1;
  Boolean blResultOK=FALSE;
  Boolean blMatch=FALSE;

  textcolor(15);
  if((fs=fopen(s_File,"r"))==NULL){
    textbackground(4);
    cprintf("\n\rERROR !! Can't Open %s !!\n\r",s_File);
    fcloseall();
    return blResultOK;
  }

  int k=0,i=0,j=0;
  if(strlen(str4)>1){

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
    fcloseall();
    return blResultOK;
  }

  if(strlen(d)>0){

    char ch2;
    i=0; k=0;j=0;
    char tmpc;

    while((tmpc=fgetc(ft))!=EOF) {
       if(!blMatch){
	 if(tmpc == str5[j]){
	   j++;
	   if(j == (strlen(str5))){
	     blMatch=TRUE;
	     j=0;
	     tmpc=fgetc(ft);
	   }
	 } else j=0;
       } else {
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
	 for(int icp=0;icp<(strlen(s1)-strlen(str5));icp++)
	 {
	   s1[icp]=s1[i+strlen(str5)];
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

Boolean blCheckLines (const char *pfile)
{
  unsigned int nCountLine = 1 , nCountSpaceLine = 0;
  unsigned int nSpaceLineIndex[500] = {0};
  unsigned int nNewLine = 0;
  unsigned int nEOF = 0;

  Boolean blFirstWord = TRUE;
  Boolean blOK = TRUE;
  char chNewLine = '\n';
  FILE *fptr;
  char ch1;

  printf ("Check File : %s\n" , pfile);
  fptr = fopen (pfile , "r+");

  if (fptr == NULL) {

    cprintf ("File Not Found...\n\r" , pfile);
    fclose (fptr);
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

Boolean blWork(void)
{
  return TRUE;
}

uLong dwTransferNowDateTime2GMT(void)
{
  struct date d;
  struct time t;
  uLong dwNowDate, dwNowTime_sec, dwGMT;

  // Calcute Time
  d.da_year=pega.BCD2Hex(RTC.Read(0x32))*100+pega.BCD2Hex(RTC.Read(0x09));
  d.da_mon=pega.BCD2Hex(RTC.Read(0x08));
  d.da_day=pega.BCD2Hex(RTC.Read(0x07));
  t.ti_hour=pega.BCD2Hex(RTC.Read(0x04));
  t.ti_min=pega.BCD2Hex(RTC.Read(0x02));
  t.ti_sec=pega.BCD2Hex(RTC.Read(0x00));
  dwNowDate=pega.CalculateDate(d.da_year, d.da_mon, d.da_day);
  dwNowTime_sec=t.ti_hour*3600L+t.ti_min*60+t.ti_sec;
  dwGMT=dwNowDate*86400L+dwNowTime_sec;

  return dwGMT;
}

uLong dwGetFileSize(char *fn)
{
  int handle;
  uLong l;

  if((handle=open(fn, O_RDONLY))==-1) {
    cprintf("File not found ...\n\r", fn);
    End(nErrorLevel);
  }

  l=filelength(handle);

  close(handle);

  return l;

}

void DisplayTxtFile(char *filename, int x, int y, uChar attr)
{
  FILE *f;
  int i;
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
      pega.PrintCh(x++,y,c,attr,1);
    }
    textattr(0x07);
    fclose(f);
  }
}

Boolean blFileCompare(char *fn1, char *fn2, Boolean blignore)
{
  FILE *tf1, *tf2, *f5, *f6;
  int f1, f2, k, kk;
  long fs1, fs2;
  char far *keybuffer=(char far*) 0x00400017;
  char s5[100],s6[100],s7[100]="\0",s8[100]="\0",s9[100]="\0",s10[100]="\0";
  uLong i,j;
  uLong ReadLength;
  uChar d1[1], d2[1];
  char buf1[ReadSize], buf2[ReadSize];

  
  int x,y;

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

    sprintf(buf, "... Compare  %s  &  %s ...", fn1, fn2);
    pega.PrintStr(1,5,buf,0,0x07);

    f1=open(fn1, O_RDONLY|O_BINARY);
    f2=open(fn2, O_RDONLY|O_BINARY);
    i=0;
    do {
      sprintf(buf,"   %ld/%ld   ",i,fs1);
      pega.PrintStr(1,7,buf,0,0x0F);
      ReadLength=ReadSize;
      if((i+ReadLength)>fs1) ReadLength=fs1-i;
      read(f1,buf1,ReadLength);
      read(f2,buf2,ReadLength);
      for(j=0; j<ReadLength; j++) {
	if(buf1[j]!=buf2[j]) {
	  sprintf(buf, "... File Compare ERROR at Byte %ld ...", i+j+1);
	  pega.PrintStr(1,9,buf,0,0x4F);
	  close(f1);
	  close(f2);
	  return FALSE;
	}
	if((*keybuffer&0x02)==0x02) {
	  pega.PrintStr(1,9,"... User Break ...",0,0x4F);
	  close(f1);
	  close(f2);
	  return FALSE;
	}
      }
      i+=ReadLength;
    } while(i<fs1);
    close(f1);
    close(f2);
    sprintf(buf,"   %ld/%ld   ",i,fs1);
    pega.PrintStr(1,7,buf,0,0x0F);
    pega.PrintStr(1,9,"... File Compare OK ...",0,0x1F);
    return TRUE;
  }

  // compare partial file context
  if(blUseAddress && blUseLine==FALSE) {
    cprintf("\n\r");
    if(dwStartAddress>dwEndAddress) {
      cprintf("Byte Range ERROR !! Start Byte=%ld > End Byte=%ld !!\n\r", dwStartAddress+1, dwEndAddress+1);
      return FALSE;
    }
    // cprintf("Compare Byte %ld to %ld\n\r", dwStartAddress+1, ((dwEndAddress<(fs1-1)) ? dwEndAddress : (fs1-1))+1); // add by KC
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
      for(k=dwStartAddress;k<=dwEndAddress;k++){
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
      }
      else{
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

    //while(i<=dwEndAddress && i<=(fs1-1)) { // add by KC
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
    if(dwStartLine>dwEndLine)  {
      cprintf("Line range set ERROR, start line=%ld & end line=%ld\n\r", dwStartLine+1, dwEndLine+1);
      return FALSE;
    }
    if(dwEndLine==0xFFFFFFFFl) cprintf("Compare line %ld to end\n\r", dwStartLine+1);
    else cprintf("Compare line %ld to %ld\n\r", dwStartLine+1, dwEndLine+1);
    tf1=fopen(fn1, "r+");
    tf2=fopen(fn2, "r+");
    i=0;
    int k = 0, l = 0;
    while(!feof(tf1)){
      if(i>dwEndLine) break;
      fgets(buf1,1024,tf1);
      fgets(buf2,1024,tf2);
      if(i>=dwStartLine && i<=dwEndLine) {
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
	if(strcmp(buf1, buf2)) {
	  cprintf("\nCompare ERROR at line %ld\n\r", i+1);
	  cprintf("\n%s --> ",fn1);
	  cprintf("\n%s\r", buf1);
	  cprintf("\n%s --> ",fn2);
	  cprintf("%s\n\r", buf2);
	  fclose(tf1);
	  fclose(tf2);
	  return FALSE;
	}
      }
      memset(buf1, 0x00, 1024);
      memset(buf2, 0x00, 1024);
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

Boolean blFileCheckSum(char *fn1, uInt wUserCheckSum)
{
  FILE *tf1, *tf2, *ff;
  int f1, f2, k1, k2;
  long fs1, fs2;
  uLong i,j;
  uLong ReadLength;
  uChar d1[1], d2[1];
  int x,y;
  uInt wCheckSum=0;
  char Code[36]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D',
		 'E','F','G','H','I','J','K','L','M','N','O','P','Q','R',
		 'S','T','U','V','W','X','Y','Z'};
  char s[100]="\0";
  BYTE buf3[ReadSize];


  if((f1=open(fn1, O_RDONLY))==-1) {
    cprintf("Open %s file error.\n\r", fn1);
    return FALSE;
  } else {
    fs1=filelength(f1);
    close(f1);
  }

  // compare all file context
  if(blUseAddress==FALSE && blUseLine==FALSE) {
    sprintf(buf, "... Compute checksum of %s ...", fn1);
    pega.PrintStr(1,5,buf,0,0x07);

    f1=open(fn1, O_RDONLY|O_BINARY);
    i=0;
    do {
      sprintf(buf,"   %ld/%ld   ",i,fs1);
      pega.PrintStr(1,7,buf,0,0x0F);
      ReadLength=ReadSize;
      if((i+ReadLength)>fs1) ReadLength=fs1-i;
      read(f1,buf3,ReadLength);
      for(j=0; j<ReadLength; j++) wCheckSum+=buf3[j];
      i+=ReadLength;
    } while(i<fs1);
    close(f1);
	//printf("%d",bldiv);
    if(blDivideBy36) {
      if((ff=fopen(fn1, "r"))==NULL){
	cprintf("\nERROR !! Can't Open %s !!\n\r",fn1);
	fcloseall();
	return FALSE;
      }
      wCheckSum=0;
      fgets(s,100,ff);
	  if(blL2u)
	  {
	    for(int iTP1=0;iTP1<strlen(s);iTP1++)
	    {
		  s[iTP1]=toupper(s[iTP1]);
	    }
	  }
      for(k1=0; k1<strlen(s); k1++) {
	for(k2=0; k2<=35; k2++) {
	  if(s[k1]==Code[k2]) break;
	}
	wCheckSum+=k2;
      }
      wCheckSum=wCheckSum%36;
      gotoxy(35,12); cprintf("CheckSum=");
      printf("%c", Code[wCheckSum]);
      if(wCheckSum==wUserCheckSum) return TRUE;
      else return FALSE;

    }
	else if(bldiv) {
      if((ff=fopen(fn1, "r"))==NULL){
	cprintf("\nERROR !! Can't Open %s !!\n\r",fn1);
	fcloseall();
	return FALSE;
      }
      wCheckSum=0;
      fgets(s,100,ff);
	  if(blL2u)
	  {
		for(int iTP2=0;iTP2<strlen(s);iTP2++)
	    {
		  s[iTP2]=toupper(s[iTP2]);
	    }
	  }
	  else
	  {
		int iS=0;
		for(int iTP2=0;iTP2<strlen(s);iTP2++)
	    {
		  s[iTP2]=toupper(s[iTP2]);
	    }
	    for(int iTP3=0;iTP3<strlen(s);iTP3++)
	    {
		  for(int iTP4=0;iTP4<strlen(s);iTP4++)
		  {
		    if(s[iTP3]==Code[iTP4])
			{
		      if(iTP4<9)
			  {
				s[iS]=s[iTP3];
				iS++;
		      }
		    }
	      }
	    }
		s[iS]='\0';
	  }
	  printf("%s",s);
      for(k1=0; k1<strlen(s); k1++) {
	for(k2=0; k2<=35; k2++) {
	  if(s[k1]==Code[k2]) break;
	}
	wCheckSum+=k2;
      }
      wCheckSum=wCheckSum%idiv;
      gotoxy(35,12); cprintf("CheckSum=");
      printf("%c", Code[wCheckSum]);
      if(wCheckSum==wUserCheckSum) return TRUE;
      else return FALSE;

    } 
	else {
      sprintf(buf,"   CheckSum=%04X   ",wCheckSum);
      pega.PrintStr(1,7,buf,0,0x0F);
      if(wCheckSum==wUserCheckSum) return TRUE;
      else return FALSE;
    }
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
      fscanf(tf1, "%s\n", buf3);
      for(j=0; j<strlen(buf3); j++) wCheckSum+=buf3[j];
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
Boolean Process_ini_File(int DelBit,int Chk_Tms,int FileNumber,char **iniFile,char *Prmpt)
{
  FILE *finiFile,*fBatchFile,*fBarcode,*fProFile,*fTxtFile,*fCopyFile,*fChkCode;
  int  i,ii,j,jj=0,CompareOK,TotalFileCount,BatchFileCount,ModFileCount,k,kk,
       Match,Mark,CountLine,m,mm,n;
  char *ptr,s[100],iniBarCode[100],NBBarCode[100],ss[100],ModMatch,ss2[100],
       BatchMatch,CH='\0',buffer1[20],buffer2[20],buffer3[20],buffer4[20],
       buffer5[20],ModelName[100]="\0",New_NBBarCode[100],ChkCode[100],
       New_ChkCode[100],buffer6[20],s1[100]="\0",s2[100]="\0";
  Boolean blResultOK=FALSE;

  if(FileNumber==0)
    return blResultOK;
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
    pega.CursorOn();
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
      fclose(fChkCode);
      if((fChkCode=fopen(buffer6,"w"))==NULL) {
	cprintf("\n ERROR !! Can't Open %s !!\n\r",buffer6);
	fcloseall();
	return blResultOK;
      }
      if(strlen(Prmpt)!=0) printf(" %s again : ",Prmpt);
      else printf(" Please Scan Barcode %d again : ",jj+1);
      pega.CursorOn();
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
/*	else{
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
	for(j=0;j<strlen(ss);j++)
	  ss[j]=toupper(ss[j]);
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


Boolean Process_ini_File2(int DelBit,int FileNumber,char **iniFile)
{
  FILE *finiFile,*fBatchFile,*fBarcode,*fProFile,*fTxtFile,*fCopyFile;
  int  i,ii,j,jj=0,CompareOK,TotalFileCount,BatchFileCount,ModFileCount,k,kk,
       Match,Mark,CountLine,m,mm,n;
  char *ptr,s[100],iniBarCode[100],NBBarCode[100],ss[100],ModMatch,ss2[100],
       BatchMatch,CH='\0',buffer1[20],buffer2[20],buffer3[20],buffer4[20],
       buffer5[20],ModelName[100]="\0",New_NBBarCode[100],s1[100]="\0";
  Boolean blResultOK=FALSE;

  if(FileNumber==0)
    return blResultOK;
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
	for(j=0;j<strlen(ss);j++)
	  ss[j]=toupper(ss[j]);
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
Boolean CheckChar(char Filename[], int ReadBit, char ch)
{
  FILE *fFilename;
  int  ii;
  //int iN=0;
  char sin;
  char s[100]={0};
  char szTems[10]={0};
  Boolean blResultOK=FALSE;

  if((fFilename=fopen(Filename,"r"))==NULL) {
    cprintf("ERROR !! Can't Open %s !!\n\r",Filename);
    return blResultOK;
  }
				while(!feof(fFilename)) 
				{
					//fgets(szTemp1,100,ins);
					//iN++;
					sin=fgetc(fFilename);
					if(sin)
					{
						if((sin == '\n')||(sin == ' '))
						{
							//iN++;
							continue;
						}
					}
					else
					{
						printf("Get String Process Happen Error !!");
						fclose(fFilename);
						return blResultOK;
					}
					sprintf(szTems,"%c",sin);
					strcat(s,szTems);
					//printf("%s\n",szTemN[iN]);
				}

  //if(fgets(s,100,fFilename)!=NULL)
    for(ii=0;ii<strlen(s);ii++)
	{
		s[ii]=toupper(s[ii]);
	}

  ch=toupper(ch);
  if(ReadBit>strlen(s)) {
    pega.PrintStr(1,10,"ERROR !!  <bit> setting is over range !!",0,0x47);
    fclose(fFilename);
    return blResultOK;
  }
  printf("\n Bit %d = %c\n",ReadBit,s[ReadBit-1]);
  printf(" Character = %c\n",ch);
  if(s[ReadBit-1]==ch) blResultOK=TRUE;
  else pega.PrintStr(1,12,"ERROR !!  No Character Matched !!",0,0x47);
  fclose(fFilename);
  return blResultOK;
}



Boolean Transfer_Barcode_Format(char *Prmpt)
{
  FILE *fBar;
  int  k;
  char BarCode1[100]="\0",BarCode2[100]="\0",New_BarCode[100]="\0";
  Boolean blResultOK=FALSE;

  if((fBar=fopen("new_bc.dat","w"))==NULL) {
    cprintf("\n ERROR !! Can't Open New_bc.dat !!\n\r");
    fcloseall();
    return blResultOK;
  }
  pega.CursorOn();
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


Boolean Set_Barcode_Environment(char DataFilename[], char iniFilename[])
{
  FILE *fDataFilename,*finiFilename,*fSetBar;
  int  ii,j,k,m=0,CompareOK,Match;
  char s[100],s1[100],NBBarCode[100],iniBarCode[100],SetBar[100],CH='\0',
       old_dir[MAXDIR],new_dir[MAXDIR];

  Boolean blResultOK=FALSE;

  if(getcurdir(0,old_dir)){
    perror("getcurdir()");
    return blResultOK;
  }
  if(chdir("\\")){
    perror("chdir()");
    return blResultOK;
  }

  if(getcurdir(0,new_dir)){
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
  m=strlen(NBBarCode);
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
  else pega.PrintStr(1,12,"ERROR !!  No Matched !!",0,0x47);
  fcloseall();
  printf("\n		       ... There Are %d Mached Setting ... \n",Match);
  return blResultOK;
}


Boolean Transfer_String(char File[],char str1[],char str2[])
{
  FILE *fFile,*ff1;
  char f1,ch1,ch2;
  int  i,j,k,count=0,match;
  Boolean blResultOK=FALSE;

  if((fFile=fopen(File,"r"))==NULL) {
    cprintf("ERROR !! Can't Open %s !!\n\r",File);
    fcloseall();
    return blResultOK;
  }
  if((ff1=fopen("update.txt","w"))==NULL) {
    cprintf("ERROR !! Can't Open %s !!\n\r",f1);
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

void CP(char *fn1, char *fn2)
{
  FILE  *f;
  FILE  *f1;
  char  s[260]="";
  int   i=0;
  uChar ch;

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


Boolean blCreateRandom(const uInt iLength)
{
  if(iLength == 0) return FALSE;
  const uInt RADN_RANGE = 255;
  BYTE cBuf = 0x00;
  BYTE *random = new BYTE[iLength];
  BYTE *rBuf = new BYTE[iLength*2];
  memset(random, sizeof(random), 0x00);
  memset(rBuf, sizeof(rBuf), 0x00);
  //delay(600);
  srand((unsigned)time(NULL));
  for(uInt i = 0 ; i < iLength ; i++){
    delay (11);
    random[i] = rand() % RADN_RANGE;
    cBuf = random[i];
    cBuf >>= 4;
    if((cBuf += 0x30) > 0x39) cBuf += 0x07;
    rBuf[i*2] = cBuf;
    cBuf = random[i];
    cBuf &= 0x0F;
    if((cBuf += 0x30) > 0x39) cBuf += 0x07;
    rBuf[(i*2)+1] = cBuf;
    delay (13);
  }
  printf(" Random Length = %d\n", iLength);
  printf(" Random Data = ");
  rBuf[iLength*2] = '\0';
  printf("%s", rBuf);
  delete [] rBuf;
  delete [] random;
  return TRUE;
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
