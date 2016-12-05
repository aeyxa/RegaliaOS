#include <Common/common.h>
#include <Regalia/kernel.h>
#include <Regalia/terminal.h>
#include <Regalia/gdt.h>
#include <Regalia/idt.h>
#include <Regalia/isr.h>
#include <Regalia/irq.h>
#include <Regalia/keyboard.h>
#include <Regalia/multiboot.h>
#include <Global/globals.h>

#define ever ;;

char* itoa(int val, int base)
{
	static char buf[32] = {0};

	int i = 30;

	for(; val && i ; --i, val /= base)

		buf[i] = "0123456789ABCDEF"[val % base];

	return &buf[i+1];
}


void kernel_main(multiboot_info_t* mbd, unsigned int magic)
{
  terminal << "Regalia\n\nLoading Operating System...\n\n\n";

  Regalia::GlobalDescriptorTable gdt;
  Regalia::InterruptDescriptorTable idt;

  __asm__ __volatile__ ("sti");

  memory_map_t* mmap = (memory_map_t*) mbd->mmap_addr;

  terminal << itoa(mbd->mem_upper,16);

  for(ever);
}
