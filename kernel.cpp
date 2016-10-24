#include <stddef.h>
#include <stdint.h>

uint16_t* terminal_buffer;

void terminal_initialize(void)
{

	terminal_buffer = (uint16_t*) 0xB8000;

  terminal_buffer[0] = (uint16_t) 2920;
  terminal_buffer[1] = (uint16_t) 2921;
}

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif

void kernel_main(void)
{
  terminal_initialize();
}
