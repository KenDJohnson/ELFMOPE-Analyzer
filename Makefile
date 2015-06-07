CC=gcc
CFLAGS=-I.

elfmope: elf.c pe.c main.c
	$(CC) -o elfmope elf.c pe.c main.c -I.
