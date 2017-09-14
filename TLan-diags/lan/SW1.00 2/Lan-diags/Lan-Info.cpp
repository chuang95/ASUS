#include "stdafx.h"
#include <conio.h>
#include "Lan-diags.h"
#include "extern.h"
#include <NtDDNdis.h>
#include <winioctl.h>


#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383
#define szLanReg "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\NetworkCards"

CString sMacAddress = "";
double dLinkSpeed = 0;
long lSignal = 0;
int nSignalQuality = 0;
ChkType CurrentType = Chk_Start;

void PrintString(CString sString, BOOL blCopy = false)
{
	int x = wherex();
	int y = wherey();
	if(blCopy) 
		textattr(0x0A);
	_cprintf("%s", sString);
	
	if(blCopy || CurrentType == Chk_Info)
	{	  
	  gotoxy(x, y);
	  printf("%s", sString);
	}
	textattr(0x07);
}

void PrintInfo(CString sTitle, CString sInfo, BOOL blWrite = false)
{	
	CString sString = "";

	textattr(0x08);	
	sString.Format(" %s", sTitle);	
	PrintString(sString);

	for(int i = sTitle.GetLength(); i < 13; i++)
	{		
		PrintString(" ");
	}
	PrintString("= ");

	textattr(0x07);
	sString.Format("%s\n\r", sInfo);
	PrintString(sString, blWrite);

}

BOOL blGetLinkSpeed(HANDLE hFile)
{
	NDIS_OID OidCode = OID_GEN_LINK_SPEED;
	DWORD OidData;
	DWORD dwReturnedCount = 0;	

	if (DeviceIoControl(
		hFile,
		IOCTL_NDIS_QUERY_GLOBAL_STATS,
		&OidCode,
		sizeof(OidCode),
		&OidData,
		sizeof(OidData),
		&dwReturnedCount,
		NULL
	))
	{
		if(dwReturnedCount == 4) 
		{
			CString sInfo;
			sInfo.Format("%d Mbps", OidData/10000);
			PrintInfo("Link Speed", sInfo, CurrentType == Chk_Speed);
			dLinkSpeed = OidData/10000.;
			return true;
		}
	}
	return false;
}

BOOL blGetConnection(HANDLE hFile)
{
	NDIS_OID OidCode = OID_GEN_MEDIA_CONNECT_STATUS;
	DWORD OidData;
	DWORD dwReturnedCount = 0;
	BOOL blWrite = (CurrentType == Chk_Status)?true:false;

	if (DeviceIoControl(
		hFile,
		IOCTL_NDIS_QUERY_GLOBAL_STATS,
		&OidCode,
		sizeof(OidCode),
		&OidData,
		sizeof(OidData),
		&dwReturnedCount,
		NULL
	))
	{
		if(dwReturnedCount == 4)
		{		
			if(OidData == NdisMediaStateConnected)
			{				
				PrintInfo("Link Status", "Connected", blWrite);
				return true;
			}
			else if(OidData == NdisMediaStateDisconnected)
			{				
				PrintInfo("Link Status", "Disconnected", blWrite);				
				return false;
			}
		}
	}
	PrintInfo("Link Status", "Unknown", blWrite);		
	return false;
}

BOOL blGetMacAddress(HANDLE hFile)
{
	NDIS_OID OidCode = OID_802_3_PERMANENT_ADDRESS;
	BYTE OidData[6];
	DWORD dwReturnedCount = 0;
	sMacAddress = "";

	if (DeviceIoControl(
		hFile,
		IOCTL_NDIS_QUERY_GLOBAL_STATS,
		&OidCode,
		sizeof(OidCode),
		&OidData,
		sizeof(OidData),
		&dwReturnedCount,
		NULL
		))
	{
		if(dwReturnedCount == 6) 
		{
			for(int i = 0;i < 6; i++)
			{
				sMacAddress.Format("%s%02X", sMacAddress, OidData[i]);
				if(i != 5) 
					sMacAddress+="-";
			}		
			return true;
		}
	}
	return false;
}

BOOL blGetMediaType(HANDLE hFile)
{
	NDIS_OID OidCode = OID_GEN_PHYSICAL_MEDIUM;	
	//NDIS_OID OidCode = OID_GEN_MEDIA_SUPPORTED;	
	NDIS_PHYSICAL_MEDIUM OidData;
	DWORD dwReturnedCount = 0;

	if (DeviceIoControl(
		hFile,
		IOCTL_NDIS_QUERY_GLOBAL_STATS,
		&OidCode,
		sizeof(OidCode),
		&OidData,
		sizeof(OidData),
		&dwReturnedCount,
		NULL
		))
	{		
		if(dwReturnedCount == sizeof(NDIS_PHYSICAL_MEDIUM)) 
		{
			CString sInfo;
			switch(OidData)
			{	
				case NdisPhysicalMediumWirelessLan:  
					sInfo = "Wireless LAN Network";
					break;
				case NdisPhysicalMediumCableModem:  
					sInfo = "DOCSIS-based Cable Network";
					break;
				case NdisPhysicalMediumPhoneLine:  
					sInfo = "Standard Phone Lines";
					break;
				case NdisPhysicalMediumPowerLine:  
					sInfo = "Power Distribution System";
					break;
				case NdisPhysicalMediumDSL:  
					sInfo = "Digital Subscriber Line (DSL) Network";
					break;
				case NdisPhysicalMedium1394:  
					sInfo = "IEEE 1394 bus";
					break;
				case NdisPhysicalMediumFibreChannel:  
					sInfo = "Fibre Channel";
					break;						
				case NdisPhysicalMediumWirelessWan:  
					sInfo = "Wireless Wan";
					break;
				case NdisPhysicalMediumNative802_11:  
					sInfo = "802_11";
					break;
				case NdisPhysicalMediumBluetooth:  
					sInfo = "Bluetooth";
					break;
				case NdisPhysicalMediumUnspecified:
				case NdisPhysicalMediumMax:
				default:
					return false;
			}

			PrintInfo("Type", sInfo/*, (CurrentType == Chk_Signal)?true:false*/);
			return true;
		}
	}
	return false;
}

BOOL blGetSignalStrength(HANDLE hFile)
{	
	NDIS_OID OidCode = OID_802_11_RSSI;	
	NDIS_802_11_RSSI OidData;
	DWORD dwReturnedCount = 0;
	lSignal = 0;	

	if (DeviceIoControl(
		hFile,
		IOCTL_NDIS_QUERY_GLOBAL_STATS,
		&OidCode,
		sizeof(OidCode),
		&OidData,
		sizeof(OidData),
		&dwReturnedCount,
		NULL
		))
	{		
		if(dwReturnedCount == sizeof(OidData)) 
		{
			CString sInfo;
			sInfo.Format("%d dBm", OidData);
			PrintInfo("Strength", sInfo, CurrentType == Chk_SignalS);
			lSignal = OidData;
			return true;
		}
	}
	return false;
}

BOOL blCheckOSAfterVista()
{
	OSVERSIONINFO ver;	
	ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&ver);
	if(ver.dwPlatformId != VER_PLATFORM_WIN32s && ver.dwMajorVersion >=6)
		return true;
	return false;
}

BOOL blGetSignalQuality(CString sServiceName)
{
	CString sLine = "";
	sServiceName.SetAt(sServiceName.GetLength()-1, 0);
	sServiceName = sServiceName.Right(sServiceName.GetLength()-1);
	BOOL blItem = false;
	int nCount = 0;

	FILE *f = NULL;
	char buffer[100];
	if(f = fopen("lan-diags.log", "r+"))
	{
		while(!feof(f))
		{			
			if(fgets(buffer, 100, f) != NULL)	
			{	
				sLine = buffer;
				sLine = sLine.MakeUpper();
				nCount++;
				if(blItem && nCount == 13)
				{
					int nLoc = sLine.Find("%");
					if(nLoc >= 0)
					{			
						sLine.SetAt(nLoc, 0);
						nLoc = sLine.Find(":");
						if(nLoc >= 0)
						{						
							sLine = sLine.Right(sLine.GetLength() - nLoc -1);
							nSignalQuality = atoi(sLine);
							sLine.Format("%d%c", nSignalQuality, '%');
							PrintInfo("Signal",sLine, CurrentType == Chk_SignalQ);
							return TRUE;
						}						
					}
				}
				if(sLine.Find(sServiceName) >= 0)
				{
					blItem = true;
					nCount = 0;
				}
			}
		}
		fclose(f);

	}
	return false;
}

BOOL  blQueryKey(HKEY hKey, ChkType Type)
{ 
	BOOL blReturn = false;
	TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
	DWORD    cbName = 0;                   // size of name string 
	TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
	DWORD    cchClassName = MAX_PATH;  // size of class string 
	DWORD    cSubKeys = 0;               // number of subkeys 
	DWORD    cbMaxSubKey;              // longest subkey size 
	DWORD    cchMaxClass;              // longest class string 
	DWORD    cValues;              // number of values for key 
	DWORD    cchMaxValue;          // longest value name 
	DWORD    cbMaxValueData;       // longest value data 
	DWORD    cbSecurityDescriptor; // size of security descriptor 
	FILETIME ftLastWriteTime;      // last write time 
	char szServiceName[MAX_VALUE_NAME];
	char szDescription[MAX_VALUE_NAME];
	CurrentType = Type;

	DWORD i = 0;
	int nDevNO = 0;
	// Get the class name and the value count. 
	DWORD dwRetCode = RegQueryInfoKey(
		hKey,                  // key handle 
		achClass,              // buffer for class name 
		&cchClassName,         // size of class string 
		NULL,                  // reserved 
		&cSubKeys,             // number of subkeys 
		&cbMaxSubKey,          // longest subkey size 
		&cchMaxClass,          // longest class string 
		&cValues,              // number of values for this key 
		&cchMaxValue,          // longest value name 
		&cbMaxValueData,       // longest value data 
		&cbSecurityDescriptor, // security descriptor 
		&ftLastWriteTime);       // last write time 

	// Enumerate the subkeys, until RegEnumKeyEx fails.

	if (cSubKeys)
	{		
		int nRegDeviceNO = 0;
		for (i=0; i<cSubKeys; i++) 
		{ 
			cbName = MAX_KEY_LENGTH;
			dwRetCode = RegEnumKeyEx(hKey, i,
				achKey, 
				&cbName, 
				NULL, 
				NULL, 
				NULL, 
				&ftLastWriteTime); 
			if (dwRetCode == ERROR_SUCCESS) 
			{		
				char szSubKey[MAX_PATH];
				sprintf_s(szSubKey, MAX_PATH, "%s\\%s", szLanReg, achKey);
				LPCTSTR lpSubKey = (LPCTSTR) szSubKey;
				char *szName = "";			
				char szSetReg[MAX_PATH];
				strcpy_s(szSetReg, MAX_PATH, "\0");
				{
					LONG lResult = 0;
					HKEY hKey1;	

					lResult = RegOpenKeyEx(
						HKEY_LOCAL_MACHINE, 
						lpSubKey,
						0,
						KEY_QUERY_VALUE | KEY_READ , 
						&hKey1 
						);
					if(lResult != ERROR_SUCCESS)				
						continue;
					
					for(int k = 0; k<3; k++)
					{	
						DWORD dwLength;

						lResult = RegQueryValueEx(
							hKey1, 
							"Description", 
							NULL, 
							NULL,
							(BYTE *) szDescription, 
							&dwLength
							);
						if(lResult != ERROR_SUCCESS)
							continue;		
						break;
					}
					for(int k = 0; k<3; k++)
					{	
						DWORD dwLength;

						lResult = RegQueryValueEx(
							hKey1, 
							"ServiceName", 
							NULL, 
							NULL,
							(BYTE *) szServiceName, 
							&dwLength
							);
						if(lResult != ERROR_SUCCESS)
							continue;				
						break;
					}	
					RegCloseKey(hKey1); 
					TCHAR LinkName[MAX_VALUE_NAME];
					if (!QueryDosDevice(szServiceName, LinkName, sizeof(LinkName)) == 0)
					{
						CString sDescription = szDescription;
						sDescription = sDescription.MakeUpper();
						CString sServiceName = szServiceName;
						sServiceName = sServiceName.MakeUpper();									
						
						CString sFileName;
						sFileName.Format("\\\\.\\%s", szServiceName);
						HANDLE hFile = CreateFile(
							sFileName,
							GENERIC_READ,
							FILE_SHARE_READ | FILE_SHARE_WRITE,
							NULL,
							OPEN_EXISTING,
							0,
							INVALID_HANDLE_VALUE
						);
						if (hFile != INVALID_HANDLE_VALUE)
						{
							if(blGetMacAddress(hFile))
							{
								nDevNO++;
								if(g_nDevNO > -1 && g_nDevNO != nDevNO)
									continue;
								if(g_sDescription != "" && sDescription.Find(g_sDescription) < 0)
									continue;
								if(g_sServiceName != "" && sServiceName.Find(g_sServiceName) < 0)
									continue;
								if(g_sMacAddress != "" && sMacAddress.CompareNoCase(g_sMacAddress) != 0)
									continue;
								textattr(0x0B);
								int x = wherex();
								int y = wherey();
								_cprintf("%d:\n\r", nDevNO);
								if(Type == Chk_Info)
								{
									gotoxy(x, y);
									printf("%d:\n", nDevNO);
								}
								PrintInfo("Description", szDescription, false);
								PrintInfo("Service Name", szServiceName, false);	
								blGetMediaType(hFile);								
								BOOL blStatus = blGetConnection(hFile);
								BOOL blSpeed = blGetLinkSpeed(hFile);									
								PrintInfo("Mac Address", sMacAddress, (Type == Chk_MAC)?true:false);		
								BOOL blSignalStrength = blGetSignalStrength(hFile);							
								BOOL blSignalQuality = blGetSignalQuality(szServiceName);
								switch(Type)
								{
									case Chk_Status:
										if(blStatus)										
											blReturn = true;										
										break;
									case Chk_Speed:
										if(blSpeed && dLinkSpeed == g_dSpeed)
											blReturn = true;
										break;
									case Chk_MAC:
										if(g_sChkMacAddress.CompareNoCase(sMacAddress) == 0)
											blReturn = true;
										break;
									case Chk_SignalS:		
										if(blSignalStrength && lSignal <= 0 && lSignal >= g_lSignalStrength)
											blReturn = true;
										break;
									case Chk_SignalQ:		
										if(blSignalQuality && nSignalQuality >= g_nSignalQLower && nSignalQuality <= g_nSignalQUpper)
											blReturn = true;
										break;
									default:
										break;
								}
								
							}
							CloseHandle(hFile);
						}
					}
				}				
			}
		}
	} 
	return blReturn;
}

BOOL blGetNetworkCards(ChkType Type)
{
	BOOL blReturn = false;
	remove("lan-diags.log");

	if(blCheckOSAfterVista())
	{
		system("netsh wlan show interface > lan-diags.log");
	}

	HKEY hKey;
	if( RegOpenKeyEx( HKEY_LOCAL_MACHINE,
		TEXT(szLanReg),
		0,
		KEY_READ,
		&hKey) == ERROR_SUCCESS
	)
	{
		blReturn = blQueryKey(hKey, Type);
		RegCloseKey(hKey);
	}
	remove("lan-diags.log");
	return blReturn;
}
