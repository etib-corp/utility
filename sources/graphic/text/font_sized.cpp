/*
** ETIB PROJECT, 2026
** utility
** File description:
** font_sized
*/

#include <utility/graphic/text/font_sized.hpp>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <vector>

namespace utility::graphic
{
	namespace
	{
		constexpr int GLYPH_PADDING = 2;
	}

	FontSized::FontSized(uint32_t fontSize, FT_Face face)
		: _fontSize(fontSize)
		, _correspondingFace(face)
		, _atlasWidth(1024)
		, _atlasHeight(1024)
		, _penX(0)
		, _penY(0)
		, _rowHeight(0)
	{
		if (!_correspondingFace) {
			throw std::runtime_error("Invalid FreeType face");
		}

		if (FT_Set_Pixel_Sizes(_correspondingFace, 0, _fontSize) != 0) {
			throw std::runtime_error("FT_Set_Pixel_Sizes failed");
		}

		_ascender = _correspondingFace->size->metrics.ascender / 64.0f;
		_descender =
			std::abs(_correspondingFace->size->metrics.descender / 64.0f);
		_lineHeight = _correspondingFace->size->metrics.height / 64.0f;

		_generatedAtlas = std::make_shared<Texture>(
			_atlasWidth, _atlasHeight, Texture::TextureType::FontAtlas);

		_generatedAtlas->_pixels.resize(_atlasWidth * _atlasHeight, 0);
		std::fill(_generatedAtlas->_pixels.begin(),
				  _generatedAtlas->_pixels.end(), 0);
	}

	Glyph FontSized::generateGlyph(uint32_t codePoint)
	{
		auto it = _generatedGlyphs.find(codePoint);
		if (it != _generatedGlyphs.end()) {
			return it->second;
		}

		if (FT_Set_Pixel_Sizes(_correspondingFace, 0, _fontSize) != 0) {
			throw std::runtime_error("FT_Set_Pixel_Sizes failed");
		}

		if (FT_Load_Char(_correspondingFace, codePoint, FT_LOAD_RENDER) != 0) {
			throw std::runtime_error("Glyph not found");
		}

		FT_GlyphSlot g = _correspondingFace->glyph;
		if (!g) {
			throw std::runtime_error("Invalid glyph slot");
		}

		if (g->bitmap.pixel_mode != FT_PIXEL_MODE_GRAY
			|| g->bitmap.num_grays != 256) {
			throw std::runtime_error("Unsupported glyph bitmap format");
		}

		const int glyphWidth  = static_cast<int>(g->bitmap.width);
		const int glyphHeight = static_cast<int>(g->bitmap.rows);

		if (_penX + glyphWidth + GLYPH_PADDING
			>= static_cast<int>(_atlasWidth)) {
			_penX = 0;
			_penY += _rowHeight + GLYPH_PADDING;
			_rowHeight = 0;
		}

		if (_penY + glyphHeight + GLYPH_PADDING
			>= static_cast<int>(_atlasHeight)) {
			throw std::runtime_error("Atlas full");
		}

		const int pitch	   = g->bitmap.pitch;
		const int absPitch = std::abs(pitch);

		for (int y = 0; y < glyphHeight; ++y) {
			const uint8_t *srcRow = nullptr;

			if (pitch >= 0) {
				srcRow = reinterpret_cast<const uint8_t *>(g->bitmap.buffer)
					+ y * absPitch;
			} else {
				srcRow = reinterpret_cast<const uint8_t *>(g->bitmap.buffer)
					+ (glyphHeight - 1 - y) * absPitch;
			}

			for (int x = 0; x < glyphWidth; ++x) {
				const int dstX = _penX + x;
				const int dstY = _penY + y;
				const int dstIndex =
					dstY * static_cast<int>(_atlasWidth) + dstX;
				_generatedAtlas->_pixels[dstIndex] = srcRow[x];
			}
		}

		Glyph glyph;
		glyph.size	  = { static_cast<float>(glyphWidth),
						  static_cast<float>(glyphHeight) };
		glyph.bearing = { static_cast<float>(g->bitmap_left),
						  static_cast<float>(g->bitmap_top) };
		glyph.advance = static_cast<float>(g->advance.x) / 64.0f;

		glyph.uvMin = {
			static_cast<float>(_penX) / static_cast<float>(_atlasWidth),
			static_cast<float>(_penY) / static_cast<float>(_atlasHeight)
		};

		glyph.uvMax = { static_cast<float>(_penX + glyphWidth)
							/ static_cast<float>(_atlasWidth),
						static_cast<float>(_penY + glyphHeight)
							/ static_cast<float>(_atlasHeight) };

		_generatedGlyphs[codePoint] = glyph;

		_penX += glyphWidth + GLYPH_PADDING;
		_rowHeight = std::max(_rowHeight, glyphHeight);

		return glyph;
	}

	std::vector<Glyph>
		FontSized::generateGlyphs(const codePointString &codePoints)
	{
		std::vector<Glyph> glyphs;
		glyphs.reserve(codePoints.size());

		for (auto codePoint: codePoints) {
			glyphs.push_back(generateGlyph(codePoint));
		}

		return glyphs;
	}

	std::shared_ptr<Texture> FontSized::getAtlas(bool shouldRegenerate)
	{
		if (!_generatedAtlas) {
			_generatedAtlas = std::make_shared<Texture>(
				_atlasWidth, _atlasHeight, Texture::TextureType::FontAtlas);
			_generatedAtlas->_pixels.resize(_atlasWidth * _atlasHeight, 0);
			shouldRegenerate = true;
		}

		if (shouldRegenerate) {
			generateAtlas();
		}

		return _generatedAtlas;
	}

	bool FontSized::hasGlyph(uint32_t codePoint) const
	{
		return _generatedGlyphs.find(codePoint) != _generatedGlyphs.end();
	}

	void FontSized::generateAtlas()
	{
		if (!_generatedAtlas) {
			throw std::runtime_error("Atlas texture is null");
		}

		std::fill(_generatedAtlas->_pixels.begin(),
				  _generatedAtlas->_pixels.end(), 0);

		_generatedGlyphs.clear();
		_penX	   = 0;
		_penY	   = 0;
		_rowHeight = 0;
	}
}	 // namespace utility::graphic