/*
** ETIB PROJECT, 2026
** utility
** File description:
** font
*/

#include <utility/graphic/text/font.hpp>

#include <algorithm>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace utility::graphic
{

	Font::Font(const std::vector<File> &fontAssets)
	{
		// Initialize FreeType library
		if (FT_Init_FreeType(reinterpret_cast<FT_Library *>(&_ftLibrary))) {
			throw std::runtime_error("Could not initialize FreeType library.");
		}

		for (const auto &fontAsset: fontAssets) {
			auto buffer = std::make_shared<std::vector<uint8_t>>();
			const std::string content = fontAsset.content();
			buffer->assign(content.begin(), content.end());
			_faceBuffers[fontAsset.path()] = buffer;

			FT_Face face;
			if (FT_New_Memory_Face(
					reinterpret_cast<FT_Library>(_ftLibrary),
					reinterpret_cast<const FT_Byte *>(buffer->data()),
					static_cast<FT_Long>(buffer->size()), 0, &face)) {
				throw std::runtime_error(
					"Could not load font " + fontAsset.path() + ": "
					+ FT_Error_String(FT_Err_Cannot_Open_Resource));
			}
			_faces[fontAsset.path()] = face;
		}
	}

	Font::~Font()
	{
		if (!isLoaded()) {
			return;
		}
		for (const auto &[_, face]: _faces) {
			FT_Done_Face(static_cast<FT_Face>(face));
		}
		if (_ftLibrary) {
			FT_Done_FreeType(reinterpret_cast<FT_Library>(_ftLibrary));
		}
	}

	////////////////////
	// Public Methods //
	////////////////////

	float Font::getAscender(uint32_t fontSize) const
	{
		auto fontSizedIt = _sizes.find({ "", fontSize });
		if (fontSizedIt != _sizes.end()) {
			return fontSizedIt->second->_ascender;
		}
		return 0.0f;
	}

	float Font::getDescender(uint32_t fontSize) const
	{
		auto fontSizedIt = _sizes.find({ "", fontSize });
		if (fontSizedIt != _sizes.end()) {
			return fontSizedIt->second->_descender;
		}
		return 0.0f;
	}

	float Font::getLineHeight(uint32_t fontSize) const
	{
		auto fontSizedIt = _sizes.find({ "", fontSize });
		if (fontSizedIt != _sizes.end()) {
			return fontSizedIt->second->_lineHeight;
		}
		return 0.0f;
	}

	std::vector<Glyph>
		Font::processCodePoints(uint32_t fontSize,
								const codePointString &codePoints)
	{
		std::vector<Glyph> glyphs;
		glyphs.reserve(codePoints.size());
		std::map<std::string, std::shared_ptr<FontSized>> dirtyFontSizeds;

		for (const auto &codePoint: codePoints) {
			const std::string faceName = _getFaceNameForGlyph(codePoint);

			if (faceName.empty()) {
				continue;
			}

			const FontSizedKey key { faceName, fontSize };

			std::shared_ptr<FontSized> fontSized;
			auto fontSizedIt = _sizes.find(key);

			if (fontSizedIt == _sizes.end()) {
				fontSized =
					std::make_shared<FontSized>(fontSize, _faces.at(faceName));
				_sizes.emplace(key, fontSized);
			} else {
				fontSized = fontSizedIt->second;
			}

			const bool hadGlyph = fontSized->hasGlyph(codePoint);
			glyphs.push_back(fontSized->generateGlyph(codePoint));
			if (!hadGlyph) {
				dirtyFontSizeds[faceName] = fontSized;
			}
		}

		if (onNewTextureCreated) {
			for (const auto &[faceName, fontSized]: dirtyFontSizeds) {
				onNewTextureCreated(faceName + "_" + std::to_string(fontSize),
									fontSized->getAtlas());
			}
		}

		return glyphs;
	}
	math::Vector2F Font::measureText(uint32_t fontSize,
									 const codePointString &codePoints) const
	{
		double width	= 0.0;
		double maxTop	= 0.0;
		double maxBottom = 0.0;

		for (const auto &codePoint: codePoints) {
			const std::string faceName = _getFaceNameForGlyph(codePoint);
			if (faceName.empty()) {
				continue;
			}
			const FontSizedKey key { faceName, fontSize };
			auto fontSizedIt = _sizes.find(key);
			if (fontSizedIt == _sizes.end()) {
				// Not yet rasterized; measure metrics without mutating state.
				FontSized probe(fontSize, _faces.at(faceName));
				const Glyph metric = probe.measureGlyph(codePoint);
				width += metric.advance;
				maxTop	   = std::max(maxTop, static_cast<double>(metric.bearing[1]));
				maxBottom = std::max(
					maxBottom,
					static_cast<double>(metric.size[1] - metric.bearing[1]));
			} else {
				const Glyph metric = fontSizedIt->second->measureGlyph(codePoint);
				width += metric.advance;
				maxTop	   = std::max(maxTop, static_cast<double>(metric.bearing[1]));
				maxBottom = std::max(
					maxBottom,
					static_cast<double>(metric.size[1] - metric.bearing[1]));
			}
		}

		return math::Vector2F { static_cast<float>(width),
								static_cast<float>(maxTop + maxBottom) };
	}

	std::vector<std::string> Font::getFontPaths(void) const
	{		std::vector<std::string> fontPaths;
		for (const auto &[fontPath, _]: _faces) {
			fontPaths.push_back(fontPath);
		}
		return fontPaths;
	}

	bool Font::isLoaded(void) const
	{
		if (_faces.empty())
			return false;
		for (const auto &[_, face]: _faces) {
			if (!face
				|| static_cast<FT_Face>(face)->num_glyphs == 0) {
				return false;
			}
		}
		return true;
	}

	bool Font::hasGlyph(char32_t codepoint) const
	{
		if (!isLoaded()) {
			return false;
		}
		for (const auto &[_, face]: _faces) {
			if (FT_Get_Char_Index(static_cast<FT_Face>(face), codepoint)
				!= 0) {
				return true;
			}
		}
		return false;
	}

	///////////////////////
	// Protected Methods //
	///////////////////////

	std::string Font::_getFaceNameForGlyph(uint32_t codePoint) const
	{
		if (_faces.empty()) {
			return "";
		}

		for (const auto &[faceName, face]: _faces) {
			FT_UInt glyphIndex =
				FT_Get_Char_Index(static_cast<FT_Face>(face), codePoint);
			if (glyphIndex != 0) {
				return faceName;
			}
		}
		return "";
	}

}	 // namespace utility::graphic