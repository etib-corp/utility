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

#pragma once

#include <ostream>

#include <glm/glm.hpp>

#include "Color.hpp"
#include "Vector.hpp"

namespace utility {

class Vertex {

private:
  Vector<float, 3> _position;
  Color _color;
  Vector<float, 2> _textureCoordinates;

protected:
public:
  Vertex(const Vector<float, 3> &position, const Color &color,
         const Vector<float, 2> &textureCoordinates);

  /**
   * @brief Default destructor
   */
  ~Vertex(void) = default;

  /**
   * @brief Set the position of the vertex
   *
   * @param position The new position as a 3D vector
   */
  void setPosition(const Vector<float, 3> &position);

  /**
   * @brief Get the position of the vertex
   *
   * @return const Vector<float, 3>& The position as a 3D vector
   */
  const Vector<float, 3> &getPosition(void) const;

  /**
   * @brief Set the color of the vertex
   *
   * @param color The new color
   */
  void setColor(const Color &color);

  /**
   * @brief Get the color of the vertex
   *
   * @return const Color& The color
   */
  const Color &getColor(void) const;

  /**
   * @brief Set the texture coordinates of the vertex
   *
   * @param textureCoordinates The new texture coordinates as a 2D vector
   */
  void setTextureCoordinates(const Vector<float, 2> &textureCoordinates);

  /**
   * @brief Get the texture coordinates of the vertex
   *
   * @return const Vector<float, 2>& The texture coordinates as a 2D vector
   */
  const Vector<float, 2> &getTextureCoordinates(void) const;
};

/**
 * @brief Stream insertion operator for Vertex
 */
std::ostream &operator<<(std::ostream &os, const Vertex &vertex);

} // namespace utility

#include <iostream>
