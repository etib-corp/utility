/*
** ETIB PROJECT, 2026
** utility
** File description:
** font_sized
*/

#pragma once

#include <utility/graphic/texture/texture.hpp>
#include <utility/math/vector.hpp>

#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace utility::graphic {
    class FontSized {
    public:
        struct Glyph {
            math::Vector<unsigned int, 2> size;
            math::Vector<int, 2> bearing;
            uint32_t advance;
            math::Vector2F uvMin;
            math::Vector2F uvMax;
        };

        FontSized(uint32_t fontSize, FT_Face face);
        ~FontSized() = default;

        Glyph& getGlyph(uint32_t cp, const std::vector<FT_Face>& faces);

        Texture &getAtlas() const;

        protected:
        Texture *_atlas;

        uint32_t _fontSize;

        FT_Face _correspondingFace;

        std::map<char32_t, Glyph> _glyphs;

        int _atlasWidth;
        int _atlasHeight;
        int _penX;
        int _penY;
        int _rowHeight;

    };
} // namespace utility::graphic