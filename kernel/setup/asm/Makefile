all: gdt.o idt.o irq.o isr.o paging.o

gdt.o: gdt.asm
	nasm -felf32 gdt.asm -o $@

idt.o: idt.asm
	nasm -felf32 idt.asm -o $@

irq.o: irq.asm
	nasm -felf32 irq.asm -o $@

isr.o: isr.asm
	nasm -felf32 isr.asm -o $@

paging.o: paging.asm
	nasm -felf32 paging.asm -o $@
