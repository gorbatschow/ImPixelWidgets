#include "PixelMultiPolarGrid.h"

PixelMultiPolarGrid::PixelMultiPolarGrid(
    const std::vector<PolarGridConfig> &configList) {
  setConfig(configList);
}

const std::vector<std::size_t> &PixelMultiPolarGrid::polarToPixel(double r,
                                                                  double phi) {
  for (const auto &grid : _gridList) {
    if (grid->polarContains(r, phi)) {
      return grid->polarToPixel(r, phi);
    }
  }
  return IPixelGrid::emptyPixel();
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

void PixelMultiPolarGrid::setConfig(
    const std::vector<PolarGridConfig> &configList) {
  _gridList.clear();
  _gridList.reserve(configList.size());
  for (const auto &config : configList) {
    _gridList.push_back(std::make_unique<PixelPolarGrid>(config));
  }

  _distance = 0;
  _gridSize = 0;
  for (const auto &grid : _gridList) {
    _distance = std::max(_distance, grid->config().distanceMax());
    _gridSize += grid->gridSize();
  }
}
