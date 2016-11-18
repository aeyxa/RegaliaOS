#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>
#include <stdint.h>

struct regs {
     uint32_t gs, fs, es, ds; /* pushed the segs last */
     uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; /* pushed by 'pusha' */
     uint32_t int_no, err_code; /* our 'push byte #' and ecodes do this */
     uint32_t eip, cs, eflags, useresp, ss; /* pushed by the processor automatically */
};

uint8_t inportb (unsigned short port);
void outportb (uint16_t port, uint8_t data);

#endif
