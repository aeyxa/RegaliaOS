#include <Regalia/multiboot.h>
#include <Regalia/memorymap.h>
#include <Global/globals.h>

#define BIT_IS_SET(bit) ((mbd->flags) & (1 << (bit)))
#define HEX(data) terminal.itoa(mbd->data,16)

Regalia::MemoryMap::MemoryMap(multiboot_info_t* mbd)
{
  this->DisplayGrubInformation(mbd);
}

Regalia::MemoryMap::~MemoryMap(){}

void Regalia::MemoryMap::DisplayGrubInformation(multiboot_info_t* mbd)
{
  if(BIT_IS_SET(0))
  {
    terminal << HEX(mem_upper) << " " << HEX(mem_lower);
  }
}
