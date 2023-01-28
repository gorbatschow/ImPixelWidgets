#include "PixelPolarGrid.h"

PixelPolarGrid::PixelPolarGrid(const PolarGridConfig &config) {
  setConfig(config);
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
