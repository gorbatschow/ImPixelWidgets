#include "PixelMultiPolarGrid.h"

PixelMultiPolarGrid::PixelMultiPolarGrid(
    const std::vector<PolarGridConfig> &configList) {
  setConfig(configList);
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
  _gridList.reserve(configList.size());
  for (const auto &config : configList) {
    _gridList.push_back(std::make_unique<PixelPolarGrid>(config));
  }

  _gridSize = 0;
  for (const auto &grid : _gridList) {
    _gridSize += grid->gridSize();
  }
}
