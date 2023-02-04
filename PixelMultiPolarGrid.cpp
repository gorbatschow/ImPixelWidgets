#include "PixelMultiPolarGrid.h"

PixelMultiPolarGrid::PixelMultiPolarGrid(
    const std::vector<PolarGridConfig> &configList) {
  setConfig(configList);
}

const std::vector<std::size_t> &
PixelMultiPolarGrid::indexToPixel(std::size_t index) const {
  // TODO
  if (index < _pixelIndex.size()) {
    return (*_pixelIndex[index]);
  }

  return IPixelGrid::emptyPixel();
}

std::size_t PixelMultiPolarGrid::gridSize(std::size_t dim) const {
  return _pixelIndex.size();
}

const std::vector<std::size_t> &
PixelMultiPolarGrid::polarToPixel(double r, double phi) const {
  for (const auto &grid : _gridList) {
    if (grid->polarContains(r, phi)) {
      return grid->polarToPixel(r, phi);
    }
  }
  return IPixelGrid::emptyPixel();
}

const std::vector<std::size_t> &
PixelMultiPolarGrid::cartesianToPixel(double x, double y) const {
  for (const auto &grid : _gridList) {
    if (grid->cartesianContains(x, y)) {
      return grid->cartesianToPixel(x, y);
    }
  }
  return IPixelGrid::emptyPixel();
}

ImVec2 PixelMultiPolarGrid::cartesianBoundsMin() const {
  return {float(-distanceRange()), float(-distanceRange())};
}

ImVec2 PixelMultiPolarGrid::cartesianBoundsMax() const {
  return {float(+distanceRange()), float(+distanceRange())};
}

std::size_t PixelMultiPolarGrid::pixelWidth() const {
  if (_gridList.empty()) {
    return 0;
  }
  return _gridList.front()->config().pixelWidth();
}

std::size_t PixelMultiPolarGrid::pixelHeight() const {
  if (_gridList.empty()) {
    return 0;
  }
  return _gridList.front()->config().pixelHeight();
}

bool PixelMultiPolarGrid::sectorToPixel(
    double r, double phi_min, double phi_max,
    std::vector<std::vector<std::size_t>> &pixel_list) const {

  for (const auto &grid : _gridList) {
    if (grid->sectorToPixel(r, phi_min, phi_max, pixel_list)) {
      return true;
    }
  }
  return false;
}

void PixelMultiPolarGrid::polarToIndex(double r, double phi,
                                       std::size_t &index) const {
  for (std::size_t i{}; const auto &grid : _gridList) {
    if (grid->polarContains(r, phi)) {
      grid->polarToIndex(r, phi, index);
      index += i;
      return;
    }
    i += grid->gridSize();
  }
}

void PixelMultiPolarGrid::makeCartesianMesh(std::vector<double> &x,
                                            std::vector<double> &y) const {
  for (const auto &grid : _gridList) {
    grid->makeCartesianMesh(x, y);
  }
}

void PixelMultiPolarGrid::makePolarMesh(std::vector<double> &r,
                                        std::vector<double> &phi) const {
  for (const auto &grid : _gridList) {
    grid->makePolarMesh(r, phi);
  }
}

bool PixelMultiPolarGrid::polarContains(double r, double phi) const {
  for (const auto &grid : _gridList) {
    if (grid->polarContains(r, phi)) {
      return true;
    }
  }
  return false;
}

bool PixelMultiPolarGrid::cartesianContains(double x, double y) const {
  for (const auto &grid : _gridList) {
    if (grid->cartesianContains(x, y)) {
      return true;
    }
  }
  return false;
}

bool PixelMultiPolarGrid::distanceBounds(double r, double &min,
                                         double &max) const {
  for (const auto &grid : _gridList) {
    if (grid->distanceBounds(r, min, max)) {
      return true;
    }
  }
  return false;
}

bool PixelMultiPolarGrid::bearingBounds(double phi, double &min,
                                        double &max) const {
  for (const auto &grid : _gridList) {
    if (grid->bearingBounds(phi, min, max)) {
      return true;
    }
  }
  return false;
}

const std::vector<double> &
PixelMultiPolarGrid::distanceNodes(double bearing) const {
  for (const auto &grid : _gridList) {
    if (grid->containsBearing(bearing)) {
      return grid->distanceNodes();
    }
  }
  return IPixelGrid::emptyNodes();
}

const std::vector<double> &
PixelMultiPolarGrid::bearingNodes(double distance) const {
  for (const auto &grid : _gridList) {
    if (grid->containsDistance(distance)) {
      return grid->bearingNodes();
    }
  }
  return IPixelGrid::emptyNodes();
}

void PixelMultiPolarGrid::setConfig(
    const std::vector<PolarGridConfig> &configList) {
  _gridList.clear();
  _pixelIndex.clear();
  if (configList.empty()) {
    return;
  }

  _gridList.reserve(configList.size());
  for (const auto &config : configList) {
    _gridList.push_back(std::make_unique<PixelPolarGrid>(config));
  }

  _pixelIndex.reserve(_gridList.size() * _gridList.front()->gridSize());
  for (std::size_t i{}; const auto &grid : _gridList) {
    for (std::size_t j{}; j != grid->gridSize(); ++j, ++i) {
      _pixelIndex.push_back(&grid->indexToPixel(j));
    }
  }
}
