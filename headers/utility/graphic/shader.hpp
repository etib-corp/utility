/*
** ETIB PROJECT, 2026
** xider
** File description:
** shader
*/

#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <cstring>

namespace utility::graphic
{
	/**
	 * @brief The Shader class represents a shader program consisting of vertex
	 * and fragment shaders.
	 *
	 * The Shader class manages the SPIR-V bytecode for both vertex and fragment
	 * shaders.
	 */
	class Shader
	{
		public:
		/**
		 * @brief Constructs a Shader object by loading vertex and fragment
		 * shader bytecode from strings.
		 *
		 * @param vertString The string containing the SPIR-V bytecode for the
		 * vertex shader.
		 * @param fragString The string containing the SPIR-V bytecode for the
		 * fragment shader
		 */
		Shader(const std::string &vertString, const std::string &fragString);

		/**
		 * @brief Destructor for the Shader class.
		 */
		~Shader() = default;

		/**
		 * @brief Retrieves the SPIR-V bytecode for the vertex shader.
		 *
		 * @return A reference to a vector containing the SPIR-V bytecode for
		 * the vertex shader.
		 */
		const std::vector<uint32_t> &getVertexCode() const;

		/**
		 * @brief Retrieves the SPIR-V bytecode for the fragment shader.
		 *
		 * @return A reference to a vector containing the SPIR-V bytecode for
		 * the fragment shader.
		 */
		const std::vector<uint32_t> &getFragmentCode() const;

		protected:
		/**
		 * @brief SPIR-V bytecode for the vertex shader.
		 */
		std::vector<uint32_t> _vertSPIRV;

		/**
		 * @brief SPIR-V bytecode for the fragment shader.
		 */
		std::vector<uint32_t> _fragSPIRV;
	};
}	 // namespace utility::graphic