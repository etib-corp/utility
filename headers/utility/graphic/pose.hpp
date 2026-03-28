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

#include <concepts>

#include "utility/graphic/orientation.hpp"
#include "utility/graphic/position.hpp"

namespace utility::graphic {

/**
 * @brief Concept to constrain pose component type.
 * @tparam Type Candidate component type.
 */
template <typename Type>
concept CanBePoseComponent =
    CanBePositionComponent<Type> && CanBeOrientationComponent<Type>;

/**
 * @brief Template class representing a pose (Position + Orientation).
 *
 * A pose encodes both the spatial Position and the Orientation of an object in
 * 3D space.
 *
 * @tparam PoseComponentType Floating-point type for Position and Orientation
 * components.
 */
template <CanBePoseComponent PoseComponentType> class Pose {
private:
  /**
   * @brief Position component of the pose.
   */
  Position<PoseComponentType> _position;

  /**
   * @brief Orientation component of the pose.
   */
  Orientation<PoseComponentType> _orientation;

public:
  /**
   * @brief Default constructor (zero position, identity orientation).
   */
  Pose(void) : _position(), _orientation() {}
  /**
   * @brief Construct a pose from position and orientation.
   * @param position The position component.
   * @param orientation The orientation component.
   */
  Pose(const Position<PoseComponentType> &position,
       const Orientation<PoseComponentType> &orientation)
      : _position(position), _orientation(orientation) {}

  /**
   * @brief Copy constructor.
   * @param other The Pose object to copy from.
   */
  Pose(const Pose &other) = default;

  /**
   * @brief Move constructor.
   * @param other The Pose object to move from.
   */
  Pose(Pose &&other) noexcept = default;

  /**
   * @brief Copy assignment operator.
   * @param other The Pose object to copy from.
   * @return A reference to this Pose object.
   */
  Pose &operator=(const Pose &other) = default;

  /**
   * @brief Move assignment operator.
   * @param other The Pose object to move from.
   * @return A reference to this Pose object.
   */
  Pose &operator=(Pose &&other) noexcept = default;

  /**
   * @brief Default destructor for Pose.
   */
  ~Pose(void) = default;

  /**
   * @brief Set the position component.
   * @param position New position value.
   * @return Reference to this object for chaining.
   */
  Pose &setPosition(const Position<PoseComponentType> &position) noexcept {
    _position = position;
    return *this;
  }

  /**
   * @brief Get the position component.
   * @return Const reference to the position.
   */
  const Position<PoseComponentType> &getPosition(void) const noexcept {
    return _position;
  }

  /**
   * @brief Set the orientation component.
   * @param orientation New orientation value.
   * @return Reference to this object for chaining.
   */
  Pose &
  setOrientation(const Orientation<PoseComponentType> &orientation) noexcept {
    _orientation = orientation;
    return *this;
  }

  /**
   * @brief Get the orientation component.
   * @return Const reference to the orientation.
   */
  const Orientation<PoseComponentType> &getOrientation(void) const noexcept {
    return _orientation;
  }
};

/**
 * @brief Type alias for single-precision pose component.
 */
using PoseF = Pose<float>;

/**
 * @brief Type alias for double-precision pose component.
 */
using PoseD = Pose<double>;

} // namespace utility::graphic
