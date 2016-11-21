#include "common.h"
#include "terminal.h"
#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "irq.h"
#include "keyboard.h"
#include "globals.h"

#define ever ;;

extern "C" void kernel_main(void)
{
  terminal.print("Regalia");

  Regalia::GlobalDescriptorTable gdt;
  Regalia::InterruptDescriptorTable idt;

  __asm__ __volatile__ ("sti");

  // Loop forever
  for(ever);
}
