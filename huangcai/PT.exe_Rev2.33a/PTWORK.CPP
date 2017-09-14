#include "PT.h"
#include "Extern.h"
#include <math.h>


Boolean blTransferHex2Dec(char *file)
{
  Boolean blReturn = FALSE;
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
	    int iTemp1=0,iTemp2=0;
	    for(int i4=0;i4<strlen(szTemp2);i4++)
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

void HexCmp(char *dwValue1,char *dwValue2)
{
		for(int i=0,jTmp=0;i<strlen(dwValue1);i++)
		{
			if(dwValue1[i]!='0')
			{
				jTmp=strlen(dwValue1)-i;
				break;
			}
		}
		char szTmpv1[1024],szTmpv2[1024];
		for(int iTmp1=0;iTmp1<jTmp;iTmp1++)
		{
			szTmpv1[iTmp1]=dwValue1[strlen(dwValue1)-jTmp+iTmp1];
		}
		szTmpv1[iTmp1]='\0';
		strcpy(dwValue1,szTmpv1);
		for(int ii=0,kTmp=0;ii<strlen(dwValue2);ii++)
		{
			if(dwValue2[ii]!='0')
			{
				kTmp=strlen(dwValue2)-ii;
				break;
			}
		}
		for(int iTmp2=0;iTmp2<kTmp;iTmp2++)
		{
			szTmpv2[iTmp2]=dwValue2[strlen(dwValue2)-kTmp+iTmp2];
		}
		szTmpv2[iTmp2]='\0';
		strcpy(dwValue2,szTmpv2);
		int iS=jTmp<kTmp?jTmp:kTmp;
		int iU=jTmp>kTmp?jTmp:kTmp;
		int a=2;
		if(iS==iU)
		{
			for(int iii=0;iii<jTmp;iii++)
			{
				if((dwValue1[iii]-'0')-(dwValue2[iii]-'0')>0)
				{
					a=1;
					break;
				}				
				if((dwValue1[iii]-'0')-(dwValue2[iii]-'0')<0)
				{
					a=-1;
					break;
				}
				if((dwValue1[iii]-'0')-(dwValue2[iii]-'0')==0)
				{
					a=0;
				}
			}
		}
		char szTemp[1024];
		szTemp[0]='\0';
		char szTstr[10];
		int iTemp;
		for(int iN=iS-1,iV=iU-1,iT=0;iN>=0;iN--)
		{
			if(iS==jTmp&&jTmp!=kTmp||a==-1)
			{
				if(iT<0)
				{
					iT=/*(dwValue2[iV]-'0')*/cXtoD(dwValue2,iV)-1-cXtoD(dwValue1,iN);/*(dwValue1[iN]-'0')*/
					if(iT<0)
					{
						sprintf(szTstr,"%X",iT+16);
						strcat(szTemp,szTstr);
					}
					else
					{
						sprintf(szTstr,"%X",iT);
						strcat(szTemp,szTstr);
					}
				}
				else
				{
					iT=cXtoD(dwValue2,iV)-cXtoD(dwValue1,iN);
					if(iT<0)
					{
						sprintf(szTstr,"%X",iT+16);
						strcat(szTemp,szTstr);
					}
					else
					{
						sprintf(szTstr,"%X",iT);
						strcat(szTemp,szTstr);
					}
				}
				if(iN==0&&iV>0)
				{
					if(iT<0)
					{
						iV--;
						for(;iV>0;iV--)
						{
							if(iT<0)
							{
								iT=cXtoD(dwValue2,iV)-1;
								if(iT<0)
								{
									sprintf(szTstr,"%X",iT+16);
									strcat(szTemp,szTstr);
								}
								else
								{
									sprintf(szTstr,"%X",iT);
									strcat(szTemp,szTstr);
								}
							}
							else
							{
								sprintf(szTstr,"%X",cXtoD(dwValue2,iV));
								strcat(szTemp,szTstr);
							}
	    				}
					}
					else
						for(;iV>0;)
						{
							iV--;
							sprintf(szTstr,"%X",cXtoD(dwValue2,iV));
							strcat(szTemp,szTstr);
	    				}
				}
			}
			if(iS==kTmp&&jTmp!=kTmp||a==1)
			{
				if(iT<0)
				{
					iT=/*(dwValue1[iV]-'0')*/cXtoD(dwValue1,iV)-1-cXtoD(dwValue2,iN);/*(dwValue2[iN]-'0')*/
					if(iT<0)
					{
						sprintf(szTstr,"%X",iT+16);
						strcat(szTemp,szTstr);
					}
					else
					{
						sprintf(szTstr,"%X",iT);
						strcat(szTemp,szTstr);
					}
				}
				else
				{
					iT=cXtoD(dwValue1,iV)-cXtoD(dwValue2,iN);
					if(iT<0)
					{
						sprintf(szTstr,"%X",iT+16);
						strcat(szTemp,szTstr);
					}
					else
					{
						sprintf(szTstr,"%X",iT);
						strcat(szTemp,szTstr);
					}
				}
				if(iN==0&&iV>0)
				{
					if(iT<0)
					{
						iV--;
						for(;iV>=0;iV--)
						{
							if(iT<0)
							{
								iT=cXtoD(dwValue1,iV)-1;
								if(iT<0)
								{
									sprintf(szTstr,"%X",iT+16);
									strcat(szTemp,szTstr);
								}
								else
								{
									sprintf(szTstr,"%X",iT);
									strcat(szTemp,szTstr);
								}
							}
							else
							{
								sprintf(szTstr,"%X",cXtoD(dwValue1,iV));
								strcat(szTemp,szTstr);
							}
	    				}
					}
					else
						for(;iV>0;)
						{
							iV--;
								sprintf(szTstr,"%X",cXtoD(dwValue1,iV));
								strcat(szTemp,szTstr);
	    				}
				}
			}
		iV--;
		}
		char szTmpv3[1024];
		for(int iTmp3=0;iTmp3<strlen(szTemp);iTmp3++)
		{
			szTmpv3[iTmp3]=szTemp[strlen(szTemp)-iTmp3-1];
		}
		szTmpv3[iTmp3+1]='\0';
		strcpy(szTemp,szTmpv3);
		//cprintf("\n");
	 //   cprintf("the difference = ");
		//printf("%s\n", szTemp);
		//cprintf("\r");


			if(iS==kTmp&&jTmp!=kTmp||a==1) 
			  {
				cprintf("%s > %s\n\r", dwValue1, dwValue2);
				fcloseall();
				End(2);
			  }
			  if(a==0)
			  {
				cprintf("%s = %s\n\r", dwValue1, dwValue2);
				fcloseall();
				End(1);
			  }
			  if(iS==jTmp&&jTmp!=kTmp||a==-1) 
			  {
				cprintf("%s < %s\n\r", dwValue1, dwValue2);
				fcloseall();
				End(0);
			  }

}

void DecCmp(char *dwValue1,char *dwValue2)
{
		char szTVal1[1024],szTVal2[1024];
		strcpy(szTVal1,dwValue1);
		strcpy(szTVal2,dwValue2);
		for (int im=0;im<strlen(dwValue1);im++)
		{
			for(int in=0;in<36;in++)
			{
				if(dwValue1[im]==Code[in])
				{
					if(in>9)
					{
						cprintf("\n\r ERROR !!%s Is Not Dec Data !! ",dwValue1);
						End(nErrorLevel);
					}
				}
			}
		}
		for (int jm=0;jm<strlen(dwValue2);jm++)
		{
			for(int jn=0;jn<36;jn++)
			{
				if(dwValue2[jm]==Code[jn])
				{
					if(jn>9)
					{
						cprintf("\n\r ERROR !! %s Is Not Dec Data !! ",dwValue2);
						End(nErrorLevel);
					}
				}
			}
		}

		int jTmp,kTmp;
		int ib=0,ic=0;
		for(int i=0;i<strlen(dwValue1);i++)
		{
		    if(dwValue1[i]=='-')
			{
				i++;
				ib=1;
			}
			if(dwValue1[i]!='0' || strlen(dwValue1)==1)
			{
				jTmp=strlen(dwValue1)-i;
				break;
			}
		}
		char szTmpv1[1024],szTmpv2[1024];
		for(int iTmp1=0;iTmp1<jTmp;iTmp1++)
		{
			szTmpv1[iTmp1]=dwValue1[strlen(dwValue1)-jTmp+iTmp1];
		}
		szTmpv1[iTmp1]='\0';
		strcpy(dwValue1,szTmpv1);
		for(int ii=0;ii<strlen(dwValue2);ii++)
		{
		    if(dwValue2[ii]=='-')
			{
				ii++;
				ic=1;
			}
			if((dwValue2[ii]!='0') || strlen(dwValue2)==1)
			{
				kTmp=strlen(dwValue2)-ii;
				break;
			}
		}
		for(int iTmp2=0;iTmp2<kTmp;iTmp2++)
		{
			szTmpv2[iTmp2]=dwValue2[strlen(dwValue2)-kTmp+iTmp2];
		}
		szTmpv2[iTmp2]='\0';
		strcpy(dwValue2,szTmpv2);
		if(ib==1&&ic!=1)
		{
			cprintf("%s < %s\n", szTVal1, szTVal2);
			fcloseall();
			End(0);
		}
		if(ib!=1&&ic==1)
		{
			cprintf("%s < %s\n", szTVal2, szTVal1);
			fcloseall();
			End(2);
		}
		if(ib==1&&ic==1||ib==0&&ic==0)
		{
			int iS=jTmp<kTmp?jTmp:kTmp;
			int iU=jTmp>kTmp?jTmp:kTmp;
			int a=2;
			if(iS==iU)
			{
				for(int iii=0;iii<jTmp;iii++)
				{
					if((dwValue1[iii]-'0')-(dwValue2[iii]-'0')>0)
					{
						a=1;
						break;
					}				
					if((dwValue1[iii]-'0')-(dwValue2[iii]-'0')<0)
					{
						a=-1;
						break;
					}
					if((dwValue1[iii]-'0')-(dwValue2[iii]-'0')==0)
					{
						a=0;
					}	
				}
			}
			char szTemp[1024];
			int iT=0;
			for(int iN=iS-1,iV=iU-1;iN>=0;iN--)
			{
				if(iS==jTmp&&jTmp!=kTmp||a==-1)
				{
					if(iT<0)
					{
						iT=(dwValue2[iV]-'0')-1-(dwValue1[iN]-'0');
						if(iT<0)
							szTemp[iV]=(dwValue2[iV]-'0')-1-(dwValue1[iN]-'0')+10+'0';
						else
							szTemp[iV]=(dwValue2[iV]-'0')-1-(dwValue1[iN]-'0')+'0';
					}
					else
					{
						iT=(dwValue2[iV]-'0')-(dwValue1[iN]-'0');
						if(iT<0)
							szTemp[iV]=(dwValue2[iV]-'0')-(dwValue1[iN]-'0')+10+'0';
						else
							szTemp[iV]=(dwValue2[iV]-'0')-(dwValue1[iN]-'0')+'0';
					}
					if(iN==0&&iV>0)
					{
						if(iT<0)
						{
							iV--;
							for(;iV>0;iV--)
							{
								if(iT<0)
								{
									cprintf("%d",iT);
									iT=(dwValue2[iV]-'0')-1;
									if(iT<0)
										szTemp[iV]=iT+10+'0';
									else
										szTemp[iV]=iT+'0';
								}
								else
									szTemp[iV]=dwValue2[iV];
		    				}
						}
						else
							for(;iV>0;)
							{
								iV--;
								szTemp[iV]=(dwValue2[iV]-'0')+'0';
		    				}
					}
					szTemp[kTmp]='\0';
				}
				if(iS==kTmp&&jTmp!=kTmp||a==1)
				{
					if(iT<0)
					{
						iT=(dwValue1[iV]-'0')-1-(dwValue2[iN]-'0');
						if(iT<0)
							szTemp[iV]=(dwValue1[iV]-'0')-1-(dwValue2[iN]-'0')+10+'0';
						else
							szTemp[iV]=(dwValue1[iV]-'0')-1-(dwValue2[iN]-'0')+'0';
					}
					else
					{
						iT=(dwValue1[iV]-'0')-(dwValue2[iN]-'0');
						if(iT<0)
							szTemp[iV]=(dwValue1[iV]-'0')-(dwValue2[iN]-'0')+10+'0';
						else
							szTemp[iV]=(dwValue1[iV]-'0')-(dwValue2[iN]-'0')+'0';
					}
					if(iN==0&&iV>0)
					{
						if(iT<0)
						{
							iV--;
							for(;iV>=0;iV--)
							{
								if(iT<0)
								{
									iT=(dwValue1[iV]-'0')-1;
									if(iT<0)
										szTemp[iV]=iT+10+'0';
									else
										szTemp[iV]=iT+'0';
								}
								else
								{
									szTemp[iV]=dwValue1[iV];
								}
		    				}
						}
						else
							for(;iV>0;)
							{
								iV--;
								szTemp[iV]=(dwValue1[iV]-'0')+'0';
		    				}
					}
					szTemp[jTmp]='\0';
				}
				if(a==0)
				{
					szTemp[0]='0';
					szTemp[1]='\0';
				}
			iV--;
			}
			//cprintf("\n");
		 //   cprintf("the difference =");	
			//printf("%s\n",szTemp);
			//cprintf("\r");
			if(((iS==kTmp&&jTmp!=kTmp||a==1)&&ib==0&&ic==0)||((iS==jTmp&&jTmp!=kTmp||a==-1)&&ib==1&&ic==1)) 
			{
				cprintf("%s > %s\n\r", szTVal1, szTVal2);
				fcloseall();
				End(2);
			}
			else if(a==0) 
			{
				cprintf("%s = %s\n\r",szTVal1, szTVal2);
				fcloseall();
				End(1);
			}
			if(((iS==jTmp&&jTmp!=kTmp||a==-1)&&ib==0&&ic==0)||((iS==kTmp&&jTmp!=kTmp||a==1)&&ib==1&&ic==1)) 
			{
				cprintf("%s < %s\n\r", szTVal1, szTVal2);
				fcloseall();
				End(0);
			}
		}
}

Boolean blDisplayBigWord(const char *lpfilename)
{
  FILE *lpfileBigWord = NULL;
  Boolean blOdd = FALSE;
  char chBigWord[8], chBW;
  int nDisplayBigWord = 0;

  unsigned int nCharX = 0,
	       nIndexX = 40;

  lpfileBigWord = fopen(lpfilename, "r");
  if(lpfileBigWord == NULL){
    fclose(lpfileBigWord);
    return FALSE;
  }

  while((chBW = fgetc(lpfileBigWord)) != EOF){
    if((chBW >= 0x30 && chBW <= 0x39)||
       (chBW >= 0x41 && chBW <= 0x5A)||
       (chBW >= 0x61 && chBW <= 0x7a)){
      chBigWord[nCharX] = chBW;
      nCharX++;
      if(nCharX > 8){
	fclose(lpfileBigWord);
	End(nErrorLevel);
      }
    }
  }
  if(nCharX == 0){
    fclose(lpfileBigWord);
    End(nErrorLevel); // if file is empty, exit
  }

  for(int i = 0 ; i <= nCharX-1 ; i++){
    if(!blOdd){
      nIndexX -= 4;
      blOdd = TRUE;
    }
    else{
      nIndexX -= 5;
      blOdd = FALSE;
    }
  }

  for(int s = 0 ; s < nCharX ; s++){
    if((chBigWord[s] >= 0x30 && chBigWord[s] <= 0x39)){
      nDisplayBigWord = chBigWord[s] - 0x30;
      pega.DisplayBigWord(nIndexX, 12, nDisplayBigWord);
      nIndexX += 9;
      continue;
    }else if((chBigWord[s] >= 0x41 && chBigWord[s] <= 0x5A)){
      nDisplayBigWord = chBigWord[s] - 0x37;
      if(nDisplayBigWord >= 16) pega.DisplayBigWord(nIndexX, 12, 18);
      else pega.DisplayBigWord(nIndexX, 12, nDisplayBigWord);
      nIndexX += 9;
      continue;
    }else if((chBigWord[s] >= 0x61 && chBigWord[s] <= 0x7A)){
      nDisplayBigWord = chBigWord[s] - 0x57;
      if(nDisplayBigWord >= 16) pega.DisplayBigWord(nIndexX, 12, 18);
      else pega.DisplayBigWord(nIndexX, 12, nDisplayBigWord);
      nIndexX += 9;
      continue;
    }
  }
  fclose(lpfileBigWord);
  return TRUE;
}


Boolean GetString(char File1[])
{
  FILE *fFile1;
  const unsigned int MAX_STRING = 1024;
  char s1[MAX_STRING]="\0",s2[MAX_STRING]="\0",zero[MAX_STRING]="\0",CH='\0';
  int  j,k,m;
  Boolean blResultOK=FALSE;
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
    //printf("%s",s2);
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
	  for(int si = 0 ; si < strlen(s2) ; si++){
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
	    pega.PrintStr(1, 4, " the number of line comma is less than of inputed comma !!", 0, 0x07);
	    return blResultOK;
	  }
	  s2[nSindx] = '\0';
	  if(nSmsk != 0){ // if there start_comma clear first comma
	    for(int nsi = 0 ; nsi < strlen(s2) ; nsi++)
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
	    pega.PrintStr(1, 4, " the number of line comma is less than of inputed comma !!", 0, 0x07);
	    //printf(" the number of line comma is less than of inputed comma !!");
	    return blResultOK;
	  }
	  s2[nSindx] = '\0';
	  if(nSmsk != 0){ // if there start_comma clear first comma
	    for(int nsi = 0 ; nsi < strlen(s2) ; nsi++)
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
	  pega.PrintStr(1, 4, " the number of line comma is less than of inputed comma !!", 0, 0x07);
	  //printf(" the number of line comma is less than of inputed comma !!");
	  return blResultOK;
	}
	s2[nSindx] = '\0';
	if(nSmsk != 0){ // if there start_comma clear first comma
	  for(int nsi = 0 ; nsi < strlen(s2) ; nsi++)
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

Boolean Set_Environment_Variable(char str3[],char EnvirVar[],char In_File[],char Out_File[])
{
  FILE *fin,*fout;
  int  j,jj,k,kk,m,mm,line=1,match=0;
  char s[450]="\0",ch1,s1[450]="\0";
  Boolean blResultOK=FALSE;

  textcolor(15);
  if((fin=fopen(In_File,"r"))==NULL) {
    textbackground(4);
    cprintf("\n\rERROR !! %s Not Found !!\n\r",In_File);
    fcloseall();
    return blResultOK;
  }
  if((fout=fopen(Out_File,"w"))==NULL) {
    textbackground(4);
    cprintf("\n\rERROR !! Can't Open %s !!\n\r",Out_File);
    fcloseall();
    return blResultOK;
  }
  if(strlen(EnvirVar)>1){
    for(k=0;k<strlen(EnvirVar);k++) EnvirVar[k]=toupper(EnvirVar[k]);
    fgets(s,450,fin);
    //for(k=0;k<strlen(s);k++) s[k]=toupper(s[k]);
    fprintf(fout,"%s","SET ");
    fprintf(fout,"%s",EnvirVar);
    fprintf(fout,"%s",s);
    textbackground(1);
    cprintf("\n\rPASS !! Environment Variable File Is OK !!\n\r");
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
    }
  }
  fcloseall();
  return blResultOK;
}


Boolean WlFileIntoCertainPosition(char *fn1, char *fn2, char *fn3, char *place)
{
  FILE *f,*f1,*f2;
  int i;
  long int x;
  unsigned char d,s[10],*result;
  uChar bData;
  Boolean blResultOK=FALSE;

  d=0,s[10]=0;
  textcolor(15);
  x=pega.atoh(place);
  if((f=fopen(fn3,"wb"))==NULL) {
    textbackground(4);
    cprintf("\n\rERROR !! %s Not Found !!\n\r",fn3);
    fcloseall();
    return blResultOK;
  }
  if((f1=fopen(fn1,"rb"))==NULL) {
    textbackground(4);
    cprintf("\n\rERROR !! %s Not Found !!\n\r",fn1);
    fcloseall();
    return blResultOK;
  }
  while(fscanf(f1,"%c",&d)!=EOF) fprintf(f,"%c",d);
  fseek(f,x,0);
  if((f2=fopen(fn2,"rb"))==NULL) {
    textbackground(4);
    cprintf("\n\rERROR !! %s Not Found !!\n\r",fn2);
    fcloseall();
    return blResultOK;
  }
  fseek(f2,40,0);
  for(;;){
    fscanf(f2,"%s",s);
    if((result=strrchr(s,'=')) != NULL) {
      result++;
      bData=pega.atoh(result);
      fprintf(f,"%c",bData);
      continue;
    }
    if((result=strrchr(s,'[')) != NULL) break;
  }
  fcloseall();
  pega.PrintStr(1,13," ... OK ... ", 0, 0x1F);
  return blResultOK=TRUE;
}


Boolean blOBWSN(char *fn)
{
  FILE *f1;
  char s[50];
  int  m,n,k;


  if((f1=fopen(fn,"r"))==NULL) {
    textbackground(4);
    cprintf("\n\r ERROR !! %s Not Found !! \n\r",fn);
    return FALSE;
  }
  fgets(s,50,f1);
  if(strlen(s)!=10){
    pega.PrintStr(1,12," Serial Number Length Error !! ",0,0x47);
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
	      pega.PrintStr(1,12," Error !! Serial Number Has  A, E, I, O, U  !! ",0,0x47);
	      return FALSE;
	    }
	  }
	} else{
	  pega.PrintStr(1,12," Week Number = 00 !! ",0,0x47);
	  return FALSE;
	}
      } else if((s[4]=='1') || (s[4]=='2') || (s[4]=='3') || (s[4]=='4')){
	if((s[5]=='0') || (s[5]=='1') || (s[5]=='2') || (s[5]=='3') || (s[5]=='4') ||
	   (s[5]=='5') || (s[5]=='6') || (s[5]=='7') || (s[5]=='8') || (s[5]=='9')){
	  for(k=6; k<10; k++){
	    if((s[k]=='A') || (s[k]=='E') || (s[k]=='I') || (s[k]=='O') || (s[k]=='U')){
	      pega.PrintStr(1,12," Error !! Serial Number Has  A, E, I, O, U  !! ",0,0x47);
	      return FALSE;
	    }
	  }
	} else{
	  pega.PrintStr(1,12," Week Number Error !! ",0,0x47);
	  return FALSE;
	}
      } else if(s[4]=='5'){
	if((s[5]=='0') || (s[5]=='1') || (s[5]=='2')){
	  //check serial number
	  for(k=6; k<10; k++){
	    if((s[k]=='A') || (s[k]=='E') || (s[k]=='I') || (s[k]=='O') || (s[k]=='U')){
	      pega.PrintStr(1,12," Error !! Serial Number Has  A, E, I, O, U  !! ",0,0x47);
	      return FALSE;
	    }
	  }
	} else{
	  pega.PrintStr(1,12," Week Number > 52 !! ",0,0x47);
	  return FALSE;
	}
      } else{
	pega.PrintStr(1,12," Week Number Error !! ",0,0x47);
	return FALSE;
      }
    } else{
      pega.PrintStr(1,12," Year Number Error !! ",0,0x47);
      return FALSE;
    }
  } else{
    pega.PrintStr(1,12," First 3 Numbers Not 2CP !! ",0,0x47);
    return FALSE;
  }
  pega.PrintStr(1,12," OBW Serial Number OK !! ",0,0x17);
  return TRUE;
}


void DCF(char *dwValue1,char *dwValue2)
{
	char szTVal1[1024]={0},szTVal2[1024]={0};
	strcpy(szTVal1,dwValue1);
	strcpy(szTVal2,dwValue2);
	for (int im=0;im<strlen(dwValue1);im++)
	{
	  for(int in=0;in<64;in++)
	  {
	    if(dwValue1[im]==Code[in])
	    {
			if(in>9)
		    {
		      cprintf("\n\r ERROR !!%s Is Not Dec Data !! ",dwValue1);
		      End(nErrorLevel);
		    }
		 }
	  }
    }
    for (int jm=0;jm<strlen(dwValue2);jm++)
    {
      for(int jn=0;jn<36;jn++)
      {
        if(dwValue2[jm]==Code[jn])
	    {
	      if(jn>9)
	      {
	        cprintf("\n\r ERROR !! %s Is Not Dec Data !! ",dwValue2);
	        End(nErrorLevel);
		  }
	    }
	  }
    }

    int jTmp,kTmp;
    int ib=0,ic=0;
    for(int i=0;i<strlen(dwValue1);i++)
    {
      if(dwValue1[i]=='-')
	  {
        i++;
	    ib=1;
	  }
	  if(dwValue1[i]!='0')
      {
	    jTmp=strlen(dwValue1)-i;
	    break;
	  }
    }
	char szTmpv1[1024]={0},szTmpv2[1024]={0};
    for(int iTmp1=0;iTmp1<jTmp;iTmp1++)
    {
      szTmpv1[iTmp1]=dwValue1[strlen(dwValue1)-jTmp+iTmp1];
    }
    szTmpv1[iTmp1]='\0';
    strcpy(dwValue1,szTmpv1);
    for(int ii=0;ii<strlen(dwValue2);ii++)
    {
      if(dwValue2[ii]=='-')
      {
	    ii++;
   	    ic=1;
      }
	  if(dwValue2[ii]!='0')
	  {
	    kTmp=strlen(dwValue2)-ii;
	    break;
	  }
    }
    for(int iTmp2=0;iTmp2<kTmp;iTmp2++)
    {
      szTmpv2[iTmp2]=dwValue2[strlen(dwValue2)-kTmp+iTmp2];
    }
    szTmpv2[iTmp2]='\0';
    strcpy(dwValue2,szTmpv2);
    if(ib==1&&ic!=1)
    {
      cprintf("%s < %s\n", szTVal1, szTVal2);
      fcloseall();
      End(1);
    }
    if(ib!=1&&ic==1)
    {
      cprintf("%s < %s\n", szTVal1, szTVal2);
   	  fcloseall();
	  End(1);
    }
    if(ib==1&&ic==1||ib==0&&ic==0)
    {
      int iS=jTmp<kTmp?jTmp:kTmp;
	  int iU=jTmp>kTmp?jTmp:kTmp;
	  int a=2;
      if(iS==iU)
	  {
	    for(int iii=0;iii<jTmp;iii++)
	    {
		  if((dwValue1[iii]-'0')-(dwValue2[iii]-'0')>0)
		  {
			  a=1;
			  break;
		  }
		  if((dwValue1[iii]-'0')-(dwValue2[iii]-'0')<0)
		  {
			  a=-1;
			  break;
		  }
		  if((dwValue1[iii]-'0')-(dwValue2[iii]-'0')==0)
		  {
			  a=0;
		  }
	    }
	  }
	  char szTemp[1024]={0};
	  int iT=0;
	  for(int iN=iS-1,iV=iU-1;iN>=0;iN--)
	  {
	    if(iS==jTmp&&jTmp!=kTmp||a==-1)
	    {
		  a=-1;
		  if(iT<0)
		  {
		    iT=(dwValue2[iV]-'0')-1-(dwValue1[iN]-'0');
		    if(iT<0)
		 	  szTemp[iV]=(dwValue2[iV]-'0')-1-(dwValue1[iN]-'0')+10+'0';
		    else
			  szTemp[iV]=(dwValue2[iV]-'0')-1-(dwValue1[iN]-'0')+'0';
		  }
		  else
		  {
		    iT=(dwValue2[iV]-'0')-(dwValue1[iN]-'0');
		    if(iT<0)
		      szTemp[iV]=(dwValue2[iV]-'0')-(dwValue1[iN]-'0')+10+'0';
		    else
		      szTemp[iV]=(dwValue2[iV]-'0')-(dwValue1[iN]-'0')+'0';
		  }
		  if(iN==0&&iV>0)
		  {
		    if(iT<0)
	        {
		      iV--;
		      for(;iV>0;iV--)
			  {
			    if(iT<0)
			    {
			      cprintf("%d",iT);
				    iT=(dwValue2[iV]-'0')-1;
				    if(iT<0)
				    szTemp[iV]=iT+10+'0';
				    else
				    szTemp[iV]=iT+'0';
			    }
			    else
			      szTemp[iV]=dwValue2[iV];
		      }
		    }
		    else
		      for(;iV>0;)
		      {
		        iV--;
			    szTemp[iV]=(dwValue2[iV]-'0')+'0';
		      }
	      }
	      szTemp[kTmp]='\0';
	    }
	    if(iS==kTmp&&jTmp!=kTmp||a==1)
	    {
	    if(iT<0)
	    {
	      iT=(dwValue1[iV]-'0')-1-(dwValue2[iN]-'0');
		  if(iT<0)
		    szTemp[iV]=(dwValue1[iV]-'0')-1-(dwValue2[iN]-'0')+10+'0';
		  else
		    szTemp[iV]=(dwValue1[iV]-'0')-1-(dwValue2[iN]-'0')+'0';
	    }
	    else
	    {
	      iT=(dwValue1[iV]-'0')-(dwValue2[iN]-'0');
		  if(iT<0)
		    szTemp[iV]=(dwValue1[iV]-'0')-(dwValue2[iN]-'0')+10+'0';
		  else
		    szTemp[iV]=(dwValue1[iV]-'0')-(dwValue2[iN]-'0')+'0';
	    }
	    if(iN==0&&iV>0)
	    {
		  if(iT<0)
		  {
		    iV--;
		    for(;iV>=0;iV--)
		    {
		      if(iT<0)
		      {
			    iT=(dwValue1[iV]-'0')-1;
			    if(iT<0)
			      szTemp[iV]=iT+10+'0';
			    else
				  szTemp[iV]=iT+'0';
			  }
			  else
			  {
			    szTemp[iV]=dwValue1[iV];
			  }
		    }
		  }
		  else
		    for(;iV>0;)
		    {
			  iV--;
			  szTemp[iV]=(dwValue1[iV]-'0')+'0';
		    }
	    }
	    szTemp[jTmp]='\0';
	  }
	  if(a==0)
	  {
		szTemp[0]='0';
		szTemp[1]='\0';
	  }
      iV--;
    }
    if(a==-1)
    {
      int kk = strlen(szTemp);
      szTemp[kk+1]='\0';
      if(szTemp[0]=='0') szTemp[0]='-';
      else
      {
	    for(kk=strlen(szTemp) ; kk>0 ; kk--)
	    {
	      szTemp[kk] = szTemp[kk-1];
	    }
	    szTemp[0]='-';
      }
    }
    cprintf("\n");
    cprintf("the difference =");
    printf("%s\n",szTemp);
    cprintf("\r");

    if(blDiff)
    {
	  if(((iS==kTmp&&jTmp!=kTmp||a==1)&&ib==0&&ic==0)||((iS==jTmp&&jTmp!=kTmp||a==-1)&&ib==1&&ic==1))
	  {
		cprintf("%s > %s\n\r", szTVal1, szTVal2);
		DecCmp(szTemp,szStr);
	  }
	  else if(a==0)
	  {
		cprintf("%s = %s\n\r",szTVal1, szTVal2);
		DecCmp(szTemp,szStr);
	  }
	  if(((iS==jTmp&&jTmp!=kTmp||a==-1)&&ib==0&&ic==0)||((iS==kTmp&&jTmp!=kTmp||a==1)&&ib==1&&ic==1))
	  {
		cprintf("%s < %s\n\r", szTVal1, szTVal2);
		DecCmp(szTemp,szStr);
	  }
    }
    else
    {
	  if(((iS==kTmp&&jTmp!=kTmp||a==1)&&ib==0&&ic==0)||((iS==jTmp&&jTmp!=kTmp||a==-1)&&ib==1&&ic==1))
	  {
		cprintf("%s > %s\n\r", szTVal1, szTVal2);
		fcloseall();
		End(2);
	  }
	  else if(a==0)
	  {
		cprintf("%s = %s\n\r",szTVal1, szTVal2);
		fcloseall();
		End(1);
	  }
	  if(((iS==jTmp&&jTmp!=kTmp||a==-1)&&ib==0&&ic==0)||((iS==kTmp&&jTmp!=kTmp||a==1)&&ib==1&&ic==1))
	  {
		cprintf("%s < %s\n\r", szTVal1, szTVal2);
		fcloseall();
		End(0);
	  }
    }
  }
}

void HCF(char *dwValue1,char *dwValue2)
{
  for(int i=0,jTmp=0;i<strlen(dwValue1);i++)
  {
    if(dwValue1[i]!='0')
    {
      jTmp=strlen(dwValue1)-i;
	   break;
	}
  }
  char szTmpv1[1024]={0},szTmpv2[1024]={0};
  for(int iTmp1=0;iTmp1<jTmp;iTmp1++)
  {
    szTmpv1[iTmp1]=dwValue1[strlen(dwValue1)-jTmp+iTmp1];
  }
  szTmpv1[iTmp1]='\0';
  strcpy(dwValue1,szTmpv1);
  for(int ii=0,kTmp=0;ii<strlen(dwValue2);ii++)
  {
    if(dwValue2[ii]!='0')
	{
      kTmp=strlen(dwValue2)-ii;
      break;
    }
  }
  for(int iTmp2=0;iTmp2<kTmp;iTmp2++)
  {
    szTmpv2[iTmp2]=dwValue2[strlen(dwValue2)-kTmp+iTmp2];
  }
  szTmpv2[iTmp2]='\0';
  strcpy(dwValue2,szTmpv2);
  int iS=jTmp<kTmp?jTmp:kTmp;
  int iU=jTmp>kTmp?jTmp:kTmp;
  int a=2;
  if(iS==iU)
  {
    for(int iii=0;iii<jTmp;iii++)
    {
      if((dwValue1[iii]-'0')-(dwValue2[iii]-'0')>0)
      {
        a=1;
        break;
      }				
      if((dwValue1[iii]-'0')-(dwValue2[iii]-'0')<0)
      {
        a=-1;
        break;
      }
      if((dwValue1[iii]-'0')-(dwValue2[iii]-'0')==0)
      {
        a=0;
      }
    }
  }
  char szTemp[1024]={0};
  szTemp[0]='\0';
  char szTstr[10]={0};
  int iTemp;
  for(int iN=iS-1,iV=iU-1,iT=0;iN>=0;iN--)
  {
    if(iS==jTmp&&jTmp!=kTmp||a==-1)
    {
      if(iT<0)
      {
        iT=/*(dwValue2[iV]-'0')*/cXtoD(dwValue2,iV)-1-cXtoD(dwValue1,iN);/*(dwValue1[iN]-'0')*/
        if(iT<0)
        {
          sprintf(szTstr,"%X",iT+16);
          strcat(szTemp,szTstr);
        }
		else
        {
	      sprintf(szTstr,"%X",iT);
	      strcat(szTemp,szTstr);
	    }
      }
      else
      {
        iT=cXtoD(dwValue2,iV)-cXtoD(dwValue1,iN);
        if(iT<0)
        {
          sprintf(szTstr,"%X",iT+16);
          strcat(szTemp,szTstr);
        }
        else
        {
          sprintf(szTstr,"%X",iT);
          strcat(szTemp,szTstr);
        }
      }
      if(iN==0&&iV>0)
      {
        if(iT<0)
        {
          iV--;
          for(;iV>0;iV--)
          {
            if(iT<0)
            {
              iT=cXtoD(dwValue2,iV)-1;
              if(iT<0)
              {
			    sprintf(szTstr,"%X",iT+16);
		        strcat(szTemp,szTstr);
              }
            else
            {
              sprintf(szTstr,"%X",iT);
              strcat(szTemp,szTstr);
            }
          }
          else
          {
            sprintf(szTstr,"%X",cXtoD(dwValue2,iV));
            strcat(szTemp,szTstr);
          }
        }
      }
      else
      for(;iV>0;)
      {
        iV--;
        sprintf(szTstr,"%X",cXtoD(dwValue2,iV));
        strcat(szTemp,szTstr);
      }
      }
    }
    if(iS==kTmp&&jTmp!=kTmp||a==1)
    {
      if(iT<0)
      {
        iT=/*(dwValue1[iV]-'0')*/cXtoD(dwValue1,iV)-1-cXtoD(dwValue2,iN);/*(dwValue2[iN]-'0')*/
        if(iT<0)
        {
          sprintf(szTstr,"%X",iT+16);
		  strcat(szTemp,szTstr);
	    }
        else
        {
          sprintf(szTstr,"%X",iT);
          strcat(szTemp,szTstr);
        }
      }
      else
      {
        iT=cXtoD(dwValue1,iV)-cXtoD(dwValue2,iN);
		if(iT<0)
		{
		  sprintf(szTstr,"%X",iT+16);
		  strcat(szTemp,szTstr);
		}
		else
		{
		  sprintf(szTstr,"%X",iT);
		  strcat(szTemp,szTstr);
		}
	  }
	  if(iN==0&&iV>0)
	  {
	    if(iT<0)
		{
		  iV--;
		  for(;iV>=0;iV--)
		  {
			if(iT<0)
			{
			  iT=cXtoD(dwValue1,iV)-1;
			  if(iT<0)
			  {
				sprintf(szTstr,"%X",iT+16);
				strcat(szTemp,szTstr);
		      }
              else
              {
                sprintf(szTstr,"%X",iT);
				strcat(szTemp,szTstr);
              }
			}
			else
			{
			  sprintf(szTstr,"%X",cXtoD(dwValue1,iV));
			  strcat(szTemp,szTstr);
			}
          }
        }
        else
        for(;iV>0;)
        {
          iV--;
          sprintf(szTstr,"%X",cXtoD(dwValue1,iV));
          strcat(szTemp,szTstr);
        }
      }
    }
	iV--;
  }
  char szTmpv3[1024];
  for(int iTmp3=0;iTmp3<strlen(szTemp);iTmp3++)
  {
    szTmpv3[iTmp3]=szTemp[strlen(szTemp)-iTmp3-1];
  }
  szTmpv3[iTmp3+1]='\0';
  strcpy(szTemp,szTmpv3);
  cprintf("\n");
  cprintf("the difference = ");
  printf("%s\n", szTemp);
  cprintf("\r");
  if(blDiff)
  {
    if(iS==kTmp&&jTmp!=kTmp||a==1) 
    {
      cprintf("%s > %s\n\r", dwValue1, dwValue2);
	  HexCmp(szTemp,szStr);
    }
    else if(a==0)
	{
      cprintf("%s = %s\n\r", dwValue1, dwValue2);
	  HexCmp(szTemp,szStr);
    }
    else if(iS==jTmp&&jTmp!=kTmp||a==-1) 
	{
	  cprintf("%s < %s\n\r", dwValue1, dwValue2);
	  HexCmp(szTemp,szStr);	
    }
  }
  else
  {
    if(iS==kTmp&&jTmp!=kTmp||a==1) 
	{
      cprintf("%s > %s\n\r", dwValue1, dwValue2);
	  fcloseall();
	  End(2);
    }
    else if(a==0)
	{
      cprintf("%s = %s\n\r", dwValue1, dwValue2);
	  fcloseall();
	  End(1);
    }
    else if(iS==jTmp&&jTmp!=kTmp||a==-1) 
	{
	  cprintf("%s < %s\n\r", dwValue1, dwValue2);
	  fcloseall();
	  End(0);
    }
  }
}