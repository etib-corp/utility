/*
** ETIB PROJECT, 2026
** utility
** File description:
** material
*/

#include <utility/graphic/material.hpp>

#include <utility/ressource_provider.hpp>

namespace utility::graphic
{
	Material::Material(RessourceProvider &ressourceProvider,
					   const std::string &shaderName,
					   const std::vector<File> &textureAssets)
		: _shaderName(shaderName)
		, _version(0)
	{
		for (const auto &textureAsset: textureAssets) {
			auto texture = ressourceProvider.loadTextureFromAsset(
				std::make_shared<File>(textureAsset));

			if (!texture) {
				throw std::runtime_error("Failed to load texture asset: "
										 + textureAsset.path());
			}

			_textures[textureAsset.path()] = texture;
		}
	}

	std::shared_ptr<Texture> Material::getTexture(const std::string &name) const
	{
		auto it = _textures.find(name);
		if (it != _textures.end()) {
			return it->second;
		}
		return nullptr;
	}

	const std::vector<std::shared_ptr<Texture>> &Material::getTextures() const
	{
		static std::vector<std::shared_ptr<Texture>> textures;
		textures.clear();
		for (const auto &[_, texture]: _textures) {
			textures.push_back(texture);
		}
		return textures;
	}

	const std::string &Material::getShaderName() const
	{
		return _shaderName;
	}

	uint32_t Material::getVersion() const
	{
		return _version;
	}
}	 // namespace utility::graphic
