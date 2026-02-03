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
#include <utility>

#include "utility/math/vector.hpp"

namespace utility::math {

/**
 * @brief Concept to ensure the type can be used as a parallelepiped component.
 * @tparam Type The type to check.
 */
template <typename Type>
concept CanBeParallelepipedComponent = std::is_arithmetic<Type>::value;

/**
 * @brief Axis-aligned parallelepiped with arithmetic type components.
 * @tparam Type Arithmetic type for position and dimensions
 */
template <CanBeParallelepipedComponent Type> class Parallelepiped {
private:
  Vector<Type, 3> _position; ///< Position vector (x, y, z)
  Vector<Type, 3> _origin;   ///< Origin vector (ox, oy, oz)
  Vector<Type, 3> _size;     ///< Size vector (width, height, depth)
public:
  /**
   * @brief Default constructor initializing parallelepiped at origin with zero
   * size.
   */
  Parallelepiped(void) : _position(), _origin(), _size() {}

  /**
   * @brief Construct parallelepiped with position, origin, and size.
   * @param position Position vector (x, y, z).
   * @param origin Origin vector (ox, oy, oz).
   * @param size Size vector (width, height, depth).
   */
  Parallelepiped(Vector<Type, 3> position, Vector<Type, 3> origin,
                 Vector<Type, 3> size)
      : _position(std::move(position)), _origin(std::move(origin)),
        _size(std::move(size)) {}

  /**
   * @brief Set the position of the parallelepiped.
   * @param position New position vector (x, y, z).
   */
  void setPosition(const Vector<Type, 3> &position) { _position = position; }

  /**
   * @brief Get the position vector of the parallelepiped.
   * @return Position vector (x, y, z).
   */
  Vector<Type, 3> getPosition(void) const { return _position; }

  /**
   * @brief Set the origin of the parallelepiped.
   * @param origin New origin vector (ox, oy, oz).
   */
  void setOrigin(const Vector<Type, 3> &origin) { _origin = origin; }

  /**
   * @brief Get the origin vector of the parallelepiped.
   * @return Origin vector (ox, oy, oz).
   */
  Vector<Type, 3> getOrigin(void) const { return _origin; }

  /**
   * @brief Set the size of the parallelepiped.
   * @param size New size vector (width, height, depth).
   */
  void setSize(const Vector<Type, 3> &size) { _size = size; }

  /**
   * @brief Get the size vector of the parallelepiped.
   * @return Size vector (width, height, depth).
   */
  Vector<Type, 3> getSize(void) const { return _size; }
};

} // namespace utility::math