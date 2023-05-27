#pragma once
#include "ImPixelColorScheme.h"
#include "ImPixelGridData.h"
#include "ImPixelImage.h"
#include <limits.h>
#include <memory>

namespace ImPixel {
class GridDataImage : public Image {
public:
  // Constructor
  GridDataImage() {}

  // Destructor
  ~GridDataImage() = default;

  // Set Color Scheme
  template <typename T> inline void setColorScheme(double min, double max,
                             ColorRGBA background = ColorRGBA::Transparent()) {
    _colorScheme.reset(new T);
    _colorScheme->valueMin = min;
    _colorScheme->valueMax = max;
    _colorScheme->valueBackground = background;
  }

  // Set Color Scheme
  template <typename T> inline void setColorScheme(double max) {
    setColorScheme<T>(std::numeric_limits<double>::epsilon(), max);
  }

  // Set Color Scheme
  template <typename T> inline void setColorScheme(double max, ColorRGBA background) {
    setColorScheme<T>(std::numeric_limits<double>::epsilon(), max, background);
  }

  // Get Color Scheme
  inline const ColorScheme &colorScheme() const { return (*_colorScheme); }

  // Fill Data
  inline void fillData(const GridData &data) {
    Image::resize(data.grid().pixelWidth(), data.grid().pixelHeight());
    for (std::size_t index{}; index != data.size(); ++index) {
      Image::fill(data.pixel(index),
                  _colorScheme->valueToColor(data.value(index)));
    }
  }

private:
  std::unique_ptr<ColorScheme> _colorScheme{new ColorSchemeMono};
};
} // namespace ImPixel
