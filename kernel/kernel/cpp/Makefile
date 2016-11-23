CFLAGS1=-ffreestanding -O2 -Wall -Wextra -std=c++11 -I../../../include/
CFLAGS2=-fno-exceptions -fno-rtti -fno-use-cxa-atexit
CFLAGS=$(CFLAGS1) $(CFLAGS2)
CC=i686-elf-g++ -c

COMMON_INC=../../../include/Common/common.h
GLOBALS_INC=../../../include/Global/globals.h
REGALIA_INC=../../../include/Regalia

KERNEL=$(REGALIA_INC)/kernel.h
KERNEL_INC=$(KERNEL) $(COMMON_INC)

all: kernel.o

kernel.o: kernel.cpp $(KERNEL_INC)
	$(CC) kernel.cpp -o $@ $(CFLAGS)
