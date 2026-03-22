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

#include <string>

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
};

} // namespace utility::graphics
