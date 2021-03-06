// AUDIO-diags.exe, Copyright by PEGATRON
//--------------------------------------------------------------------------
/*
//-----------------------------------------------------------------------------
Rev1.00: Mar 25, 2009: Patrick Kuo
	 1. Modified from Waudio.exe Rev1.06 and add function as Waudio.exe Rev1.10 
	 2. first release the program
//-----------------------------------------------------------------------------
*/
//--------------------------------------------------------------------------


// AUDIO-diags.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "AUDIO-diags.h"
#include "global.h"
#include "windows.h"
#include "conio.h"
#include "devicetopology.h"

void gotoxy(int x, int y)
{
  COORD c;
 
  c.X = x - 1;
  c.Y = y - 1;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//--------------------------------------------------------------------------
void Logo(void)
{
  system("cls");
  cprintf("                              Audio diagnostic Utility\n");
  cprintf("              Copyright by Pegatron, Build Date:2009-06-01 Rev1.01d  ");
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
  cprintf("Diagnostics");
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
  cprintf("================================================================================");
  

  
}
//--------------------------------------------------------------------------
void ReadMe(void)
{
  //int i;

  //Logo();
  printf(" /?: show usage\n\r");
  printf("  -1: Analyze Time domain signal , -2: Analyze Frequency domain signal\n\r");
  printf("  -H/-L: Upper/Lower limit tolerance (%) (default: 80%/10%)\n\r");
  printf("  -RCH/-LCH: SET Right/Left Channel volume (%) (default: 50%/50%)\n\r");
  printf("  -N:  Set times for testing speaker function\n\r");
  printf("  -TI: Set time interval(ms) of playing sound\n\r");
  printf(" /LNOUT2MIC: Diagnosing Line-out to Mic-in audio\n\r");
  printf(" /SETWV: Control wave volume, /GETLNOUT: Get line out volume.\n\r");
  printf(" /LRT: Test Left or Right channel, /GETWV: Get wave volume.\n\r");
  printf(" /LNOUT2LNIN: diagnosing Line-out to Line-in audio\n\r");
  printf(" /SPDIF2MIC: diagnosing SPDIF-out to Mic-in audio\n\r");
  printf(" /PCBEEP2MIC: diagnosing PC Beep to Mic-in audio\n\r");
  printf(" /REC:  record sound. /PLREC: play the recorded sound\n\r");
  printf("  -left: set Microphone left channel, -right:set Microphone Right channel\n\r");
  printf(" /TSP: test speaker function, /UNMUTESPDIF: Unmute SPDIF out\n\r");
 // printf(" /SETWV: Control wave volume\n\r");
  printf(" /SETLNOUT: Set Line out volume, /SETWAVOUT: Set Wave out volume\n\r");
  printf(" /SETLINEIN: Set Line in volume, /SETMICIN: Set Mic in volume\n\r");
  printf(" /SETLINEIN_REC: Set Line in REC volume, /SETMICIN_REC: Set Mic in REC volume\n\r");
  //printf(" /TESTMIC: diagnosing Mic in function\n\r");
  printf(" /PLAY: Play the wave file\n\r");
  printf("  -s <sec>: Setting time in seconds to play the wave file.\n\r");
 // printf("Ex:\n\r");
  //printf("  Audio-diags.exe -RCH -N 3 /TSP -> test RCH speaker function\n\r");
  //printf("  Audio-diags.exe -RCH 50 -LCH 50 /SETLNOUT -> adjust Line_out,RCH=50%,LCH=50%\n\r");
  End(255);

}

void ReadMe4Debug(void)
{
//  int i;

  //Logo();

  printf("/?: show usage\n\r");
  printf("-DB: Debug \n\r");
  printf("-1: Analyze Time domain signal \n\r");
  printf("-2: Analyze Frequency domain signal \n\r"); 
  printf("-NORV: don't adjust REC volume\n\r");
  printf("-H: High limit tolerance (%%) (default: 80%%) \n\r");
  printf("-L: Low limit tolerance (%%) (default: 10%%) \n\r"); 
  printf("-RCH: SET Right CH volume (%%) (default: 50%%) , -VISTA: for Vista OS\n\r");
  printf("-LCH: SET Left CH volume (%%) (default: 50%%) \n\r");
  printf("-LNOUTVOL: SET Line-Out volume (%%) (default: 80%%) \n\r");
  printf("-WAVOUTVOL: SET Wave-Out volume (%%) (default: 80%%) \n\r");
  printf("-MICREC: SET Mic-in rec volume (%%) (default: 80%%) \n\r");
  printf("-LINREC: SET Line-in rec volume (%%) (default: 80%%) \n\r"); 
  printf("-N: set times for testing speaker function\n\r");
  printf("-TI: set time interval(ms) of playing sound\n\r");
  printf("/LNOUT2MIC: diagnosing Line-out to Mic-in audio\n\r");
  printf("/LNOUT2LNIN:  diagnosing Line-out to Line-in audio\n\r");
  printf("/SPDIF2MIC: diagnosing SPDIF-out to Mic-in audio\n\r");
  printf("/PCBEEP2MIC: diagnosing PC Beep to Mic-in audio\n\r");
  printf("/TSP:  test speaker function , /UNMUTESPDIF: Unmute SPDIF out\n\r");
  printf("/SETLNOUT:  Set Line out volume , /SETWAVOUT:  Set Wave out volume \n\r");
  printf("/SETLINEIN:  Set Line in volume , /SETMICIN:  Set Mic in volume \n\r");
  printf("/SETLINEIN_REC:  Set Line in REC volume , /SETMICIN_REC:  Set Mic in REC volume \n\r");

  
  End(255);

}

//--------------------------------------------------------------------------
void End(int ReturnCode)
{
//  char buf[80];
  gotoxy(1,23);		
  printf("\n                              Return_Code = %d", ReturnCode);
  
  exit(ReturnCode);

}
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
bool GetOSVersion()
{ 
	OSVERSIONINFO osvi; 
    memset(&osvi, 0, sizeof(OSVERSIONINFO)); 
    osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO); 
    GetVersionEx (&osvi); 
	if( (osvi.dwMajorVersion == 6) && (osvi.dwMinorVersion >= 0) )	//only can use OS version > 6.0//vista,server 2008
 	{
		return true;	
	}
	else
	{
		return false;
	}
}
//-------------------------------------------------------------------------

int _tmain(int argc, _TCHAR* argv[])
{



  int i,retry;

  if(GetOSVersion())
  {
	blIsVista=TRUE;
  }

  //KSJACK_DESCRIPTION des;


  // begin handle the user interface
  // handle switch(-) parameter
  for(i=0; i<(argc-1); i++) {
    if(stricmp(argv[i+1], "-nl")==0) {
      blLogo=FALSE;
	  continue;
    }
    if(stricmp(argv[i+1], "-db")==0) {
      blDebugOn=TRUE;
	  continue;
    }
    if(stricmp(argv[i+1], "-norv")==0) {
      blNoAdjustRecVol = TRUE;
	  continue;
    }

	if(stricmp(argv[i+1], "-1")==0) {
      blAnalyze_Amp=TRUE;
      blAnalyze_Freq=FALSE;
	  continue;
    }

	if(stricmp(argv[i+1], "-2")==0) {
      blAnalyze_Amp=FALSE;
      blAnalyze_Freq=TRUE;
	  continue;
    }
	
    if(stricmp(argv[i+1], "-h")==0) {
      iH_limit_percentage= atoi(argv[i+2]);
	  if(iH_limit_percentage >= 100) iH_limit_percentage=100; 
      if(iH_limit_percentage <= 0) iH_limit_percentage=0; 
	  continue;
    }
    if(stricmp(argv[i+1], "-l")==0) {
      iL_limit_percentage= atoi(argv[i+2]);
      if(iL_limit_percentage >= 100) iL_limit_percentage=100; 
      if(iL_limit_percentage <= 0) iL_limit_percentage=0; 
	  continue;
    }
    if(stricmp(argv[i+1], "-micrec")==0) {
      pMicInVolume= atoi(argv[i+2]);
      if(pMicInVolume >= 100.0) pMicInVolume=100.0; 
      if(pMicInVolume <= 0.0) pMicInVolume=1; 
      pMicInVolume=1/(pMicInVolume/100.0);
      continue;
    }
    if(stricmp(argv[i+1], "-linrec")==0) {
      pLineInVolume= atoi(argv[i+2]);
	  if(pLineInVolume >= 100.0) pLineInVolume=100.0; 
      if(pLineInVolume <= 0.0) pLineInVolume=1; 
	  pLineInVolume=1/(pLineInVolume/100.0);
      continue;
    }
    if(stricmp(argv[i+1], "-lnoutvol")==0) {
      iLineOutVolumeValue= atoi(argv[i+2]);
	  if(iLineOutVolumeValue >= 100) iLineOutVolumeValue=100; 
      if(iLineOutVolumeValue <= 0) iLineOutVolumeValue=1; 
	  continue;
    } 
    if(stricmp(argv[i+1], "-wavoutvol")==0) {
      iWaveOutVolumeValue= atoi(argv[i+2]);
	  if(iWaveOutVolumeValue >= 100) iWaveOutVolumeValue=100; 
      if(iWaveOutVolumeValue <= 0) iWaveOutVolumeValue=1; 
	  continue;
    }

	if(stricmp(argv[i+1], "-vista")==0) {
      blIsVista=TRUE;
	  continue;
    } 
    
    if(stricmp(argv[i+1], "-rch")==0) {
      iRightVolume= atoi(argv[i+2]);
	  if(iRightVolume >= 100) iRightVolume=100; 
      if(iRightVolume <= 0) iRightVolume=0; 

	  if(blIsVista==TRUE) blSelect_RightCH=TRUE;
	  continue;
    } 
    if(stricmp(argv[i+1], "-lch")==0) {
      iLeftVolume= atoi(argv[i+2]);
	  if(iLeftVolume >= 100) iLeftVolume=100; 
      if(iLeftVolume <= 0) iLeftVolume=0; 

	  if(blIsVista==TRUE) blSelect_LeftCH=TRUE;
	  continue;
    }
	if(stricmp(argv[i+1], "-n")==0) {
      iTestTimes= atoi(argv[i+2]);
      if(iTestTimes <= 0) iTestTimes=1; 
	  continue;
    }
    if(stricmp(argv[i+1], "-ti")==0) {
      iInterval_time= atoi(argv[i+2]);
      if(iInterval_time <= 0) iInterval_time=1; 
	  continue;
    } 

	    if(stricmp(argv[i+1], "-left")==0) {
        blLeft = TRUE;
	  continue;
    } 
		if(stricmp(argv[i+1], "-right")==0) {
        blRight = TRUE;
	  continue;
    }
	  if(stricmp(argv[i+1], "-resmic")==0) {
      blResMic = TRUE;
	  continue;
    } 

	  if(stricmp(argv[i+1], "-t")==0) 
	  {
          recTime = atoi(argv[i+2]);
		  continue;
    } 

	if(stricmp(argv[i+1], "-s")==0) 
	{
      blPlayWaveTime=true;
      iPlayWaveTime= atoi(argv[i+2]);
      continue;
    }

  }

  if(blLogo) Logo(); // display Logo

  // handle command(/) parameter
  for(i=0; i<(argc-1); i++) {
    // display readme
    if(stricmp(argv[i+1], "?")==0  ||\
       stricmp(argv[i+1], "/?")==0 ||\
       stricmp(argv[i+1], "/h")==0 ||\
       stricmp(argv[i+1], "/help")==0) {
	 blParameterOK=TRUE;
	 ReadMe();
	 continue;
    }
    if(stricmp(argv[i+1], "/??")==0) {
	 blParameterOK=TRUE;
	 ReadMe4Debug();
	 continue;
    }
    if(stricmp(argv[i+1], "/T")==0) {
      blParameterOK=TRUE;
      printf("/T \n");

	  blPlayWavFile=TRUE;
	  if(blPlay_Rec_Wavfile()==FALSE) printf("Can't play 100HZ.wav\n\r");

	  if(Analyze_Wav()==TRUE) {
        blResult=TRUE;
		printf("Line-out to Mic-in pass\n\r");
	  }
	  else {
          blResult=FALSE;
		  printf("Line-out to Mic-in fail\n\r");
	  }

	  /*
	  SelectMic_Rec();
      UnMuteMic_Rec();
      SetMicVolume_Rec();
      */


      //if(blWork()==TRUE) blResultOK=TRUE;
      //else blResultOK=FALSE;
      continue;
    }
    if(stricmp(argv[i+1], "/T1")==0) {
      blParameterOK=TRUE;
      printf("/T1 \n");
	  
	  //SelectRecording_Rec();
	  UnMuteRecording_Rec();

	  //SelectMic_Rec();




      UnMuteMic_Rec();
      SetMicVolume_Rec();
	  blMuteSPDIF_OUT();
      continue;
    }
    if(stricmp(argv[i+1], "/T2")==0) {
      blParameterOK=TRUE;
      printf("/T2 \n");

      SelectLineIn_Rec();
      UnMuteLineIn_Rec();
      //SetLineInVolume_Rec();
	  SetLineInVolumeLeft_Rec();
	  //blUnMuteSPDIF_OUT();
		
      continue;
    }

	if(stricmp(argv[i+1], "/T3")==0) {
      blParameterOK=TRUE;
      printf("/T3 \n");
	   blPlay_0to9_Wavfile(11);
      //Analyze_Wave_Freq();

      continue;
    }

	if(stricmp(argv[i+1], "/LRT")==0) 
	{
		BOOL blRet;
		blParameterOK=TRUE;

	    blRet = blSelectCH();

		if (blRet == FALSE)
			blResult = false;
		else
			blResult = true;

      continue;
    }
	
	if(stricmp(argv[i+1], "/T4")==0) 
	{
      blParameterOK=TRUE;
      printf("/T4 \n");
	  
      
	 // UpdateData(true);
	  EnumerateVolumeDevices();	
	  /*
	  if(blMute) MuteBn.SetIcon(AfxGetApp()->LoadIconA(IDI_MUTE));
	  else MuteBn.SetIcon(AfxGetApp()->LoadIconA(IDI_VOLUME));
	  VolScroll.SetScrollRange(0,VolumeLevel-1);	
	  wCurrent=VolumeLevel-1-VolumeLevelCount;
	  VolScroll.SetScrollPos(wCurrent);
	  */
	  blSetVolume(100);
	  //UpdateData(false);

      continue;
    }

	if(stricmp(argv[i+1], "/Play")==0) 
	{
		blParameterOK=TRUE;
		PlayWavefileName.Empty();
    	PlayWavefileName+=argv[i+2];
		blPlay_Wavfile();
	}

	if(stricmp(argv[i+1], "/SETWV")==0) 
	{
		blParameterOK=TRUE;
		blResult=TRUE;	
		if(ShowVolume())
		printf("setVolume OK!");
        continue;
    }

	if(stricmp(argv[i+1], "/GETWV")==0) 
	{
		blParameterOK=TRUE;
		blResult=FALSE;
		printf("Get wave volume  ");
		if(GetVolume())
		printf("GetVolume OK!");
        continue;
    }

     if(stricmp(argv[i+1], "/GETLNOUT")==0) {
      blParameterOK=TRUE;
      printf("\n Get Line-out volume");
    
	  if(blIsVista==TRUE) {
        EnumerateVolumeDevices();
        blResult=blVistaGetChVol();
		if(blResult)
		{
			printf(" Get Volume Successful!!!\n");
		}
		else
		{
			printf(" Get Volume FAIL!!!\n");
		}
		blResult = FALSE;
        /*blSetVolume(0);
		if(iRightVolume >= iLeftVolume)  blSetVolume(iRightVolume/2);
        if(iLeftVolume >= iRightVolume)  blSetVolume(iLeftVolume/2);
		*/
	  }
	  else 
	  {
	   GetAudioControl();
       Get_LineOut_RLch();
	  }
	  
	  //blResult=TRUE;
		
      continue;
    }
  
    
	if(stricmp(argv[i+1], "/SETLNOUT")==0) {
      blParameterOK=TRUE;
      printf("\n Set Line-out volume (Right_CH=%d%% , Left_CH=%d%%) \n\n",iRightVolume,iLeftVolume);
    
	  if(blIsVista==TRUE) 
	  {
          EnumerateVolumeDevices();
          blResult=blVistaSetChVol();
		  if(blResult)
		  {
			  printf(" Set Volume Successful!!!\n");
		  }
		  else
		  {
			  printf(" Set Volume FAIL!!!\n");
		  }
	  }
	  else 
	  {
		   GetAudioControl();
		   blSet_LineOut_RLch();
	  }
      continue;
    }
  
	if(stricmp(argv[i+1], "/SETWAVOUT")==0) {
      blParameterOK=TRUE;
      printf("\n Set Wave-out volume (Right_CH=%d%% , Left_CH=%d%%) \n\n",iRightVolume,iLeftVolume);
    
	  blSet_WaveOut_RLch();
	  
	  //blResult=TRUE;
		
      continue;
    }
 
	if(stricmp(argv[i+1], "/SETMICIN")==0) {
      blParameterOK=TRUE;
      printf("\n Set Mic-in volume (Right_CH=%d%% , Left_CH=%d%%) \n\n",iRightVolume,iLeftVolume);
    
	  blSet_MicIn_RLch();
	  
	  //blResult=TRUE;
		
      continue;
    }

    if(stricmp(argv[i+1], "/SETLINEIN")==0) {
      blParameterOK=TRUE;
      printf("\n Set Line-in volume (Right_CH=%d%% , Left_CH=%d%%) \n\n",iRightVolume,iLeftVolume);

      blSet_LineIn_RLch();
      	  
	  //blResult=TRUE;
		
      continue;
    }

	if(stricmp(argv[i+1], "/SETMICIN_REC")==0) {
      blParameterOK=TRUE;
	  printf("\n Set Mic-in REC volume (Right_CH=%d%% , Left_CH=%d%%) \n\n",iRightVolume,iLeftVolume);

	  pMicInVolume_R=1.0/(iRightVolume/100.0);
	  pMicInVolume_L=1.0/(iLeftVolume/100.0);

	  //if( SelectMic_Rec() == FALSE) {
		 // printf(" Error! No mixer found or No Mic_in REC item. \n");
	  //    End(255);
	  //}






      UnMuteMic_Rec();
      SetMicVolume_Rec();
     
	  //blResult=TRUE;
		
      continue;
    }

	if(stricmp(argv[i+1], "/SETLINEIN_REC")==0) {
      blParameterOK=TRUE;
	  printf("\n Set Line-in REC volume (Right_CH=%d%% , Left_CH=%d%%) \n\n",iRightVolume,iLeftVolume);
      
	  pLineInVolume=1.0/(iRightVolume/100.0);
	  pLineInVolume=1.0/(iLeftVolume/100.0);

	  if( SelectLineIn_Rec()== FALSE) {
	      printf(" Error! No mixer found or No Line_in REC item . \n");
	      End(255);
	  }
      UnMuteLineIn_Rec();
      SetLineInVolume_Rec();
	 
	  //blResult=TRUE;
		
      continue;
    }

	if(stricmp(argv[i+1], "/UNMUTESPDIF")==0) {
      blParameterOK=TRUE;
      printf("\n Unmute SPDIF out\n\n");
      blUnMuteSPDIF_OUT();	
      continue;
    }

	if(stricmp(argv[i+1], "/TSP")==0) {
      blParameterOK=TRUE;
	  if(blRandom0to9_presskey()) blResult=TRUE;	
      continue;
    }

    if(stricmp(argv[i+1], "/PCBEEP2MIC")==0) 
	{
      
      blParameterOK=TRUE;
      printf("\n Diagnosing PC-Beep to Mic-in audio \n\n");
	  GetAudioControl();

      //----  set Mic-in record channel volume  -----
	  if(blNoAdjustRecVol==FALSE) 
	  {
		//if( SelectMic_Rec() == FALSE) 
		//{
		//  printf(" Error! No mixer found or No Mic_in REC item. \n");
	 //     End(255);
		//}
         SetMicVolume_Rec();
	  }
      //----------------------------------------------------------
	  if(blMute_WaveOut_RLch()==FALSE) { printf("Can't adjust volume\n\r"); blResult=FALSE; }
      blUnMute_LineOut_RLch_80percent();
      blUnMute_PcBeep_RLch();
      
	  // ********** detect sound output **********
	  blPlayWav_NoSound=FALSE;
	  // test Line-out CH (PCbeep on) to Mic-in
      blPlayWavFile=FALSE;
	  if(blPlay_Rec_Wavfile()==FALSE)  blResult=FALSE; 
      printf("\n\r Diagnosing PC-Beep to Mic-in ");
	 
	  blUnMute_WaveOut_RLch();
	  blUnMute_LineOut_RLch();

	
	  if(Analyze_Wav()==TRUE) 
	  {
        printf("\n\n");
        printf("    Diagnosing PC-Beep to Mic-in pass.\n\r");
        blResult=TRUE;
	  }
	  else 
	  {
        printf("\n\n");
        printf("    Diagnosing PC-Beep to Mic-in fail !\n\r");
        blResult=FALSE;
	  }
      //---------------------------------------------------------------- 
     	
      continue;
    }

	if(stricmp(argv[i+1], "/REC")==0) 
	{
        blParameterOK=TRUE;
		 CString str;
		 GetModuleFileName(NULL,str.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
		 str.ReleaseBuffer();
		 int pos = str.ReverseFind('\\');
		 str = str.Left(pos);
		 sprintf(szStr2,"%s",str);
		 int len,j;
		 
		 for (int k = 0; k < len; k++)
		 {
			 len = strlen(szStr2);
			 j = len;
			 if (szStr2[k] == '\\')
			 {
				for (j; j >k; j--)
					szStr2[j] = szStr2[j - 1];

				szStr2[k + 1] = '\\';
				k = k + 2;
			 }
		 }
         
		 int n = strlen(szStr2);
		 len = strlen(szRec);
		 j = len;

		 for (int k = 0; k < j; k++)
			 szStr2[n + k] = szRec[k];


		blParameterOK=TRUE;
		strcpy(szDevName,"Microp");
		strcpy(szDevName2,"麦");

		record();
		continue;
        
	}

	if(stricmp(argv[i+1], "/plrec")==0) 
	{
        blParameterOK=TRUE;
		blPlayWavFile = TRUE;
		play();
		continue;
        
	}


	if(stricmp(argv[i+1], "/TESTMIC")==0) 
	{
      blParameterOK=TRUE;
	  blAnalyze_Amp=FALSE;
      blAnalyze_Freq=TRUE;
	  blTestMic=TRUE;

      //printf("\n Diagnosing Mic-in function\n\n");
    
	  /*     
	  // ********** Play .wav file and no sound output **********
	  blPlayWav_NoSound=TRUE;
	  // test Line-out Right CH to Mic-in
	  blPlayWavFile=TRUE;
	  if(blPlay_Rec_Wavfile()==FALSE)  blResult=FALSE; 
	  printf("\n\r Diagnosing Mic-in function");
	 
	  if(blAnalyze_Amp==TRUE) {
	    if(Analyze_Wav()==TRUE) {
          blRightCH_OK_0=TRUE;
	    }
	    else {
            blRightCH_OK_0=FALSE;
	    }
	  }

	  if(blAnalyze_Freq==TRUE) {
	    if(Analyze_Wave_Freq()==TRUE) {
          if(blRightCH_OK_0==TRUE) blRightCH_OK_0=TRUE;
	    }
	    else {
            blRightCH_OK_0=FALSE;
	    }
	  }
	  */
	  blRightCH_OK_0=TRUE;
	  //---------------------------------------------------------------- 

      
      
      // ********** Play .wav file and output sound **********
      blPlayWav_NoSound=FALSE;
	  // test Line-out Right CH to Mic-in
	  blPlayWavFile=TRUE;
	  printf("\n\r Diagnosing Mic-in function");
	for(retry=0;retry<3;retry++) 
	{
	  if(blPlay_Rec_Wavfile()==FALSE)  blResult=FALSE; 
	  printf(" .");

	  if(blAnalyze_Amp==TRUE) 
	  {
	    if(Analyze_Wav()==TRUE) 
		{
          blRightCH_OK_1=TRUE;
		}
	    else 
		{
            blRightCH_OK_1=FALSE;
		}
	  }

	  if(blAnalyze_Freq==TRUE) 
	  {
	    if(Analyze_Wave_Freq()==TRUE) 
		{
          if(blRightCH_OK_1==TRUE) blRightCH_OK_1=TRUE;
	    }
	    else 
		{
            blRightCH_OK_1=FALSE;
	    }
	  }
      //---------------------------------------------------------------- 

	  //printf("\n");

	     

	  if( (blRightCH_OK_0==TRUE) && (blRightCH_OK_1==TRUE) ) { blResult=TRUE; break;}
	}
	   
      if( iPercentage_globe >= iH_limit_percentage )  blRightCH_OK_1=TRUE;
	  
	  if( (blRightCH_OK_0==TRUE) && (blRightCH_OK_1==TRUE) ) {
       	printf("\n\r Test Mic-in pass.  ");
        blResult=TRUE;
	  }
	  else {
          printf("\n\r Test Mic-in fail !  ");
	  }
	  printf("[F](%3d%%,%3d%%)\n\r",iPercentage_globe, iH_limit_percentage );
	  if( (blRightCH_OK_1==FALSE) && (retry > 2) ) { blResult=FALSE; }

      continue;
	}

	if(stricmp(argv[i+1], "/LNOUT2MIC")==0 || stricmp(argv[i+1], "/HDMI2MIC")==0) 
	{
		if (stricmp(argv[i+1], "/HDMI2MIC")==0)
		{
			blHDMI = TRUE;
		}
		else
			bllnout = TRUE;
         CString str;
		 GetModuleFileName(NULL,str.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
		 str.ReleaseBuffer();
		 int pos = str.ReverseFind('\\');
		 str = str.Left(pos);
		 sprintf(szStr2,"%s",str);
		 int len,j;
		 
		 for (int k = 0; k < len; k++)
		 {
			 len = strlen(szStr2);
			 j = len;
			 if (szStr2[k] == '\\')
			 {
				for (j; j >k; j--)
					szStr2[j] = szStr2[j - 1];

				szStr2[k + 1] = '\\';
				k = k + 2;
			 }
		 }
         
		 int n = strlen(szStr2);
		 len = strlen(szRec);
		 j = len;

		 for (int k = 0; k < j; k++)
			 szStr2[n + k] = szRec[k];


		  blParameterOK=TRUE;
		  strcpy(szDevName,"Microphone");

		  GetAudioControl();
		  //	
		  ////----  set Mic-in record channel volume to 50% -----
		  if(blNoAdjustRecVol==FALSE) 
		  {
			  UnMuteMic_Rec();
		  }
  
		  //if (blMute_MicIn_ch())
			 // printf("adjust micphone right!");
		  //else
			 // printf("wrong!");

		  //blMute_LineIn_RLch();
		  //blMuteSPDIF_OUT(); 
	      
		  // ********** Play .wav file and no sound output **********
		  
		  // test Line-out Right CH to Mic-in
		  if(blNoAdjustRecVol==FALSE) 
			  SetMicVolumeRight_Rec();
		  //blMute_LineOut_Lch();
		  
		  blTestRch = TRUE;
		  blTestLch = FALSE;
		  blPlayWav_NoSound=FALSE;
		  if(blIsVista==TRUE) 
		  {
			  EnumerateVolumeDevices();
			  if (stricmp(argv[i+1], "/HDMI2MIC")==0)
			  {
				  blVistaMuteRch();
			  }
			  else
			      blVistaMuteLch();
		  }
		  else 
		  {
			   GetAudioControl();
			   blSet_LineOut_Rch();
	      }
		  blPlayWavFile=TRUE;
		  if(blPlay_Rec_Wavfile()==FALSE)  blResult=FALSE; 
		  if (ichannel == 1)
	      {
		      printf("\n\r Diagnosing Line-out to Mic-in");
	      }
	      else
	          printf("\n\r Diagnosing Line-out Right CH to Mic-in ");
		 
		  if(blAnalyze_Amp == TRUE) 
		  {
			  if(Analyze_Wav() == TRUE)
			  {
				  blRightCH_OK_0 = TRUE;
			  }
			  else 
			  {
				  blRightCH_OK_0 = FALSE;
			  }
		  }

			if(blAnalyze_Freq == TRUE)
			{
				if(Analyze_Wave_Freq() == TRUE)
				{
				  if(blRightCH_OK_0==TRUE) blRightCH_OK_0=TRUE;
				}
				else 
				{
					blRightCH_OK_0=FALSE;
				}
			}
		  //---------------------------------------------------------------- 
		  
		  // test Line-out Left CH to Mic-in
		//  if(blNoAdjustRecVol == FALSE) SetMicVolumeLeft_Rec();
		  blTestRch = FALSE;
		  blTestLch = TRUE;
		  //blMute_LineOut_Rch();
		  blPlayWavFile = TRUE;

		  if(blIsVista==TRUE) 
		  {
              EnumerateVolumeDevices();
		      if (stricmp(argv[i+1], "/HDMI2MIC")==0)
			  {
				  blVistaMuteLch();
			  }
			  else
			      blVistaMuteRch();
		  }
		  else 
		  {
			  GetAudioControl();
			  blSet_LineOut_Lch();
	      }

		  if(blPlay_Rec_Wavfile()==FALSE)  
			  blResult=FALSE;

		  printf("\n\r Diagnosing Line-out Left  CH to Mic-in ");

		  if(blAnalyze_Amp==TRUE) 
		  {
			  if(Analyze_Wav()==TRUE) 
			  {
				  blLeftCH_OK_0=TRUE;
			  }
			  else 
			  {
				  blLeftCH_OK_0=FALSE;
			  }
		  }

		  if(blAnalyze_Freq==TRUE) 
		  {
			  if(Analyze_Wave_Freq()==TRUE) 
			  {
			      if(blLeftCH_OK_0==TRUE) blLeftCH_OK_0=TRUE;
			  }
			  else 
			  {
				  blLeftCH_OK_0=FALSE;
			  }
		  }
		  //---------------------------------------------------------------- 
		  	
 	      blUnMute_LineOut_RLch();

	      
		  // ********** Play .wav file and output sound **********
		  blPlayWav_NoSound=TRUE;
		  blTestRch = TRUE;
		  blTestLch = FALSE;
		  // test Line-out Right CH to Mic-in
		  if(blNoAdjustRecVol==FALSE) SetMicVolumeRight_Rec();
		  //blMute_LineOut_Rch(); 
		  blPlayWavFile=TRUE;
		  if(blIsVista==TRUE) 
		  {
			  EnumerateVolumeDevices();
			  if (stricmp(argv[i+1], "/HDMI2MIC")==0)
			  {
				  blVistaMuteRch();
			  }
			  else
			      blVistaMuteLch();
		  }
		  else 
		  {
			  GetAudioControl();
			  blSet_LineOut_Rch();
	      }

		  if(blPlay_Rec_Wavfile()==FALSE) 
			  blResult=FALSE; 

		if (ichannel == 1)
	    {
		    printf("\n\r Diagnosing Line-out to Mic-in");
	    }
	    else
	        printf("\n\r Diagnosing Line-out Right CH to Mic-in ");
	      
		  if(blAnalyze_Amp==TRUE) 
		  {
			  if(Analyze_Wav()==TRUE) 
			  {
				  blRightCH_OK_1=TRUE;
			  }
			  else 
			  {
				  blRightCH_OK_1=FALSE;
			  }
		  }
		  	
		  if(blAnalyze_Freq==TRUE) 
		  {
			  if(Analyze_Wave_Freq()==TRUE) 
			  {
			      if(blRightCH_OK_1==TRUE) blRightCH_OK_1=TRUE;
			  }
			  else 
			  {
				  blRightCH_OK_1=FALSE;
			  }
		  }


		  //---------------------------------------------------------------- 
		  	
		  // test Line-out Left CH to Mic-in
		//  if(blNoAdjustRecVol==FALSE) SetMicVolumeLeft_Rec();
		  blTestRch = FALSE;
		  blTestLch = TRUE;
		  //blMute_LineOut_Rch(); 
		  blPlayWavFile = TRUE;
		  if(blIsVista==TRUE) 
		  {
			  EnumerateVolumeDevices();
			  if (stricmp(argv[i+1], "/HDMI2MIC")==0)
			  {
				  blVistaMuteLch();
			  }
			  else
			      blVistaMuteRch();
		  }
		  else 
		  {
			  GetAudioControl();
			  blSet_LineOut_Lch();
	      }

		  if(blPlay_Rec_Wavfile()==FALSE) 
			  blResult=FALSE; 

		   printf("\n\r Diagnosing Line-out Left  CH to Mic-in ");

		  if(blAnalyze_Amp==TRUE) 
		  {
			  if(Analyze_Wav()==TRUE) 
			  {
			      blLeftCH_OK_1=TRUE;
			  }
			  else 
			  {
				  blLeftCH_OK_1=FALSE;
			  }
		  }

		  if(blAnalyze_Freq==TRUE) 
		  {
			  if(Analyze_Wave_Freq()==TRUE) 
			  {
				  if(blLeftCH_OK_1==TRUE) 
					blLeftCH_OK_1=TRUE;
			  }
			  else 
			  {
				  blLeftCH_OK_1=FALSE;
			  }
		  }
		  
		  //---------------------------------------------------------------- 
		   	
	      blUnMute_LineOut_RLch();
		  blSet_LineOut_RLch();

		  if(blNoAdjustRecVol==FALSE) 
			  SetMicVolume_Rec();

		  printf("\n");

		  if( (blRightCH_OK_0==TRUE) && (blRightCH_OK_1==TRUE) ) 
		  {
       		  printf("    Line-out Right CH to Mic-in pass\n\r");
		  }
		  else 
		  {
			  printf("    Line-out Right CH to Mic-in fail\n\r");
		  }
		  if( (blLeftCH_OK_0==TRUE) && (blLeftCH_OK_1==TRUE) ) 
		  {
       		  printf("    Line-out Left  CH to Mic-in pass\n\r");
		  }
		  else 
		  {
			  printf("    Line-out Left  CH to Mic-in fail\n\r");
		  }

		  if( (blRightCH_OK_0==TRUE) && (blLeftCH_OK_0==TRUE) && (blRightCH_OK_1==TRUE) && (blLeftCH_OK_1==TRUE) ) blResult=TRUE;

		  continue;
	}


	if(stricmp(argv[i+1], "/LNOUT2LNIN")==0 || stricmp(argv[i+1], "/HDMI2LNIN")==0) 
	{
		if(stricmp(argv[i+1], "/HDMI2LNIN")==0)
		{
			blHDMI = TRUE;
		}
		else
			bllnout = TRUE;

		 CString str;
		 GetModuleFileName(NULL,str.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
		 str.ReleaseBuffer();
		 int pos = str.ReverseFind('\\');
		 str = str.Left(pos);
		 sprintf(szStr2,"%s",str);
		 int len,j;
		 
		 for (int k = 0; k < len; k++)
		 {
			 len = strlen(szStr2);
			 j = len;
			 if (szStr2[k] == '\\')
			 {
				for (j; j >k; j--)
					szStr2[j] = szStr2[j - 1];

				szStr2[k + 1] = '\\';
				k = k + 2;
			 }
		 }
         
		 int n = strlen(szStr2);
		 len = strlen(szRec);
		 j = len;

		 for (int k = 0; k < j; k++)
			 szStr2[n + k] = szRec[k];

      blParameterOK=TRUE;
	  strcpy(szDevName,"Line");
      printf(" \n Diagnosing Line-out to Line-in audio \n\n");

	  //GetAudioControl();

   //   //----  set Line-in record channel volume to 80% -----
		 // 	
		 GetAudioControl();
		  //	
		  ////----  set Mic-in record channel volume to 50% -----
		  if(blNoAdjustRecVol==FALSE) 
		  {
			  UnMuteMic_Rec();
		  }
  
		  //if (blMute_MicIn_ch())
			 // printf("adjust micphone right!");
		  //else
			 // printf("wrong!");

		  //blMute_LineIn_RLch();
		  //blMuteSPDIF_OUT(); 
	      
		  // ********** Play .wav file and no sound output **********
		  
		  // test Line-out Right CH to Mic-in
		  if(blNoAdjustRecVol==FALSE) 
			  SetMicVolumeRight_Rec();
		  //blMute_LineOut_Lch();
		  
		  blTestRch = TRUE;
		  blTestLch = FALSE;
		  blPlayWav_NoSound=FALSE;
		  if(blIsVista==TRUE) 
		  {
			  EnumerateVolumeDevices();
              if(stricmp(argv[i+1], "/HDMI2LNIN")==0)
			  {
				  blVistaMuteRch();
			  }
			  else
			      blVistaMuteLch();
		  }
		  else 
		  {
			   GetAudioControl();
			   blSet_LineOut_Rch();
	      }
		  blPlayWavFile=TRUE;
		  if(blPlay_Rec_Wavfile()==FALSE)  blResult=FALSE; 
		  if (ichannel == 1)
	      {
		      printf("\n\r Diagnosing Line-out to line-in");
	      }
	      else
	          printf("\n\r Diagnosing Line-out Right CH to line-in ");
		 
		  if(blAnalyze_Amp == TRUE) 
		  {
			  if(Analyze_Wav() == TRUE)
			  {
				  blRightCH_OK_0 = TRUE;
			  }
			  else 
			  {
				  blRightCH_OK_0 = FALSE;
			  }
		  }

			if(blAnalyze_Freq == TRUE)
			{
				if(Analyze_Wave_Freq() == TRUE)
				{
				  if(blRightCH_OK_0==TRUE) blRightCH_OK_0=TRUE;
				}
				else 
				{
					blRightCH_OK_0=FALSE;
				}
			}
		  //---------------------------------------------------------------- 
		  
		  // test Line-out Left CH to Mic-in
		 // if(blNoAdjustRecVol == FALSE) SetMicVolumeLeft_Rec();
		  blTestRch = FALSE;
		  blTestLch = TRUE;
		  //blMute_LineOut_Rch();
		  blPlayWavFile = TRUE;

		  if(blIsVista==TRUE) 
		  {
              EnumerateVolumeDevices();
		      if(stricmp(argv[i+1], "/HDMI2LNIN")==0)
			  {
				  blVistaMuteLch();
			  }
			  else
			      blVistaMuteRch();
		  }
		  else 
		  {
			  GetAudioControl();
			  blSet_LineOut_Lch();
	      }

		  if(blPlay_Rec_Wavfile()==FALSE)  
			  blResult=FALSE;

		  printf("\n\r Diagnosing Line-out Left  CH to line-in ");

		  if(blAnalyze_Amp==TRUE) 
		  {
			  if(Analyze_Wav()==TRUE) 
			  {
				  blLeftCH_OK_0=TRUE;
			  }
			  else 
			  {
				  blLeftCH_OK_0=FALSE;
			  }
		  }

		  if(blAnalyze_Freq==TRUE) 
		  {
			  if(Analyze_Wave_Freq()==TRUE) 
			  {
			      if(blLeftCH_OK_0==TRUE) blLeftCH_OK_0=TRUE;
			  }
			  else 
			  {
				  blLeftCH_OK_0=FALSE;
			  }
		  }
		  //---------------------------------------------------------------- 
		  	
 	      blUnMute_LineOut_RLch();

	      
		  // ********** Play .wav file and output sound **********
		  blPlayWav_NoSound=TRUE;
		  blTestRch = TRUE;
		  blTestLch = FALSE;
		  // test Line-out Right CH to Mic-in
		  if(blNoAdjustRecVol==FALSE) SetMicVolumeRight_Rec();
		  //blMute_LineOut_Rch(); 
		  blPlayWavFile=TRUE;
		  if(blIsVista==TRUE) 
		  {
			  EnumerateVolumeDevices();
			  if(stricmp(argv[i+1], "/HDMI2LNIN")==0)
			  {
				  blVistaMuteRch();
			  }
			  else
			      blVistaMuteLch();
		  }
		  else 
		  {
			  GetAudioControl();
			  blSet_LineOut_Rch();
	      }

		  if(blPlay_Rec_Wavfile()==FALSE) 
			  blResult=FALSE; 

		if (ichannel == 1)
	    {
		    printf("\n\r Diagnosing Line-out to Line-in");
	    }
	    else
	        printf("\n\r Diagnosing Line-out Right CH to line-in ");
	      
		  if(blAnalyze_Amp==TRUE) 
		  {
			  if(Analyze_Wav()==TRUE) 
			  {
				  blRightCH_OK_1=TRUE;
			  }
			  else 
			  {
				  blRightCH_OK_1=FALSE;
			  }
		  }
		  	
		  if(blAnalyze_Freq==TRUE) 
		  {
			  if(Analyze_Wave_Freq()==TRUE) 
			  {
			      if(blRightCH_OK_1==TRUE) blRightCH_OK_1=TRUE;
			  }
			  else 
			  {
				  blRightCH_OK_1=FALSE;
			  }
		  }


		  //---------------------------------------------------------------- 
		  	
		  // test Line-out Left CH to Mic-in
		 // if(blNoAdjustRecVol==FALSE) SetMicVolumeLeft_Rec();
		  blTestRch = FALSE;
		  blTestLch = TRUE;
		  //blMute_LineOut_Rch(); 
		  blPlayWavFile = TRUE;
		  if(blIsVista==TRUE) 
		  {
			  EnumerateVolumeDevices();
			  if(stricmp(argv[i+1], "/HDMI2LNIN")==0)
			  {
				  blVistaMuteLch();
			  }
			  else
			      blVistaMuteRch();
		  }
		  else 
		  {
			  GetAudioControl();
			  blSet_LineOut_Lch();
	      }

		  if(blPlay_Rec_Wavfile()==FALSE) 
			  blResult=FALSE; 

		   printf("\n\r Diagnosing Line-out Left  CH to line-in ");

		  if(blAnalyze_Amp==TRUE) 
		  {
			  if(Analyze_Wav()==TRUE) 
			  {
			      blLeftCH_OK_1=TRUE;
			  }
			  else 
			  {
				  blLeftCH_OK_1=FALSE;
			  }
		  }

		  if(blAnalyze_Freq==TRUE) 
		  {
			  if(Analyze_Wave_Freq()==TRUE) 
			  {
				  if(blLeftCH_OK_1==TRUE) 
					blLeftCH_OK_1=TRUE;
			  }
			  else 
			  {
				  blLeftCH_OK_1=FALSE;
			  }
		  }
		  
		  //---------------------------------------------------------------- 
		   	
	      blUnMute_LineOut_RLch();
		  blSet_LineOut_RLch();

		  if(blNoAdjustRecVol==FALSE) 
			  SetMicVolume_Rec();

		  printf("\n");

		  if( (blRightCH_OK_0==TRUE) && (blRightCH_OK_1==TRUE) ) 
		  {
       		  printf("    Line-out Right CH to line-in pass\n\r");
		  }
		  else 
		  {
			  printf("    Line-out Right CH to line-in fail\n\r");
		  }
		  if( (blLeftCH_OK_0==TRUE) && (blLeftCH_OK_1==TRUE) ) 
		  {
       		  printf("    Line-out Left  CH to line-in pass\n\r");
		  }
		  else 
		  {
			  printf("    Line-out Left  CH to line-in fail\n\r");
		  }

		  if( (blRightCH_OK_0==TRUE) && (blLeftCH_OK_0==TRUE) && (blRightCH_OK_1==TRUE) && (blLeftCH_OK_1==TRUE) ) blResult=TRUE;

		  continue;
	}

	if(stricmp(argv[i+1], "/SPDIF2MIC")==0) 
	{
		 blSpdif = TRUE;
         CString str;
		 GetModuleFileName(NULL,str.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
		 str.ReleaseBuffer();
		 int pos = str.ReverseFind('\\');
		 str = str.Left(pos);
		 sprintf(szStr2,"%s",str);
		 int len,j;
		 
		 for (int k = 0; k < len; k++)
		 {
			 len = strlen(szStr2);
			 j = len;
			 if (szStr2[k] == '\\')
			 {
				for (j; j >k; j--)
					szStr2[j] = szStr2[j - 1];

				szStr2[k + 1] = '\\';
				k = k + 2;
			 }
		 }
         
		 int n = strlen(szStr2);
		 len = strlen(szRec);
		 j = len;

		 for (int k = 0; k < j; k++)
			 szStr2[n + k] = szRec[k];


		  blParameterOK=TRUE;
		  strcpy(szDevName,"Microphone");

		  GetAudioControl();
		  //blSpdif = TRUE;
		  //	
		  ////----  set Mic-in record channel volume to 50% -----
		  if(blNoAdjustRecVol==FALSE) 
		  {
			  UnMuteMic_Rec();
		  }
  
		  //if (blMute_MicIn_ch())
			 // printf("adjust micphone right!");
		  //else
			 // printf("wrong!");

		  //blMute_LineIn_RLch();
		  //blMuteSPDIF_OUT(); 
	      
		  // ********** Play .wav file and no sound output **********
		  
		  // test Line-out Right CH to Mic-in
		  if(blNoAdjustRecVol==FALSE) 
			  SetMicVolumeRight_Rec();
		  //blMute_LineOut_Lch();
		  
		  blTestRch = TRUE;
		  blTestLch = FALSE;
		  blPlayWav_NoSound=FALSE;
		  if(blIsVista==TRUE) 
		  {
			  EnumerateVolumeDevices();
			  blVistaMuteLch();
			  //IMMDeviceCollection::Item
		  }
		  else 
		  {
			   GetAudioControl();
			   blSet_LineOut_Rch();
	      }
		  blPlayWavFile=TRUE;
		  if(blPlay_Rec_Wavfile()==FALSE)  blResult=FALSE; 
		  if (ichannel == 1)
	      {
		      printf("\n\r Diagnosing Line-out to Mic-in");
	      }
	      else
	          printf("\n\r Diagnosing Line-out Right CH to Mic-in ");
		 
		  if(blAnalyze_Amp == TRUE) 
		  {
			  if(Analyze_Wav() == TRUE)
			  {
				  blRightCH_OK_0 = TRUE;
			  }
			  else 
			  {
				  blRightCH_OK_0 = FALSE;
			  }
		  }

			if(blAnalyze_Freq == TRUE)
			{
				if(Analyze_Wave_Freq() == TRUE)
				{
				  if(blRightCH_OK_0==TRUE) blRightCH_OK_0=TRUE;
				}
				else 
				{
					blRightCH_OK_0=FALSE;
				}
			}
		  //---------------------------------------------------------------- 
		  
		  // test Line-out Left CH to Mic-in
		//  if(blNoAdjustRecVol == FALSE) SetMicVolumeLeft_Rec();
		  blTestRch = FALSE;
		  blTestLch = TRUE;
		  //blMute_LineOut_Rch();
		  blPlayWavFile = TRUE;

		  if(blIsVista==TRUE) 
		  {
              EnumerateVolumeDevices();
		      blVistaMuteRch();
		  }
		  else 
		  {
			  GetAudioControl();
			  blSet_LineOut_Lch();
	      }

		  if(blPlay_Rec_Wavfile()==FALSE)  
			  blResult=FALSE;

		  printf("\n\r Diagnosing Line-out Left  CH to Mic-in ");

		  if(blAnalyze_Amp==TRUE) 
		  {
			  if(Analyze_Wav()==TRUE) 
			  {
				  blLeftCH_OK_0=TRUE;
			  }
			  else 
			  {
				  blLeftCH_OK_0=FALSE;
			  }
		  }

		  if(blAnalyze_Freq==TRUE) 
		  {
			  if(Analyze_Wave_Freq()==TRUE) 
			  {
			      if(blLeftCH_OK_0==TRUE) blLeftCH_OK_0=TRUE;
			  }
			  else 
			  {
				  blLeftCH_OK_0=FALSE;
			  }
		  }
		  //---------------------------------------------------------------- 
		  	
 	      blUnMute_LineOut_RLch();

	      
		  // ********** Play .wav file and output sound **********
		  blPlayWav_NoSound=TRUE;
		  blTestRch = TRUE;
		  blTestLch = FALSE;
		  // test Line-out Right CH to Mic-in
		  if(blNoAdjustRecVol==FALSE) SetMicVolumeRight_Rec();
		  //blMute_LineOut_Rch(); 
		  blPlayWavFile=TRUE;
		  if(blIsVista==TRUE) 
		  {
			  EnumerateVolumeDevices();
			  blVistaMuteLch();
		  }
		  else 
		  {
			  GetAudioControl();
			  blSet_LineOut_Rch();
	      }

		  if(blPlay_Rec_Wavfile()==FALSE) 
			  blResult=FALSE; 

		if (ichannel == 1)
	    {
		    printf("\n\r Diagnosing Line-out to Mic-in");
	    }
	    else
	        printf("\n\r Diagnosing Line-out Right CH to Mic-in ");
	      
		  if(blAnalyze_Amp==TRUE) 
		  {
			  if(Analyze_Wav()==TRUE) 
			  {
				  blRightCH_OK_1=TRUE;
			  }
			  else 
			  {
				  blRightCH_OK_1=FALSE;
			  }
		  }
		  	
		  if(blAnalyze_Freq==TRUE) 
		  {
			  if(Analyze_Wave_Freq()==TRUE) 
			  {
			      if(blRightCH_OK_1==TRUE) blRightCH_OK_1=TRUE;
			  }
			  else 
			  {
				  blRightCH_OK_1=FALSE;
			  }
		  }


		  //---------------------------------------------------------------- 
		  	
		  // test Line-out Left CH to Mic-in
		//  if(blNoAdjustRecVol==FALSE) SetMicVolumeLeft_Rec();
		  blTestRch = FALSE;
		  blTestLch = TRUE;
		  //blMute_LineOut_Rch(); 
		  blPlayWavFile = TRUE;
		  if(blIsVista==TRUE) 
		  {
			  EnumerateVolumeDevices();
			  blVistaMuteRch();
		  }
		  else 
		  {
			  GetAudioControl();
			  blSet_LineOut_Lch();
	      }

		  if(blPlay_Rec_Wavfile()==FALSE) 
			  blResult=FALSE; 

		   printf("\n\r Diagnosing Line-out Left  CH to Mic-in ");

		  if(blAnalyze_Amp==TRUE) 
		  {
			  if(Analyze_Wav()==TRUE) 
			  {
			      blLeftCH_OK_1=TRUE;
			  }
			  else 
			  {
				  blLeftCH_OK_1=FALSE;
			  }
		  }

		  if(blAnalyze_Freq==TRUE) 
		  {
			  if(Analyze_Wave_Freq()==TRUE) 
			  {
				  if(blLeftCH_OK_1==TRUE) 
					blLeftCH_OK_1=TRUE;
			  }
			  else 
			  {
				  blLeftCH_OK_1=FALSE;
			  }
		  }
		  
		  //---------------------------------------------------------------- 
		   	
	      blUnMute_LineOut_RLch();
		  blSet_LineOut_RLch();

		  if(blNoAdjustRecVol==FALSE) 
			  SetMicVolume_Rec();

		  printf("\n");

		  if( (blRightCH_OK_0==TRUE) && (blRightCH_OK_1==TRUE) ) 
		  {
       		  printf("    Line-out Right CH to Mic-in pass\n\r");
		  }
		  else 
		  {
			  printf("    Line-out Right CH to Mic-in fail\n\r");
		  }
		  if( (blLeftCH_OK_0==TRUE) && (blLeftCH_OK_1==TRUE) ) 
		  {
       		  printf("    Line-out Left  CH to Mic-in pass\n\r");
		  }
		  else 
		  {
			  printf("    Line-out Left  CH to Mic-in fail\n\r");
		  }

		  if( (blRightCH_OK_0==TRUE) && (blLeftCH_OK_0==TRUE) && (blRightCH_OK_1==TRUE) && (blLeftCH_OK_1==TRUE) ) blResult=TRUE;

		  continue;
	}

  }


 
  if(blResult && blParameterOK ) End(0);
  else if(!blParameterOK ) ReadMe();
  End(255);
  // -----------------------------------------------------------------------
  //return 0;
}

