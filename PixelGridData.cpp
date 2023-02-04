#include "PixelGridData.h"
#include <numeric>
#include <random>

PixelGridData::PixelGridData() {}

PixelGridData::PixelGridData(std::shared_ptr<IPixelGrid> grid) {
  setGrid(grid);
}

void PixelGridData::setGrid(std::shared_ptr<IPixelGrid> grid) {
  checkGridSize();
  _grid.swap(grid);
}

void PixelGridData::setLinearValues() {
  checkGridSize();
  std::iota(_values.begin(), _values.end(), 0);
}

void PixelGridData::setRandomValues() {
  checkGridSize();

  std::random_device rnd_device;
  std::mt19937 rnd_engine{rnd_device()};
  std::uniform_int_distribution<int> rnd_dist{0, int(_values.size())};

  const auto gen{[&rnd_dist, &rnd_engine]() { return rnd_dist(rnd_engine); }};
  std::generate(_values.begin(), _values.end(), gen);
}

void PixelGridData::checkGridSize() {
  if (_grid && _values.size() != _grid->gridSize()) {
    _values.resize(_grid->gridSize(), 0.);
  }
}
