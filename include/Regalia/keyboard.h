#pragma once

//void keyboard_handler();

namespace Regalia
{
  class Keyboard
  {
  public:
    Keyboard();
    ~Keyboard();
    void CheckData();
  private:
    void DisplayActivation();
    void HandleKey(uint8_t keycode);
    uint8_t keycode;
    bool capitials;
  };
}
