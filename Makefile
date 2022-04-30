CC=gcc 

default:
	$(CC) -Wall -std=c99 src/*.c -IC:/migw_dev_libs/include -LC:/migw_dev_libs/lib -lmingw32 -lSDL2main -lSDL2 -o build/renderer.exe

clean:
	cd build
	rm renderer.exe
	cd ..

run:
	build/renderer.exe