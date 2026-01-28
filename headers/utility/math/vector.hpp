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
 * @file vector.hpp
 * @brief Fixed-size arithmetic vector template declaration.
 *
 * Declares `utility::Vector<Type, Dimension>`, a compile-time sized vector
 * supporting common linear algebra operations including addition, subtraction,
 * scaling, dot product, magnitude, normalization, and (for 3D) cross product.
 */

#pragma once

#include <cmath>
#include <initializer_list>
#include <ostream>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace utility::math {

/**
 * @brief Concept to ensure the type can be used as a vector component.
 * @tparam Type The type to check.
 */
template <typename Type>
concept CanBeVectorComponent = std::is_arithmetic<Type>::value;

/**
 * @brief Fixed-size arithmetic vector supporting common linear operations.
 * @tparam Type Arithmetic component type
 * @tparam Dimension Compile-time vector dimension
 */
template <CanBeVectorComponent Type, size_t Dimension> class Vector {
private:
protected:
  /**
   * @brief Stored components in Cartesian order.
   */
  Type _components[Dimension];

public:
  /**
   * @brief Default constructor initializing all components to zero.
   */
  Vector() {
    for (size_t i = 0; i < Dimension; ++i) {
      _components[i] = Type{};
    }
  }

  /**
   * @brief Construct from initializer list matching the vector dimension.
   * @param values The initializer list of component values.
   * @throws std::invalid_argument if the list size doesn't match the dimension.
   */
  Vector(std::initializer_list<Type> values) {
    if (values.size() != Dimension) {
      throw std::invalid_argument(
          "Initializer list size must match vector dimension");
    }
    size_t i = 0;
    for (const auto &value : values) {
      _components[i++] = value;
    }
  }

  /**
   * @brief Construct by filling all components with the same value.
   * @param value The value to fill all components with.
   */
  explicit Vector(Type value) {
    for (size_t i = 0; i < Dimension; ++i) {
      _components[i] = value;
    }
  }

  /**
   * @brief Copy constructor.
   * @param other The vector to copy from.
   */
  Vector(const Vector &other) {
    for (size_t i = 0; i < Dimension; ++i) {
      _components[i] = other._components[i];
    }
  }

  /**
   * @brief Move constructor.
   * @param other The vector to move from.
   */
  Vector(Vector &&other) noexcept {
    for (size_t i = 0; i < Dimension; ++i) {
      _components[i] = std::move(other._components[i]);
    }
  }

  /**
   * @brief Copy assignment operator.
   * @param other The vector to copy from.
   * @return Reference to this vector.
   */
  Vector &operator=(const Vector &other) {
    if (this != &other) {
      for (size_t i = 0; i < Dimension; ++i) {
        _components[i] = other._components[i];
      }
    }
    return *this;
  }

  /**
   * @brief Move assignment operator.
   * @param other The vector to move from.
   * @return Reference to this vector.
   */
  Vector &operator=(Vector &&other) noexcept {
    if (this != &other) {
      for (size_t i = 0; i < Dimension; ++i) {
        _components[i] = std::move(other._components[i]);
      }
    }
    return *this;
  }

  // Destructor
  ~Vector() = default;

  /**
   * @brief Mutable element access with bounds checking.
   * @param index The index of the element to access.
   * @return Reference to the element at the given index.
   * @throws std::out_of_range if index is out of bounds.
   */
  Type &operator[](size_t index) {
    if (index >= Dimension) {
      throw std::out_of_range("Vector index out of range");
    }
    return _components[index];
  }

  /**
   * @brief Const element access with bounds checking.
   * @param index The index of the element to access.
   * @return Const reference to the element at the given index.
   * @throws std::out_of_range if index is out of bounds.
   */
  const Type &operator[](size_t index) const {
    if (index >= Dimension) {
      throw std::out_of_range("Vector index out of range");
    }
    return _components[index];
  }

  /**
   * @brief Compile-time dimension helper.
   * @return The number of components in the vector.
   */
  size_t size() const { return Dimension; }

  /**
   * @brief Mutable access to internal component array.
   * @return Pointer to the first component.
   */
  Type *data() { return _components; }

  /**
   * @brief Const access to internal component array.
   * @return Const pointer to the first component.
   */
  const Type *data() const { return _components; }

  /**
   * @brief Vector addition.
   * @param other The vector to add.
   * @return Result of vector addition.
   */
  Vector operator+(const Vector &other) const {
    Vector result;
    for (size_t i = 0; i < Dimension; ++i) {
      result._components[i] = _components[i] + other._components[i];
    }
    return result;
  }

  /**
   * @brief Vector subtraction.
   * @param other The vector to subtract.
   * @return Result of vector subtraction.
   */
  Vector operator-(const Vector &other) const {
    Vector result;
    for (size_t i = 0; i < Dimension; ++i) {
      result._components[i] = _components[i] - other._components[i];
    }
    return result;
  }

  /**
   * @brief Scalar multiplication.
   * @param scalar The scalar to multiply by.
   * @return Result of scalar multiplication.
   */
  Vector operator*(Type scalar) const {
    Vector result;
    for (size_t i = 0; i < Dimension; ++i) {
      result._components[i] = _components[i] * scalar;
    }
    return result;
  }

  /**
   * @brief Scalar division.
   * @param scalar The scalar to divide by.
   * @return Result of scalar division.
   * @throws std::invalid_argument if scalar is zero.
   */
  Vector operator/(Type scalar) const {
    if (scalar == Type{}) {
      throw std::invalid_argument("Division by zero");
    }
    Vector result;
    for (size_t i = 0; i < Dimension; ++i) {
      result._components[i] = _components[i] / scalar;
    }
    return result;
  }

  /**
   * @brief In-place vector addition.
   * @param other The vector to add.
   * @return Reference to this vector.
   */
  Vector &operator+=(const Vector &other) {
    for (size_t i = 0; i < Dimension; ++i) {
      _components[i] += other._components[i];
    }
    return *this;
  }

  /**
   * @brief In-place vector subtraction.
   * @param other The vector to subtract.
   * @return Reference to this vector.
   */
  Vector &operator-=(const Vector &other) {
    for (size_t i = 0; i < Dimension; ++i) {
      _components[i] -= other._components[i];
    }
    return *this;
  }

  /**
   * @brief In-place scalar multiplication.
   * @param scalar The scalar to multiply by.
   * @return Reference to this vector.
   */
  Vector &operator*=(Type scalar) {
    for (size_t i = 0; i < Dimension; ++i) {
      _components[i] *= scalar;
    }
    return *this;
  }

  /**
   * @brief In-place scalar division.
   * @param scalar The scalar to divide by.
   * @return Reference to this vector.
   * @throws std::invalid_argument if scalar is zero.
   */
  Vector &operator/=(Type scalar) {
    if (scalar == Type{}) {
      throw std::invalid_argument("Division by zero");
    }
    for (size_t i = 0; i < Dimension; ++i) {
      _components[i] /= scalar;
    }
    return *this;
  }

  /**
   * @brief Unary negation operator.
   * @return Negated vector.
   */
  Vector operator-() const {
    Vector result;
    for (size_t i = 0; i < Dimension; ++i) {
      result._components[i] = -_components[i];
    }
    return result;
  }

  /**
   * @brief Equality comparison.
   * @param other The vector to compare with.
   * @return True if all components are equal, false otherwise.
   */
  bool operator==(const Vector &other) const {
    for (size_t i = 0; i < Dimension; ++i) {
      if (_components[i] != other._components[i]) {
        return false;
      }
    }
    return true;
  }

  /**
   * @brief Inequality comparison.
   * @param other The vector to compare with.
   * @return True if any component is not equal, false otherwise.
   */
  bool operator!=(const Vector &other) const { return !(*this == other); }

  /**
   * @brief Compute the dot product with another vector.
   * @param other The vector to compute the dot product with.
   * @return The dot product value.
   */
  Type dot(const Vector &other) const {
    Type result = Type{};
    for (size_t i = 0; i < Dimension; ++i) {
      result += _components[i] * other._components[i];
    }
    return result;
  }

  /**
   * @brief Compute the Euclidean magnitude.
   * @return The magnitude of the vector.
   */
  Type magnitude() const {
    Type sum = Type{};
    for (size_t i = 0; i < Dimension; ++i) {
      sum += _components[i] * _components[i];
    }
    return std::sqrt(sum);
  }

  /**
   * @brief Compute squared magnitude (avoids sqrt cost).
   * @return The squared magnitude of the vector.
   */
  Type magnitudeSquared() const {
    Type sum = Type{};
    for (size_t i = 0; i < Dimension; ++i) {
      sum += _components[i] * _components[i];
    }
    return sum;
  }

  /**
   * @brief Return a normalized copy.
   * @return A normalized version of this vector.
   * @throws std::runtime_error if the vector has zero magnitude.
   */
  Vector normalized() const {
    Type mag = magnitude();
    if (mag == Type{}) {
      throw std::runtime_error("Cannot normalize zero vector");
    }
    return *this / mag;
  }

  /**
   * @brief Normalize in place.
   */
  void normalize() {
    Type mag = magnitude();
    if (mag == Type{}) {
      throw std::runtime_error("Cannot normalize zero vector");
    }
    *this /= mag;
  }

  /**
   * @brief Cross product (enabled only for 3D vectors).
   * @param other The vector to compute the cross product with.
   * @return The cross product vector.
   */
  template <size_t D = Dimension>
  typename std::enable_if<D == 3, Vector>::type
  cross(const Vector &other) const {
    Vector result;
    result._components[0] = _components[1] * other._components[2] -
                            _components[2] * other._components[1];
    result._components[1] = _components[2] * other._components[0] -
                            _components[0] * other._components[2];
    result._components[2] = _components[0] * other._components[1] -
                            _components[1] * other._components[0];
    return result;
  }

  /**
   * @brief Euclidean distance to another vector.
   * @param other The vector to compute distance to.
   * @return The Euclidean distance.
   */
  Type distance(const Vector &other) const {
    return (*this - other).magnitude();
  }

  /**
   * @brief Squared Euclidean distance to another vector.
   * @param other The vector to compute squared distance to.
   * @return The squared Euclidean distance.
   */
  Type distanceSquared(const Vector &other) const {
    return (*this - other).magnitudeSquared();
  }
};

/**
 * @brief Scalar multiplication (scalar * vector).
 * @tparam Type Arithmetic component type
 * @tparam Dimension Compile-time vector dimension
 * @param scalar The scalar to multiply by.
 * @param vector The vector to multiply.
 * @return Result of scalar multiplication.
 */
template <typename Type, size_t Dimension>
Vector<Type, Dimension> operator*(Type scalar,
                                  const Vector<Type, Dimension> &vector) {
  return vector * scalar;
}

/**
 * @brief Stream output as "(a, b, c)".
 * @tparam Type Arithmetic component type
 * @tparam Dimension Compile-time vector dimension
 * @param outputStream The output stream.
 * @param vector The vector to output.
 * @return Reference to the output stream.
 */
template <typename Type, size_t Dimension>
std::ostream &operator<<(std::ostream &outputStream,
                         const Vector<Type, Dimension> &vector) {
  outputStream << '(';
  for (size_t i = 0; i < Dimension; ++i) {
    outputStream << vector[i];
    if (i + 1 < Dimension) {
      outputStream << ", ";
    }
  }
  outputStream << ')';
  return outputStream;
}

} // namespace utility::math