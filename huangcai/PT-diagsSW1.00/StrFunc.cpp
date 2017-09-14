#include <math.h>
#include "PT-diags.h"
#include "extern.h"

//--------------------------------------------------------------------------
void vExist_EXE(BOOL blExistFlag,char *sString1)
{
	if (blExistFlag) 	strcat(sString1,"\n");
//	else				strcat(sString1,"0");
//	return;
}

//--------------------------------------------------------------------------
char *  __cdecl SmartStrcpy(char *strDestination, const char *strSource )
{
	if (sizeof (*strDestination)==0) strcpy(strDestination,strSource);
	else							 strcat(strDestination,strSource);
	return strDestination;
}

//--------------------------------------------------------------------------
int iStringSeek(int iCurrentBufPtr,char S1[_wATStringMAX],char S2[_wATStringMAX])
{
	int i,j=0,iS1Len,iS2Len;
	iS1Len=(int)(strlen(S1))-iCurrentBufPtr; 
	iS2Len=(int)(strlen(S2));
	if (iS1Len<iS2Len) {
		//fprintf(stdout,"String1(%s) length(%d) < than String2(%s) length(%d) --> error\n",S1,iS1Len,S2,iS2Len);
		return _wATStringMAX;
	}
	i=iCurrentBufPtr;
	do {
		if (S1[i]==S2[j]) {
			i++;j++;
			if ((j==iS2Len) && (S1[i]=='|')) break;		//it's for function
			if ((j==iS2Len) && (S1[i-1]=='=')) break;	//it's for parameter
		} else {
			i++;
			j=0;
		}
	} while (i<_wATStringMAX);
	if (i==_wATStringMAX) return _wATStringMAX;
	return i;
}

//--------------------------------------------------------------------------
BYTE bHex2BCD(BYTE bHex)
{
	BYTE bBCD=0;
	for (int i=0;i<2;i++) bBCD+=((bHex>>(i*4))&0x0F)*(BYTE)(pow(10,(double)i));
	return bBCD;
}

//--------------------------------------------------------------------------
WORD wHex2BCD(WORD wHex)
{
	WORD wBCD=0;
	for (int i=0;i<4;i++) wBCD+=((wHex>>(i*4))&0x0F)*(WORD)(pow(10,(double)i));
	return wBCD;
}

//--------------------------------------------------------------------------
void vDelay838ns(WORD wInterval)
{
	_asm         mov     cx,wInterval
    _asm         mov     al,0x6
    _asm         out     0x43,al
    _asm         in      al,0x40
    _asm         mov     ah,al
    _asm         in      al,0x40
    _asm         xchg    ah,al
    _asm         mov     bx,ax
loc_delay:
    _asm         in      al,0x40
    _asm         mov     ah,al
    _asm         in      al,0x40
    _asm         xchg    ah,al
    _asm         mov     dx,bx
    _asm         sub     dx,ax
    _asm         cmp     dx,cx
    _asm         jb      loc_delay
}
