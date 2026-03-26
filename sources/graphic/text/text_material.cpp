/*
** ETIB PROJECT, 2026
** utility
** File description:
** text_material
*/

#include <utility/graphic/text/text_material.hpp>

namespace utility::graphic {
    TextMaterial::TextMaterial(const std::shared_ptr<Font> &syncedFont) : Material("text_shader", std::vector<FileAsset>()), _syncedFont(syncedFont) {}

    void TextMaterial::syncFont() {
        if (!_syncedFont) {
            return;
        }

        const std::vector<std::string> &fontPaths = _syncedFont->getFontPaths();
        const std::vector<uint32_t> &fontSizes = _syncedFont->getProcessedSizes();

        // For each combination of font path and size, create a uniform name and
        // associate it with the corresponding texture atlas from the FontSized object.
        for (const std::string &fontPath : fontPaths) {
            for (uint32_t fontSize : fontSizes) {
                std::string uniformName = "font_" + fontPath + "_" + std::to_string(fontSize);
                auto fontSized = _syncedFont->getSize(fontSize);

                _textures[uniformName] = &fontSized.getAtlas();
            }
        }
    }
} // namespace utility::graphic
