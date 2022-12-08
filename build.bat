@echo off

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

REM INCLUDES
set sdl_inc_path="D:\dev\libraries\SDL2-devel-2.24.2-VC\SDL2-2.24.2\include"
set sdl_lib_path="D:\dev\libraries\SDL2-devel-2.24.2-VC\SDL2-2.24.2\lib\x64"
set output_dir="build\"

cl /nologo /Zi /Fd"build/" /Fo"build/" /Fe"build/renderer.exe" /I %sdl_inc_path% src\*.c SDL2.lib SDL2main.lib shell32.lib /link /SUBSYSTEM:WINDOWS /LIBPATH:%sdl_lib_path% 


