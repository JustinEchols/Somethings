@echo off

set macro_options=-DENABLE_ASSERT=0
set cl_options=-FC -GR -EHa -nologo -Zi %macro_options%
set clang_options=-o test.exe %macro_options%

IF NOT EXIST ..\..\build mkdir ..\..\build
pushd ..\..\build

cl %cl_options% ..\somethings\src\test_base.cpp -Fmtest_base.map
REM clang %clang_options% ..\somethings\src\test_base.cpp
