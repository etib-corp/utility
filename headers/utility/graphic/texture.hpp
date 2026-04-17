/*
** ETIB PROJECT, 2026
** utility
** File description:
** texture
*/

#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace utility::graphic {
    /**
     * @brief The Texture class represents a texture resource that can be used for rendering in a graphics application.
     *
     * The Texture class manages pixel data for a texture, including its width and height.
     * It provides functionality to store and retrieve pixel data,
     * which can be used for rendering operations in conjunction with shaders and materials.
     */
    class Texture {
        public:
        /**
         * @brief Constructs a Texture object with the specified width and height.
         *
         * This constructor initializes a Texture object with the given width and height,
         * and it sets up the internal pixel data storage for the texture.
         * The pixel data is stored as a vector of bytes in RGBA format,
         * allowing for efficient management of texture data for rendering purposes.
         *
         * @param width The width of the texture in pixels.
         * @param height The height of the texture in pixels.
         */
        Texture(uint32_t width, uint32_t height);

        /**
         * @brief Destructs the Texture object.
         */
        ~Texture() = default;

        /**
         * @brief Retrieves the width of the texture.
         *
         * This method returns the width of the texture in pixels, which is stored as a member variable in the Texture class. The width is an important property of the texture that is used for rendering operations and managing texture data.
         *
         * @return The width of the texture in pixels.
         */
        [[nodiscard]] uint32_t width() const { return _width; }

        /**
         * @brief Retrieves the height of the texture.
         *
         * This method returns the height of the texture in pixels, which is stored as a member variable in the Texture class. The height is an important property of the texture that is used for rendering operations and managing texture data.
         *
         * @return The height of the texture in pixels.
         */
        [[nodiscard]] uint32_t height() const { return _height; }

        /**
         * @brief The corresponding pixel data for this texture, stored as a vector of bytes (RGBA format).
         */
        std::vector<uint8_t> _pixels;

        protected:
        /**
         * @brief The width of the texture in pixels.
         */
        uint32_t _width;

        /**
         * @brief The height of the texture in pixels.
         */
        uint32_t _height;

    };
}