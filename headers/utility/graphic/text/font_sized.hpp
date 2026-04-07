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

// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H

// Types
#include <utility/graphic/text/code_point.hpp>

namespace utility::graphic {
    class FontSized {
    public:
        struct Glyph {
            math::Vector<float, 2> size;
            math::Vector<float, 2> bearing;
            uint32_t advance;
            math::Vector2F uvMin;
            math::Vector2F uvMax;
        };

        FontSized(uint32_t fontSize, FT_Face face);

        ~FontSized() = default;

        std::shared_ptr<Texture> getAtlas(bool shouldRegenerate = false);

        Glyph generateGlyph(uint32_t codePoint);
        std::vector<Glyph> generateGlyphs(const codePointString &codePoints);

        protected:
        std::shared_ptr<Texture> _generatedAtlas;

        uint32_t _fontSize;

        FT_Face _correspondingFace;

        std::map<uint32_t, Glyph> _generatedGlyphs;

        int _atlasWidth;
        int _atlasHeight;
        int _penX;
        int _penY;
        int _rowHeight;

        void generateAtlas();

    };
} // namespace utility::graphic