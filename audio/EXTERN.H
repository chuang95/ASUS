// declare external variables, same as GLOBAL.H, called by procedure program
// -------------------------------------------------------------------------

#pragma once
#include <MMSystem.h>
#define MAX_BUFFERS 3

extern BOOL blLogo;
extern BOOL blParameterOK;
extern BOOL blResult;

extern BOOL blRightCH_OK;
extern BOOL blLeftCH_OK;

extern BOOL blSelect_RightCH;
extern BOOL blSelect_LeftCH;

extern BOOL blIsVista;

extern BOOL blRightCH_OK_0;
extern BOOL blLeftCH_OK_0;
extern BOOL blRightCH_OK_1;
extern BOOL blLeftCH_OK_1;

extern BOOL blPlayWavFile;
extern BOOL blPlayWav_NoSound;
extern BOOL blDebugOn;
extern BOOL blNoAdjustRecVol;

extern BOOL blLeft;
extern BOOL blRight;
extern BOOL blResMic;

extern BOOL blTestMic;

extern void Get_LineOut_RLch();
extern WORD				wMixerDevNum;
extern MIXERCAPS			mixCap[10];
extern HMIXER				hMixer;
extern MIXERLINE			mxl;
extern MIXERCONTROL		mxc;
extern MIXERLINECONTROLS	mxlc;
extern MIXERCONTROLDETAILS mxcd;
extern MIXERCONTROLDETAILS_UNSIGNED mxcdVolume[2];
extern DevList Mixer[20];
extern TCHAR	strStr[80];

extern int	iVolumeItemNo,iVolumeValue,iH_limit_percentage,iL_limit_percentage,iPercentage_globe;
extern int iTestTimes,iInterval_time;
extern int	iLineOutVolumeValue,iWaveOutVolumeValue,iRightVolume,iLeftVolume;
extern DWORD  dwVolumeValue;
extern BOOL	 blMutePara;
extern float pMicInVolume,pMicInVolume_R,pMicInVolume_L,pLineInVolume;
/* 戈挡篶 */
extern struct X
{
  float R,I;/* 龟计场籔店计场 */
};


//Vista
extern int blMuteV;

extern BOOL blHDMI;
extern BOOL blSpdif;
extern BOOL bllnout;

extern unsigned int VolumeLevel;
extern unsigned int VolumeLevelCount;
//extern CComboBox DeviceCombo;
//UINT wDeviceNO=0;
//UINT wSelect=1;
extern CString sSelect;
extern CString PlayWavefileName;
extern int iPlayWaveTime;
extern bool blPlayWaveTime;
extern BOOL blWork(void);
extern BOOL blVistaSetChVol(void);
extern BOOL blSelectCH(void);
extern BOOL ShowVolume();
extern BOOL blVistaGetChVol();
extern BOOL GetVolume();

extern void Get_LineOut_RLch();
extern BOOL FillDevices();
extern void StartRecording();
extern void ProcessHeader(WAVEHDR *pHdr);
extern void SetStatus(LPCTSTR lpszFormat, ...);
extern void OpenDevice();
extern void CloseDevice();
extern void PrepareBuffers();
extern BOOL blVistaMuteRch();
extern BOOL blVistaMuteLch();
extern BOOL blSet_LineOut_Rch();
extern BOOL blSet_LineOut_Lch();
extern void record();
extern void play();
extern int recTime;
extern int MicDev;
extern char szDevName[10];
extern char szDevName2[10];

extern BOOL m_bRun;
extern HWND m_hWnd;
extern HWAVEIN m_hWaveIn;
extern WAVEFORMATEX m_stWFEX;
extern WAVEHDR m_stWHDR[MAX_BUFFERS];
extern HANDLE m_hThread;
extern HMMIO m_hOPFile;
extern MMIOINFO m_stmmIF;
extern MMCKINFO m_stckOut,m_stckOutRIFF;
extern int Cdevice;
extern CHAR* device[32];
extern WAVEINCAPS stWIC;
extern char szStr2[200];
extern int ichannel;
extern BOOL blTestRch;
extern BOOL blTestLch;
//extern char *path;