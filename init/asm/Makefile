all: crti.o crtn.o

crti.o: crti.asm
	nasm -felf32 crti.asm -o $@

crtn.o: crtn.asm
	nasm -felf32 crtn.asm -o $@
