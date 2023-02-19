#include "ImPixelColorScheme.h"

namespace ImPixel {

struct ColorSchemeMonoImpl {
  std::array<std::array<uint8_t, 3>, 256> mono_srgb_bytes;

  constexpr ColorSchemeMonoImpl() {
    for (uint8_t i{}; i != mono_srgb_bytes.size(); ++i) {
      mono_srgb_bytes[i] = {i, i, i};
    }
  }
};

const std::array<uint8_t, 3> &ColorSchemeMono::rgb(uint8_t value) const {
  static const ColorSchemeMonoImpl scheme;
  return scheme.mono_srgb_bytes[value];
}
} // namespace ImPixel
