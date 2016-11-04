#include "common.h"
#include "terminal.h"
#include "gdt.h"
#include "idt.h"

Regalia::InterruptDescriptorTable::GateDescriptor Regalia::InterruptDescriptorTable::idt_gate[256];

Regalia::InterruptDescriptorTable::InterruptDescriptorTable
(GlobalDescriptorTable* gdt)
{
  Regalia::InterruptDescriptorTable::KeyboardStage(gdt);

  InterruptDescriptorTablePointer pointer;

  // The size is the gate descriptor times 256 -1 due to there being 0-255
  // available enteries.
  pointer.size = (256*sizeof(GateDescriptor)-1);

  // This is basically the same as gdt.cpp where we assign it to 'this' except
  // here we use a structure instead.
  pointer.base = (uint32_t)idt_gate;

  // Pass the pointer to lidt register
  __asm__ __volatile__("lidt (%0)" :: "r" ((&pointer)));

  //Regalia::InterruptDescriptorTable::KeyboardHandler();
}

Regalia::InterruptDescriptorTable::~InterruptDescriptorTable()
{
  /* Currently unused, this should unload the lidt. */
}

void Regalia::InterruptDescriptorTable::KeyboardStage
(GlobalDescriptorTable* gdt)
{
  uint32_t keyboard_address = 0x01;

  idt_gate[0x21].offset_low = (keyboard_address & 0xFFFF);
  idt_gate[0x21].code = gdt->CodeSegmentSelector();
  idt_gate[0x21].zero = 0;
  idt_gate[0x21].flags = 0x8E;
  idt_gate[0x21].offset_high = (keyboard_address & 0xFFFF) >> 16;

  /**
  * The PICs are initialized using 8-bit command words known as Initialization
  * Command Words (ICW)
  */

  // ICW1 - Tell Pic to wait for other commands
  Regalia::InterruptDescriptorTable::write(0x20, 0x11);
  Regalia::InterruptDescriptorTable::write(0xA0, 0x11);

  // ICW2 - Tell it's vector offset
  Regalia::InterruptDescriptorTable::write(0x21 , 0x20);
  Regalia::InterruptDescriptorTable::write(0xA1 , 0x28);

  // ICW3 - Tell it's master/slave (which we clear out)
  Regalia::InterruptDescriptorTable::write(0x21 , 0x00);
  Regalia::InterruptDescriptorTable::write(0xA1 , 0x00);

  // ICW4 - Tell it which mode we're in
  Regalia::InterruptDescriptorTable::write(0x21 , 0x01);
  Regalia::InterruptDescriptorTable::write(0xA1 , 0x01);

  // Mask
  Regalia::InterruptDescriptorTable::write(0x21 , 0xFF);
  Regalia::InterruptDescriptorTable::write(0xA1 , 0xFF);
}

void Regalia::InterruptDescriptorTable::Activate()
{
  __asm__ __volatile__("sti");
}
void Regalia::InterruptDescriptorTable::KeyboardEnable()
{
  Regalia::InterruptDescriptorTable::write(0x21 , 0xFD);
}

static inline void Regalia::InterruptDescriptorTable::write
(uint16_t _port, uint8_t _data)
{
  __asm__ __volatile__("outb %0, %1" : : "a" (_data), "Nd" (_port));
}

static inline uint8_t Regalia::InterruptDescriptorTable::read(uint16_t _port)
{
  uint8_t result;

  __asm__ __volatile__("inb %1, %0" : "=a" (result) : "Nd" (_port));

  return result;
}

void Regalia::InterruptDescriptorTable::KeyboardHandler()
{
  uint8_t status, keycode;
  char* foo = "INTERRUPT 0x00";
  char* hex = "0123456789ABCDEF";

  write(0x20,0x20);

  status = read(0x64);

  if(status & 0x01)
  {
    keycode = read(0x60);

    foo[12] = hex[(keycode >> 4) & 0xF];
    foo[13] = hex[keycode & 0xF];

    Regalia::Terminal terminal;

    terminal.print(foo);
  }
}
