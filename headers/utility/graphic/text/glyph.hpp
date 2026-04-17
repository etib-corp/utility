/*
** ETIB PROJECT, 2026
** utility
** File description:
** glyph
*/

#pragma once

#include <utility/math/vector.hpp>

namespace utility::graphic {
    /**
     * @brief The Glyph struct represents a single character's visual representation in a font atlas.
     *
     * It contains information about the glyph's size, bearing, advance, and texture coordinates (UVs) in the font atlas.
     * This information is essential for rendering text using a font atlas,
     * as it allows the renderer to correctly position and display each character based on its metrics and texture mapping.
     * The `size` field represents the dimensions of the glyph in pixels, while `bearing` indicates the offset from the baseline to the top-left corner of the glyph.
     * The `advance` field specifies the horizontal distance to advance the cursor after rendering the glyph,
     * and `uvMin` and `uvMax` define the texture coordinates for the glyph in the font atlas.
     */
    struct Glyph {
        /**
         * @brief Size of the glyph in pixels (width and height).
         */
        math::Vector<float, 2> size;

        /**
         * @brief Bearing of the glyph, representing the offset from the baseline to the top-left corner of the glyph.
         */
        math::Vector<float, 2> bearing;

        /**
         * @brief Advance value, specifying the horizontal distance to advance the cursor after rendering the glyph.
         */
        uint32_t advance;

        /**
         * @brief Minimum UV coordinates for the glyph in the font atlas.
         */
        math::Vector2F uvMin;

        /**
         * @brief Maximum UV coordinates for the glyph in the font atlas.
         */
        math::Vector2F uvMax;
    };
} // namespace utility::graphic
