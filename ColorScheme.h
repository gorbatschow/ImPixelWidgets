#pragma once
#include "ColorRGBA.h"
#include <algorithm>

struct ColorScheme {
  double valueMin{0};
  double valueMax{1};

  virtual ~ColorScheme() = default;

  inline ColorRGBA valueToColor(double value, double alpha = 1.0) const {
    value = std::clamp(value, valueMin, valueMax);
    value = value / valueMax;
    return {uint8_t(red(value) * ColorRGBA_Max),
            uint8_t(green(value) * ColorRGBA_Max),
            uint8_t(blue(value) * ColorRGBA_Max),
            uint8_t(alpha * ColorRGBA_Max)};
  }

  virtual double red(const double &value) const = 0;
  virtual double green(const double &value) const = 0;
  virtual double blue(const double &value) const = 0;
};

// Monochromatic
// -----------------------------------------------------------------------------
struct ColorSchemeMono : public ColorScheme {
  virtual double red(const double &value) const { return value; }
  virtual double green(const double &value) const { return value; }
  virtual double blue(const double &value) const { return value; }
};
