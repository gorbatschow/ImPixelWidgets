#pragma once
#include "IPixelGrid.h"
#include "PixelPolarGrid.h"
#include "PolarGridConfig.h"
#include <memory>
#include <vector>

class PixelMultiPolarGrid : public IPixelGrid {
public:
  // Constructor
  PixelMultiPolarGrid(const std::vector<PolarGridConfig> &configList = {});

  // Destructor
  virtual ~PixelMultiPolarGrid() override = default;

  // Polar To Pixel
  virtual const std::vector<std::size_t> &
  polarToPixel(double r, double phi) const override;

  // Cartesian To Pixel
  virtual const std::vector<std::size_t> &
  cartesianToPixel(double x, double y) const override;

  // Sector To Pixel
  virtual bool sectorToPixel(
      double r, double phi_min, double phi_max,
      std::vector<std::vector<std::size_t>> &pixel_list) const override;

  // Cartesian Bounds Min
  virtual ImVec2 cartesianBoundsMin() const override {
    return {float(-distanceRange()), float(-distanceRange())};
  }
  // Cartesian Bounds Max
  virtual ImVec2 cartesianBoundsMax() const override {
    return {float(+distanceRange()), float(+distanceRange())};
  }

  // Make Cartesian Mesh
  virtual void makeCartesianMesh(std::vector<double> &x,
                                 std::vector<double> &y) const override;

  // Make Polar Mesh
  virtual void makePolarMesh(std::vector<double> &r,
                             std::vector<double> &phi) const override;

  // Grid Size
  virtual std::size_t gridSize() const override { return _gridSize; }

  // Pixel Width
  virtual std::size_t pixelWidth() const override {
    if (_gridList.empty()) {
      return 0;
    }
    return _gridList.front()->config().pixelWidth();
  }

  // Pixel Height
  virtual std::size_t pixelHeight() const override {
    if (_gridList.empty()) {
      return 0;
    }
    return _gridList.front()->config().pixelHeight();
  }

  // Distance Range
  inline double distanceRange() const {
    if (_gridList.empty()) {
      return 0;
    }
    return _gridList.front()->config().distanceRange();
  }

  // Polar Contains
  virtual bool polarContains(double r, double phi) const override;

  // Cartesian Contains
  virtual bool cartesianContains(double x, double y) const override;

  // Range Bounds
  virtual bool distanceBounds(double r, double &min,
                              double &max) const override;

  // Bearing Bounds
  virtual bool bearingBounds(double phi, double &min,
                             double &max) const override;

  // Config
  void setConfig(const std::vector<PolarGridConfig> &configList);

private:
  std::vector<std::unique_ptr<PixelPolarGrid>> _gridList;
  std::size_t _gridSize{};
};
