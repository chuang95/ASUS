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
			{ //��Щ���ǻ��IP�ĺ���
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
//		m_adoRecordSet.GetCollect("�Ա�", Sex);
//		m_strSex = (Sex == -1) ? "��" : "Ů";
//		m_Bitmap.DeleteObject();
//		
//		if (!m_adoRecordSet.GetCollect("����", m_strName)
//		 || !m_adoRecordSet.GetCollect("����", m_nAge)
//		 || !m_adoRecordSet.GetCollect("���", m_fLength)
//		 || !m_adoRecordSet.GetCollect("��������", m_dtDate)
//		 || !m_adoRecordSet.GetCollect("���ʲ�", m_cyMoney)
//		 || !m_adoRecordSet.GetCollect("�绰", m_strTel)
//		 || !m_adoRecordSet.GetChunk("����", m_Bitmap))
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
//		if (m_strSex == "��") bSex = -1;
//
//		if (!m_adoRecordSet.PutCollect("����", m_nAge)
//		 || !m_adoRecordSet.PutCollect("���", m_fLength)
//		 || !m_adoRecordSet.PutCollect("����", m_strName)
//		 || !m_adoRecordSet.PutCollect("�绰", m_strTel)
//		 || !m_adoRecordSet.PutCollect("���ʲ�", m_cyMoney)
//		 || !m_adoRecordSet.PutCollect("��������", m_dtDate)
//		 || !m_adoRecordSet.PutCollect("�Ա�", bSex))
//		{
//			AfxMessageBox("Error!");
//		}
//		return TRUE;
//	}
//}
