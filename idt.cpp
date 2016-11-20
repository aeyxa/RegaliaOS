#include "common.h"
#include "idt.h"
#include "isr.h"
#include "irq.h"
#include "terminal.h"
#include "keyboard.h"

// GDT segment entries are 8 bytes each, code is our second one, meaning 0x08
#define CODESELECTOR 0x08
// (P=1, DPL=00b, S=0, type=1110b, type_attr=1000_1110b=0x8E)
#define INTERRUPTGATE 0x8E

Regalia::InterruptDescriptorTable::IDT_Pointer idt;

Regalia::InterruptDescriptorTable::InterruptDescriptorTable()
{
  this->InterruptDescriptorTableStart();
  this->InterruptServicesRequestStart();
  this->InterruptHardwareRequestStart();
}

Regalia::InterruptDescriptorTable::~InterruptDescriptorTable(){}

void Regalia::InterruptDescriptorTable::InterruptDescriptorTableEntry
(uint8_t number, void(*handler)(), uint16_t selector, uint8_t flags)
{
  entry[number].base_low = ((uint32_t)handler) & 0xFFFF;
  entry[number].base_high = ((uint32_t)handler >> 16) & 0xFFFF;
  entry[number].selector = selector;
  entry[number].flags = flags;
  entry[number].always0 = 0;
}

// Sets up IDT
void Regalia::InterruptDescriptorTable::InterruptDescriptorTableStart()
{
  idt.limit = (sizeof(struct IDT_Entry)*256) - 1;
  idt.base = (uint32_t)&entry;

  idt_load();
}

// Sets up ISR
void Regalia::InterruptDescriptorTable::InterruptServicesRequestStart()
{
  Regalia::InterruptDescriptorTable::InterruptServicesRequest isr;
  isr.Configure(this);
}

// Sets up IRQ
void Regalia::InterruptDescriptorTable::InterruptHardwareRequestStart()
{
  Regalia::InterruptDescriptorTable::InterruptHardwareRequest irq;
  irq.Configure(this);
}

// Empty Constructor
Regalia::InterruptDescriptorTable::InterruptServicesRequest
::InterruptServicesRequest(){}

// Empty deconstructor
Regalia::InterruptDescriptorTable::InterruptServicesRequest
::~InterruptServicesRequest(){}

// Constructor
Regalia::InterruptDescriptorTable::InterruptHardwareRequest
::InterruptHardwareRequest()
{
  this->Remap();
}

// Deconstructor
Regalia::InterruptDescriptorTable::InterruptHardwareRequest
::~InterruptHardwareRequest(){}

void Regalia::InterruptDescriptorTable::InterruptServicesRequest::Configure
(Regalia::InterruptDescriptorTable* const IDT)
{
  IDT->InterruptDescriptorTableEntry(0, isr0, CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(1, isr1, CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(2, isr2, CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(3, isr3, CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(4, isr4, CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(5, isr5, CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(6, isr6, CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(7, isr7, CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(8, isr8, CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(9, isr9, CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(10,isr10,CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(11,isr11,CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(12,isr12,CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(13,isr13,CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(14,isr14,CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(15,isr15,CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(16,isr16,CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(17,isr17,CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(18,isr18,CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(19,isr19,CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(20,isr20,CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(21,isr21,CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(22,isr22,CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(23,isr23,CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(24,isr24,CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(25,isr25,CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(26,isr26,CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(27,isr27,CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(28,isr28,CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(29,isr29,CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(30,isr30,CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(31,isr31,CODESELECTOR,INTERRUPTGATE);
}

void Regalia::InterruptDescriptorTable::InterruptHardwareRequest::Configure
(Regalia::InterruptDescriptorTable* const IDT)
{
  IDT->InterruptDescriptorTableEntry(32,irq0, CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(33,irq1, CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(34,irq2, CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(35,irq3, CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(36,irq4, CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(37,irq5, CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(38,irq6, CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(39,irq7, CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(40,irq8, CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(41,irq9, CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(42,irq10,CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(43,irq11,CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(44,irq12,CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(45,irq13,CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(46,irq14,CODESELECTOR,INTERRUPTGATE);
  IDT->InterruptDescriptorTableEntry(47,irq15,CODESELECTOR,INTERRUPTGATE);
}

void Regalia::InterruptDescriptorTable::InterruptHardwareRequest::Remap()
{
  outportb(0x20, 0x11);
  outportb(0xA0, 0x11);
  outportb(0x21, 0x20);
  outportb(0xA1, 0x28);
  outportb(0x21, 0x04);
  outportb(0xA1, 0x02);
  outportb(0x21, 0x01);
  outportb(0xA1, 0x01);
  outportb(0x21, 0x00);
  outportb(0xA1, 0x00);
}

void Regalia::InterruptDescriptorTable::InterruptHardwareRequest::LoadHandler
(uint32_t irq, void (*handler)(struct Registers *registers))
{
  this->Routines[irq] = handler;
}

extern "C" void Regalia::InterruptDescriptorTable::InterruptServicesRequest
::Handler()
{

}

void Regalia::InterruptDescriptorTable::InterruptHardwareRequest
::Handler(struct Registers* registers)
{
  //void (*handler)(struct Registers* registers);
  //void (*handler)();
  //this->LoadHandler((uint32_t)1, keyboard_handler);

  //handler = this->Routines[registers->int_no];

  if(registers->int_no == 1)
  {
    keyboard_handler();
  }

  if(registers->int_no >= 8)
  {
    outportb(0xA0, 0x20);
  }
  outportb(0x20, 0x20);
}
