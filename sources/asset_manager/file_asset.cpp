/*
 Copyright (c) 2026 ETIB Corporation

 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include "utility/asset_manager/file_asset.hpp"

utility::FileAsset::FileAsset(const std::string &content) : _content(content) {}

utility::FileAsset::~FileAsset() {}

size_t utility::FileAsset::write(const void *ptr, size_t size, size_t nmemb) {
  size_t lenBefore = _content.size();
  size_t newLen = lenBefore + size * nmemb;
  if (newLen > _content.capacity()) {
    _content.reserve(newLen);
  }
  _content.insert(_pos, static_cast<const char *>(ptr), size * nmemb);
  _pos += size * nmemb;
  return (_content.size() - lenBefore) / size;
}

size_t utility::FileAsset::read(void *ptr, size_t size, size_t count) {
  size_t toRead = size * count;
  if (_pos + toRead > _content.size())
    toRead = _content.size() - _pos;
  std::memcpy(ptr, _content.c_str() + _pos, toRead);
  _pos += toRead;
  return toRead / size;
}

size_t utility::FileAsset::read(std::string &str, size_t size, size_t count) {
  return this->read(&str[0], size, count);
}

int utility::FileAsset::seek(long offset, Seek whence) {
  switch (whence) {
  case FileAsset::Seek::SET:
    _pos = offset;
    break;
  case FileAsset::Seek::CUR:
    _pos += offset;
    break;
  case FileAsset::Seek::END:
    _pos = _content.size() + offset;
    break;
  default:
    return -1;
  }
  return 0;
}

size_t utility::FileAsset::tell() const { return _pos; }

void utility::FileAsset::clear() {
  _content.clear();
  _pos = 0;
}

size_t utility::FileAsset::remove(size_t count) {
  size_t toRemove = std::min(count, _content.size() - _pos);
  _content.erase(_pos, toRemove);
  return toRemove;
}