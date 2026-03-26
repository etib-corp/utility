/*
** ETIB PROJECT, 2026
** utility
** File description:
** font
*/

#include "utility/graphics/font/font.hpp"

namespace utility::graphics {

    Font::Font(const std::vector<FileAsset> &fontAssets)
    {
        // Initialize FreeType library
        if (FT_Init_FreeType(&_ftLibrary)) {
            throw std::runtime_error("Could not initialize FreeType library.");
        }

        for (const auto &fontAsset : fontAssets) {
            FT_Face face;
            if (FT_New_Memory_Face(_ftLibrary, reinterpret_cast<const FT_Byte *>(fontAsset.content().c_str()), fontAsset.content().size(), 0, &face)) {
                throw std::runtime_error("Could not load font " + fontAsset.path() + ": " + FT_Error_String(FT_Err_Cannot_Open_Resource));
            }
            _faces[fontAsset.path()] = face;
        }
    }

    Font::~Font()
    {
        if (!isLoaded()) {
            return;
        }
        for (const auto &[_, face] : _faces) {
            FT_Done_Face(face);
        }
        if (_ftLibrary) {
            FT_Done_FreeType(_ftLibrary);
        }
    }

    ////////////////////
    // Public Methods //
    ////////////////////

    FontSized &Font::getSize(uint32_t fontSize)
    {
        if (_sizes.find(fontSize) == _sizes.end()) {
            _sizes[fontSize] = FontSized(fontSize, _faces.begin()->second);
        }
        return _sizes[fontSize];
    }

    const std::vector<std::string> &Font::getFontPaths(void) const
    {
        std::vector<std::string> *fontPaths = new std::vector<std::string>();

        for (const auto &[fontPath, _] : _faces) {
            fontPaths->push_back(fontPath);
        }
        return *fontPaths;
    }

    bool Font::isLoaded(void) const
    {
        if (_faces.empty())
            return false;
        for (const auto &[_, face] : _faces) {
            if (!face || face->num_glyphs == 0) {
                return false;
            }
        }
        return true;
    }

    bool Font::hasGlyph(char32_t codepoint) const
    {
        if (!isLoaded()) {
            return false;
        }
        for (const auto &[_, face] : _faces) {
            if (FT_Get_Char_Index(face, codepoint) != 0) {
                return true;
            }
        }
        return false;
    }
} // namespace utility::graphics