#include <windows.h>

#if !defined(_CMOS_Type)
#define _CMOS_Type

class obj_CMOS {
  public:
    BOOL blCheckUIP;
    BYTE bBAdd;
    obj_CMOS();
    ~obj_CMOS();
    BYTE Read(BYTE reg, BOOL blCheckUIP_=TRUE);
    //BYTE Read((BYTE) reg, BOOL blCheckUIP_);
    char Write(BYTE reg, BYTE data, BOOL blCheckUIP_=TRUE);
    BYTE ReadEx7273(BYTE reg);
    char WriteEx7273(BYTE reg, BYTE data);
    BYTE ReadEx7071(BYTE reg);
    char WriteEx7071(BYTE reg, BYTE data);
};

#endif
