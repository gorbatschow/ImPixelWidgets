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
  inline const IPixelGrid &grid() const { return (*_pixelGrid); }

  // Set Pixel Sub Grid
  void setPixelSubGrid(std::shared_ptr<IPixelGrid> subgrid);
  inline const IPixelGrid subGrid() const { return (*_pixelSubGrid); }

  // Set Color Scheme
  template <typename T> void setColorScheme(double min, double max) {
    _colorScheme.reset(new T);
    _colorScheme->valueMin = min;
    _colorScheme->valueMax = max;
  }

  // Get Color Scheme
  const ColorScheme &colorScheme() const { return (*_colorScheme); }

  // Set Polar Data
  template <typename T>
  inline void setPolarData(const T *r, const T *phi, const T *val,
                           std::size_t size) {

    for (std::size_t i{}; i != size; ++i) {
      _pixelData.fill(_pixelGrid->polarToPixel(r[i], phi[i]),
                      _colorScheme->valueToColor(val[i]));
    }

    if (_pixelSubGrid) {
      std::vector<std::vector<std::size_t>> pixel_list;

      ColorRGBA color, color0, color1;
      double phi_min{}, phi_max{}, phi_delta{};
      const auto &r_nodes = _pixelSubGrid->distanceNodes();

      for (std::size_t i{}; i != r_nodes.size(); ++i) {
        const auto &phi_nodes = _pixelGrid->bearingNodes(r_nodes[i]);
        if (phi_nodes.empty()) {
          continue;
        }
        for (std::size_t j{}; j != phi_nodes.size(); ++j) {
          pixel_list.clear();
          _pixelGrid->bearingBounds(phi_nodes[j], phi_min, phi_max);
          phi_delta = (phi_nodes[j + 1] - phi_nodes[j]) / 2.;
          _pixelSubGrid->sectorToPixel(r_nodes[i], phi_min + phi_delta,
                                       phi_max + phi_delta, pixel_list);
          if (pixel_list.empty()) {
            continue;
          }

          color0 = _pixelData.colorAt(pixel_list.front().front());
          color1 = _pixelData.colorAt(pixel_list.back().back());
          for (std::size_t k{}; k != pixel_list.size(); ++k) {
            color = ColorRGBA::Mean(color0, color1, pixel_list.size() - k, k);
            _pixelData.fill(pixel_list[k], color0);
          }
        }
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

  // Clear Image
  inline void clearImage() { _pixelData.clear(); }
  inline void clearImage(const std::vector<std::size_t> &pixel) {
    _pixelData.clear(pixel);
  }

  // Fill Image
  inline void fillImage(const ColorRGBA &color) { _pixelData.fill(color); }
  inline void fillImage(const std::vector<std::size_t> &pixel,
                        const ColorRGBA &color) {
    _pixelData.fill(pixel, color);
  }

  // Get Image
  const PixelData &image() const { return _pixelData; }

  // Display Scatter
  inline void setDisplayScatter(bool display) { _displayScatter = display; }
  inline bool displayScatter() const { return _displayScatter; }

private:
  ImVec2 _boundsMin;
  ImVec2 _boundsMax;
  PixelData _pixelData;
  std::shared_ptr<IPixelGrid> _pixelGrid{};
  std::vector<double> _xGridNodes, _yGridNodes;
  std::shared_ptr<IPixelGrid> _pixelSubGrid{};
  std::vector<double> _xSubGridNodes, _ySubGridNodes;
  std::unique_ptr<ColorScheme> _colorScheme{new ColorSchemeMono};
  bool _displayScatter{false};
};
