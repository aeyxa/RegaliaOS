#include "common.h"
#include "terminal.h"
#include "gdt.h"

#define ever ;;

extern "C" void kernel_main(void)
{
  Regalia::Terminal terminal;
  terminal.print("Regalia");

  Regalia::GlobalDescriptorTable gdt;

  for(ever);
}
