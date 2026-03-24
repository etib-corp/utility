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

#pragma once

#include <cmath>
#include <numbers>
#include <stdexcept>

#include "utility/math/vector.hpp"

namespace utility::graphics {

/**
 * @brief Quaternion rotation represented as (x, y, z, w).
 *
 * The quaternion is stored in xyzw order, where (x, y, z) is the vector part
 * and w is the scalar part.
 */
class Rotation : public math::Vector<std::float_t, 4> {
public:
  /**
   * @brief Default constructor initializing identity quaternion (0, 0, 0, 1).
   */
  Rotation(void) : math::Vector<std::float_t, 4>({0.0F, 0.0F, 0.0F, 1.0F}) {}

  /**
   * @brief Construct from initializer list of four float values.
   * @param values The initializer list containing quaternion components in
   * xyzw order.
   * @throws std::invalid_argument if the list size is not 4.
   */
  Rotation(std::initializer_list<std::float_t> values)
      : math::Vector<std::float_t, 4>(values) {}

  /**
   * @brief Construct from explicit quaternion components.
   * @param x X component.
   * @param y Y component.
   * @param z Z component.
   * @param w W component.
   */
  Rotation(const std::float_t x, const std::float_t y, const std::float_t z,
           const std::float_t w)
      : math::Vector<std::float_t, 4>({x, y, z, w}) {}

  /**
   * @brief Construct by filling all quaternion components with the same value.
   * @param value Value assigned to x, y, z, and w.
   */
  explicit Rotation(const std::float_t value)
      : math::Vector<std::float_t, 4>(value) {}

  /**
   * @brief Copy constructor.
   * @param other The Rotation object to copy from.
   */
  Rotation(const Rotation &other) : math::Vector<std::float_t, 4>(other) {}

  /**
   * @brief Move constructor.
   * @param other The Rotation object to move from.
   */
  Rotation(Rotation &&other) noexcept
      : math::Vector<std::float_t, 4>(std::move(other)) {}

  /**
   * @brief Copy assignment operator.
   * @param other The Rotation object to copy from.
   * @return A reference to this Rotation object.
   */
  Rotation &operator=(const Rotation &other) {
    math::Vector<std::float_t, 4>::operator=(other);
    return *this;
  }

  /**
   * @brief Move assignment operator.
   * @param other The Rotation object to move from.
   * @return A reference to this Rotation object.
   */
  Rotation &operator=(Rotation &&other) noexcept {
    math::Vector<std::float_t, 4>::operator=(std::move(other));
    return *this;
  }

  /**
   * @brief Default destructor for Rotation.
   */
  ~Rotation(void) = default;

  /**
   * @brief Set the X component of the quaternion.
   * @param value The new X value.
   * @return A reference to this Rotation object for method chaining.
   */
  Rotation &setX(const std::float_t value) noexcept {
    (*this)[0] = value;
    return *this;
  }

  /**
   * @brief Get the X component of the quaternion.
   * @return The X value.
   */
  std::float_t getX(void) const noexcept { return (*this)[0]; }

  /**
   * @brief Set the Y component of the quaternion.
   * @param value The new Y value.
   * @return A reference to this Rotation object for method chaining.
   */
  Rotation &setY(const std::float_t value) noexcept {
    (*this)[1] = value;
    return *this;
  }

  /**
   * @brief Get the Y component of the quaternion.
   * @return The Y value.
   */
  std::float_t getY(void) const noexcept { return (*this)[1]; }

  /**
   * @brief Set the Z component of the quaternion.
   * @param value The new Z value.
   * @return A reference to this Rotation object for method chaining.
   */
  Rotation &setZ(const std::float_t value) noexcept {
    (*this)[2] = value;
    return *this;
  }

  /**
   * @brief Get the Z component of the quaternion.
   * @return The Z value.
   */
  std::float_t getZ(void) const noexcept { return (*this)[2]; }

  /**
   * @brief Set the W component of the quaternion.
   * @param value The new W value.
   * @return A reference to this Rotation object for method chaining.
   */
  Rotation &setW(const std::float_t value) noexcept {
    (*this)[3] = value;
    return *this;
  }

  /**
   * @brief Get the W component of the quaternion.
   * @return The W value.
   */
  std::float_t getW(void) const noexcept { return (*this)[3]; }

  /**
   * @brief Multiply by a quaternion delta and update this rotation.
   * @param delta Quaternion delta to apply.
   * @return A reference to this Rotation object for method chaining.
   */
  Rotation &rotate(const Rotation &delta) noexcept {
    *this = (*this) * delta;
    return *this;
  }

  /**
   * @brief Return a copy rotated by quaternion multiplication.
   * @param delta Quaternion delta to apply.
   * @return A new Rotation object with the delta applied.
   */
  Rotation rotated(const Rotation &delta) const noexcept {
    return (*this) * delta;
  }

  /**
   * @brief Quaternion Hamilton product.
   * @param other Right-hand quaternion.
   * @return Product quaternion.
   */
  Rotation operator*(const Rotation &other) const noexcept {
    const auto x1 = getX();
    const auto y1 = getY();
    const auto z1 = getZ();
    const auto w1 = getW();

    const auto x2 = other.getX();
    const auto y2 = other.getY();
    const auto z2 = other.getZ();
    const auto w2 = other.getW();

    return Rotation(w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2,
                    w1 * y2 - x1 * z2 + y1 * w2 + z1 * x2,
                    w1 * z2 + x1 * y2 - y1 * x2 + z1 * w2,
                    w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2);
  }

  /**
   * @brief Return the quaternion conjugate.
   * @return Conjugate quaternion.
   */
  Rotation conjugated(void) const noexcept {
    return Rotation(-getX(), -getY(), -getZ(), getW());
  }

  /**
   * @brief Conjugate this quaternion in place.
   * @return A reference to this Rotation object.
   */
  Rotation &conjugate(void) noexcept {
    (*this)[0] = -(*this)[0];
    (*this)[1] = -(*this)[1];
    (*this)[2] = -(*this)[2];
    return *this;
  }

  /**
   * @brief Return a normalized quaternion copy.
   * @return Normalized quaternion.
   * @throws std::runtime_error when quaternion norm is zero.
   */
  Rotation normalizedQuaternion(void) const {
    const auto normalizedBase = this->normalized();
    return Rotation(normalizedBase[0], normalizedBase[1], normalizedBase[2],
                    normalizedBase[3]);
  }

  /**
   * @brief Normalize this quaternion in place.
   * @return A reference to this Rotation object.
   * @throws std::runtime_error when quaternion norm is zero.
   */
  Rotation &normalizeQuaternion(void) {
    this->normalize();
    return *this;
  }

  /**
   * @brief Return the inverse quaternion.
   * @return Inverse quaternion.
   * @throws std::runtime_error when quaternion norm is zero.
   */
  Rotation inversed(void) const {
    const auto normSquared = this->magnitudeSquared();
    if (normSquared == 0.0F) {
      throw std::runtime_error("Cannot invert zero quaternion");
    }
    return Rotation(-getX() / normSquared, -getY() / normSquared,
                    -getZ() / normSquared, getW() / normSquared);
  }

  /**
   * @brief Invert this quaternion in place.
   * @return A reference to this Rotation object.
   * @throws std::runtime_error when quaternion norm is zero.
   */
  Rotation &inverse(void) {
    *this = inversed();
    return *this;
  }

  /**
   * @brief Build a quaternion from Euler angles in degrees.
   *
   * Angles are applied in X then Y then Z order.
   *
   * @param xDegrees Rotation around X axis in degrees.
   * @param yDegrees Rotation around Y axis in degrees.
   * @param zDegrees Rotation around Z axis in degrees.
   * @return Quaternion corresponding to the given Euler angles.
   */
  static Rotation fromEulerDegrees(const std::float_t xDegrees,
                                   const std::float_t yDegrees,
                                   const std::float_t zDegrees) {
    const auto degToRad = std::numbers::pi_v<std::float_t> / 180.0F;
    const auto hx = xDegrees * degToRad * 0.5F;
    const auto hy = yDegrees * degToRad * 0.5F;
    const auto hz = zDegrees * degToRad * 0.5F;

    const auto cx = std::cos(hx);
    const auto sx = std::sin(hx);
    const auto cy = std::cos(hy);
    const auto sy = std::sin(hy);
    const auto cz = std::cos(hz);
    const auto sz = std::sin(hz);

    return Rotation(sx * cy * cz - cx * sy * sz, cx * sy * cz + sx * cy * sz,
                    cx * cy * sz - sx * sy * cz, cx * cy * cz + sx * sy * sz);
  }
};
} // namespace utility::graphics