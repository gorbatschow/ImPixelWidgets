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

  // Interface
  // ---------------------------------------------------------------------------
  // Linear Node To Pixel
  virtual const std::vector<std::size_t> &
  nodeToPixel(std::size_t dim_0) const override;

  // Node To Pixel
  virtual const std::vector<std::size_t> &
  nodeToPixel(std::size_t dim_1, std::size_t dim_2) const override;

  // Polar To Pixel
  virtual const std::vector<std::size_t> &
  polarToPixel(double r, double phi) const override;

  // Polar To Linear Node
  virtual void polarToNode(double r, double phi,
                           std::size_t &dim_0) const override;

  // Polar To Node
  virtual void polarToNode(double r, double phi, std::size_t &dim_1,
                           std::size_t &dim_2) const override;

  // Cartesian To Pixel
  virtual const std::vector<std::size_t> &
  cartesianToPixel(double x, double y) const override;

  // Sector To Pixel
  virtual bool sectorToPixel(
      double r, double phi_min, double phi_max,
      std::vector<std::vector<std::size_t>> &pixel_list) const override;

  // Cartesian Bounds Min
  virtual ImVec2 cartesianBoundsMin() const override;

  // Cartesian Bounds Max
  virtual ImVec2 cartesianBoundsMax() const override;

  // Make Cartesian Mesh
  virtual void makeCartesianMesh(std::vector<double> &x,
                                 std::vector<double> &y) const override;

  // Make Polar Mesh
  virtual void makePolarMesh(std::vector<double> &r,
                             std::vector<double> &phi) const override;

  // Grid Size
  virtual std::size_t gridSize(std::size_t dim = 0) const override;

  // Polar Contains
  virtual bool polarContains(double r, double phi) const override;

  // Cartesian Contains
  virtual bool cartesianContains(double x, double y) const override {
    return false;
  }

  // Pixel Size
  virtual std::size_t pixelWidth() const override;
  virtual std::size_t pixelHeight() const override;

  // Distance Bounds
  virtual bool distanceBounds(double r, double &min,
                              double &max) const override;

  // Bearing Bounds
  virtual bool bearingBounds(double phi, double &min,
                             double &max) const override;

  // Config
  // ---------------------------------------------------------------------------
  void setConfig(const PolarGridConfig &config);
  inline const PolarGridConfig &config() const { return _config; }

  // Polar Nodes
  // ---------------------------------------------------------------------------
  inline const std::vector<double> &
  distanceNodes(double distance = 0) const override {
    return _distanceNodes;
  }

  inline const std::vector<double> &
  bearingNodes(double distnace = 0) const override {
    return _bearingNodes;
  }

  // Helpers
  // ---------------------------------------------------------------------------
  inline double sind(double v) const {
    return sin(fmod(v, 360.) * M_PI / 180.);
  }

  inline double cosd(double v) const {
    return cos(fmod(v, 360.) * M_PI / 180.);
  }

  inline double atan2d(double y, double x) const {
    return atan2(y, x) * 180. / M_PI;
  }

  inline void polarToCartesian(double r, double phi, double &x,
                               double &y) const {
    x = r * cosd(90. - phi - _config.rotation() + _baseRotation);
    y = r * sind(90. - phi - _config.rotation() + _baseRotation);
  }

  inline void cartesianToPolar(double x, double y, double &r,
                               double &phi) const {
    r = sqrt(x * x + y * y);
    phi = fmod(90. - atan2d(y, x) + 360. - _config.rotation() + _baseRotation,
               360.);
  }

  inline std::size_t distanceToNode(double r) const {
    return std::floor((r - _config.distanceMin()) / _config.distanceStep());
  }

  inline std::size_t bearingToNode(double phi) const {
    return std::floor((phi - _config.bearingMin()) / _config.bearingStep());
  }

  inline double roundValue(double value, double decimals) const {
    return std::ceil(value * decimals) / decimals;
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
  std::vector<std::vector<std::size_t>> _linearNodesIndex{};
  std::vector<std::array<std::size_t, 3>> _dimNodesIndex{};

  // Map nodes to pixels
  std::vector<std::vector<std::vector<std::size_t>>> _pixelMap;

  // Base Rotation
  const double _baseRotation{90.f};
  const double _cartToPixelDecimals{1e3};
};
