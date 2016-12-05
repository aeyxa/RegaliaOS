CFLAGS1=-ffreestanding -O2 -Wall -Wextra -std=c++11 -I../../../include/
CFLAGS2=-fno-exceptions -fno-rtti -fno-use-cxa-atexit
CFLAGS=$(CFLAGS1) $(CFLAGS2)
CC=i686-elf-g++ -c

COMMON_INC=../../../include/Common/common.h
GLOBALS_INC=../../../include/Global/globals.h
REGALIA_INC=../../../include/Regalia

KEYBOARD=$(REGALIA_INC)/keyboard.h
PORT=$(REGALIA_INC)/port.h
TERMINAL=$(REGALIA_INC)/terminal.h

KEYBOARD_INC=$(KEYBOARD) $(COMMON_INC) $(GLOBAL_INC)
PORT_INC=$(PORT) $(COMMON_INC)
TERMINAL_INC=$(TERMINAL) $(COMMON_INC)

all: keyboard.o port.o terminal.o

keyboard.o: keyboard.cpp $(KEYBOARD_INC)
	$(CC) keyboard.cpp -o $@ $(CFLAGS)

port.o: port.cpp $(PORT_INC)
	$(CC) port.cpp -o $@ $(CFLAGS)

terminal.o: terminal.cpp $(TERMINAL_INC)
	$(CC) terminal.cpp -o $@ $(CFLAGS)
