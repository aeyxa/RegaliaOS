#pragma once

#include <stddef.h>
#include <stdint.h>

struct Registers
{
     uint32_t gs, fs, es, ds;
     uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
     uint32_t int_no, err_code;
     uint32_t eip, cs, eflags, useresp, ss;
};
