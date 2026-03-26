/*
** ETIB PROJECT, 2026
** utility
** File description:
** texture
*/

#include <utility/graphics/texture.hpp>

namespace utility::graphics {
    Texture::Texture(uint32_t width, uint32_t height) : _width(width), _height(height)
    {
        _pixels.resize(width * height);
    }
}
