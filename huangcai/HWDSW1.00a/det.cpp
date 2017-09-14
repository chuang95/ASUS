// det.cpp : 實作檔
//

#include "stdafx.h"
#include "HWD-diags.h"
#include "det.h"
#include "Dbt.h"
#include "setupapi.h"
#include "extern.h"


// Cdet 對話方塊

IMPLEMENT_DYNAMIC(Cdet, CDialog)

Cdet::Cdet(CWnd* pParent /*=NULL*/)
	: CDialog(Cdet::IDD, pParent)
{

}

Cdet::~Cdet()
{
}

void Cdet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Cdet, CDialog)
//	ON_WM_SHOWWINDOW()
//ON_WM_SHOWWINDOW()
ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()



BOOL Cdet::OnInitDialog()
{
	//CDialog::OnInitDialog();
	//this->ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);
	//WINDOWPLACEMENT   wp;   
	//wp.length=sizeof(WINDOWPLACEMENT);   
	//wp.flags=WPF_RESTORETOMAXIMIZED;   
	//wp.showCmd=SW_HIDE;   
	//SetWindowPlacement(&wp);   
	static const GUID GUID_DEVINTERFACE_LIST[] = 
	{
		// GUID_DEVINTERFACE_USB_DEVICE
		{ 0xA5DCBF10, 0x6530, 0x11D2, { 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED } },
		// GUID_DEVINTERFACE_DISK
		{ 0x53f56307, 0xb6bf, 0x11d0, { 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b } },
		// GUID_DEVINTERFACE_HID, 
		{ 0x4D1E55B2, 0xF16F, 0x11CF, { 0x88, 0xCB, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30 } },
		// GUID_NDIS_LAN_CLASS
		{ 0xad498944, 0x762f, 0x11d0, { 0x8d, 0xcb, 0x00, 0xc0, 0x4f, 0xc3, 0x35, 0x8c } }
	};

	HDEVNOTIFY hDevNotify;
    DEV_BROADCAST_DEVICEINTERFACE NotificationFilter;
    ZeroMemory( &NotificationFilter, sizeof(NotificationFilter) );
    NotificationFilter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
    NotificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	for(int i=0; i<sizeof(GUID_DEVINTERFACE_LIST)/sizeof(GUID); i++) {
		NotificationFilter.dbcc_classguid = GUID_DEVINTERFACE_LIST[i];
		hDevNotify = RegisterDeviceNotification(this->GetSafeHwnd(), &NotificationFilter, DEVICE_NOTIFY_WINDOW_HANDLE);
		if( !hDevNotify ) {
			printf("Can't register device notification:");
			return FALSE;
		}
	}
					//	do
//{
// //HWND hwnd;
// int WM_DRIVEADD=0x0401;
///*#define */int WM_DRIVEREMOVE=0x0402;//WM_DRIVEADD + 1;
////#define 
//long DRIVEREMOVED;
//DRIVEREMOVED = 0x00000080;//
// SHChangeNotifyEntry *tmp;//=new SHChangeNotifyEntry();
//
// ULONG l=SHChangeNotifyRegister(this->GetSafeHwnd(),0x0002,DRIVEREMOVED,WM_DRIVEREMOVE,1,tmp);
// //printf("%08X\n",l);
//}//while(1);
	return TRUE;  
}

LRESULT Cdet::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类

	if ( DBT_DEVICEARRIVAL == wParam || DBT_DEVICEREMOVECOMPLETE == wParam ) 
	{
		PDEV_BROADCAST_HDR pHdr = (PDEV_BROADCAST_HDR)lParam;
		PDEV_BROADCAST_DEVICEINTERFACE pDevInf;
		PDEV_BROADCAST_HANDLE pDevHnd;
		PDEV_BROADCAST_OEM pDevOem;
		PDEV_BROADCAST_PORT pDevPort;
		PDEV_BROADCAST_VOLUME pDevVolume;
		printf("pHdr->dbch_devicetype = %08X\n",pHdr->dbch_devicetype);
		
		switch( pHdr->dbch_devicetype ) {
			case DBT_DEVTYP_DEVICEINTERFACE:
				printf("pHdr->dbch_devicetype = %08X\n",pHdr->dbch_devicetype);
				pDevInf = (PDEV_BROADCAST_DEVICEINTERFACE)pHdr;
					blUSBDet=true;
					blFCR=true;
				//UpdateDevice(pDevInf, wParam);
				break;

			case DBT_DEVTYP_HANDLE:
				pDevHnd = (PDEV_BROADCAST_HANDLE)pHdr;
				break;

			case DBT_DEVTYP_OEM:
				pDevOem = (PDEV_BROADCAST_OEM)pHdr;
				break;

			case DBT_DEVTYP_PORT:
				pDevPort = (PDEV_BROADCAST_PORT)pHdr;
				break;

			case DBT_DEVTYP_VOLUME:
				pDevVolume = (PDEV_BROADCAST_VOLUME)pHdr;
				blCDDet=true;
				break;
		}
	}
	return CDialog::WindowProc(message, wParam, lParam);
}


void Cdet::OnOK()
{
	//CDialog::OnOK();
}

void Cdet::OnCancel()
{

	//CDialog::OnCancel();
}

void Cdet::OnShowWindow(BOOL bShow, UINT nStatus)
{

	long style = ::GetWindowLong(*this, GWL_STYLE);
	::SetWindowLong(*this, GWL_STYLE, style | WS_VISIBLE);
	CDialog::OnShowWindow(SW_HIDE, nStatus);

	//CDialog::OnShowWindow(bShow, nStatus);

}
