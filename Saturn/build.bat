@echo off

if not defined DevEnvDir (
    call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat"
)

set config="Dist"

set project="Saturn.vcxproj"

if "%1" == "Debug" ( set config="Debug" )
if "%1" == "Release" ( set config="Release" )
if "%1" == "Dist" ( set config="Dist" )

if not exist %solutionFile% (
        call premake.bat vs2019
)


msbuild %project% /t:Build /p:Configuration=%config% /p:Platform=x64