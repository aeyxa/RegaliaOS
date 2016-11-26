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
    void Capitialization(uint8_t keycode, bool status);
    void DisplayActivation();
    void HandleKey(uint8_t keycode);
    uint8_t keycode;
    bool capitials;
    bool shift;
  };
}
