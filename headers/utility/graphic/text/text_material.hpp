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
         * @brief Synchronizes the TextMaterial with the provided Font object.
         *
         * This method updates the TextMaterial's textures based on the processed sizes and paths of the provided Font object. It ensures that the correct textures are available for rendering text with the specified font, allowing for efficient rendering of text using the associated shader.
         *
         * @param font The Font object to synchronize with this TextMaterial.
         */
        void addAtlas(const std::string &name, std::shared_ptr<Texture> atlas);

    };
} // namespace utility::graphic