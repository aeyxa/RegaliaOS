#pragma once

#include <Common/common.h>

extern "C" void gdt_flush();

namespace Regalia
{
  class GlobalDescriptorTable
  {
  private:
    struct GDT_Entry
    {
      uint16_t limit_low;
      uint16_t base_low;
      uint8_t base_middle;
      uint8_t access;
      uint8_t granularity;
      uint8_t base_high;
    }__attribute__((packed)); // Must be byte perfect

    GDT_Entry entry[256]; // GDT has a maximum of 256 entries

  public:
    struct GDT_Pointer
    {
      uint16_t limit;
      uint32_t base;
    }__attribute__((packed)); // Must be byte perfect

    GlobalDescriptorTable();
    ~GlobalDescriptorTable();
    void GlobalDescriptorTableEntry
    (uint16_t number,uint32_t base,uint32_t limit,uint8_t access,uint8_t gran);
    void GlobalDescriptorTableStart();
  };
}
