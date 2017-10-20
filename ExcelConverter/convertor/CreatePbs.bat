@echo off
set DIR=%~dp0
set DIR=%DIR%\pbs
cd /d "%DIR%"

setlocal enabledelayedexpansion

printf "\n##################################################"
printf "\nstart to convert proto to pb ...\n"

for /r %%i in (*.proto) do ( 
set pbname=%%i 
set pbname=!pbname:~0,-5!b
..\tools\protoc-generator\protoc -I %DIR% --descriptor_set_out !pbname! %%i 
)
