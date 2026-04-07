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

#include <utility/graphic/mesh.hpp>

#include <utility/graphic/text/font.hpp>

#include <utility/graphic/color.hpp>
#include <utility/math/vector.hpp>

#include <utility/asset_manager/file_asset.hpp>

// Types
#include <utility/graphic/text/code_point.hpp>

#define DEFAULT_FONT_COLOR utility::graphic::Color<std::uint8_t>(255, 255, 255, 255)

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
  PoseF _pose;                ///< Text pose (position + orientation)
  graphic::Color32Bit _color; ///< Text RGBA color

  protected:
	std::shared_ptr<Font> _font; 					  ///< Shared pointer to the font used for rendering
	utility::graphic::Mesh _mesh; 					  ///< Mesh for rendering the text

	void updateMesh(void); 							  ///< Update the mesh based on current text properties
	codePointString utf8ToCodepoints(const std::string& str); //< Convert UTF-8 string to Unicode code points

public:
  /**
   * @brief Constructor with content and font.
   * @param content The text content.
   * @param fontPath Path to the font file.
   * @param fontSize Font size in points.
   * @param pose The pose (position and orientation) of the text.
   * @param color The color of the text.
   */
  Text(const std::string &content, const std::vector<FileAsset> &fontAssets,
           uint32_t fontSize);

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
	 * @brief Get the text content.
	 * @return Reference to the text content string.
	 */
	const std::string &getContent(void) const;

	/**
	 * @brief Set the text content.
	 * @param content The new text content.
	 * @return Reference to this Text instance for chaining.
	 */
	Text &setContent(const std::string &content);

	/**
	 * @brief Get the font size.
	 * @return Font size in points.
	 */
	uint32_t getFontSize(void) const;

	/**
	 * @brief Set the font size.
	 * @param fontSize Font size in points.
	 * @return Reference to this Text instance for chaining.
	 */
	Text &setFontSize(uint32_t fontSize);

  /**
   * @brief Set the text pose
   * @param pose Text world pose (position and orientation).
   * @return Reference to this Text instance for chaining.
   */
  Text &setPose(const PoseF &pose) {
    _pose = pose;
    return *this;
  }

  /**
   * @brief Get the text pose
   * @return Const reference to the text pose (position and orientation).
   */
  const PoseF &getPose(void) const { return _pose; }

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

};

} // namespace utility::graphic
