#pragma once
#include "IPixelGrid.h"
#include "PolarGridConfig.h"
#include <cassert>
#include <cmath>
#include <vector>

class PixelPolarGrid : public IPixelGrid {
public:
  PixelPolarGrid(const PolarGridConfig &config = PolarGridConfig());
  virtual ~PixelPolarGrid() override = default;

  // Interface
  // ---------------------------------------------------------------------------
  inline const double *xNodes2D() const override { return _xNodes.data(); }
  inline const double *yNodes2D() const override { return _yNodes.data(); }

  inline std::size_t nodeSize() const override {
    return _distanceNodes.size() * _bearingNodes.size();
  }

  virtual const std::vector<std::size_t> &polarToPixel(double r,
                                                       double phi) override {
    std::size_t node_r{}, node_phi{};
    polarToNode(r, phi, node_r, node_phi);
    return nodeToPixel(node_r, node_phi);
  }

  virtual const std::vector<std::size_t> &cartToPixel(double y,
                                                      double x) override {
    double r{}, phi{};
    cartToPolar(y, x, r, phi);
    return polarToPixel(r, phi);
  }

  virtual ImVec2 boundsMin() const override {
    return {-float(_config.distanceMax()), -float(_config.distanceMax())};
  }

  virtual ImVec2 boundsMax() const override {
    return {+float(_config.distanceMax()), +float(_config.distanceMax())};
  }

  // Config
  // ---------------------------------------------------------------------------
  inline void setConfig(const PolarGridConfig &config) {
    _config = config;
    updateGrid();
  }
  inline const PolarGridConfig &config() const { return _config; }

  // Polar Nodes
  // ---------------------------------------------------------------------------
  inline const std::vector<double> &distanceNodes() const {
    return _distanceNodes;
  }

  inline const std::vector<double> &bearingNodes() const {
    return _bearingNodes;
  }

  // Node Pixel Conversion
  // ---------------------------------------------------------------------------
  inline const std::vector<std::size_t> &nodeToPixel(std::size_t node_r,
                                                     std::size_t node_phi) {
    if (_distanceNodes.size() <= node_r) {
      return IPixelGrid::emptyPixel();
    }
    if (_bearingNodes.size() <= node_phi) {
      return IPixelGrid::emptyPixel();
    }
    return _pixelMap.at(node_r).at(node_phi);
  }

  inline const std::vector<std::size_t> &nodeToPixel(std::size_t node_index) {
    const std::size_t node_r{node_index / _bearingNodes.size()};
    const std::size_t node_phi{node_index % _bearingNodes.size()};
    return nodeToPixel(node_r, node_phi);
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

  inline void polarToCart(double r, double phi, double &x, double &y) const {
    x = r * cosd(90. - phi - rotation() + _baseRotation);
    y = r * sind(90. - phi - rotation() + _baseRotation);
  }

  inline void cartToPolar(double y, double x, double &r, double &phi) const {
    r = sqrt(x * x + y * y);
    phi = fmod(90. - atan2d(y, x) + 360. - rotation() + _baseRotation, 360.);
  }

  inline void polarToNode(double r, double phi, std::size_t &node_r,
                          std::size_t &node_phi) const {
    node_r = std::floor((r - _config.distanceMin()) / _config.distanceStep());
    node_phi = std::floor((phi - _config.bearingMin()) / _config.bearingStep());
  }

private:
  void updateGrid();
  void updateDistanceNodes();
  void updateBearingNodes();
  void updateCartesianNodes();
  void bindNodesToPixels();

  // Config
  PolarGridConfig _config;

  // Nodes
  std::vector<double> _distanceNodes{};
  std::vector<double> _bearingNodes{};

  // Cartesian
  std::vector<double> _xNodes;
  std::vector<double> _yNodes;

  // Map nodes to pixels
  std::vector<std::vector<std::vector<std::size_t>>> _pixelMap;

  //
  const double _baseRotation{90.f};
};
