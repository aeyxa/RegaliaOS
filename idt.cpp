#include "idt.h"
#include "terminal.h"

struct idt_entry
{
  uint16_t base_lo;
  uint16_t sel;
  uint8_t always0;
  uint8_t flags;
  uint16_t base_hi;
}__attribute__((packed));

struct idt_ptr
{
  uint16_t limit;
  uint32_t base;
}__attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

extern "C" void idt_load();

void idt_set_gate(uint8_t num, void(*handler)(), uint16_t sel, uint8_t flags)
{
  idt[num].base_lo = ((uint32_t)handler) & 0xFFFF;
  idt[num].base_hi = ((uint32_t)handler >> 16) & 0xFFFF;
  idt[num].sel = sel;
  idt[num].flags = flags;
  idt[num].always0 = 0;
}

void idt_install()
{
  idtp.limit = ((sizeof(struct idt_entry) * 256) - 1);
  idtp.base = &idt;

  idt_load();
}
