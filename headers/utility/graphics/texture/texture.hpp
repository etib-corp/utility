/*
** ETIB PROJECT, 2026
** utility
** File description:
** texture
*/

#pragma once

#include <string>
#include <vector>

namespace utility::graphics {
    class Texture {
        public:
        Texture(uint32_t width, uint32_t height);

        ~Texture() = default;

        std::vector<uint8_t> _pixels;

        protected:
        uint32_t _width;
        uint32_t _height;

    };
}