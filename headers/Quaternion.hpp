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

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace utility {

/**
 * @brief Wrapper class for quaternions used in 3D rotation
 *
 * Quaternions provide smooth rotation interpolation (SLERP) and avoid gimbal
 * lock.
 */
class Quaternion {
private:
  glm::quat _data;

public:
  /**
   * @brief Construct an identity quaternion (no rotation)
   */
  Quaternion(void);

  /**
   * @brief Construct from individual components
   *
   * @param w The scalar component
   * @param x The x vector component
   * @param y The y vector component
   * @param z The z vector component
   */
  Quaternion(float w, float x, float y, float z);

  /**
   * @brief Construct from an axis and angle
   *
   * @param axis The rotation axis
   * @param angle The rotation angle in radians
   */
  Quaternion(const glm::vec3 &axis, float angle);

  /**
   * @brief Construct from a glm::quat
   *
   * @param quaternion The glm::quat to copy
   */
  Quaternion(const glm::quat &quaternion);

  /**
   * @brief Default destructor
   */
  ~Quaternion(void) = default;

  /**
   * @brief Get the quaternion data
   *
   * @return const glm::quat& The quaternion
   */
  const glm::quat &getData(void) const;

  /**
   * @brief Set the quaternion data
   *
   * @param quaternion The new quaternion
   */
  void setData(const glm::quat &quaternion);

  /**
   * @brief Get the w component
   *
   * @return float The w component
   */
  float getW(void) const;

  /**
   * @brief Get the x component
   *
   * @return float The x component
   */
  float getX(void) const;

  /**
   * @brief Get the y component
   *
   * @return float The y component
   */
  float getY(void) const;

  /**
   * @brief Get the z component
   *
   * @return float The z component
   */
  float getZ(void) const;

  /**
   * @brief Normalize the quaternion
   */
  void normalize(void);

  /**
   * @brief Get a normalized copy of the quaternion
   *
   * @return Quaternion A normalized copy
   */
  Quaternion getNormalized(void) const;

  /**
   * @brief Get the conjugate of the quaternion
   *
   * @return Quaternion The conjugate
   */
  Quaternion conjugate(void) const;

  /**
   * @brief Get the inverse of the quaternion
   *
   * @return Quaternion The inverse
   */
  Quaternion inverse(void) const;

  /**
   * @brief Convert to a rotation matrix
   *
   * @return glm::mat4 The corresponding rotation matrix
   */
  glm::mat4 toMatrix(void) const;

  /**
   * @brief Spherical linear interpolation between two quaternions
   *
   * @param other The other quaternion
   * @param t The interpolation factor (0.0 to 1.0)
   * @return Quaternion The interpolated quaternion
   */
  Quaternion slerp(const Quaternion &other, float t) const;

  /**
   * @brief Quaternion multiplication operator
   *
   * @param other The other quaternion
   * @return Quaternion The result of the multiplication
   */
  Quaternion operator*(const Quaternion &other) const;

  /**
   * @brief Quaternion multiplication assignment operator
   *
   * @param other The other quaternion
   * @return Quaternion& Reference to this quaternion
   */
  Quaternion &operator*=(const Quaternion &other);

  /**
   * @brief Equality operator
   *
   * @param other The other quaternion
   * @return bool True if equal
   */
  bool operator==(const Quaternion &other) const;

  /**
   * @brief Inequality operator
   *
   * @param other The other quaternion
   * @return bool True if not equal
   */
  bool operator!=(const Quaternion &other) const;
};

/**
 * @brief Stream insertion operator for Quaternion
 */
std::ostream &operator<<(std::ostream &os, const Quaternion &quat);

} // namespace utility

#include <iostream>
