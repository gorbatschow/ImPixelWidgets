#include "PixelData.h"
#include <cstring>
#include <fstream>

PixelData::PixelData() {
  resize(4, 4);
  fill(ColorRGBA::Aqua());
  loadTexture();
}

PixelData::~PixelData() { unloadTexture(); }

void PixelData::resize(std::size_t w, std::size_t h) {
  if (_width == w && _height == h) {
    return;
  }
  _width = w;
  _height = h;
  _blob.resize(_width * _height * ColorRGBA::Size(), 0);
  _blob.shrink_to_fit();
}

void PixelData::loadTexture() {
  unloadTexture();
  glGenTextures(1, &_id);
  glBindTexture(GL_TEXTURE_2D, _id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, _blob.data());
}

void PixelData::unloadTexture() {
  if (_id) {
    glDeleteTextures(1, &_id);
    _id = {};
  }
}

void PixelData::clear() { memset(_blob.data(), {}, _blob.size()); }

void PixelData::clear(const std::vector<std::size_t> &pixel) {
  fill(pixel, ColorRGBA::Transparent());
}

void PixelData::fill(const ColorRGBA &rgba) {
  for (std::size_t i = 0; i != _blob.size(); i = i + ColorRGBA::Size()) {
    rgba.fill(&_blob[i]);
  }
}

void PixelData::fill(const std::vector<std::size_t> &pixel,
                     const ColorRGBA &rgba) {
  std::size_t i{};
  for (const auto &ind : pixel) {
    i = ind * ColorRGBA::Size();
    rgba.fill(&_blob[i]);
  }
}

ColorRGBA PixelData::colorAt(std::size_t pixel) const {
  pixel *= ColorRGBA::Size();
  return ColorRGBA(&_blob[pixel]);
}

bool PixelData::savePixelData(const std::string &fname) const {

  std::ofstream stream(fname.c_str(), std::fstream::out | std::fstream::binary);
  if (stream) {
    stream.write(reinterpret_cast<const char *>(_blob.data()), _blob.size());
    return (stream.good());
  }
  return false;
}
