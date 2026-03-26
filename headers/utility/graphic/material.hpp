/*
** ETIB PROJECT, 2026
** utility
** File description:
** material
*/

#pragma once

#include <string>
#include <map>
#include <vector>

#include <utility/asset_manager/file_asset.hpp>

#include <utility/graphic/texture.hpp>

namespace utility::graphic {
    class Material {
        public:
        Material(const std::string &shaderName, const std::vector<FileAsset> &textureAssets);

        ~Material() = default;

        protected:
        std::string _shaderName;
        std::map<std::string, Texture *> _textures;
    };
}