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
if not exist "%SDK_DIRECTORY%\Include\Externals"																	mkdir "%SDK_DIRECTORY%\Include\Externals"
if exist "%VENUS_DIRECTORY%\Externals\%1\%1" if not exist "%SDK_DIRECTORY%\Include\Externals\%1"																mkdir "%SDK_DIRECTORY%\Include\Externals\%1"
if not exist "%SDK_DIRECTORY%\Windows"																						mkdir "%SDK_DIRECTORY%\Windows"
if not exist "%SDK_DIRECTORY%\Windows\VC100"																			mkdir "%SDK_DIRECTORY%\Windows\VC100"
if not exist "%SDK_DIRECTORY%\Windows\VC100\Win32"																mkdir "%SDK_DIRECTORY%\Windows\VC100\Win32"
if not exist "%SDK_DIRECTORY%\Windows\VC100\Win32\Debug"													mkdir "%SDK_DIRECTORY%\Windows\VC100\Win32\Debug"
if not exist "%SDK_DIRECTORY%\Windows\VC100\Win32\Release"												mkdir "%SDK_DIRECTORY%\Windows\VC100\Win32\Release"
if not exist "%SDK_DIRECTORY%\Windows\VC100\Win32\Shipping"												mkdir "%SDK_DIRECTORY%\Windows\VC100\Win32\Shipping"
if not exist "%SDK_DIRECTORY%\Windows\VC100\x64"																	mkdir "%SDK_DIRECTORY%\Windows\VC100\x64"
if not exist "%SDK_DIRECTORY%\Windows\VC100\x64\Debug"														mkdir "%SDK_DIRECTORY%\Windows\VC100\x64\Debug"
if not exist "%SDK_DIRECTORY%\Windows\VC100\x64\Release"													mkdir "%SDK_DIRECTORY%\Windows\VC100\x64\Release"
if not exist "%SDK_DIRECTORY%\Windows\VC100\x64\Shipping"													mkdir "%SDK_DIRECTORY%\Windows\VC100\x64\Shipping"

echo (only copying new or modified files)

:: COPY STANDARD FILES
if not exist "%VENUS_DIRECTORY%\Externals\%1\%1" if exist "%VENUS_DIRECTORY%\Externals\%1\*.h"																			xcopy /D /F /I /R /Y "%VENUS_DIRECTORY%\Externals\%1\*.h"																		"%SDK_DIRECTORY%\Include\Externals"
if exist "%VENUS_DIRECTORY%\Externals\%1\%1\*.h"																	xcopy /D /F /I /R /Y "%VENUS_DIRECTORY%\Externals\%1\%1\*.h"																"%SDK_DIRECTORY%\Include\Externals\%1"

if exist "%VENUS_DIRECTORY%\Binaries\Windows\%2\%3\%4\%1.lib"											xcopy /D /F /I /R /Y "%VENUS_DIRECTORY%\Binaries\Windows\%2\%3\%4\%1.lib"										"%SDK_DIRECTORY%\Windows\%2\%3\%4"
if exist "%VENUS_DIRECTORY%\Binaries\Windows\%2\%3\%4\%1.dll"											xcopy /D /F /I /R /Y "%VENUS_DIRECTORY%\Binaries\Windows\%2\%3\%4\%1.dll"										"%SDK_DIRECTORY%\Windows\%2\%3\%4"
if exist "%VENUS_DIRECTORY%\Binaries\Windows\%2\%3\%4\%1.pdb"											xcopy /D /F /I /R /Y "%VENUS_DIRECTORY%\Binaries\Windows\%2\%3\%4\%1.pdb"										"%SDK_DIRECTORY%\Windows\%2\%3\%4"

if exist "%SDK_DIRECTORY%\Include\Externals" attrib +R "%SDK_DIRECTORY%\Include\Externals\*"
if exist "%SDK_DIRECTORY%\Include\Externals\%1" attrib +R "%SDK_DIRECTORY%\Include\Externals\%1\*"
if exist "%SDK_DIRECTORY%\Windows\%2\%3\%4" attrib +R "%SDK_DIRECTORY%\Windows\%2\%3\%4\*"

exit /b

:==ERROR_NO_SDK
echo %0: fatal error: Cannot locate SDK directory.
exit 1
