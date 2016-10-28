#include "common.h"
#include "gdt.h"

/*
* ------------------------------------------------------------------------------
* Information Source
* ------------------------------------------------------------------------------
*
* AMD64 Architecture Programmer’s Manual, Volume 2: System Programming
*
* ------------------------------------------------------------------------------
*/


/*
* ------------------------------------------------------------------------------
*  Segment
* ------------------------------------------------------------------------------
*
* Base points to the starting location of a segment
*
* Limit defines the segment size
*
* Attributes define the segment-protection characteristics
*
* ------------------------------------------------------------------------------
*/

/*
* ------------------------------------------------------------------------------
* Segment Descriptor
* ------------------------------------------------------------------------------
*
* Segment descriptors define, protect, and isolate segments from each other.
*
* There are two types of descriptors which are defined in the type field:
*
* User Segments - These include code and data segments.
* System Segments - These consist of LDT and TSS segments.
*
* ------------------------------------------------------------------------------
*/

/*
* ------------------------------------------------------------------------------
* Generic Segment Descriptor - Legacy Mode (32 bit)
* ------------------------------------------------------------------------------
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
*   The S field is 1 bit long, consisting of bit 12 in the upper doubleword and
*   the Type field is 4 bits long, with bits 11:8 in the upper doubleworld.
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
*   The reserved field is 1 bit long, located at bit 21 in the upper doubleword.
*
* ------------------------------------------------------------------------------
*/

/*
* ------------------------------------------------------------------------------
* Flat-Memory model 32 bit mode
* ------------------------------------------------------------------------------
*
* Clear segment base value to 0 effectively disabling segment translation,
* resulting in a single segment spanning the entire virtual-address space.
*
* Segment limits are fixed at 4 Gbytes.
*
* ------------------------------------------------------------------------------
*/

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

Regalia::NullDescriptor()
{

}

/*
Regalia::GlobalDescriptorTable::GlobalDescriptorTable() :
null(0,0,0), hold(0,0,0), code(0,0xFFFFFFFF,0x9A), data(0,0xFFFFFFFF,0x92)
{

}

Regalia::GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor
(uint32_t base, uint32_t limit, uint8_t flags)
{

}
*/
