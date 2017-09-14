1. Description: 
	This utility test antenna RSSI on Windows XP/Vista. It will return value depending on connection status, rssi values.

2. Command parameters in RT2800 file
	2.1 Ra_Ant_RSSI.exe -ssid Ralink_AP 
	    ssid: SSID of the AP to connect. (The security mode of AP must set open)
	2.2 Ra_Ant_RSSI.exe -r0 -60 -r1 -60 -rd 0 -rl 30
	    r0: Minimum RSSI value for antenna 0 to pass the test.If 0: bypass checking RSSI 0
	    r1: Minimum RSSI value for antenna 1 to pass the test.If 0: bypass checking RSSI 1
	    rd: Maximum difference between antenna 0 and antenna 1 to pass the test. If the value is set to 0, this parameter is ignored.
	    rl: Antenna RSSI query loop count. (The period is 20ms between each RSSI query)

3. Test procedure for Windows XP:
	3.1 Copy all the files to a folder.
	3.2 Copy wlanapi.dll from xp folder.
	3.3 Add your card's VID/PID in RT2800.ini.	
	3.4 Exit RaUI if it is running.
	3.5 Stop Windows "Wireless Zero Configuration" service.
	3.6 Run Ra_Ant_RSSI.exe to connect AP.(Ra_Ant_RSSI.exe -ssid Ralink_AP)
	    => This setp is to connect to an AP with specific SSID, the security mode of AP must set open.
	3.7 Run Ra_Ant_RSSI.exe to do RSSI test.(Ra_Ant_RSSI.exe -r0 -60 -r1 -60 -rd 0 -rl 30)
	
4. Test Procedure for Windows Vista:
	4.1 Copy all the files to a folder.
	4.2 Add your card's VID/PID in RT2800.ini.	
	4.3 Exit RaUI if it is running.	
	4.4 Run Ra_Ant_RSSI.exe (with administrator privilege) to connect AP.(Ra_Ant_RSSI.exe -ssid Ralink_AP)
	    => This setp is to connect to an AP with specific SSID, the AP must not set security mode.
	4.5 Run Ra_Ant_RSSI.exe (with administrator privilege) to do RSSI test.(Ra_Ant_RSSI.exe -r0 -60 -r1 -60 -rd 0 -rl 30)	

5. Return values:
	-1: Open adaptor failed.
	0: Pass.
	1: Ant0 RSSI < RSSI Threshold0.
	2: Ant1 RSSI < RSSI Threshold1.
	3: Ant0 RSSI < RSSI Threshold0 and Ant1 RSSI < RSSI Threshold1.
	4. Antenna 0 and antenna 1 RSSI difference is greater than RSSI_Diff.
	5. Can not connect to AP after LinkTimeOut time is expired if SSID parameter is set.
 	