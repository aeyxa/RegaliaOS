#pragma once

#include <Regalia/multiboot.h>
//extern "C" void kernel_main(void);
extern "C" void kernel_main(multiboot_info_t* mbd, unsigned int magic);
