@echo off
:: This file is called after the resources have been compiled :-/
set VERSION=1,0,0,
set BUILD=BUILD
set outfile=.\version.h
for /f "" %%i in ('type %BUILD%') do (
  set X=%%i
  )
set /a X=%X%+1
echo %X% > %BUILD%
:: ... therefore we write currentversion+1 into the header file
set /a X=%X%+1
set /a Y=%X%-1
set NEWVERSION=%VERSION%%X%
echo // Automatically created file! > %outfile%
echo #define VERSION_BIN %NEWVERSION% >> %outfile%
echo Current build is %Y%
echo Next version is %NEWVERSION% (Build %X%)
set NEWVERSION=%NEWVERSION:,=.%
set NEWVERSION=%NEWVERSION: =%
echo #define VERSION_STR ^"%NEWVERSION%\0^" >> %outfile%
echo.                              >> %outfile%

