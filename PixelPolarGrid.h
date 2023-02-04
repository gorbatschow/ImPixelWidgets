#pragma once
#include "IPixelGrid.h"
#include "PolarGridConfig.h"
#include <array>
#include <cassert>
#include <cmath>
#include <numeric>
#include <vector>

class PixelPolarGrid : public IPixelGrid {
public:
  PixelPolarGrid(const PolarGridConfig &config = PolarGridConfig());
  virtual ~PixelPolarGrid() override = default;

  // Index
  // ---------------------------------------------------------------------------
  // Index To Pixel
  virtual const std::vector<std::size_t> &
  indexToPixel(std::size_t index) const override;

  virtual bool indexToNode(std::size_t &dim_1, std::size_t &dim_2,
                           std::size_t index) const override;

  // Node
  // ---------------------------------------------------------------------------
  // to Pixel
  virtual const std::vector<std::size_t> &
  nodeToPixel(std::size_t dim_1, std::size_t dim_2) const override;

  // to Index
  virtual bool nodeToIndex(std::size_t &index, std::size_t dim_1,
                           std::size_t dim_2) const override;

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
  virtual bool polarToIndex(std::size_t &index, double r,
                            double phi) const override;

  // Polar To Node
  virtual bool polarToNode(std::size_t &dim_1, std::size_t &dim_2, double r,
                           double phi) const override;

  // Distance Nodes
  virtual const std::vector<double> &
  distanceNodes(double distance = 0) const override;

  // Bearing Nodes
  virtual const std::vector<double> &
  bearingNodes(double distnace = 0) const override;

  // Distance Bounds
  virtual bool distanceBounds(double &min, double &max,
                              double r) const override;

  // Bearing Bounds
  virtual bool bearingBounds(double &min, double &max,
                             double phi) const override;

  // Polar Contains
  virtual bool polarContains(double r, double phi) const override;

  // Make Polar Mesh
  virtual void makePolarMesh(std::vector<double> &r,
                             std::vector<double> &phi) const override;

  // Cartesian
  // ---------------------------------------------------------------------------
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
  virtual bool cartesianContains(double x, double y) const override {
    return false;
  }

  // Config
  // ---------------------------------------------------------------------------
  void setConfig(const PolarGridConfig &config);
  inline const PolarGridConfig &config() const { return _config; }

  // Helpers
  // ---------------------------------------------------------------------------
  inline std::size_t distanceToNode(double r) const {
    return std::floor((r - _config.distanceMin()) / _config.distanceStep());
  }

  inline std::size_t bearingToNode(double phi) const {
    return std::floor((phi - _config.bearingMin()) / _config.bearingStep());
  }

  inline bool containsDistance(double r) const {
    return _config.containsDistance(r);
  }

  inline bool containsBearing(double phi) const {
    return _config.containsBearing(phi);
  }

private:
  void updateDistanceNodes();
  void updateBearingNodes();
  void updateNodesIndex();
  void bindNodesToPixels();

  // Config
  PolarGridConfig _config;

  // Nodes
  std::vector<double> _distanceNodes{};
  std::vector<double> _bearingNodes{};

  // Nodes indexing
  std::vector<std::vector<std::size_t>> _flatNodesIndex{};
  std::vector<std::array<std::size_t, 3>> _dimNodesIndex{};

  // Map nodes to pixels
  std::vector<std::vector<std::vector<std::size_t>>> _pixelMap;

  // Base Rotation
  const double _cartToPixelDecimals{1e3};
};
