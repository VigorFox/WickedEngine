@echo off
setlocal

echo Locating Visual Studio...
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%VSWHERE%" (
    echo vswhere.exe not found.
    exit /b 1
)

for /f "usebackq tokens=*" %%i in (`"%VSWHERE%" -latest -products * -requires Microsoft.Component.MSBuild -property installationPath`) do (
    set "VS_INSTALL_DIR=%%i"
)

if "%VS_INSTALL_DIR%"=="" (
    echo Visual Studio not found.
    exit /b 1
)

echo Found VS at: %VS_INSTALL_DIR%

call "%VS_INSTALL_DIR%\Common7\Tools\VsDevCmd.bat" -arch=x64

echo Building WickedEngine...
msbuild "%~dp0..\WickedEngine_Windows.vcxproj" /t:Clean;Build /p:Configuration=Debug /p:Platform=x64 /v:m
if %errorlevel% neq 0 (
    echo Build Failed!
    exit /b 1
)

echo Build Successful.
echo Building C_API_Test...

msbuild "%~dp0..\C_API_Test.vcxproj" /t:Clean;Build /p:Configuration=Debug /p:Platform=x64 /v:m
if %errorlevel% neq 0 (
    echo Test Build Failed!
    exit /b 1
)

echo Test Build Successful. Running Test...

set "TEST_EXE=%~dp0..\x64\Debug\C_API_Test.exe"

if not exist "%TEST_EXE%" (
    echo Test executable not found at %TEST_EXE%
    echo Checking alternative paths...
    set "TEST_EXE=%~dp0..\C_API_Test\x64\Debug\C_API_Test.exe"
)

if not exist "%TEST_EXE%" (
    echo Test executable still not found.
    exit /b 1
)

"%TEST_EXE%"

