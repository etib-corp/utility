/*
** EPITECH PROJECT, 2026
** utility
** File description:
** AndroidAssetManagerr
*/

#include "utility/AssetManager/AndroidAssetManager.hpp"

#ifdef __ANDROID__

utility::AndroidAssetManager::AndroidAssetManager(AAssetManager *assetManager)
    : _assetManager(assetManager)
{
}

bool utility::AndroidAssetManager::loadDirectory(const std::string &directory)
{
    AAssetDir *assetDir = AAssetManager_openDir(_assetManager, directory.c_str());
    if (assetDir == nullptr) {
        std::cerr << "Failed to open asset directory: " << directory << std::endl;
        return false;
    }

    const char *fileName = nullptr;
    while ((fileName = AAssetDir_getNextFileName(assetDir)) != nullptr) {
        std::string assetPath = directory + "/" + fileName;
        if (!this->add(assetPath)) {
            std::cerr << "Failed to load asset: " << assetPath << std::endl;
        }
    }
    AAssetDir_close(assetDir);
    return true;
}

std::shared_ptr<utility::FileAsset> utility::AndroidAssetManager::add(const std::string &path)
{
    AAsset *file = AAssetManager_open(_assetManager, path.c_str(), AASSET_MODE_UNKNOWN);
    if (file == nullptr) {
        return nullptr;
    }
    off_t fileLength = AAsset_getLength(file);
    std::string content(fileLength, '\0');
    AAsset_read(file, &content[0], fileLength);
    AAsset_close(file);
    return std::make_shared<utility::FileAsset>(content);
}

void utility::AndroidAssetManager::remove(const std::string &path, bool save)
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

bool utility::AndroidAssetManager::save(const std::string &path, const std::string &newPath)
{
    auto it = _assets.find(path);
    if (it == _assets.end()) {
        std::cerr << "Asset not found: " << path << std::endl;
        return false;
    }
    // Android assets are read-only from the APK. Saving to a new path must be provided.
    if (newPath.empty()) {
        std::cerr << "Cannot save Android asset to original path. Provide a newPath." << std::endl;
        return false;
    }
    const std::string &content = it->second->content();
    std::ofstream file(newPath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << newPath << std::endl;
        return false;
    }
    file.write(content.data(), content.size());
    file.close();
    return true;
}

#endif // __ANDROID__