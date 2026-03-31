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
 * @brief Represents the current 3D orientation (pose) of an object or view.
 * @tparam OrientationComponentType Floating-point type for quaternion
 * components.
 *
 * @note An orientation describes how the object is rotated in space relative to
 * a reference frame (e.g. world or parent), but does not describe the
 * history of how it got there.
 *
 */
template <CanBeOrientationComponent OrientationComponentType>
class Orientation : public utility::math::Quaternion<OrientationComponentType> {
public:
  /**
   * @brief Default constructor (identity orientation).
   *
   * @note Initializes to no rotation (facing -Z, up +Y).
   */
  Orientation(void)
      : utility::math::Quaternion<OrientationComponentType>(
            OrientationComponentType(1), OrientationComponentType(0),
            OrientationComponentType(0), OrientationComponentType(0)) {}

  /**
   * @brief Construct by filling all components with the same
   * OrientationComponentType value.
   * @param value The OrientationComponentType value to fill all components
   * with.
   */
  explicit Orientation(OrientationComponentType value)
      : utility::math::Quaternion<OrientationComponentType>(value, value, value,
                                                            value) {}

  /**
   * @brief Construct from a quaternion.
   * @param quaternion Quaternion to use for orientation.
   */
  explicit Orientation(
      const utility::math::Quaternion<OrientationComponentType> &quaternion)
      : utility::math::Quaternion<OrientationComponentType>(quaternion) {}

  /**
   * @brief Construct from explicit quaternion components (xyzw order).
   * @param x X component.
   * @param y Y component.
   * @param z Z component.
   * @param w W component.
   */
  Orientation(OrientationComponentType x, OrientationComponentType y,
              OrientationComponentType z, OrientationComponentType w)
      : utility::math::Quaternion<OrientationComponentType>(w, x, y, z) {}

  /**
   * @brief Construct from initializer list of three PositionComponentType
   * values.
   * @param values The initializer list containing x, y, z components.
   * @throws std::invalid_argument if the list size is not 3.
   */
  Orientation(std::initializer_list<OrientationComponentType> values)
      : utility::math::Quaternion<OrientationComponentType>(
            OrientationComponentType(1), OrientationComponentType(0),
            OrientationComponentType(0), OrientationComponentType(0)) {
    if (values.size() != 4) {
      throw std::invalid_argument(
          "Orientation requires exactly four components");
    }
    const auto it = values.begin();
    this->w() = *it;
    this->x() = *(it + 1);
    this->y() = *(it + 2);
    this->z() = *(it + 3);
  }

  /**
   * @brief Construct from a const initializer list of three
   * PositionComponentType values.
   * @param value Source vector.
   */
  Orientation(const std::initializer_list<OrientationComponentType> &value)
      : utility::math::Quaternion<OrientationComponentType>(value) {}

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
   * @brief Get the forward (Z-) axis in world space.
   * @return Forward direction as a 3D vector.
   */
  utility::math::Vector<OrientationComponentType, 3>
  getForward(void) const noexcept {
    return utility::math::Quaternion<OrientationComponentType>(
               this->w(), this->x(), this->y(), this->z()) *
           utility::math::Vector<OrientationComponentType, 3>(
               OrientationComponentType(0), OrientationComponentType(0),
               OrientationComponentType(-1));
  }

  /**
   * @brief Get the up (Y+) axis in world space.
   * @return Up direction as a 3D vector.
   */
  utility::math::Vector<OrientationComponentType, 3>
  getUp(void) const noexcept {
    return utility::math::Quaternion<OrientationComponentType>(
               this->w(), this->x(), this->y(), this->z()) *
           utility::math::Vector<OrientationComponentType, 3>(
               OrientationComponentType(0), OrientationComponentType(1),
               OrientationComponentType(0));
  }

  /**
   * @brief Get the right (X+) axis in world space.
   * @return Right direction as a 3D vector.
   */
  utility::math::Vector<OrientationComponentType, 3>
  getRight(void) const noexcept {
    return utility::math::Quaternion<OrientationComponentType>(
               this->w(), this->x(), this->y(), this->z()) *
           utility::math::Vector<OrientationComponentType, 3>(
               OrientationComponentType(1), OrientationComponentType(0),
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
    return utility::math::Quaternion<OrientationComponentType>(
               this->w(), this->x(), this->y(), this->z()) *
           local;
  }

  /**
   * @brief Combine with another orientation (parent * this).
   * @param parent Parent orientation to combine with.
   * @return Combined orientation (parent * this).
   */
  Orientation combined(const Orientation &parent) const noexcept {
    return Orientation(utility::math::Quaternion<OrientationComponentType>(
                           parent.w(), parent.x(), parent.y(), parent.z()) *
                       utility::math::Quaternion<OrientationComponentType>(
                           this->w(), this->x(), this->y(), this->z()));
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
    return math::Matrix4x4F(
        math::toMat4(utility::math::Quaternion<OrientationComponentType>(
            this->w(), this->x(), this->y(), this->z())));
  }

  /**
   * @brief Get the normalized quaternion representing this orientation.
   * @return Normalized quaternion.
   *
   * @note This is useful for ensuring the quaternion is a valid rotation
   * without scaling. It can be used for interpolation or when converting to
   * other representations.
   */
  utility::math::Quaternion<OrientationComponentType>
  normalizedQuaternion(void) const noexcept {
    return utility::math::Quaternion<OrientationComponentType>(this->w, this->x,
                                                               this->y, this->z)
        .normalized();
  }

  /**
   * @brief Get a normalized Orientation object representing this orientation.
   * @return Normalized Orientation.
   *
   * @note This is a convenience method that returns a new Orientation object
   * with the quaternion normalized. It can be used for interpolation or when
   * converting to other representations while ensuring the rotation is valid.
   */
  Orientation<OrientationComponentType>
  normalizedOrientation(void) const noexcept {
    return Orientation<OrientationComponentType>(this->normalizedQuaternion());
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
