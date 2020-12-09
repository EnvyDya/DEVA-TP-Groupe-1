BIN=bin/TachiAi.exe
OBJECTS=src/main.o src/bouge.o src/affichage.o src/alea.o
CC=gcc
CFLAGS=-I include -L lib -lmingw32 -lSDL2main -lSDL2

all: $(OBJECTS)
	$(CC) -o $(BIN) $(OBJECTS) $(CFLAGS)

main.o: main.c
	$(CC) -c src/main.c $(CFLAGS)

bouge.o: bouge.c
	$(CC) -c src/bouge.c $(CFLAGS)

affichage.o: affichage.c
	$(CC) -c src/affichage.c $(CFLAGS)

alea.o: alea.c
	$(CC) -c src/alea.c $(CFLAGS)
	
clear:
	del bin\*.exe src\*.o

clearO:
	del src\*.o