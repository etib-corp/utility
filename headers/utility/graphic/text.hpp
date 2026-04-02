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
 * Declares `graphic::Text`, which encapsulates text content and
 * rendering properties such as font path, font size, and styling options.
 */

#pragma once

#include <cmath>
#include <string>

#include <utility/graphic/color.hpp>
#include <utility/graphic/pose.hpp>

namespace utility::graphic {

/**
 * @brief Storage for text content and rendering properties.
 *
 * Encapsulates all properties needed to render text, including content,
 * font information and size.
 */
class Text {
private:
  std::string _content;       ///< Text content to display
  std::string _fontPath;      ///< Path to the font file
  float _fontSize;            ///< Font size in points
  graphic::Color32Bit _color; ///< Text RGBA color

public:
  /**
   * @brief Default constructor.
   *
   * Initializes Text with empty content, empty font path, default font size
   * of 12.0f.
   */
  Text(void)
      : _content(""), _fontPath(""), _fontSize(12.0f), _color() {}

  /**
   * @brief Constructor with content and font.
   * @param content The text content.
   * @param fontPath Path to the font file.
   * @param fontSize Font size in points.
   * @param color The color of the text.
   */
  Text(std::string content, std::string fontPath, float fontSize,
       graphic::Color32Bit color)
      : _content(std::move(content)), _fontPath(std::move(fontPath)),
        _fontSize(fontSize), _color(std::move(color)) {}

  /**
   * @brief Copy constructor.
   * @param other The Text object to copy from.
   */
  Text(const Text &other) = default;

  /**
   * @brief Move constructor.
   * @param other The Text object to move from.
   */
  Text(Text &&other) noexcept = default;

  /**
   * @brief Copy assignment operator.
   * @param other The Text object to copy from.
   * @return A reference to this Text object.
   */
  Text &operator=(const Text &other) = default;

  /**
   * @brief Move assignment operator.
   * @param other The Text object to move from.
   * @return A reference to this Text object.
   */
  Text &operator=(Text &&other) noexcept = default;

  /**
   * @brief Destructor.
   */
  ~Text(void) = default;

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
   * @brief Get the text content.
   * @return Reference to the text content string.
   */
  const std::string &getContent(void) const { return _content; }

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
   * @brief Get the font path.
   * @return Reference to the font path string.
   */
  const std::string &getFontPath(void) const { return _fontPath; }

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
   * @brief Get the font size.
   * @return Font size in points.
   */
  float getFontSize(void) const { return _fontSize; }

  /**
   * @brief Set the text color.
   * @param color Text RGBA color.
   * @return Reference to this Text instance for chaining.
   */
  Text &setColor(const graphic::Color32Bit &color) {
    _color = color;
    return *this;
  }

  /**
   * @brief Get the text color.
   * @return Const reference to the text color.
   */
  const graphic::Color32Bit &getColor(void) const { return _color; }

  /**
   * @brief Check if text content is empty.
   * @return True if content has no characters.
   */
  bool empty(void) const noexcept { return _content.empty(); }

  /**
   * @brief Check if font path is set.
   * @return True if a non-empty font path is configured.
   */
  bool hasFontPath(void) const noexcept { return !_fontPath.empty(); }

  /**
   * @brief Clear text content.
   * @return Reference to this Text instance for chaining.
   */
  Text &clearContent(void) {
    _content.clear();
    return *this;
  }

  /**
   * @brief Equality comparison.
   * @param other Text object to compare with.
   * @return True when all properties are equal.
   */
  bool operator==(const Text &other) const {
    return _content == other._content && _fontPath == other._fontPath &&
           _fontSize == other._fontSize && _color == other._color;
  }

  /**
   * @brief Inequality comparison.
   * @param other Text object to compare with.
   * @return True when any property differs.
   */
  bool operator!=(const Text &other) const { return !(*this == other); }
};

} // namespace utility::graphic
