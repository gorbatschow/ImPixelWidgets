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
  inline double distanceMin() const { return _distanceMin; }

  inline void setDistanceMax(double max) { _distanceMax = max; }
  inline double distanceMax() const { return _distanceMax; }

  inline void setDistanceStep(double step) { _distanceStep = step; }
  inline double distanceStep() const { return _distanceStep; }

  inline bool containsDistance(double value) const {
    return value >= _distanceMin && value < _distanceMax;
  }

  inline void setDistanceRange(double range) { _distanceRange = range; }
  inline double distanceRange() const { return _distanceRange; }

  // Bearing
  // ---------------------------------------------------------------------------
  inline void setBearingMin(double min) { _bearingMin = min; }
  inline double bearingMin() const { return _bearingMin; }

  inline void setBearingMax(double max) { _bearingMax = max; }
  inline double bearingMax() const { return _bearingMax; }

  inline void setBearingStep(double step) { _bearingStep = step; }
  inline double bearingStep() const { return _bearingStep; }

  inline bool containsBearing(double value) const {
    return value >= _bearingMin && value < _bearingMax;
  }

private:
  double _distanceMin{100.};
  double _distanceMax{1000.};
  double _distanceStep{10.};
  double _distanceRange{1100.};
  double _bearingMin{0.};
  double _bearingMax{180.};
  double _bearingStep{5.};
};
