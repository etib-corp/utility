/*
** EPITECH PROJECT, 2026
** utility
** File description:
** DefaultAssetManager
*/

#include "utility/AssetManager/DefaultAssetManager.hpp"

bool utility::DefaultAssetManager::loadDirectory(const std::string &directory)
{
    for (const auto &entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            const std::string path = entry.path().string();
            if (!this->add(path)) {
                std::cerr << "Failed to load asset: " << path << std::endl;
            }
        }
    }
    return true;
}

std::shared_ptr<utility::FileAsset> utility::DefaultAssetManager::add(const std::string &path)
{
    if (this->exists(path)) {
		return _assets[path];
	}
	std::ifstream file(path, std::ios::binary);

	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << path << std::endl;
		return nullptr;
	}
	std::string content;
	file.seekg(0, std::ios::end);
	content.resize(file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&content[0], content.size());
	file.close();
	_assets[path] = std::make_shared<utility::FileAsset>(content);
	if (!_assets[path]) {
		std::cerr << "Failed to create FileAsset for: " << path << std::endl;
		return nullptr;
	}
	return _assets[path];
}

void utility::DefaultAssetManager::remove(const std::string &path, bool save)
{
	auto it = _assets.find(path);
	if (it != _assets.end()) {
		if (save) {
			this->save(path);
		}
		_assets.erase(it);
	} else {
		std::cerr << "Asset not found: " << path << std::endl;
	}
}

bool utility::DefaultAssetManager::save(const std::string &path, const std::string &newPath)
{
    auto it = _assets.find(path);
    if (it == _assets.end()) {
        std::cerr << "Asset not found: " << path << std::endl;
        return false;
    }
    const std::string &content = it->second->content();
    std::string savePath = newPath.empty() ? path : newPath;
    std::ofstream file(savePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << savePath << std::endl;
        return false;
    }
    file.write(content.data(), content.size());
    file.close();
    return true;
}