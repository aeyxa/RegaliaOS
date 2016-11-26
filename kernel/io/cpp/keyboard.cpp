#include <Regalia/terminal.h>
#include <Regalia/port.h>
#include <Regalia/keyboard.h>
#include <Common/common.h>
#include <Global/globals.h>

#define TAB "    "
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

void Regalia::Keyboard::Capitialization(uint8_t keycode, bool status)
{
  switch(keycode)
  {
    case 0x3A: case 0xBA: this->capitials = !this->capitials; break;
    case 0x2A: this->capitials = this->shift = !this->capitials; break;
    case 0xAA: this->capitials = this->shift = !this->capitials; break;
    case 0x36: this->capitials = this->shift = !this->capitials; break;
    case 0xB6: this->capitials = this->shift = !this->capitials; break;
  }
}

void Regalia::Keyboard::HandleKey(uint8_t keycode)
{

  if(capitials)
  {
    switch(keycode)
    {
      case 0x10: terminal << "Q"; break;
      case 0x11: terminal << "W"; break;
      case 0x12: terminal << "E"; break;
      case 0x13: terminal << "R"; break;
      case 0x14: terminal << "T"; break;
      case 0x15: terminal << "Y"; break;
      case 0x16: terminal << "U"; break;
      case 0x17: terminal << "I"; break;
      case 0x18: terminal << "O"; break;
      case 0x19: terminal << "P"; break;
      case 0x1E: terminal << "A"; break;
      case 0x1F: terminal << "S"; break;
      case 0x20: terminal << "D"; break;
      case 0x21: terminal << "F"; break;
      case 0x22: terminal << "G"; break;
      case 0x23: terminal << "H"; break;
      case 0x24: terminal << "J"; break;
      case 0x25: terminal << "K"; break;
      case 0x26: terminal << "L"; break;
      case 0x2C: terminal << "Z"; break;
      case 0x2D: terminal << "X"; break;
      case 0x2E: terminal << "C"; break;
      case 0x2F: terminal << "V"; break;
      case 0x30: terminal << "B"; break;
      case 0x31: terminal << "N"; break;
      case 0x32: terminal << "M"; break;
    }
    if(shift)
    {
      switch(keycode)
      {
        case 0x02: terminal << "!"; break;
        case 0x03: terminal << "@"; break;
        case 0x04: terminal << "#"; break;
        case 0x05: terminal << "$"; break;
        case 0x06: terminal << "%"; break;
        case 0x07: terminal << "^"; break;
        case 0x08: terminal << "&"; break;
        case 0x09: terminal << "*"; break;
        case 0x0A: terminal << "("; break;
        case 0x0B: terminal << ")"; break;
        case 0x0C: terminal << "_"; break;
        case 0x0D: terminal << "+"; break;
        case 0x27: terminal << ":"; break;
        case 0x28: terminal << "\""; break;
        case 0x29: terminal << "~"; break;
        case 0x2B: terminal << "|"; break;
        case 0x33: terminal << "<"; break;
        case 0x34: terminal << ">"; break;
        case 0x35: terminal << "?"; break;
        case 0x1A: terminal << "{"; break;
        case 0x1B: terminal << "}"; break;
      }
    }
  }
  else
  {
    switch(keycode)
    {
      case 0x02: terminal << "1"; break;
      case 0x03: terminal << "2"; break;
      case 0x04: terminal << "3"; break;
      case 0x05: terminal << "4"; break;
      case 0x06: terminal << "5"; break;
      case 0x07: terminal << "6"; break;
      case 0x08: terminal << "7"; break;
      case 0x09: terminal << "8"; break;
      case 0x0A: terminal << "9"; break;
      case 0x0B: terminal << "0"; break;
      case 0x0C: terminal << "-"; break;
      case 0x0D: terminal << "="; break;
      case 0x27: terminal << ";"; break;
      case 0x28: terminal << "'"; break;
      case 0x29: terminal << "`"; break;
      case 0x2B: terminal << "\\"; break;
      case 0x33: terminal << ","; break;
      case 0x34: terminal << "."; break;
      case 0x35: terminal << "/"; break;
      case 0x1A: terminal << "["; break;
      case 0x1B: terminal << "]"; break;

      case 0x10: terminal << "q"; break;
      case 0x11: terminal << "w"; break;
      case 0x12: terminal << "e"; break;
      case 0x13: terminal << "r"; break;
      case 0x14: terminal << "t"; break;
      case 0x15: terminal << "y"; break;
      case 0x16: terminal << "u"; break;
      case 0x17: terminal << "i"; break;
      case 0x18: terminal << "o"; break;
      case 0x19: terminal << "p"; break;
      case 0x1E: terminal << "a"; break;
      case 0x1F: terminal << "s"; break;
      case 0x20: terminal << "d"; break;
      case 0x21: terminal << "f"; break;
      case 0x22: terminal << "g"; break;
      case 0x23: terminal << "h"; break;
      case 0x24: terminal << "j"; break;
      case 0x25: terminal << "k"; break;
      case 0x26: terminal << "l"; break;
      case 0x2C: terminal << "z"; break;
      case 0x2D: terminal << "x"; break;
      case 0x2E: terminal << "c"; break;
      case 0x2F: terminal << "v"; break;
      case 0x30: terminal << "b"; break;
      case 0x31: terminal << "n"; break;
      case 0x32: terminal << "m"; break;
    }
  }

  switch(keycode)
  {
    case 0x39: terminal << " "; break;
    case 0x0F: terminal << TAB; break;

    //case 0x01: terminal.keycode(ESCAPE); break;
    //case 0x38: terminal.print("LEFT ALT"); break;
    //case 0x1D: terminal.print("LEFT CONTROL"); break;

    case 0x1C: terminal.keycode(ENTER); break;
    case 0x0E: terminal.keycode(BACKSPACE); break;

    case 0x3A: this->Capitialization(CAPSLOCK_PRESS,(bool)1); break;
    case 0xBA: this->Capitialization(CAPSLOCK_RELEASE,(bool)0); break;

    case 0x2A: this->Capitialization(LEFT_SHIFT_PRESS,(bool)1); break;
    case 0xAA: this->Capitialization(LEFT_SHIFT_RELEASE,(bool)0); break;

    case 0x36: this->Capitialization(RIGHT_SHIFT_PRESS,(bool)1); break;
    case 0xB6: this->Capitialization(RIGHT_SHIFT_RELEASE,(bool)0); break;
  }
}
