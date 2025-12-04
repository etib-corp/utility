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

#include "Vertex.hpp"

namespace utility {

Vertex::Vertex(const Vector<float, 3> &position, const Color &color,
               const Vector<float, 2> &textureCoordinates)
    : _position(position), _color(color),
      _textureCoordinates(textureCoordinates) {}

void Vertex::setPosition(const Vector<float, 3> &position) {
  _position = position;
}

const Vector<float, 3> &Vertex::getPosition(void) const { return _position; }

void Vertex::setColor(const Color &color) { _color = color; }

const Color &Vertex::getColor(void) const { return _color; }

void Vertex::setTextureCoordinates(const Vector<float, 2> &textureCoordinates) {
  _textureCoordinates = textureCoordinates;
}

const Vector<float, 2> &Vertex::getTextureCoordinates(void) const {
  return _textureCoordinates;
}

std::ostream &operator<<(std::ostream &os, const Vertex &vertex) {
  os << "Vertex(Pos:" << vertex.getPosition() << ", Color:" << vertex.getColor()
     << ", TexCoord:" << vertex.getTextureCoordinates() << ")";
  return os;
}

} // namespace utility