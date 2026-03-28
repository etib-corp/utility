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

#include <type_traits>

#include "utility/math/matrix.hpp"
#include "utility/math/quaternion.hpp"
#include "utility/math/vector.hpp"

namespace utility::graphic {

/**
 * @brief Concept to constrain orientation component type.
 * @tparam Type Candidate component type.
 */
template <typename Type>
concept CanBeOrientationComponent = std::is_floating_point_v<Type>;

/**
 * @brief Represents the current 3D orientation (pose) of an object or camera.
 * @tparam OrientationComponentType Floating-point type for quaternion
 * components.
 *
 * @note An orientation describes how the object is rotated in space relative to
 * a reference frame (e.g. world or parent), but does not describe the
 * history of how it got there.
 *
 */
template <CanBeOrientationComponent OrientationComponentType>
class Orientation {
private:
  /**
   * @brief Quaternion representing the orientation.
   *
   * @note Stores the current orientation as a unit quaternion (xyzw order).
   */
  utility::math::Quaternion<OrientationComponentType> _quaternion;

public:
  /**
   * @brief Default constructor (identity orientation).
   *
   * @note Initializes to no rotation (facing -Z, up +Y).
   */
  Orientation(void)
      : _quaternion(OrientationComponentType(1), OrientationComponentType(0),
                    OrientationComponentType(0), OrientationComponentType(0)) {}

  /**
   * @brief Construct from a GLM quaternion.
   * @param quaternion Quaternion to use for orientation.
   */
  explicit Orientation(
      const utility::math::Quaternion<OrientationComponentType> &quaternion)
      : _quaternion(quaternion) {}

  /**
   * @brief Construct from explicit quaternion components (xyzw order).
   * @param x X component.
   * @param y Y component.
   * @param z Z component.
   * @param w W component.
   */
  Orientation(OrientationComponentType x, OrientationComponentType y,
              OrientationComponentType z, OrientationComponentType w)
      : _quaternion(w, x, y, z) {}

  /**
   * @brief Copy constructor.
   * @param other The Orientation object to copy from.
   */
  Orientation(const Orientation &other) = default;

  /**
   * @brief Move constructor.
   * @param other The Orientation object to move from.
   */
  Orientation(Orientation &&other) noexcept = default;

  /**
   * @brief Copy assignment operator.
   * @param other The Orientation object to copy from.
   * @return A reference to this Orientation object.
   */
  Orientation &operator=(const Orientation &other) = default;

  /**
   * @brief Move assignment operator.
   * @param other The Orientation object to move from.
   * @return A reference to this Orientation object.
   */
  Orientation &operator=(Orientation &&other) noexcept = default;

  /**
   * @brief Default destructor for Orientation.
   */
  ~Orientation(void) = default;

  /**
   * @brief Set the orientation from a quaternion.
   * @param quaternion New quaternion value.
   * @return Reference to this object for chaining.
   */
  Orientation &
  setQuaternion(const utility::math::Quaternion<OrientationComponentType>
                    &quaternion) noexcept {
    _quaternion = quaternion;
    return *this;
  }

  /**
   * @brief Get the underlying quaternion.
   * @return Const reference to the internal GLM quaternion.
   */
  const utility::math::Quaternion<OrientationComponentType> &
  getQuaternion(void) const noexcept {
    return _quaternion;
  }

  /**
   * @brief Get the forward (Z-) axis in world space.
   * @return Forward direction as a 3D vector.
   */
  utility::math::Vector<OrientationComponentType, 3>
  getForward(void) const noexcept {
    return _quaternion * utility::math::Vector<OrientationComponentType, 3>(
                             OrientationComponentType(0),
                             OrientationComponentType(0),
                             OrientationComponentType(-1));
  }

  /**
   * @brief Get the up (Y+) axis in world space.
   * @return Up direction as a 3D vector.
   */
  utility::math::Vector<OrientationComponentType, 3>
  getUp(void) const noexcept {
    return _quaternion * utility::math::Vector<OrientationComponentType, 3>(
                             OrientationComponentType(0),
                             OrientationComponentType(1),
                             OrientationComponentType(0));
  }

  /**
   * @brief Get the right (X+) axis in world space.
   * @return Right direction as a 3D vector.
   */
  utility::math::Vector<OrientationComponentType, 3>
  getRight(void) const noexcept {
    return _quaternion * utility::math::Vector<OrientationComponentType, 3>(
                             OrientationComponentType(1),
                             OrientationComponentType(0),
                             OrientationComponentType(0));
  }

  /**
   * @brief Transform a point from local to world space.
   * @param local Point in local space.
   * @return Transformed point in world space.
   */
  utility::math::Vector<OrientationComponentType, 3> transformPoint(
      const utility::math::Vector<OrientationComponentType, 3> &local)
      const noexcept {
    return _quaternion * local;
  }

  /**
   * @brief Combine with another orientation (parent * this).
   * @param parent Parent orientation to combine with.
   * @return Combined orientation (parent * this).
   */
  Orientation combined(const Orientation &parent) const noexcept {
    return Orientation(parent._quaternion * _quaternion);
  }

  /**
   * @brief Convert the orientation to a 4x4 rotation matrix.
   * @return Rotation matrix corresponding to this orientation.
   *
   * @note The resulting matrix can be used for transforming vertices or
   * constructing view matrices, but does not include translation or scaling
   * components. It represents only the rotation defined by the quaternion.
   */
  math::Matrix4x4F toRotationMatrix(void) const noexcept {
    return math::Matrix4x4F(math::toMat4(_quaternion));
  }
};

/**
 * @brief Type alias for single-precision orientation component.
 */
using OrientationF = Orientation<float>;

/**
 * @brief Type alias for double-precision orientation component.
 */
using OrientationD = Orientation<double>;

} // namespace utility::graphic
