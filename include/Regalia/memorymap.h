#pragma once

namespace Regalia
{
  class MemoryMap
  {
  public:
    MemoryMap(multiboot_info_t* mbd);
    ~MemoryMap();
  private:
    void DisplayGrubInformation(multiboot_info_t* mbd);
  };
}
