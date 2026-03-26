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

#include <utility/graphics/mesh.hpp>

#include <utility/graphics/font/font.hpp>
#include <utility/math/vector.hpp>

#include <utility/asset_manager/file_asset.hpp>

#define DEFAULT_FONT_COLOR utility::graphics::Color<std::uint8_t>(255, 255, 255, 255)

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
	utility::graphics::Mesh _mesh; 					  ///< Mesh for rendering the text

	void updateMesh(void); 							  ///< Update the mesh based on current text properties
	std::vector<uint32_t> utf8ToCodepoints(const std::string& str); //< Convert UTF-8 string to Unicode code points

public:
  /**
   * @brief Default constructor.
   *
   * Initializes Text with empty content, empty font path, default font size
   * of 12.0f.
   */
  Text(void)
      : _content(""), _fontPath(""), _fontSize(12.0f), _pose(), _color() {}

  /**
   * @brief Constructor with content and font.
   * @param content The text content.
   * @param fontPath Path to the font file.
   * @param fontSize Font size in points.
   * @param pose The pose (position and orientation) of the text.
   * @param color The color of the text.
   */
  Text(std::string content, std::string fontPath, float fontSize, PoseF pose,
       graphic::Color32Bit color)
      : _content(std::move(content)), _fontPath(std::move(fontPath)),
        _fontSize(fontSize), _pose(std::move(pose)), _color(std::move(color)) {}

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
	 * @brief Get the text position.
	 * @return Const reference to the text position.
	 */
	const utility::math::Vector<std::float_t, 3> &getPosition(void) const;
	/**
	 * @brief Set the text position.
	 * @param position Text world position.
	 * @return Reference to this Text instance for chaining.
	 */
	Text &setPosition(const utility::math::Vector<std::float_t, 3> &position);

	/**
	 * @brief Get the text rotation.
	 * @return Const reference to the text rotation.
	 */
	const utility::math::Vector<std::float_t, 3> &getRotation(void) const;

	/**
	 * @brief Set the text rotation.
	 * @param rotation Text euler rotation.
	 * @return Reference to this Text instance for chaining.
	 */
	Text &setRotation(const utility::math::Vector<std::float_t, 3> &rotation);

  /**
   * @brief Get the font size.
   * @return Font size in points.
   */
  float getFontSize(void) const { return _fontSize; }

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
	/**
	 * @brief Get the text scale.
	 * @return Const reference to the text scale.
	 */
	const utility::math::Vector<std::float_t, 3> &getScale(void) const;

	/**
	 * @brief Set the text scale.
	 * @param scale Text local scale.
	 * @return Reference to this Text instance for chaining.
	 */
	Text &setScale(const utility::math::Vector<std::float_t, 3> &scale);

	/**
	 * @brief Get the text color.
	 * @return Const reference to the text color.
	 */
	const utility::graphics::Color<std::uint8_t> &getColor(void) const;

	/**
	 * @brief Set the text color.
	 * @param color Text RGBA color.
	 * @return Reference to this Text instance for chaining.
	 */
	Text &setColor(const utility::graphics::Color<std::uint8_t> &color);
};

} // namespace utility::graphic
