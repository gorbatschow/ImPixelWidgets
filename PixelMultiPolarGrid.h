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

  // Index
  // ---------------------------------------------------------------------------
  // Index To Pixel
  virtual const std::vector<std::size_t> &
  indexToPixel(std::size_t index) const override;

  // Node
  // ---------------------------------------------------------------------------
  // to Pixel
  virtual const std::vector<std::size_t> &
  nodeToPixel(std::size_t dim_1, std::size_t dim_2) const override {
    return IPixelGrid::nodeToPixel(dim_1, dim_2);
  }

  // Grid Size
  virtual std::size_t gridSize(std::size_t dim = 0) const override;

  // Pixel
  // ---------------------------------------------------------------------------
  // Pixel Width
  virtual std::size_t pixelWidth() const override;

  // Pixel Height
  virtual std::size_t pixelHeight() const override;

  // Polar
  // ---------------------------------------------------------------------------
  // to Pixel
  virtual const std::vector<std::size_t> &
  polarToPixel(double r, double phi) const override;

  // Sector To Pixel
  virtual bool sectorToPixel(std::vector<std::vector<std::size_t>> &pixel_list,
                             double r, double phi_min,
                             double phi_max) const override;

  // to Index
  virtual void polarToIndex(std::size_t &index, double r,
                            double phi) const override;

  // Distance Range
  inline double distanceRange() const {
    if (_gridList.empty()) {
      return 0;
    }
    return _gridList.front()->config().distanceRange();
  }

  // Polar Contains
  virtual bool polarContains(double r, double phi) const override;

  // Make Polar Mesh
  virtual void makePolarMesh(std::vector<double> &r,
                             std::vector<double> &phi) const override;
  // Cartesian
  // ---------------------------------------------------------------------------
  // Cartesian To Pixel
  virtual const std::vector<std::size_t> &
  cartesianToPixel(double x, double y) const override;

  // Cartesian Bounds Min
  virtual ImVec2 cartesianBoundsMin() const override;
  // Cartesian Bounds Max
  virtual ImVec2 cartesianBoundsMax() const override;

  // Make Cartesian Mesh
  virtual void makeCartesianMesh(std::vector<double> &x,
                                 std::vector<double> &y) const override;

  // Cartesian Contains
  virtual bool cartesianContains(double x, double y) const override;

  // Range Bounds
  virtual bool distanceBounds(double &min, double &max,
                              double r) const override;

  // Bearing Bounds
  virtual bool bearingBounds(double &min, double &max,
                             double phi) const override;

  // Distance Nodes
  virtual const std::vector<double> &
  distanceNodes(double bearing) const override;

  // Bearing Nodes
  virtual const std::vector<double> &
  bearingNodes(double distance) const override;

  // Config
  void setConfig(const std::vector<PolarGridConfig> &configList);

private:
  std::vector<std::unique_ptr<PixelPolarGrid>> _gridList;
  std::vector<const std::vector<std::size_t> *> _pixelIndex;
};
