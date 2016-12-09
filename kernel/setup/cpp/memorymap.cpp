#include <Regalia/multiboot.h>
#include <Regalia/memorymap.h>
#include <Global/globals.h>

#define MB (uint32_t)(1024)
#define GB (uint32_t)(1024*1024)
#define TB (uint32_t)(1024*1024*1024)
#define PRINT_HEX(data) terminal.Itoa(data,16)
#define BIT_IS_SET(bit) ((mbd->flags) & (1 << (bit)))
#define MMAP_ADDR_PLUS_LENGTH (memory_map_t*)(mbd->mmap_addr + mbd->mmap_length)
#define MMAP_SIZE (mmap->size + sizeof(mmap->size))
#define MMAP_INCREMENT_BY(size) mmap = (memory_map_t*)((uint32_t)mmap + size)
#define ROUND_UP(x) while(x)
#define WHILE_NOT_DIVISIBLE_BY(x) (((memory_combined++)/x % x) != 0)

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

Regalia::MemoryMap::MemoryMap(multiboot_info_t* mbd)
{
  this->DisplayGrubInformation(mbd);
}

Regalia::MemoryMap::~MemoryMap(){}

void Regalia::MemoryMap::DisplayGrubInformation(multiboot_info_t* mbd)
{

  if(BIT_IS_SET(0))
  {
    uint32_t memory_combined = mbd->mem_upper + mbd->mem_lower;

    terminal << "\nDetected memory: ";

    if(memory_combined >= GB)
    {
      ROUND_UP(WHILE_NOT_DIVISIBLE_BY(1024));
    }
    else
    {
      ROUND_UP(WHILE_NOT_DIVISIBLE_BY(256));
    }

    if(memory_combined >= TB)
    {
      terminal << (memory_combined / TB) << "TB";
    }
    else if(memory_combined >= GB)
    {
      terminal << (memory_combined / GB) << "GB";
    }
    else
    {
      terminal << (memory_combined / MB) << "MB";
    }
  }
  else
  {
    terminal << "Error! Invalid information passed from GRUB/BIOS!\n";
  }

  if(BIT_IS_SET(1))
  {
    //PRINT_HEX(mbd->boot_device);
  }
  else
  {
    terminal << "Error! Invalid information passed from GRUB/BIOS!\n";
  }
  
  if(BIT_IS_SET(6))
  {
    memory_map_t *mmap = (memory_map_t*)mbd->mmap_addr;

    terminal << "\nMemory map:";
    PRINT_HEX(mbd->mmap_addr);
    terminal << " Length 0x";
    PRINT_HEX(mbd->mmap_length);
    terminal << "\n\n";

    terminal << "-------------------------------------------------------------";
    terminal << "\n Base Address      | Address Length    | Memory Type    | #";
    terminal << "\n";
    terminal << "-------------------------------------------------------------";
    terminal << "\n";

    while(mmap < MMAP_ADDR_PLUS_LENGTH)
    {
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

      MMAP_INCREMENT_BY(MMAP_SIZE);
    }

    terminal << "-------------------------------------------------------------";
  }
  else
  {
    terminal << "Error! Invalid information passed from GRUB/BIOS!\n";
  }

  if(BIT_IS_SET(7))
  {
    PRINT_HEX(mbd->drives_addr); terminal << " ";
    PRINT_HEX(mbd->drives_length);
  }
  else
  {
    terminal << "Error! Invalid information passed from GRUB/BIOS!\n";
  }
}
