/*
** ETIB PROJECT, 2026
** utility
** File description:
** glyph
*/

#pragma once

#include <utility/math/vector.hpp>

namespace utility::graphic {
    struct Glyph {
        math::Vector<float, 2> size;
        math::Vector<float, 2> bearing;
        uint32_t advance;
        math::Vector2F uvMin;
        math::Vector2F uvMax;
    };
} // namespace utility::graphic
