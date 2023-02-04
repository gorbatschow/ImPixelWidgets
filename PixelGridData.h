#pragma once
#include "IPixelGrid.h"
#include <functional>
#include <memory>
#include <numeric>
#include <random>
#include <vector>

class PixelGridData {
public:
  using TransformFunc =
      std::function<double(const double &curr, const double &prev)>;

  static inline const TransformFunc DefaultTransform{
      [](const double &curr, const double &) { return curr; }};

  // Constructor
  PixelGridData() = default;

  // Constructor
  PixelGridData(std::shared_ptr<IPixelGrid> grid) { setGrid(grid); }

  // Destructor
  ~PixelGridData() = default;

  // Set Grid
  inline void setGrid(std::shared_ptr<IPixelGrid> grid) {
    _grid.swap(grid);
    checkGridSize();
  }

  // Get Grid
  inline const IPixelGrid &grid() const { return (*_grid); }

  // Set Transform
  inline void setTransform(const TransformFunc &func) { _transform = func; }
  void resetTransform() { _transform = DefaultTransform; }

  // Set Zero Values
  inline void setZeroValues() {
    checkGridSize();
    std::fill(_values.begin(), _values.end(), 0.);
  }

  // Set Linear Values
  inline void setLinearValues() {
    checkGridSize();
    std::iota(_values.begin(), _values.end(), 0);
  }

  // Set Random Vales
  inline void setRandomValues() {
    checkGridSize();
    std::random_device rnd_device;
    std::mt19937 rnd_engine{rnd_device()};
    std::uniform_int_distribution<int> rnd_dist{0, int(_values.size())};
    const auto gen{[&rnd_dist, &rnd_engine]() { return rnd_dist(rnd_engine); }};
    std::generate(_values.begin(), _values.end(), gen);
  }

  // Set Coordinate Values
  template <CS::System T_cs, typename T_val, typename T_dim>
  inline void setCoordinateValues(const std::vector<T_val> &val,
                                  const std::vector<T_dim> &dim_1,
                                  const std::vector<T_dim> &dim_2 = {}) {
    setCoordinateValues<T_cs, T_val, T_dim>(val.data(), val.size(),
                                            dim_1.data(), dim_2.data());
  }

  // Set Coordinate Values
  template <CS::System T_cs, typename T_val, typename T_dim>
  inline void setCoordinateValues(const T_val *val, std::size_t size,
                                  const T_dim *dim_1,
                                  const T_dim *dim_2 = nullptr) {
    checkGridSize();
    for (std::size_t index{}, i{}; i != size; ++i) {
      if constexpr (T_cs == CS::System::Index) {
        _grid->toIndex<T_cs, T_dim>(index, dim_1[i]);
      } else {
        _grid->toIndex<T_cs, T_dim>(index, dim_1[i], dim_2[i]);
      }
      _values[index] = _transform(val[i], _values[index]);
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

private:
  std::shared_ptr<IPixelGrid> _grid{};
  std::vector<double> _values{};
  TransformFunc _transform{DefaultTransform};

  inline void checkGridSize() {
    if (_grid && _values.size() != _grid->gridSize()) {
      _values.resize(_grid->gridSize(), 0.);
    }
  }
};
