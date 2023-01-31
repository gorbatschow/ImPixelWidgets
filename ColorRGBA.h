#pragma once
#include <array>
#include <cstdint>

class ColorRGBA {
public:
  // Constructor
  ColorRGBA() {}

  // Constructor
  ColorRGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
      : _red(red), _green(green), _blue(blue), _alpha(alpha) {}

  // Destructor
  ~ColorRGBA() = default;

  // Fill
  inline void fill(uint8_t *ptr) const {
    ptr[0] = red();
    ptr[1] = green();
    ptr[2] = blue();
    ptr[3] = alpha();
  }

  inline void setRed(uint8_t red) { _red = red; }
  inline uint8_t red() const { return _red; }

  inline void setGreen(uint8_t green) { _green = green; }
  inline uint8_t green() const { return _green; }

  inline void setBlue(uint8_t blue) { _blue = blue; }
  inline uint8_t blue() const { return _blue; }

  inline void setAlpha(uint8_t alpha) { _alpha = alpha; }
  inline uint8_t alpha() const { return _alpha; }

  static ColorRGBA Transparent() { return {0, 0, 0, 0}; }
  static ColorRGBA Aqua() { return {0, 255, 255, 255}; }
  static ColorRGBA Lime() { return {0, 255, 0, 255}; }

  static uint8_t Size() { return 4; }
  static uint8_t Max() { return 255; }

private:
  uint8_t _red{};
  uint8_t _green{};
  uint8_t _blue{};
  uint8_t _alpha{};
};
