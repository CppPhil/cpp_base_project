@echo off 

REM Install git dependencies
set "GITHUB=https://github.com"
set "LIB_PATH=%~dp0%libraries"
set "PHILSLIB_PATH=%LIB_PATH%\philslib"
set "EXPECTED_LITE_PATH=%LIB_PATH%\expected-lite"
set "BRIGAND_PATH=%LIB_PATH%\brigand"
set "CLANG_FMT_PATH=%~dp0%clang-format"

call :delete_directory_if_exists %PHILSLIB_PATH%
call :delete_directory_if_exists %EXPECTED_LITE_PATH%
call :delete_directory_if_exists %BRIGAND_PATH%
call :delete_directory_if_exists %CLANG_FMT_PATH%

git clone %GITHUB%/CppPhil/philslib.git %PHILSLIB_PATH%
git clone %GITHUB%/martinmoene/expected-lite.git %EXPECTED_LITE_PATH%
git clone %GITHUB%/edouarda/brigand.git %BRIGAND_PATH%
git clone %GITHUB%/CppPhil/clang-format.git %CLANG_FMT_PATH%


REM Install vcpkg
set "PACKAGE_MANAGER_PATH=%~dp0%package_manager"
set "VCPKG_PATH=%PACKAGE_MANAGER_PATH%\vcpkg"
set "VCPKG=%VCPKG_PATH%\vcpkg.exe"

call :delete_directory_if_exists %VCPKG_PATH%

git clone %GITHUB%/Microsoft/vcpkg %VCPKG_PATH%
call %VCPKG_PATH%\bootstrap-vcpkg.bat
%VCPKG% update
%VCPKG% install boost
%VCPKG% install ms-gsl
%VCPKG% install doctest
%VCPKG% install fmt
EXIT /B 0


:delete_directory_if_exists
    IF EXIST "%~1%" (
        rmdir /s /q "%~1%"
    )
    EXIT /B 0
