/*
** ETIB PROJECT, 2026
** utility
** File description:
** code_points
*/

#pragma once

#include <cstdint>
#include <map>
#include <string>

namespace utility::graphic
{
	/**
	 * @brief The CodePoints class manages a mapping from glyph names to Unicode
	 * code points.
	 *
	 * It parses `.codepoints` files (space-separated name and hexadecimal code)
	 * and provides fast lookup of code points by glyph name, as well as
	 * conversion of a single code point to a UTF-8 encoded string.
	 */
	class CodePoints
	{
		public:
		/**
		 * @brief Constructs an empty CodePoints object.
		 */
		CodePoints() = default;

		/**
		 * @brief Constructs a CodePoints object and populates it from a string
		 * containing
		 * `.codepoints` formatted data.
		 *
		 * Each non-empty line is expected to contain a glyph name followed by a
		 * space and a hexadecimal code point.
		 *
		 * @param content The raw content of a `.codepoints` file.
		 */
		CodePoints(const std::string &content);

		/**
		 * @brief Default destructor.
		 */
		~CodePoints() = default;

		/**
		 * @brief Populates the mapping from a `.codepoints` formatted string.
		 *
		 * @param content The raw content of a `.codepoints` file.
		 */
		void parse(const std::string &content);

		/**
		 * @brief Retrieves the Unicode code point for a given glyph name.
		 *
		 * @param name The glyph name to look up.
		 * @return The corresponding code point, or 0 if the name is not found.
		 */
		[[nodiscard]] uint32_t getCode(const std::string &name) const;

		/**
		 * @brief Converts a single Unicode code point to a UTF-8 encoded
		 * string.
		 *
		 * @param codePoint The Unicode code point to convert.
		 * @return A UTF-8 string representing the code point.
		 */
		[[nodiscard]] static std::string toUtf8(uint32_t codePoint);

		protected:
		std::map<std::string, uint32_t>
			_codes;	   ///< Internal name-to-code mapping.
	};
}	 // namespace utility::graphic
