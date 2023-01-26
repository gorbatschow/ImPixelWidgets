#include "PixelPolarGrid.h"

PixelPolarGrid::PixelPolarGrid(const PolarGridConfig &config)
    : _config(config) {}

void PixelPolarGrid::makeCartesianMesh(std::vector<double> &x,
                                       std::vector<double> &y) const {
  x.resize(gridSize());
  y.resize(gridSize());
  for (std::size_t i{}, k{}; i != _distanceNodes.size(); ++i) {
    for (std::size_t j{}; j != _bearingNodes.size(); ++j, ++k) {
      polarToCartesian(_distanceNodes[i], _bearingNodes[j], x[k], y[k]);
    }
  }
}

void PixelPolarGrid::makePolarMesh(std::vector<double> &r,
                                   std::vector<double> &phi) const {

  r.resize(gridSize());
  phi.resize(gridSize());
  std::size_t k{};
  for (const auto &r_k : _distanceNodes) {
    for (const auto &phi_k : _bearingNodes) {
      r[k] = r_k;
      phi[k] = phi_k;
      ++k;
    }
  }
}

void PixelPolarGrid::updateDistanceNodes() {
  _distanceNodes.clear();
  _distanceNodes.reserve(
      std::size_t(_config.distanceMax() / _config.distanceStep()));
  auto r{_config.distanceMin()};
  while (r <= _config.distanceMax()) {
    _distanceNodes.push_back(r);
    r += _config.distanceStep();
  }
}

void PixelPolarGrid::updateBearingNodes() {
  _bearingNodes.clear();
  _bearingNodes.reserve(
      std::size_t(_config.bearingMax() / _config.bearingStep()));
  auto phi{_config.bearingMin()};
  while (phi <= _config.bearingMax()) {
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
  double x{-_config.distanceMax()};
  double y{+_config.distanceMax()};
  const double dy{_config.distanceMax() * 2. /
                  double(IPixelGrid::pixelHeight())};
  const double dx{_config.distanceMax() * 2. /
                  double(IPixelGrid::pixelWidth())};

  for (std::size_t i{}, k{}; i != IPixelGrid::pixelHeight(); ++i) {
    for (std::size_t j{}; j != IPixelGrid::pixelWidth(); ++j, ++k) {
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
    x = -_config.distanceMax();
    y -= dy;
  }
}
