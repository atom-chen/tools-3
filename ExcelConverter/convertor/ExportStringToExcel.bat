
@echo off
set DIR=%~dp0


setlocal enabledelayedexpansion


set XLS_PATH="E:\\hlb\\ExcelConverter\\xlsx\\"


if exist %XLS_PATH%Multi_lang.xlsx (
printf "\n ###### file already exist!!!  ##### \n" 
pause&exit)


printf "\n\n##################################################"
printf "\nstart to convert xlsx ...\n"
tools\xlsx2Lua\Debug\xlsx2Lua %XLS_PATH%

if ERRORLEVEL 1 (
printf "\n ====  fail !!!  ===== \n"
pause&exit
)


printf "\n #####  create multi-lan xlsx success #### \n"
pause


