
Regalia.iso: boot.o kernel.o terminal.o globals.o port.o gdt.o gdt_asm.o idt.o idt_asm.o isr_asm.o irq_asm.o keyboard.o Regalia.bin
	grub2-mkrescue -o Regalia.iso loader

boot.o: boot.asm
	nasm -felf32 boot.asm -o boot.o

kernel.o: kernel.cpp common.h
	i686-elf-g++ -c kernel.cpp -o kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

terminal.o: terminal.cpp terminal.h common.h
	i686-elf-g++ -c terminal.cpp -o terminal.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

globals.o: globals.cpp globals.h common.h terminal.cpp terminal.h
	i686-elf-g++ -c globals.cpp -o globals.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

combined:o globals.o terminal.o
	i686-elf-g++ -c globals.o terminal.o -o combined.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

gdt.o: gdt.cpp gdt.h common.h
	i686-elf-g++ -c gdt.cpp -o gdt.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -fpermissive

gdt_asm.o: gdt.asm
	nasm -felf32 gdt.asm -o gdt_asm.o

idt.o: idt.cpp idt.h common.h
	i686-elf-g++ -c idt.cpp -o idt.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -fpermissive

idt_asm.o: idt.asm
	nasm -felf32 idt.asm -o idt_asm.o

isr_asm.o: isr.asm
	nasm -felf32 isr.asm -o isr_asm.o

irq_asm.o: irq.asm
	nasm -felf32 irq.asm -o irq_asm.o

port.o: port.cpp port.h common.h
	i686-elf-g++ -c port.cpp -o port.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -fpermissive

keyboard.o: keyboard.cpp keyboard.h common.h
	i686-elf-g++ -c keyboard.cpp -o keyboard.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -fpermissive

Regalia.bin: linker.ld
	i686-elf-g++ -T linker.ld -o Regalia.bin -ffreestanding -O2 -nostdlib boot.o kernel.o terminal.o globals.o port.o gdt.o gdt_asm.o idt.o idt_asm.o isr_asm.o irq_asm.o keyboard.o -fno-exceptions -fno-rtti -lgcc
	mv Regalia.bin loader/boot/Regalia.bin

clean:
	rm *.o
