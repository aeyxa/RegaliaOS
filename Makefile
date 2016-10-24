
aeyOS.iso: boot.o kernel.o aeyOS.bin
	grub2-mkrescue -o aeyOS.iso isodir

boot.o: boot.asm
	nasm -felf32 boot.asm -o boot.o

kernel.o: kernel.cpp
	i686-elf-g++ -c kernel.cpp -o kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

aeyOS.bin: linker.ld
	i686-elf-gcc -T linker.ld -o aeyOS.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc
	mv aeyOS.bin isodir/boot/aeyOS.bin

clean:
	rm *.o
