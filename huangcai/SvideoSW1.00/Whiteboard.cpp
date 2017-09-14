// Whiteboard.cpp : ?作檔
//

#include "stdafx.h"
#include "Svideo-diags.h"
#include "Whiteboard.h"
#include "extern.h"

// Whiteboard 對?方塊

IMPLEMENT_DYNAMIC(Whiteboard, CDialog)

Whiteboard::Whiteboard(CWnd* pParent /*=NULL*/,int x,int y,int iwidth,int iheight)
	: CDialog(Whiteboard::IDD, pParent)
{
	m_hGLContext = NULL;
	m_GLPixelIndex = 0;


//	m_dbIdleTime = 0;

	m_iPositionX=x;
	m_iPositionY=y;
	m_iHeight=iheight;
	m_iWidth=iwidth;

	m_xRotate = 0;
	m_yRotate = 0;

	m_ScaleX = 0.5f;
	m_ScaleY = 0.5f;
	m_ScaleZ = 0.5f;

	m_fSize = 1.0;
}

Whiteboard::~Whiteboard()
{
}

void Whiteboard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Whiteboard, CDialog)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
//	ON_WM_INITMENU()
END_MESSAGE_MAP()


// Whiteboard ?息?理常式

void Whiteboard::vBuildList()
{
	glNewList(1,GL_COMPILE_AND_EXECUTE);

	float x = m_fSize;
	float xt = 5.0f;


	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);
		glColor3ub(255,0,0);
		glVertex3d( x,  x, x);
		glColor3ub(0,255,0);
		glVertex3d( x, -x, x);
		glColor3ub(0,0,255);
		glVertex3d(-x, -x, x);
		glColor3ub(255,255,0);
		glVertex3d(-x,  x, x);
	glEnd();

	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,-1.0);
		glColor3ub(255,0,0);
		glVertex3d( -x,  x, -x);
		glColor3ub(0,255,0);
		glVertex3d( -x, -x, -x);
		glColor3ub(0,0,255);
		glVertex3d(  x, -x, -x);
		glColor3ub(255,255,0);
		glVertex3d(  x,  x, -x);
	glEnd();


	glBegin(GL_POLYGON);
		glNormal3d(1.0,0.0,0.0);
		glColor3ub(255,0,0);
		glVertex3d( x, x, x);
		glColor3ub(0,255,0);
		glVertex3d( x, x, -x);
		glColor3ub(0,0,255);
		glVertex3d( x, -x, -x);
		glColor3ub(255,255,0);
		glVertex3d( x, -x, x);
	glEnd();


	glBegin(GL_POLYGON);
		glNormal3d(-1.0,0.0,0.0);
		glColor3ub(255,0,0);
		glVertex3d( -x, x, x);
		glColor3ub(0,255,0);
		glVertex3d( -x, x, -x);
		glColor3ub(0,0,255);
		glVertex3d( -x, -x, -x);
		glColor3ub(255,255,0);
		glVertex3d( -x, -x, x);
	glEnd();


	glBegin(GL_POLYGON);
		glNormal3d(0.0,-1.0,0.0);
		glColor3ub(255,0,0);
		glVertex3d( -x, -x, x);
		glColor3ub(0,255,0);
		glVertex3d( x, -x, x);
		glColor3ub(0,0,255);
		glVertex3d( x, -x, -x);
		glVertex3d( -x, -x, -x);
	glEnd();


	glBegin(GL_POLYGON);
		glNormal3d(0.0,1.0,0.0);
		glColor3ub(255,0,0);
		glVertex3d( -x, x, x);
		glColor3ub(0,255,0);
		glVertex3d( x, x, x);
		glColor3ub(0,0,255);
		glVertex3d( x, x, -x);
		glColor3ub(255,255,0);
		glVertex3d( -x, x, -x);
	glEnd();



	//glEndList();




	//glNewList(2,GL_COMPILE_AND_EXECUTE);

	//float x = m_fSize;
	//float xt = 5.0f;


	//glBegin(GL_POLYGON);
	//	glNormal3d(2.0,0.0,1.0);
	//	glColor3ub(255,0,0);
	//	glVertex3d( x,  x, x);
	//	glColor3ub(0,255,0);
	//	glVertex3d( x, -x, x);
	//	glColor3ub(0,0,255);
	//	glVertex3d(-x, -x, x);
	//	glColor3ub(255,255,0);
	//	glVertex3d(-x,  x, x);
	//glEnd();

	//glBegin(GL_POLYGON);
	//	glNormal3d(2.0,0.0,-1.0);
	//	glColor3ub(255,0,0);
	//	glVertex3d( -x,  x, -x);
	//	glColor3ub(0,255,0);
	//	glVertex3d( -x, -x, -x);
	//	glColor3ub(0,0,255);
	//	glVertex3d(  x, -x, -x);
	//	glColor3ub(255,255,0);
	//	glVertex3d(  x,  x, -x);
	//glEnd();


	//glBegin(GL_POLYGON);
	//	glNormal3d(3.0,0.0,0.0);
	//	glColor3ub(255,0,0);
	//	glVertex3d( x, x, x);
	//	glColor3ub(0,255,0);
	//	glVertex3d( x, x, -x);
	//	glColor3ub(0,0,255);
	//	glVertex3d( x, -x, -x);
	//	glColor3ub(255,255,0);
	//	glVertex3d( x, -x, x);
	//glEnd();


	//glBegin(GL_POLYGON);
	//	glNormal3d(1.0,0.0,0.0);
	//	glColor3ub(255,0,0);
	//	glVertex3d( -x, x, x);
	//	glColor3ub(0,255,0);
	//	glVertex3d( -x, x, -x);
	//	glColor3ub(0,0,255);
	//	glVertex3d( -x, -x, -x);
	//	glColor3ub(255,255,0);
	//	glVertex3d( -x, -x, x);
	//glEnd();


	//glBegin(GL_POLYGON);
	//	glNormal3d(2.0,-1.0,0.0);
	//	glColor3ub(255,0,0);
	//	glVertex3d( -x, -x, x);
	//	glColor3ub(0,255,0);
	//	glVertex3d( x, -x, x);
	//	glColor3ub(0,0,255);
	//	glVertex3d( x, -x, -x);
	//	glVertex3d( -x, -x, -x);
	//glEnd();


	//glBegin(GL_POLYGON);
	//	glNormal3d(2.0,1.0,0.0);
	//	glColor3ub(255,0,0);
	//	glVertex3d( -x, x, x);
	//	glColor3ub(0,255,0);
	//	glVertex3d( x, x, x);
	//	glColor3ub(0,0,255);
	//	glVertex3d( x, x, -x);
	//	glColor3ub(255,255,0);
	//	glVertex3d( -x, x, -x);
	//glEnd();



	glEndList();







}

void Whiteboard::vInitGL()
{
	COLORREF color = ::GetSysColor(COLOR_3DFACE);
	glClearColor((float)GetRValue(color)/255.0f,
				 (float)GetGValue(color)/255.0f,
				 (float)GetBValue(color)/255.0f,
				 1.0);

	glPolygonMode(GL_FRONT,GL_FILL);
	glPolygonMode(GL_BACK,GL_FILL);

	glShadeModel(GL_SMOOTH);

}

void Whiteboard::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPushMatrix();

	//glTranslated(0.0,0.0,-8.0);
	//glRotated(m_xRotate, 1.0, 0.0, 0.0);
	//glRotated(m_yRotate, 0.0, 1.0, 0.0);
	//glScalef(m_ScaleX,m_ScaleY,m_ScaleZ);
	//::glCallList(1);
	//glPopMatrix();


	//glPushMatrix();
	//glTranslated(-2.0,-0.0,-8.0);
	//glRotated(m_xRotate, 1.0, 0.0, 0.0);
	//glRotated(m_yRotate, 0.0, 1.0, 0.0);
	//glScalef(m_ScaleX,m_ScaleY,m_ScaleZ);
	////::glCallList(1);
	//::glCallList(1);
	//glPopMatrix();
	int iL=0;
	if(nFormNum >= 5)
		iL=nFormNum/5;
	//printf("GetSystemMetrics length is %d\n",GetSystemMetrics(SM_CXSCREEN));
	for(float i=0;i<5;i++)
	{
		for(float j=0;j<iL;j++)
		{
			glPushMatrix();
			
			glTranslated(-4.0 + 2*i,2.0-2*j,-8.0);
			glRotated(m_xRotate, 1.0, 0.0, 0.0);
			glRotated(m_yRotate, 0.0, 1.0, 0.0);
			glScalef(m_ScaleX,m_ScaleY,m_ScaleZ);
			//::glCallList(1);
			::glCallList(1);
			glPopMatrix();
		}
	}
	for(float i=0;i<(nFormNum%5);i++)
	{
		glPushMatrix();
		glTranslated(-4.0 + 2*i,2.0 - 2*iL,-8.0);
		glRotated(m_xRotate, 1.0, 0.0, 0.0);
		glRotated(m_yRotate, 0.0, 1.0, 0.0);
		glScalef(m_ScaleX,m_ScaleY,m_ScaleZ);
		//::glCallList(1);
		::glCallList(1);
		glPopMatrix();
	}
}

BOOL Whiteboard::SetWindowPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc;
	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion = 1;

	pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW | 
						PFD_SUPPORT_OPENGL |
						PFD_DOUBLEBUFFER |
						PFD_STEREO_DONTCARE;
	pixelDesc.iPixelType = PFD_TYPE_RGBA;
	pixelDesc.cColorBits = 32;
	pixelDesc.cRedBits = 8;
	pixelDesc.cRedShift = 16;
	pixelDesc.cGreenBits = 8;
	pixelDesc.cGreenShift = 8;
	pixelDesc.cBlueBits = 8;
	pixelDesc.cBlueShift = 0;
	pixelDesc.cAlphaBits = 0;
	pixelDesc.cAlphaShift = 0;
	pixelDesc.cAccumBits = 64;
	pixelDesc.cAccumRedBits = 16;
	pixelDesc.cAccumGreenBits = 16;
	pixelDesc.cAccumBlueBits = 16;
	pixelDesc.cAccumAlphaBits = 0;
	pixelDesc.cDepthBits = 32;
	pixelDesc.cStencilBits = 8;
	pixelDesc.cAuxBuffers = 0;
	pixelDesc.iLayerType = PFD_MAIN_PLANE;
	pixelDesc.bReserved = 0;
	pixelDesc.dwLayerMask = 0;
	pixelDesc.dwVisibleMask = 0;
	pixelDesc.dwDamageMask = 0;

	m_GLPixelIndex = ChoosePixelFormat(hDC,&pixelDesc);
	if(m_GLPixelIndex==0) // Choose default
	{
		m_GLPixelIndex = 1;
		if(DescribePixelFormat(hDC,m_GLPixelIndex,sizeof(PIXELFORMATDESCRIPTOR),&pixelDesc)==0)
			return FALSE;
	}
	if(SetPixelFormat(hDC,m_GLPixelIndex,&pixelDesc)==FALSE)
		return FALSE;

	return TRUE;
} 
BOOL Whiteboard::CreateViewGLContext(HDC hDC)
{
	m_hGLContext = wglCreateContext(hDC);

	if(m_hGLContext==NULL)
		return FALSE;

	if(wglMakeCurrent(hDC,m_hGLContext)==FALSE)
		return FALSE;

	return TRUE;
}

BOOL Whiteboard::OnInitDialog()
{
	this->ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);
	g_hwnd[0] = m_hWnd;
     //CRect rs;
     //CpuDlg.Create(IDD_FORMVIEW,this);
     //this->GetClientRect(&rs);
     //CpuDlg.MoveWindow(&rs);
     //CpuDlg.ShowWindow(true);
	return CDialog::OnInitDialog();  
}


// Whiteboard 對?方塊
int Whiteboard::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此加入特別建立的程式碼


	HWND hWnd = GetSafeHwnd();
	HDC hDC = ::GetDC(hWnd);

	GLsizei width,height;
	GLdouble aspect;

	if(SetWindowPixelFormat(hDC)==FALSE)
		return 0;
	
	if(CreateViewGLContext(hDC)==FALSE)
		return 0;

	COLORREF color = ::GetSysColor(COLOR_3DFACE);
	glClearColor((float)GetRValue(color)/255.0f,
				 (float)GetGValue(color)/255.0f,
				 (float)GetBValue(color)/255.0f,
				 1.0);
	glPolygonMode(GL_FRONT,GL_FILL);
	glPolygonMode(GL_BACK,GL_FILL);

	// Gouraud
	glShadeModel(GL_SMOOTH);
	vBuildList();
	SetTimer(0,10,NULL);
	width = m_iWidth;
	height = m_iHeight;

	aspect = (GLdouble)width/(GLdouble)height;

	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,aspect,1,10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glDrawBuffer(GL_BACK);

	glEnable(GL_DEPTH_TEST);

	::ReleaseDC(hWnd,hDC);

	return 0;
}

void Whiteboard::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	 //TODO: 在此加入您的?息?理常式程式碼
	 //不要呼叫圖片?息的 CDialog::OnPaint() 
	RenderScene();
	SwapBuffers(dc.m_ps.hdc);

}
//BOOL Whiteboard::PreCreateWindow(CREATESTRUCT& cs)
//{
//    //if( !Whiteboard::PreCreateWindow(cs) )
//    //    return FALSE;
//    //// TODO: 在此处通过修改
//    ////  CREATESTRUCT cs 来修改窗口类或样式
//    //cs.cx = 1000;
//    //cs.cy = 1000;
//    ////cs.style &= ~WS_MAXIMIZEBOX;//禁止最大化
//    ////cs.style &= ~WS_THICKFRAME;//禁止调整大小
//    ////cs.style &= ~WS_MINIMIZEBOX;禁止最小化
//    //cs.lpszName = "算法收集器";
//if(   !Whiteboard::PreCreateWindow(cs)   )   
//  return   FALSE;   
//  //   TODO:   Modify   the   Window   class   or   styles   here   by   modifying   
//  //     the   CREATESTRUCT   cs
//int m_iXScreen,m_iYScreen;
//  m_iXScreen   =   GetSystemMetrics(SM_CXSCREEN);   
//  m_iYScreen   =   GetSystemMetrics(SM_CYSCREEN);   
//  ASSERT(m_iXScreen   >   0   &&   m_iYScreen   >   0);   
//    
//  //设置界面初始状态值   
//  cs.x   =   5;   
//  cs.y   =   5;   
//  cs.cx   =   m_iXScreen   -   10;   
//  cs.cy   =   m_iYScreen   -   35;   
//  cs.dwExStyle   &=   ~WS_EX_CLIENTEDGE;   
//  cs.lpszClass   =   AfxRegisterWndClass(0);   
//    return TRUE;
//}
void Whiteboard::OnShowWindow(BOOL bShow, UINT nStatus)
{

	MoveWindow(0/*m_iPositionX*/,0/*m_iPositionY*/,m_iWidth,m_iHeight,TRUE);
	//MoveWindow(0,0,1000,1000,TRUE);
	// TODO: 在此加入您的?息?理常式程式碼
	//printf("%d,%d,%d,%d",m_iPositionX,m_iPositionY,m_iWidth,m_iHeight);

	CDialog::OnShowWindow(bShow, nStatus);

}

void Whiteboard::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此加入您的?息?理常式程式碼和 (或) 呼叫預設值
	m_yRotate -= 3;
	m_xRotate -= 2;
	//RenderScene();
	InvalidateRect(NULL,FALSE);

	//blShowCPU();
	CDialog::OnTimer(nIDEvent);
}

void Whiteboard::OnOK()
{
	// TODO: 在此加入特定的程式碼和 (或) 呼叫基底?別
	::SendMessage(::GetParent(m_hWnd),WM_CLOSE,0,0);
	CDialog::OnOK();
}

void Whiteboard::OnCancel()
{
	// TODO: 在此加入特定的程式碼和 (或) 呼叫基底?別
	::SendMessage(g_hwnd[3],WM_CLOSE,0,0);
	::SendMessage(g_hwnd[2],WM_CLOSE,0,0);
	::SendMessage(g_hwnd[1],WM_CLOSE,0,0);
	CDialog::OnCancel();
}


