/*
** ETIB PROJECT, 2025
** evan
** File description:
** Vertex
*/

#pragma once

#include <ostream>
#include <type_traits>

#include "utility/graphic/color.hpp"
#include "utility/graphic/position.hpp"

#include "utility/math/vector.hpp"

namespace utility::graphic {

/**
 * @brief Concept to constrain color component type.
 * @tparam Type Candidate component type.
 */
template <typename Type>
concept CanBeVectorComponent =
    math::CanBeVectorComponent<Type> && CanBePositionComponent<Type>;

/**
 * @brief Vertex type containing common mesh attributes.
 * @tparam VectorComponent Arithmetic type for vertex components (e.g.,
 * float, double).
 * @tparam ColorComponent Arithmetic type for color components (e.g., float,
 * uint8_t).
 */
template <CanBeVectorComponent VectorComponent> class Vertex {
private:
  Position<VectorComponent> _position;      ///< Vertex position in 3D space.
  math::Vector<VectorComponent, 3> _normal; ///< Vertex normal.
  math::Vector<VectorComponent, 2>
      _textureCoordinates; ///< Vertex texture coordinates.
  Color32Bit _color;       ///< Vertex color in RGBA.

public:
  /**
   * @brief Default constructor.
   *
   * Initializes:
   * - Position to (0, 0, 0)
   * - Normal to (0, 0, 0)
   * - Texture coordinates to (0, 0)
   * - Color to white (1, 1, 1, 1)
   */
  Vertex(void) : _position{}, _normal{}, _textureCoordinates{}, _color{} {}

  /**
   * @brief Construct from all vertex attributes.
   * @param position Vertex position.
   * @param normal Vertex normal.
   * @param textureCoordinates Vertex texture coordinates.
   * @param color Vertex color in RGBA.
   */
  Vertex(const Position<VectorComponent> &position,
         const math::Vector<VectorComponent, 3> &normal,
         const math::Vector<VectorComponent, 2> &textureCoordinates,
         const Color32Bit &color)
      : _position(position), _normal(normal),
        _textureCoordinates(textureCoordinates), _color(color) {}

  /**
   * @brief Set vertex position.
   * @param position Position vector.
   */
  void setPosition(const Position<VectorComponent> &position) {
    _position = position;
  }

  /**
   * @brief Get vertex position.
   * @return Position vector.
   */
  Position<VectorComponent> getPosition(void) const { return _position; }

  /**
   * @brief Set vertex normal.
   * @param normal Normal vector.
   */
  void setNormal(const math::Vector<VectorComponent, 3> &normal) {
    _normal = normal;
  }

  /**
   * @brief Get vertex normal.
   * @return Normal vector.
   */
  math::Vector<VectorComponent, 3> getNormal(void) const { return _normal; }

  /**
   * @brief Set vertex texture coordinates.
   * @param textureCoordinates Texture coordinates.
   */
  void setTextureCoordinates(
      const math::Vector<VectorComponent, 2> &textureCoordinates) {
    _textureCoordinates = textureCoordinates;
  }

  /**
   * @brief Get vertex texture coordinates.
   * @return Texture coordinates.
   */
  math::Vector<VectorComponent, 2> getTextureCoordinates(void) const {
    return _textureCoordinates;
  }

  /**
   * @brief Set vertex color.
   * @param color Color in RGBA.
   */
  void setColor(const Color32Bit &color) { _color = color; }

  /**
   * @brief Get vertex color.
   * @return Color in RGBA.
   */
  Color32Bit getColor(void) const { return _color; }

  /**
   * @brief Equality comparison.
   * @param other Vertex to compare with.
   * @return True when all attributes are equal.
   */
  bool operator==(const Vertex &other) const {
    return _position == other._position && _normal == other._normal &&
           _textureCoordinates == other._textureCoordinates &&
           _color == other._color;
  }

  /**
   * @brief Inequality comparison.
   * @param other Vertex to compare with.
   * @return True when any attribute differs.
   */
  bool operator!=(const Vertex &other) const { return !(*this == other); }
};

/**
 * @brief Type alias for single-precision vertex component.
 */
using VertexF = Vertex<float>;

/**
 * @brief Type alias for double-precision vertex component.
 */
using VertexD = Vertex<double>;

} // namespace utility::graphic
