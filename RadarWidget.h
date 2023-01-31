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

  // Set Pixel Sub Grid
  void setPixelSubGrid(std::shared_ptr<IPixelGrid> subgrid) {
    _pixelSubGrid = subgrid;
  }

  const IPixelGrid subGrid() const { return (*_pixelSubGrid); }

  // Set Color Scheme
  template <typename T> void setColorScheme(double min, double max) {
    _colorScheme.reset(new T);
    _colorScheme->valueMin = min;
    _colorScheme->valueMax = max;
  }

  // Get Color Scheme
  const ColorScheme &colorScheme() const { return (*_colorScheme); }

  // Clear Data
  inline void clearData() { _pixelData.fill(ColorRGBA::Transparent()); }

  // Set Polar Data
  template <typename T>
  inline void setPolarData(const T *r, const T *phi, const T *val,
                           std::size_t size) {
    if (!_pixelSubGrid) {
      for (std::size_t i{}; i != size; ++i) {
        _pixelData.fill(_pixelGrid->polarToPixel(r[i], phi[i]),
                        _colorScheme->valueToColor(val[i]));
      }
    } else {
      std::vector<std::size_t> pixel;
      double phi_min{}, phi_max{};
      for (std::size_t i{}; i != size; ++i) {
        /*
    _pixelGrid.
    _pixelData.fill(_pixelGrid->polarToPixel(r[i], phi[i]),
                    _colorScheme->valueToColor(val[i]));
                    */
      }
    }

    _pixelData.loadTexture();
  }

  // Set Cartesian Data
  template <typename T>
  inline void setCartesianData(const T *x, const T *y, const T *val,
                               std::size_t size) {
    for (std::size_t i{}; i != size; ++i) {
      _pixelData.fill(_pixelGrid->cartesianToPixel(x[i], y[i]),
                      _colorScheme->valueToColor(val[i]));
    }
    _pixelData.loadTexture();
  }

  // Get Pixel Data
  const PixelData &pixelData() const { return _pixelData; }

  // Display Scatter
  inline void setDisplayScatter(bool display) { _displayScatter = display; }
  inline bool displayScatter() const { return _displayScatter; }

  // Set Background Color
  inline void setBackgroundColor(ColorRGBA color) { _backgroudColor = color; }
  inline const ColorRGBA &backgroundColor() const { return _backgroudColor; }

private:
  ImVec2 _boundsMin;
  ImVec2 _boundsMax;
  PixelData _pixelData;
  std::shared_ptr<IPixelGrid> _pixelGrid{};
  std::shared_ptr<IPixelGrid> _pixelSubGrid{};
  std::unique_ptr<ColorScheme> _colorScheme{new ColorSchemeMono};
  bool _displayScatter{false};
  std::vector<double> _xGridNodes, _yGridNodes;
  ColorRGBA _backgroudColor{ColorRGBA::Transparent()};
};
