#include "common.h"
#include "terminal.h"
#include "gdt.h"
#include "idt.h"
#include "isr.h"

#define ever ;;

extern "C" void kernel_main(void)
{
  Regalia::Terminal terminal;
  terminal.print("Regalia");

  // Global Descriptor Table
  Regalia::GlobalDescriptorTable gdt;

  // Interrupt Descriptor Table
  idt_install();

  isr_install();

  //__asm__ __volatile__ ("sti");

  // Start listening for interrupts
  //idt.Activate();

  // Loop forever
  for(ever);
}
