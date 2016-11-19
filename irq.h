#ifndef IRQ_H
#define IRQ_H

#include "common.h"

extern "C" void irq0();
extern "C" void irq1();
extern "C" void irq2();
extern "C" void irq3();
extern "C" void irq4();
extern "C" void irq5();
extern "C" void irq6();
extern "C" void irq7();
extern "C" void irq8();
extern "C" void irq9();
extern "C" void irq10();
extern "C" void irq11();
extern "C" void irq12();
extern "C" void irq13();
extern "C" void irq14();
extern "C" void irq15();

//void irq_install_handler(uint32_t irq, void (*handler)(struct regs *r));
//void irq_uninstall_handler(uint32_t irq);
//void irq_remap(void);
//void irq_install(void);
//extern "C" void irq_handler(struct regs *r);

#endif