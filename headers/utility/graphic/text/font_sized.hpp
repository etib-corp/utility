/*
** ETIB PROJECT, 2026
** utility
** File description:
** font_sized
*/

#pragma once

#include <map>

#include <utility/graphic/texture/texture.hpp>

// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H

// Types & structs
#include <utility/graphic/text/code_point.hpp>
#include <utility/graphic/text/glyph.hpp>

namespace utility::graphic {
    class FontSized {
    public:
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