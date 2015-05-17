@echo off

set SDK_DIRECTORY=not_found

if exist "..\..\..\..\..\Binaries"																								set VENUS_DIRECTORY=..\..\..\..\..
if exist "..\..\..\..\Binaries"																										set VENUS_DIRECTORY=..\..\..\..
if exist "..\..\..\Binaries"																											set VENUS_DIRECTORY=..\..\..
if exist "..\..\Binaries"																													set VENUS_DIRECTORY=..\..
if exist "..\Binaries"																														set VENUS_DIRECTORY=..
if (%VENUS_DIRECTORY%)==(not_found)																								goto :ERROR_NO_BIN
set BIN_DIRECTORY="%VENUS_DIRECTORY%\Binaries"
set VENUS_DIRECTORY="%VENUS_DIRECTORY%"

echo (copy dll to binaries)

:: COPY STANDARD FILES
if exist "%VENUS_DIRECTORY%\Externals\OGLES2\WindowsX86\Lib\*.dll"								xcopy /D /F /I /R /Y "%VENUS_DIRECTORY%\Externals\OGLES2\WindowsX86\Lib\*.dll"							"%BIN_DIRECTORY%"

exit /b

:==ERROR_NO_BIN
echo %0: fatal error: Cannot locate Binaries directory.
exit 1
