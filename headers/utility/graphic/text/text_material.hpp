/*
** ETIB PROJECT, 2026
** utility
** File description:
** text_material
*/

#pragma once

#include <utility/graphic/text/font.hpp>

#include <utility/graphic/material.hpp>

namespace utility::graphic {
    /**
     * @brief The TextMaterial class is a specialized Material that is designed to work with Font objects for rendering text.
     *
     * The TextMaterial class extends the Material class and includes functionality to synchronize with a Font object. It manages the textures associated with the font's glyph atlases, allowing for efficient rendering of text using the associated shader.
     *
     * The syncFont method is responsible for updating the material's textures based on the font's processed sizes and paths, ensuring that the correct textures are available for rendering text with the specified font.
     */
    class TextMaterial : public Material {
        public:
        /**
         * @brief Constructs a TextMaterial object that is synchronized with the provided Font object.
         *
         * This constructor initializes the TextMaterial with a reference to a Font object. The TextMaterial will use this Font to manage its textures and ensure that they are synchronized with the font's glyph atlases.
         */
        TextMaterial();

        /**
         * @brief Destructs the TextMaterial object, releasing any allocated resources.
         */
        ~TextMaterial() = default;

        /**
         * @brief Add a texture atlas to the material with the specified name and Texture object.
         *
         * This method allows adding a texture atlas to the material by associating it with a specific name.
         * The texture atlas is represented by a shared pointer to a Texture object,
         * which contains the pixel data for the glyphs in the font.
         * This method is used to manage the textures that are required for rendering text with the associated shader.
         *
         * @param name The name to associate with the texture atlas.
         * @param atlas A shared pointer to the Texture object representing the texture atlas to be added to the material.
         */
        void addAtlas(const std::string &name, std::shared_ptr<Texture> atlas);

    };
} // namespace utility::graphic