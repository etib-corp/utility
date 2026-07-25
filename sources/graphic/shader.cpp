/*
** ETIB PROJECT, 2026
** xider
** File description:
** shader
*/

#include <utility/graphic/shader.hpp>

namespace utility::graphic
{
	Shader::Shader(const std::string &vertString, const std::string &fragString)
	{
		_vertSPIRV =
			std::vector<uint32_t>(vertString.size() / sizeof(uint32_t));
		std::memcpy(_vertSPIRV.data(), vertString.data(), vertString.size());

		_fragSPIRV =
			std::vector<uint32_t>(fragString.size() / sizeof(uint32_t));
		std::memcpy(_fragSPIRV.data(), fragString.data(), fragString.size());
	}

	/////////////
	// Getters //
	/////////////

	const std::vector<uint32_t> &Shader::getVertexCode() const
	{
		return _vertSPIRV;
	}

	const std::vector<uint32_t> &Shader::getFragmentCode() const
	{
		return _fragSPIRV;
	}
}	 // namespace utility::graphic