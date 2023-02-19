#include "ImPixelMultiPolarGrid.h"

namespace ImPixel {
MultiPolarGrid::MultiPolarGrid(const std::vector<PolarGridConfig> &configList) {
  setConfig(configList);
}

const std::vector<std::size_t> &
MultiPolarGrid::indexToPixel(std::size_t index) const {
  // TODO
  if (index < _pixelIndex.size()) {
    return (*_pixelIndex[index]);
  }

  return AnyGrid::emptyPixel();
}

std::size_t MultiPolarGrid::gridSize(std::size_t dim) const {
  return _pixelIndex.size();
}

const std::vector<std::size_t> &MultiPolarGrid::polarToPixel(double r,
                                                             double phi) const {
  for (const auto &grid : _gridList) {
    if (grid->polarContains(r, phi)) {
      return grid->polarToPixel(r, phi);
    }
  }
  return AnyGrid::emptyPixel();
}

const std::vector<std::size_t> &
MultiPolarGrid::cartesianToPixel(double x, double y) const {
  for (const auto &grid : _gridList) {
    if (grid->cartesianContains(x, y)) {
      return grid->cartesianToPixel(x, y);
    }
  }
  return AnyGrid::emptyPixel();
}

ImVec2 MultiPolarGrid::cartesianBoundsMin() const {
  return {float(-distanceRange()), float(-distanceRange())};
}

ImVec2 MultiPolarGrid::cartesianBoundsMax() const {
  return {float(+distanceRange()), float(+distanceRange())};
}

std::size_t MultiPolarGrid::pixelWidth() const {
  if (_gridList.empty()) {
    return 0;
  }
  return _gridList.front()->config().pixelWidth();
}

std::size_t MultiPolarGrid::pixelHeight() const {
  if (_gridList.empty()) {
    return 0;
  }
  return _gridList.front()->config().pixelHeight();
}

bool MultiPolarGrid::sectorToPixel(
    std::vector<std::vector<std::size_t>> &pixel_list, double r, double phi_min,
    double phi_max) const {

  for (const auto &grid : _gridList) {
    if (grid->sectorToPixel(pixel_list, r, phi_min, phi_max)) {
      return true;
    }
  }
  return false;
}

bool MultiPolarGrid::polarToIndex(std::size_t &index, double r,
                                  double phi) const {
  bool ok{};
  for (std::size_t i{}; const auto &grid : _gridList) {
    if (grid->polarContains(r, phi)) {
      ok = grid->polarToIndex(index, r, phi);
      index += i;
      return ok;
    }
    i += grid->gridSize();
  }
  return ok;
}

void MultiPolarGrid::makeCartesianMesh(std::vector<double> &x,
                                       std::vector<double> &y) const {
  for (const auto &grid : _gridList) {
    grid->makeCartesianMesh(x, y);
  }
}

void MultiPolarGrid::makePolarMesh(std::vector<double> &r,
                                   std::vector<double> &phi) const {
  for (const auto &grid : _gridList) {
    grid->makePolarMesh(r, phi);
  }
}

bool MultiPolarGrid::polarContains(double r, double phi) const {
  for (const auto &grid : _gridList) {
    if (grid->polarContains(r, phi)) {
      return true;
    }
  }
  return false;
}

bool MultiPolarGrid::cartesianContains(double x, double y) const {
  for (const auto &grid : _gridList) {
    if (grid->cartesianContains(x, y)) {
      return true;
    }
  }
  return false;
}

bool MultiPolarGrid::distanceBounds(double &min, double &max, double r) const {
  for (const auto &grid : _gridList) {
    if (grid->distanceBounds(r, min, max)) {
      return true;
    }
  }
  return false;
}

bool MultiPolarGrid::bearingBounds(double &min, double &max, double phi) const {
  for (const auto &grid : _gridList) {
    if (grid->bearingBounds(phi, min, max)) {
      return true;
    }
  }
  return false;
}

const std::vector<double> &MultiPolarGrid::distanceNodes(double bearing) const {
  for (const auto &grid : _gridList) {
    if (grid->containsBearing(bearing)) {
      return grid->distanceNodes();
    }
  }
  return AnyGrid::emptyNodes();
}

const std::vector<double> &MultiPolarGrid::bearingNodes(double distance) const {
  for (const auto &grid : _gridList) {
    if (grid->containsDistance(distance)) {
      return grid->bearingNodes();
    }
  }
  return AnyGrid::emptyNodes();
}

void MultiPolarGrid::setConfig(const std::vector<PolarGridConfig> &configList) {
  _gridList.clear();
  _pixelIndex.clear();
  if (configList.empty()) {
    return;
  }

  _gridList.reserve(configList.size());
  for (const auto &config : configList) {
    _gridList.push_back(std::make_unique<PolarGrid>(config));
  }

  _pixelIndex.reserve(_gridList.size() * _gridList.front()->gridSize());
  for (std::size_t i{}; const auto &grid : _gridList) {
    for (std::size_t j{}; j != grid->gridSize(); ++j, ++i) {
      _pixelIndex.push_back(&grid->indexToPixel(j));
    }
  }
}
} // namespace ImPixel
