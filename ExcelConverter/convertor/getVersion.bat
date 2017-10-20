
@echo off

setlocal enabledelayedexpansion

set DIR=%~dp0
set SOURCE_PATH=%DIR%\..\..\..\work\sanguo_res\trunk\Data


svn info %SOURCE_PATH% > svnVersion.txt

for /f "delims=" %%a in ('findstr "Revision:" svnVersion.txt') do (set svnState=%%a)
echo vesion %svnState:~10%

set VersionFile=%DIR%\lua_utf8\_Version.lua

echo local MAJOR_VERSION = 1 >%VersionFile%
echo local MINOR_VERSION = 3 >>%VersionFile%
echo local BUILD_VERSION = 0 >>%VersionFile%
echo local SVN_VERSION = "%svnState:~10%" >>%VersionFile%
echo local function MakeVersion() >>%VersionFile%
echo   return "Ver: "..MAJOR_VERSION.."."..MINOR_VERSION.."."..BUILD_VERSION.."."..SVN_VERSION >>%VersionFile%
echo end >>%VersionFile%
echo return MakeVersion() >>%VersionFile% 
