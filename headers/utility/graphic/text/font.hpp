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

#include <utility/graphic/text/font_sized.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace utility::graphic {
    /**
     * @brief The Font class represents a font resource that can be used to render text.
     *
     * The Font class manages font faces and sizes, allowing you to retrieve glyph information for rendering text. It uses the FreeType library to load and manage font data.
     */
    class Font {
        public:
        /**
         * @brief Constructs a Font object by loading font data from the provided file assets.
         *
         * @param fontAssets A vector of FileAsset objects containing the font data to load.
         *
         * @throws std::runtime_error if the FreeType library cannot be initialized or if any of the font assets cannot be loaded.
         */
        Font(const std::vector<FileAsset> &fontAssets);

        /**
         * @brief Destructs the Font object, releasing any allocated resources.
         *
         * This destructor cleans up the FreeType library and any loaded font faces to prevent memory leaks.
         */
        ~Font();

        /**
         * @brief Retrieves a FontSized object for the specified font size.
         *
         * If a FontSized object for the requested size does not already exist, it will be created and stored for future use.
         *
         * @param fontSize The desired font size in points.
         *
         * @return A reference to the FontSized object corresponding to the requested font size.
         */
        FontSized &getSize(uint32_t fontSize);

        /**
         * @brief Retrieves the paths of the loaded font assets.
         *
         * This method returns a vector of strings containing the paths of the font assets that were loaded into this Font object. The paths are extracted from the FileAsset objects used to initialize the Font.
         *
         * @return A const reference to a vector of strings containing the paths of the loaded font assets.
         */
        const std::vector<std::string> &getFontPaths(void) const;

        /**
         * @brief Retrieves the FreeType face objects for the loaded fonts.
         *
         * This method returns a vector of FT_Face objects corresponding to the loaded font faces. These objects can be used to access glyph information and other font properties as needed.
         *
         * @return A const vector of FT_Face objects for the loaded font faces.
         */
        const std::vector<FT_Face> getFaces(void) const;

        /**
         * @brief Checks if the font has been successfully loaded.
         *
         * This method checks if the FreeType library was initialized and if at least one font face was loaded. It returns true if the font is ready to be used for rendering, and false otherwise.
         *
         * @return true if the font is loaded and ready for use, false otherwise.
         */
        bool isLoaded(void) const;

        /**
         * @brief Checks if the font contains a glyph for the specified Unicode code point.
         *
         * This method checks if the font has a glyph corresponding to the given Unicode code point. It can be used to determine if a particular character can be rendered using this font.
         *
         * @param codepoint The Unicode code point to check for a corresponding glyph in the font.
         *
         * @return true if the font contains a glyph for the specified code point, false otherwise.
         */
        bool hasGlyph(char32_t codepoint) const;

        protected:
        /**
         * @brief FreeType library instance used for managing font resources.
         *
         * This member variable holds the FreeType library instance that is initialized when the Font object is created. It is used to load and manage font faces, and it is cleaned up in the destructor to prevent memory leaks.
         */
        FT_Library _ftLibrary;

        /**
         * @brief Map of font paths to their corresponding FreeType face objects.
         *
         * This map stores the loaded font faces, allowing the Font class to manage multiple fonts and retrieve glyph information as needed. Each entry maps a font path (as a string) to its corresponding FT_Face object.
         *
         * The map is populated during the construction of the Font object, and the faces are released in the destructor to ensure proper resource management.
         */
        std::map<std::string, FT_Face> _faces;

        /**
         * @brief Map of font sizes to their corresponding FontSized objects.
         *
         * This map stores FontSized objects for different font sizes, allowing the Font class to manage multiple sizes of the same font. Each entry maps a font size (as a uint32_t) to its corresponding FontSized object.
         *
         * FontSized objects are created on demand when the getSize method is called, and they are stored in this map for future retrieval. The Font class is responsible for managing the lifetime of these FontSized objects to ensure proper resource management.
         */
        std::map<uint32_t, FontSized *> _sizes;
    };
}