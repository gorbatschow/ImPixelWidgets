#include "../include/ImPixelPolarGrid.h"
#include "../include/ImPixelCoordinateSystem.h"

namespace ImPixel {
PolarGrid::PolarGrid(const PolarGridConfig &config) { setConfig(config); }

// Index
// -----------------------------------------------------------------------------
const std::vector<std::size_t> &
PolarGrid::indexToPixel(std::size_t index) const {
  return nodeToPixel(_dimNodesIndex[index][1], _dimNodesIndex[index][2]);
}

bool PolarGrid::indexToNode(std::size_t &dim_1, std::size_t &dim_2,
                            std::size_t index) const {
  if (_dimNodesIndex.size() <= index) {
    return false;
  }
  dim_1 = _dimNodesIndex[index][1];
  dim_2 = _dimNodesIndex[index][2];
  return true;
}

// Node
//------------------------------------------------------------------------------
const std::vector<std::size_t> &
PolarGrid::nodeToPixel(std::size_t node_r, std::size_t node_phi) const {
  if (_distanceNodes.size() <= node_r) {
    return AnyGrid::emptyPixel();
  }
  if (_bearingNodes.size() <= node_phi) {
    return AnyGrid::emptyPixel();
  }
  return _pixelMap.at(node_r).at(node_phi);
}

bool PolarGrid::nodeToIndex(std::size_t &index, std::size_t dim_1,
                            std::size_t dim_2) const {
  if (_distanceNodes.size() <= dim_1 || _bearingNodes.size() <= dim_2) {
    return false;
  }
  index = _flatNodesIndex[dim_1][dim_2];
  return true;
}

// Pixel
//------------------------------------------------------------------------------
std::size_t PolarGrid::pixelWidth() const { return _config.pixelWidth(); }

std::size_t PolarGrid::pixelHeight() const { return _config.pixelHeight(); }

// Polar
//------------------------------------------------------------------------------
const std::vector<std::size_t> &PolarGrid::polarToPixel(double r,
                                                        double phi) const {
  std::size_t node_r{}, node_phi{};
  polarToNode(node_r, node_phi, r, phi);
  return nodeToPixel(node_r, node_phi);
}

bool PolarGrid::sectorToPixel(std::vector<std::vector<std::size_t>> &pixel_list,
                              double r, double phi_min, double phi_max) const {
  if (polarContains(r, phi_min)) {
    phi_max = std::min(phi_max, _config.bearingMax());
    while (phi_min < phi_max) {
      const auto &pixel{polarToPixel(r, phi_min)};
      if (!pixel.empty()) {
        pixel_list.push_back(pixel);
      }
      phi_min += _config.bearingStep();
    }
    return true;
  }
  return false;
}

bool PolarGrid::polarToIndex(std::size_t &index, double r, double phi) const {
  return nodeToIndex(index, distanceToNode(r), bearingToNode(phi));
}

bool PolarGrid::polarToNode(std::size_t &dim_1, std::size_t &dim_2, double r,
                            double phi) const {
  dim_1 = distanceToNode(r);
  dim_2 = bearingToNode(phi);
  return dim_1 < _distanceNodes.size() && dim_2 < _bearingNodes.size();
}

bool PolarGrid::distanceBounds(double &min, double &max, double r) const {
  if (containsDistance(r)) {
    min = _distanceNodes.at(distanceToNode(r));
    max = std::min(min + _config.distanceStep(), _config.distanceMax());
    return true;
  }
  return false;
}

bool PolarGrid::bearingBounds(double &min, double &max, double phi) const {
  if (containsBearing(phi)) {
    min = _bearingNodes.at(bearingToNode(phi));
    max = std::min(min + _config.bearingStep(), _config.bearingMax());
    return true;
  }
  return false;
}

const std::vector<double> &PolarGrid::distanceNodes(double distance) const {
  return _distanceNodes;
}

const std::vector<double> &PolarGrid::bearingNodes(double distnace) const {
  return _bearingNodes;
}

bool PolarGrid::polarContains(double r, double phi) const {
  return _config.containsDistance(r) && _config.containsBearing(phi);
}

void PolarGrid::makePolarMesh(std::vector<double> &r,
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

// Cartesian
//----------------------------------------------------------------------------
const std::vector<std::size_t> &PolarGrid::cartesianToPixel(double x,
                                                            double y) const {
  double r{}, phi{};
  CoordinateSystem::cartesianToPolar(r, phi, x, y, _config.rotation());
  r = CoordinateSystem::round(r, _cartToPixelDecimals);
  phi = CoordinateSystem::round(phi, _cartToPixelDecimals);
  return polarToPixel(r, phi);
}

ImVec2 PolarGrid::cartesianBoundsMin() const {
  return {float(-_config.distanceRange()), float(-_config.distanceRange())};
}

ImVec2 PolarGrid::cartesianBoundsMax() const {
  return {float(+_config.distanceRange()), float(+_config.distanceRange())};
}

void PolarGrid::makeCartesianMesh(std::vector<double> &x,
                                  std::vector<double> &y) const {
  x.reserve(gridSize());
  y.reserve(gridSize());
  double x_k{}, y_k{};
  for (std::size_t i{}; i != _distanceNodes.size(); ++i) {
    for (std::size_t j{}; j != _bearingNodes.size(); ++j) {
      CoordinateSystem::polarToCartesian(x_k, y_k, _distanceNodes[i],
                                         _bearingNodes[j], _config.rotation());
      x.push_back(x_k);
      y.push_back(y_k);
    }
  }
}

std::size_t PolarGrid::gridSize(std::size_t dim) const {
  if (dim == 1) {
    return _distanceNodes.size();
  } else if (dim == 2) {
    return _bearingNodes.size();
  }
  return _distanceNodes.size() * _bearingNodes.size();
}

// Config
//----------------------------------------------------------------------------
void PolarGrid::setConfig(const PolarGridConfig &config) {
  _config = config;
  updateDistanceNodes();
  updateBearingNodes();
  updateNodesIndex();
  bindNodesToPixels();
}

//
// ---------------------------------------------------------------------------

void PolarGrid::updateDistanceNodes() {
  _distanceNodes.clear();
  _distanceNodes.reserve(
      std::size_t(_config.distanceMax() / _config.distanceStep()));
  auto r{_config.distanceMin()};
  while (r < _config.distanceMax()) {
    _distanceNodes.push_back(r);
    r += _config.distanceStep();
  }
  _distanceNodes.push_back(r);
}

void PolarGrid::updateBearingNodes() {
  _bearingNodes.clear();
  _bearingNodes.reserve(
      std::size_t(_config.bearingMax() / _config.bearingStep()));
  auto phi{_config.bearingMin()};
  while (phi < _config.bearingMax()) {
    _bearingNodes.push_back(phi);
    phi += _config.bearingStep();
  }
  _bearingNodes.push_back(phi);
}

void PolarGrid::updateNodesIndex() {
  _flatNodesIndex.resize(_distanceNodes.size());
  _dimNodesIndex.resize(_distanceNodes.size() * _bearingNodes.size());
  for (std::size_t dim_0{}, dim_1{}; dim_1 != _distanceNodes.size(); ++dim_1) {
    _flatNodesIndex[dim_1].resize(_bearingNodes.size());
    for (std::size_t dim_2{}; dim_2 != _bearingNodes.size(); ++dim_2, ++dim_0) {
      _flatNodesIndex[dim_1][dim_2] = dim_0;
      _dimNodesIndex[dim_0] = {dim_0, dim_1, dim_2};
    }
  }
}

void PolarGrid::bindNodesToPixels() {
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
      CoordinateSystem::cartesianToPolar(r, phi, x, y, _config.rotation());
      PolarGrid::polarToNode(node_r, node_phi, r, phi);
      x += dx;
      if (_pixelMap.size() <= node_r || r >= _config.distanceMax()) {
        continue;
      }
      if (_pixelMap[node_r].size() <= node_phi || phi >= _config.bearingMax()) {
        continue;
      }
      _pixelMap[node_r][node_phi].push_back(k);
    }
    x = -_config.distanceRange();
    y -= dy;
  }
}
} // namespace ImPixel
