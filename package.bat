@echo off

SETLOCAL

SET ROOT_DIR=%~dp0
SET BUILD_DIR=%ROOT_DIR%build\
SET PACKAGE_DIR=%ROOT_DIR%package

if exist %BUILD_DIR% rmdir /S /Q %BUILD_DIR%
call %ROOT_DIR%build.bat

if exist %PACKAGE_DIR% rmdir /S /Q %PACKAGE_DIR%
mkdir %PACKAGE_DIR%

for /R %BUILD_DIR% %%f in (*.exe) do copy %%f %PACKAGE_DIR%
for /R %BUILD_DIR% %%f in (*.dll) do copy %%f %PACKAGE_DIR%