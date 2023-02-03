#pragma once
#include "IPixelGrid.h"
#include <memory>
#include <vector>

class PixelGridData {
public:
  // Constructor
  PixelGridData() {}

  PixelGridData(std::shared_ptr<IPixelGrid> grid) { setGrid(grid); }

  // Destructor
  ~PixelGridData() = default;

  // Set Grid
  void setGrid(std::shared_ptr<IPixelGrid> grid) {
    _grid.swap(grid);
    _values.resize(_grid->gridSize(), 0.);
  }

  // Set Polar Values
  void setPolarValues(const double *r, const double *phi, const double *val,
                      std::size_t size) {

    std::size_t index{};
    for (std::size_t i{}; i != size; ++i) {
      _grid->polarToIndex(r[i], phi[i], index);
      _values[index] = val[i];
    }
  }

  // Set Cartesian Values
  void setCartesianValues(const double *x, const double *y, const double *val,
                          std::size_t size) {
    std::size_t index{};
    for (std::size_t i{}; i != size; ++i) {
      _grid->cartesianToIndex(x[i], y[i], index);
      _values[index] = val[i];
    }
  }

  // Get Size
  inline const std::size_t size() const { return _values.size(); }

  // Get Value
  inline const double value(std::size_t index) const { return _values[index]; }

  // Get Pixel
  inline const std::vector<std::size_t> &pixel(std::size_t index) const {
    return _grid->indexToPixel(index);
  }

  // Get Grid
  const IPixelGrid &grid() const { return (*_grid); }

private:
  std::shared_ptr<IPixelGrid> _grid{};
  std::vector<double> _values{};
};
