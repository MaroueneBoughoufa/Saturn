@echo off
rem Environment variables for building with Visual Studio

set ROOTDIR=%~dp0
set ROOTDIR=%ROOTDIR:~0,-1%

set SLN_FILE=SaturnEngine.sln

set VS_PATH="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat"
set VS_VER="vs2019"