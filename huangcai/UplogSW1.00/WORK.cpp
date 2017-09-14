#include "stdafx.h"
#include "Uplog-diags.h"
#include "extern.h"


void CheckIP(void) 
{
	WSADATA wsaData;
	char name[155];
	char *ip;
	PHOSTENT hostinfo; 
	if ( WSAStartup( MAKEWORD(2,0), &wsaData ) == 0 )
	{ 
		if( gethostname ( name, sizeof(name)) == 0) 
		{ 
			if((hostinfo = gethostbyname(name)) != NULL)
			{ //这些就是获得IP的函数
				ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list); 
				printf("Server ip:%s\n",ip);
			} 
		} 
		WSACleanup( );
	}
} 
LONG64 l64GetTime()
{
	SYSTEMTIME st;
	FILETIME ft;
	GetSystemTime(&st);
	SystemTimeToFileTime(&st,&ft);
	return ((LONG64)ft.dwHighDateTime<<32)+ft.dwLowDateTime;
}
//BOOL CMyAdoDlg::UpdateRecord(BOOL bLoad)
//{
//	if (m_adoRecordSet.GetRecordCount() < 1) return FALSE;
//	if (bLoad)
//	{
//		int Sex;
//		m_adoRecordSet.GetCollect("性别", Sex);
//		m_strSex = (Sex == -1) ? "男" : "女";
//		m_Bitmap.DeleteObject();
//		
//		if (!m_adoRecordSet.GetCollect("姓名", m_strName)
//		 || !m_adoRecordSet.GetCollect("年龄", m_nAge)
//		 || !m_adoRecordSet.GetCollect("身高", m_fLength)
//		 || !m_adoRecordSet.GetCollect("出生年月", m_dtDate)
//		 || !m_adoRecordSet.GetCollect("总资产", m_cyMoney)
//		 || !m_adoRecordSet.GetCollect("电话", m_strTel)
//		 || !m_adoRecordSet.GetChunk("玉照", m_Bitmap))
//		{
//			;
//		}
//		CRect rect(370, 100, 500, 260);
//		InvalidateRect(rect);
//
//		m_lPostion = m_adoRecordSet.GetAbsolutePosition();
//		UpdateData(FALSE);
//		return TRUE;
//	}
//	else
//	{
//		if (!UpdateData()) return FALSE;
//		int bSex = 0;
//		if (m_strSex == "男") bSex = -1;
//
//		if (!m_adoRecordSet.PutCollect("年龄", m_nAge)
//		 || !m_adoRecordSet.PutCollect("身高", m_fLength)
//		 || !m_adoRecordSet.PutCollect("姓名", m_strName)
//		 || !m_adoRecordSet.PutCollect("电话", m_strTel)
//		 || !m_adoRecordSet.PutCollect("总资产", m_cyMoney)
//		 || !m_adoRecordSet.PutCollect("出生年月", m_dtDate)
//		 || !m_adoRecordSet.PutCollect("性别", bSex))
//		{
//			AfxMessageBox("Error!");
//		}
//		return TRUE;
//	}
//}
