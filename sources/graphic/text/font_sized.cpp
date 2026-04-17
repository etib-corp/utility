/*
** ETIB PROJECT, 2026
** utility
** File description:
** font_sized
*/

#include <utility/graphic/text/font_sized.hpp>

namespace utility::graphic {
    FontSized::FontSized(uint32_t fontSize, FT_Face face) : _fontSize(fontSize), _correspondingFace(face)
    {
        _atlasWidth = 1024;
        _atlasHeight = 1024;
        _penX = 0;
        _penY = 0;
        _rowHeight = 0;

        _generatedAtlas = std::make_shared<Texture>(_atlasWidth, _atlasHeight);
        FT_Set_Pixel_Sizes(_correspondingFace, 0, _fontSize);
    }

    Glyph FontSized::generateGlyph(uint32_t codePoint)
    {
        auto it = _generatedGlyphs.find(codePoint);
        if (it != _generatedGlyphs.end())
            return it->second;

        FT_GlyphSlot g = nullptr;

        FT_Set_Pixel_Sizes(_correspondingFace, 0, _fontSize);

        if (FT_Load_Char(_correspondingFace, codePoint, FT_LOAD_RENDER) == 0) {
            g = _correspondingFace->glyph;
        }

        if (!g) {
            throw std::runtime_error("Glyph not found");
        }

        if (_penX + static_cast<int>(g->bitmap.width) >= _atlasWidth) {
            _penX = 0;
            _penY += _rowHeight;
            _rowHeight = 0;
        }

        if (_penY + static_cast<int>(g->bitmap.rows) >= _atlasHeight) {
            throw std::runtime_error("Atlas full");
        }

        for (unsigned int y = 0; y < g->bitmap.rows; ++y) {
            for (unsigned int x = 0; x < g->bitmap.width; ++x) {
                int pixelIndex = (_penY + y) * _atlasWidth + (_penX + x);
                int atlasIndex = pixelIndex * 4;
                uint8_t value = static_cast<uint8_t>(g->bitmap.buffer[y * g->bitmap.pitch + x]);

                _generatedAtlas->_pixels[atlasIndex + 0] = 255;
                _generatedAtlas->_pixels[atlasIndex + 1] = 255;
                _generatedAtlas->_pixels[atlasIndex + 2] = 255;
                _generatedAtlas->_pixels[atlasIndex + 3] = value;
            }
        }

        Glyph glyph;
        glyph.size = {(float)g->bitmap.width, (float)g->bitmap.rows};
        glyph.bearing = {(float)g->bitmap_left, (float)g->bitmap_top};
        glyph.advance = (float)g->advance.x;

        glyph.uvMin = {
            (float)_penX / _atlasWidth,
            (float)_penY / _atlasHeight
        };

        glyph.uvMax = {
            (float)(_penX + g->bitmap.width) / _atlasWidth,
            (float)(_penY + g->bitmap.rows) / _atlasHeight
        };

        _generatedGlyphs[codePoint] = glyph;

        _penX += g->bitmap.width;
        _rowHeight = std::max(_rowHeight, (int)g->bitmap.rows);

        return _generatedGlyphs[codePoint];
    }

    std::vector<Glyph> FontSized::generateGlyphs(const codePointString &codePoints)
    {
        std::vector<Glyph> glyphs;
        for (auto codePoint : codePoints) {
            glyphs.push_back(generateGlyph(codePoint));
        }
        return glyphs;
    }

    std::shared_ptr<Texture> FontSized::getAtlas(bool shouldRegenerate)
    {
        if (shouldRegenerate || !_generatedAtlas) {
            if (!_generatedAtlas)
                _generatedAtlas = std::make_shared<Texture>(_atlasWidth, _atlasHeight);
            generateAtlas();
        }
        return _generatedAtlas;
    }

    void FontSized::generateAtlas()
    {
        std::copy(_generatedAtlas->_pixels.begin(), _generatedAtlas->_pixels.end(), _generatedAtlas->_pixels.begin());
    }
}
