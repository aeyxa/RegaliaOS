#include <Common/common.h>
#include <Regalia/gdt.h>
#include <Global/globals.h>

#define RING_0 0
#define RING_3 3
#define CODE 0x9A
#define DATA 0x92
#define GRAN 0xCF
#define LIMIT 0xFFFFFFFF

Regalia::GlobalDescriptorTable::GDT_Pointer gdt;

Regalia::GlobalDescriptorTable::GlobalDescriptorTable()
{
  this->GlobalDescriptorTableStart();
}

Regalia::GlobalDescriptorTable::~GlobalDescriptorTable(){}

void Regalia::GlobalDescriptorTable::GlobalDescriptorTableEntry
(uint16_t number, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
  entry[number].base_low = (base & 0xFFFF);
  entry[number].base_middle = (base >> 16) & 0xFF;
  entry[number].base_high = (base >> 24) & 0xFF;

  entry[number].limit_low = (limit & 0xFFFF);
  entry[number].granularity = ((limit >> 16) & 0x0F);
  entry[number].granularity |= (gran & 0xF0);

  entry[number].access = access;
}

void Regalia::GlobalDescriptorTable::GlobalDescriptorTableStart()
{
  this->GlobalDescriptorTableEntry(NULL,NULL,NULL,NULL,NULL);
  this->GlobalDescriptorTableEntry(1,RING_0,LIMIT,CODE,GRAN);
  this->GlobalDescriptorTableEntry(2,RING_0,LIMIT,DATA,GRAN);

  gdt.limit = (sizeof(struct GDT_Entry)*256) - 1;
  gdt.base = (uint32_t)&entry;

  gdt_flush();
}
