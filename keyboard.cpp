#include "terminal.h"
#include "keyboard.h"
#include "common.h"

//void keyboard_handler(struct Registers *registers)
void keyboard_handler()
{
  uint8_t scancode;

  Regalia::Terminal terminal;

  scancode = inportb(0x60);

  if(scancode == 0x02)
  {
    terminal.print("1");
  }
  if(scancode == 0x03)
  {
    terminal.print("2");
  }
  if(scancode == 0x04)
  {
    terminal.print("3");
  }
  else
  {
    terminal.print("UNKNOWN");
  }
}
