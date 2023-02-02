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

    std::size_t dim_0{};
    for (std::size_t i{}; i != size; ++i) {
      _grid->polarToNode(r[i], phi[i], dim_0);
      _values[dim_0] = val[i];
    }
  }

  // Set Cartesian Values
  void setCartesianValues(const double *x, const double *y, const double *val,
                          std::size_t size) {
    std::size_t dim_0{};
    for (std::size_t i{}; i != size; ++i) {
      _grid->cartesianToNode(x[i], y[i], dim_0);
      _values[dim_0] = val[i];
    }
  }

  // Get Size
  inline const std::size_t size() const { return _values.size(); }

  // Get Value
  inline const double value(std::size_t dim_0) const { return _values[dim_0]; }

  // Get Pixel
  inline const std::vector<std::size_t> &pixel(std::size_t dim_0) const {
    return _grid->nodeToPixel(dim_0);
  }

  // Get Grid
  const IPixelGrid &grid() const { return (*_grid); }

private:
  std::shared_ptr<IPixelGrid> _grid{};
  std::vector<double> _values{};
};
