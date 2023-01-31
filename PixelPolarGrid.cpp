#include "PixelPolarGrid.h"

PixelPolarGrid::PixelPolarGrid(const PolarGridConfig &config) {
  setConfig(config);
}

const std::vector<std::size_t> &PixelPolarGrid::polarToPixel(double r,
                                                             double phi) const {
  std::size_t node_r{}, node_phi{};
  polarToNode(r, phi, node_r, node_phi);
  return nodeToPixel(node_r, node_phi);
}

const std::vector<std::size_t> &
PixelPolarGrid::cartesianToPixel(double x, double y) const {
  double r{}, phi{};
  cartesianToPolar(x, y, r, phi);
  r = roundValue(r, _cartToPixelDecimals);
  phi = roundValue(phi, _cartToPixelDecimals);
  return polarToPixel(r, phi);
}

bool PixelPolarGrid::sectorToPixel(
    double r, double phi_min, double phi_max,
    std::vector<std::vector<std::size_t>> &pixel_list) const {
  if (polarContains(r, phi_min) && polarContains(r, phi_max)) {
    while (phi_min < phi_max) {
      pixel_list.push_back(polarToPixel(r, phi_min));
      phi_min += _config.bearingStep();
    }
    return true;
  }
  return false;
}

void PixelPolarGrid::makeCartesianMesh(std::vector<double> &x,
                                       std::vector<double> &y) const {
  x.reserve(gridSize());
  y.reserve(gridSize());
  double x_k{}, y_k{};
  for (std::size_t i{}; i != _distanceNodes.size(); ++i) {
    for (std::size_t j{}; j != _bearingNodes.size(); ++j) {
      polarToCartesian(_distanceNodes[i], _bearingNodes[j], x_k, y_k);
      x.push_back(x_k);
      y.push_back(y_k);
    }
  }
}

void PixelPolarGrid::makePolarMesh(std::vector<double> &r,
                                   std::vector<double> &phi) const {

  r.reserve(gridSize());
  phi.reserve(gridSize());
  for (const auto &r_k : _distanceNodes) {
    for (const auto &phi_k : _bearingNodes) {
      r.push_back(r_k);
      phi.push_back(phi_k);
    }
  }
}

bool PixelPolarGrid::distanceBounds(double r, double &min, double &max) const {
  if (containsDistance(r)) {
    min = _distanceNodes.at(distanceToNode(r));
    max = min + _config.distanceStep();
    return true;
  }
  return false;
}

bool PixelPolarGrid::bearingBounds(double phi, double &min, double &max) const {
  if (containsBearing(phi)) {
    min = _bearingNodes.at(bearingToNode(phi));
    max = min + _config.bearingStep();
    return true;
  }
  return false;
}

void PixelPolarGrid::setConfig(const PolarGridConfig &config) {
  _config = config;
  updateDistanceNodes();
  updateBearingNodes();
  bindNodesToPixels();
}

void PixelPolarGrid::updateDistanceNodes() {
  _distanceNodes.clear();
  _distanceNodes.reserve(
      std::size_t(_config.distanceMax() / _config.distanceStep()));
  auto r{_config.distanceMin()};
  while (r < _config.distanceMax()) {
    _distanceNodes.push_back(r);
    r += _config.distanceStep();
  }
}

void PixelPolarGrid::updateBearingNodes() {
  _bearingNodes.clear();
  _bearingNodes.reserve(
      std::size_t(_config.bearingMax() / _config.bearingStep()));
  auto phi{_config.bearingMin()};
  while (phi < _config.bearingMax()) {
    _bearingNodes.push_back(phi);
    phi += _config.bearingStep();
  }
}

void PixelPolarGrid::bindNodesToPixels() {
  // Resize
  _pixelMap.clear();
  _pixelMap.resize(_distanceNodes.size());
  for (auto &value : _pixelMap) {
    value.resize(_bearingNodes.size());
  }

  // Fill
  std::size_t node_r{}, node_phi{};
  double r{}, phi{};
  double x{-_config.distanceRange()};
  double y{+_config.distanceRange()};
  const double dy{_config.distanceRange() * 2. / double(_config.pixelHeight())};
  const double dx{_config.distanceRange() * 2. / double(_config.pixelWidth())};

  for (std::size_t i{}, k{}; i != _config.pixelHeight(); ++i) {
    for (std::size_t j{}; j != _config.pixelWidth(); ++j, ++k) {
      cartesianToPolar(x, y, r, phi);
      polarToNode(r, phi, node_r, node_phi);
      x += dx;
      if (_pixelMap.size() <= node_r || r > _config.distanceMax()) {
        continue;
      }
      if (_pixelMap[node_r].size() <= node_phi || phi > _config.bearingMax()) {
        continue;
      }
      _pixelMap[node_r][node_phi].push_back(k);
    }
    x = -_config.distanceRange();
    y -= dy;
  }
}
