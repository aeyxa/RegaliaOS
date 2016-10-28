#ifndef GDT_H
#define GDT_H

#include "common.h"

namespace Regalia
{
  NullDescriptor();
  CodeDescriptor();
  DataDescriptor();
}

/*
namespace Regalia
{
  class GlobalDescriptorTable
  {
  public:
    GlobalDescriptorTable();
    ~GlobalDescriptorTable();

    class SegmentDescriptor
    {
    public:
      SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t flags);
    private:
      uint16_t *limit_0_15;
      uint16_t *base_0_15;
      uint8_t *base_16_23;
      uint8_t *access;
      uint8_t *limit_16_19_and_flags; // limit and flags are 4 bits each
      uint8_t *base_24_31;
    }__attribute__((packed));

  private:
    SegmentDescriptor null;
    SegmentDescriptor hold;
    SegmentDescriptor code;
    SegmentDescriptor data;
  };
}
*/
#endif
