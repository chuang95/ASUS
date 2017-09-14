@echo off

Video-diags.exe -d 3 /t
if errorlevel 255 goto file
goto end

:file
echo fail >>1.log

:end