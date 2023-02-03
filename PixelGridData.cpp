#include "PixelGridData.h"

PixelGridData::PixelGridData() {}

PixelGridData::PixelGridData(std::shared_ptr<IPixelGrid> grid) {
  setGrid(grid);
}

void PixelGridData::setGrid(std::shared_ptr<IPixelGrid> grid) {
  _grid.swap(grid);
  _values.resize(_grid->gridSize(), 0.);
}

void PixelGridData::setLinearValues() {}

void PixelGridData::setRandomValues() {}

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
