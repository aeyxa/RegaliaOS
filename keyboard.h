#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "idt.h"

void keyboard_handler(struct Registers *registers);
void keyboard_install(Regalia::InterruptDescriptorTable* const IDT);

#endif
