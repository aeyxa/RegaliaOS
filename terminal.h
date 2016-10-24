#ifndef TERMINAL_H
#define TERMINAL_H

namespace aeyOS
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
    void display(char character, uint8_t color, size_t x, size_t y);
    void position(char character);
    void send(const char* data, size_t size);
    void print(const char* data);
  private:
    static const size_t VGA_WIDTH = 80;
    static const size_t VGA_HEIGHT = 25;

    size_t terminal_row;
    size_t terminal_column;
    uint8_t terminal_color;
    uint16_t* terminal_buffer;
  };
}

#endif
