@echo off
set errorlevel=255
wlanchk-auto.exe /connect

echo %errorlevel%
pause