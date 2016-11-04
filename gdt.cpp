#include "common.h"
#include "gdt.h"

Regalia::GlobalDescriptorTable::GlobalDescriptorTable() :
null(0,0,0), hold(0,0,0), code(0,0xFFFFFFFF,0x9A), data(0,0xFFFFFFFF,0x92)
{
  /*
    As stated in the "AMD64 Architecture Programmer’s Manual, Volume 2: System
    Programming", it expects a 16-bit Descriptor-Table Limit and a 32-bit
    Descriptor-Table Base Address on page 74-75, in figure 4-7.

    Since it expects 6 bytes and not 8 bytes, we will use the 32-bit address of
    the Global Descriptor Table using the 'this' pointer. Then use another 32-
    bits for the limit or size of the Global Descriptor Table, but shift it 16-
    bits to the left.

    This means we have 32-bits pointing to the base address or where the table
    is in memory and then how long it is (the limit) side by side. The other
    16-bits left over would now be 0's and would be ignored by the cpu.
  */

  uint32_t GDT_Pointer[2];

  GDT_Pointer[0] = (uint32_t)this;
  GDT_Pointer[1] = sizeof(GlobalDescriptorTable) << 16;

  __asm__ __volatile__("lgdt (%0)" :: "r" ((&GDT_Pointer)));
}

Regalia::GlobalDescriptorTable::~GlobalDescriptorTable()
{
  /* Currently unused, not sure how or if I should unload the lgdt. */
}

uint16_t Regalia::GlobalDescriptorTable::DataSegmentSelector()
{
  return (uint8_t *)&data - (uint8_t*)this;
}

uint16_t Regalia::GlobalDescriptorTable::CodeSegmentSelector()
{
  return (uint8_t *)&code - (uint8_t*)this;
}

Regalia::GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor
(uint32_t base, uint32_t limit, uint8_t access)
{

  /*
  * ----------------------------------------------------------------------------
  * AMD64 Architecture Programmer’s Manual, Volume 2: System Programming
  *   Page 80, Figure 4-13 -> Generic Segment Descriptor - Legacy Mode (32 bit)
  * ----------------------------------------------------------------------------
  *
  * A Legacy mode Segment Descriptor is made up of 8 bytes.
  *
  * The 8 bytes are created with two double words (4 bytes) stacked together.
  *
  * The upper doubleword is located at offset + 4
  * The lower doubleword is located at offset + 0
  *
  * Segment Limit:
  *   The Segment Limit is 20 bits long, with bits 19:16 in the upper doubleword
  *   and 0:15 in the bottom doubleword.
  *
  * Base Address:
  *   The Base Address is 32 bits long, with bits 31:24 and 7:0 in the upper
  *   doubleword and bits 15:0 of the lower doubleword.
  *
  * Type and S:
  *   The S field is 1 bit long, with bits 12 in the upper doubleword and the
  *   Type field is 4 bits long, with bits 11:8 in the upper doubleworld.
  *
  * Descriptor Privilege-Level (DPL):
  *   The DPL field is 2 bits long, consisting of bits 14:13 in the upper
  *   doubleword.
  *
  * Present (P):
  *   The P field is 1 bit long, consisting of bit 15 in the upper doubleword.
  *
  * Available To Software (AVL):
  *   The AVL field is 1 bit long, consisting of bit 20 in the upper doubleword.
  *
  * Default Operand Size (D/B):
  *   The D/B field is 1 bit long, consisting of bit 22 in the upper doubleword.
  *
  * Granularity (G):
  *   The G field is 1 bit long, consisting of bit 23 in the upper doubleword.
  *
  * Reserved Bits:
  *   The reserved field is 1 bit long, at bit 21 in the upper doubleword.
  * ----------------------------------------------------------------------------
  */

  /*
    What we are doing here is meeting the specifications above, for the
    specific segments we are passing such as code and data segment. We need to
    set 8 bytes of data with the limit, base and specific values for the type
    of segment.

    Instead of calculating this ourselves each time, the code below allows it
    to be calculated automatically when information is passed to it.

    Information about this can be found here:
      http://wiki.osdev.org/GDT_Tutorial

    If you're not sure what's happening here, you probably need to learn about
    bit manipulation.

    Additionally, you'll notice that target isn't actually being returned,
    instead, it's setting the bit values in memory which are then read by the
    lgdt register in our constructor above.

    Lastly, I should point out that the targets below, correspond to the
    variables in gdt.h.
  */

  uint8_t *target = (uint8_t*)this;
                                        // Relative pos     | Absolute pos
  if(limit <= 65536)
  {
    target[6] = 0x40;                   // Flags at 20:23   | (52:55)
  }
  else
  {
    /*
      This logic here refers to the fact that the limit is only 20 bits long
      instead of 32. We shift to the left by 12 adding in values to the other
      portion of the limit.
    */
    if((limit & 0xFFF) != 0xFFF)
    {
      limit = (limit >> 12)-1;
    }
    else limit = (limit >> 12);

    target[6] = 0xC0;
  }

  target[0] = limit & 0xFF;             // Limit at 0:7     | (0:7)
  target[1] = (limit >> 8) & 0xFF;      // Limit at 8:15    | (8:15)
  target[6] |= (limit >> 16) & 0xF;     // Limit at 16:19   | (48:51)

  target[2] = base & 0xFF;              // Base at 0:7      | (16:23)
  target[3] = (base >> 8) & 0xFF;       // Base at 8:15     | (24:31)
  target[4] = (base >> 16) & 0xFF;      // Base at 16:23    | (32:39)
  target[7] = (base >> 24) & 0xFF;      // Base at 24:31    | (56:63)

  target[5] = access;                   // Access at 24:31  | (40:47)
}

uint32_t Regalia::GlobalDescriptorTable::SegmentDescriptor::Base()
{
  /*
    If we need to obtain the base, we can calculate it backwards doing what we
    did above, except backwards. Above we went right by 8, here we will go left
    by 8.

    We have to add the target onto result because result only equals the [7] to
    start with.

    So we have some binary like 0101 0010 then we shift left and change it to
    0101 0010 0000 0000 then add the next target onto it to to fill in the 0's
    and repeat until we recreate the base.
  */
  uint8_t *target = (uint8_t*)this;

  uint32_t result = target[7];

  result = (result << 8) + target[4];
  result = (result << 8) + target[3];
  result = (result << 8) + target[2];

  return result;
}

uint32_t Regalia::GlobalDescriptorTable::SegmentDescriptor::Limit()
{
  /*
    Here we do the same for above, it's a little more complicated for two
    reasons.

    One, is that the target[6] was in a shared byte, which is why we need to do
    & 0xF again.

    The other reason, is that we shifted to the right by 12 above, so we now
    must shift to the left 12, but only if it meets the conditions on which we
    shifted by 12 above.
  */

  uint8_t *target = (uint8_t*)this;

  uint32_t result = target[6] & 0xF;

  result = (result << 8) + target[1];
  result = (result << 8) + target[0];

  if((target[6] & 0xC0) == 0xC0)
  {
    result = (result << 12) | 0xFFF;
  }
  return result;
}
