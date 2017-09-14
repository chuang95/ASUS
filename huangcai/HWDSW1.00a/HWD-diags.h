

#include <conio.h>
#include <stdio.h>
#include <atlbase.h> 
#include "windows.h"
#include "Winsock2.h"
//#include "work.h"

void ReadMe(void);
void Logo(void);
void End(int ReturnCode);
//bool ChangeMountPoint(LPCTSTR lpDriveLetter,LPCTSTR lpDevice,bool bAddMountPoint);
BOOL GetOSDisplayString( LPTSTR pszOS);
BOOL blDetectlanThread();
BOOL blDetectUSBThread();
BOOL blDetectCDThread();
BOOL blDetectCarReaderThread();

