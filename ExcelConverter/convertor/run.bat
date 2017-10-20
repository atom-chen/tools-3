
@echo off
set DIR=%~dp0


setlocal enabledelayedexpansion


set XLS_PATH="E:\\hlb\\ExcelConverter\\xlsx\\"


::just pack data only
::lua %DIR%\luaToData.lua
::pause&exit




set LUA_ucs=%DIR%lua_ucs
set LUA_utf=%DIR%lua_utf8
set PB_PATH=%DIR%pbs
set CPP_PATH=%DIR%cpps
set DATA_PATH=%DIR%data

if not exist %LUA_ucs% md %LUA_ucs%
if not exist %LUA_utf% md %LUA_utf%
if not exist %PB_PATH% md %PB_PATH%
if not exist %CPP_PATH% md %CPP_PATH%
if not exist %DATA_PATH% md %DATA_PATH%

del /a /f /s /q %LUA_ucs%\*.*
del /a /f /s /q %LUA_utf%\*.*
del /a /f /s /q %PB_PATH%\*.*
del /a /f /s /q %CPP_PATH%\*.*
del /a /f /s /q %DATA_PATH%\*.*

echo XLS_PATH: %XLS_PATH%




::if no multi-language excel file, then create it first.
if not exist %XLS_PATH%Multi_lang.xlsx call ExportStringToExcel.bat


printf "\n\n##################################################"
printf "\nstart to convert xlsx ...\n"
tools\xlsx2Lua\Debug\xlsx2Lua %LUA_ucs% %PB_PATH% %XLS_PATH%
if ERRORLEVEL 1 goto ERROR



printf "\n\n##################################################"
printf "\nstart to Encoding to utf-8 ...\n"
for /r %LUA_ucs% %%i in (*.lua) do (	
	set luaname=%%~nxi
	
	tools\iconv\iconv -s -f gbk -t utf-8 %%i > %LUA_utf%\!luaname!
	
	if ERRORLEVEL 1 goto ERROR
)

::printf "\n\n##################################################"
::printf "\nstart to get version ...\n"
::call getVersion.bat

printf "\n\n##################################################"
printf "\nstart to package ...\n"
lua %DIR%\luaToData.lua
if ERRORLEVEL 1 goto ERROR






printf "\n ==== convert success ===== \n"
pause&exit


:ERROR
printf "\n ====  convert ERROR  ===== \n"
pause


