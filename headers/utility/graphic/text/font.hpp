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
#include <functional>
#include <iostream>

#include <utility/system_io/file.hpp>

#include <utility/graphic/text/font_sized.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace utility::graphic
{
	/**
	 * @brief The Font class represents a font resource that can be used to
	 * render text.
	 *
	 * The Font class manages font faces and sizes, allowing you to retrieve
	 * glyph information for rendering text. It uses the FreeType library to
	 * load and manage font data.
	 */
	class Font
	{
		public:
		/**
		 * @brief A struct representing a unique key for identifying a specific
		 * font face and size combination.
		 */
		struct FontSizedKey {
			/**
			 * @brief The name of the font face (e.g., "Arial", "Times New
			 * Roman").
			 */
			std::string faceName;

			/**
			 * @brief The size of the font in points (e.g., 12, 14, 16).
			 */
			uint32_t fontSize = 0;

			/**
			 * @brief Comparison operator to allow FontSizedKey to be used as a
			 * key in std::map or other associative containers.
			 *
			 * @param other The other FontSizedKey to compare against.
			 * @return true if this FontSizedKey is less than the other, false
			 * otherwise.
			 */
			bool operator<(const FontSizedKey &other) const
			{
				if (faceName != other.faceName) {
					return faceName < other.faceName;
				}
				return fontSize < other.fontSize;
			}
		};

		/**
		 * @brief Constructs a Font object by loading font data from the
		 * provided file assets.
		 *
		 * @param fontAssets A vector of File objects containing the font
		 * data to load.
		 *
		 * @throws std::runtime_error if the FreeType library cannot be
		 * initialized or if any of the font assets cannot be loaded.
		 */
		Font(const std::vector<File> &fontAssets);

		/**
		 * @brief Destructs the Font object, releasing any allocated resources.
		 *
		 * This destructor cleans up the FreeType library and any loaded font
		 * faces to prevent memory leaks.
		 */
		~Font();

		/**
		 * @brief Retrieves the ascender value for the specified font size.
		 *
		 * The ascender value represents the distance from the baseline to the
		 * highest point of the font. It is used in text layout calculations to
		 * determine the vertical positioning of text.
		 *
		 * @param fontSize The font size for which to retrieve the ascender
		 * value.
		 * @return The ascender value for the specified font size.
		 */
		float getAscender(uint32_t fontSize) const;

		/**
		 * @brief Retrieves the descender value for the specified font size.
		 *
		 * The descender value represents the distance from the baseline to the
		 * lowest point of the font. It is used in text layout calculations to
		 * determine the vertical positioning of text.
		 *
		 * @param fontSize The font size for which to retrieve the descender
		 * value.
		 * @return The descender value for the specified font size.
		 */
		float getDescender(uint32_t fontSize) const;

		/**
		 * @brief Retrieves the line height for the specified font size.
		 *
		 * The line height represents the vertical distance between lines of
		 * text. It is used in text layout calculations to determine the spacing
		 * between lines of text.
		 *
		 * @param fontSize The font size for which to retrieve the line height.
		 * @return The line height for the specified font size.
		 */
		float getLineHeight(uint32_t fontSize) const;

		/**
		 * @brief Processes a string of Unicode code points to generate glyphs
		 * for rendering text.
		 *
		 * This method takes a string of Unicode code points and generates the
		 * corresponding glyphs for rendering text. It uses the FreeType library
		 * to load and render the glyphs, and it returns a vector of Glyph
		 * objects containing the necessary information for rendering each
		 * character.
		 *
		 * @param fontSize The font size to use for generating the glyphs.
		 * @param codePoints A string of Unicode code points representing the
		 * characters for which to generate glyphs.
		 *
		 * @return A vector of Glyph objects containing the information needed
		 * to render each character in the input string.
		 */
		std::vector<Glyph> processCodePoints(uint32_t fontSize,
											 const codePointString &codePoints);

		/**
		 * @brief Retrieves the paths of the loaded font assets.
		 *
		 * This method returns a vector of strings containing the paths of the
		 * font assets that were loaded into this Font object. The paths are
		 * extracted from the File objects used to initialize the Font.
		 *
		 * @return A const reference to a vector of strings containing the paths
		 * of the loaded font assets.
		 */
		std::vector<std::string> getFontPaths(void) const;

		/**
		 * @brief Checks if the font has been successfully loaded.
		 *
		 * This method checks if the FreeType library was initialized and if at
		 * least one font face was loaded. It returns true if the font is ready
		 * to be used for rendering, and false otherwise.
		 *
		 * @return true if the font is loaded and ready for use, false
		 * otherwise.
		 */
		bool isLoaded(void) const;

		/**
		 * @brief Checks if the font contains a glyph for the specified Unicode
		 * code point.
		 *
		 * This method checks if the font has a glyph corresponding to the given
		 * Unicode code point. It can be used to determine if a particular
		 * character can be rendered using this font.
		 *
		 * @param codepoint The Unicode code point to check for a corresponding
		 * glyph in the font.
		 *
		 * @return true if the font contains a glyph for the specified code
		 * point, false otherwise.
		 */
		bool hasGlyph(char32_t codepoint) const;

		/**
		 * @brief Member function to set a callback that is called when a new
		 * texture atlas is created for a font size.
		 *
		 * This callback function is invoked whenever a new texture atlas is
		 * generated for a specific font size. It allows the caller to receive
		 * the path of the font face associated with the new atlas and a shared
		 * pointer to the Texture object representing the atlas. This can be
		 * useful for updating rendering resources or performing additional
		 * processing when new glyphs are added to the atlas.
		 */
		std::function<void(std::string, std::shared_ptr<Texture>)>
			onNewTextureCreated;

		protected:
		/**
		 * @brief Retrieves the font face name associated with a specific
		 * Unicode code point.
		 *
		 * This method determines which font face contains the glyph for the
		 * given Unicode code point and returns the corresponding font path. It
		 * is used internally to manage multiple font faces and ensure that the
		 * correct glyphs are retrieved for rendering text.
		 *
		 * @param codePoint The Unicode code point for which to retrieve the
		 * associated font face name.
		 *
		 * @return A string containing the path of the font face associated with
		 * the specified Unicode code point.
		 */
		std::string _getFaceNameForGlyph(uint32_t codePoint) const;

		/**
		 * @brief FreeType library instance used for managing font resources.
		 *
		 * This member variable holds the FreeType library instance that is
		 * initialized when the Font object is created. It is used to load and
		 * manage font faces, and it is cleaned up in the destructor to prevent
		 * memory leaks.
		 */
		FT_Library _ftLibrary;

		/**
		 * @brief Map of font paths to their corresponding FreeType face
		 * objects.
		 *
		 * This map stores the loaded font faces, allowing the Font class to
		 * manage multiple fonts and retrieve glyph information as needed. Each
		 * entry maps a font path (as a string) to its corresponding FT_Face
		 * object.
		 *
		 * The map is populated during the construction of the Font object, and
		 * the faces are released in the destructor to ensure proper resource
		 * management.
		 */
		std::map<std::string, FT_Face> _faces;

		/**
		 * @brief Map of font sizes to their corresponding FontSized objects.
		 *
		 * This map stores FontSized objects for different font sizes, allowing
		 * the Font class to manage multiple sizes of the same font. Each entry
		 * maps a font size (as a uint32_t) to its corresponding FontSized
		 * object.
		 *
		 * FontSized objects are created on demand when the getSize method is
		 * called, and they are stored in this map for future retrieval. The
		 * Font class is responsible for managing the lifetime of these
		 * FontSized objects to ensure proper resource management.
		 */
		std::map<FontSizedKey, std::shared_ptr<FontSized>> _sizes;

		/**
		 * @brief In-memory buffers backing FreeType faces.
		 *
		 * FT_New_Memory_Face does not copy the provided bytes, so these buffers
		 * must remain alive for as long as the corresponding FT_Face exists.
		 */
		std::map<std::string, std::string> _faceBuffers;
	};
}	 // namespace utility::graphic