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

/**
 * @file color.hpp
 * @brief RGBA color representation with blending and manipulation operations.
 *
 * Declares `utility::Color<Type>`, supporting RGBA color components with
 * operations for blending, grayscale conversion, and color manipulation.
 */

#pragma once

#include <algorithm>
#include <cstdint>
#include <ostream>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace utility {

/**
 * @brief Concept to ensure the type can be used as a color component.
 * @tparam Type The type to check.
 */
template <typename Type>
concept CanBeColorComponent =
    std::is_arithmetic<Type>::value &&
    (std::is_floating_point<Type>::value || std::is_integral<Type>::value);

/**
 * @brief RGBA color with arithmetic type components.
 * @tparam Type Arithmetic type for color components (typically float or
 * uint8_t)
 *
 * Components are expected to be normalized: [0.0, 1.0] for floating-point types
 * or [0, 255] for integral types.
 */
template <CanBeColorComponent Type> class Color {
private:
protected:
  /**
   * @brief Red component.
   */
  Type _red;

  /**
   * @brief Green component.
   */
  Type _green;

  /**
   * @brief Blue component.
   */
  Type _blue;

  /**
   * @brief Alpha (opacity) component.
   */
  Type _alpha;

  /**
   * @brief Clamp a value to valid range based on type.
   * @param value The value to clamp.
   * @return Clamped value.
   */
  static Type clamp(Type value) {
    if constexpr (std::is_floating_point<Type>::value) {
      return std::max(Type{0}, std::min(Type{1}, value));
    } else {
      return std::max(Type{0}, std::min(Type{255}, value));
    }
  }

  /**
   * @brief Get the maximum value for the type.
   * @return Maximum value (1.0 for float, 255 for uint8_t).
   */
  static constexpr Type maxValue() {
    if constexpr (std::is_floating_point<Type>::value) {
      return Type{1};
    } else {
      return Type{255};
    }
  }

public:
  /**
   * @brief Default constructor creating opaque black.
   */
  Color() : _red(Type{}), _green(Type{}), _blue(Type{}), _alpha(maxValue()) {}

  /**
   * @brief Construct color with RGB values (fully opaque).
   * @param red Red component.
   * @param green Green component.
   * @param blue Blue component.
   */
  Color(Type red, Type green, Type blue)
      : _red(clamp(red)), _green(clamp(green)), _blue(clamp(blue)),
        _alpha(maxValue()) {}

  /**
   * @brief Construct color with RGBA values.
   * @param red Red component.
   * @param green Green component.
   * @param blue Blue component.
   * @param alpha Alpha (opacity) component.
   */
  Color(Type red, Type green, Type blue, Type alpha)
      : _red(clamp(red)), _green(clamp(green)), _blue(clamp(blue)),
        _alpha(clamp(alpha)) {}

  /**
   * @brief Copy constructor.
   * @param other The color to copy from.
   */
  Color(const Color &other)
      : _red(other._red), _green(other._green), _blue(other._blue),
        _alpha(other._alpha) {}

  /**
   * @brief Move constructor.
   * @param other The color to move from.
   */
  Color(Color &&other) noexcept
      : _red(std::move(other._red)), _green(std::move(other._green)),
        _blue(std::move(other._blue)), _alpha(std::move(other._alpha)) {}

  /**
   * @brief Copy assignment operator.
   * @param other The color to copy from.
   * @return Reference to this color.
   */
  Color &operator=(const Color &other) {
    if (this != &other) {
      _red = other._red;
      _green = other._green;
      _blue = other._blue;
      _alpha = other._alpha;
    }
    return *this;
  }

  /**
   * @brief Move assignment operator.
   * @param other The color to move from.
   * @return Reference to this color.
   */
  Color &operator=(Color &&other) noexcept {
    if (this != &other) {
      _red = std::move(other._red);
      _green = std::move(other._green);
      _blue = std::move(other._blue);
      _alpha = std::move(other._alpha);
    }
    return *this;
  }

  // Destructor
  ~Color() = default;

  /**
   * @brief Get the red component.
   * @return Red value.
   */
  Type red() const { return _red; }

  /**
   * @brief Get the green component.
   * @return Green value.
   */
  Type green() const { return _green; }

  /**
   * @brief Get the blue component.
   * @return Blue value.
   */
  Type blue() const { return _blue; }

  /**
   * @brief Get the alpha (opacity) component.
   * @return Alpha value.
   */
  Type alpha() const { return _alpha; }

  /**
   * @brief Set the red component.
   * @param red New red value (will be clamped to valid range).
   */
  void setRed(Type red) { _red = clamp(red); }

  /**
   * @brief Set the green component.
   * @param green New green value (will be clamped to valid range).
   */
  void setGreen(Type green) { _green = clamp(green); }

  /**
   * @brief Set the blue component.
   * @param blue New blue value (will be clamped to valid range).
   */
  void setBlue(Type blue) { _blue = clamp(blue); }

  /**
   * @brief Set the alpha (opacity) component.
   * @param alpha New alpha value (will be clamped to valid range).
   */
  void setAlpha(Type alpha) { _alpha = clamp(alpha); }

  /**
   * @brief Set all RGBA components.
   * @param red Red component.
   * @param green Green component.
   * @param blue Blue component.
   * @param alpha Alpha component.
   */
  void setRGBA(Type red, Type green, Type blue, Type alpha) {
    _red = clamp(red);
    _green = clamp(green);
    _blue = clamp(blue);
    _alpha = clamp(alpha);
  }

  /**
   * @brief Equality comparison.
   * @param other The color to compare with.
   * @return True if all components are equal, false otherwise.
   */
  bool operator==(const Color &other) const {
    return _red == other._red && _green == other._green &&
           _blue == other._blue && _alpha == other._alpha;
  }

  /**
   * @brief Inequality comparison.
   * @param other The color to compare with.
   * @return True if any component is not equal, false otherwise.
   */
  bool operator!=(const Color &other) const { return !(*this == other); }

  /**
   * @brief Component-wise color addition (clamped).
   * @param other The color to add.
   * @return Result of color addition.
   */
  Color operator+(const Color &other) const {
    return Color(clamp(_red + other._red), clamp(_green + other._green),
                 clamp(_blue + other._blue), _alpha);
  }

  /**
   * @brief Component-wise color subtraction (clamped).
   * @param other The color to subtract.
   * @return Result of color subtraction.
   */
  Color operator-(const Color &other) const {
    return Color(clamp(_red - other._red), clamp(_green - other._green),
                 clamp(_blue - other._blue), _alpha);
  }

  /**
   * @brief Scalar multiplication of color components.
   * @param scalar The scalar to multiply by.
   * @return Result of scalar multiplication.
   */
  Color operator*(Type scalar) const {
    return Color(clamp(_red * scalar), clamp(_green * scalar),
                 clamp(_blue * scalar), _alpha);
  }

  /**
   * @brief Convert color to grayscale using luminance formula.
   * @return Grayscale version of this color.
   */
  Color grayscale() const {
    Type luminance;
    if constexpr (std::is_floating_point<Type>::value) {
      luminance = clamp(Type{0.299} * _red + Type{0.587} * _green +
                        Type{0.114} * _blue);
    } else {
      luminance = clamp((299 * _red + 587 * _green + 114 * _blue) / 1000);
    }
    return Color(luminance, luminance, luminance, _alpha);
  }

  /**
   * @brief Invert the color (keeping alpha unchanged).
   * @return Inverted color.
   */
  Color inverted() const {
    return Color(maxValue() - _red, maxValue() - _green, maxValue() - _blue,
                 _alpha);
  }

  /**
   * @brief Linearly interpolate between this color and another.
   * @param other The target color.
   * @param t Interpolation factor [0, 1].
   * @return Interpolated color.
   */
  Color lerp(const Color &other, Type t) const {
    t = clamp(t);
    Type oneMinusT = maxValue() - t;

    if constexpr (std::is_floating_point<Type>::value) {
      return Color(oneMinusT * _red + t * other._red,
                   oneMinusT * _green + t * other._green,
                   oneMinusT * _blue + t * other._blue,
                   oneMinusT * _alpha + t * other._alpha);
    } else {
      return Color(clamp((oneMinusT * _red + t * other._red) / maxValue()),
                   clamp((oneMinusT * _green + t * other._green) / maxValue()),
                   clamp((oneMinusT * _blue + t * other._blue) / maxValue()),
                   clamp((oneMinusT * _alpha + t * other._alpha) / maxValue()));
    }
  }

  /**
   * @brief Alpha blend this color over another background color.
   * @param background The background color.
   * @return Blended color.
   */
  Color blendOver(const Color &background) const {
    if constexpr (std::is_floating_point<Type>::value) {
      Type a = _alpha;
      Type oneMinusA = Type{1} - a;
      return Color(a * _red + oneMinusA * background._red,
                   a * _green + oneMinusA * background._green,
                   a * _blue + oneMinusA * background._blue,
                   a + oneMinusA * background._alpha);
    } else {
      Type a = _alpha;
      Type oneMinusA = maxValue() - a;
      return Color(
          clamp((a * _red + oneMinusA * background._red) / maxValue()),
          clamp((a * _green + oneMinusA * background._green) / maxValue()),
          clamp((a * _blue + oneMinusA * background._blue) / maxValue()),
          clamp((a + oneMinusA * background._alpha) / maxValue()));
    }
  }

  /**
   * @brief Create a lighter version of this color.
   * @param factor Lightening factor (0 = no change, 1 = white).
   * @return Lightened color.
   */
  Color lighter(Type factor) const {
    factor = clamp(factor);
    return lerp(Color(maxValue(), maxValue(), maxValue(), _alpha), factor);
  }

  /**
   * @brief Create a darker version of this color.
   * @param factor Darkening factor (0 = no change, 1 = black).
   * @return Darkened color.
   */
  Color darker(Type factor) const {
    factor = clamp(factor);
    return lerp(Color(Type{}, Type{}, Type{}, _alpha), factor);
  }

  /**
   * @brief Get black color (floating-point types).
   * @return Black color.
   */
  template <typename T = Type>
  static typename std::enable_if<std::is_floating_point<T>::value, Color>::type
  Black() {
    return Color(T{0}, T{0}, T{0});
  }

  /**
   * @brief Get white color (floating-point types).
   * @return White color.
   */
  template <typename T = Type>
  static typename std::enable_if<std::is_floating_point<T>::value, Color>::type
  White() {
    return Color(T{1}, T{1}, T{1});
  }

  /**
   * @brief Get red color (floating-point types).
   * @return Red color.
   */
  template <typename T = Type>
  static typename std::enable_if<std::is_floating_point<T>::value, Color>::type
  Red() {
    return Color(T{1}, T{0}, T{0});
  }

  /**
   * @brief Get green color (floating-point types).
   * @return Green color.
   */
  template <typename T = Type>
  static typename std::enable_if<std::is_floating_point<T>::value, Color>::type
  Green() {
    return Color(T{0}, T{1}, T{0});
  }

  /**
   * @brief Get blue color (floating-point types).
   * @return Blue color.
   */
  template <typename T = Type>
  static typename std::enable_if<std::is_floating_point<T>::value, Color>::type
  Blue() {
    return Color(T{0}, T{0}, T{1});
  }

  /**
   * @brief Get yellow color (floating-point types).
   * @return Yellow color.
   */
  template <typename T = Type>
  static typename std::enable_if<std::is_floating_point<T>::value, Color>::type
  Yellow() {
    return Color(T{1}, T{1}, T{0});
  }

  /**
   * @brief Get cyan color (floating-point types).
   * @return Cyan color.
   */
  template <typename T = Type>
  static typename std::enable_if<std::is_floating_point<T>::value, Color>::type
  Cyan() {
    return Color(T{0}, T{1}, T{1});
  }

  /**
   * @brief Get magenta color (floating-point types).
   * @return Magenta color.
   */
  template <typename T = Type>
  static typename std::enable_if<std::is_floating_point<T>::value, Color>::type
  Magenta() {
    return Color(T{1}, T{0}, T{1});
  }

  /**
   * @brief Get transparent color (floating-point types).
   * @return Transparent color.
   */
  template <typename T = Type>
  static typename std::enable_if<std::is_floating_point<T>::value, Color>::type
  Transparent() {
    return Color(T{0}, T{0}, T{0}, T{0});
  }

  /**
   * @brief Get black color (integral types).
   * @return Black color.
   */
  template <typename T = Type>
  static typename std::enable_if<std::is_integral<T>::value, Color>::type
  Black() {
    return Color(T{0}, T{0}, T{0});
  }

  /**
   * @brief Get white color (integral types).
   * @return White color.
   */
  template <typename T = Type>
  static typename std::enable_if<std::is_integral<T>::value, Color>::type
  White() {
    return Color(T{255}, T{255}, T{255});
  }

  /**
   * @brief Get red color (integral types).
   * @return Red color.
   */
  template <typename T = Type>
  static typename std::enable_if<std::is_integral<T>::value, Color>::type
  Red() {
    return Color(T{255}, T{0}, T{0});
  }

  /**
   * @brief Get green color (integral types).
   * @return Green color.
   */
  template <typename T = Type>
  static typename std::enable_if<std::is_integral<T>::value, Color>::type
  Green() {
    return Color(T{0}, T{255}, T{0});
  }

  /**
   * @brief Get blue color (integral types).
   * @return Blue color.
   */
  template <typename T = Type>
  static typename std::enable_if<std::is_integral<T>::value, Color>::type
  Blue() {
    return Color(T{0}, T{0}, T{255});
  }

  /**
   * @brief Get yellow color (integral types).
   * @return Yellow color.
   */
  template <typename T = Type>
  static typename std::enable_if<std::is_integral<T>::value, Color>::type
  Yellow() {
    return Color(T{255}, T{255}, T{0});
  }

  /**
   * @brief Get cyan color (integral types).
   * @return Cyan color.
   */
  template <typename T = Type>
  static typename std::enable_if<std::is_integral<T>::value, Color>::type
  Cyan() {
    return Color(T{0}, T{255}, T{255});
  }

  /**
   * @brief Get magenta color (integral types).
   * @return Magenta color.
   */
  template <typename T = Type>
  static typename std::enable_if<std::is_integral<T>::value, Color>::type
  Magenta() {
    return Color(T{255}, T{0}, T{255});
  }

  /**
   * @brief Get transparent color (integral types).
   * @return Transparent color.
   */
  template <typename T = Type>
  static typename std::enable_if<std::is_integral<T>::value, Color>::type
  Transparent() {
    return Color(T{0}, T{0}, T{0}, T{0});
  }
};

/**
 * @brief Stream output as "RGBA(r, g, b, a)".
 * @param outputStream The output stream.
 * @param color The color to output.
 * @return Reference to the output stream.
 */
template <typename Type>
std::ostream &operator<<(std::ostream &outputStream, const Color<Type> &color) {
  outputStream << "RGBA(" << color.red() << ", " << color.green() << ", "
               << color.blue() << ", " << color.alpha() << ')';
  return outputStream;
}

} // namespace utility
