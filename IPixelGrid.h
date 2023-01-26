#pragma once
#include "imgui.h"
#include <imgui.h>
#include <vector>

class IPixelGrid {
public:
  virtual ~IPixelGrid() = default;

  virtual const std::vector<std::size_t> &polarToPixel(double r,
                                                       double phi) = 0;

  virtual const std::vector<std::size_t> &cartToPixel(double x, double y) = 0;

  virtual const double *xNodes2D() const = 0;
  virtual const double *yNodes2D() const = 0;
  virtual std::size_t nodeSize() const = 0;

  virtual ImVec2 boundsMin() const = 0;
  virtual ImVec2 boundsMax() const = 0;

  // Pixel Size
  // ---------------------------------------------------------------------------
  inline void setPixelWidth(std::size_t w) { _pixelWidth = w; }
  inline double pixelWidth() const { return _pixelWidth; }

  inline void setPixelHeight(std::size_t h) { _pixelHeight = h; }
  inline double pixelHeight() const { return _pixelHeight; }

  inline std::size_t pixelSize() const { return _pixelWidth * _pixelHeight; }

  // Rotation
  // ---------------------------------------------------------------------------
  inline void setRotation(double rot) { _rotation = rot; }
  inline double rotation() const { return _rotation; }

protected:
  inline const std::vector<std::size_t> &emptyPixel() const {
    return _emptyPixel;
  }

private:
  const std::vector<std::size_t> _emptyPixel{};
  std::size_t _pixelWidth{512};
  std::size_t _pixelHeight{512};
  double _rotation{};
};
