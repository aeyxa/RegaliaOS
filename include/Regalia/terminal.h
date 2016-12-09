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
    void Keycode(uint8_t scancode);
    void ClearScreen();
    void Itoa(uint32_t x, uint32_t base);

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

    void Print(int64_t data);
    void Print(const char* data);
    void Position(char character);
    void Send(const char* data, size_t size);
    bool ValidateScanCode(uint8_t scancode, uint8_t character);
    void Display(char character, uint8_t color, uint8_t x, uint8_t y);

    void Tab(uint8_t scancode);
    void Enter(uint8_t scancode);
    void Backspace(uint8_t scancode);

    void ReverseConverted();
    char ConvertToCharacter(uint32_t x);
    void SetArray(uint32_t x, uint32_t base);
    char converted[8];
  };
}
