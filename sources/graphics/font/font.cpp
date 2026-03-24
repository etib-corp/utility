/*
** ETIB PROJECT, 2026
** utility
** File description:
** font
*/

#include "utility/graphics/font/font.hpp"

namespace utility::graphics {

    Font::Font(const std::map<std::string, LOAD_METHOD> &dataAndLoadMethods)
    {
        // Initialize FreeType library
        if (FT_Init_FreeType(&_ftLibrary)) {
            throw std::runtime_error("Could not initialize FreeType library.");
        }

        for (const auto &[data, loadMethod] : dataAndLoadMethods) {
            if (loadMethod == LOAD_FROM_FILE) {
                loadFromFile(data);
            } else {
                loadFromMemory(data);
            }
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

    /////////////////////
    // Private Methods //
    /////////////////////

    void Font::loadFromFile(const std::string &fontPath)
    {
        FT_Face face;
        if (FT_New_Face(_ftLibrary, fontPath.c_str(), 0, &face)) {
            throw std::runtime_error("Could not load font: " + fontPath);
        }
        _faces[fontPath] = face;
    }

    void Font::loadFromMemory(const std::string &fontData)
    {
        FT_Face face;
        if (FT_New_Memory_Face(_ftLibrary, reinterpret_cast<const FT_Byte *>(fontData.c_str()), fontData.size(), 0, &face)) {
            throw std::runtime_error("Could not load font from memory.");
        }
        _faces[fontData] = face;
    }
} // namespace utility::graphics