

#include <conio.h>
#include <stdio.h>
#include <atlbase.h> 
#include "windows.h"
#include "Winsock2.h"
#include "work.h"
#include "CountTime.h"
void ReadMe(void);
void Logo(void);
void End(int ReturnCode);
//void vChangeDisk(int iOldName,int iNewName);
bool ChangeMountPoint(LPCTSTR lpDriveLetter,LPCTSTR lpDevice,bool bAddMountPoint);
struct Position
{
	int a;
	int b;
};
struct CubeSize
{
	int x;
	int y;
};

BOOL blCubeThread(Position *p);
bool blCountThread(int a);
bool blMUThread(int a);
bool blCPUThread();
bool blMemoryThread();
bool blCountTime();
extern CubeSize g_CubeSize;
extern int nFormNum;