@echo off

pushd ..

if not defined DevEnvDir (
    call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat"
)

set config="Dist"

if "~%1" == "Debug" ( set config="Debug" )
if "~%1" == "Release" ( set config="Release" )
if "~%1" == "Dist" ( set config="Dist" )

set solutionFile="SaturnEngine.sln"
msbuild /t:Build /p:Configuration=%config% /p:Platform=x64 %solutionFile%

popd

PAUSE