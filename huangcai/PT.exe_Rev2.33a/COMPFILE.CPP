#include "PT.h"
#include "Extern.h"
#include <math.h>

Boolean blCompareValueInFile(char *szFile, char *szValue)
{
  Boolean blReturn = FALSE;
  int p=0, value = 0;
  FILE *f1;
  char s[100], s3[100]="\0",szS[1024]="\0";
  char Code[36]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D',
		  'E','F','G','H','I','J','K','L','M','N','O','P','Q','R',
		  'S','T','U','V','W','X','Y','Z'};

	int m1 = 0,
	    n1 = 0,
	    sub = 0;
	Boolean blHex = FALSE;
	if((f1=fopen(szFile,"r+"))!=NULL) {
	  fgets(s,100,f1);//add by Jackson, 2003-08-15
	  //if(blmask)
	  //{
		 // int iTmask=0;
		 // iTmask=atoi(s)|imask;
		 // itoa(iTmask,s,16);
		 // printf("%s\n",s);
	  //}
	  strcpy(s3, szValue);
	  strcpy(szS,szFile);
	  for(int j=0;j<strlen(s);j++){
	    if(s[j]==' ' || s[j]=='\n'){
	      s[j]='\0';
	      break;
	    }
	    s[j]=toupper(s[j]);
	  }
		for(int i=0,jTmp=0;i<strlen(s3);i++)
		{
			if(s3[i]!='0')
			{
				jTmp=strlen(s3)-i;
				break;
			}
		}
		char szTmpv1[1024],szTmpv2[1024];
		for(int iTmp1=0;iTmp1<jTmp;iTmp1++)
		{
			szTmpv1[iTmp1]=s3[strlen(s3)-jTmp+iTmp1];
		}
		szTmpv1[iTmp1]='\0';
		strcpy(s3,szTmpv1);
		for(int ii=0,kTmp=0;ii<strlen(s);ii++)
		{
			if(s[ii]!='0')
			{
				kTmp=strlen(s)-ii;
				break;
			}
		}
		for(int iTmp2=0;iTmp2<kTmp;iTmp2++)
		{
			szTmpv2[iTmp2]=s[strlen(s)-kTmp+iTmp2];
		}
		szTmpv2[iTmp2]='\0';
		strcpy(s,szTmpv2);
	  for(j=0;j<jTmp;j++) s3[j]=toupper(s3[j]);
	  for(j=0;j<kTmp;j++){
	    for(int m=0;m<36;m++)
	      if(s[j]==Code[m]) break;
	    if(m>15){
	      textcolor(15);
	      textbackground(4);
	      cprintf("\n\r ERROR !! %s='%s' Is Not Hex Data !! ",szFile,s);
	      fcloseall();
	      End(nErrorLevel);
	    }
	    if(m > -1 && m < 16) blHex = TRUE;
	  }
	  if(blmask)
	  {
		  int iTmask=0;
		  iTmask=atoh(s)&imask;
		  itoa(iTmask,s,16);
		  printf("%s\n",s);
	  }
	  for(j=0;j<jTmp;j++){
	    for(int n=0;n<36;n++)
	      if(s3[j]==Code[n]) break;
	    if(n>15){
	      textcolor(15);
	      textbackground(4);
	      cprintf("\n\r ERROR !! '%s' Is Not Hex Data !! ",s3);
	      fcloseall();
	      End(nErrorLevel);
	    }
	    if( n > -1 && n < 16) blHex = TRUE;
	  }
	  if(kTmp==jTmp){
	    for(j=0;j<kTmp;j++){
	      for(int m=0;m<36;m++)
		if(s[j]==Code[m]) break;
	      for(int n=0;n<36;n++)
		if(s3[j]==Code[n]) break;
	      if(blDiff)
	      {
		if(blHex){
		  m1 = atoh(s); n1 = atoh(s3);
		}else{
		  m1 = atoi(s); n1 = atoi(s3);
		}
		sub = abs(m1-n1);
		if(sub > (int) nDiffValue){
		  value = 2;
		  break;
		}else if(sub == (int) nDiffValue){
		  value = 1;
		  break;
		}else if(sub < (int) nDiffValue){
		  value = 0;
		  break;
		}
	      }else{
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
	  else if(kTmp>jTmp){
	    if(blDiff){
	      if(blHex){
		m1 = atoh(s); n1 = atoh(s3);
	      }else{
		m1 = atoi(s); n1 = atoi(s3);
	      }
	      sub = abs(m1-n1);
	      if(sub > (int) nDiffValue) value = 2;
	      else if(sub == (int) nDiffValue) value = 1;
	      else if(sub < (int) nDiffValue) value = 0;
	    }else value=2;
	  }
	  else if(kTmp<jTmp){
	    if(blDiff){
	      if(blHex){
		m1 = atoh(s); n1 = atoh(s3);
	      }else{
		m1 = atoi(s); n1 = atoi(s3);
	      }
	      sub = abs(m1 - n1);
	      if(sub > (int) nDiffValue) value = 2;
	      else if(sub == (int) nDiffValue) value = 1;
	      else if(sub < (int) nDiffValue) value = 0;
	    }else value=0;
	  }

	  if(value==2) {
	    cprintf("value in file(%s) = %s\n\r",szS,s);
	    cprintf("value in parameter = %s\n\r",s3);
	    if(blDiff)
	      cprintf("value in Difference = %d\n\r", (int) nDiffValue);
	    textcolor(15);
	    textbackground(1);
	    if(blDiff)
	      cprintf("the Difference in %s and %s is %d > %d\n\r", s, s3,
		  sub, (int)nDiffValue);
	    else cprintf("%s > %s\n\r",s,s3);
	    fcloseall();
	    End(2);
	  }
	  if(value==1) {
	    cprintf("value in file(%s) = %s\n\r",szS,s);
	    //cprintf("value in file(%s) = %s\n\r",argv[i+2],s);
	    cprintf("value in parameter = %s\n\r",s3);
	    if(blDiff)
	      cprintf("value in Difference = %d\n\r", (int) nDiffValue);
	    textcolor(15);
	    textbackground(1);
	    if(blDiff)
	      cprintf("the Difference in %s and %s is %d = %d\n\r", s, s3,
		  sub, (int)nDiffValue);
	    else cprintf("%s = %s\n\r",s,s3);
	    fcloseall();
	    End(1);
	  }
	  if(value==0) {
	    cprintf("value in file(%s) = %s\n\r",szS,s);
	    //cprintf("value in file(%s) = %s\n\r",argv[i+2],s);
	    cprintf("value in parameter = %s\n\r",s3);
	    if(blDiff)
	      cprintf("value in Difference = %d\n\r", (int) nDiffValue);
	    textcolor(15);
	    textbackground(1);
	    if(blDiff)
	      cprintf("the Difference in %s and %s is %d < %d\n\r", s, s3,
		  sub, (int)nDiffValue);
	    else cprintf("%s < %s\n\r",s,s3);
	    fcloseall();
	    End(0);
	  }
	}
	else{
	  textcolor(15);
	  textbackground(4);
	  cprintf("\n ERROR !! Can't Open '%s' !! \n\r",szFile);
	  fcloseall();
	  End(nErrorLevel);
	}
   return blReturn;
}

Boolean blCompareValueInFile1(char *szFile, char *szValue)
{
      FILE *f1;
      char chFileValue[100] = {"\0"};
      char chFileNumber[100] = {"\0"};
      //char *pStrEnd;
      int n2e = 0, j= 0;
      float nFileValue = 0.0,
	    nCompareValue = 0.0,
	    nSubValue = 0.0;


	if((f1 = fopen(szFile, "r+")) != NULL){
	  fgets(chFileValue, 100, f1);
	  for(j ; j < 100 ; j++){
	    if(chFileValue[j] == 0x00 || chFileValue[j] == 0x20) break;
	    chFileNumber[j] = chFileValue[j];
	  }
	  for(int k = 0 ; k < strlen(chFileNumber)-1 ; k++){
	    if(chFileNumber[k] == 0x2e){
	      n2e++;
	      if(n2e > 1){
		textcolor(15);
		textbackground(4);
		cprintf("\n\r ERROR 0x2E !! %s = '%s' %d Is Not Numeral Data", szFile, chFileValue, k);
		End(nErrorLevel);
	      }
	      continue;
	    }else if(!isdigit(chFileNumber[k])){
	      textcolor(15);
	      textbackground(4);
	      cprintf("\n\r ERROR !! %s = '%s' %d Is Not Numeral Data", szFile, chFileValue, k);
	      End(nErrorLevel);
	    }
	  }
	  //nFileValue = strtod(chFileNumber, &pStrEnd);
	  nFileValue = (float) atof(chFileNumber);
	  // check input value
	  for(int a = 0 ; a < strlen(szValue) ; a++){
	    if(!isdigit(szValue[a]) && szValue[a] != 0x2e){
	      textcolor(15);
	      textbackground(4);
	      cprintf("\n\r ERROR !! The inputed %s Is Not Numeral Data", szValue);
	      End(nErrorLevel);
	    }
	  }
	  //nCompareValue = strtod(argv[i+3], &pStrEnd);
	  nCompareValue = (float) atof(szValue);
	  cprintf("Value in File(%s) = %s \n\r", szFile, chFileNumber);
	  cprintf("Value in Parameter = %4.3f \n\r", nCompareValue);
	  if(blDiff){
	    cprintf("Value in Difference %4.3f\n\r", nDiffValue);
	    nSubValue = (float) fabs(nFileValue - nCompareValue);
	    if((float)fabs(nSubValue - nDiffValue) <=0.0009){
	      textcolor(15);
	      textbackground(1);
	      cprintf("the Difference in %4.3f and %4.3f is %4.3f = %4.3f\n\r",
		nFileValue, nCompareValue, nSubValue, nDiffValue);
	      End(1);
	    }else if(nSubValue > nDiffValue){
	      textcolor(15);
	      textbackground(1);
	      cprintf("the Difference in %4.3f and %4.3f is %4.3f > %4.3f\n\r",
		nFileValue, nCompareValue, nSubValue, nDiffValue);
	      End(2);

	    }else if(nSubValue < nDiffValue){
	      textcolor(15);
	      textbackground(1);
	      cprintf("the Difference in %4.3f and %4.3f is %4.3f < %4.3f\n\r",
		nFileValue, nCompareValue, nSubValue, nDiffValue);
	      End(0);
	    }
	    fcloseall();
	  }else{
	    if(nFileValue > nCompareValue){
	      textcolor(15);
	      textbackground(1);
	      cprintf("%f > %f\n\r", nFileValue, nCompareValue);
	      End(2);
	    }
	    else if(nFileValue < nCompareValue){
	      textcolor(15);
	      textbackground(1);
	      cprintf("%f < %f\n\r", nFileValue, nCompareValue);
	      End(0);
	    }
	    else if(nFileValue == nCompareValue){
	      textcolor(15);
	      textbackground(1);
	      cprintf("%f = %f\n\r", nFileValue, nCompareValue);
	      End(1);
	    }
	    fcloseall();
	  }
	}
	else{
	  textcolor(15);
	  textbackground(4);
	  cprintf("\n ERROR !! Can't Open %s !!\n\r", szFile);
	  fcloseall();
	  End(nErrorLevel);

	}
  return FALSE;
}

Boolean blCheckString(char *szFile, char *szValue)
{
  Boolean blReturn = FALSE;
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
      k=0;
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