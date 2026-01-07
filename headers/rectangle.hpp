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

/**
 * @file rectangle.hpp
 * @brief Axis-aligned rectangle template declaration.
 *
 * Declares `utility::Rectangle<Type>`, an axis-aligned rectangle supporting
 * geometry operations such as area, perimeter, containment, intersection,
 * translation, and scaling.
 */

#pragma once

#include <ostream>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace utility {

/**
 * @brief Axis-aligned rectangle with arithmetic type components.
 * @tparam Type Arithmetic type for position and dimensions
 */
template <typename Type> class Rectangle {
private:
protected:
  /**
   * @brief X-coordinate of the top-left corner.
   */
  Type _x;

  /**
   * @brief Y-coordinate of the top-left corner.
   */
  Type _y;

  /**
   * @brief Width of the rectangle.
   */
  Type _width;

  /**
   * @brief Height of the rectangle.
   */
  Type _height;

public:
  /**
   * @brief Default constructor initializing rectangle at origin with zero size.
   */
  Rectangle() : _x(Type{}), _y(Type{}), _width(Type{}), _height(Type{}) {}

  /**
   * @brief Construct rectangle with position and dimensions.
   * @param x X-coordinate of the top-left corner.
   * @param y Y-coordinate of the top-left corner.
   * @param width Width of the rectangle.
   * @param height Height of the rectangle.
   * @throws std::invalid_argument if width or height is negative.
   */
  Rectangle(Type x, Type y, Type width, Type height)
      : _x(x), _y(y), _width(width), _height(height) {
    if (width < Type{} || height < Type{}) {
      throw std::invalid_argument(
          "Rectangle width and height must be non-negative");
    }
  }

  /**
   * @brief Copy constructor.
   * @param other The rectangle to copy from.
   */
  Rectangle(const Rectangle &other)
      : _x(other._x), _y(other._y), _width(other._width),
        _height(other._height) {}

  /**
   * @brief Move constructor.
   * @param other The rectangle to move from.
   */
  Rectangle(Rectangle &&other) noexcept
      : _x(std::move(other._x)), _y(std::move(other._y)),
        _width(std::move(other._width)), _height(std::move(other._height)) {}

  /**
   * @brief Copy assignment operator.
   * @param other The rectangle to copy from.
   * @return Reference to this rectangle.
   */
  Rectangle &operator=(const Rectangle &other) {
    if (this != &other) {
      _x = other._x;
      _y = other._y;
      _width = other._width;
      _height = other._height;
    }
    return *this;
  }

  /**
   * @brief Move assignment operator.
   * @param other The rectangle to move from.
   * @return Reference to this rectangle.
   */
  Rectangle &operator=(Rectangle &&other) noexcept {
    if (this != &other) {
      _x = std::move(other._x);
      _y = std::move(other._y);
      _width = std::move(other._width);
      _height = std::move(other._height);
    }
    return *this;
  }

  // Destructor
  ~Rectangle() = default;

  /**
   * @brief Get the X-coordinate of the top-left corner.
   * @return X-coordinate.
   */
  Type x() const { return _x; }

  /**
   * @brief Get the Y-coordinate of the top-left corner.
   * @return Y-coordinate.
   */
  Type y() const { return _y; }

  /**
   * @brief Get the width of the rectangle.
   * @return Width.
   */
  Type width() const { return _width; }

  /**
   * @brief Get the height of the rectangle.
   * @return Height.
   */
  Type height() const { return _height; }

  /**
   * @brief Set the X-coordinate of the top-left corner.
   * @param x New X-coordinate.
   */
  void setX(Type x) { _x = x; }

  /**
   * @brief Set the Y-coordinate of the top-left corner.
   * @param y New Y-coordinate.
   */
  void setY(Type y) { _y = y; }

  /**
   * @brief Set the width of the rectangle.
   * @param width New width.
   * @throws std::invalid_argument if width is negative.
   */
  void setWidth(Type width) {
    if (width < Type{}) {
      throw std::invalid_argument("Rectangle width must be non-negative");
    }
    _width = width;
  }

  /**
   * @brief Set the height of the rectangle.
   * @param height New height.
   * @throws std::invalid_argument if height is negative.
   */
  void setHeight(Type height) {
    if (height < Type{}) {
      throw std::invalid_argument("Rectangle height must be non-negative");
    }
    _height = height;
  }

  /**
   * @brief Get the X-coordinate of the right edge.
   * @return Right edge X-coordinate.
   */
  Type right() const { return _x + _width; }

  /**
   * @brief Get the Y-coordinate of the bottom edge.
   * @return Bottom edge Y-coordinate.
   */
  Type bottom() const { return _y + _height; }

  /**
   * @brief Get the X-coordinate of the center.
   * @return Center X-coordinate.
   */
  Type centerX() const { return _x + _width / Type{2}; }

  /**
   * @brief Get the Y-coordinate of the center.
   * @return Center Y-coordinate.
   */
  Type centerY() const { return _y + _height / Type{2}; }

  /**
   * @brief Compute the area of the rectangle.
   * @return Area.
   */
  Type area() const { return _width * _height; }

  /**
   * @brief Compute the perimeter of the rectangle.
   * @return Perimeter.
   */
  Type perimeter() const { return Type{2} * (_width + _height); }

  /**
   * @brief Check if a point is contained within the rectangle.
   * @param px X-coordinate of the point.
   * @param py Y-coordinate of the point.
   * @return True if the point is inside or on the boundary, false otherwise.
   */
  bool contains(Type px, Type py) const {
    return px >= _x && px <= right() && py >= _y && py <= bottom();
  }

  /**
   * @brief Check if this rectangle intersects with another.
   * @param other The other rectangle to check intersection with.
   * @return True if the rectangles intersect, false otherwise.
   */
  bool intersects(const Rectangle &other) const {
    return !(_x > other.right() || right() < other._x || _y > other.bottom() ||
             bottom() < other._y);
  }

  /**
   * @brief Check if this rectangle completely contains another rectangle.
   * @param other The other rectangle to check.
   * @return True if this rectangle contains the other, false otherwise.
   */
  bool containsRectangle(const Rectangle &other) const {
    return other._x >= _x && other.right() <= right() && other._y >= _y &&
           other.bottom() <= bottom();
  }

  /**
   * @brief Equality comparison.
   * @param other The rectangle to compare with.
   * @return True if all components are equal, false otherwise.
   */
  bool operator==(const Rectangle &other) const {
    return _x == other._x && _y == other._y && _width == other._width &&
           _height == other._height;
  }

  /**
   * @brief Inequality comparison.
   * @param other The rectangle to compare with.
   * @return True if any component is not equal, false otherwise.
   */
  bool operator!=(const Rectangle &other) const { return !(*this == other); }

  /**
   * @brief Translate the rectangle by offset amounts.
   * @param dx X-offset.
   * @param dy Y-offset.
   */
  void translate(Type dx, Type dy) {
    _x += dx;
    _y += dy;
  }

  /**
   * @brief Scale the rectangle from its center.
   * @param factor Scaling factor.
   * @throws std::invalid_argument if factor is negative.
   */
  void scale(Type factor) {
    if (factor < Type{}) {
      throw std::invalid_argument("Scale factor must be non-negative");
    }
    Type cx = centerX();
    Type cy = centerY();
    _width *= factor;
    _height *= factor;
    _x = cx - _width / Type{2};
    _y = cy - _height / Type{2};
  }

  /**
   * @brief Get a scaled copy of the rectangle.
   * @param factor Scaling factor.
   * @return Scaled rectangle.
   * @throws std::invalid_argument if factor is negative.
   */
  Rectangle scaled(Type factor) const {
    if (factor < Type{}) {
      throw std::invalid_argument("Scale factor must be non-negative");
    }
    Type cx = centerX();
    Type cy = centerY();
    Type newWidth = _width * factor;
    Type newHeight = _height * factor;
    return Rectangle(cx - newWidth / Type{2}, cy - newHeight / Type{2},
                     newWidth, newHeight);
  }

  /**
   * @brief Get a translated copy of the rectangle.
   * @param dx X-offset.
   * @param dy Y-offset.
   * @return Translated rectangle.
   */
  Rectangle translated(Type dx, Type dy) const {
    return Rectangle(_x + dx, _y + dy, _width, _height);
  }
};

/**
 * @brief Stream output as "Rectangle(x, y, width, height)".
 * @tparam Type Arithmetic type of the rectangle.
 * @param outputStream The output stream.
 * @param rectangle The rectangle to output.
 * @return Reference to the output stream.
 */
template <typename Type>
std::ostream &operator<<(std::ostream &outputStream,
                         const Rectangle<Type> &rectangle) {
  outputStream << "Rectangle(" << rectangle.x() << ", " << rectangle.y() << ", "
               << rectangle.width() << ", " << rectangle.height() << ')';
  return outputStream;
}

} // namespace utility
