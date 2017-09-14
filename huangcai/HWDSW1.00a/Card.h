// DevicePropertySheetDialogDlg.h : header file
//

#if !defined(AFX_DEVICEPROPERTYSHEETDIALOGDLG_H__5CFD3355_6368_4AEF_9468_0008AE77B8E1__INCLUDED_)
#define AFX_DEVICEPROPERTYSHEETDIALOGDLG_H__5CFD3355_6368_4AEF_9468_0008AE77B8E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//define function pointer
typedef VOID (CALLBACK *FuncProc) (HWND, HINSTANCE, LPSTR, int); 

/////////////////////////////////////////////////////////////////////////////
// CDevicePropertySheetDialogDlg dialog


/////////////////////////////////////////////////////////////////////////////
// CDevicePropertySheetDialogDlg dialog
#include "SetupAPI.h"
#include "cfgmgr32.h"
#include "windows.h"
#include <vector>
#include "Resource.h"
using namespace std;

// DevicePropertySheetDialogDlg.h : header file
//



typedef struct _tagDeviceProperties
{
	int ID;
	TCHAR Property[100];
	TCHAR PropertyValue[500];
} DeviceProperties;

typedef struct _tagDevicePropertiesDN
{
	DEVNODE dn;
	DeviceProperties Properties[26];
} DevicePropertiesDN;


class CDevicePropertySheetDialogDlg : public CDialog
{
// Construction
public:
	void EnumDeviceProperties(DEVNODE dn);
	CString GetProperty(DEVNODE dn, ULONG Property);
	CString GetDeviceName(DEVNODE DevNode);
	void RetrieveSubNodes(DEVINST parent, DEVINST sibling, DEVNODE dn);
	void EnumDevices();
	afx_msg void OnDeviceProperty();
	CDevicePropertySheetDialogDlg();	// standard constructor
	
	HMACHINE m_hMachine;
	SP_CLASSIMAGELIST_DATA m_ImageListData;
	CImageList m_ImageList;
	vector<DevicePropertiesDN> DeviceProperty;

// Dialog Data
	//{{AFX_DATA(CDevicePropertySheetDialogDlg)
	enum { IDD = IDD_DEVICEPROPERTYSHEETDIALOG_DIALOG };
	CListCtrl	m_Devices;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDevicePropertySheetDialogDlg)
	protected:
	//virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDevicePropertySheetDialogDlg)
	//virtual BOOL OnInitDialog();
	//afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnDestroy();
	//}}AFX_MSG
	//DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEVICEPROPERTYSHEETDIALOGDLG_H__5CFD3355_6368_4AEF_9468_0008AE77B8E1__INCLUDED_)
