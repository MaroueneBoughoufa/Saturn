@echo off

goto Begin

:Error

echo Could not find MSVC !

goto End


:Begin

set vspath="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat"

pushd %~dp0\..\

if not defined DevEnvDir (
	if not exist %vspath% ( goto Error )
	call %vspath%	
)

set config="Dist"

set solutionFile="SaturnEngine.sln"

if "%1" == "Debug" ( set config="Debug" )
if "%1" == "Release" ( set config="Release" )
if "%1" == "Dist" ( set config="Dist" )

if not exist %solutionFile% (
	call premake.bat vs2019
)

set system = ""

if config == "Dist" ( set system = "/system:windows")

msbuild -m /t:Build /p:Configuration=%config% /p:Platform=x64 %solutionFile% %system%

popd

goto End

:End
PAUSE