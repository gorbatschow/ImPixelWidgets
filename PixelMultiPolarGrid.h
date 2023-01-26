#pragma once
#include "IPixelGrid.h"
#include "PixelPolarGrid.h"
#include "PolarGridConfig.h"
#include <memory>
#include <vector>

class PixelMultiPolarGrid : public IPixelGrid {
public:
  // Constructor
  PixelMultiPolarGrid() {}

  // Destructor
  virtual ~PixelMultiPolarGrid() override {}

  // Interface
  // ---------------------------------------------------------------------------
  inline const double *xNodes2D() const override { return _xNodes.data(); }
  inline const double *yNodes2D() const override { return _yNodes.data(); }
  inline std::size_t nodeSize() const override {
    return _xNodes.size() * _yNodes.size();
  }

  virtual const std::vector<std::size_t> &polarToPixel(double r,
                                                       double phi) override {
    return {};
  }

  virtual ImVec2 boundsMin() const override { return {-1000, -1000}; }

  virtual ImVec2 boundsMax() const override { return {+1000, +1000}; }

  // Config
  // ---------------------------------------------------------------------------
  inline void setConfig(const std::vector<PolarGridConfig> &configList) {}

  // inline const PolarGridConfig &config() const { return _config; }

private:
  std::vector<std::unique_ptr<PixelPolarGrid>> _gridList;
  std::vector<double> _xNodes, _yNodes;
};
