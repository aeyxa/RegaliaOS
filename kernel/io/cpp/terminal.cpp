#include <Common/common.h>
#include <Regalia/terminal.h>

/**
* The code below is the short hand version of what's actually happening between
* all the functions. The functions just make it easier to calculate the numbers
* needed to be passed to the buffer and where you want them displayed on the
* screen.
*
* uint16_t* terminal_buffer;
*
* void terminal_initialize(void)
* {
*   terminal_buffer = (uint16_t*) 0xB8000;
*
*   terminal_buffer[0] = (uint16_t) 2920;
*   terminal_buffer[1] = (uint16_t) 2921;
* }
*
* The code above prints out "hi" to the screen, using the four digit numbers in
* which color and character are taken into account.
*/

Regalia::Terminal::Terminal()
{
  /**
  * Initializes the terminal, by setting the initial color state and the
  * position of the terminal.
  *
  * @terminal_buffer 0xB8000 is the memory location for writing with vga
  *
  * Information regarding this memory location can be found on Wikipedia:
  *   https://en.wikipedia.org/wiki/VGA-compatible_text_mode
  */
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = this->VGAColor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  terminal_buffer = (uint16_t*) 0xB8000;

  for(size_t y = 0; y < VGA_HEIGHT; y++)
  {
    for(size_t x = 0; x < VGA_WIDTH; x++)
    {
      const size_t index = y * VGA_WIDTH + x;
      terminal_buffer[index] = this->VGACharacter(' ', terminal_color);
    }
  }
}

Regalia::Terminal::~Terminal(){}

inline uint8_t Regalia::Terminal::VGAColor
(enum vga_colors fg, enum vga_colors bg)
{
  /**
  * Needed to calculate the appropiate color code for both the foreground and
  * the background.
  */
  return fg | bg << 4;
}

inline uint16_t Regalia::Terminal::VGACharacter(unsigned char uc,uint8_t color)
{
  /**
  * This function takes into account the character passed, and adds it's value
  * to the color selected, which is then returned to be displayed.
  */
  return(uint16_t) uc | (uint16_t) color << 8;
}

size_t Regalia::Terminal::StringLength(const char* str)
{
  /**
  * Needed to know how many characters the loop in send should be.
  */
  size_t len = 0;

  while(str[len])
  {
    len++;
  }
  return len;
}

void Regalia::Terminal::SetColor(uint8_t color)
{
  /**
  * This can be used to change the color at any time, an example would be for
  * changing color states between an error or success message.
  */
  terminal_color = color;
}

void Regalia::Terminal::Display
(char character, uint8_t color ,uint8_t x, uint8_t y)
{
  /**
  * This is what actually displays information, by passing a uint16_t number to
  * the vga location of memory, which is then evaluated and displayed.
  *
  * @index is the current position of where a character will be printed.
  */
  const size_t index = y * VGA_WIDTH + x;
  terminal_buffer[index] = this->VGACharacter(character, color);
}

bool Regalia::Terminal::ValidateScanCode(uint8_t validate, uint8_t scancode)
{
  /**
  * Compare values to validate before performing terminal logic.
  */
  bool correctScanCode;

  if(validate==scancode)
  {
    correctScanCode = true;
  }
  else correctScanCode = false;

  return correctScanCode;
}

void Regalia::Terminal::Enter(uint8_t scancode)
{
  /**
  * Add one to the row, reset cursor to position 0 on new line.
  */
  if(this->ValidateScanCode(0x1C,scancode))
  {
    if(terminal_column > 0)
    {
      ++terminal_row;
      terminal_column = 0;
    }
  }
}

void Regalia::Terminal::ClearScreen()
{
  terminal_column = 80;
  terminal_row = 25;

  for(uint8_t i = 0; i <= 10; i++)
  {
    for(uint8_t i = 0; i < 200; ++i)
    {
      this->Backspace(0x0E);
    }
  }
}

void Regalia::Terminal::Backspace(uint8_t scancode)
{
  /**
  * If we're not at the start position
  */
  if(ValidateScanCode(0x0E,scancode))
  {
    if(terminal_column == 0 && terminal_row != 0)
    {
      --terminal_row;
      terminal_column = 80;
      this->Display(' ', terminal_color, terminal_column, terminal_row);
    }
    if(terminal_column != 0)
    {
      --terminal_column;
      this->Display(' ', terminal_color, terminal_column, terminal_row);
    }
  }
}

void Regalia::Terminal::Position(char character)
{
  /**
  * Character from send goes to display, and then we add one to the column. If
  * the column is equal to the maximum, we add a new row, if the row is also at
  * it's maximum, then we reset that back to 0.
  */
  this->Display(character, terminal_color, terminal_column, terminal_row);

  if(++terminal_column == VGA_WIDTH)
  {
    terminal_column = 0;

    if(++terminal_row == VGA_HEIGHT)
    {
      terminal_row = 0;
    }
  }
}

void Regalia::Terminal::Send(const char* data, size_t size)
{
  /**
  * Loop over data equal to the number of times the size of the string passed,
  * and for each loop send that character to position.
  */
  for (size_t i = 0; i < size; i++)
  {
    if(data[i] == '\n')
    {
      ++terminal_row;
      terminal_column = 0;
    }
    else
    {
      this->Position(data[i]);
    }
  }
}

void Regalia::Terminal::Print(const char* data)
{
  /**
  * Send data to be displayed on the screen.
  */
  this->Send(data, StringLength(data));
}

void Regalia::Terminal::Print(int64_t data)
{
  // Get character for '0' then add the integer number to it, this increments
  // the binary value of the character '0' to represent the correct integer
  // provided as a char.

  #define OPPOSITE_OF_DATA (data = -(data))

  if(data < 0)
  {
    this->Position('-');
    data = ((char)('0' + OPPOSITE_OF_DATA));
  }
  else
  {
    data = ((char)('0' + data));
  }
  this->Position(data);
}

void Regalia::Terminal::Keycode(uint8_t scancode)
{
  switch(scancode)
  {
    case 0x01: this->ClearScreen(); break;
    case 0x0E: this->Backspace(scancode); break;
    case 0x1C: this->Enter(scancode); break;
  }
}

void Regalia::Terminal::Itoa(uint32_t x, uint32_t base)
{
  this->SetArray(x,base);
}

void Regalia::Terminal::SetArray(uint32_t x, uint32_t base)
{
  for(int i = 0; i <= 7; i++)
  {
    this->converted[i] = this->ConvertToCharacter(x % base);

    x /= base;
  }
  this->ReverseConverted();
}

char Regalia::Terminal::ConvertToCharacter(uint32_t x)
{
  if(x < 10)
  {
    return x + '0';
  }
  else
  {
    return x + 'A' - 10;
  }
}

void Regalia::Terminal::ReverseConverted()
{
  for(int i = 7; i >= 0; i--)
  {
    this->Position(this->converted[i]);
  }
}
