all: boot.o

boot.o: boot.asm
	nasm -felf32 boot.asm -o $@
