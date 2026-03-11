/*
** ETIB PROJECT, 2025
** utility
** File description:
** AAssetManager
*/

#include "utility/AssetManager/AAssetManager.hpp"

bool utility::AAssetManager::exists(const std::string &path) const
{
	return _assets.find(path) != _assets.end();
}

std::shared_ptr<utility::FileAsset>
	utility::AAssetManager::get(const std::string &path)
{
	if (exists(path)) {
		return _assets[path];
	}
	return nullptr;
}