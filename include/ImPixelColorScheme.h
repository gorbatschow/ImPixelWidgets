#pragma once
#include "ImPixelColorRGBA.h"
#include <algorithm>
#include <limits>

namespace ImPixel {
struct ColorScheme {
  double valueMin{0};
  double valueMax{1};
  ColorRGBA valueBackground{ColorRGBA::Transparent()};

  virtual ~ColorScheme() = default;

  inline ColorRGBA valueToColor(double value, double alpha = 1.0) const {
    if (value >= valueMin) {
      const auto norm_value{normalizeValue(value)};
      return {red(norm_value), green(norm_value), blue(norm_value),
              normalizaAlpha(alpha)};
    };
    return valueBackground;
  }

  inline const std::array<uint8_t, 3> &valueToRGB(double value) const {
    if (value >= valueMin) {
      return rgb(normalizeValue(value));
    }
    static const std::array<uint8_t, 3> zeros{0, 0, 0};
    return zeros;
  }

  virtual uint8_t red(uint8_t value) const = 0;
  virtual uint8_t green(uint8_t value) const = 0;
  virtual uint8_t blue(uint8_t value) const = 0;
  virtual const std::array<uint8_t, 3> &rgb(uint8_t value) const = 0;

  inline uint8_t normalizeValue(const double &value) const {
    return std::min(value, valueMax) / valueMax * ColorRGBA::Max();
  }

  inline uint8_t normalizaAlpha(const double &alpha) const {
    return uint8_t(alpha * ColorRGBA::Max());
  }
};

// Monochromatic
// -----------------------------------------------------------------------------
struct ColorSchemeMono : public ColorScheme {
  virtual uint8_t red(uint8_t value) const override { return value; }
  virtual uint8_t green(uint8_t value) const override { return value; }
  virtual uint8_t blue(uint8_t value) const override { return value; }
  virtual const std::array<uint8_t, 3> &rgb(uint8_t value) const override;
};

// Turbo
// -----------------------------------------------------------------------------
struct ColorSchemeTurbo : public ColorScheme {
  virtual uint8_t red(uint8_t value) const override;
  virtual uint8_t green(uint8_t value) const override;
  virtual uint8_t blue(uint8_t value) const override;
  virtual const std::array<uint8_t, 3> &rgb(uint8_t value) const override;
};

} // namespace ImPixel
