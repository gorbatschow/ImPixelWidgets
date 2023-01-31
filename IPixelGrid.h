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

  // Sector To Pixel
  virtual void sectorToPixel(double r, double phi_min, double phi_max,
                             std::vector<std::vector<std::size_t>> &pixel) {}

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
  virtual std::size_t pixelWidth() const { return 0; }
  virtual std::size_t pixelHeight() const { return 0; }

  // Distance Bounds
  virtual bool distanceBounds(double r, double &min, double &max) const {
    return false;
  }

  // Bearing Bounds
  virtual bool bearingBounds(double phi, double &min, double &max) const {
    return false;
  }

protected:
  inline const std::vector<std::size_t> &emptyPixel() const {
    return _emptyPixel;
  }

private:
  const std::vector<std::size_t> _emptyPixel{};
};
