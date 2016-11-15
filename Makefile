
Regalia.iso: boot.o kernel.o terminal.o port.o gdt.o idt.o idt_asm.o Regalia.bin
	grub2-mkrescue -o Regalia.iso loader

boot.o: boot.asm
	nasm -felf32 boot.asm -o boot.o

kernel.o: kernel.cpp common.h
	i686-elf-g++ -c kernel.cpp -o kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

terminal.o: terminal.cpp terminal.h
	i686-elf-g++ -c terminal.cpp -o terminal.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

gdt.o: gdt.cpp gdt.h
	i686-elf-g++ -c gdt.cpp -o gdt.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -fpermissive

idt.o: idt.cpp idt.h
	i686-elf-g++ -c idt.cpp -o idt.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -fpermissive

idt_asm.o: idt.asm
	nasm -felf32 idt.asm -o idt_asm.o

port.o: port.cpp port.h
	i686-elf-g++ -c port.cpp -o port.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -fpermissive

Regalia.bin: linker.ld
	i686-elf-g++ -T linker.ld -o Regalia.bin -ffreestanding -O2 -nostdlib port.o boot.o kernel.o terminal.o gdt.o idt.o idt_asm.o -fno-exceptions -fno-rtti -lgcc
	mv Regalia.bin loader/boot/Regalia.bin

clean:
	rm *.o
