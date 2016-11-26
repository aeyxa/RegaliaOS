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
    static inline uint8_t VGAColor(enum vga_colors fg, enum vga_colors bg);
    static inline uint16_t VGACharacter(unsigned char uc, uint8_t color);
    size_t StringLength(const char* str);
    void SetColor(uint8_t color);
    void Display(char character, uint8_t color, uint8_t x, uint8_t y);
    void Position(char character);
    void Enter(uint8_t scancode);
    void Backspace(uint8_t scancode);
    void Tab(uint8_t scancode);
    bool ValidateScanCode(uint8_t scancode, uint8_t character);
    void Send(const char* data, size_t size);
    void Print(const char* data);
    void Print(uint8_t data);
    void Keycode(uint8_t scancode);
    void ClearScreen();

    template <typename T>auto operator<<(T data) -> Terminal &
    {
      Print(data);
      return *this;
    }

  private:
    static const size_t VGA_WIDTH = 80;
    static const size_t VGA_HEIGHT = 25;

    uint8_t terminal_row;
    uint8_t terminal_column;
    uint8_t terminal_color;
    uint16_t* terminal_buffer;
  };
}
