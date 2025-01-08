CC=gcc -std=c11
CFLAGS= -Wall 
LDFLAGS= -Wall -lm
EXEC= pvp
all: $(EXEC)

pvp: init.o verif.o pvp.o
	$(CC) -o $@ $^ $(LDFLAGS)

init.o: init.c
	$(CC)  -c $^ $(CFLAGS)

verif.o: verif.c
	$(CC) -c $^ $(CFLAGS)

pvp.o: pvp.c
	$(CC) -c $^ $(CFLAGS)
