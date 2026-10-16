/*
** ETIB PROJECT, 2026
** utility
** File description:
** code_points
*/

#include <charconv>
#include <sstream>
#include <utility/graphic/text/code_points.hpp>

namespace utility::graphic
{
	CodePoints::CodePoints(const std::string &content)
	{
		parse(content);
	}

	void CodePoints::parse(const std::string &content)
	{
		std::istringstream stream(content);
		std::string line;
		while (std::getline(stream, line)) {
			const size_t spacePos = line.find(' ');
			if (spacePos == std::string::npos) {
				continue;
			}
			// Skip a line whose code is not a 32-bit hexadecimal number, as a
			// line without a space is skipped: std::stoul threw out of the
			// constructor on it, and truncated codes above 0xFFFFFFFF.
			const char *first = line.data() + spacePos + 1;
			const char *last  = line.data() + line.size();
			while (first != last && (*first == ' ' || *first == '\t')) {
				++first;
			}
			if (last - first > 2 && first[0] == '0'
				&& (first[1] == 'x' || first[1] == 'X')) {
				first += 2;
			}
			uint32_t code = 0;
			if (std::from_chars(first, last, code, 16).ec != std::errc()) {
				continue;
			}
			_codes[line.substr(0, spacePos)] = code;
		}
	}

	uint32_t CodePoints::getCode(const std::string &name) const
	{
		auto it = _codes.find(name);
		if (it != _codes.end()) {
			return it->second;
		}
		return 0;
	}

	std::string CodePoints::toUtf8(uint32_t codePoint)
	{
		std::string result;
		if (codePoint <= 0x7F) {
			result.push_back(static_cast<char>(codePoint));
		} else if (codePoint <= 0x7FF) {
			result.push_back(
				static_cast<char>(0xC0 | ((codePoint >> 6) & 0x1F)));
			result.push_back(static_cast<char>(0x80 | (codePoint & 0x3F)));
		} else if (codePoint <= 0xFFFF) {
			result.push_back(
				static_cast<char>(0xE0 | ((codePoint >> 12) & 0x0F)));
			result.push_back(
				static_cast<char>(0x80 | ((codePoint >> 6) & 0x3F)));
			result.push_back(static_cast<char>(0x80 | (codePoint & 0x3F)));
		} else {
			result.push_back(
				static_cast<char>(0xF0 | ((codePoint >> 18) & 0x07)));
			result.push_back(
				static_cast<char>(0x80 | ((codePoint >> 12) & 0x3F)));
			result.push_back(
				static_cast<char>(0x80 | ((codePoint >> 6) & 0x3F)));
			result.push_back(static_cast<char>(0x80 | (codePoint & 0x3F)));
		}
		return result;
	}
}	 // namespace utility::graphic
