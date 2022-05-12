CC=gcc 
MINGW_INC_PATH=C:/migw_dev_libs/include
MINGW_LIB_PATH=C:/migw_dev_libs/lib

default:
	$(CC) -Wall -std=c99 src/*.c -I$(MINGW_INC_PATH) -L$(MINGW_LIB_PATH) -lmingw32 -lSDL2main -lSDL2 -lm -o build/renderer.exe

clean:
	cd build
	rm renderer.exe
	cd ..

run: default
	build/renderer.exe