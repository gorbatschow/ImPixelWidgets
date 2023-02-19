#pragma once
#include "ImPixelColorScheme.h"
#include "ImPixelGridData.h"
#include "ImPixelImage.h"
#include <implot.h>
#include <memory>

namespace ImPixel {
class RadarWidget {
public:
  // Constructor
  RadarWidget();

  // Destructor
  virtual ~RadarWidget() = default;

  // Paint
  virtual void paint();

  // Set Color Scheme
  template <typename T> void setColorScheme(double min, double max) {
    _colorScheme.reset(new T);
    _colorScheme->valueMin = min;
    _colorScheme->valueMax = max;
  }

  // Get Color Scheme
  const ColorScheme &colorScheme() const { return (*_colorScheme); }

  // Fill Image
  void fillImage(const PixelGridData &data);

  inline void fillImage(const std::vector<std::size_t> &pixel,
                        const ColorRGBA &color) {
    _pixelData.fill(pixel, color);
  }

  inline void fillImage(const ColorRGBA &color) { _pixelData.fill(color); }

  // Clear Image
  inline void clearImage() { _pixelData.clear(); }

  inline void clearImage(const std::vector<std::size_t> &pixel) {
    _pixelData.clear(pixel);
  }

  // Render Image
  inline void renderImage() { _pixelData.render(); }

  // Resize Image
  inline void resizeImage(std::size_t w, std::size_t h) {
    _pixelData.resize(w, h);
  }

  // Get Image
  const PixelImage &image() const { return _pixelData; }

  // Display Scatter
  inline void setDisplayScatter(bool display) { _displayScatter = display; }
  inline bool displayScatter() const { return _displayScatter; }

private:
  ImVec2 _boundsMin;
  ImVec2 _boundsMax;
  PixelImage _pixelData;
  std::vector<double> _xGridNodes, _yGridNodes;
  std::unique_ptr<ColorScheme> _colorScheme{new ColorSchemeMono};
  bool _displayScatter{false};
};
} // namespace ImPixel
