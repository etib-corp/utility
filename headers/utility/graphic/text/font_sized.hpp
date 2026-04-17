/*
** ETIB PROJECT, 2026
** utility
** File description:
** font_sized
*/

#pragma once

#include <map>
#include <memory>

#include <utility/graphic/texture.hpp>

// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H

// Types & structs
#include <utility/graphic/text/code_point.hpp>
#include <utility/graphic/text/glyph.hpp>

namespace utility::graphic {
    /**
     * @brief The FontSized class represents a specific size of a font face, managing the glyphs and texture atlas for that size.
     *
     * The FontSized class is responsible for generating glyphs for a specific font size and managing the texture atlas that contains the rendered glyphs.
     * It uses the FreeType library to load and render the glyphs, and it provides functionality to retrieve the generated texture atlas and glyph information for rendering text.
     */
    class FontSized {
    public:
        /**
         * @brief Constructs a FontSized object for a specific font size and corresponding FreeType face.
         *
         * This constructor initializes the FontSized object with the specified font size and the corresponding FreeType face.
         * It sets up the necessary data structures for managing glyphs and the texture atlas for rendering text at the specified size.
         */
        FontSized(uint32_t fontSize, FT_Face face);

        /**
         * @brief Destructs the FontSized object, releasing any allocated resources.
         */
        ~FontSized() = default;

        /**
         * @brief Retrieves the texture atlas containing the rendered glyphs for this font size.
         *
         * This method returns a shared pointer to the Texture object that contains the rendered glyphs for this font size.
         * The texture atlas is generated based on the glyphs that have been created for this font size,
         * and it can be used for rendering text with the associated shader.
         *
         * @param shouldRegenerate A boolean flag indicating whether to regenerate the texture atlas.
         * If true, the atlas will be regenerated based on the current glyphs; if false, the existing atlas will be returned.
         *
         * @return A shared pointer to the Texture object containing the rendered glyphs for this font size.
         */
        std::shared_ptr<Texture> getAtlas(bool shouldRegenerate = false);

        /**
         * @brief Generates a glyph for a specific Unicode code point and adds it to the texture atlas.
         *
         * This method generates a glyph for the specified Unicode code point using the FreeType library.
         * It renders the glyph and adds it to the texture atlas managed by this FontSized object.
         * The generated glyph information is stored in a map for later retrieval when rendering text.
         *
         * @param codePoint The Unicode code point for which to generate the glyph.
         *
         * @return A Glyph object containing the information about the generated glyph, including its size, bearing, advance, and texture coordinates in the atlas.
         */
        Glyph generateGlyph(uint32_t codePoint);

        /**
         * @brief Retrieves the generated glyph information for a specific Unicode code point.
         *
         * This method retrieves the Glyph information for the specified Unicode code point from the map of generated glyphs.
         * If the glyph has not been generated yet, it will call the generateGlyph method to create the glyph and add it to the atlas before returning the information.
         *
         * @param codePoint The Unicode code point for which to retrieve the glyph information.
         * @return A Glyph object containing the information about the requested glyph.
         */
        std::vector<Glyph> generateGlyphs(const codePointString &codePoints);

        protected:
        /**
         * @brief Generates the texture atlas based on the currently generated glyphs for this font size.
         *
         * This method creates a texture atlas by arranging the generated glyphs in a grid and rendering them into a single Texture object.
         * It updates the texture coordinates for each glyph based on their position in the atlas,
         * allowing for efficient rendering of text using the associated shader.
         */
        void generateAtlas();

        /**
         * @brief The font size in points for this FontSized object.
         */
        std::shared_ptr<Texture> _generatedAtlas;

        /**
         * @brief The font size in points for this FontSized object.
         */
        uint32_t _fontSize;

        /**
         * @brief The corresponding FreeType face associated with this FontSized object.
         */
        FT_Face _correspondingFace;

        /**
         * @brief A map storing the generated glyphs for this font size.
         */
        std::map<uint32_t, Glyph> _generatedGlyphs;

        /**
         * @brief The width of the texture atlas.
         */
        int _atlasWidth;

        /**
         * @brief The height of the texture atlas.
         */
        int _atlasHeight;

        /**
         * @brief The x-coordinate of the pen for glyph placement.
         */
        int _penX;

        /**
         * @brief The y-coordinate of the pen for glyph placement.
         */
        int _penY;

        /**
         * @brief The height of each row in the texture atlas.
         */
        int _rowHeight;

    };
} // namespace utility::graphic