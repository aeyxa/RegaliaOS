#ifndef IDT_H
#define IDT_H

#include "common.h"
#include "gdt.h"
#include "isr.h" // These are required
#include "irq.h" // These are required

extern "C"
{
  void idt_load();
}

namespace Regalia
{
  class InterruptDescriptorTable
  {
  private:
    class InterruptServicesRequest
    {
    public:
      InterruptServicesRequest();
      ~InterruptServicesRequest();
      void Configure(Regalia::InterruptDescriptorTable* const IDT);
      void Handler();
    };
    class InterruptHardwareRequest
    {
    public:
      InterruptHardwareRequest();
      ~InterruptHardwareRequest();
      void Configure(Regalia::InterruptDescriptorTable* const IDT);
      void Handler(struct Registers* registers);
      void Remap();
      void LoadHandler(uint32_t irq,void(*handler)(struct Registers*registers));
      void *Routines[16] =
      {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
      };
    };

    void InterruptDescriptorTableEntry
    (uint8_t num, void(*handler)(), uint16_t sel, uint8_t flags);

    struct IDT_Entry
    {
      uint16_t base_low;
      uint16_t selector;
      uint8_t always0;
      uint8_t flags;
      uint16_t base_high;
    }__attribute__((packed));

    IDT_Entry entry[256];

    void InterruptDescriptorTableStart(); // IDT
    void InterruptServicesRequestStart(); // ISR
    void InterruptHardwareRequestStart(); // IRQ
  public:
    struct IDT_Pointer
    {
      uint16_t limit;
      uint32_t base;
    }__attribute__((packed));

    InterruptDescriptorTable();
    ~InterruptDescriptorTable();
  };
}
//void irq_install_handler(uint32_t irq, void (*handler)(struct regs *r));
//void idt_set_gate(uint8_t num, void(*handler)(), uint16_t sel, uint8_t flags);
//void idt_install();

#endif
