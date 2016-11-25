#include <Regalia/terminal.h>
#include <Regalia/port.h>
#include <Regalia/keyboard.h>
#include <Common/common.h>
#include <Global/globals.h>

#define TAB 0x0F
#define ENTER 0x1C
#define BACKSPACE 0x0E
#define RIGHT_SHIFT_PRESS 0x36
#define LEFT_SHIFT_PRESS 0x2A
#define LEFT_SHIFT_RELEASE 0xAA
#define RIGHT_SHIFT_RELEASE 0xB6
#define CAPSLOCK_PRESS 0x3A
#define CAPSLOCK_RELEASE 0xBA
#define ESCAPE 0x01

Regalia::Keyboard::Keyboard()
{
  this->DisplayActivation();
}

Regalia::Keyboard::~Keyboard(){}

void Regalia::Keyboard::DisplayActivation()
{
  terminal << "Keyboard Interrupt Handler: Activated!\n";
}

void Regalia::Keyboard::CheckData()
{
  keycode = inportb(0x60);

  if(keycode)
  {
    this->HandleKey(keycode);
  }
}

void Regalia::Keyboard::HandleKey(uint8_t keycode)
{
  switch(keycode)
  {
    case 0x02: terminal.keycode(keycode); break; // 1
    case 0x03: terminal.keycode(keycode); break; // 2
    case 0x04: terminal.keycode(keycode); break; // 3
    case 0x05: terminal.keycode(keycode); break; // 4
    case 0x06: terminal.keycode(keycode); break; // 5
    case 0x07: terminal.keycode(keycode); break; // 6
    case 0x08: terminal.keycode(keycode); break; // 7
    case 0x09: terminal.keycode(keycode); break; // 8
    case 0x0A: terminal.keycode(keycode); break; // 9
    case 0x0B: terminal.keycode(keycode); break; // 0
    case 0x0C: terminal.keycode(keycode); break; // -
    case 0x0D: terminal.keycode(keycode); break; // =
    case 0x27: terminal.keycode(keycode); break; // ;
    case 0x28: terminal.keycode(keycode); break; // '
    case 0x29: terminal.keycode(keycode); break; // `
    case 0x2B: terminal.keycode(keycode); break; /* \ */
    case 0x33: terminal.keycode(keycode); break; // ,
    case 0x34: terminal.keycode(keycode); break; // .
    case 0x35: terminal.keycode(keycode); break; /* / */
    case 0x37: terminal.keycode(keycode); break; // *
    case 0x1A: terminal.keycode(keycode); break; // [
    case 0x1B: terminal.keycode(keycode); break; // ]

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
    case 0x1E: terminal.print("a"); break;
    case 0x1F: terminal.print("s"); break;
    case 0x20: terminal.print("d"); break;
    case 0x21: terminal.print("f"); break;
    case 0x22: terminal.print("g"); break;
    case 0x23: terminal.print("h"); break;
    case 0x24: terminal.print("j"); break;
    case 0x25: terminal.print("k"); break;
    case 0x26: terminal.print("l"); break;
    case 0x2C: terminal.print("z"); break;
    case 0x2D: terminal.print("x"); break;
    case 0x2E: terminal.print("c"); break;
    case 0x2F: terminal.print("v"); break;
    case 0x30: terminal.print("b"); break;
    case 0x31: terminal.print("n"); break;
    case 0x32: terminal.print("m"); break;
    case 0x39: terminal.print(" "); break;

    case 0x01: terminal.keycode(ESCAPE); break;
    case 0x0F: terminal.keycode(TAB); break;
    case 0x1C: terminal.keycode(ENTER); break;
    case 0x38: terminal.print("LEFT ALT"); break;
    case 0x0E: terminal.keycode(BACKSPACE); break;
    case 0x1D: terminal.print("LEFT CONTROL"); break;
    case 0x3A: terminal.keycode(CAPSLOCK_PRESS); break;
    case 0xBA: terminal.keycode(CAPSLOCK_RELEASE); break;
    case 0x2A: terminal.keycode(LEFT_SHIFT_PRESS); break;
    case 0x36: terminal.keycode(RIGHT_SHIFT_PRESS); break;
    case 0xAA: terminal.keycode(LEFT_SHIFT_RELEASE); break;
    case 0xB6: terminal.keycode(RIGHT_SHIFT_RELEASE); break;
  }
}
