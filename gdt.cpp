#include "common.h"
#include "gdt.h"

Regalia::GlobalDescriptorTable::GlobalDescriptorTable() :
null(0,0,0), hold(0,0,0), code(0,0xFFFFFFFF,0x9A), data(0,0xFFFFFFFF,0x92)
{
  
}

Regalia::GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor
(uint32_t base, uint32_t limit, uint8_t flags)
{

}
