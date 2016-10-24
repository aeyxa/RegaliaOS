#include "common.h"
#include "terminal.h"

extern "C" /* Use C linkage for kernel_main. */

void kernel_main(void)
{
  Regalia::Terminal terminal;
  terminal.print("Regalia");
}
