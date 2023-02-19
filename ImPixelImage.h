#pragma once
#include "ImPixelColorRGBA.h"
#include <GL/gl.h>
#include <array>
#include <imgui.h>
#include <string>
#include <vector>

namespace ImPixel {
class Image {
public:
  // Constructor
  Image();

  // Destructor
  ~Image();

  // Resize
  void resize(std::size_t w, std::size_t h);

  // Render
  void render();

  // Clear All
  void clear();

  // Clear Pixel
  void clear(const std::vector<std::size_t> &pixel);

  // Fill All
  void fill(const ColorRGBA &rgba);

  // Fill Pixel
  void fill(const std::vector<std::size_t> &pixel,
            const ColorRGBA &rgba = ColorRGBA::Lime());

  // Get Color
  ColorRGBA colorAt(std::size_t pixel) const;

  // ID
  inline GLuint glID() const { return _id; }
  inline ImTextureID imID() const { return (ImTextureID)(intptr_t)glID(); }

  // Get Blob
  const std::vector<uint8_t> &blob() const { return _blob; }

  // Save Blob
  bool savePixelData(const std::string &fname) const;

private:
  std::size_t _width{};
  std::size_t _height{};
  std::vector<uint8_t> _blob;
  GLuint _id{};

  // Load Texture
  void loadTexture();

  // Unload Texture
  void unloadTexture();
};
} // namespace ImPixel
