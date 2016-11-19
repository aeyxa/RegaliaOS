#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>
#include <stdint.h>

/*
struct regs {
     uint32_t gs, fs, es, ds;
     uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
     uint32_t int_no, err_code;
     uint32_t eip, cs, eflags, useresp, ss;
};
*/

struct Registers {
     uint32_t gs, fs, es, ds;
     uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
     uint32_t int_no, err_code;
     uint32_t eip, cs, eflags, useresp, ss;
};


uint8_t inportb (unsigned short port);
void outportb (uint16_t port, uint8_t data);

#endif
