/*
 Copyright (c) 2026 ETIB Corporation

 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include <utility/graphic/text/text.hpp>
#include <utility/graphic/size.hpp>

#include <algorithm>
#include <cstdint>
#include <memory>
#include <vector>

namespace utility::graphic
{
	Text::Text(std::shared_ptr<RessourceProvider> ressourceProvider,
			   const PoseF &pose, const Color32Bit &color,
			   const std::string &content, uint32_t fontSize,
			   const std::string &font)
		: Renderable(pose, color)
		, logging::Loggable<Text, logging::DefaultLogger>()
		, _content(content)
		, _fontSize(fontSize)
		, _fontPath(font)
	{
		_font	= ressourceProvider->loadFont(_fontPath);
		_meshes = { std::make_shared<Mesh>(std::vector<VertexF> {},
										   std::vector<uint32_t> {}) };
		updateMesh();
	}

	std::shared_ptr<Mesh> Text::getMesh() const
	{
		return _meshes.front();
	}

	const std::string &Text::getFontFamily(void) const
	{
		return _fontPath;
	}

	const std::string &Text::getContent(void) const
	{
		return _content;
	}

	Text &Text::setContent(const std::string &content)
	{
		_content = content;
		updateMesh();
		return *this;
	}

	uint32_t Text::getFontSize(void) const
	{
		return _fontSize;
	}

	Text &Text::setFontSize(uint32_t fontSize)
	{
		_fontSize = fontSize;

		updateMesh();

		return *this;
	}

	graphic::SizeF Text::getTextDimensions(void) const
	{
		graphic::SizeF dimensions({ 0.0, 0.0 });

		std::vector<uint32_t> codepoints = utf8ToCodepoints(_content);
		std::vector<Glyph> glyphs =
			_font->processCodePoints(_fontSize, codepoints);

		double maxTop	 = 0.0;
		double maxBottom = 0.0;

		for (const auto &g: glyphs) {
			dimensions.setWidth(dimensions.getWidth() + g.advance);
			maxTop = std::max(maxTop, static_cast<double>(g.bearing[VEC_Y]));
			maxBottom =
				std::max(maxBottom,
						 static_cast<double>(g.size[VEC_Y] - g.bearing[VEC_Y]));
		}

		dimensions.setHeight(maxTop + maxBottom);

		getLogger().debug() << "Calculated text dimensions for content '"
							<< _content << "' with font size " << _fontSize
							<< ": width = " << dimensions.getWidth()
							<< ", height = " << dimensions.getHeight();

		return dimensions;
	}

	///////////////////////
	// Protected Methods //
	///////////////////////

	void Text::updateMesh(void)
	{
		_meshes.front() = std::make_shared<Mesh>(std::vector<VertexF> {},
												 std::vector<uint32_t> {});

		float x = getPose().getPosition().getX();
		float y = getPose().getPosition().getY();
		float z = getPose().getPosition().getZ();

		uint32_t indexOffset			 = 0;
		std::vector<uint32_t> codepoints = utf8ToCodepoints(_content);
		std::vector<Glyph> glyphs =
			_font->processCodePoints(_fontSize, codepoints);

		double penX		= 0.0;
		double baseline = std::round(_font->getAscender(_fontSize));

		float maxHeight = 0.0f;
		for (const auto &g: glyphs) {
			maxHeight = std::max(maxHeight, g.size[VEC_Y]);
		}

		for (const auto &g: glyphs) {
			const float xpos =
				static_cast<float>(std::round(x + penX + g.bearing[VEC_X]));
			const float ypos =
				static_cast<float>(std::round(y + baseline - g.bearing[VEC_Y]));

			const float w = g.size[VEC_X];
			const float h = g.size[VEC_Y];

			VertexF v0(PositionF(xpos, ypos + h + maxHeight, z),
					   getPose().getOrientation().getForward(),
					   math::Vector2F({ g.uvMin[VEC_X], g.uvMax[VEC_Y] }),
					   _color);

			VertexF v1(PositionF(xpos, ypos + maxHeight, z),
					   getPose().getOrientation().getForward(),
					   math::Vector2F({ g.uvMin[VEC_X], g.uvMin[VEC_Y] }),
					   _color);

			VertexF v2(PositionF(xpos + w, ypos + maxHeight, z),
					   getPose().getOrientation().getForward(),
					   math::Vector2F({ g.uvMax[VEC_X], g.uvMin[VEC_Y] }),
					   _color);

			VertexF v3(PositionF(xpos + w, ypos + h + maxHeight, z),
					   getPose().getOrientation().getForward(),
					   math::Vector2F({ g.uvMax[VEC_X], g.uvMax[VEC_Y] }),
					   _color);

			_meshes.front()->addIndex(indexOffset + 0);
			_meshes.front()->addIndex(indexOffset + 1);
			_meshes.front()->addIndex(indexOffset + 2);

			_meshes.front()->addIndex(indexOffset + 0);
			_meshes.front()->addIndex(indexOffset + 2);
			_meshes.front()->addIndex(indexOffset + 3);

			_meshes.front()->addVertex(v0);
			_meshes.front()->addVertex(v1);
			_meshes.front()->addVertex(v2);
			_meshes.front()->addVertex(v3);

			indexOffset += 4;
			penX += g.advance;
		}
	}
	std::vector<uint32_t> Text::utf8ToCodepoints(const std::string &str) const
	{
		std::vector<uint32_t> codepoints;

		size_t i = 0;
		while (i < str.size()) {
			uint8_t c0		   = static_cast<uint8_t>(str[i]);
			uint32_t codepoint = 0;
			size_t bytes	   = 0;

			if (c0 < 0x80) {
				codepoint = c0;
				bytes	  = 1;
			} else if (c0 >= 0xC2 && c0 <= 0xDF) {
				codepoint = c0 & 0x1F;
				bytes	  = 2;
			} else if (c0 >= 0xE0 && c0 <= 0xEF) {
				codepoint = c0 & 0x0F;
				bytes	  = 3;
			} else if (c0 >= 0xF0 && c0 <= 0xF4) {
				codepoint = c0 & 0x07;
				bytes	  = 4;
			} else {
				++i;
				continue;
			}

			if (i + bytes > str.size()) {
				break;
			}

			bool valid = true;
			for (size_t j = 1; j < bytes; ++j) {
				uint8_t cc = static_cast<uint8_t>(str[i + j]);
				if ((cc & 0xC0) != 0x80) {
					valid = false;
					break;
				}
				codepoint = (codepoint << 6) | (cc & 0x3F);
			}

			if (valid) {
				if ((bytes == 2 && codepoint < 0x80)
					|| (bytes == 3
						&& (codepoint < 0x800
							|| (codepoint >= 0xD800 && codepoint <= 0xDFFF)))
					|| (bytes == 4
						&& (codepoint < 0x10000 || codepoint > 0x10FFFF))) {
					valid = false;
				}
			}

			if (valid) {
				codepoints.push_back(codepoint);
				i += bytes;
			} else {
				++i;
			}
		}

		return codepoints;
	}
}	 // namespace utility::graphic