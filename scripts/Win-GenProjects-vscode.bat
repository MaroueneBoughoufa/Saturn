@echo off
pushd %~dp0\..\
call vendor\premake\bin\premake5.exe gmake2
call vendor\premake\bin\premake5.exe vscode
popd
PAUSE