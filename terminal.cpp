#include "common.h"
#include "terminal.h"

aeyOS::Terminal::Terminal()
{
  /**
  * Initializes the terminal, by setting the initial color state and the
  * position of the terminal.
  *
  * @terminal_buffer 0xB8000 is the memory location for writing with vga
  */
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = vga_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  terminal_buffer = (uint16_t*) 0xB8000;

  for(size_t y = 0; y < VGA_HEIGHT; y++)
  {
    for(size_t x = 0; x < VGA_WIDTH; x++)
    {
      const size_t index = y * VGA_WIDTH + x;
      terminal_buffer[index] = vga_character(' ', terminal_color);
    }
  }
}

aeyOS::Terminal::~Terminal()
{
  /**
  * Decontructor, not current used.
  */
};

inline uint8_t aeyOS::Terminal::vga_color(enum vga_colors fg, enum vga_colors bg)
{
  /**
  * Needed to calculate the appropiate color code for both the foreground and
  * the background.
  */
  return fg | bg << 4;
}

inline uint16_t aeyOS::Terminal::vga_character(unsigned char uc, uint8_t color)
{
  /**
  * This function takes into account the character passed, and adds it's value
  * to the color selected, which is then returned to be displayed.
  */
  return(uint16_t) uc | (uint16_t) color << 8;
}

size_t aeyOS::Terminal::strlen(const char* str)
{
  /**
  * Needed to know how many characters the loop in send should be.
  */
  size_t len = 0

  while(str[len])
  {
    len++;
  }
  return len;
}

void aeyOS::Terminal::setcolor(uint8_t color)
{
  /**
  * This can be used to change the color at any time, an example would be for
  * changing color states between an error or success message.
  */
  terminal_color = color;
}

void aeyOS::Terminal::display(char character, uint8_t color, size_t x, size_t y)
{
  /**
  * This is what actually displays information, by passing a uint16_t number to
  * the vga location of memory, which is then evaluated and displayed.
  *
  * @index is the current position of where a character will be printed.
  */
  const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_character(character, color);
}

void aeyOS::Terminal::position(char character)
{
  /**
  * Character from send goes to display, and then we add one to the column. If
  * the column is equal to the maximum, we add a new row, if the row is also at
  * it's maximum, then we reset that back to 0.
  */
  display(character, terminal_color, terminal_column, terminal_row);

  if(++terminal_column == VGA_WIDTH)
  {
    terminal_column = 0;

    if(++terminal_row == VGA_HEIGHT)
    {
      terminal_row = 0;
    }
  }
}

void aeyOS::Terminal::send(const char* data, size_t size)
{
  /**
  * Loop over data equal to the number of times the size of the string passed,
  * and for each loop send that character to position.
  */
  for (size_t i = 0; i < size; i++)
  {
    position(data[i]);
  }
}

void aeyOS::Terminal::print(const char* data)
{
  /**
  * Send data to be displayed on the screen.
  */
  send(data, strlen(data));
}
