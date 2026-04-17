/*
** ETIB PROJECT, 2026
** utility
** File description:
** text_material
*/

#include <utility/graphic/text/text_material.hpp>

namespace utility::graphic {
    TextMaterial::TextMaterial()
    {
        _shaderName = "text_shader";
    }

    void TextMaterial::addAtlas(const std::string &name, std::shared_ptr<Texture> atlas)
    {
        _textures[name] = atlas;
    }

} // namespace utility::graphic
