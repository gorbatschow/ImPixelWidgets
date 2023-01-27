#pragma once
#include <cstddef>

class PixelGridConfig {

public:
  // Width
  inline void setPixelWidth(std::size_t w) { _pixelWidth = w; }
  inline std::size_t pixelWidth() const { return _pixelWidth; }

  // Height
  inline void setPixelHeight(std::size_t h) { _pixelHeight = h; }
  inline std::size_t pixelHeight() const { return _pixelHeight; }

  //
  inline std::size_t pixelSize() const { return _pixelWidth * _pixelHeight; }

  // Rotation
  inline void setRotation(double rot) { _rotation = rot; }
  inline double rotation() const { return _rotation; }

private:
  double _rotation{};
  std::size_t _pixelWidth{512};
  std::size_t _pixelHeight{512};
};
