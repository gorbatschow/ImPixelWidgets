#pragma once
#include "ColorScheme.h"
#include "PixelGridData.h"
#include "PixelImage.h"
#include <limits.h>
#include <memory>

class PixelGridDataImage : public PixelImage {
public:
  // Constructor
  PixelGridDataImage() {}

  // Destructor
  ~PixelGridDataImage() = default;

  // Set Color Scheme
  template <typename T> inline void setColorScheme(double min, double max) {
    _colorScheme.reset(new T);
    _colorScheme->valueMin = min;
    _colorScheme->valueMax = max;
  }

  // Set Color Scheme
  template <typename T> inline void setColorScheme(double max) {
    setColorScheme<T>(std::numeric_limits<double>::epsilon(), max);
  }

  // Get Color Scheme
  inline const ColorScheme &colorScheme() const { return (*_colorScheme); }

  // Fill Data
  inline void fillData(const PixelGridData &data) {
    PixelImage::resize(data.grid().pixelWidth(), data.grid().pixelHeight());
    for (std::size_t index{}; index != data.size(); ++index) {
      PixelImage::fill(data.pixel(index),
                       _colorScheme->valueToColor(data.value(index)));
    }
  }

private:
  std::unique_ptr<ColorScheme> _colorScheme{new ColorSchemeMono};
};
