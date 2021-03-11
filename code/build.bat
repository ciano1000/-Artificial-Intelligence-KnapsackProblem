@echo off

set flags=-FC -GR- -EHa- -nologo -Zi
set link_flags=
if not defined DevEnvDir call vcvarsall x64
if not exist .\build mkdir .\build 
pushd build
cl ..\\code\\main.c %flags% /DEBUG /link %link_flags% /out:assignment1.exe
popd
