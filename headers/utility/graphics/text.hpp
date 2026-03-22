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
 * @file text.hpp
 * @brief Text rendering properties and storage.
 *
 * Declares `utility::graphics::Text`, which encapsulates text content and
 * rendering properties such as font path, font size, and styling options.
 */

#pragma once

#include <cmath>
#include <string>
#include <utility/graphics/color.hpp>
#include <utility/math/vector.hpp>

namespace utility::graphics {

/**
 * @brief Storage for text content and rendering properties.
 *
 * Encapsulates all properties needed to render text, including content,
 * font information and size.
 */
class Text {
private:
  std::string _content;  ///< Text content to display
  std::string _fontPath; ///< Path to the font file
  float _fontSize;       ///< Font size in points
  utility::math::Vector<std::float_t, 3> _position; ///< Text world position
  utility::math::Vector<std::float_t, 3> _rotation; ///< Text euler rotation
  utility::math::Vector<std::float_t, 3> _scale;    ///< Text local scale
  utility::graphics::Color<std::float_t> _color;        ///< Text RGBA color

public:
  /**
   * @brief Default constructor.
   *
   * Initializes Text with empty content, empty font path, default font size
   * of 12.0f.
   */
  Text(void);

  /**
   * @brief Constructor with content and font.
   * @param content The text content.
   * @param fontPath Path to the font file.
   * @param fontSize Font size in points.
   */
  Text(const std::string &content, const std::string &fontPath, float fontSize);

  /**
   * @brief Destructor.
   */
  ~Text(void) = default;

  /**
   * @brief Get the text content.
   * @return Reference to the text content string.
   */
  const std::string &getContent(void) const { return _content; }

  /**
   * @brief Set the text content.
   * @param content The new text content.
   * @return Reference to this Text instance for chaining.
   */
  Text &setContent(const std::string &content) {
    _content = content;
    return *this;
  }

  /**
   * @brief Get the font path.
   * @return Reference to the font path string.
   */
  const std::string &getFontPath(void) const { return _fontPath; }

  /**
   * @brief Set the font path.
   * @param fontPath Path to the font file.
   * @return Reference to this Text instance for chaining.
   */
  Text &setFontPath(const std::string &fontPath) {
    _fontPath = fontPath;
    return *this;
  }

  /**
   * @brief Get the font size.
   * @return Font size in points.
   */
  float getFontSize(void) const { return _fontSize; }

  /**
   * @brief Set the font size.
   * @param fontSize Font size in points.
   * @return Reference to this Text instance for chaining.
   */
  Text &setFontSize(float fontSize) {
    _fontSize = fontSize;
    return *this;
  }

  /**
   * @brief Get the text position.
   * @return Const reference to the text position.
   */
  const utility::math::Vector<std::float_t, 3> &getPosition(void) const {
    return _position;
  }

  /**
   * @brief Set the text position.
   * @param position Text world position.
   * @return Reference to this Text instance for chaining.
   */
  Text &setPosition(const utility::math::Vector<std::float_t, 3> &position) {
    _position = position;
    return *this;
  }

  /**
   * @brief Get the text rotation.
   * @return Const reference to the text rotation.
   */
  const utility::math::Vector<std::float_t, 3> &getRotation(void) const {
    return _rotation;
  }

  /**
   * @brief Set the text rotation.
   * @param rotation Text euler rotation.
   * @return Reference to this Text instance for chaining.
   */
  Text &setRotation(const utility::math::Vector<std::float_t, 3> &rotation) {
    _rotation = rotation;
    return *this;
  }

  /**
   * @brief Get the text scale.
   * @return Const reference to the text scale.
   */
  const utility::math::Vector<std::float_t, 3> &getScale(void) const {
    return _scale;
  }

  /**
   * @brief Set the text scale.
   * @param scale Text local scale.
   * @return Reference to this Text instance for chaining.
   */
  Text &setScale(const utility::math::Vector<std::float_t, 3> &scale) {
    _scale = scale;
    return *this;
  }

  /**
   * @brief Get the text color.
   * @return Const reference to the text color.
   */
  const utility::graphics::Color<std::float_t> &getColor(void) const {
    return _color;
  }

  /**
   * @brief Set the text color.
   * @param color Text RGBA color.
   * @return Reference to this Text instance for chaining.
   */
  Text &setColor(const utility::graphics::Color<std::float_t> &color) {
    _color = color;
    return *this;
  }
};

} // namespace utility::graphics
