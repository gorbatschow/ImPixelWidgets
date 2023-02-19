#include "ImPixelImage.h"
#include <cstring>
#include <fstream>

namespace ImPixel {
Image::Image() {
  resize(4, 4);
  fill(ColorRGBA::Aqua());
  loadTexture();
}

Image::~Image() { unloadTexture(); }

void Image::resize(std::size_t w, std::size_t h) {
  if (_width == w && _height == h) {
    return;
  }
  _width = w;
  _height = h;
  _blob.resize(_width * _height * ColorRGBA::Size(), 0);
  _blob.shrink_to_fit();
}

void Image::render() { loadTexture(); }

void Image::clear() { memset(_blob.data(), {}, _blob.size()); }

void Image::clear(const std::vector<std::size_t> &pixel) {
  fill(pixel, ColorRGBA::Transparent());
}

void Image::fill(const ColorRGBA &color) {
  for (std::size_t i = 0; i != _blob.size(); i = i + ColorRGBA::Size()) {
    color.fill(&_blob[i]);
  }
}

void Image::fill(const std::vector<std::size_t> &pixel,
                 const ColorRGBA &color) {
  std::size_t i{};
  for (const auto &ind : pixel) {
    i = ind * ColorRGBA::Size();
    color.fill(&_blob[i]);
  }
}

void Image::fill(const std::vector<std::size_t> &pixel,
                 const std::array<uint8_t, 3> &rgb, const uint8_t &alpha) {
  std::size_t i{};
  for (const auto &ind : pixel) {
    i = ind * ColorRGBA::Size();
    ColorRGBA::Fill(&_blob[i], rgb, alpha);
  }
}

bool Image::savePixelData(const std::string &fname) const {

  std::ofstream stream(fname.c_str(), std::fstream::out | std::fstream::binary);
  if (stream) {
    stream.write(reinterpret_cast<const char *>(_blob.data()), _blob.size());
    return (stream.good());
  }
  return false;
}

void Image::loadTexture() {
  unloadTexture();
  glGenTextures(1, &_id);
  glBindTexture(GL_TEXTURE_2D, _id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, _blob.data());
}

void Image::unloadTexture() {
  if (_id) {
    glDeleteTextures(1, &_id);
    _id = {};
  }
}
} // namespace ImPixel
