// NOTE: This file is only used for experimental purposes.

/*
#include <Experimental/terminal.h>

#define VGA_MEMORY_LOCATION 0xB8000

Experimental::Terminal::Terminal()
{
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = Color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  terminal_buffer = (uint16_t*) VGA_MEMORY_LOCATION;

  for(size_t y = 0; y < VGA_HEIGHT; y++)
  {
    for(size_t x = 0; x < VGA_WIDTH; x++)
    {
      const size_t index = y * VGA_WIDTH + x;
      terminal_buffer[index] = Character(' ', terminal_color);
    }
  }
}

Experimental::Terminal::~Terminal()
{
  terminal_buffer = 0;
}

uint8_t Experimental::Terminal::Color
(enum vga_colors foreground, enum vga_colors background)
{
  return foreground | background << 4;
}

uint16_t Experimental::Terminal::Character(uint8_t character, uint8_t color)
{
  return (uint16_t) character | (uint16_t) color << 8;
}

void Experimental::Terminal::SetColor(uint8_t color)
{
  terminal_color = color;
}

void Experimental::Terminal::Display
(char character, uint8_t color, uint8_t x, uint8_t y)
{
  const size_t index = y * VGA_WIDTH + x;
  terminal_buffer[index] = Character(character, color);
}

size_t Experimental::Terminal::StringLength(const char* str)
{
  size_t len = 0;

  while(str[len])
  {
    len++;
  }
  return len;
}

void Experimental::Terminal::Position(char character)
{
  Display(character, terminal_color, terminal_column, terminal_row);

  if(++terminal_column == VGA_WIDTH)
  {
    terminal_column = 0;

    if(++terminal_row == VGA_HEIGHT)
    {
      terminal_row = 0;
    }
  }
}

void Experimental::Terminal::Send(const char* data, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    if(data[i] == '\n')
    {
      ++terminal_row;
      terminal_column = 0;
    }
    else
    {
      Position(data[i]);
    }
  }
}

void Experimental::Terminal::Print(const char* data)
{
  Send(data, StringLength(data));
}

void Experimental::Terminal::Print(uint64_t data)
{

}
*/
