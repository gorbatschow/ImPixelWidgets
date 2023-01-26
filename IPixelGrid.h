#pragma once
#include "imgui.h"
#include <imgui.h>
#include <vector>

class IPixelGrid {
public:
  virtual ~IPixelGrid() = default;

  // Polar To Pixel
  virtual const std::vector<std::size_t> &polarToPixel(double r, double phi) {
    return _emptyPixel;
  };

  // Cartesian To Pixel
  virtual const std::vector<std::size_t> &cartesianToPixel(double x, double y) {
    return _emptyPixel;
  };

  // Cartesian Bounds Min
  virtual ImVec2 cartesianBoundsMin() const { return {0, 0}; };

  // Cartesian Bounds Max
  virtual ImVec2 cartesianBoundsMax() const { return {0, 0}; };

  // Make Cartesian Mesh
  virtual void makeCartesianMesh(std::vector<double> &x,
                                 std::vector<double> &y) const {}

  // Make Polar Mesh
  virtual void makePolarMesh(std::vector<double> &r,
                             std::vector<double> &phi) const {}

  // Grid Size
  virtual std::size_t gridSize() const { return 0; }

  // Polar Contains
  virtual bool polarContains(double r, double phi) const { return false; }

  // Cartesian Contains
  virtual bool cartesianContains(double x, double y) const { return false; }

  // Pixel Size
  // ---------------------------------------------------------------------------
  inline void setPixelWidth(std::size_t w) { _pixelWidth = w; }
  inline double pixelWidth() const { return _pixelWidth; }

  inline void setPixelHeight(std::size_t h) { _pixelHeight = h; }
  inline double pixelHeight() const { return _pixelHeight; }

  inline std::size_t pixelSize() const { return _pixelWidth * _pixelHeight; }

  // Rotation
  // ---------------------------------------------------------------------------
  inline void setRotation(double rot) { _rotation = rot; }
  inline double rotation() const { return _rotation; }

protected:
  inline const std::vector<std::size_t> &emptyPixel() const {
    return _emptyPixel;
  }

private:
  const std::vector<std::size_t> _emptyPixel{};
  std::size_t _pixelWidth{512};
  std::size_t _pixelHeight{512};
  double _rotation{};
};
