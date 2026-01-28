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

#include "utility/math/vector.hpp"

namespace utility::math {

/**
 * @brief Concept to ensure the type can be used as a rectangle component.
 * @tparam Type The type to check.
 */
template <typename Type>
concept CanBeRectangleComponent = std::is_arithmetic<Type>::value;

/**
 * @brief Axis-aligned rectangle with arithmetic type components.
 * @tparam Type Arithmetic type for position and dimensions
 */
template <CanBeRectangleComponent Type> class Rectangle {
private:
protected:
  /**
   * @brief Position vector storing X and Y coordinates of the top-left corner.
   */
  Vector<Type, 2> _position;

  /**
   * @brief Size vector storing width and height of the rectangle.
   */
  Vector<Type, 2> _size;

public:
  /**
   * @brief Default constructor initializing rectangle at origin with zero size.
   */
  Rectangle() : _position(), _size() {}

  /**
   * @brief Construct rectangle with position and size.
   * @param position Top-left corner position vector (x, y).
   * @param size Size vector (width, height).
   * @throws std::invalid_argument if width or height is negative.
   */
  Rectangle(Vector<Type, 2> position, Vector<Type, 2> size)
      : _position(std::move(position)), _size(std::move(size)) {
    if (_size[0] < Type{} || _size[1] < Type{}) {
      throw std::invalid_argument(
          "Rectangle width and height must be non-negative");
    }
  }

  /**
   * @brief Construct rectangle with position and dimensions.
   * @param x X-coordinate of the top-left corner.
   * @param y Y-coordinate of the top-left corner.
   * @param width Width of the rectangle.
   * @param height Height of the rectangle.
   * @throws std::invalid_argument if width or height is negative.
   */
  Rectangle(Type x, Type y, Type width, Type height)
      : _position({x, y}), _size({width, height}) {
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
      : _position(other._position), _size(other._size) {}

  /**
   * @brief Move constructor.
   * @param other The rectangle to move from.
   */
  Rectangle(Rectangle &&other) noexcept
      : _position(std::move(other._position)), _size(std::move(other._size)) {}

  /**
   * @brief Copy assignment operator.
   * @param other The rectangle to copy from.
   * @return Reference to this rectangle.
   */
  Rectangle &operator=(const Rectangle &other) {
    if (this != &other) {
      _position = other._position;
      _size = other._size;
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
      _position = std::move(other._position);
      _size = std::move(other._size);
    }
    return *this;
  }

  // Destructor
  ~Rectangle() = default;

  /**
   * @brief Get the position of the top-left corner.
   * @return Position vector (x, y).
   */
  Vector<Type, 2> getPosition() const { return _position; }

  /**
   * @brief Get the size of the rectangle.
   * @return Size vector (width, height).
   */
  Vector<Type, 2> getSize() const { return _size; }

  /**
   * @brief Set the position of the top-left corner.
   * @param position New position vector (x, y).
   */
  void setPosition(const Vector<Type, 2> &position) { _position = position; }

  /**
   * @brief Get the X-coordinate of the top-left corner.
   * @return X-coordinate.
   */
  Type x() const { return _position[0]; }

  /**
   * @brief Get the Y-coordinate of the top-left corner.
   * @return Y-coordinate.
   */
  Type y() const { return _position[1]; }

  /**
   * @brief Get the width of the rectangle.
   * @return Width.
   */
  Type width() const { return _size[0]; }

  /**
   * @brief Get the height of the rectangle.
   * @return Height.
   */
  Type height() const { return _size[1]; }

  /**
   * @brief Set the size of the rectangle.
   * @param size New size vector (width, height).
   * @throws std::invalid_argument if width or height is negative.
   */
  void setSize(const Vector<Type, 2> &size) {
    if (size[0] < Type{} || size[1] < Type{}) {
      throw std::invalid_argument(
          "Rectangle width and height must be non-negative");
    }
    _size = size;
  }

  /**
   * @brief Set the X-coordinate of the top-left corner.
   * @param x New X-coordinate.
   */
  void setX(Type x) { _position[0] = x; }

  /**
   * @brief Set the Y-coordinate of the top-left corner.
   * @param y New Y-coordinate.
   */
  void setY(Type y) { _position[1] = y; }

  /**
   * @brief Set the width of the rectangle.
   * @param width New width.
   * @throws std::invalid_argument if width is negative.
   */
  void setWidth(Type width) {
    if (width < Type{}) {
      throw std::invalid_argument("Rectangle width must be non-negative");
    }
    _size[0] = width;
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
    _size[1] = height;
  }

  /**
   * @brief Get the X-coordinate of the right edge.
   * @return Right edge X-coordinate.
   */
  Type right() const { return _position[0] + _size[0]; }

  /**
   * @brief Get the Y-coordinate of the bottom edge.
   * @return Bottom edge Y-coordinate.
   */
  Type bottom() const { return _position[1] + _size[1]; }

  /**
   * @brief Get the X-coordinate of the center.
   * @return Center X-coordinate.
   */
  Type centerX() const { return _position[0] + _size[0] / Type{2}; }

  /**
   * @brief Get the Y-coordinate of the center.
   * @return Center Y-coordinate.
   */
  Type centerY() const { return _position[1] + _size[1] / Type{2}; }

  /**
   * @brief Compute the area of the rectangle.
   * @return Area.
   */
  Type area() const { return _size[0] * _size[1]; }

  /**
   * @brief Compute the perimeter of the rectangle.
   * @return Perimeter.
   */
  Type perimeter() const { return Type{2} * (_size[0] + _size[1]); }

  /**
   * @brief Check if a point is contained within the rectangle.
   * @param point Point as a vector.
   * @return True if the point is inside or on the boundary, false
   * otherwise.
   */
  bool contains(Vector<Type, 2> point) const {
    return point[0] >= _position[0] && point[0] <= right() &&
           point[1] >= _position[1] && point[1] <= bottom();
  }

  /**
   * @brief Check if this rectangle intersects with another.
   * @param other The other rectangle to check intersection with.
   * @return True if the rectangles intersect, false otherwise.
   */
  bool intersects(const Rectangle &other) const {
    return !(_position[0] > other.right() || right() < other._position[0] ||
             _position[1] > other.bottom() || bottom() < other._position[1]);
  }

  /**
   * @brief Check if this rectangle completely contains another rectangle.
   * @param other The other rectangle to check.
   * @return True if this rectangle contains the other, false otherwise.
   */
  bool containsRectangle(const Rectangle &other) const {
    return other._position[0] >= _position[0] && other.right() <= right() &&
           other._position[1] >= _position[1] && other.bottom() <= bottom();
  }

  /**
   * @brief Equality comparison.
   * @param other The rectangle to compare with.
   * @return True if all components are equal, false otherwise.
   */
  bool operator==(const Rectangle &other) const {
    return _position == other._position && _size == other._size;
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
    _position[0] += dx;
    _position[1] += dy;
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
    _size[0] *= factor;
    _size[1] *= factor;
    _position[0] = cx - _size[0] / Type{2};
    _position[1] = cy - _size[1] / Type{2};
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
    Type newWidth = _size[0] * factor;
    Type newHeight = _size[1] * factor;
    return Rectangle(cx - newWidth / Type{2}, cy - newHeight / Type{2},
                     newWidth, newHeight);
  }

  /**
   * @brief Get a translated copy of the rectangle.
   * @param offset Offset vector (dx, dy).
   * @return Translated rectangle.
   */
  Rectangle translated(Vector<Type, 2> offset) const {
    return Rectangle(_position[0] + offset[0], _position[1] + offset[1],
                     _size[0], _size[1]);
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

} // namespace utility::math
