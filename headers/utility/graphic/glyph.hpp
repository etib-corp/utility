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
 * @file glyph.hpp
 * @brief Glyph representation for text/typography rendering.
 */

#pragma once

#include "utility/graphic/color.hpp"
#include "utility/math/vector.hpp"
#include <string>

namespace utility::graphic {

/**
 * @brief Minimal glyph class placeholder.
 */
class Glyph {
  private:
    std::string _name;          ///< Name of the glyph (e.g., character code).
    std::string _code;          ///< Code representing the glyph (e.g., Unicode code point).
    std::string _fontPath;      ///< Path to the font file containing this glyph.
    utility::math::Vector2F _size; ///< Size of the glyph in pixels.
    graphic::Color32Bit _color;   ///< Color of the glyph.

    /**
     * @brief Retrieve the glyph code based on its name.
     * @param name The name of the glyph (e.g., character code).
     * @return std::string The corresponding glyph code.
     */
    static std::string getGlyphCode(const std::string &name) {
        // Placeholder for actual glyph code retrieval logic
        return "U+E8DC"; // Default to thumbs up emoji code point as an example
    }

  public:
    /**
     * @brief Default constructor.
     * @param name The name of the glyph (e.g., character code).
     * @param fontPath The path to the font file containing this glyph.
     * @param size The size of the glyph in pixels.
     * @param color The color of the glyph.
     */
    Glyph(const std::string &name = "", const std::string &fontPath = "",
          const utility::math::Vector2F &size = utility::math::Vector2F(0.0f),
          const graphic::Color32Bit &color = graphic::Color32Bit())
        : _name(name), _code(getGlyphCode(name)), _fontPath(fontPath),
        _size(size), _color(color) {}

    /**
     * @brief Copy constructor.
     * @param other The Glyph object to copy from.
     */
    Glyph(const Glyph &other) = default;

    /**
     * @brief Move constructor.
     * @param other The Glyph object to move from.
     */
    Glyph(Glyph &&other) noexcept = default;

    /**
     * @brief Copy assignment operator.
     * @param other The Glyph object to copy from.
     * @return Glyph& A reference to this Glyph object for chaining.
     */
    Glyph &operator=(const Glyph &other) = default;

    /**
     * @brief Move assignment operator.
     * @param other The Glyph object to move from.
     * @return Glyph& A reference to this Glyph object for chaining.
     */
    Glyph &operator=(Glyph &&other) noexcept = default;

    /**
     * @brief Destructor.
     */
    ~Glyph(void) = default;

    /**
     * @brief Set the Name object
     * @param name The name of the glyph (e.g., character code).
     * @return Glyph& A reference to this Glyph object for chaining.
     */
    Glyph &setName(const std::string &name) {
        _name = name;
        return *this;
    }

    /**
     * @brief Get the Name object
     * @return const std::string& A reference to the glyph's name.
     */
    const std::string &getName(void) const { return _name; }

    /**
     * @brief Set the Font Path object
     * @param fontPath The path to the font file containing this glyph.
     * @return Glyph& A reference to this Glyph object for chaining.
     */
    Glyph &setFontPath(const std::string &fontPath) {
        _fontPath = fontPath;
        return *this;
    }

    /**
     * @brief Get the Font Path object
     * @return const std::string& A reference to the font path.
     */
    const std::string &getFontPath(void) const { return _fontPath; }

    /**
     * @brief Set the Size object
     * @param size The size of the glyph in pixels.
     * @return Glyph& A reference to this Glyph object for chaining.
     */
    Glyph &setSize(const utility::math::Vector2F &size) {
        _size = size;
        return *this;
    }

    /**
     * @brief Get the Size object
     * @return const utility::math::Vector2F& A reference to the glyph's size.
     */
    const utility::math::Vector2F &getSize(void) const { return _size; }

    /**
    * @brief Set the Color object
    * @param color The color of the glyph.
    * @return Glyph& A reference to this Glyph object for chaining.
    */
    Glyph &setColor(const graphic::Color32Bit &color) {
        _color = color;
        return *this;
    }

    /**
     * @brief Get the Color object
     * @return const graphic::Color32Bit& A reference to the glyph's color.
     */
    const graphic::Color32Bit &getColor(void) const { return _color; }
};

} // namespace utility::graphic
