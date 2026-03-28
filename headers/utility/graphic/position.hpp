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
#include <type_traits>
#include <utility>

#include "utility/math/vector.hpp"

namespace utility::graphic {

/**
 * @brief Concept to constrain position component type.
 * @tparam Type Candidate component type.
 */
template <typename Type>
concept CanBePositionComponent = math::CanBeVectorComponent<Type>;

/**
 * @brief Position in 3D space represented as a vector of three float components
 * (x, y, z).
 */
template <CanBePositionComponent PositionComponentType>
class Position : public math::Vector<PositionComponentType, 3> {
public:
  /**
   * @brief Default constructor initializing position to (0, 0, 0).
   */
  Position(void)
      : math::Vector<PositionComponentType, 3>(PositionComponentType{0}) {}

  /**
   * @brief Construct from three float values (x, y, z).
   * @param x X component.
   * @param y Y component.
   * @param z Z component.
   */
  Position(PositionComponentType x, PositionComponentType y,
           PositionComponentType z)
      : math::Vector<PositionComponentType, 3>({x, y, z}) {}

  /**
   * @brief Construct from initializer list of three float values.
   * @param values The initializer list containing x, y, z components.
   * @throws std::invalid_argument if the list size is not 3.
   */
  Position(std::initializer_list<std::float_t> values)
      : math::Vector<PositionComponentType, 3>(PositionComponentType{0},
                                               PositionComponentType{0},
                                               PositionComponentType{0}) {
    if (values.size() != 3) {
      throw std::invalid_argument("Position requires exactly three components");
    }
    const auto it = values.begin();
    this->x = *it;
    this->y = *(it + 1);
    this->z = *(it + 2);
  }

  /**
   * @brief Construct by filling all components with the same float value.
   * @param value The float value to fill all components with.
   */
  explicit Position(std::float_t value)
      : math::Vector<PositionComponentType, 3>(PositionComponentType{value},
                                               PositionComponentType{value},
                                               PositionComponentType{value}) {}

  /**
   * @brief Construct from a GLM vector.
   * @param value Source vector.
   */
  Position(const std::initializer_list<std::float_t> &value)
      : math::Vector<PositionComponentType, 3>(value) {}

  /**
   * @brief Copy constructor.
   * @param other The Position object to copy from.
   */
  Position(const Position &other) = default;

  /**
   * @brief Move constructor.
   * @param other The Position object to move from.
   */
  Position(Position &&other) noexcept = default;

  /**
   * @brief Copy assignment operator.
   * @param other The Position object to copy from.
   * @return A reference to this Position object.
   */
  Position &operator=(const Position &other) = default;

  /**
   * @brief Move assignment operator.
   * @param other The Position object to move from.
   * @return A reference to this Position object.
   */
  Position &operator=(Position &&other) noexcept = default;

  /**
   * @brief Default destructor for Position.
   */
  ~Position(void) = default;

  /**
   * @brief Set the X component of the position.
   * @param value The new X value.
   * @return A reference to this Position object for method chaining.
   */
  Position &setX(const std::float_t value) noexcept {
    this->x = value;
    return *this;
  }

  /**
   * @brief Get the X component of the position.
   * @return The X value.
   */
  std::float_t getX(void) const noexcept { return this->x; }

  /**
   * @brief Set the Y component of the position.
   * @param value The new Y value.
   * @return A reference to this Position object for method chaining.
   */
  Position &setY(const std::float_t value) noexcept {
    this->y = value;
    return *this;
  }

  /**
   * @brief Get the Y component of the position.
   * @return The Y value.
   */
  std::float_t getY(void) const noexcept { return this->y; }

  /**
   * @brief Set the Z component of the position.
   * @param value The new Z value.
   * @return A reference to this Position object for method chaining.
   */
  Position &setZ(const std::float_t value) noexcept {
    this->z = value;
    return *this;
  }

  /**
   * @brief Get the Z component of the position.
   * @return The Z value.
   */
  std::float_t getZ(void) const noexcept { return this->z; }

  /**
   * @brief Translate this position by an offset.
   * @param offset Position offset to add.
   * @return A reference to this Position object for method chaining.
   */
  Position &translate(const Position &offset) noexcept {
    *this += offset;
    return *this;
  }

  /**
   * @brief Return a translated copy of this position.
   * @param offset Position offset to add.
   * @return A new translated Position object.
   */
  Position translated(const Position &offset) const noexcept {
    Position result(*this);
    result += offset;
    return result;
  }

  /**
   * @brief Compute Euclidean distance to another position.
   * @param other Position to measure distance to.
   * @return Distance between the two positions.
   */
  PositionComponentType distanceTo(const Position &other) const {
    return math::distance(
        static_cast<const math::Vector<PositionComponentType, 3> &>(*this),
        static_cast<const math::Vector<PositionComponentType, 3> &>(other));
  }
};

/**
 * @brief Type alias for single-precision position component.
 */
using PositionF = Position<float>;

/**
 * @brief Type alias for double-precision position component.
 */
using PositionD = Position<double>;

} // namespace utility::graphic