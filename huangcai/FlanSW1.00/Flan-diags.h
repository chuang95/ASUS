

#include <conio.h>
#include <stdio.h>
#include <atlbase.h> 
#include "windows.h"
#include "Winsock2.h"
//#include "work.h"

void ReadMe(void);
void Logo(void);
void End(int ReturnCode);
//void vChangeDisk(int iOldName,int iNewName);
bool ChangeMountPoint(LPCTSTR lpDriveLetter,LPCTSTR lpDevice,bool bAddMountPoint);
void CheckIP(void) ;
LONG64 l64AddTime(DWORD dwSecond, DWORD dwMSecond);
LONG64 l64GetTime();
void sError(char *str);
void vRandomStr(char *pStr);
bool blThread1();
