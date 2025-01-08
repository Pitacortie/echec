CC=gcc -std=c11
CFLAGS= -Wall 
LDFLAGS= -Wall -lm
EXEC= main
all: $(EXEC)

main: init.o verif.o pvp.o main.o
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: main.c
	$(CC)  -c $^ $(CFLAGS)

init.o: init.c
	$(CC)  -c $^ $(CFLAGS)

verif.o: verif.c
	$(CC) -c $^ $(CFLAGS)

pvp.o: pvp.c
	$(CC) -c $^ $(CFLAGS)
