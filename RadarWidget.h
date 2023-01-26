#pragma once
#include "ColorScheme.h"
#include "IPixelGrid.h"
#include "PixelData.h"
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

  // Set Pixel Grid
  void setPixelGrid(std::shared_ptr<IPixelGrid> grid);

  // Get Grid
  const IPixelGrid &grid() const { return (*_pixelGrid); }

  // Set Color Scheme
  template <typename T> void setColorScheme(double min, double max) {
    _colorScheme.reset(new T);
    _colorScheme->valueMin = min;
    _colorScheme->valueMax = max;
  }

  // Get Color Scheme
  const ColorScheme &colorScheme() const { return (*_colorScheme); }

  // Clear Data
  inline void clearData() { _pixelData.fill(ColorRGBA_Transparent); }

  // Set Polar Data
  template <typename T>
  inline void setPolarData(const T *r, const T *phi, const T *val,
                           std::size_t size) {
    for (std::size_t i{}; i != size; ++i) {
      _pixelData.fill(_pixelGrid->polarToPixel(r[i], phi[i]),
                      _colorScheme->valueToColor(val[i]));
    }
    _pixelData.loadTexture();
  }

  // Set Cartesian Data
  template <typename T>
  inline void setCartesianData(const T *y, const T *x, const T *val,
                               std::size_t size) {
    for (std::size_t i{}; i != size; ++i) {
      _pixelData.fill(_pixelGrid->cartesianToPixel(y[i], x[i]),
                      _colorScheme->valueToColor(val[i]));
    }
    _pixelData.loadTexture();
  }

  // Get Pixel Data
  const PixelData &pixelData() const { return _pixelData; }

  // Display Scatter
  inline void setDisplayScatter(bool display) { _displayScatter = display; }
  inline bool displayScatter() const { return _displayScatter; }

private:
  ImVec2 _boundsMin;
  ImVec2 _boundsMax;
  PixelData _pixelData;
  std::shared_ptr<IPixelGrid> _pixelGrid{};
  std::unique_ptr<ColorScheme> _colorScheme{new ColorSchemeMono};
  bool _displayScatter{false};
  std::vector<double> _xGridNodes, _yGridNodes;
};
