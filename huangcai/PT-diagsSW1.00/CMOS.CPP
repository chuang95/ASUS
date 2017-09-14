#include "cmos.h"
#include "extern.h"

obj_CMOS::obj_CMOS(void)
{
  blCheckUIP=TRUE;
  bBAdd=0x70;
}

obj_CMOS::~obj_CMOS(void)
{
}

BYTE obj_CMOS::Read(BYTE reg, BOOL blCheckUIP_)
{
  if(blCheckUIP && blCheckUIP_ && bBAdd==0x70) {
	  int i=0;
    for(; i<1000; i++) {
	  IOWB(bBAdd,0x0A);
      if((bIOR(bBAdd+1)&0x80)==0x00) break;
      Sleep(1);
    }
    if(i==1000) blCheckUIP=FALSE;
  }
  IOWB(bBAdd,reg);

  return bIOR(bBAdd+1);
}

char obj_CMOS::Write(BYTE reg, BYTE data, BOOL blCheckUIP_)
{
  if(blCheckUIP && blCheckUIP_ && bBAdd==0x70) {
	  int i=0;
    for(; i<1000; i++) {
      IOWB(bBAdd,0x0A);
      if((bIOR(bBAdd+1)&0x80)==0x00) break;
      Sleep(1);
    }
    if(i==1000) blCheckUIP=blCheckUIP_=FALSE;
  }
  IOWB(bBAdd,reg);
  IOWB(bBAdd+1,data);

  if(Read(reg, blCheckUIP_)==data) return 0;
  return -1;
}

BYTE obj_CMOS::ReadEx7273(BYTE reg)
{
  IOWB(0x72,reg);
  return bIOR(0x73);
}

char obj_CMOS::WriteEx7273(BYTE reg, BYTE data)
{
  IOWB(0x72,reg);
  IOWB(0x73,data);

  if(ReadEx7273(reg)==data) return 0;
  return -1;
}

BYTE obj_CMOS::ReadEx7071(BYTE reg)
{
  IOWB(0x70,reg);
  return bIOR(0x71);
}

char obj_CMOS::WriteEx7071(BYTE reg, BYTE data)
{
  IOWB(0x70,reg);
  IOWB(0x71,data);

  if(ReadEx7071(reg)==data) return 0;
  return -1;
}
