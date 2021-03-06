#pragma once
#include <Common/common.h>

extern uint32_t kernel_end;

namespace Regalia
{
  class MemoryMap
  {
  public:
    MemoryMap(multiboot_info_t* mbd);
    ~MemoryMap();
  private:
    void DisplayGrubInformation(multiboot_info_t* mbd);
    void HandleMemory(multiboot_info_t* mbd);
    void* AllocateBlock(size_t size);
    void InitMemoryMap(multiboot_info_t* mbd);
    bool *m_memory_map;
    uint32_t *m_kernel_end_address = &kernel_end;
    uint32_t *m_current_address = &kernel_end;
    uint32_t m_memory_available;
  };
}
