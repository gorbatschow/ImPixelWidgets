#pragma once
#include "PixelGridConfig.h"
#include <cstddef>

class PolarGridConfig : public PixelGridConfig {
public:
  PolarGridConfig() = default;
  ~PolarGridConfig() = default;

  // Distance
  // ---------------------------------------------------------------------------
  inline void setDistanceMin(double min) { _distanceMin = min; }
  double distanceMin() const { return _distanceMin; }

  inline void setDistanceMax(double max) { _distanceMax = max; }
  double distanceMax() const { return _distanceMax; }

  inline void setDistanceStep(double step) { _distanceStep = step; }
  double distanceStep() const { return _distanceStep; }

  // Bearing
  // ---------------------------------------------------------------------------
  inline void setBearingMin(double min) { _bearingMin = min; }
  inline double bearingMin() const { return _bearingMin; }

  inline void setBearingMax(double max) { _bearingMax = max; }
  inline double bearingMax() const { return _bearingMax; }

  inline void setBearingStep(double step) { _bearingStep = step; }
  inline double bearingStep() const { return _bearingStep; }

private:
  double _distanceMin{100.};
  double _distanceMax{1000.};
  double _distanceStep{10.};
  double _bearingMin{0.};
  double _bearingMax{180.};
  double _bearingStep{5.};
};
