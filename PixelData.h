#pragma once
#include "ColorRGBA.h"
#include <GL/gl.h>
#include <array>
#include <imgui.h>
#include <string>
#include <vector>

class PixelData {
public:
  // Constructor
  PixelData();

  // Destructor
  ~PixelData();

  // Resize
  void resize(std::size_t w, std::size_t h);

  // Load Texture
  void loadTexture();

  // Unload Texture
  void unloadTexture();

  // Fill
  void fill(const ColorRGBA &rgba = ColorRGBA::Aqua());

  // Fill
  void fill(const std::vector<std::size_t> &indexes,
            const ColorRGBA &rgba = ColorRGBA::Lime());

  // ID
  inline GLuint glID() const { return _id; }
  inline ImTextureID imID() const { return (ImTextureID)(intptr_t)glID(); }

  // Get Blob
  const std::vector<uint8_t> &pixelData() const { return _blob; }

  // Save Blob
  bool savePixelData(const std::string &fname) const;

private:
  std::size_t _width{};
  std::size_t _height{};
  std::vector<uint8_t> _blob;
  GLuint _id{};
};
