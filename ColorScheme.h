#pragma once
#include "ColorRGBA.h"
#include <algorithm>

struct ColorScheme {
  double valueMin{0};
  double valueMax{1};

  virtual ~ColorScheme() = default;

  inline ColorRGBA valueToColor(double value, double alpha = 1.0) const {
    value = std::clamp(value, valueMin, valueMax);
    value = value / valueMax * ColorRGBA::Max();
    return {red(uint8_t(value)), green(uint8_t(value)), blue(uint8_t(value)),
            uint8_t(alpha * ColorRGBA::Max())};
  }

  virtual uint8_t red(uint8_t value) const = 0;
  virtual uint8_t green(uint8_t value) const = 0;
  virtual uint8_t blue(uint8_t value) const = 0;
};

// Monochromatic
// -----------------------------------------------------------------------------
struct ColorSchemeMono : public ColorScheme {
  virtual uint8_t red(uint8_t value) const override { return value; }
  virtual uint8_t green(uint8_t value) const override { return value; }
  virtual uint8_t blue(uint8_t value) const override { return value; }
};

// Turbo
// -----------------------------------------------------------------------------
struct ColorSchemeTurbo : public ColorScheme {
  virtual uint8_t red(uint8_t value) const override;
  virtual uint8_t green(uint8_t value) const override;
  virtual uint8_t blue(uint8_t value) const override;
};
