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
#include <concepts>
#include <numbers>

#include "utility/math/vector.hpp"

namespace utility::graphic {

/**
 * @brief Concept to constrain scale component type.
 * @tparam Type Candidate component type.
 */
template <typename Type>
concept CanBeScaleComponent = math::CanBeVectorComponent<Type>;

/**
 * @brief Scale in 3D space represented as a vector of three ScaleComponentType components
 * (x, y, z).
 *
 * This class provides a 3D scale vector, typically used for scaling objects in
 * 3D graphic. It supports construction from initializer lists, GLM vectors, and
 * provides methods for component access and scaling operations.
 *
 * @tparam ScaleComponentType The type of the scale components (e.g., float,
 * double).
 */
template <CanBeScaleComponent ScaleComponentType>
class Scale : public math::Vector<ScaleComponentType, 3> {
public:
  /**
   * @brief Default constructor initializing scale to (1, 1, 1).
   */
  Scale(void) : math::Vector<ScaleComponentType, 3>({ScaleComponentType{1.0F}, ScaleComponentType{1.0F}, ScaleComponentType{1.0F}}) {}

  /**
   * @brief Construct from three ScaleComponentType values (x, y, z).
   * @param x X component.
   * @param y Y component.
   * @param z Z component.
   */
  Scale(ScaleComponentType x, ScaleComponentType y,
           ScaleComponentType z)
      : math::Vector<ScaleComponentType, 3>({x, y, z}) {}

  /**
   * @brief Construct from initializer list of three ScaleComponentType values.
   * @param values The initializer list containing x, y, z components.
   * @throws std::invalid_argument if the list size is not 3.
   */
  Scale(std::initializer_list<ScaleComponentType> values)
      : math::Vector<ScaleComponentType, 3>(1.0F, 1.0F, 1.0F) {
    if (values.size() != 3) {
      throw std::invalid_argument("Scale requires exactly three components");
    }
    const auto it = values.begin();
    this->x = *it;
    this->y = *(it + 1);
    this->z = *(it + 2);
  }

  /**
   * @brief Construct by filling all components with the same ScaleComponentType value.
   * @param value The ScaleComponentType value to fill all components with.
   */
  explicit Scale(ScaleComponentType value)
      : math::Vector<ScaleComponentType, 3>(value, value, value) {}

  /**
   * @brief Construct from a GLM vector.
   * @param value Source vector.
   */
  Scale(const std::initializer_list<ScaleComponentType> &value)
      : math::Vector<ScaleComponentType, 3>(value) {}

  /**
   * @brief Copy constructor.
   * @param other The Scale object to copy from.
   */
  Scale(const Scale &other) = default;

  /**
   * @brief Move constructor.
   * @param other The Scale object to move from.
   */
  Scale(Scale &&other) noexcept = default;

  /**
   * @brief Copy assignment operator.
   * @param other The Scale object to copy from.
   * @return A reference to this Scale object.
   */
  Scale &operator=(const Scale &other) = default;

  /**
   * @brief Move assignment operator.
   * @param other The Scale object to move from.
   * @return A reference to this Scale object.
   */
  Scale &operator=(Scale &&other) noexcept = default;

  /**
   * @brief Default destructor for Scale.
   */
  ~Scale(void) = default;

  /**
   * @brief Set the X component of the scale.
   * @param value The new X value.
   * @return A reference to this Scale object for method chaining.
   */
  Scale &setX(const ScaleComponentType value) noexcept {
    this->x = value;
    return *this;
  }

  /**
   * @brief Get the X component of the scale.
   * @return The X value.
   */
  ScaleComponentType getX(void) const noexcept { return this->x; }

  /**
   * @brief Set the Y component of the scale.
   * @param value The new Y value.
   * @return A reference to this Scale object for method chaining.
   */
  Scale &setY(const ScaleComponentType value) noexcept {
    this->y = value;
    return *this;
  }

  /**
   * @brief Get the Y component of the scale.
   * @return The Y value.
   */
  ScaleComponentType getY(void) const noexcept { return this->y; }

  /**
   * @brief Set the Z component of the scale.
   * @param value The new Z value.
   * @return A reference to this Scale object for method chaining.
   */
  Scale &setZ(const ScaleComponentType value) noexcept {
    this->z = value;
    return *this;
  }

  /**
   * @brief Get the Z component of the scale.
   * @return The Z value.
   */
  ScaleComponentType getZ(void) const noexcept { return this->z; }

  /**
   * @brief Scale this object by another scale (component-wise multiplication).
   * @param factor Scale factor to multiply by.
   * @return A reference to this Scale object for method chaining.
   */
  Scale &scaleBy(const Scale &factor) noexcept {
    this->x *= factor.x;
    this->y *= factor.y;
    this->z *= factor.z;
    return *this;
  }

  /**
   * @brief Return a scaled copy of this object (component-wise multiplication).
   * @param factor Scale factor to multiply by.
   * @return A new scaled Scale object.
   */
  Scale scaled(const Scale &factor) const noexcept {
    Scale result(*this);
    result.scaleBy(factor);
    return result;
  }
};

/**
 * @brief Type alias for single-precision scale component.
 */
using ScaleF = Scale<float>;

/**
 * @brief Type alias for double-precision scale component.
 */
using ScaleD = Scale<double>;

} // namespace utility::graphic
