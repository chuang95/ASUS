// include the header file
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <process.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mmsystem.h>

//Vista

#include <Mmdeviceapi.h>
#include <Propidl.h>
#include <Devicetopology.h>
#include <Endpointvolume.h>
#include <Devicetopology.h>
#include <propkey.h>
#include <FunctionDiscoveryKeys_devpkey.h>
#include "Audioclient.h"



typedef struct 
{
	HMIXER	hMixer;
	TCHAR	strName[80];
	DWORD	dwVolumeMax;
	DWORD	dwVolumeMin;
	DWORD	dwControlType1;
	DWORD	dwControlType2;
	DWORD	dwControlType3;
	DWORD	dwControlMuteType;
	DWORD	dwControlID;
	DWORD	dwMuteControlID;
	DWORD	dwChannels;
	DWORD	dwVolumeValue1;
	DWORD	dwVolumeValue2;
	BOOL	blMute;
	BOOL	blMuteEnable;
	BOOL	blVolumeEnable;
	BOOL	blLR;
	int		iSourceNum;
	HWND	hTrackBarL;
	HWND	hTrackBarR;
	HWND	hMute;
	HWND	hLR;
	int		iLRID;
	int		iMuteID;
	int		iTrackBarIDL;
	int		iTrackBarIDR;
	int		iLX,iLY;
	int		iRX,iRY;
}DevList, *LPDevList;


// declare the procedure name
void ReadMe(void);
void Logo(void);
void End(int ReturnCode);
void ReadMe4Debug(void);

BOOL Analyze_Wav(void);
BOOL Analyze_Wave_Freq(void);
BOOL blPlay_Rec_Wavfile(void);
BOOL blPlay_Wavfile(void);
BOOL blPlay_0to9_Wavfile(int playindex);
BOOL blRandom0to9_presskey(void);
BOOL SelectLineIn_Rec();
BOOL UnMuteLineIn_Rec();
BOOL MuteLineIn_Rec();
BOOL SetLineInVolume_Rec();
BOOL SetLineInVolumeRight_Rec();
BOOL SetLineInVolumeLeft_Rec();
BOOL SelectMic_Rec();
BOOL UnMuteMic_Rec();
BOOL MuteMic_Rec();
BOOL SetMicVolume_Rec();
BOOL SetMicVolumeRight_Rec();
BOOL SetMicVolumeLeft_Rec();
BOOL SelectRecording_Rec();
BOOL UnMuteRecording_Rec();
BOOL blGetControl(LPDevList dl);
BOOL blGetVolumeValue(LPDevList dl);
BOOL blSetVolumeValue(LPDevList dl);
BOOL blGetMuteStatus(LPDevList dl);
BOOL blSetMuteStatus(LPDevList dl);
void CloseControl(LPDevList dl);
void GetAudioControl(void);
int iGetLineInItemNo(void);
int iGetWaveOutItemNo(void);
int iGetPcBeepItemNo(void);
int iGetMicInItemNo(void);
BOOL blUnMute_LineOut_RLch(void);
BOOL blSet_LineOut_RLch(void);
BOOL blUnMute_LineOut_RLch_80percent(void);
BOOL blMute_LineOut_Rch(void);
BOOL blMute_LineOut_Lch(void);
BOOL blMute_WaveOut_RLch(void);
BOOL blUnMute_WaveOut_RLch(void);
BOOL blSet_WaveOut_RLch(void);
BOOL blMute_PcBeep_RLch(void);
BOOL blUnMute_PcBeep_RLch(void);
BOOL blMute_MicIn_ch(void);
BOOL blMute_LineIn_RLch(void);
BOOL blUnMute_LineIn_RLch(void);
BOOL blMute_LineIn_Rch(void);
BOOL blMute_LineIn_Lch(void);
BOOL blUnMuteSPDIF_OUT(void);
BOOL blMuteSPDIF_OUT(void);
BOOL blSet_LineIn_RLch(void);
BOOL blSet_MicIn_RLch(void);
/* 由檔案讀出資料 */
void text2data(char *filename,struct X *indata,int size);
/* 將資料做FFT運算 */
void FFT(struct X *indata,struct X *outdata,int size);
/* 資料備份 */
void copy_data(struct X *s,struct X *t,int size);
/* 將資料做FFT計算前的交換位置 */
void swap_data(struct X *data,int size);
/* 計算交換的次序排列 */
void count_swap(int *s,int size);
/* 將資料存入檔案 */
void data2text(char *filename,struct X *outdata,int size);


// Vista

int EnumerateVolumeDevices();

int blSetMute();
int blSetVolume(int Volume);

int InitialVolumeDevices();