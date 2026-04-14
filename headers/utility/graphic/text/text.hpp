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
#include <utility/ressource_manager.hpp>

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
  graphic::Color32Bit _color; ///< Text RGBA color
  PoseF _pose;                ///< World pose (position and orientation) of the text

  protected:
	std::shared_ptr<Font> _font; 					  ///< Shared pointer to the font used for rendering
	std::shared_ptr<Mesh> _mesh; 					  ///< Mesh for rendering the text

	void updateMesh(void); 							  ///< Update the mesh based on current text properties
	codePointString utf8ToCodepoints(const std::string& str); //< Convert UTF-8 string to Unicode code points

public:
  /**
   * @brief Constructor with content and font.
   * @param content The text content.
   * @param fontPath Path to the font file.
   * @param fontSize Font size in points.
   * @param color The color of the text.
   */
  Text(RessourceManager &ressourceManager, AssetManager &assetManager, const std::string &content, uint32_t fontSize, const std::string &font = "assets/fonts/Roboto.ttf");

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
   * @brief Get the mesh for rendering the text.
   *
   * This method returns a shared pointer to the Mesh object that represents the geometry of the text for rendering.
   * The mesh is generated based on the current text content, font, and font size,
   * and it is updated whenever the text properties change (e.g., when the content or font size is modified).
   *
   * @return A shared pointer to the Mesh object for rendering the text.
   */
  std::shared_ptr<Mesh> getMesh() const;

  /**
   * @brief Get the font family (path) used for rendering the text.
   *
   * This method returns the path to the font file that is currently being used to render the text.
   * The font family is determined by the font file specified during the construction of the Text object
   * or when the font is changed. It can be used to identify the font being used for rendering or to retrieve additional font information if needed.
   *
   * @return A const reference to the string containing the path to the font file used for rendering the text.
   */
  const std::string &getFontFamily(void) const;

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
  Text &setPose(const PoseF &pose);

  /**
   * @brief Get the text pose
   * @return Const reference to the text pose (position and orientation).
   */
  const PoseF &getPose(void) const;

  /**
   * @brief Set the text color.
   * @param color Text RGBA color.
   * @return Reference to this Text instance for chaining.
   */
  Text &setColor(const graphic::Color32Bit &color);

  /**
   * @brief Get the text color.
   * @return Const reference to the text color.
   */
  const graphic::Color32Bit &getColor(void) const;

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
