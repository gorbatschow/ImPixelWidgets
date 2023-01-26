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

  // Interface
  // ---------------------------------------------------------------------------

  // Polar To Pixel
  virtual const std::vector<std::size_t> &polarToPixel(double r,
                                                       double phi) override;

  // Cartesian Bounds Min
  virtual ImVec2 cartesianBoundsMin() const override {
    return {float(-_distance), float(-_distance)};
  }
  // Cartesian Bounds Max
  virtual ImVec2 cartesianBoundsMax() const override {
    return {float(+_distance), float(+_distance)};
  }

  // Make Cartesian Mesh
  virtual void makeCartesianMesh(std::vector<double> &x,
                                 std::vector<double> &y) const override;

  // Make Polar Mesh
  virtual void makePolarMesh(std::vector<double> &r,
                             std::vector<double> &phi) const override;

  // Grid Size
  virtual std::size_t gridSize() const override { return _gridSize; }

  // Config
  // ---------------------------------------------------------------------------
  void setConfig(const std::vector<PolarGridConfig> &configList);

private:
  std::vector<std::unique_ptr<PixelPolarGrid>> _gridList;
  double _distance{};
  std::size_t _gridSize{};
};
