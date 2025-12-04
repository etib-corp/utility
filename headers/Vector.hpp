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

#include <cmath>
#include <ostream>

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

namespace utility {

/**
 * @brief Template Vector class that encapsulates glm::vec for type-safe vector
 * operations
 *
 * Supports 2D, 3D, and 4D vectors with compile-time dimension specification
 * @tparam T The scalar type (float, double, int, etc.)
 * @tparam Dim The dimension of the vector (2, 3, or 4)
 */
template <typename T, unsigned int Dim> class Vector {
  static_assert(Dim >= 2 && Dim <= 4, "Vector dimension must be 2, 3, or 4");

private:
  glm::tvec4<T> _data;

protected:
public:
  /**
   * @brief Construct a 2D vector
   *
   * @param x The x component
   * @param y The y component
   */
  Vector(T x, T y);

  /**
   * @brief Construct a 3D vector
   *
   * @param x The x component
   * @param y The y component
   * @param z The z component
   */
  Vector(T x, T y, T z);

  /**
   * @brief Construct a 4D vector
   *
   * @param x The x component
   * @param y The y component
   * @param z The z component
   * @param w The w component
   */
  Vector(T x, T y, T z, T w);

  /**
   * @brief Construct from a glm::tvec2
   *
   * @param vec The glm::tvec2 to copy
   */
  Vector(const glm::tvec2<T> &vec);

  /**
   * @brief Construct from a glm::tvec3
   *
   * @param vec The glm::tvec3 to copy
   */
  Vector(const glm::tvec3<T> &vec);

  /**
   * @brief Construct from a glm::tvec4
   *
   * @param vec The glm::tvec4 to copy
   */
  Vector(const glm::tvec4<T> &vec);

  /**
   * @brief Default destructor
   */
  ~Vector(void) = default;

  /**
   * @brief Get the dimension of the vector (2, 3, or 4)
   *
   * @return unsigned int The dimension
   */
  constexpr unsigned int getDimension(void) const { return Dim; }

  /**
   * @brief Set the x component
   *
   * @param x The x value
   */
  void setX(T x);

  /**
   * @brief Get the x component
   *
   * @return T The x value
   */
  T getX(void) const;

  /**
   * @brief Set the y component
   *
   * @param y The y value
   */
  void setY(T y);

  /**
   * @brief Get the y component
   *
   * @return T The y value
   */
  T getY(void) const;

  /**
   * @brief Set the z component (only for 3D and 4D vectors)
   *
   * @param z The z value
   */
  void setZ(T z);

  /**
   * @brief Get the z component (only for 3D and 4D vectors)
   *
   * @return T The z value
   */
  T getZ(void) const;

  /**
   * @brief Set the w component (only for 4D vectors)
   *
   * @param w The w value
   */
  void setW(T w);

  /**
   * @brief Get the w component (only for 4D vectors)
   *
   * @return T The w value
   */
  T getW(void) const;

  /**
   * @brief Calculate the magnitude (length) of the vector
   *
   * @return T The magnitude
   */
  T getMagnitude(void) const;

  /**
   * @brief Normalize the vector
   */
  void normalize(void);

  /**
   * @brief Get a normalized copy of the vector
   *
   * @return Vector A normalized copy
   */
  Vector getNormalized(void) const;

  /**
   * @brief Calculate the dot product with another vector
   *
   * @param other The other vector
   * @return T The dot product
   */
  T dot(const Vector &other) const;

  /**
   * @brief Calculate the cross product with another vector (only for 3D
   * vectors)
   *
   * @param other The other 3D vector
   * @return Vector The cross product as a 3D vector
   */
  Vector cross(const Vector &other) const;

  /**
   * @brief Convert to a glm::tvec2 (returns x, y)
   *
   * @return glm::tvec2<T> The 2D vector
   */
  glm::tvec2<T> toVec2(void) const;

  /**
   * @brief Convert to a glm::tvec3 (returns x, y, z or x, y, 0)
   *
   * @return glm::tvec3<T> The 3D vector
   */
  glm::tvec3<T> toVec3(void) const;

  /**
   * @brief Convert to a glm::tvec4 (returns x, y, z, w)
   *
   * @return glm::tvec4<T> The 4D vector
   */
  glm::tvec4<T> toVec4(void) const;

  /**
   * @brief Vector addition operator
   *
   * @param other The other vector
   * @return Vector The sum
   */
  Vector operator+(const Vector &other) const;

  /**
   * @brief Vector subtraction operator
   *
   * @param other The other vector
   * @return Vector The difference
   */
  Vector operator-(const Vector &other) const;

  /**
   * @brief Scalar multiplication operator
   *
   * @param scalar The scalar value
   * @return Vector The scaled vector
   */
  Vector operator*(T scalar) const;

  /**
   * @brief Scalar division operator
   *
   * @param scalar The scalar value
   * @return Vector The scaled vector
   */
  Vector operator/(T scalar) const;

  /**
   * @brief Addition assignment operator
   *
   * @param other The other vector
   * @return Vector& Reference to this vector
   */
  Vector &operator+=(const Vector &other);

  /**
   * @brief Subtraction assignment operator
   *
   * @param other The other vector
   * @return Vector& Reference to this vector
   */
  Vector &operator-=(const Vector &other);

  /**
   * @brief Scalar multiplication assignment operator
   *
   * @param scalar The scalar value
   * @return Vector& Reference to this vector
   */
  Vector &operator*=(T scalar);

  /**
   * @brief Scalar division assignment operator
   *
   * @param scalar The scalar value
   * @return Vector& Reference to this vector
   */
  Vector &operator/=(T scalar);

  /**
   * @brief Equality operator
   *
   * @param other The other vector
   * @return bool True if equal
   */
  bool operator==(const Vector &other) const;

  /**
   * @brief Inequality operator
   *
   * @param other The other vector
   * @return bool True if not equal
   */
  bool operator!=(const Vector &other) const;
};

// Template implementation

template <typename T, unsigned int Dim> Vector<T, Dim>::Vector(T x, T y) {
  static_assert(Dim == 2, "2-argument constructor is only for 2D vectors");
  _data = glm::tvec4<T>(x, y, T(0), T(0));
}

template <typename T, unsigned int Dim> Vector<T, Dim>::Vector(T x, T y, T z) {
  static_assert(Dim == 3, "3-argument constructor is only for 3D vectors");
  _data = glm::tvec4<T>(x, y, z, T(0));
}

template <typename T, unsigned int Dim>
Vector<T, Dim>::Vector(T x, T y, T z, T w) {
  static_assert(Dim == 4, "4-argument constructor is only for 4D vectors");
  _data = glm::tvec4<T>(x, y, z, w);
}

template <typename T, unsigned int Dim>
Vector<T, Dim>::Vector(const glm::tvec2<T> &vec) {
  static_assert(Dim == 2, "glm::tvec2 constructor is only for 2D vectors");
  _data = glm::tvec4<T>(vec.x, vec.y, T(0), T(0));
}

template <typename T, unsigned int Dim>
Vector<T, Dim>::Vector(const glm::tvec3<T> &vec) {
  static_assert(Dim == 3, "glm::tvec3 constructor is only for 3D vectors");
  _data = glm::tvec4<T>(vec.x, vec.y, vec.z, T(0));
}

template <typename T, unsigned int Dim>
Vector<T, Dim>::Vector(const glm::tvec4<T> &vec) {
  static_assert(Dim == 4, "glm::tvec4 constructor is only for 4D vectors");
  _data = vec;
}

template <typename T, unsigned int Dim> void Vector<T, Dim>::setX(T x) {
  _data.x = x;
}

template <typename T, unsigned int Dim> T Vector<T, Dim>::getX(void) const {
  return _data.x;
}

template <typename T, unsigned int Dim> void Vector<T, Dim>::setY(T y) {
  _data.y = y;
}

template <typename T, unsigned int Dim> T Vector<T, Dim>::getY(void) const {
  return _data.y;
}

template <typename T, unsigned int Dim> void Vector<T, Dim>::setZ(T z) {
  _data.z = z;
}

template <typename T, unsigned int Dim> T Vector<T, Dim>::getZ(void) const {
  return _data.z;
}

template <typename T, unsigned int Dim> void Vector<T, Dim>::setW(T w) {
  _data.w = w;
}

template <typename T, unsigned int Dim> T Vector<T, Dim>::getW(void) const {
  return _data.w;
}

template <typename T, unsigned int Dim>
T Vector<T, Dim>::getMagnitude(void) const {
  glm::tvec4<T> temp = _data;
  temp.w = T(0); // Ignore w component for magnitude calculation
  return glm::length(temp);
}

template <typename T, unsigned int Dim> void Vector<T, Dim>::normalize(void) {
  T magnitude = getMagnitude();
  if (magnitude > T(0)) {
    _data.x /= magnitude;
    _data.y /= magnitude;
    _data.z /= magnitude;
  }
}

template <typename T, unsigned int Dim>
Vector<T, Dim> Vector<T, Dim>::getNormalized(void) const {
  Vector normalized = *this;
  normalized.normalize();
  return normalized;
}

template <typename T, unsigned int Dim>
T Vector<T, Dim>::dot(const Vector &other) const {
  T result = _data.x * other._data.x + _data.y * other._data.y;

  if (Dim >= 3) {
    result += _data.z * other._data.z;
  }

  if (Dim == 4) {
    result += _data.w * other._data.w;
  }

  return result;
}

template <typename T, unsigned int Dim>
Vector<T, Dim> Vector<T, Dim>::cross(const Vector &other) const {
  static_assert(Dim == 3, "Cross product is only defined for 3D vectors");

  glm::tvec3<T> a(_data.x, _data.y, _data.z);
  glm::tvec3<T> b(other._data.x, other._data.y, other._data.z);
  glm::tvec3<T> result = glm::cross(a, b);

  return Vector(result);
}

template <typename T, unsigned int Dim>
glm::tvec2<T> Vector<T, Dim>::toVec2(void) const {
  static_assert(Dim >= 2, "Cannot convert vector with dimension < 2 to vec2");
  return glm::tvec2<T>(_data.x, _data.y);
}

template <typename T, unsigned int Dim>
glm::tvec3<T> Vector<T, Dim>::toVec3(void) const {
  static_assert(Dim >= 3, "Cannot convert vector with dimension < 3 to vec3");
  return glm::tvec3<T>(_data.x, _data.y, _data.z);
}

template <typename T, unsigned int Dim>
glm::tvec4<T> Vector<T, Dim>::toVec4(void) const {
  static_assert(Dim == 4, "Cannot convert non-4D vector to vec4");
  return _data;
}

template <typename T, unsigned int Dim>
Vector<T, Dim> Vector<T, Dim>::operator+(const Vector &other) const {
  Vector result = *this;
  result += other;
  return result;
}

template <typename T, unsigned int Dim>
Vector<T, Dim> Vector<T, Dim>::operator-(const Vector &other) const {
  Vector result = *this;
  result -= other;
  return result;
}

template <typename T, unsigned int Dim>
Vector<T, Dim> Vector<T, Dim>::operator*(T scalar) const {
  Vector result = *this;
  result *= scalar;
  return result;
}

template <typename T, unsigned int Dim>
Vector<T, Dim> Vector<T, Dim>::operator/(T scalar) const {
  Vector result = *this;
  result /= scalar;
  return result;
}

template <typename T, unsigned int Dim>
Vector<T, Dim> &Vector<T, Dim>::operator+=(const Vector &other) {
  _data.x += other._data.x;
  _data.y += other._data.y;

  if (Dim >= 3) {
    _data.z += other._data.z;
  }

  if (Dim == 4) {
    _data.w += other._data.w;
  }

  return *this;
}

template <typename T, unsigned int Dim>
Vector<T, Dim> &Vector<T, Dim>::operator-=(const Vector &other) {
  _data.x -= other._data.x;
  _data.y -= other._data.y;

  if (Dim >= 3) {
    _data.z -= other._data.z;
  }

  if (Dim == 4) {
    _data.w -= other._data.w;
  }

  return *this;
}

template <typename T, unsigned int Dim>
Vector<T, Dim> &Vector<T, Dim>::operator*=(T scalar) {
  _data.x *= scalar;
  _data.y *= scalar;
  if (Dim >= 3) {
    _data.z *= scalar;
  }
  if (Dim == 4) {
    _data.w *= scalar;
  }
  return *this;
}

template <typename T, unsigned int Dim>
Vector<T, Dim> &Vector<T, Dim>::operator/=(T scalar) {
  if (scalar != T(0)) {
    _data.x /= scalar;
    _data.y /= scalar;
    if (Dim >= 3) {
      _data.z /= scalar;
    }
    if (Dim == 4) {
      _data.w /= scalar;
    }
  }
  return *this;
}

template <typename T, unsigned int Dim>
bool Vector<T, Dim>::operator==(const Vector &other) const {
  const T epsilon = T(1e-6);

  if (std::abs(_data.x - other._data.x) > epsilon ||
      std::abs(_data.y - other._data.y) > epsilon) {
    return false;
  }

  if (Dim >= 3 && std::abs(_data.z - other._data.z) > epsilon) {
    return false;
  }

  if (Dim == 4 && std::abs(_data.w - other._data.w) > epsilon) {
    return false;
  }

  return true;
}

template <typename T, unsigned int Dim>
bool Vector<T, Dim>::operator!=(const Vector &other) const {
  return !(*this == other);
}

// Type aliases for convenience
using Vector2f = Vector<float, 2>;
using Vector3f = Vector<float, 3>;
using Vector4f = Vector<float, 4>;
using Vector2d = Vector<double, 2>;
using Vector3d = Vector<double, 3>;
using Vector4d = Vector<double, 4>;
using Vector2i = Vector<int, 2>;
using Vector3i = Vector<int, 3>;
using Vector4i = Vector<int, 4>;

/**
 * @brief Stream insertion operator for Vector
 */
template <typename T, unsigned int Dim>
std::ostream &operator<<(std::ostream &os, const Vector<T, Dim> &vec);

} // namespace utility

#include <iostream>
