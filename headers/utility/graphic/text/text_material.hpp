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
        TextMaterial(const std::shared_ptr<Font> &syncedFont);

        /**
         * @brief Destructs the TextMaterial object, releasing any allocated resources.
         */
        ~TextMaterial() = default;

        /**
         * @brief Synchronizes the TextMaterial's textures with the associated Font object.
         *
         * This method updates the TextMaterial's textures based on the font sizes and paths available in the associated Font object. It ensures that the correct textures are associated with the appropriate uniform names for rendering text using the shader.
         *
         * If the associated Font object is not set or does not contain any processed sizes, this method will not perform any updates.
         */
        void syncFont();

        private:
        /**
         * @brief A shared pointer to the Font object that this TextMaterial is synchronized with.
         *
         * This member variable holds a reference to the Font object that the TextMaterial uses to manage its textures. The TextMaterial will synchronize its textures with the glyph atlases of this Font, allowing for efficient rendering of text using the associated shader.
         */
        std::shared_ptr<Font> _syncedFont;
    };
} // namespace utility::graphic