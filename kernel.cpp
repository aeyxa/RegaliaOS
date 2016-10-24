#include "common.h"
#include "terminal.h"

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif

void kernel_main(void)
{
  aeyOS::Terminal terminal;
  terminal.print("aeyOS");
}
