#include "common.h"
#include "terminal.h"
#include "gdt.h"
#include "idt.h"

#define ever ;;

extern "C" void kernel_main(void)
{
  Regalia::Terminal terminal;
  terminal.print("Regalia");

  Regalia::GlobalDescriptorTable gdt;
  Regalia::InterruptDescriptorTable idt(&gdt);
  idt.Activate();
  idt.KeyboardEnable();
  for(ever);
}
