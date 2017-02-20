#include <Regalia/multiboot.h>
#include <Regalia/memorymap.h>
#include <Global/globals.h>

#define MB (uint32_t)(1024)
#define GB (uint32_t)(1024*1024)
#define TB (uint32_t)(1024*1024*1024)
#define PRINT_HEX(data) terminal.Itoa(data,16)
#define PRINT_INT(data) terminal.Itoa(data,10)
#define BIT_IS_SET(bit) ((mbd->flags) & (1 << (bit)))
#define MMAP_SIZE (memory_map_t*)(mbd->mmap_addr + mbd->mmap_length)
#define SIZE_OF_MMAP (mmap->size + sizeof(mmap->size))
#define MMAP_INCREMENT_BY(size) mmap = (memory_map_t*)((uint32_t)mmap + size)
#define NOT_DIVISIBLE(x) ((x++ / 256) == 0) || (((x++ / 256) % 256) != 0)

Regalia::MemoryMap::MemoryMap(multiboot_info_t* mbd)
{
  this->DisplayGrubInformation(mbd);
  InitMemoryMap(mbd);
  /*
  uint32_t* p = (uint32_t*)0x10C000;
  p[0] = (uint32_t)5;
  uint32_t* x = (uint32_t*)0x10C000;
  PRINT_INT((uint32_t)x[0]);
  */

  uint32_t *p = (uint32_t*)AllocateBlock(sizeof(uint32_t));
  terminal << "\n"; PRINT_HEX((uint32_t)p);

}
Regalia::MemoryMap::~MemoryMap(){}

void Regalia::MemoryMap::InitMemoryMap(multiboot_info_t* mbd)
{
  m_memory_size = m_memory_end_address - m_kernel_end_address;
  memory_blocks = m_memory_size / 4096;

  for(uint32_t i = 0; i <= memory_blocks; i++)
    m_memory_map[i] = 1;
}

void* Regalia::MemoryMap::AllocateBlock(size_t size)
{
  void* x = m_current_address;
  m_current_address = m_current_address + size;
  return x;
}

void Regalia::MemoryMap::DisplayGrubInformation(multiboot_info_t* mbd)
{
  /*
  if(BIT_IS_SET(0))
  {
    uint32_t memory_combined = mbd->mem_upper + mbd->mem_lower;

    terminal << "\nDetected memory: 0x";
    PRINT_HEX(memory_combined);
    terminal << "KB ~0x";

    while(NOT_DIVISIBLE(memory_combined));

    if(memory_combined >= GB)
    {
      PRINT_HEX(memory_combined / GB);
      terminal << "GB";
    }
    else
    {
      PRINT_HEX(memory_combined / MB);
      terminal << "MB";
    }
  }

  if(BIT_IS_SET(1))
  {
    /terminal << "\nBoot Device: 0x"; PRINT_HEX(mbd->boot_device);
  }
  */
  if(BIT_IS_SET(6))
  {
    memory_map_t *mmap = (memory_map_t*)mbd->mmap_addr;

    /*
    terminal << "\nMemory Map -> (MM): Address 0x";
    PRINT_HEX(mbd->mmap_addr);
    terminal << " Length 0x";
    PRINT_HEX(mbd->mmap_length);
    terminal << "\n\n";

    terminal << "-------------------------------------------------------------"
    << "\n Base Address      | Address Length    | Memory Type    | #" << "\n"
    << "-------------------------------------------------------------" << "\n";
    */

    while(mmap < MMAP_SIZE)
    {
      /*
      terminal << " 0x";
      PRINT_HEX(mmap->base_upper);
      PRINT_HEX(mmap->base_lower);

      terminal << "  0x";
      PRINT_HEX(mmap->length_upper);
      PRINT_HEX(mmap->length_lower);

      switch(mmap->type)
      {
        case 1: terminal << "  Available    -> (1)"; break;
        case 2: terminal << "  Reserved     -> (2)"; break;
        case 3: terminal << "  Limbo        -> (3)"; break;
        case 4: terminal << "  Non-volatile -> (4)"; break;
        case 5: terminal << "  Bad          -> (5)"; break;
      }
      terminal << "\n";
      */
      if(mmap->type == 1 && mmap->length_lower > 0x100000)
      {
        m_memory_end_address = mmap->base_lower + mmap->length_lower;
      }

      MMAP_INCREMENT_BY(SIZE_OF_MMAP);
    }

    //terminal << "-------------------------------------------------------------"
    //<< "\n";
  }

  if(BIT_IS_SET(7))
  {
    //PRINT_HEX(mbd->drives_addr); terminal << " ";
    //PRINT_HEX(mbd->drives_length);
  }

  //this->HandleMemory(mbd);
}



void Regalia::MemoryMap::HandleMemory(multiboot_info_t* mbd)
{
  memory_map_t *mmap = (memory_map_t*)mbd->mmap_addr;

  while(mmap < MMAP_SIZE)
  {
    if(mmap->base_lower > 0 && mmap->type == 1)
    {
      //PRINT_HEX(mmap->base_lower);
    }
    MMAP_INCREMENT_BY(SIZE_OF_MMAP);
  }
}
