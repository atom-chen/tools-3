@echo off
set DIR=%~dp0
set PB_FOLDER=%DIR%\pbs
set CPP_FOLDER=%DIR%\cpps


printf "\n##################################################"
printf "\nstart to convert proto to cc/h ...\n"

setlocal enabledelayedexpansion
set "total_pkgs= "
for /f %%i in ('dir /B %PB_FOLDER%\*.proto') do ( 
	set total_pkgs=!total_pkgs! %%i

)
cd %PB_FOLDER%
..\tools\protoc-generator\protoc --cpp_out=%CPP_FOLDER% %total_pkgs%

