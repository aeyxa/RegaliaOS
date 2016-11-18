#include "common.h"
#include "terminal.h"
#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "irq.h"
#include "keyboard.h"

#define ever ;;

uint8_t inportb (unsigned short port)
{
    uint8_t rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (port));
    return rv;
}

void outportb (uint16_t port, uint8_t data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
}

extern "C" void kernel_main(void)
{
  Regalia::Terminal terminal;
  terminal.print("Regalia");

  Regalia::GlobalDescriptorTable gdt;
  //gdt_install();
  idt_install();
  isr_install();
  irq_install();
  keyboard_install();

  __asm__ __volatile__ ("sti");

  // Loop forever
  for(ever);
}
