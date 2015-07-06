CC=gcc
CFLAGS=-I. -std=gnu99

elfmope: elf.c pe.c main.c
	$(CC) -o elfmope elf.c pe.c main.c $(CFLAGS)
