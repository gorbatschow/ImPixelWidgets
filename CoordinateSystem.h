#pragma once
#include <cmath>

namespace CoordinateSystem {
enum class Type { Index, Node, Cartesian, Polar, Biangular };

inline static const double BaseRotation{90.};

inline double sind(double v) { return sin(fmod(v, 360.) * M_PI / 180.); }
inline double cosd(double v) { return cos(fmod(v, 360.) * M_PI / 180.); }
inline double atan2d(double y, double x) { return atan2(y, x) * 180. / M_PI; }
inline double round(double v, double d = 1e3) { return std::ceil(v * d) / d; }

inline void polarToCartesian(double &x, double &y, double r, double phi,
                             double rot = 0.) {
  x = r * cosd(90. - phi - BaseRotation + rot);
  y = r * sind(90. - phi - BaseRotation + rot);
}

inline void cartesianToPolar(double &r, double &phi, double x, double y,
                             double rot = 0.) {
  r = sqrt(x * x + y * y);
  phi = fmod(90. - atan2d(y, x) + 360. + BaseRotation - rot, 360.);
}
} // namespace CoordinateSystem
