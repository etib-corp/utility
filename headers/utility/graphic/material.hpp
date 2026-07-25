/*
** ETIB PROJECT, 2026
** utility
** File description:
** material
*/

#pragma once

#include <string>
#include <map>
#include <vector>

#include <utility/system_io/file.hpp>

#include <utility/graphic/texture.hpp>

namespace utility
{
	class RessourceProvider;
}

namespace utility::graphic
{

	/**
	 * @brief The Material class represents a material that can be used for
	 * rendering objects in a graphics application.
	 *
	 * The Material class manages a shader and its associated textures, allowing
	 * for efficient rendering of objects with the specified visual properties.
	 * It provides functionality to load textures from file assets and retrieve
	 * them for use in rendering operations.
	 *
	 * The constructor of the Material class takes a shader name and a vector of
	 * File objects representing the textures to be loaded. The textures
	 * are loaded using the stb_image library, and the pixel data is stored in
	 * Texture objects for later use.
	 */
	class Material
	{
		public:
		/**
		 * @brief Constructs an empty Material.
		 *
		 * This constructor initializes a Material object without any shader or
		 * textures. It can be used when the shader and textures will be set up
		 * later, allowing for more flexible material creation and management.
		 */
		Material() = default;

		/**
		 * @brief Constructs a Material object with the specified shader name
		 * and texture assets.
		 *
		 * This constructor initializes the Material with a shader name and
		 * loads the textures from the provided File objects. The textures
		 * are loaded using the stb_image library, and the pixel data is stored
		 * in Texture objects for later use in rendering operations.
		 *
		 * @param ressourceProvider A reference to the RessourceProvider
		 * instance.
		 * @param shaderName The name of the shader associated with this
		 * material.
		 * @param textureAssets A vector of File objects representing the
		 * textures to be loaded for this material.
		 *
		 * @throws std::runtime_error if any of the textures fail to load from
		 * the provided File objects.
		 */
		Material(RessourceProvider &ressourceProvider,
				 const std::string &shaderName,
				 const std::vector<File> &textureAssets);

		/**
		 * @brief Destructs the Material object, releasing any allocated
		 * resources.
		 */
		virtual ~Material() = default;

		/**
		 * @brief Retrieves a texture by its name.
		 *
		 * This method returns a shared pointer to the Texture object associated
		 * with the specified name. If the texture does not exist in the
		 * material, it returns a nullptr.
		 *
		 * @param name The name of the texture to retrieve.
		 * @return A shared pointer to the Texture object associated with the
		 * specified name, or nullptr if the texture does not exist.
		 */
		std::shared_ptr<Texture> getTexture(const std::string &name) const;

		/**
		 * @brief Retrieves the textures associated with this material.
		 *
		 * This method returns a vector of pointers to Texture objects that are
		 * associated with this material. The textures are loaded from the
		 * File objects provided during construction and can be used for
		 * rendering operations that require these textures.
		 *
		 * @return A const reference to a vector of pointers to Texture objects
		 * associated with this material.
		 */
		const std::vector<std::shared_ptr<Texture>> &getTextures() const;

		/**
		 * @brief Retrieves the shader name associated with this material.
		 *
		 * This method returns the name of the shader that is associated with
		 * this material. The shader name is used to identify which shader
		 * program should be used when rendering objects that use this material,
		 * allowing for proper rendering of the material's visual properties.
		 *
		 * @return A const reference to a string representing the shader name
		 * associated with this material.
		 */
		const std::string &getShaderName() const;

		/**
		 * @brief Retrieves the version number of the material.
		 *
		 * This method returns the version number of the material, which is used
		 * for tracking changes and updates to the material's properties and
		 * resources.
		 *
		 * @return A const reference to the version number of the material.
		 */
		uint32_t getVersion() const;

		protected:
		/**
		 * @brief The name of the shader associated with this material.
		 */
		std::string _shaderName;

		/**
		 * @brief A map of texture names to Texture objects associated with this
		 * material.
		 */
		std::map<std::string, std::shared_ptr<Texture>> _textures;

		/**
		 * @brief A version number for the material, used for tracking changes
		 * and updates.
		 */
		uint32_t _version = 0;
	};
}	 // namespace utility::graphic