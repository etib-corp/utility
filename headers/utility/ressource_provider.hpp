#pragma once

#include <utility/system_io/file.hpp>
#include <utility/system_io/system_io.hpp>


#include <utility/graphic/pose.hpp>
#include <utility/graphic/text/font.hpp>
#include <utility/graphic/text/code_points.hpp>
#include <utility/graphic/text/text_material.hpp>
#include <utility/graphic/material.hpp>
#include <utility/graphic/texture.hpp>
#include <utility/graphic/model.hpp>
#include <utility/graphic/shader.hpp>

#include <utility/sound/audio_source.hpp>
#include <utility/sound/decoder/decoder_registry.hpp>
#include <utility/sound/audio_manager.hpp>

#include <utility/logging/loggable.hpp>
#include <utility/logging/default_logger.hpp>

namespace utility
{
	/**
	 * @brief The RessourceProvider class is responsible for managing and
	 * loading various resources such as fonts, materials, and textures in a
	 * graphics application.
	 *
	 * The RessourceProvider provides methods to load resources from file paths
	 * or from asset objects, and it maintains internal maps to store loaded
	 * resources for efficient retrieval. It supports loading fonts, materials,
	 * and textures, and it can handle different shader types for materials.
	 */
	class RessourceProvider:
		protected utility::logging::Loggable<RessourceProvider,
											 utility::logging::DefaultLogger>
	{
		public:
		/**
		 * @brief Enumeration for different shader types that can be associated
		 * with materials.
		 *
		 * This enum defines the types of shaders that can be used when loading
		 * materials. It currently includes `TEXT_SHADER` for text rendering and
		 * `MESH_SHADER` for mesh rendering, allowing for different visual
		 * effects based on the shader type used in the material.
		 */
		enum class ShaderType { TEXT_SHADER, MESH_SHADER };

		/**
		 * @brief Constructs a RessourceProvider object with a reference to a
		 * SystemIO instance.
		 * @param systemInterface A reference to the SystemIO instance used for
		 * loading assets from file paths. The RessourceProvider relies on the
		 * SystemIO interface to load resources from the filesystem, and this
		 * constructor initializes the RessourceProvider with the provided
		 * SystemIO instance for asset loading operations.
		 * @param basePath An optional base path to prepend to resource paths
		 * when loading resources. This can be used to specify a common
		 * directory for all resources, allowing for more flexible resource
		 * management and organization.
		 */
		RessourceProvider(SystemIO &systemInterface,
						  const std::string &basePath = "");

		/**
		 * @brief Destructs the RessourceProvider object.
		 */
		~RessourceProvider() = default;

		/**
		 * @brief Retrieves a map of loaded materials.
		 *
		 * @return A map where the keys are material IDs (uint32_t) and the
		 * values are shared pointers to the corresponding Material objects.
		 */
		[[nodiscard]] std::map<uint32_t, std::shared_ptr<graphic::Material>>
			getMaterials() const;

		/**
		 * @brief Retrieves a map of loaded textures.
		 *
		 * @return A map where the keys are texture IDs (uint32_t) and the
		 * values are shared pointers to the corresponding Texture objects.
		 */
		[[nodiscard]] std::map<uint32_t, std::shared_ptr<graphic::Texture>>
			getTextures() const;

		/**
		 * @brief Retrieves a map of loaded models.
		 *
		 * @return A map where the keys are model IDs (uint32_t) and the values
		 * are shared pointers to the corresponding Model objects.
		 */
		[[nodiscard]] std::map<uint32_t, std::shared_ptr<graphic::Model>>
			getModels() const;

		/**
		 * @brief Retrieves a map of loaded shaders.
		 *
		 * @return A map where the keys are shader IDs (uint32_t) and the values
		 * are shared pointers to the corresponding Shader objects.
		 */
		[[nodiscard]] std::map<uint32_t, std::shared_ptr<graphic::Shader>>
			getShaders() const;

		/**
		 * @brief Retrieves a map of loaded code points resources.
		 *
		 * @return A map where the keys are code points IDs (uint32_t) and the
		 * values are shared pointers to the corresponding CodePoints objects.
		 */
		[[nodiscard]] std::map<uint32_t, std::shared_ptr<graphic::CodePoints>>
			getCodePoints() const;

		/**
		 * @brief Retrieves the unique shader ID associated with a given shader
		 * name.
		 *
		 * This method looks up the shader name in an internal map and returns
		 * the corresponding shader ID if found. If the shader name is not
		 * found, it returns 0, indicating that the shader does not exist in the
		 * resource provider.
		 *
		 * @param shaderName The name of the shader for which to retrieve the
		 * ID.
		 *
		 * @return The unique shader ID associated with the given shader name,
		 * or 0 if the shader name is not found.
		 */
		[[nodiscard]] uint32_t getShaderID(const std::string &shaderName) const;

		/**
		 * @brief Retrieves the unique material ID associated with a given
		 * material name.
		 *
		 * @param materialName The name of the material for which to retrieve
		 * the ID.
		 *
		 * @return The unique material ID associated with the given material
		 * name, or 0 if the material name is not found.
		 */
		[[nodiscard]] uint32_t getMaterialID(const std::string &materialName);

		/**
		 * @brief Retrieves the unique ID of the default material.
		 *
		 * If the default material is not found,
		 * then it creates a new default material with the default shader and
		 * returns its ID. The default material is used as a fallback when a
		 * specific material is not found for a resource, ensuring that the
		 * application can still render objects even if their intended materials
		 * are missing or misconfigured.
		 *
		 * @return The unique ID of the default material.
		 */
		[[nodiscard]] uint32_t getDefaultMaterialID();

		/**
		 * @brief Retrieves the unique ID of the mesh material.
		 *
		 * @return The unique ID of the mesh material.
		 */
		[[nodiscard]] uint32_t getMeshMaterialID();

		/**
		 * @brief Loads a font resource from a specified file path.
		 *
		 * @param path The file path to the font resource to be loaded.
		 *
		 * @return A shared pointer to the loaded Font object.
		 */
		std::shared_ptr<graphic::Font> loadFont(const std::string &path);

		/**
		 * @brief Loads a font resource from a specified asset.
		 *
		 * @param fontAsset A shared pointer to the File object containing
		 * the font data to be loaded.
		 *
		 * @return A shared pointer to the loaded Font object.
		 */
		std::shared_ptr<graphic::Font>
			loadFontFromAsset(std::shared_ptr<utility::File> fontAsset);

		// TODO: add loadFontsFromDirectory method to load all fonts from a
		// directory But needs to be implemented in the SystemIO first to
		// load all assets from a directory

		// TODO: add loadFontFamily method to load all fonts from a directory
		// But needs to be implemented in the SystemIO first to load all
		// assets from a directory

		/**
		 * @brief Loads a font family resource from a vector of font assets.
		 *
		 * @param fontAssets A vector of shared pointers to File objects
		 * containing the font data for the font family to be loaded.
		 *
		 * @return A shared pointer to the loaded Font object representing the
		 * font family.
		 */
		std::shared_ptr<graphic::Font> loadFontFamilyFromAssets(
			const std::vector<std::shared_ptr<utility::File>> &fontAssets);

		/**
		 * @brief Loads a material resource from a specified file path.
		 *
		 * @param path The file path to the material resource to be loaded.
		 * @param shaderType The type of shader to be associated with the loaded
		 * material.
		 *
		 * @return A shared pointer to the loaded Material object.
		 */
		std::shared_ptr<graphic::Material> loadMaterial(const std::string &path,
														ShaderType shaderType);

		/**
		 * @brief Loads a material resource from a specified asset.
		 *
		 * @param shaderType The type of shader to be associated with the loaded
		 * material.
		 * @param materialAsset A shared pointer to the File object
		 * containing the material data to be loaded.
		 *
		 * @return A shared pointer to the loaded Material object.
		 */
		std::shared_ptr<graphic::Material>
			loadMaterialFromAsset(ShaderType shaderType,
								  std::shared_ptr<utility::File> materialAsset);

		/**
		 * @brief Loads a texture resource from a specified file path.
		 *
		 * @param path The file path to the texture resource to be loaded.
		 * @return A shared pointer to the loaded Texture object.
		 */
		std::shared_ptr<graphic::Texture> loadTexture(const std::string &path);

		/**
		 * @brief Loads a texture resource from a specified asset.
		 *
		 * @param textureAsset A shared pointer to the File object
		 * containing the texture data to be loaded.
		 *
		 * @return A shared pointer to the loaded Texture object.
		 */
		std::shared_ptr<graphic::Texture>
			loadTextureFromAsset(std::shared_ptr<utility::File> textureAsset);

		// TODO: add loadTexturesFromDirectory method to load all textures from
		// a directory But needs to be implemented in the SystemIO first to
		// load all assets from a directory

		/**
		 * @brief Loads a model resource from a specified file path.
		 *
		 * @param path The file path to the model resource to be loaded.
		 * @param pose The initial position and orientation for the model.
		 * @param material The name of the material to be associated with the
		 * loaded model. If not specified, the default material will be used.
		 *
		 * @return A shared pointer to the loaded Model object.
		 */
		std::shared_ptr<graphic::Model>
			loadModel(const std::string &path,
					  const utility::graphic::PoseF &pose = utility::graphic::PoseF(),
					  const std::string &material = "default_material");

		/**
		 * @brief Loads a model resource from a specified asset.
		 *
		 * @param modelAsset A shared pointer to the File object containing the
		 * model data to be loaded.
		 * @param pose The initial position and orientation for the model.
		 * @param material The name of the material to be associated with the
		 * loaded model. If not specified, the default material will be used.
		 *
		 * @return A shared pointer to the loaded Model object.
		 */
		std::shared_ptr<graphic::Model> loadModelFromAsset(
			std::shared_ptr<utility::File> modelAsset,
			const utility::graphic::PoseF &pose = utility::graphic::PoseF(),
			const std::string &material = "default_material");

		/**
		 * @brief Loads a model resource from a specified file path and model
		 * type.
		 *
		 * @param modelAsset A shared pointer to the File object containing the
		 * model data to be loaded.
		 * @param type The type of the model (e.g., OBJ, FBX, GLTF) to be
		 * loaded.
		 * @param pose The initial position and orientation for the model.
		 * @param material The name of the material to be associated with the
		 * loaded model. If not specified, the default material will be used.
		 *
		 * @return A shared pointer to the loaded Model object.
		 */
		std::shared_ptr<graphic::Model> loadModelFromAsset(
			std::shared_ptr<utility::File> modelAsset,
			graphic::Model::ModelType type,
			const utility::graphic::PoseF &pose = utility::graphic::PoseF(),
			const std::string &material = "default_material");

		/**
		 * @brief Loads an OBJ model resource from a specified file path.
		 *
		 * @param path The file path to the OBJ model resource to be loaded.
		 * @param pose The initial position and orientation for the model.
		 * @param material The name of the material to be associated with the
		 * loaded OBJ model. If not specified, the default material will be
		 * used.
		 *
		 * @return A shared pointer to the loaded Model object representing the
		 * OBJ model.
		 */
		std::shared_ptr<graphic::Model>
			loadObj(const std::string &path,
					const utility::graphic::PoseF &pose = utility::graphic::PoseF(),
					const std::string &material = "default_material");

		/**
		 * @brief Loads an OBJ model resource from a specified asset.
		 *
		 * @param modelAsset A shared pointer to the File object containing the
		 * OBJ model data to be loaded.
		 * @param pose The initial position and orientation for the model.
		 * @param material The name of the material to be associated with the
		 * loaded OBJ model. If not specified, the default material will be
		 * used.
		 *
		 * @return A shared pointer to the loaded Model object representing the
		 * OBJ model.
		 */
		std::shared_ptr<graphic::Model>
			loadObjFromAsset(std::shared_ptr<utility::File> modelAsset,
						 	 const utility::graphic::PoseF &pose = utility::graphic::PoseF(),
							 const std::string &material = "default_material");

		/**
		 * @brief Loads a shader resource from specified vertex and fragment
		 * shader file paths.
		 *
		 * @param vertexPath The file path to the vertex shader resource to be
		 * loaded.
		 * @param fragmentPath The file path to the fragment shader resource to
		 * be loaded.
		 *
		 * @return A shared pointer to the loaded Shader object.
		 */
		std::shared_ptr<graphic::Shader>
			loadShader(const std::string &vertexPath,
					   const std::string &fragmentPath);

		/**
		 * @brief Loads a shader resource from specified vertex and fragment
		 * shader assets.
		 *
		 * @param vertexAsset A shared pointer to the File object containing the
		 * vertex shader data to be loaded.
		 * @param fragmentAsset A shared pointer to the File object containing
		 * the fragment shader data to be loaded.
		 *
		 * @return A shared pointer to the loaded Shader object.
		 */
		std::shared_ptr<graphic::Shader>
			loadShaderFromAssets(std::shared_ptr<utility::File> vertexAsset,
								 std::shared_ptr<utility::File> fragmentAsset);

		/**
		 * @brief Loads a code points resource from a specified file path.
		 *
		 * @param path The file path to the `.codepoints` file to be loaded.
		 * @return A shared pointer to the loaded CodePoints object.
		 */
		std::shared_ptr<graphic::CodePoints>
			loadCodePoints(const std::string &path);

		/**
		 * @brief Loads a code points resource from a specified asset.
		 *
		 * @param codePointsAsset A shared pointer to the File object
		 * containing the `.codepoints` data to be loaded.
		 * @return A shared pointer to the loaded CodePoints object.
		 */
		std::shared_ptr<graphic::CodePoints> loadCodePointsFromAsset(
			std::shared_ptr<utility::File> codePointsAsset);

		/**
		 * @brief Loads an audio source resource from a specified file path.
		 *
		 * @param path The file path to the audio source resource to be loaded.
		 *
		 * @return A unique pointer to the loaded AudioSource object.
		 */
		std::unique_ptr<sound::AudioSource>
			loadAudioSource(const std::string &path);

		/**
		 * @brief Loads an audio source resource from a specified asset.
		 *
		 * @param audioAsset A shared pointer to the File object containing the
		 * audio source data to be loaded.
		 *
		 * @return A unique pointer to the loaded AudioSource object.
		 */
		std::unique_ptr<sound::AudioSource>
			loadAudioSourceFromAsset(std::shared_ptr<utility::File> audioAsset);

		protected:
		/**
		 * @brief Builds a unique shader name based on the vertex and fragment
		 * shader file paths.
		 *
		 * This method constructs a unique name for a shader by combining the
		 * vertex and fragment shader file paths. The resulting name can be used
		 * as a key in the internal map to store and retrieve shader resources
		 * efficiently. The method ensures that shaders with the same vertex and
		 * fragment paths will have the same name, allowing for proper caching
		 * and reuse of shader resources.
		 *
		 * @param vertexPath The file path to the vertex shader resource.
		 * @param fragmentPath The file path to the fragment shader resource.
		 *
		 * @return A string representing the unique shader name constructed from
		 * the vertex and fragment shader file paths.
		 */
		std::string buildShaderPath(const std::string &vertexPath,
									const std::string &fragmentPath) const;

		/**
		 * @brief Retrieves the next unique ID for a resource.
		 *
		 * This method increments the internal `nextID` counter and returns the
		 * next unique ID for a resource. It is used internally to assign unique
		 * IDs to loaded resources such as fonts, materials, textures, and
		 * models. The returned ID can be used as a key in the internal maps to
		 * store and retrieve resources efficiently.
		 *
		 * @note Do not modify the internal `nextID` variable directly. Use this
		 * method to ensure that unique IDs are generated correctly and
		 * consistently for all resources.
		 *
		 * @return A uint32_t representing the next unique ID for a resource.
		 * Each call to this method will return a different ID, ensuring that
		 * all resources have unique identifiers.
		 */
		uint32_t getNextID();

		/**
		 * @brief Internal counter for generating unique IDs for resources
		 *
		 * @note Do not modify this variable directly.
		 * Use the getNextID() method to retrieve the next unique ID for a
		 * resource.
		 */
		uint32_t _currentID = 1;

		/**
		 * @brief Internal maps to store loaded fonts for efficient retrieval.
		 */
		std::map<uint32_t, std::shared_ptr<graphic::Font>> _fonts;

		/**
		 * @brief Internal map to store loaded materials for efficient
		 * retrieval.
		 */
		std::map<uint32_t, std::shared_ptr<graphic::Material>> _materials;

		/**
		 * @brief Internal map to store loaded textures for efficient retrieval.
		 */
		std::map<uint32_t, std::shared_ptr<graphic::Texture>> _textures;

		/**
		 * @brief Internal map to store loaded models for efficient retrieval.
		 */
		std::map<uint32_t, std::shared_ptr<graphic::Model>> _models;

		/**
		 * @brief Internal map to store loaded shaders for efficient retrieval.
		 */
		std::map<uint32_t, std::shared_ptr<graphic::Shader>> _shaders;

		/**
		 * @brief Internal map to store loaded code points resources for
		 * efficient retrieval.
		 */
		std::map<uint32_t, std::shared_ptr<graphic::CodePoints>> _codePoints;

		/**
		 * @brief Internal map to store loaded audio buffers for efficient
		 * retrieval.
		 */
		std::map<uint32_t, std::shared_ptr<sound::AudioBuffer>> _audioSources;

		/**
		 * @brief Internal map to store resource IDs for efficient lookup based
		 * on file paths.
		 */
		std::unordered_map<std::string, uint32_t> _elementsIDs;

		/**
		 * @brief Reference to the SystemIO instance used for loading assets
		 * from file paths.
		 *
		 * The RessourceProvider relies on the SystemIO interface to load
		 * resources from the filesystem, and this member variable holds a
		 * reference to the SystemIO instance that is used for asset loading
		 * operations. It allows the RessourceProvider to access the necessary
		 * functionality of the SystemIO interface to read files and load
		 * resources based on file paths provided in the loading methods.
		 */
		SystemIO &_systemInterface;

		/**
		 * @brief An optional base path to prepend to resource paths when
		 * loading resources.
		 *
		 * This member variable holds a base path that can be used to specify a
		 * common directory for all resources. When loading resources, the
		 * RessourceProvider can prepend this base path to the provided resource
		 * paths, allowing for more flexible resource management and
		 * organization. This is particularly useful when all resources are
		 * stored in a specific directory, as it eliminates the need to provide
		 * the full path for each resource when loading them.
		 */
		std::string _basePath;

		/**
		 * @brief Internal audio manager instance for managing audio operations.
		 *
		 * This member variable holds an instance of the AudioManager that is
		 * used for managing audio playback and related operations. It handles
		 * the creation and management of audio sources loaded through the
		 * resource provider.
		 */
		utility::sound::AudioManager _audioManager;

		private:
		/**
		 * @brief Resolves a resource path by prepending the base path if it is
		 * set.
		 * This method takes a resource path as input and checks if a base path
		 * is set for the RessourceProvider. If a base path is set, it prepends
		 * the base path to the provided resource path to create a full path. If
		 * no base path is set, it returns the original resource path unchanged.
		 * This allows for flexible resource management, as it enables the use
		 * of a common base directory for all resources while still allowing for
		 * individual resource paths to be specified.
		 * @param path The original resource path to be resolved.
		 * @return The resolved resource path with the base path prepended if it
		 * is set, or the original path if no base path is set.
		 */
		std::string resolvePath(const std::string &path) const;

		using Loggable::getLogger;
	};
}	 // namespace utility
