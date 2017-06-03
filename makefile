CC = gcc
CFLAGS = -Wall -m64
LDFLAGS = $(shell pkg-config --cflags --libs allegro-5.0 allegro_dialog-5.0 allegro_image-5.0)
all: main.o transform.o
	$(CC) $(CFLAGS)  main.o transform.o -o Affinite 

transform.o: transform.asm
	nasm -f elf64 -o transform.o transform.asm

main.o: main.c transform.h
	$(CC) $(CFLAGS) -c -o main.o main.c 
clean:
	rm -f *.o

