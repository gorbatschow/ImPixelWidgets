#include "PixelGridData.h"
#include <numeric>
#include <random>

PixelGridData::PixelGridData() {}

PixelGridData::PixelGridData(std::shared_ptr<IPixelGrid> grid) {
  setGrid(grid);
}

void PixelGridData::setGrid(std::shared_ptr<IPixelGrid> grid) {
  _grid.swap(grid);
  _values.resize(_grid->gridSize(), 0.);
}

void PixelGridData::setLinearValues() {
  std::iota(_values.begin(), _values.end(), 0);
}

void PixelGridData::setRandomValues() {
  std::random_device rnd_device;
  std::mt19937 rnd_engine{rnd_device()};
  std::uniform_int_distribution<int> rnd_dist{0, int(_values.size())};

  const auto gen{[&rnd_dist, &rnd_engine]() { return rnd_dist(rnd_engine); }};
  std::generate(_values.begin(), _values.end(), gen);
}

void PixelGridData::setPolarValues(const double *r, const double *phi,
                                   const double *val, std::size_t size) {

  std::size_t index{};
  for (std::size_t i{}; i != size; ++i) {
    _grid->polarToIndex(r[i], phi[i], index);
    _values[index] = val[i];
  }
}

void PixelGridData::setCartesianValues(const double *x, const double *y,
                                       const double *val, std::size_t size) {
  std::size_t index{};
  for (std::size_t i{}; i != size; ++i) {
    _grid->cartesianToIndex(x[i], y[i], index);
    _values[index] = val[i];
  }
}
