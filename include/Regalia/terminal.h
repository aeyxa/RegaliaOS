#pragma once

#include <Common/common.h>

namespace Regalia
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
    static inline uint8_t vga_color(enum vga_colors fg, enum vga_colors bg);
    static inline uint16_t vga_character(unsigned char uc, uint8_t color);
    size_t strlen(const char* str);
    void setcolor(uint8_t color);
    void display(char character, uint8_t color, uint8_t x, uint8_t y);
    void position(char character);
    void enter(uint8_t scancode);
    void backspace(uint8_t scancode);
    void tab(uint8_t scancode);
    bool validateScanCode(uint8_t scancode, uint8_t character);
    void send(const char* data, size_t size);
    void print(const char* data);
    void print(uint8_t data);
    void keycode(uint8_t scancode);
    bool startPosition();
    void capitialStatus(uint8_t scancode, bool status);
  private:
    bool capitials;

    static const size_t VGA_WIDTH = 80;
    static const size_t VGA_HEIGHT = 25;

    uint8_t terminal_row;
    uint8_t terminal_column;
    uint8_t terminal_color;
    uint16_t* terminal_buffer;
  };
}
