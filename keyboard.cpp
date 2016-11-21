#include "terminal.h"
#include "keyboard.h"
#include "common.h"
#include "globals.h"
#include "port.h"

void keyboard_handler()
{
  uint8_t scancode;

  scancode = inportb(0x60);

  switch(scancode)
  {
    case 0x02: terminal.print("1"); break;
    case 0x03: terminal.print("2"); break;
    case 0x04: terminal.print("3"); break;
    case 0x05: terminal.print("4"); break;
    case 0x06: terminal.print("5"); break;
    case 0x07: terminal.print("6"); break;
    case 0x08: terminal.print("7"); break;
    case 0x09: terminal.print("8"); break;
    case 0x0A: terminal.print("9"); break;
    case 0x0B: terminal.print("0"); break;
    case 0x0C: terminal.print("-"); break;
    case 0x0D: terminal.print("="); break;
    case 0x0E: terminal.print("BACKSPACE"); break;
    case 0x0F: terminal.print("TAB"); break;
    case 0x10: terminal.print("q"); break;
    case 0x11: terminal.print("w"); break;
    case 0x12: terminal.print("e"); break;
    case 0x13: terminal.print("r"); break;
    case 0x14: terminal.print("t"); break;
    case 0x15: terminal.print("y"); break;
    case 0x16: terminal.print("u"); break;
    case 0x17: terminal.print("i"); break;
    case 0x18: terminal.print("o"); break;
    case 0x19: terminal.print("p"); break;
    case 0x1A: terminal.print("["); break;
    case 0x1B: terminal.print("]"); break;
    case 0x1C: terminal.print("ENTER"); break;
    case 0x1D: terminal.print("LEFT CONTROL"); break;
    case 0x1E: terminal.print("a"); break;
    case 0x1F: terminal.print("s"); break;
    case 0x20: terminal.print("d"); break;
    case 0x21: terminal.print("f"); break;
    case 0x22: terminal.print("g"); break;
    case 0x23: terminal.print("h"); break;
    case 0x24: terminal.print("j"); break;
    case 0x25: terminal.print("k"); break;
    case 0x26: terminal.print("l"); break;
    case 0x27: terminal.print(";"); break;
    case 0x28: terminal.print("'"); break;
    case 0x29: terminal.print("`"); break;
    case 0x2A: terminal.print("LEFT SHIFT"); break;
    case 0x2B: terminal.print("\\"); break;
    case 0x2C: terminal.print("z"); break;
    case 0x2D: terminal.print("x"); break;
    case 0x2E: terminal.print("c"); break;
    case 0x2F: terminal.print("v"); break;
    case 0x30: terminal.print("b"); break;
    case 0x31: terminal.print("n"); break;
    case 0x32: terminal.print("m"); break;
    case 0x33: terminal.print(","); break;
    case 0x34: terminal.print("."); break;
    case 0x35: terminal.print("/"); break;
    case 0x36: terminal.print("RIGHT SHIFT"); break;
    case 0x37: terminal.print("*"); break;
    case 0x38: terminal.print("LEFT ALT"); break;
    case 0x39: terminal.print(" "); break;
    case 0x3A: terminal.print("CAPS LOCK"); break;
  }
}
