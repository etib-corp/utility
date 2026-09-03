/*
** ETIB PROJECT, 2026
** utility
** File description:
** font_sized
*/

#include <utility/graphic/text/font_sized.hpp>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace utility::graphic
{
	namespace
	{
		constexpr int GLYPH_PADDING = 2;
	}

	FontSized::FontSized(uint32_t fontSize, void *face)
		: _fontSize(fontSize)
		, _correspondingFace(face)
		, _atlasWidth(1024)
		, _atlasHeight(1024)
		, _penX(0)
		, _penY(0)
		, _rowHeight(0)
	{
		FT_Face ftFace = static_cast<FT_Face>(_correspondingFace);
		if (!ftFace) {
			throw std::runtime_error("Invalid FreeType face");
		}

		if (FT_Set_Pixel_Sizes(ftFace, 0, _fontSize) != 0) {
			throw std::runtime_error("FT_Set_Pixel_Sizes failed");
		}

		_ascender	= ftFace->size->metrics.ascender / 64.0f;
		_descender	= std::abs(ftFace->size->metrics.descender / 64.0f);
		_lineHeight = ftFace->size->metrics.height / 64.0f;

		_generatedAtlas = std::make_shared<Texture>(
			_atlasWidth, _atlasHeight, Texture::TextureType::FontAtlas);

		_generatedAtlas->pixels().resize(_atlasWidth * _atlasHeight, 0);
		std::fill(_generatedAtlas->pixels().begin(),
				  _generatedAtlas->pixels().end(), 0);
	}

	Glyph FontSized::generateGlyph(uint32_t codePoint)
	{
		auto it = _generatedGlyphs.find(codePoint);
		if (it != _generatedGlyphs.end()) {
			return it->second;
		}

		FT_Face ftFace = static_cast<FT_Face>(_correspondingFace);

		if (FT_Set_Pixel_Sizes(ftFace, 0, _fontSize) != 0) {
			throw std::runtime_error("FT_Set_Pixel_Sizes failed");
		}

		if (FT_Load_Char(ftFace, codePoint, FT_LOAD_RENDER) != 0) {
			throw std::runtime_error("Glyph not found");
		}

		FT_GlyphSlot g = ftFace->glyph;
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
			resizeAtlas(_atlasHeight * 2);
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
				_generatedAtlas->pixels()[dstIndex] = srcRow[x];
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

	Glyph FontSized::measureGlyph(uint32_t codePoint) const
	{
		Glyph glyph;
		FT_Face ftFace = static_cast<FT_Face>(_correspondingFace);
		if (!ftFace) {
			return glyph;
		}

		if (FT_Set_Pixel_Sizes(ftFace, 0, _fontSize) != 0) {
			return glyph;
		}

		// Load metrics without rendering into a bitmap.
		if (FT_Load_Char(ftFace, codePoint, FT_LOAD_NO_BITMAP) != 0) {
			return glyph;
		}

		FT_GlyphSlot g = ftFace->glyph;
		if (!g) {
			return glyph;
		}

		glyph.size	  = { static_cast<float>(g->metrics.width) / 64.0f,
						  static_cast<float>(g->metrics.height) / 64.0f };
		glyph.bearing = { static_cast<float>(g->metrics.horiBearingX) / 64.0f,
						  static_cast<float>(g->metrics.horiBearingY) / 64.0f };
		glyph.advance = static_cast<float>(g->metrics.horiAdvance) / 64.0f;
		return glyph;
	}

	std::shared_ptr<Texture> FontSized::getAtlas(bool shouldRegenerate)
	{
		if (!_generatedAtlas) {
			_generatedAtlas = std::make_shared<Texture>(
				_atlasWidth, _atlasHeight, Texture::TextureType::FontAtlas);
			_generatedAtlas->pixels().resize(_atlasWidth * _atlasHeight, 0);
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

		std::fill(_generatedAtlas->pixels().begin(),
				  _generatedAtlas->pixels().end(), 0);

		_generatedGlyphs.clear();
		_penX	   = 0;
		_penY	   = 0;
		_rowHeight = 0;
	}

	void FontSized::resizeAtlas(int newHeight)
	{
		if (!_generatedAtlas) {
			_atlasHeight = newHeight;
			return;
		}

		if (newHeight <= _atlasHeight) {
			return;
		}

		std::vector<uint8_t> resized(
			static_cast<size_t>(_atlasWidth) * newHeight, 0);

		const int oldWidth	= static_cast<int>(_atlasWidth);
		const int oldHeight = _atlasHeight;

		for (int y = 0; y < oldHeight; ++y) {
			const size_t srcRowStart = static_cast<size_t>(y) * oldWidth;
			const size_t dstRowStart = static_cast<size_t>(y) * oldWidth;
			auto &atlasPixels		 = _generatedAtlas->pixels();
			std::copy(
				atlasPixels.begin() + static_cast<std::ptrdiff_t>(srcRowStart),
				atlasPixels.begin()
					+ static_cast<std::ptrdiff_t>(srcRowStart + oldWidth),
				resized.begin() + static_cast<std::ptrdiff_t>(dstRowStart));
		}

		_generatedAtlas->pixels().swap(resized);
		_atlasHeight = newHeight;
	}
}	 // namespace utility::graphic