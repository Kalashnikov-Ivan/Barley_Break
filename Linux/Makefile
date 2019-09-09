CC=gcc
CFLAGS=-c -Wall -std=c99 -O3 -lncurses

all : barleyBreak.elf

barleyBreak.elf : main.o barley.o
	$(CC) main.o barley.o -o barleyBreak.elf -lncurses

main.o : main.c
	$(CC) $(CFLAGS) main.c

barley.o : barley.c
	$(CC) $(CFLAGS) barley.c
	
clean:
	rm -rf *.o