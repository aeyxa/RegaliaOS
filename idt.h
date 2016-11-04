#ifndef IDT_H
#define IDT_H

#include "common.h"
#include "gdt.h"

namespace Regalia
{
  class InterruptDescriptorTable
  {
  protected:
    struct GateDescriptor
    {
      uint16_t offset_low;
      uint16_t code;
      uint8_t zero;
      uint8_t flags;
      uint16_t offset_high;
    }__attribute__((packed));

    static GateDescriptor idt_gate[256];

    struct InterruptDescriptorTablePointer
    {
      uint16_t size;
      uint32_t base;
    }__attribute__((packed));

  public:
    InterruptDescriptorTable(GlobalDescriptorTable* gdt);
    ~InterruptDescriptorTable();
    void Activate();
    void KeyboardStage(GlobalDescriptorTable* gdt);
    void KeyboardHandler();
    void KeyboardEnable();
    static inline void write(uint16_t _port, uint8_t _data);
    static inline uint8_t read(uint16_t _port);
  };
}

#endif
