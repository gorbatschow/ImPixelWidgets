#pragma once
#include "ColorScheme.h"
#include "PixelData.h"
#include "PolarGrid.h"
#include <implot.h>
#include <memory>

class RadarWidget {
public:
  // Constructor
  RadarWidget();

  // Destructor
  virtual ~RadarWidget() = default;

  // Paint
  virtual void paint();

  // Set Grid
  void setGrid(const PolarGrid &grid);

  // Get Grid
  const PolarGrid &grid() const { return _grid; }

  // Set Color Scheme
  template <typename T> void setColorScheme(double min, double max) {
    _colorScheme.reset(new T);
    _colorScheme->valueMin = min;
    _colorScheme->valueMax = max;
  }

  // Get Color Scheme
  const ColorScheme &colorScheme() const { return (*_colorScheme); }

  // Clear Data
  inline void clearData() { _pixels.fill(ColorRGBA_Transparent); }

  // Set Data
  template <typename T>
  inline void setData(const std::vector<T> &r, const std::vector<T> &phi,
                      const std::vector<T> &val) {
    for (std::size_t i{}; i != r.size(); ++i) {
      _pixels.fill(_grid.polarToPixel(r[i], phi[i]),
                   _colorScheme->valueToColor(val[i]));
    }
    _pixels.loadTexture();
  }

  // Get Pixel Data
  const PixelData &pixelData() const { return _pixels; }

  // Display Scatter
  inline void setDisplayScatter(bool display) { _displayScatter = display; }
  inline bool displayScatter() const { return _displayScatter; }

private:
  ImVec2 _boundsMin;
  ImVec2 _boundsMax;
  PixelData _pixels;
  PolarGrid _grid;
  std::unique_ptr<ColorScheme> _colorScheme{new ColorSchemeMono};
  bool _displayScatter{false};
};
