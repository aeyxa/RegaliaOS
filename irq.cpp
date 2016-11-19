#include "irq.h"
#include "idt.h"
#include "common.h"
#include "terminal.h"

/**
void *irq_routines[16] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};
*/
/*
void irq_install_handler(uint32_t irq, void (*handler)(struct regs *r))
{
    irq_routines[irq] = handler;
}

void irq_uninstall_handler(uint32_t irq)
{
    irq_routines[irq] = 0;
}

void irq_remap(void)
{
    outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    outportb(0x21, 0x00);
    outportb(0xA1, 0x00);
}

void irq_install()
{
    irq_remap();
    idt_set_gate(32, irq0, 0x08, 0x8E);
    idt_set_gate(33, irq1, 0x08, 0x8E);
    idt_set_gate(34, irq2, 0x08, 0x8E);
    idt_set_gate(35, irq3, 0x08, 0x8E);
    idt_set_gate(36, irq4, 0x08, 0x8E);
    idt_set_gate(37, irq5, 0x08, 0x8E);
    idt_set_gate(38, irq6, 0x08, 0x8E);
    idt_set_gate(39, irq7, 0x08, 0x8E);
    idt_set_gate(40, irq8, 0x08, 0x8E);
    idt_set_gate(41, irq9, 0x08, 0x8E);
    idt_set_gate(42, irq10, 0x08, 0x8E);
    idt_set_gate(43, irq11, 0x08, 0x8E);
    idt_set_gate(44, irq12, 0x08, 0x8E);
    idt_set_gate(45, irq13, 0x08, 0x8E);
    idt_set_gate(46, irq14, 0x08, 0x8E);
    idt_set_gate(47, irq15, 0x08, 0x8E);
}

void irq_handler(struct regs *r)
{

  void (*handler)(struct regs *r);

  handler = irq_routines[r->int_no];

  if(handler)
  {
      handler(r);
  }

  if(r->int_no >= 8)
  {
      outportb(0xA0, 0x20);
  }
}
*/
