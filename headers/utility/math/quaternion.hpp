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
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

#include <glm/gtx/quaternion.hpp>

namespace utility::math {

using glm::toMat4;

/**
 * @brief Concept to constrain quaternion component type.
 * @tparam Type Candidate component type.
 */
template <typename Type>
concept CanBeQuaternionComponent = std::is_floating_point_v<Type>;

/**
 * @brief Quaternion class inheriting from glm::qua.
 *
 * @tparam QuaternionComponentType Floating-point type for quaternion
 * components.
 */
template <CanBeQuaternionComponent QuaternionComponentType>
class Quaternion : public glm::qua<QuaternionComponentType> {
public:
  /**
   * @brief Default constructor (identity quaternion).
   */
  Quaternion()
      : glm::qua<QuaternionComponentType>(
            QuaternionComponentType(1), QuaternionComponentType(0),
            QuaternionComponentType(0), QuaternionComponentType(0)) {}

  /**
   * @brief Construct from explicit components (w, x, y, z).
   * @param w W component.
   * @param x X component.
   * @param y Y component.
   * @param z Z component.
   */
  Quaternion(QuaternionComponentType w, QuaternionComponentType x,
             QuaternionComponentType y, QuaternionComponentType z)
      : glm::qua<QuaternionComponentType>(w, x, y, z) {}

  /**
   * @brief Construct from a GLM quaternion.
   * @param q Source quaternion.
   */
  Quaternion(const glm::qua<QuaternionComponentType> &q)
      : glm::qua<QuaternionComponentType>(q) {}

  /**
   * @brief Copy constructor.
   * @param other The Quaternion object to copy from.
   */
  Quaternion(const Quaternion &other) = default;

  /**
   * @brief Move constructor.
   * @param other The Quaternion object to move from.
   */
  Quaternion(Quaternion &&other) noexcept = default;

  /**
   * @brief Copy assignment operator.
   * @param other The Quaternion object to copy from.
   * @return A reference to this Quaternion object.
   */
  Quaternion &operator=(const Quaternion &other) = default;

  /**
   * @brief Move assignment operator.
   * @param other The Quaternion object to move from.
   * @return A reference to this Quaternion object.
   */
  Quaternion &operator=(Quaternion &&other) noexcept = default;

  /**
   * @brief Default destructor for Quaternion.
   */
  ~Quaternion() = default;
};

/**
 * @brief Type alias for single-precision quaternion.
 */
using QuaternionF = Quaternion<float>;

/**
 * @brief Type alias for double-precision quaternion.
 */
using QuaternionD = Quaternion<double>;

} // namespace utility::math
