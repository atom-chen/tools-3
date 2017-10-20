@echo off
set DIR=%~dp0
set DATA_PATH=%DIR%data
set RAR_EXE="C:\Program Files\WinRAR\WinRAR.exe"


setlocal enabledelayedexpansion

for /r %DATA_PATH% %%i in (*.data) do ( 
set pbname=%%i 
set pbname=!pbname:~0,-6!.zip
%RAR_EXE% a -ep1 !pbname! %%i
)

	

