BIN=bin/Prog.exe
OBJECTS=src/main.o
CC=gcc
CFLAGS=-I include -L lib -lmingw32 -lSDL2main -lSDL2

all: $(OBJECTS)
	$(CC) -o $(BIN) $(OBJECTS) $(CFLAGS)

main.o: main.c
	$(CC) -c src/main.c $(CFLAGS)

clear:
	del *.o *.exe