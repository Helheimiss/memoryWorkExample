CC = g++
ARCH = 64
CFLAGS = -m$(ARCH) -Wall -s
src_dllWorkExample = ./dllWorkExample/dllWorkExample.cpp
src_memoryWorkExample = ./memoryWorkExample/memoryWorkExample.cpp


all :
	mkdir -p ./bin
	$(CC) -shared $(CFLAGS) $(src_dllWorkExample)    -o ./bin/dllWorkExample.dll
	$(CC)         $(CFLAGS) $(src_memoryWorkExample) -o ./bin/memoryWorkExample.exe

clean :
	rm ./bin/*