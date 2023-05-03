@echo off

set common_compiler_flags=-FC -GR -EHa -nologo -Zi

IF NOT EXIST ..\..\build mkdir ..\..\build
pushd ..\..\build

cl %common_compiler_flags% ..\somethings\src\test_base.cpp -Fmtest_base.map
