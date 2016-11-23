CFLAGS1=-ffreestanding -O2 -Wall -Wextra -std=c++11 -I../../../include/
CFLAGS2=-fno-exceptions -fno-rtti -fno-use-cxa-atexit
CFLAGS=$(CFLAGS1) $(CFLAGS2)
CC=i686-elf-g++ -c

COMMON_INC=../../../include/Common/common.h
GLOBALS_INC=../../../include/Global/globals.h

INCLUDES=$(COMMON_INC) $(GLOBALS_INC)

all: globals.o

globals.o: globals.cpp $(INCLUDES)
	$(CC) globals.cpp -o $@ $(CFLAGS)
