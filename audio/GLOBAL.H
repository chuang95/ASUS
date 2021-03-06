// declare global variables, always called by main program
// -------------------------------------------------------------------------
// declare variables
#pragma once
#include <MMSystem.h>
#define MAX_BUFFERS 3

BOOL blLogo=TRUE;
BOOL blParameterOK=FALSE; // record the user parameter is proper or not
BOOL blResult=FALSE; // record the test result is OK or ERROR

BOOL blRightCH_OK=FALSE;
BOOL blLeftCH_OK=FALSE;

BOOL blSelect_RightCH=FALSE;
BOOL blSelect_LeftCH=FALSE;

BOOL blIsVista=FALSE;

BOOL blRightCH_OK_0=TRUE;
BOOL blLeftCH_OK_0=TRUE;
BOOL blRightCH_OK_1=TRUE;
BOOL blLeftCH_OK_1=TRUE;

BOOL blPlayWavFile=FALSE;
BOOL blPlayWav_NoSound=FALSE;
BOOL blDebugOn=FALSE;
BOOL blNoAdjustRecVol=FALSE;
BOOL blAnalyze_Amp=TRUE;
BOOL blAnalyze_Freq=TRUE;
BOOL blTestRch = FALSE;
BOOL blTestLch = FALSE;

BOOL blTestMic=FALSE;
BOOL ShowVolume();
BOOL blVistaGetChVol();
BOOL blVistaMuteRch();
BOOL blVistaMuteLch();
BOOL blSet_LineOut_Rch();
BOOL blSet_LineOut_Lch();
BOOL GetVolume();
void Get_LineOut_RLch();
BOOL FillDevices();
void play();
void StartRecording();
void ProcessHeader(WAVEHDR *pHdr);
void SetStatus(LPCTSTR lpszFormat, ...);
void OpenDevice();
void CloseDevice();
void record();
void PrepareBuffers();
int MicDev;
char szDevName[10];
char szDevName2[10];
int recTime = 3;
BOOL blHDMI = FALSE;
BOOL blSpdif = FALSE;
BOOL bllnout = FALSE;

BOOL blLeft = FALSE;
BOOL blRight = FALSE;
BOOL blResMic = FALSE;


BOOL m_bRun;
HWND m_hWnd;
HWAVEIN m_hWaveIn;
WAVEFORMATEX m_stWFEX;
WAVEHDR m_stWHDR[MAX_BUFFERS];
HANDLE m_hThread;
HMMIO m_hOPFile;
MMIOINFO m_stmmIF;
MMCKINFO m_stckOut,m_stckOutRIFF;
int Cdevice;
CHAR* device[32];
WAVEINCAPS stWIC;

WORD				wMixerDevNum;
MIXERCAPS			mixCap[10];
HMIXER				hMixer;
MIXERLINE			mxl;
MIXERCONTROL		mxc;
MIXERLINECONTROLS	mxlc;
MIXERCONTROLDETAILS mxcd;
MIXERCONTROLDETAILS_UNSIGNED mxcdVolume[2];
DevList Mixer[20];
TCHAR	strStr[80];

int	iVolumeItemNo,iVolumeValue,iH_limit_percentage=80,iL_limit_percentage=10,iPercentage_globe=0;
int	iLineOutVolumeValue=80,iWaveOutVolumeValue=80,iRightVolume=50,iLeftVolume=50;
int iTestTimes=1,iInterval_time=0;
DWORD	dwVolumeValue=0;
BOOL	blMutePara;
float pMicInVolume=1.25,pMicInVolume_R=1.25,pMicInVolume_L=1.25,pLineInVolume=1.25;

/* 資料的結構 */
struct X
{
  float R,I;/* 實數部份與虛數部份 */
};

//Vista

int blMuteV=1;
unsigned int VolumeLevel=0;
unsigned int VolumeLevelCount=0;
//CComboBox DeviceCombo;
//UINT wDeviceNO=0;
//UINT wSelect=1;
CString sSelect;
CString PlayWavefileName;
int iPlayWaveTime;
bool blPlayWaveTime=false;
BOOL blWork(void);
BOOL blVistaSetChVol(void);
BOOL blSelectCH(void);
char szStr2[200];
char szRec[20] = "\\\\record.wav";
int ichannel;