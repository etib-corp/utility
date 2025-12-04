/*
 Copyright (c) 2025 ETIB Corporation

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

#include "Color.hpp"
#include "Vector.hpp"

utility::Color::Color(void) : _red(0), _green(0), _blue(0), _alpha(255) {}

utility::Color::~Color(void) {}

void utility::Color::setRed(unsigned char red) { _red = red; }

unsigned char utility::Color::getRed(void) const { return _red; }

void utility::Color::setGreen(unsigned char green) { _green = green; }

unsigned char utility::Color::getGreen(void) const { return _green; }

void utility::Color::setBlue(unsigned char blue) { _blue = blue; }

unsigned char utility::Color::getBlue(void) const { return _blue; }

void utility::Color::setAlpha(unsigned char alpha) { _alpha = alpha; }

unsigned char utility::Color::getAlpha(void) const { return _alpha; }

utility::Vector<float, 3> utility::Color::toVector(void) const {
  return Vector<float, 3>(static_cast<float>(_red) / 255.0f,
                          static_cast<float>(_green) / 255.0f,
                          static_cast<float>(_blue) / 255.0f);
}

glm::vec3 utility::Color::toVector3(void) const {
  return glm::vec3(static_cast<float>(_red) / 255.0f,
                   static_cast<float>(_green) / 255.0f,
                   static_cast<float>(_blue) / 255.0f);
}

glm::vec4 utility::Color::toVector4(void) const {
  return glm::vec4(
      static_cast<float>(_red) / 255.0f, static_cast<float>(_green) / 255.0f,
      static_cast<float>(_blue) / 255.0f, static_cast<float>(_alpha) / 255.0f);
}

std::ostream &utility::operator<<(std::ostream &os, const Color &color) {
  os << "Color(R:" << static_cast<int>(color.getRed()) 
     << ", G:" << static_cast<int>(color.getGreen())
     << ", B:" << static_cast<int>(color.getBlue())
     << ", A:" << static_cast<int>(color.getAlpha()) << ")";
  return os;
}
