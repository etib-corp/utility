/*
** ETIB PROJECT, 2026
** xider
** File description:
** shader
*/

#include <cstring>
#include <stdexcept>
#include <string>

#include <utility/graphic/shader.hpp>

namespace utility::graphic
{
	namespace
	{
		void validateSpirv(const std::string &data, const char *which)
		{
			if (data.size() % sizeof(uint32_t) != 0) {
				throw std::invalid_argument(
					std::string(which)
					+ " shader bytecode length is not a multiple of 4");
			}
		}
	}	 // namespace

	Shader::Shader(const std::string &vertString, const std::string &fragString)
	{
		validateSpirv(vertString, "Vertex");
		validateSpirv(fragString, "Fragment");

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