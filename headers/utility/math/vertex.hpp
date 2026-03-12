/*
** ETIB PROJECT, 2025
** evan
** File description:
** Vertex
*/

#pragma once

#include <ostream>
#include <type_traits>

#include "utility/math/color.hpp"
#include "utility/math/vector.hpp"

namespace utility::math {

/**
 * @brief Vertex type containing common mesh attributes.
 * @tparam VectorComponent Arithmetic type for vertex components (e.g., float,
 * double).
 * @tparam ColorComponent Arithmetic type for color components (e.g., float,
 * uint8_t).
 */
template <CanBeVectorComponent VectorComponent,
          CanBeColorComponent ColorComponent>
class Vertex {
private:
  Vector<VectorComponent, 3> _position;
  Vector<VectorComponent, 3> _normal;
  Vector<VectorComponent, 2> _textureCoordinates;
  Color<ColorComponent> _color;

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
  Vertex() : _position{}, _normal{}, _textureCoordinates{}, _color{} {}

  /**
   * @brief Construct from all vertex attributes.
   * @param position Vertex position.
   * @param normal Vertex normal.
   * @param textureCoordinates Vertex texture coordinates.
   * @param color Vertex color in RGBA.
   */
  Vertex(const Vector<VectorComponent, 3> &position,
         const Vector<VectorComponent, 3> &normal,
         const Vector<VectorComponent, 2> &textureCoordinates,
         const Color<ColorComponent> &color)
      : _position(position), _normal(normal),
        _textureCoordinates(textureCoordinates), _color(color) {}

  /**
   * @brief Get vertex position.
   * @return Position vector.
   */
  Vector<VectorComponent, 3> getPosition(void) const { return _position; }

  /**
   * @brief Set vertex position.
   * @param position Position vector.
   */
  void setPosition(const Vector<VectorComponent, 3> &position) {
    _position = position;
  }

  /**
   * @brief Get vertex normal.
   * @return Normal vector.
   */
  Vector<VectorComponent, 3> getNormal(void) const { return _normal; }

  /**
   * @brief Set vertex normal.
   * @param normal Normal vector.
   */
  void setNormal(const Vector<VectorComponent, 3> &normal) { _normal = normal; }

  /**
   * @brief Get vertex texture coordinates.
   * @return Texture coordinates.
   */
  Vector<VectorComponent, 2> getTextureCoordinates(void) const {
    return _textureCoordinates;
  }

  /**
   * @brief Set vertex texture coordinates.
   * @param textureCoordinates Texture coordinates.
   */
  void
  setTextureCoordinates(const Vector<VectorComponent, 2> &textureCoordinates) {
    _textureCoordinates = textureCoordinates;
  }

  /**
   * @brief Get vertex color.
   * @return Color in RGBA.
   */
  Color<ColorComponent> getColor(void) const { return _color; }

  /**
   * @brief Set vertex color.
   * @param color Color in RGBA.
   */
  void setColor(const Color<ColorComponent> &color) { _color = color; }

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
 * @brief Stream output for debugging.
 * @tparam VectorComponent Arithmetic type for vertex components (e.g., float,
 * double).
 * @tparam ColorComponent Arithmetic type for color components (e.g., float,
 * uint8
 * @param outputStream The output stream.
 * @param vertex The vertex to output.
 * @return Reference to the output stream.
 */
template <CanBeVectorComponent VectorComponent,
          CanBeColorComponent ColorComponent>
std::ostream &
operator<<(std::ostream &outputStream,
           const Vertex<VectorComponent, ColorComponent> &vertex) {
  outputStream << "Vertex(position=" << vertex.getPosition()
               << ", normal=" << vertex.getNormal()
               << ", textureCoordinates=" << vertex.getTextureCoordinates()
               << ", color=" << vertex.getColor() << ')';
  return outputStream;
}

} // namespace utility::math
