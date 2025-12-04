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

#include "Vector.hpp"

namespace utility {

/**
 * @brief RGBA color representation with 8-bit channels
 *
 * Manages red, green, blue, and alpha color channels with values from 0-255.
 * Provides conversion to vector and glm::vec formats for graphics operations.
 */
class Color {
private:
  unsigned char _red;
  unsigned char _green;
  unsigned char _blue;
  unsigned char _alpha;

protected:
public:
  Color(void);
  ~Color(void);

  /**
   * @brief Set the red value
   *
   * @param red The red value (0-255)
   */
  void setRed(unsigned char red);

  /**
   * @brief Get the red value
   *
   * @return unsigned char The red value (0-255)
   */
  unsigned char getRed(void) const;

  /**
   * @brief Set the green value
   *
   * @param green The green value (0-255)
   */
  void setGreen(unsigned char green);

  /**
   * @brief Get the green value
   *
   * @return unsigned char The green value (0-255)
   */
  unsigned char getGreen(void) const;

  /**
   * @brief Set the blue value
   *
   * @param blue The blue value (0-255)
   */
  void setBlue(unsigned char blue);

  /**
   * @brief Get the blue value
   *
   * @return unsigned char The blue value (0-255)
   */
  unsigned char getBlue(void) const;

  /**
   * @brief Set the alpha value
   *
   * @param alpha The alpha value (0-255)
   */
  void setAlpha(unsigned char alpha);

  /**
   * @brief Get the alpha value
   *
   * @return unsigned char The alpha value (0-255)
   */
  unsigned char getAlpha(void) const;

  /**
   * @brief Convert the color to a Vector (3D)
   *
   * @return Vector<float, 3> The color as a 3D vector
   */
  Vector<float, 3> toVector(void) const;

  /**
   * @brief Convert the color to a glm::vec3
   *
   * @return glm::vec3 The color as a glm::vec3
   */
  glm::vec3 toVector3(void) const;

  /**
   * @brief Convert the color to a glm::vec4
   *
   * @return glm::vec4 The color as a glm::vec4
   */
  glm::vec4 toVector4(void) const;
};

/**
 * @brief Stream insertion operator for Color
 */
std::ostream &operator<<(std::ostream &os, const Color &color);

} // namespace utility

#include <iostream>