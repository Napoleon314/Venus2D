@echo off

set SDK_DIRECTORY=not_found

if exist "..\..\..\..\..\SDK"																											set VENUS_DIRECTORY=..\..\..\..\..
if exist "..\..\..\..\SDK"																												set VENUS_DIRECTORY=..\..\..\..
if exist "..\..\..\SDK"																														set VENUS_DIRECTORY=..\..\..
if exist "..\..\SDK"																															set VENUS_DIRECTORY=..\..
if exist "..\SDK"																																	set VENUS_DIRECTORY=..
if (%VENUS_DIRECTORY%)==(not_found)																								goto :ERROR_NO_SDK
set SDK_DIRECTORY="%VENUS_DIRECTORY%\SDK"
set VENUS_DIRECTORY="%VENUS_DIRECTORY%"

echo (Creating SDK directories)
if not exist "%SDK_DIRECTORY%\Include"																						mkdir "%SDK_DIRECTORY%\Include"
if not exist "%SDK_DIRECTORY%\MobileSim"																					mkdir "%SDK_DIRECTORY%\MobileSim"
if not exist "%SDK_DIRECTORY%\MobileSim\VC100"																		mkdir "%SDK_DIRECTORY%\MobileSim\VC100"
if not exist "%SDK_DIRECTORY%\MobileSim\VC100\Debug"															mkdir "%SDK_DIRECTORY%\MobileSim\VC100\Debug"
if not exist "%SDK_DIRECTORY%\MobileSim\VC100\Release"														mkdir "%SDK_DIRECTORY%\MobileSim\VC100\Release"
if not exist "%SDK_DIRECTORY%\MobileSim\VC100\Shipping"														mkdir "%SDK_DIRECTORY%\MobileSim\VC100\Shipping"

echo (only copying new or modified files)

:: COPY STANDARD FILES
if exist "%VENUS_DIRECTORY%\Source\%1\Ve*.h"																			xcopy /D /F /I /R /Y "%VENUS_DIRECTORY%\Source\%1\Ve*.h"																		"%SDK_DIRECTORY%\Include"
if exist "%VENUS_DIRECTORY%\Source\%1\Ve*.inl"																		xcopy /D /F /I /R /Y "%VENUS_DIRECTORY%\Source\%1\Ve*.inl"																	"%SDK_DIRECTORY%\Include"

if exist "%VENUS_DIRECTORY%\Binaries\MobileSim\%2\%3\%1.lib"											xcopy /D /F /I /R /Y "%VENUS_DIRECTORY%\Binaries\MobileSim\%2\%3\%1.lib"										"%SDK_DIRECTORY%\MobileSim\%2\%3"
if exist "%VENUS_DIRECTORY%\Binaries\MobileSim\%2\%3\%1.dll"											xcopy /D /F /I /R /Y "%VENUS_DIRECTORY%\Binaries\MobileSim\%2\%3\%1.dll"										"%SDK_DIRECTORY%\MobileSim\%2\%3"
if exist "%VENUS_DIRECTORY%\Binaries\MobileSim\%2\%3\%1.pdb"											xcopy /D /F /I /R /Y "%VENUS_DIRECTORY%\Binaries\MobileSim\%2\%3\%1.pdb"										"%SDK_DIRECTORY%\MobileSim\%2\%3"

if exist "%SDK_DIRECTORY%\Include" attrib +R "%SDK_DIRECTORY%\Include\*"
if exist "%SDK_DIRECTORY%\MobileSim\%2\%3" attrib +R "%SDK_DIRECTORY%\MobileSim\%2\%3\*"

exit /b

:==ERROR_NO_SDK
echo %0: fatal error: Cannot locate SDK directory.
exit 1
