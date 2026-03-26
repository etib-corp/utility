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

#include "utility/graphic/text.hpp"

namespace utility::graphic {
    Text::Text(const std::string &content, const std::vector<FileAsset> &fontAssets,
           uint32_t fontSize)
    : _content(content), _fontSize(fontSize), _position(0.0f), _rotation(0.0f),
      _scale(1.0f), _color(DEFAULT_FONT_COLOR), _mesh({}, {})
{
	_font = std::make_shared<Font>(fontAssets);
	updateMesh();
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

	_font->getSize(static_cast<uint32_t>(fontSize));
	updateMesh();

	return *this;
}

const utility::math::Vector<std::float_t, 3> &Text::getPosition(void) const
{
	return _position;
}

Text &Text::setPosition(const utility::math::Vector<std::float_t, 3> &position)
{
	_position = position;
	return *this;
}

const utility::math::Vector<std::float_t, 3> &Text::getRotation(void) const
{
	return _rotation;
}

Text &Text::setRotation(const utility::math::Vector<std::float_t, 3> &rotation)
{
	_rotation = rotation;
	return *this;
}

const utility::math::Vector<std::float_t, 3> &Text::getScale(void) const
{
	return _scale;
}

Text &Text::setScale(const utility::math::Vector<std::float_t, 3> &scale)
{
	_scale = scale;
	return *this;
}

const utility::graphics::Color<std::uint8_t> &Text::getColor(void) const
{
	return _color;
}

Text &Text::setColor(const utility::graphics::Color<std::uint8_t> &color)
{
	_color = color;
	return *this;
}

///////////////////////
// Protected Methods //
///////////////////////

void Text::updateMesh(void)
{
	auto fontSized = _font->getSize(static_cast<uint32_t>(_fontSize));
	auto faces = _font->getFaces();

	float x = 0;
	float y = 0;

	uint32_t indexOffset = 0;
	std::vector<uint32_t> codepoints = utf8ToCodepoints(_content);

	for (uint32_t cp : codepoints) {
		FontSized::Glyph& g = fontSized.getGlyph(cp, faces);

		float xpos = x + g.bearing[VEC_X];
		float ypos = y - (g.size[VEC_Y] - g.bearing[VEC_Y]);

		float w = g.size[VEC_X];
		float h = g.size[VEC_Y];

		Vertex v0(utility::math::Vector<float, 3>({xpos,     ypos + h, 0.0f}),
					utility::math::Vector<float, 3>({g.uvMin[VEC_X], g.uvMax[VEC_Y], 0.0f}),
					utility::math::Vector<float, 2>({0.0f, 0.0f}),
					_color);
		Vertex v1(utility::math::Vector<float, 3>({xpos,     ypos, 0.0f}),
					utility::math::Vector<float, 3>({g.uvMin[VEC_X], g.uvMin[VEC_Y], 0.0f}),
					utility::math::Vector<float, 2>({0.0f, 0.0f}),
					_color);
		Vertex v2(utility::math::Vector<float, 3>({xpos + w, ypos, 0.0f}),
					utility::math::Vector<float, 3>({g.uvMax[VEC_X], g.uvMin[VEC_Y], 0.0f}),
					utility::math::Vector<float, 2>({0.0f, 0.0f}),
					_color);
		Vertex v3(utility::math::Vector<float, 3>({xpos + w, ypos + h, 0.0f}),
					utility::math::Vector<float, 3>({g.uvMax[VEC_X], g.uvMax[VEC_Y], 0.0f}),
					utility::math::Vector<float, 2>({0.0f, 0.0f}),
					_color);

		_mesh.addVertex(v0);
		_mesh.addVertex(v1);
		_mesh.addVertex(v2);
		_mesh.addVertex(v3);

		_mesh.addIndex(indexOffset + 0);
		_mesh.addIndex(indexOffset + 1);
		_mesh.addIndex(indexOffset + 2);

		_mesh.addIndex(indexOffset + 0);
		_mesh.addIndex(indexOffset + 2);
		_mesh.addIndex(indexOffset + 3);

		indexOffset += 4;

		// Freetype uses 1/64th of a pixel as its unit, so we need to shift by 6 to get the actual pixel value
		x += (g.advance >> 6);
	}
}

std::vector<uint32_t> Text::utf8ToCodepoints(const std::string& str)
{
    std::vector<uint32_t> codepoints;

    size_t i = 0;
    while (i < str.size()) {
        uint8_t c = static_cast<uint8_t>(str[i]);

        uint32_t codepoint = 0;
        int bytes = 0;

        if ((c & 0x80) == 0) {
            // 1 byte
            codepoint = c;
            bytes = 1;
        }
        else if ((c & 0xE0) == 0xC0) {
            // 2 bytes
            codepoint = c & 0x1F;
            bytes = 2;
        }
        else if ((c & 0xF0) == 0xE0) {
            // 3 bytes
            codepoint = c & 0x0F;
            bytes = 3;
        }
        else if ((c & 0xF8) == 0xF0) {
            // 4 bytes
            codepoint = c & 0x07;
            bytes = 4;
        }
        else {
            // invalid byte
            i++;
            continue;
        }

        for (int j = 1; j < bytes; j++) {
            if (i + j >= str.size())
                break;

            uint8_t cc = static_cast<uint8_t>(str[i + j]);

            if ((cc & 0xC0) != 0x80)
                break;

            codepoint = (codepoint << 6) | (cc & 0x3F);
        }

        codepoints.push_back(codepoint);
        i += bytes;
    }

    return codepoints;
}

} // namespace utility::graphics
