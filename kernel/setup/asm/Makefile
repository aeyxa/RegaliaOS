all: gdt.o idt.o irq.o isr.o

gdt.o: gdt.asm
	nasm -felf32 gdt.asm -o $@

idt.o: idt.asm
	nasm -felf32 idt.asm -o $@

irq.o: irq.asm
	nasm -felf32 irq.asm -o $@

isr.o: isr.asm
	nasm -felf32 isr.asm -o $@

mm.o: mm.asm
	nasm -felf32 mm.asm -o $@
