# This section is used to define all the object files in the entire program

################################################################################
# Global Directory
################################################################################
GLOBALS_CPP=kernel/global/cpp/globals.o

GLOBAL_CPP=$(GLOBALS_CPP)

GLOBAL=$(GLOBAL_CPP)
################################################################################


################################################################################
# IO Directory
################################################################################
KEYBOARD_CPP=kernel/io/cpp/keyboard.o
PORT_CPP=kernel/io/cpp/port.o
TERMINAL_CPP=kernel/io/cpp/terminal.o

IO_CPP=$(KEYBOARD_CPP) $(PORT_CPP) $(TERMINAL_CPP)

IO=$(IO_CPP)
################################################################################


################################################################################
# Kernel Nested Directory
################################################################################
KERNEL_CPP=kernel/kernel/cpp/kernel.o

KERNEL_NESTED=$(KERNEL_CPP)
################################################################################


################################################################################
# Setup Directory
################################################################################
GDT_ASM=kernel/setup/asm/gdt.o
IDT_ASM=kernel/setup/asm/idt.o
IRQ_ASM=kernel/setup/asm/irq.o
ISR_ASM=kernel/setup/asm/isr.o

GDT_CPP=kernel/setup/cpp/gdt.o
IDT_CPP=kernel/setup/cpp/idt.o
MM_CPP=kernel/setup/cpp/memorymap.o

SETUP_ASM=$(GDT_ASM) $(IDT_ASM) $(IRQ_ASM) $(ISR_ASM) $(MM_ASM)
SETUP_CPP=$(GDT_CPP) $(IDT_CPP) $(MM_CPP)

SETUP=$(SETUP_ASM) $(SETUP_CPP)
################################################################################


################################################################################
# Experimental Directory
################################################################################

################################################################################


################################################################################
# Boot Directory
################################################################################
BOOT_ASM=boot/asm/boot.o

BOOT_NESTED=$(BOOT_ASM)

BOOT=$(BOOT_NESTED)
################################################################################


################################################################################
# Init Directory
################################################################################
CRTI_ASM=init/asm/crti.o
CRTN_ASM=init/asm/crtn.o

INIT_ASM=$(CRTI_ASM) $(CRTN_ASM)

INIT=$(INIT_ASM)
################################################################################


################################################################################
# Kernel Directory
################################################################################
KERNEL=$(GLOBAL) $(IO) $(KERNEL_NESTED) $(SETUP) $(EXPERIMENTAL)
################################################################################


################################################################################
# Home Directory
################################################################################
OBJS=$(KERNEL) $(BOOT)
################################################################################
# This section is used for compiling cpp files
CFLAGS1=-fno-exceptions -fno-rtti -fno-use-cxa-atexit
CFLAGS2=-ffreestanding -O2 -Wall -Wextra -std=c++11
CFLAGS=$(CFLAGS1) $(CFLAGS2)
CC=i686-elf-g++ -c


# This section is used for linking object files
CC_LINKER=i686-elf-g++ -T
FLAGS_LINKER=-ffreestanding -O2 -nostdlib -fno-exceptions -fno-rtti -lgcc


# This section is used to create the CRT files ourselves
CRTI_OBJ=$(CRTI_ASM)
CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
CRTN_OBJ=$(CRTN_ASM)
################################################################################
# List of our objects that need to be linked together
#
# NOTE: It's been noted that this needs to be created in this specific order or
# else strange bugs may be introduced. The information regarding this can be
# found here:
#
# http://wiki.osdev.org/Calling_Global_Constructors
#
################################################################################
OBJ_LINK_LIST:=$(CRTI_OBJ) $(CRTBEGIN_OBJ) $(OBJS) $(CRTEND_OBJ) $(CRTN_OBJ)

# Start our Makefile calling tree
all:
	+$(MAKE) -C boot
	+$(MAKE) -C init
	+$(MAKE) -C kernel

# This builds the bootable iso
build: $(CRTI_OBJ) $(CRTBEGIN_OBJ) $(OBJS) Regalia.bin
	grub2-mkrescue -o Regalia.iso loader

os:
	clear; make -s; make -s build;

# This links the object files together
Regalia.bin: linker.ld
	$(CC_LINKER) linker.ld $(OBJ_LINK_LIST) $(FLAGS_LINKER) -o $@
	mv Regalia.bin loader/boot/Regalia.bin

# Remove all unneeded files
clean:
	rm -f Regalia.iso Regalia.bin
