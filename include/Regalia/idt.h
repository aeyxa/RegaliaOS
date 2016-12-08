#pragma once

#include <Common/common.h>
#include <Regalia/keyboard.h>

extern "C" void idt_load();

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
      void Handler(struct Registers* registers) asm("ISR_Handler");
    };
    class InterruptHardwareRequest
    {
    public:
      InterruptHardwareRequest();
      ~InterruptHardwareRequest();
      void Configure(Regalia::InterruptDescriptorTable* const IDT);
      void Handler(struct Registers* registers) asm("IRQ_Handler");
      void Remap();
      void LoadHandler(uint32_t irq,void(*handler)(struct Registers*registers));
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

    void InterruptDescriptorTableBegin(); // IDT
    void InterruptServicesRequestBegin(); // ISR
    void InterruptHardwareRequestBegin(); // IRQ

    void InterruptDescriptorTableStart();

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
