#ifndef GDT_H
#define GDT_H

#include "common.h"

/*
* ------------------------------------------------------------------------------
* Relationship
* ------------------------------------------------------------------------------
*
* Segment Selectors point to Descriptor Tables.
*
* Descriptor Tables hold Segment Descriptors.
*
* Segment Descriptors describe Segments.
*
* Segments are blocks of memory.
*
* ------------------------------------------------------------------------------
*/


namespace Regalia
{
  class GlobalDescriptorTable
  {
  public:
    GlobalDescriptorTable();
    ~GlobalDescriptorTable();

    uint16_t CodeSegmentSelector();
    uint16_t DataSegmentSelector();

    class SegmentDescriptor
    {
    public:
      SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t flags);
      uint32_t Base();
      uint32_t Limit();
    private:
      /*
        It's very important that these variables get called in the order they
        are displayed here, as this is how the cpu will try to read them.

        If the order is changed, the cpu will use values in ways we did not 
        intend and the kernel will likely crash.

        This is why the __attribute__((packed)) is required below.
      */
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

#endif
