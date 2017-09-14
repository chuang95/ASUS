#include "stdafx.h"
#include "extern.h"
#include "work.h"
#include "Orderdisk-diags.h"


bool ChangeMountPoint(LPCTSTR lpDriveLetter,LPCTSTR lpDevice,bool bAddMountPoint)
{
    bool bRet = false;
    TCHAR szDriveLetterAndSlash[4] = {0};
    TCHAR szDriveLetter[3] = {0};
    TCHAR szUniqueVolumeName[MAX_PATH] = {0};
    if(lpDriveLetter && lpDevice)
    {
        szDriveLetter[0] = lpDriveLetter[0];
        szDriveLetter[1] = TEXT(':');
        szDriveLetter[2] = TEXT('\0');
        
        szDriveLetterAndSlash[0] = lpDriveLetter[0];
        szDriveLetterAndSlash[1] = TEXT(':');
        szDriveLetterAndSlash[2] = TEXT('\\');
        szDriveLetterAndSlash[3] = TEXT('\0');
        if ( bAddMountPoint )
        {
            //Try to Attach lpDevice to lpDriveLetter
            bRet = DefineDosDevice (DDD_RAW_TARGET_PATH, szDriveLetter,
                lpDevice);
            
            if (bRet)
            {
                if (!GetVolumeNameForVolumeMountPoint (szDriveLetterAndSlash,
                    szUniqueVolumeName,
                    MAX_PATH))
                {
                    //Can't Find Attached lpDevice 's VolumeName
                    szUniqueVolumeName[0] = '\0';
                }
                
                bRet = DefineDosDevice ( 
                    DDD_RAW_TARGET_PATH|DDD_REMOVE_DEFINITION|
                    DDD_EXACT_MATCH_ON_REMOVE, szDriveLetter,
                    lpDevice);
                
                if (!bRet)
                    return bRet;
                
                bRet = SetVolumeMountPoint(szDriveLetterAndSlash, 
                    szUniqueVolumeName);
            }
        }
        else
        {
            bRet = DeleteVolumeMountPoint (szDriveLetterAndSlash);
        }
    }
    
    return bRet;
}
void vChangeDisk(int iOldName, int iNewName)
{
	//REBOOT WILL RESUME
	//QueryDosDeviceA(szPath[iOldName],device,1024);   
	////printf("%s\n",device);
	//DefineDosDeviceA(DDD_RAW_TARGET_PATH,szPath[iOldName],"");   
	//DefineDosDeviceA(DDD_RAW_TARGET_PATH,szPath[iNewName],device);
	//DefineDosDevice ( 
 //                   DDD_RAW_TARGET_PATH|DDD_REMOVE_DEFINITION|
 //                   DDD_EXACT_MATCH_ON_REMOVE,szPath[iOldName],
 //                   NULL);
	//NEVER RESUME 
	szCPPath[0]='A'+iOldName;
	QueryDosDeviceA(szPath[iOldName],device,1024);
	DeleteVolumeMountPointA(szCPPath);	
	szCPPath[0]='A'+iNewName;
	ChangeMountPoint( _T(szCPPath), _T(device),true);
}