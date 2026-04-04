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
    std::string _name;
    std::string _fontPath;
    utility::math::Vector2F _size;
    graphic::Color32Bit _color;

  public:
    /**
     * @brief Default constructor.
     */
    Glyph(void) = default;

    /**
     * @brief Copy constructor.
     */
    Glyph(const Glyph &other) = default;

    /**
     * @brief Move constructor.
     */
    Glyph(Glyph &&other) noexcept = default;

    /**
     * @brief Copy assignment operator.
     */
    Glyph &operator=(const Glyph &other) = default;

    /**
     * @brief Move assignment operator.
     */
    Glyph &operator=(Glyph &&other) noexcept = default;

    /**
     * @brief Destructor.
     */
    ~Glyph(void) = default;

    Glyph &setName(const std::string &name) {
        _name = name;
        return *this;
    }

    const std::string &getName(void) const { return _name; }

    Glyph &setFontPath(const std::string &fontPath) {
        _fontPath = fontPath;
        return *this;
    }

    const std::string &getFontPath(void) const { return _fontPath; }

    Glyph &setSize(const utility::math::Vector2F &size) {
        _size = size;
        return *this;
    }

    const utility::math::Vector2F &getSize(void) const { return _size; }

    Glyph &setColor(const graphic::Color32Bit &color) {
        _color = color;
        return *this;
    }

    const graphic::Color32Bit &getColor(void) const { return _color; }
};

} // namespace utility::graphic
