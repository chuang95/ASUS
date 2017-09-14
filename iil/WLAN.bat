@echo off

:test_wlan
if exist wnetwork.log del wnetwork.log
if exist wlan.log del wlan.log

rem Modify speed "54 Mbps" according to different device
WNetwork.exe -n 2 /S 54 > wnetwork.log
if errorlevel 1 goto fail
if not exist wnetwork.log goto lost

echo.
rem Modify this Description according to different device
chkstr /file wnetwork.log "USB Wireless 802.11 b/g Adaptor"
if errorlevel 1 goto fail
goto chkspe

:chkspe
echo.
chkstr /file wnetwork.log "Connect     = Connected"
if errorlevel 1 goto fail
goto pass

:fail
echo.
echo **********************************
echo **********Wlan test fail**********
echo **********************************
pause >nul
goto fail

:lost
echo.
echo **********************************
echo ****wnetwork.log lost*************
echo **********************************
pause >nul
goto lost

:pass
echo wlan test ok > wlan.log

:end
