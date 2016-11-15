#ifndef __IDT_H
#define __IDT_H

#include "common.h"
#include "gdt.h"
#include "port.h"

namespace Regalia
{
  class InterruptManager
  {
  protected:
    struct GateDescriptor
    {
      uint16_t handlerAddressLow;
      uint16_t gdt_codeSegmentSelector;
      uint8_t zero;
      uint8_t access;
      uint16_t handlerAddressHigh;
    }__attribute__((packed)); // needs to be specific like gdt

    static GateDescriptor idt[256]; // idt has a max of 256

    // This will point to the idt in memory
    struct InterruptDescriptorTablePointer
    {
      uint16_t size;
      uint32_t base;
    }__attribute__((packed)); // needs to be specific

    // This is used to set the specific things inside GateDescriptor
    static void SetInterruptDescriptorTableEntry
    (
      uint8_t interruptNumber,
      uint16_t codeSegmentSelectorOffset,
      void (*handler)(),
      uint8_t DescriptorPrivilegeLevel,
      uint8_t DescriptorType
    );

    Port8BitSlow picMasterCommand;
    Port8BitSlow picMasterData;
    Port8BitSlow picSlaveCommand;
    Port8BitSlow picSlaveData;

  public:
    InterruptManager(GlobalDescriptorTable* gdt);
    ~InterruptManager();

    void Activate();

    // This function is called from idt.asm
    static uint32_t HandleInterrupt(uint8_t interruptNumber, uint32_t esp);

    static void IgnoreInterruptRequest();     // This is for unused interrupts
    static void HandleInterruptRequest0x00(); // 0x00 is timer interrupt
    static void HandleInterruptRequest0x01(); // 0x01 is keyboard interrupt
  };
}

#endif
