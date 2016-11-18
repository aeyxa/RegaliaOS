#ifndef IRQ_H
#define IRQ_H

#include "common.h"

void irq_install_handler(uint32_t irq, void (*handler)(struct regs *r));
void irq_uninstall_handler(uint32_t irq);
void irq_remap(void);
void irq_install(void);
extern "C" void irq_handler(struct regs *r);

#endif
