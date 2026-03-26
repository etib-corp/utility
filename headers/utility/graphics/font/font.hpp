/*
** ETIB PROJECT, 2026
** utility
** File description:
** font
*/

#pragma once

#include <string>
#include <map>
#include <memory>

#include <utility/asset_manager/file_asset.hpp>

#include <utility/graphics/font/font_sized.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace utility::graphics {
    class Font {
        public:
        enum LOAD_METHOD {
            LOAD_FROM_FILE,
            LOAD_FROM_MEMORY
        };

        Font(const std::vector<FileAsset> &fontAssets);

        ~Font();

        FontSized &getSize(uint32_t fontSize);

        const std::vector<std::string> &getFontPaths(void) const;

        bool isLoaded(void) const;

        bool hasGlyph(char32_t codepoint) const;

        protected:
        FT_Library _ftLibrary;
        std::map<std::string, FT_Face> _faces;

        std::map<uint32_t, FontSized> _sizes;
    };
}