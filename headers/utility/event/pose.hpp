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

#include "utility/math/vector.hpp"

#include "utility/graphics/position.hpp"
#include "utility/graphics/rotation.hpp"

namespace utility::event {

/**
 * @brief Combined position and rotation pose used by XR events.
 */
class Pose {
private:
  utility::graphics::Position _position; /**< Position component of the pose */
  utility::graphics::Rotation _rotation; /**< Rotation component of the pose */

public:
  /**
   * @brief Default constructor initializing position to (0, 0, 0) and rotation
   * to identity.
   */
  Pose(void) : _position(0.0f), _rotation() {}

  /**
   * @brief Construct a Pose with specified position and rotation.
   * @param position The position component of the pose.
   * @param rotation The rotation component of the pose.
   */
  Pose(const utility::graphics::Position &position,
       const utility::graphics::Rotation &rotation)
      : _position(position), _rotation(rotation) {}

  /**
   * @brief Get the position component of the pose.
   * @return The position of the pose.
   */
  const utility::graphics::Position &getPosition(void) const noexcept {
    return _position;
  }

  /**
   * @brief Get the rotation component of the pose.
   * @return The rotation of the pose.
   */
  const utility::graphics::Rotation &getRotation(void) const noexcept {
    return _rotation;
  }

  /**
   * @brief Set the position component of the pose.
   * @param position The new position to set.
   * @return Reference to this Pose for method chaining.
   */
  Pose &setPosition(const utility::graphics::Position &position) noexcept {
    _position = position;
    return *this;
  }

  /**
   * @brief Set the rotation component of the pose.
   * @param rotation The new rotation to set.
   * @return Reference to this Pose for method chaining.
   */
  Pose &setRotation(const utility::graphics::Rotation &rotation) noexcept {
    _rotation = rotation;
    return *this;
  }
};

} // namespace utility::event