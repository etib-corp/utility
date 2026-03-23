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
 * @file ray.hpp
 * @brief Geometric ray template declaration.
 *
 * Declares `utility::graphics::Ray<Type, Dimension>`, a fixed-dimension ray
 * defined by an origin and a non-zero direction vector. Provides accessors,
 * mutators, translation utilities, and point evaluation along the ray.
 */

#pragma once

#include <ostream>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "utility/math/vector.hpp"

namespace utility::graphics {

using utility::math::Vector;

/**
 * @brief Concept to ensure the type can be used as a ray component.
 * @tparam Type The type to check.
 */
template <typename Type>
concept CanBeRayComponent = std::is_arithmetic<Type>::value;

/**
 * @brief Geometric ray with arithmetic component type and fixed dimension.
 * @tparam Type Arithmetic type for origin and direction components.
 * @tparam Dimension Compile-time dimension of the ray vectors.
 */
template <CanBeRayComponent Type, size_t Dimension> class Ray {
private:
protected:
  /**
   * @brief Origin point of the ray.
   */
  Vector<Type, Dimension> _origin;

  /**
   * @brief Direction vector of the ray (must be non-zero).
   */
  Vector<Type, Dimension> _direction;

  /**
   * @brief Validate that a direction vector is non-zero.
   * @param direction Direction vector to validate.
   * @throws std::invalid_argument if direction is the zero vector.
   */
  static void validateDirection(const Vector<Type, Dimension> &direction) {
    if (direction.magnitudeSquared() == Type{}) {
      throw std::invalid_argument("Ray direction must be non-zero");
    }
  }

public:
  /**
   * @brief Default constructor creating a ray at origin along the first axis.
   */
  Ray() : _origin() {
    _direction = Vector<Type, Dimension>();
    _direction[0] = Type{1};
  }

  /**
   * @brief Construct ray from origin and direction.
   * @param origin Origin point.
   * @param direction Direction vector (must be non-zero).
   * @throws std::invalid_argument if direction is the zero vector.
   */
  Ray(Vector<Type, Dimension> origin, Vector<Type, Dimension> direction)
      : _origin(std::move(origin)), _direction(std::move(direction)) {
    validateDirection(_direction);
  }

  /**
   * @brief Copy constructor.
   * @param other The ray to copy from.
   */
  Ray(const Ray &other)
      : _origin(other._origin), _direction(other._direction) {}

  /**
   * @brief Move constructor.
   * @param other The ray to move from.
   */
  Ray(Ray &&other) noexcept
      : _origin(std::move(other._origin)),
        _direction(std::move(other._direction)) {}

  /**
   * @brief Copy assignment operator.
   * @param other The ray to copy from.
   * @return Reference to this ray.
   */
  Ray &operator=(const Ray &other) {
    if (this != &other) {
      _origin = other._origin;
      _direction = other._direction;
    }
    return *this;
  }

  /**
   * @brief Move assignment operator.
   * @param other The ray to move from.
   * @return Reference to this ray.
   */
  Ray &operator=(Ray &&other) noexcept {
    if (this != &other) {
      _origin = std::move(other._origin);
      _direction = std::move(other._direction);
    }
    return *this;
  }

  // Destructor
  ~Ray() = default;

  /**
   * @brief Get the ray origin.
   * @return Origin vector.
   */
  Vector<Type, Dimension> getOrigin() const { return _origin; }

  /**
   * @brief Set the ray origin.
   * @param origin New origin vector.
   */
  void setOrigin(const Vector<Type, Dimension> &origin) { _origin = origin; }

  /**
   * @brief Get the ray direction.
   * @return Direction vector.
   */
  Vector<Type, Dimension> getDirection() const { return _direction; }

  /**
   * @brief Set the ray direction.
   * @param direction New direction vector (must be non-zero).
   * @throws std::invalid_argument if direction is the zero vector.
   */
  void setDirection(const Vector<Type, Dimension> &direction) {
    validateDirection(direction);
    _direction = direction;
  }

  /**
   * @brief Get a normalized copy of the ray direction.
   * @return Unit-length direction vector.
   */
  Vector<Type, Dimension> normalizedDirection() const {
    return _direction.normalized();
  }

  /**
   * @brief Evaluate a point on the ray at the provided parameter.
   * @param distanceParameter Parameter value measured along direction.
   * @return Point computed as origin + direction * parameter.
   */
  Vector<Type, Dimension> pointAt(Type distanceParameter) const {
    return _origin + (_direction * distanceParameter);
  }

  /**
   * @brief Translate ray origin by the provided offset.
   * @param offset Translation vector.
   */
  void translate(const Vector<Type, Dimension> &offset) { _origin += offset; }

  /**
   * @brief Get translated ray copy.
   * @param offset Translation vector.
   * @return Ray copy with translated origin.
   */
  Ray translated(const Vector<Type, Dimension> &offset) const {
    return Ray(_origin + offset, _direction);
  }

  /**
   * @brief Equality comparison.
   * @param other Ray to compare with.
   * @return True when origin and direction are equal.
   */
  bool operator==(const Ray &other) const {
    return _origin == other._origin && _direction == other._direction;
  }

  /**
   * @brief Inequality comparison.
   * @param other Ray to compare with.
   * @return True when origin or direction differ.
   */
  bool operator!=(const Ray &other) const { return !(*this == other); }
};

/**
 * @brief Stream output as "Ray(origin=..., direction=...)".
 * @tparam Type Arithmetic type of ray components.
 * @tparam Dimension Ray dimension.
 * @param outputStream Output stream.
 * @param ray Ray to output.
 * @return Reference to output stream.
 */
template <typename Type, size_t Dimension>
std::ostream &operator<<(std::ostream &outputStream,
                         const Ray<Type, Dimension> &ray) {
  outputStream << "Ray(origin=" << ray.getOrigin()
               << ", direction=" << ray.getDirection() << ')';
  return outputStream;
}

} // namespace utility::graphics
