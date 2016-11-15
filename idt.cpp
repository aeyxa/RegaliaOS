#include "idt.h"
#include "terminal.h"

Regalia::InterruptManager::GateDescriptor Regalia::InterruptManager::idt[256];

Regalia::InterruptManager::InterruptManager(GlobalDescriptorTable* gdt) :
  picMasterCommand(0x20),picMasterData(0x21),
  picSlaveCommand(0xA0),picSlaveData(0xA1)
{
  // This comes from gdt.cpp (which was passed from kernel.cpp)
  uint32_t CodeSegment = gdt->CodeSegmentSelector();

  const uint8_t IDT_INTERRUPT_GATE = 0xE;

  /**
  * Here we set all the unspecified interrupts using InterruptIgnore().
  *
  * This is important because if the cpu receives an interrupt that it is not
  * able to handle, this will produce a kernel crash.
  */
  Regalia::Terminal terminal;

  for(uint16_t i = 0; i < 256; i++)
  {
    SetInterruptDescriptorTableEntry
    (i,CodeSegment,&IgnoreInterruptRequest,0,IDT_INTERRUPT_GATE);
  }
  terminal.print("END");
  // These are the interrupt numbers for timer and keyboard interrupts.
  const uint8_t IDT_TIMER = 0x20;
  const uint8_t IDT_KEYBOARD = 0x21;

  // Set timer interrupt
  SetInterruptDescriptorTableEntry
  (IDT_TIMER,CodeSegment,&HandleInterruptRequest0x00,0,IDT_INTERRUPT_GATE);
  terminal.print("ONE");
  // Set keyboard interrupt
  SetInterruptDescriptorTableEntry
  (IDT_KEYBOARD,CodeSegment,&HandleInterruptRequest0x01,0,IDT_INTERRUPT_GATE);
  terminal.print("TWO");
  /**
  * Here we are specifying the interrupt numbers to not overwrite the existing
  * interrupts that are used by the CPU already.
  */
  picMasterCommand.Write(0x11);
  picSlaveCommand.Write(0x11);

  picMasterData.Write(0x20);
  picSlaveData.Write(0x28);

  /**
  * ICW3
  *
  * Here we tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
  * and we tell Slave PIC its cascade identity (0000 0010).
  */
  picMasterData.Write(0x04);
  picSlaveData.Write(0x02);

  // Here we specify 8086 mode
  picMasterData.Write(0x01);
  picSlaveData.Write(0x01);

  // Here we restore defaults
  picMasterData.Write(0x00);
  picSlaveData.Write(0x00);

  // Create a pointer to the idt
  InterruptDescriptorTablePointer idt_pointer;

  // idt has a max of 256 entries
  idt_pointer.size = 256 * sizeof(GateDescriptor) - 1;

  // a pointer to the table
  idt_pointer.base = (uint32_t)idt;

  // Inline assembly that loads the idt using the lidt register
  __asm__ __volatile__("lidt %0" :: "m" (idt_pointer));
}

void Regalia::InterruptManager::SetInterruptDescriptorTableEntry
  (uint8_t interruptNumber, uint16_t codeSegmentSelectorOffset,
  void (*handler)(), uint8_t DescriptorPrivilegeLevel, uint8_t DescriptorType)
{
  const uint8_t IDT_DESC_PRESENT = 0x80;

  /**
  * Here we are setting the bytes for the idt which will later be pointed at in
  * memory below.
  *
  * Information regarding the structure of the idt can be found on the
  * AMD/INTEL manuals regarding the IDT.
  */
  idt[interruptNumber].handlerAddressLow = ((uint32_t)handler) & 0xFFFF;
  idt[interruptNumber].handlerAddressHigh = (((uint32_t)handler)>>16) & 0xFFFF;
  idt[interruptNumber].gdt_codeSegmentSelector = codeSegmentSelectorOffset;
  idt[interruptNumber].access =
  (IDT_DESC_PRESENT | DescriptorType | ((DescriptorPrivilegeLevel&3) << 5));
  idt[interruptNumber].zero = 0; // always set to 0 as defined in AMD manual
}

Regalia::InterruptManager::~InterruptManager()
{

}

void Regalia::InterruptManager::Activate()
{
  // Tell the cpu to start listening for interrupts using the start interrupt
  // register. This is in a different function because we will need to call the
  // idt first, and then set up the hardware, lastly we will then call activate.

  __asm__ __volatile__("sti");
}

/**
* This is used to handle an interrupt that is passed;
*
* @param interruptNumber this number specifies the type of interrupt
* @param esp This is the current stack pointer
*/
uint32_t Regalia::InterruptManager::HandleInterrupt
  (uint8_t interruptNumber, uint32_t esp)
{
  Regalia::Terminal terminal;
  terminal.print("INTERRUPT");
  return esp;
}
