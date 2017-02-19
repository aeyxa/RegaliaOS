#pragma once

namespace Regalia
{
  class PhysicalMemoryManager
  {
  public:
    PhysicalMemoryManager();
    ~PhysicalMemoryManager();
  private:
    static uint32_t m_physical_memory_size;
    static uint32_t m_physical_used_blocks;
    static uint32_t m_physical_max_blocks;
    static uint32_t m_physical_memory_map;
  };
}
