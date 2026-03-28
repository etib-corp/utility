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

#include <glm/geometric.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace utility::math {

using glm::cross;
using glm::distance;
using glm::dot;
using glm::faceforward;
using glm::length;
using glm::normalize;
using glm::reflect;
using glm::refract;

/**
 * @brief Concept to constrain vector component type.
 * @tparam Type Candidate component type.
 */
template <typename Type>
concept CanBeVectorComponent = std::is_floating_point_v<Type>;

/**
 * @brief 3D vector class inheriting from glm::vec3.
 *
 * @tparam Type Floating-point type for vector components.
 */
template <typename VectorComponentType, std::size_t VectorDimension,
          typename =
              std::enable_if_t<std::is_floating_point_v<VectorComponentType> &&
                               (VectorDimension > 0) && (VectorDimension <= 4)>>
class Vector : public glm::vec<VectorDimension, VectorComponentType> {
public:
  /**
   * @brief Default constructor initializing vector values to zero.
   */
  Vector(void) : glm::vec<VectorDimension, VectorComponentType>(0) {}

  /**
   * @brief Construct from initializer list of float values.
   * @param values The initializer list containing vector components.
   * @throws std::invalid_argument if the list size does not match the vector
   * dimension.
   */
  Vector(std::initializer_list<VectorComponentType> values) {
    if (values.size() != VectorDimension) {
      throw std::invalid_argument("Vector requires exactly " +
                                  std::to_string(VectorDimension) +
                                  " components");
    }
    const auto it = values.begin();
    for (std::size_t i = 0; i < VectorDimension; ++i) {
      (*this)[i] = *(it + i);
    }
  }

  /**
   * @brief Construct by filling all components with the same float value.
   * @param value The float value to fill all components with.
   */
  explicit Vector(VectorComponentType value)
      : glm::vec<VectorDimension, VectorComponentType>(value) {}
};

/**
 * @brief Type alias for 2D single-precision vector.
 */
using Vector2F = Vector<float, 2>;

/**
 * @brief Type alias for 2D double-precision vector.
 */
using Vector2D = Vector<double, 2>;

/**
 * @brief Type alias for 3D single-precision vector.
 */
using Vector3F = Vector<float, 3>;

/**
 * @brief Type alias for 3D double-precision vector.
 */
using Vector3D = Vector<double, 3>;

/**
 * @brief Type alias for 4D single-precision vector.
 */
using Vector4F = Vector<float, 4>;

/**
 * @brief Type alias for 4D double-precision vector.
 */
using Vector4D = Vector<double, 4>;

} // namespace utility::math
