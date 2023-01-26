#include "PixelPolarGrid.h"

PixelPolarGrid::PixelPolarGrid(const PolarGridConfig &config)
    : _config(config) {
  updateGrid();
}

void PixelPolarGrid::updateGrid() {
  updateDistanceNodes();
  updateBearingNodes();
  updateCartesianNodes();
  bindNodesToPixels();
}

void PixelPolarGrid::updateDistanceNodes() {
  // assert(_distanceMax > _distanceMin);

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
  // assert(_bearingMax > _bearingMin);

  _bearingNodes.clear();
  _bearingNodes.reserve(
      std::size_t(_config.bearingMax() / _config.bearingStep()));
  auto phi{_config.bearingMin()};
  while (phi <= _config.bearingMax()) {
    _bearingNodes.push_back(phi);
    phi += _config.bearingStep();
  }
}

void PixelPolarGrid::updateCartesianNodes() {
  _xNodes.clear();
  _yNodes.clear();
  _xNodes.resize(_distanceNodes.size() * _bearingNodes.size());
  _yNodes.resize(_distanceNodes.size() * _bearingNodes.size());
  for (std::size_t i{}, k{}; i != _distanceNodes.size(); ++i) {
    for (std::size_t j{}; j != _bearingNodes.size(); ++j, ++k) {
      polarToCart(_distanceNodes[i], _bearingNodes[j], _xNodes[k], _yNodes[k]);
    }
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
      cartToPolar(y, x, r, phi);
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
