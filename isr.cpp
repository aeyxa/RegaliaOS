#include "isr.h"
#include "terminal.h"
#include "common.h"

/*

extern "C" void isr0();
extern "C" void isr1();
extern "C" void isr2();
extern "C" void isr3();
extern "C" void isr4();
extern "C" void isr5();
extern "C" void isr6();
extern "C" void isr7();
extern "C" void isr8();
extern "C" void isr9();
extern "C" void isr10();
extern "C" void isr11();
extern "C" void isr12();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();

void isr_install()
{
  idt_set_gate(0,isr0,0x08,0x8E);
  idt_set_gate(1,isr1,0x08,0x8E);
  idt_set_gate(2,isr2,0x08,0x8E);
  idt_set_gate(3,isr3,0x08,0x8E);
  idt_set_gate(4,isr4,0x08,0x8E);
  idt_set_gate(5,isr5,0x08,0x8E);
  idt_set_gate(6,isr6,0x08,0x8E);
  idt_set_gate(7,isr7,0x08,0x8E);
  idt_set_gate(8,isr8,0x08,0x8E);
  idt_set_gate(9,isr9,0x08,0x8E);
  idt_set_gate(10,isr10,0x08,0x8E);
  idt_set_gate(11,isr11,0x08,0x8E);
  idt_set_gate(12,isr12,0x08,0x8E);
  idt_set_gate(13,isr13,0x08,0x8E);
  idt_set_gate(14,isr14,0x08,0x8E);
  idt_set_gate(15,isr15,0x08,0x8E);
  idt_set_gate(16,isr16,0x08,0x8E);
  idt_set_gate(17,isr17,0x08,0x8E);
  idt_set_gate(18,isr18,0x08,0x8E);
  idt_set_gate(19,isr19,0x08,0x8E);
  idt_set_gate(20,isr20,0x08,0x8E);
  idt_set_gate(21,isr21,0x08,0x8E);
  idt_set_gate(22,isr22,0x08,0x8E);
  idt_set_gate(23,isr23,0x08,0x8E);
  idt_set_gate(24,isr24,0x08,0x8E);
  idt_set_gate(25,isr25,0x08,0x8E);
  idt_set_gate(26,isr26,0x08,0x8E);
  idt_set_gate(27,isr27,0x08,0x8E);
  idt_set_gate(28,isr28,0x08,0x8E);
  idt_set_gate(29,isr29,0x08,0x8E);
  idt_set_gate(30,isr30,0x08,0x8E);
  idt_set_gate(31,isr31,0x08,0x8E);
}

static const char * exception_messages[] =
{
  "Division by zero",
  "Debug",
  "Non-maskable interrupt",
  "Breakpoint",
  "Detected overflow",
  "Out-of-bounds",
  "Invalid opcode",
  "No coprocessor",
  "Double fault",
  "Coprocessor segment overrun",
  "Bad TSS",
  "Segment not present",
  "Stack fault",
  "General protection fault",
  "Page fault",
  "Unknown interrupt",
  "Coprocessor fault",
  "Alignment check",
  "Machine check",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved"
};

extern "C" void exception_handler(struct regs *r)
{
  if(r->int_no < 32)
  {
    Regalia::Terminal terminal;
    terminal.print(exception_messages[r->int_no]);
  }
}

*/
