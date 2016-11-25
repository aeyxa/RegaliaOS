CFLAGS1=-ffreestanding -O2 -Wall -Wextra -std=c++11 -I../../../include/
CFLAGS2=-fno-exceptions -fno-rtti -fno-use-cxa-atexit
CFLAGS=$(CFLAGS1) $(CFLAGS2)
CC=i686-elf-g++ -c

COMMON_INC=../../../include/Common/common.h
GLOBALS_INC=../../../include/Global/globals.h
REGALIA_INC=../../../include/Regalia

GDT=$(REGALIA_INC)/gdt.h
IDT=$(REGALIA_INC)/idt.h

GDT_INC=$(GDT) $(COMMON_INC)
IDT_INC=$(IDT) $(COMMON_INC)

all: gdt.o idt.o

gdt.o: gdt.cpp $(GDT_INC)
	$(CC) gdt.cpp $(CFLAGS) -o $@

idt.o: idt.cpp $(IDT_INC)
	$(CC) idt.cpp $(CFLAGS) -o $@
