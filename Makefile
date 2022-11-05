CC=gcc 
MINGW_INC_PATH=D:/dev/libraries/mingw/SDL2-devel-2.24.2-mingw/SDL2-2.24.2/x86_64-w64-mingw32/include/SDL2
MINGW_LIB_PATH=D:/dev/libraries/mingw/SDL2-devel-2.24.2-mingw/SDL2-2.24.2/x86_64-w64-mingw32/lib
CLANG_INC_PATH=""
CLANG_LIB_PATH=""

default:
	$(CC) -Wall -std=c99 src/*.c -I$(MINGW_INC_PATH) -L$(MINGW_LIB_PATH) -lmingw32 -lSDL2main -lSDL2 -lm -o build/renderer.exe

clean:
	cd build
	rm renderer.exe
	cd ..

run: default
	build/renderer.exe