/*
** ETIB PROJECT, 2026
** utility
** File description:
** texture
*/

#include <utility/graphic/texture.hpp>

namespace utility::graphic
{
	Texture::Texture(uint32_t width, uint32_t height, TextureType type)
		: _type(type)
		, _width(width)
		, _height(height)
	{
		if (type == TextureType::FontAtlas) {
			_pixels.resize(
				width * height,
				0);	   // Initialize pixel data with zeros (grayscale)
		} else {
			_pixels.resize(width * height * 4, 0);
		}
	}
}	 // namespace utility::graphic
