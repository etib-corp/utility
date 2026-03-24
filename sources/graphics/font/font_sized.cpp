/*
** ETIB PROJECT, 2026
** utility
** File description:
** font_sized
*/

#include "utility/graphics/font/font_sized.hpp"

namespace utility::graphics {
    FontSized::FontSized(uint32_t fontSize, FT_Face face) : _fontSize(fontSize), _correspondingFace(face)
    {
        _atlasWidth = 1024;
        _atlasHeight = 1024;
        _penX = 0;
        _penY = 0;
        _rowHeight = 0;

        _atlas = new Texture(_atlasWidth, _atlasHeight);
        FT_Set_Pixel_Sizes(_correspondingFace, 0, _fontSize);
    }

    FontSized::Glyph& FontSized::getGlyph(uint32_t cp, const std::vector<FT_Face>& faces)
    {
        auto it = _glyphs.find(cp);
        if (it != _glyphs.end())
            return it->second;

        FT_GlyphSlot g = nullptr;

        for (auto face : faces) {
            FT_Set_Pixel_Sizes(face, 0, _fontSize);

            if (FT_Load_Char(face, cp, FT_LOAD_RENDER) == 0) {
                g = face->glyph;
                break;
            }
        }

        if (!g) {
            throw std::runtime_error("Glyph not found");
        }

        if (_penX + g->bitmap.width >= _atlasWidth) {
            _penX = 0;
            _penY += _rowHeight;
            _rowHeight = 0;
        }

        if (_penY + g->bitmap.rows >= _atlasHeight) {
            throw std::runtime_error("Atlas full");
        }

        for (int y = 0; y < g->bitmap.rows; y++) {
            for (int x = 0; x < g->bitmap.width; x++) {
                int atlasIndex =
                    (_penY + y) * _atlasWidth + (_penX + x);

                _atlas->_pixels[atlasIndex] =
                    g->bitmap.buffer[y * g->bitmap.pitch + x];
            }
        }

        Glyph glyph;
        glyph.size = {g->bitmap.width, g->bitmap.rows};
        glyph.bearing = {g->bitmap_left, g->bitmap_top};
        glyph.advance = g->advance.x;

        glyph.uvMin = {
            (float)_penX / _atlasWidth,
            (float)_penY / _atlasHeight
        };

        glyph.uvMax = {
            (float)(_penX + g->bitmap.width) / _atlasWidth,
            (float)(_penY + g->bitmap.rows) / _atlasHeight
        };

        _glyphs[cp] = glyph;

        _penX += g->bitmap.width;
        _rowHeight = std::max(_rowHeight, (int)g->bitmap.rows);

        return _glyphs[cp];
    }
}