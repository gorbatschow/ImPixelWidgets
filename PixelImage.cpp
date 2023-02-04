#include "PixelImage.h"
#include <cstring>
#include <fstream>

PixelImage::PixelImage() {
  resize(4, 4);
  fill(ColorRGBA::Aqua());
  loadTexture();
}

PixelImage::~PixelImage() { unloadTexture(); }

void PixelImage::resize(std::size_t w, std::size_t h) {
  if (_width == w && _height == h) {
    return;
  }
  _width = w;
  _height = h;
  _blob.resize(_width * _height * ColorRGBA::Size(), 0);
  _blob.shrink_to_fit();
}

void PixelImage::render() { loadTexture(); }

void PixelImage::clear() { memset(_blob.data(), {}, _blob.size()); }

void PixelImage::clear(const std::vector<std::size_t> &pixel) {
  fill(pixel, ColorRGBA::Transparent());
}

void PixelImage::fill(const ColorRGBA &rgba) {
  for (std::size_t i = 0; i != _blob.size(); i = i + ColorRGBA::Size()) {
    rgba.fill(&_blob[i]);
  }
}

void PixelImage::fill(const std::vector<std::size_t> &pixel,
                      const ColorRGBA &rgba) {
  std::size_t i{};
  for (const auto &ind : pixel) {
    i = ind * ColorRGBA::Size();
    rgba.fill(&_blob[i]);
  }
}

ColorRGBA PixelImage::colorAt(std::size_t pixel) const {
  pixel *= ColorRGBA::Size();
  return ColorRGBA(&_blob[pixel]);
}

bool PixelImage::savePixelData(const std::string &fname) const {

  std::ofstream stream(fname.c_str(), std::fstream::out | std::fstream::binary);
  if (stream) {
    stream.write(reinterpret_cast<const char *>(_blob.data()), _blob.size());
    return (stream.good());
  }
  return false;
}

void PixelImage::loadTexture() {
  unloadTexture();
  glGenTextures(1, &_id);
  glBindTexture(GL_TEXTURE_2D, _id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, _blob.data());
}

void PixelImage::unloadTexture() {
  if (_id) {
    glDeleteTextures(1, &_id);
    _id = {};
  }
}
