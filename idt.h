#ifndef IDT_H
#define IDT_H

#include "common.h"
#include "gdt.h"

void idt_set_gate(uint8_t num, void(*handler)(), uint16_t sel, uint8_t flags);
void idt_install();

#endif
