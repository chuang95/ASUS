#include "stdafx.h"
#include "cfgmgr32.h"
#include "Card.h"
#include "SetupAPI.h"
#include "setupapi.h"
#include "Resource.h"
#include "define.h"
#include "wchar.h"
#include "extern.h"
#include "conio.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define REGSTR_VAL_MAX_HCID_LEN		1024 

#ifdef _UNICODE 
#define DeviceProperties_RunDLL  "DeviceProperties_RunDLLW"
typedef void (_stdcall *PDEVICEPROPERTIES)(
										   HWND hwndStub,
										   HINSTANCE hAppInstance,
										   LPWSTR lpCmdLine,
										   int    nCmdShow
										   );

#else
#define DeviceProperties_RunDLL  "DeviceProperties_RunDLLA"
typedef void (_stdcall *PDEVICEPROPERTIES)(
										   HWND hwndStub,
										   HINSTANCE hAppInstance,
										   LPSTR lpCmdLine,
										   int    nCmdShow
										   );
#endif
char szTem[100];



CDevicePropertySheetDialogDlg::CDevicePropertySheetDialogDlg(/*CWnd* pParent*/ /*=NULL*/)
	//: CDialog(CDevicePropertySheetDialogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDevicePropertySheetDialogDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}




HCURSOR CDevicePropertySheetDialogDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CDevicePropertySheetDialogDlg::EnumDevices()
{
	TCHAR LocalComputer[MAX_PATH];
    DWORD Size = MAX_PATH - 2;
    
	GetComputerName(LocalComputer + 2, &Size);
    LocalComputer[0] = _T('\\');
    LocalComputer[1] = _T('\\');
    
	CONFIGRET cr;
	cr = CM_Connect_Machine(LocalComputer, &m_hMachine);
	
	if (cr != CR_SUCCESS)
	{
		TCHAR Text[MAX_PATH];
		wsprintf(Text, _T("Machine Connection failed, cr= %lx(hex)\n"), cr);
		::MessageBox(m_hWnd, Text, _T("Error"), MB_ICONSTOP | MB_OK);
		return;
	}	
	
	//Set Image List 
	m_ImageListData.cbSize = sizeof(m_ImageListData);
	SetupDiGetClassImageList(&m_ImageListData);
	
	m_ImageList.Attach(m_ImageListData.ImageList);
	m_Devices.SetImageList(&m_ImageList, LVSIL_SMALL);
	m_Devices.SetImageList(&m_ImageList, LVSIL_NORMAL);
	
	DEVNODE dnRoot;
	CM_Locate_DevNode_Ex(&dnRoot, NULL, 0, m_hMachine);
	
	DEVNODE dnFirst;
	CM_Get_Child_Ex(&dnFirst, dnRoot, 0, m_hMachine);	
	
	RetrieveSubNodes(dnRoot, NULL, dnFirst);
	CM_Disconnect_Machine(m_hMachine);
}

void CDevicePropertySheetDialogDlg::RetrieveSubNodes(DEVINST parent, DEVINST sibling, DEVNODE dn)
{
	DEVNODE dnSibling, dnChild;
    
	do
    {
		CONFIGRET cr = CM_Get_Sibling_Ex(&dnSibling, dn, 0, m_hMachine);
		
		if (cr != CR_SUCCESS)
			dnSibling = NULL;
		
#ifdef UNICODE
		TCHAR GuidString[MAX_GUID_STRING_LEN];
#else
		UCHAR GuidString[MAX_GUID_STRING_LEN];
#endif
		
		ULONG Size = sizeof(GuidString);
		
		cr = CM_Get_DevNode_Registry_Property_Ex(dn, CM_DRP_CLASSGUID, NULL,
			GuidString, &Size, 0,  m_hMachine);
		
		if (cr == CR_SUCCESS)
		{
			GUID Guid;
			GuidString[MAX_GUID_STRING_LEN - 2] = _T('\0');
			UuidFromString(&GuidString[1], &Guid);
			int Index;
			if (SetupDiGetClassImageIndex(&m_ImageListData, &Guid, &Index))
			{
				CString DeviceName=GetDeviceName(dn);
				sprintf(szTem,"%s",DeviceName);
				//strcat(DevN,szTem);
				
				if(strstr(szTem,"Card")!=0||strstr(szTem,"SD")!=0)
				{
					iSN++;
					lpCard=TRUE;
				}
				int itemNum=m_Devices.GetItemCount();
				m_Devices.InsertItem(itemNum, DeviceName, Index);
				m_Devices.SetItemData(itemNum, dn);
				EnumDeviceProperties(dn);
			}
		}
		
		cr = CM_Get_Child_Ex(&dnChild, dn, 0, m_hMachine);
		if (cr == CR_SUCCESS)
		{
			RetrieveSubNodes(dn, NULL, dnChild);
		}
		
		dn = dnSibling;
		
    } while (dn != NULL);
	
}


CString CDevicePropertySheetDialogDlg::GetDeviceName(DEVNODE DevNode)
{
	CString	strType;
    CString	strValue;
	CString DisplayName;
    LPTSTR	Buffer;
    
	int  BufferSize = MAX_PATH + MAX_DEVICE_ID_LEN;
    ULONG  BufferLen = BufferSize * sizeof(TCHAR);
    
	Buffer  = strValue.GetBuffer(BufferSize);
    if (CR_SUCCESS == CM_Get_DevNode_Registry_Property_Ex(DevNode,
		CM_DRP_FRIENDLYNAME, NULL,
		Buffer, &BufferLen, 0, m_hMachine))
    {
		DisplayName = Buffer;
    }
    else
    {
		BufferLen = BufferSize * sizeof(TCHAR);
		
		if (CR_SUCCESS == CM_Get_DevNode_Registry_Property_Ex(DevNode,
			CM_DRP_DEVICEDESC, NULL,
			Buffer, &BufferLen, 0, m_hMachine))
		{
			DisplayName = Buffer;
		}
		else
		{
			DisplayName=_T("Unknown Device");
		}
    }
	
	return DisplayName;
}

void CDevicePropertySheetDialogDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	SetupDiDestroyClassImageList(&m_ImageListData);
}

void CDevicePropertySheetDialogDlg::EnumDeviceProperties(DEVNODE dn)
{
	int BufferSize = MAX_PATH + MAX_DEVICE_ID_LEN;
	TCHAR Buffer[MAX_PATH + MAX_DEVICE_ID_LEN];
	CString Temp;
	
	DeviceProperties Properties[26]=
	{
		ID_DEVICEID,            _T("Device ID: "), _T(""),
		ID_STATUS,              _T("Status: "), _T(""),
		ID_PROBLEM,             _T("Problem: "), _T(""),
		ID_SERVICE,             _T("Service: "), _T(""),
		ID_CAPABILITIES,        _T("Capabilities: "), _T(""),
		ID_CONFIGFLAGS,         _T("Config Flags: "), _T(""),
		ID_DEVNODE,             _T("DevNode: "), _T(""),
		ID_COMPATIBELID,        _T("Compatible IDs: "), _T(""),
		ID_CLASS,               _T("Class: "), _T(""),
		ID_INFOFILE,            _T("Inf file: "), _T(""),
		ID_MFG,                 _T("Manufacturer: "), _T(""),
		ID_HARDWAREID,          _T("Hardware IDs: "), _T(""),
		ID_COMPATIBLEID,        _T("Compatible IDs: "), _T(""),
		ID_CLASSGUID,           _T("Class Guid: "), _T(""),
		ID_LOCATION,            _T("Location: "), _T(""),
		ID_BUSNUMBER,           _T("Bus number: "), _T(""),
		ID_ENUMERATOR_NAME,     _T("Enumerator name: "), _T(""),
		ID_DEVICEDESC,          _T("Description: "), _T(""),
		ID_FRIENDLYNAME,        _T("Friendly name: "), _T(""),
		ID_DRIVER,              _T("Driver: "), _T(""),
		ID_PHYSICAL_DEVPATH,    _T("Physical Object Name: "), _T(""),
		ID_UI_NUMBER,           _T("UI number: "), _T(""),
		ID_UPPERFILTERS,        _T("Upper filters: "), _T(""),
		ID_LOWERFILTERS,        _T("Lower filters: "), _T(""),
		ID_BUSTYPEGUID,         _T("Bustype GUID: "), _T(""),
		ID_LEGACYBUSTYPE,       _T("Legacy bus type: "), _T("")
	};

	if (CM_Get_Device_ID_Ex(dn, Buffer, BufferSize, 0, m_hMachine) == CR_SUCCESS)
    {
		_tcscpy(Properties[ID_DEVICEID].PropertyValue, Buffer);
    }
	else
	{
		Temp=_T("Fail to retrieve Device ID");
		_tcscpy(Properties[ID_DEVICEID].PropertyValue, Temp);		
	}

    ULONG Status, Problem;

    if (CM_Get_DevNode_Status_Ex(&Status, &Problem, dn, 0, m_hMachine) == CR_SUCCESS)
    {
		Temp.Format(_T("0x%08x"), Status);
		_tcscpy(Properties[ID_STATUS].PropertyValue, Temp);

		Temp.Format(_T("0x%08x"), Problem);
		_tcscpy(Properties[ID_PROBLEM].PropertyValue, Temp);
    }
	else
	{
		Temp=_T("Fail to retrieve Device Status");
		_tcscpy(Properties[ID_STATUS].PropertyValue, Temp);

		Temp=_T("Fail to retrieve Device Problem");
		_tcscpy(Properties[ID_PROBLEM].PropertyValue, Temp);
	}


	Temp=GetProperty(dn, CM_DRP_SERVICE);
	_tcscpy(Properties[ID_SERVICE].PropertyValue, Temp);
	
    Temp=GetProperty(dn, CM_DRP_CAPABILITIES);
	_tcscpy(Properties[ID_CAPABILITIES].PropertyValue, Temp);

    Temp=GetProperty(dn, CM_DRP_CONFIGFLAGS);
	_tcscpy(Properties[ID_CONFIGFLAGS].PropertyValue, Temp);

    Temp=GetProperty(dn, CM_DRP_MFG);
	_tcscpy(Properties[ID_MFG].PropertyValue, Temp);

    Temp=GetProperty(dn, CM_DRP_CLASS);
	_tcscpy(Properties[ID_CLASS].PropertyValue, Temp);

    Temp=GetProperty(dn, CM_DRP_HARDWAREID);
	_tcscpy(Properties[ID_HARDWAREID].PropertyValue, Temp);

    Temp=GetProperty(dn, CM_DRP_COMPATIBLEIDS);
	_tcscpy(Properties[ID_COMPATIBLEID].PropertyValue, Temp);

    Temp=GetProperty(dn, CM_DRP_CLASSGUID);
	_tcscpy(Properties[ID_CLASSGUID].PropertyValue, Temp);

    Temp=GetProperty(dn, CM_DRP_LOCATION_INFORMATION);
	_tcscpy(Properties[ID_LOCATION].PropertyValue, Temp);

    Temp=GetProperty(dn, CM_DRP_BUSNUMBER);
	_tcscpy(Properties[ID_BUSNUMBER].PropertyValue, Temp);

    Temp=GetProperty(dn, CM_DRP_ENUMERATOR_NAME);
	_tcscpy(Properties[ID_ENUMERATOR_NAME].PropertyValue, Temp);

    Temp=GetProperty(dn, CM_DRP_DEVICEDESC);
	_tcscpy(Properties[ID_DEVICEDESC].PropertyValue, Temp);

    Temp=GetProperty(dn, CM_DRP_FRIENDLYNAME);
	_tcscpy(Properties[ID_FRIENDLYNAME].PropertyValue, Temp);

    Temp=GetProperty(dn, CM_DRP_DRIVER);
	_tcscpy(Properties[ID_DRIVER].PropertyValue, Temp);

    Temp=GetProperty(dn, CM_DRP_PHYSICAL_DEVICE_OBJECT_NAME);
	_tcscpy(Properties[ID_PHYSICAL_DEVPATH].PropertyValue, Temp);

    Temp=GetProperty(dn, CM_DRP_UI_NUMBER);
	_tcscpy(Properties[ID_UI_NUMBER].PropertyValue, Temp);

    Temp=GetProperty(dn, CM_DRP_UPPERFILTERS);
	_tcscpy(Properties[ID_UPPERFILTERS].PropertyValue, Temp);

    Temp=GetProperty(dn, CM_DRP_LOWERFILTERS);
    _tcscpy(Properties[ID_LOWERFILTERS].PropertyValue, Temp);
	
	Temp=GetProperty(dn, CM_DRP_BUSTYPEGUID);
	_tcscpy(Properties[ID_BUSTYPEGUID].PropertyValue, Temp);

    Temp=GetProperty(dn, CM_DRP_LEGACYBUSTYPE);
	_tcscpy(Properties[ID_LEGACYBUSTYPE].PropertyValue, Temp);

	DevicePropertiesDN dp;
	dp.dn=dn;
	memcpy(dp.Properties, Properties, sizeof(Properties));
	DeviceProperty.push_back(dp);
}


CString CDevicePropertySheetDialogDlg::GetProperty(DEVNODE dn, ULONG Property)
{
	CString Temp;
	
    TCHAR Buffer[REGSTR_VAL_MAX_HCID_LEN]=_T("");
    ULONG Type;
    ULONG Size = sizeof(Buffer);
    
	if (CM_Get_DevNode_Registry_Property_Ex(dn, Property,
							  &Type,
							  Buffer,
							  &Size,
							  0, m_hMachine) == CR_SUCCESS)
    {
		if (Type == REG_DWORD || Type == REG_MULTI_SZ || Type == REG_SZ )
		{
			if (Type == REG_DWORD)
			{
				DWORD Data = *((DWORD*)Buffer);
				wsprintf(Buffer, _T("0x%08x"), *((DWORD*) Buffer) );
			}
			else if (Type == REG_MULTI_SZ)
			{
				LPTSTR p = Buffer;
				while (_T('\0') != *p)
				{
					p += lstrlen(p);
					if (_T('\0') != *p)
					*p++ = _T(',');
				}
			}
		}
    }

	Temp=Buffer;
	return Temp;
}


void CDevicePropertySheetDialogDlg::OnDeviceProperty() 
{
	DEVNODE dn;
	
	for (int i=0; i<m_Devices.GetItemCount(); i++)
	{
		if (m_Devices.GetItemState(i, LVIS_SELECTED))	//item was selected
		{
			//AfxMessageBox(m_Devices.GetItemText(i, 0));
			dn=(DEVNODE) m_Devices.GetItemData(i);
			break;
		}
	}
	
	CString CommandLine;

	//Enumerate properties
	for (int j=0; j<DeviceProperty.size(); j++)
	{
		if (DeviceProperty[j].dn==dn)
		{
			CommandLine.Format(_T("/MachineName \"\" /DeviceID %s"),
						DeviceProperty[j].Properties[ID_DEVICEID].PropertyValue);
			
			//CommandLine.Format("/DeviceID \"%s\"",DeviceProperty[j].Properties[ID_DEVICEID].PropertyValue);
			//AfxMessageBox(CommandLine);
			break;
		}
	}
	
	PDEVICEPROPERTIES pDeviceProperties;
	HINSTANCE hInst=AfxGetInstanceHandle();
	HINSTANCE  hDevMgr = LoadLibrary(_TEXT("devmgr.dll"));		
	if (hDevMgr) 
	{
		pDeviceProperties = (PDEVICEPROPERTIES) GetProcAddress((HMODULE) hDevMgr, 
			DeviceProperties_RunDLL);
	}
	
	if (pDeviceProperties)
	{
		pDeviceProperties(m_hWnd, hInst, CommandLine.GetBuffer(0), SW_SHOW);
	}
	
}

