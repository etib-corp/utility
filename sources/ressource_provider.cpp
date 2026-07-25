/*
** ETIB PROJECT, 2026
** utility
** File description:
** ressource_provider
*/

#include <utility/ressource_provider.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace utility
{

	RessourceProvider::RessourceProvider(SystemIO &systemInterface,
										 const std::string &basePath)
		: _systemInterface(systemInterface)
		, _basePath(basePath)
	{
		getLogger().info() << "RessourceProvider initialized with base path: "
						   << basePath;
	}

	/////////////
	// Getters //
	/////////////

	std::map<uint32_t, std::shared_ptr<graphic::Material>>
		RessourceProvider::getMaterials() const
	{
		return _materials;
	}

	std::map<uint32_t, std::shared_ptr<graphic::Texture>>
		RessourceProvider::getTextures() const
	{
		return _textures;
	}

	std::map<uint32_t, std::shared_ptr<graphic::Model>>
		RessourceProvider::getModels() const
	{
		return _models;
	}

	std::map<uint32_t, std::shared_ptr<graphic::Shader>>
		RessourceProvider::getShaders() const
	{
		return _shaders;
	}

	std::map<uint32_t, std::shared_ptr<graphic::CodePoints>>
		RessourceProvider::getCodePoints() const
	{
		return _codePoints;
	}

	uint32_t RessourceProvider::getShaderID(const std::string &shaderName) const
	{
		for (const auto &[name, id]: _elementsIDs) {
			const auto &shaderIt = _shaders.find(id);

			if (name.starts_with(shaderName) && shaderIt != _shaders.end()) {
				return id;
			}
		}
		return 0;	 // Return 0 if the shader name is not found
	}

	uint32_t RessourceProvider::getMaterialID(const std::string &materialName)
	{
		auto it = _elementsIDs.find(resolvePath(materialName));

		if (it != _elementsIDs.end()) {
			return it->second;
		}

		if (materialName == "default_material") {
			return getDefaultMaterialID();
		}

		if (materialName == "mesh_material") {
			return getMeshMaterialID();
		}

		return 0;
	}

	uint32_t RessourceProvider::getDefaultMaterialID()
	{
		auto it = _elementsIDs.find("default_material");

		if (it != _elementsIDs.end()) {
			return it->second;
		}

		auto id = getNextID();

		auto textureFile =
			_systemInterface.add(resolvePath("textures/default_texture.png"));

		_materials[id] = std::make_shared<graphic::Material>(
			*this, std::string("default"), std::vector<File> { *textureFile });
		_elementsIDs["default_material"] = id;

		return id;
	}

	uint32_t RessourceProvider::getMeshMaterialID()
	{
		auto it = _elementsIDs.find("mesh_material");

		if (it != _elementsIDs.end()) {
			return it->second;
		}

		auto id = getNextID();

		auto textureFile =
			_systemInterface.add(resolvePath("textures/default_texture.png"));

		_materials[id] = std::make_shared<graphic::Material>(
			*this, std::string("mesh"), std::vector<File> { *textureFile });
		_elementsIDs["mesh_material"] = id;

		return id;
	}

	////////////////////
	// Public Methods //
	////////////////////

	std::shared_ptr<graphic::Font>
		RessourceProvider::loadFont(const std::string &path)
	{
		std::string resolvedPath = resolvePath(path);
		auto it					 = _elementsIDs.find(resolvedPath);

		if (it != _elementsIDs.end()) {
			if (_fonts.find(it->second) != _fonts.end()) {
				return _fonts[it->second];
			}
		}

		auto fontAsset = _systemInterface.add(resolvedPath);

		if (!fontAsset) {
			getLogger().warning() << "Failed to load font asset: " << path;
			return nullptr;
		}

		auto font = loadFontFromAsset(fontAsset);

		return font;
	}

	std::shared_ptr<graphic::Font> RessourceProvider::loadFontFromAsset(
		std::shared_ptr<utility::File> fontAsset)
	{
		auto it = _elementsIDs.find(fontAsset->path());

		if (it != _elementsIDs.end()) {
			if (_fonts.find(it->second) != _fonts.end()) {
				return _fonts[it->second];
			}
		}

		auto font = std::make_shared<graphic::Font>(std::vector { *fontAsset });
		auto fontID = getNextID();

		_fonts[fontID]					= font;
		_elementsIDs[fontAsset->path()] = fontID;

		font->onNewTextureCreated =
			[this](std::string name, std::shared_ptr<graphic::Texture> atlas) {
				auto textureID	 = getNextID();
				auto materialKey = name + "_material";

				_textures[textureID] = atlas;
				_elementsIDs[name]	 = textureID;

				auto materialKeyIt = _elementsIDs.find(materialKey);
				if (materialKeyIt == _elementsIDs.end()) {
					auto textMaterial =
						std::make_shared<graphic::TextMaterial>();
					auto materialID = getNextID();

					_materials[materialID]	  = textMaterial;
					_elementsIDs[materialKey] = materialID;
					materialKeyIt			  = _elementsIDs.find(materialKey);
				}

				if (materialKeyIt == _elementsIDs.end()) {
					getLogger().warning()
						<< "Missing text material entry for font atlas: "
						<< name;
					return;
				}

				auto materialIt = _materials.find(materialKeyIt->second);

				if (materialIt == _materials.end()) {
					getLogger().warning()
						<< "Missing text material for font atlas: " << name;
					return;
				}

				auto atlasMaterial =
					std::dynamic_pointer_cast<graphic::TextMaterial>(
						materialIt->second);

				if (!atlasMaterial) {
					getLogger().warning()
						<< "Misconfigured material for font: " << name
						<< " is not a TextMaterial";
					return;
				}

				atlasMaterial->addAtlas(name, atlas);
			};

		return font;
	}

	std::shared_ptr<graphic::Font> RessourceProvider::loadFontFamilyFromAssets(
		const std::vector<std::shared_ptr<utility::File>> &fontAssets)
	{
		std::vector<File> assets;
		std::string familyName;

		if (!fontAssets.empty()) {
			familyName = fontAssets[0]->path();

			auto lastSlashPos = familyName.find_last_of("/\\");

			if (lastSlashPos != std::string::npos) {
				familyName = familyName.substr(lastSlashPos + 1);
			}

			auto dotPos = familyName.find_last_of(".");

			if (dotPos != std::string::npos) {
				familyName = familyName.substr(0, dotPos);
			}
		}

		for (const auto &asset: fontAssets) {
			assets.push_back(*asset);
		}

		auto it = _elementsIDs.find(familyName);

		if (it != _elementsIDs.end()) {
			if (_fonts.find(it->second) != _fonts.end()) {
				return _fonts[it->second];
			}
		}

		auto font	= std::make_shared<graphic::Font>(assets);
		auto fontID = getNextID();

		_fonts[fontID]			 = font;
		_elementsIDs[familyName] = fontID;

		font->onNewTextureCreated =
			[this](std::string name, std::shared_ptr<graphic::Texture> atlas) {
				auto textureID	 = getNextID();
				auto materialKey = name + "_material";

				_textures[textureID] = atlas;
				_elementsIDs[name]	 = textureID;

				auto materialKeyIt = _elementsIDs.find(materialKey);
				if (materialKeyIt == _elementsIDs.end()) {
					auto textMaterial =
						std::make_shared<graphic::TextMaterial>();
					auto materialID = getNextID();

					_materials[materialID]	  = textMaterial;
					_elementsIDs[materialKey] = materialID;
					materialKeyIt			  = _elementsIDs.find(materialKey);
				}

				if (materialKeyIt == _elementsIDs.end()) {
					getLogger().warning()
						<< "Missing text material entry for font atlas: "
						<< name;
					return;
				}

				auto materialIt = _materials.find(materialKeyIt->second);

				if (materialIt == _materials.end()) {
					getLogger().warning()
						<< "Missing text material for font atlas: " << name;
					return;
				}

				auto atlasMaterial =
					std::dynamic_pointer_cast<graphic::TextMaterial>(
						materialIt->second);

				if (!atlasMaterial) {
					getLogger().warning()
						<< "Misconfigured material for font: " << name
						<< " is not a TextMaterial";
					return;
				}

				atlasMaterial->addAtlas(name, atlas);
			};

		return font;
	}

	std::shared_ptr<graphic::Material>
		RessourceProvider::loadMaterial(const std::string &path,
										ShaderType shaderType)
	{
		auto it = _elementsIDs.find(resolvePath(path));

		if (it != _elementsIDs.end()) {
			if (_materials.find(it->second) != _materials.end()) {
				return _materials[it->second];
			}
		}

		auto materialAsset = _systemInterface.add(resolvePath(path));

		if (!materialAsset) {
			getLogger().warning() << "Failed to load material asset: " << path;
			return nullptr;
		}

		auto material = loadMaterialFromAsset(shaderType, materialAsset);

		return material;
	}

	std::shared_ptr<graphic::Material> RessourceProvider::loadMaterialFromAsset(
		ShaderType shaderType, std::shared_ptr<utility::File> materialAsset)
	{
		auto it = _elementsIDs.find(materialAsset->path());

		if (it != _elementsIDs.end()) {
			if (_materials.find(it->second) != _materials.end()) {
				return _materials[it->second];
			}
		}

		std::string shaderName =
			(shaderType == ShaderType::TEXT_SHADER) ? "text" : "mesh";
		std::vector<File> textureAssets = { *materialAsset };
		auto material = std::make_shared<graphic::Material>(*this, shaderName,
															textureAssets);
		auto id		  = getNextID();

		// TODO: we should discuss about the format of the material file to be
		// able to load the textures from the material file and store them in
		// the material object
		_materials[id] = material;

		return _materials[id];
	}

	std::shared_ptr<graphic::Texture>
		RessourceProvider::loadTexture(const std::string &path)
	{
		std::string resolvedPath = resolvePath(path);
		auto it					 = _elementsIDs.find(resolvedPath);

		if (it != _elementsIDs.end()) {
			if (_textures.find(it->second) != _textures.end()) {
				return _textures[it->second];
			}
		}

		auto textureAsset = _systemInterface.add(resolvedPath);

		if (!textureAsset) {
			getLogger().warning() << "Failed to load texture asset: " << path;
			return nullptr;
		}

		auto texture = loadTextureFromAsset(textureAsset);

		return texture;
	}

	std::shared_ptr<graphic::Texture> RessourceProvider::loadTextureFromAsset(
		std::shared_ptr<utility::File> textureAsset)
	{
		auto it = _elementsIDs.find(textureAsset->path());

		if (it != _elementsIDs.end()) {
			if (_textures.find(it->second) != _textures.end()) {
				return _textures[it->second];
			}
		}

		int texWidth	= 0;
		int texHeight	= 0;
		int texChannels = 0;

		stbi_uc *pixels = stbi_load_from_memory(
			reinterpret_cast<const stbi_uc *>(textureAsset->content().c_str()),
			textureAsset->size(), &texWidth, &texHeight, &texChannels,
			STBI_rgb_alpha);

		if (!pixels) {
			getLogger().warning()
				<< "Failed to load texture: " << textureAsset->path();
			return nullptr;
		}

		auto id = getNextID();

		_textures[id] = std::make_shared<graphic::Texture>(texWidth, texHeight);
		std::copy(pixels, pixels + (texWidth * texHeight * 4),
				  _textures[id]->_pixels.data());

		_elementsIDs[textureAsset->path()] = id;
		return _textures[id];
	}

	std::shared_ptr<graphic::Model>
		RessourceProvider::loadModel(const std::string &path,
									 const utility::graphic::PoseF &pose,
									 const std::string &material)
	{
		std::string resolvedPath = resolvePath(path);
		auto it					 = _elementsIDs.find(resolvedPath);

		if (it != _elementsIDs.end()) {
			if (_models.find(it->second) != _models.end()) {
				return _models[it->second];
			}
		}

		auto modelAsset = _systemInterface.add(resolvedPath);

		if (!modelAsset) {
			getLogger().warning() << "Failed to load model asset: " << path;
			return nullptr;
		}

		auto id = getNextID();

		_models[id] = loadModelFromAsset(modelAsset, pose, material);

		return _models[id];
	}

	std::shared_ptr<graphic::Model> RessourceProvider::loadModelFromAsset(
		std::shared_ptr<utility::File> modelAsset, const utility::graphic::PoseF &pose, const std::string &material)
	{
		auto it = _elementsIDs.find(modelAsset->path());

		if (it != _elementsIDs.end()) {
			if (_models.find(it->second) != _models.end()) {
				return _models[it->second];
			}
		}

		auto materialID = getMaterialID(
			resolvePath(material));	   // Default material ID if not found

		if (materialID == 0) {
			loadMaterial(material, ShaderType::MESH_SHADER);
			materialID = getMaterialID(resolvePath(material));

			if (materialID == 0) {
				getLogger().warning() << "Material not found: " << material
									  << ". Using default material for model: "
									  << modelAsset->path();
				materialID = getDefaultMaterialID();
			}
		}

		auto model = std::make_shared<graphic::Model>(modelAsset, pose, materialID);
		auto id	   = getNextID();

		_models[id] = model;

		return _models[id];
	}

	std::shared_ptr<graphic::Model> RessourceProvider::loadModelFromAsset(
		std::shared_ptr<utility::File> modelAsset,
		graphic::Model::ModelType type, const utility::graphic::PoseF &pose, const std::string &material)
	{
		auto it = _elementsIDs.find(modelAsset->path());

		if (it != _elementsIDs.end()) {
			if (_models.find(it->second) != _models.end()) {
				return _models[it->second];
			}
		}

		auto materialID = getMaterialID(resolvePath(material));

		if (materialID == 0) {
			getLogger().warning()
				<< "Material not found: " << material
				<< ". Using default material for model: " << modelAsset->path();
			materialID = getDefaultMaterialID();
		}

		auto model =
			std::make_shared<graphic::Model>(modelAsset, type, pose, materialID);
		auto id = getNextID();

		_models[id] = model;

		return _models[id];
	}

	std::shared_ptr<graphic::Model>
		RessourceProvider::loadObj(const std::string &path,
								   const utility::graphic::PoseF &pose,
								   const std::string &material)
	{
		std::string resolvedPath = resolvePath(path);
		auto it					 = _elementsIDs.find(resolvedPath);

		if (it != _elementsIDs.end()) {
			if (_models.find(it->second) != _models.end()) {
				return _models[it->second];
			}
		}

		auto modelAsset = _systemInterface.add(resolvedPath);

		if (!modelAsset) {
			getLogger().warning() << "Failed to load model asset: " << path;
			return nullptr;
		}

		auto materialID = getMaterialID(resolvePath(material));

		if (materialID == 0) {
			getLogger().warning()
				<< "Material not found: " << material
				<< ". Using default material for model: " << modelAsset->path();
			materialID = getDefaultMaterialID();
		}

		auto model = std::make_shared<graphic::Model>(
			modelAsset, graphic::Model::ModelType::OBJ, pose, materialID);
		auto id = getNextID();

		_models[id] = model;

		return _models[id];
	}

	std::shared_ptr<graphic::Model> RessourceProvider::loadObjFromAsset(
		std::shared_ptr<utility::File> modelAsset, const utility::graphic::PoseF &pose,
		const std::string &material)
	{
		auto it = _elementsIDs.find(modelAsset->path());

		if (it != _elementsIDs.end()) {
			if (_models.find(it->second) != _models.end()) {
				return _models[it->second];
			}
		}

		auto materialID = getMaterialID(resolvePath(material));

		if (materialID == 0) {
			getLogger().warning()
				<< "Material not found: " << material
				<< ". Using default material for model: " << modelAsset->path();
			materialID = getDefaultMaterialID();
		}

		auto model = std::make_shared<graphic::Model>(
			modelAsset, graphic::Model::ModelType::OBJ, pose, materialID);
		auto id = getNextID();

		_models[id] = model;

		return _models[id];
	}

	std::shared_ptr<graphic::Shader>
		RessourceProvider::loadShader(const std::string &vertexPath,
									  const std::string &fragmentPath)
	{
		std::string resolvedVertexPath	 = resolvePath(vertexPath);
		std::string resolvedFragmentPath = resolvePath(fragmentPath);
		auto path = buildShaderPath(resolvedVertexPath, resolvedFragmentPath);
		auto it	  = _elementsIDs.find(path);

		if (it != _elementsIDs.end()) {
			if (_shaders.find(it->second) != _shaders.end()) {
				return _shaders[it->second];
			}
		}

		auto vertex	  = _systemInterface.add(resolvedVertexPath);
		auto fragment = _systemInterface.add(resolvedFragmentPath);

		if (!vertex) {
			getLogger().warning()
				<< "Failed to load shader asset: " << vertexPath;
			return nullptr;
		}

		if (!fragment) {
			getLogger().warning()
				<< "Failed to load shader asset: " << fragmentPath;
			return nullptr;
		}

		auto shader = std::make_shared<graphic::Shader>(vertex->content(),
														fragment->content());
		auto id		= getNextID();

		_shaders[id]	   = shader;
		_elementsIDs[path] = id;

		return _shaders[id];
	}

	std::shared_ptr<graphic::Shader> RessourceProvider::loadShaderFromAssets(
		std::shared_ptr<utility::File> vertexAsset,
		std::shared_ptr<utility::File> fragmentAsset)
	{
		auto path = buildShaderPath(vertexAsset->path(), fragmentAsset->path());
		auto it	  = _elementsIDs.find(path);

		if (it != _elementsIDs.end()) {
			if (_shaders.find(it->second) != _shaders.end()) {
				return _shaders[it->second];
			}
		}

		auto shader = std::make_shared<graphic::Shader>(
			vertexAsset->content(), fragmentAsset->content());
		auto id = getNextID();

		_shaders[id]	   = shader;
		_elementsIDs[path] = id;

		return _shaders[id];
	}

	std::shared_ptr<graphic::CodePoints>
		RessourceProvider::loadCodePoints(const std::string &path)
	{
		std::string resolvedPath = resolvePath(path);
		auto it					 = _elementsIDs.find(resolvedPath);

		if (it != _elementsIDs.end()) {
			if (_codePoints.find(it->second) != _codePoints.end()) {
				return _codePoints[it->second];
			}
		}

		auto codePointsAsset = _systemInterface.add(resolvedPath);

		if (!codePointsAsset) {
			getLogger().warning()
				<< "Failed to load codepoints asset: " << path;
			return nullptr;
		}

		auto codePoints = loadCodePointsFromAsset(codePointsAsset);

		return codePoints;
	}

	std::shared_ptr<graphic::CodePoints>
		RessourceProvider::loadCodePointsFromAsset(
			std::shared_ptr<utility::File> codePointsAsset)
	{
		auto it = _elementsIDs.find(codePointsAsset->path());

		if (it != _elementsIDs.end()) {
			if (_codePoints.find(it->second) != _codePoints.end()) {
				return _codePoints[it->second];
			}
		}

		auto codePoints =
			std::make_shared<graphic::CodePoints>(codePointsAsset->content());
		auto id = getNextID();

		_codePoints[id]						  = codePoints;
		_elementsIDs[codePointsAsset->path()] = id;

		return _codePoints[id];
	}

	std::unique_ptr<sound::AudioSource>
		RessourceProvider::loadAudioSource(const std::string &path)
	{
		std::string resolvedPath = resolvePath(path);
		auto it					 = _elementsIDs.find(resolvedPath);

		if (it != _elementsIDs.end()) {
			if (_audioSources.find(it->second) != _audioSources.end()) {
				auto audioBuffer = _audioSources[it->second];
				return _audioManager.createAudioSource(audioBuffer);
			}
		}

		auto audioAsset = _systemInterface.add(resolvedPath);

		if (!audioAsset) {
			getLogger().warning() << "Failed to load audio asset: " << path;
			return nullptr;
		}

		auto audioSource = loadAudioSourceFromAsset(audioAsset);

		return audioSource;
	}

	std::unique_ptr<sound::AudioSource>
		RessourceProvider::loadAudioSourceFromAsset(
			std::shared_ptr<utility::File> audioAsset)
	{
		auto it = _elementsIDs.find(audioAsset->path());

		if (it != _elementsIDs.end()) {
			if (_audioSources.find(it->second) != _audioSources.end()) {
				auto audioBuffer = _audioSources[it->second];
				return _audioManager.createAudioSource(audioBuffer);
			}
		}

		auto audioDecoder =
			sound::DecoderRegistry::getDecoderForFile(audioAsset->path());

		if (!audioDecoder) {
			getLogger().warning() << "Failed to get audio decoder for asset: "
								  << audioAsset->path();
			return nullptr;
		}

		auto audioBuffer = audioDecoder->decode(audioAsset);

		if (!audioBuffer) {
			getLogger().warning()
				<< "Failed to decode audio asset: " << audioAsset->path();
			return nullptr;
		}

		auto id = getNextID();

		_audioSources[id]				 = audioBuffer;
		_elementsIDs[audioAsset->path()] = id;

		return _audioManager.createAudioSource(audioBuffer);
	}

	///////////////////////
	// Protected Methods //
	///////////////////////

	std::string RessourceProvider::buildShaderPath(
		const std::string &vertexPath, const std::string &fragmentPath) const
	{
		std::string pureVertexName =
			vertexPath.substr(vertexPath.find_last_of("/\\") + 1);
		std::string pureFragmentName =
			fragmentPath.substr(fragmentPath.find_last_of("/\\") + 1);
		std::string path = pureVertexName + "_with_" + pureFragmentName;

		return path;
	}

	uint32_t RessourceProvider::getNextID()
	{
		return _currentID++;
	}

	///////////////////////
	// Protected Private //
	///////////////////////

	std::string RessourceProvider::resolvePath(const std::string &path) const
	{
		if (_basePath.empty())
			return path;

		if (_basePath.back() == '/' && !path.empty() && path.front() == '/')
			return _basePath + path.substr(1);

		if (_basePath.back() != '/' && !path.empty() && path.front() != '/')
			return _basePath + "/" + path;

		return _basePath + path;
	}
}	 // namespace utility
