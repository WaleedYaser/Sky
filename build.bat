@echo off

call "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd" -arch=amd64

SETLOCAL

SET ROOT_DIR=%~dp0
SET BUILD_DIR=%ROOT_DIR%build\
SET CODE_DIR=%ROOT_DIR%code\

if not exist %BUILD_DIR% mkdir %BUILD_DIR%
pushd %BUILD_DIR%

SET COMMON_COMPILE_OPTIONS=/MTd /nologo /GR- /EHa /Od /Oi /WX /W4 /wd4201 /wd4100 /wd4109 /FC /Z7
SET COMMON_LINK_OPTIONS=/incremental:no /opt:ref

del *.pdb >nul 2>&1
SET SKY_GAME_PDB=sky_game_%random%.pdb

SET SKY_GAME_COMPILE_OPTIONS=%COMMON_COMPILE_OPTIONS% /Fe: sky_game /Fm: sky_game.map /LD
SET SKY_GAME_LINK_OPTIONS=%COMMON_LINK_OPTIONS% /PDB:%SKY_GAME_PDB%
SET SKY_GAME_LIBS=opengl32.lib

cl %SKY_GAME_COMPILE_OPTIONS% %CODE_DIR%sky_game.cpp /link %SKY_GAME_LINK_OPTIONS% %SKY_GAME_LIBS%

SET SKY_WIN32_COMPILE_OPTIONS=%COMMON_COMPILE_OPTIONS% /Fe: sky.exe /Fm: sky.map
SET SKY_WIN32_LINK_OPTIONS=%COMMON_LINK_OPTIONS%
SET SKY_WIN32_LIBS=sky_game.lib User32.lib Gdi32.lib Winmm.lib opengl32.lib

cl %SKY_WIN32_COMPILE_OPTIONS% %CODE_DIR%sky_win32.cpp /link %SKY_WIN32_LINK_OPTIONS% %SKY_WIN32_LIBS%

ENDLOCAL