#pragma once
#include <array>
#include <cstdint>
#include <cstring>

namespace ImPixel {
class ColorRGBA {
public:
  // Constructor
  ColorRGBA() {}

  ColorRGBA(const uint8_t *rgba) {
    std::memcpy(_rgba.data(), rgba, _rgba.size());
  }

  ColorRGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
    _rgba[0] = red;
    _rgba[1] = green;
    _rgba[2] = blue;
    _rgba[3] = alpha;
  }

  // Destructor
  ~ColorRGBA() = default;

  // Fill
  inline void fill(uint8_t *dst) const {
    std::memcpy(dst, _rgba.data(), _rgba.size());
  }

  inline void setRed(uint8_t red) { _rgba[0] = red; }
  inline uint8_t red() const { return _rgba[0]; }

  inline void setGreen(uint8_t green) { _rgba[1] = green; }
  inline uint8_t green() const { return _rgba[1]; }

  inline void setBlue(uint8_t blue) { _rgba[2] = blue; }
  inline uint8_t blue() const { return _rgba[2]; }

  inline void setAlpha(uint8_t alpha) { _rgba[3] = alpha; }
  inline uint8_t alpha() const { return _rgba[3]; }

  inline static void Fill(uint8_t *dst, const uint8_t *src) {
    std::memcpy(dst, src, Size());
  }
  inline static void Fill(uint8_t *dst, const std::array<uint8_t, 3> &rgb,
                          const uint8_t &alpha) {
    std::memcpy(dst, rgb.data(), Size());
    dst[3] = alpha;
  }

  static ColorRGBA Transparent() { return {0, 0, 0, 0}; }
  static ColorRGBA Aqua() { return {0, 255, 255, 255}; }
  static ColorRGBA Lime() { return {0, 255, 0, 255}; }

  static uint8_t Size() { return 4; }
  static uint8_t Max() { return 255; }

  static ColorRGBA Mean(const ColorRGBA &first, const ColorRGBA &second) {
    ColorRGBA color;
    color.setRed(float(first.red()) + float(second.red()) / 2.f);
    color.setGreen(float(first.green()) + float(second.green()) / 2.f);
    color.setBlue(float(first.blue()) + float(second.blue()) / 2.f);
    return color;
  }

  static ColorRGBA Mean(const ColorRGBA &first, const ColorRGBA &second,
                        float w1, float w2) {
    ColorRGBA color;
    color.setRed(w1 * float(first.red()) +
                 w2 * float(second.red()) / (w1 + w2));
    color.setGreen(w1 * float(first.green()) +
                   w2 * float(second.green()) / (w1 + w2));
    color.setBlue(w1 * float(first.blue()) +
                  w2 * float(second.blue()) / (w1 + w2));
    return color;
  }

private:
  std::array<uint8_t, 4> _rgba{};
};
} // namespace ImPixel
