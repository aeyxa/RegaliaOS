#include <Common/common.h>
#include <Regalia/kernel.h>
#include <Regalia/terminal.h>
#include <Regalia/gdt.h>
#include <Regalia/idt.h>
#include <Regalia/isr.h>
#include <Regalia/irq.h>
#include <Regalia/keyboard.h>
#include <Global/globals.h>

#define ever ;;

void kernel_main(void)
{
  terminal << "Regalia\n\nLoading Operating System...\n\n\n";

  Regalia::GlobalDescriptorTable gdt;
  Regalia::InterruptDescriptorTable idt;

  __asm__ __volatile__ ("sti");

  for(ever);
}
