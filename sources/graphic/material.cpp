/*
** ETIB PROJECT, 2026
** utility
** File description:
** material
*/

#include <utility/graphic/material.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace utility::graphic {
    Material::Material(const std::string &shaderName, const std::vector<FileAsset> &textureAssets)
        : _shaderName(shaderName) {
        for (const auto &asset : textureAssets) {
            int texWidth	= 0;
            int texHeight	= 0;
            int texChannels = 0;

            stbi_uc *pixels			= stbi_load_from_memory(
                reinterpret_cast<const stbi_uc *>(asset.content().c_str()),
                asset.size(), &texWidth, &texHeight, &texChannels,
                STBI_rgb_alpha);

            if (!pixels) {
                throw std::runtime_error("Failed to load texture: " + asset.path());
            }

            _textures[asset.path()] = new Texture(texWidth, texHeight);
            std::copy(pixels, pixels + (texWidth * texHeight * 4), _textures[asset.path()]->_pixels.data());
        }
    }

    const std::vector<Texture *> &Material::getTextures() const {
        static std::vector<Texture *> textures;
        textures.clear();
        for (const auto &[_, texture] : _textures) {
            textures.push_back(texture);
        }
        return textures;
    }
}
