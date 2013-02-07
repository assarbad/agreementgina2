@echo off
:: ----------------------------------------------------------------------------
:: Replaces the GINA which is not in use. It toggles between the two names
:: AgreementGINA.dll and AgreementGINA2.dll
:: Makes the appropriate registry setting as well :-)
:: ----------------------------------------------------------------------------
set GINA1=AgreementGINA.dll
set GINA2=AgreementGINA2.dll
del /q /f %SystemRoot%\System32\%GINA1% > NUL
del /q /f %SystemRoot%\System32\%GINA2% > NUL
IF EXIST %SystemRoot%\System32\%GINA1% (
  set GINA=%GINA2%
) ELSE (
  set GINA=%GINA1%
)
echo Using name %GINA%
set REGFILE=%TEMP%\Winlogon.reg
echo Creating registry script %REGFILE%
echo REGEDIT4 > %REGFILE%
echo ^[HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon^] >> %REGFILE%
echo "GinaDLL"="%GINA%" >> %REGFILE%
:: Delete the registry script file
regedit /s %REGFILE%
del /q /f %REGFILE%
copy AgreementGINA.dll %SystemRoot%\System32\%GINA%
pause
