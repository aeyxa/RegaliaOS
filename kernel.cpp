#include "common.h"
#include "terminal.h"

extern "C" /* Use C linkage for kernel_main. */

void kernel_main(void)
{
  aeyOS::Terminal terminal;
  terminal.print("aeyOS");
}
