CFLAGS1=-fno-exceptions -fno-rtti -fno-use-cxa-atexit
CFLAGS2=-ffreestanding -O2 -Wall -Wextra -std=c++11 -I../../../include/
CFLAGS=$(CFLAGS1) $(CFLAGS2)
CC=i686-elf-g++ -c

COMMON_INC=../../../include/Common/common.h
EXPERIMENTAL_INC=../../../include/Experimental

TERMINAL=$(EXPERIMENTAL_INC)/terminal.h

TERMINAL_INC=$(TERMINAL) $(COMMON_INC)

all: terminal.o

terminal.o: terminal_experimental.cpp $(TERMINAL_INC)
	$(CC) terminal_experimental.cpp -o $@ $(CFLAGS)
