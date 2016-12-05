// NOTE: This file is only used for experimental purposes.

#pragma once

#include <Common/common.h>

namespace Experimental
{
  class Terminal
  {
  public:
    enum vga_colors
    {
      VGA_COLOR_BLACK,
      VGA_COLOR_BLUE,
      VGA_COLOR_GREEN,
      VGA_COLOR_CYAN,
      VGA_COLOR_RED,
      VGA_COLOR_MAGENTA,
      VGA_COLOR_BROWN,
      VGA_COLOR_LIGHT_GREY,
      VGA_COLOR_DARK_GREY,
      VGA_COLOR_LIGHT_BLUE,
      VGA_COLOR_LIGHT_GREEN,
      VGA_COLOR_LIGHT_CYAN,
      VGA_COLOR_LIGHT_RED,
      VGA_COLOR_LIGHT_MAGENTA,
      VGA_COLOR_LIGHT_BROWN,
      VGA_COLOR_WHITE,
    };
    Terminal();
    ~Terminal();
    uint8_t Color(enum vga_colors foreground, enum vga_colors background);
    uint16_t Character(uint8_t character, uint8_t color);
    void SetColor(uint8_t color);
    size_t StringLength(const char* str);
    void Display(char character, uint8_t color, uint8_t x, uint8_t y);
    void Position(char character);
    void Send(const char* data, size_t size);
    void Print(const char* data);

    template <typename T>auto operator<<(T data) -> Terminal &
    {
      Print(data);
      return *this;
    }
    
  private:
    uint8_t terminal_row;
    uint8_t terminal_column;
    uint8_t terminal_color;
    uint16_t* terminal_buffer;

    static const size_t VGA_WIDTH = 80;
    static const size_t VGA_HEIGHT = 25;
  };
}
