/*
 Copyright (c) 2026 ETIB Corporation

 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include "utility/asset_manager/android_asset_manager.hpp"

#ifdef __ANDROID__

#include <filesystem>
#include <fstream>

namespace {
std::string NormalizePath(const std::string &path) {
  return std::filesystem::path(path).lexically_normal().string();
}
} // namespace

utility::AndroidAssetManager::AndroidAssetManager(AAssetManager *assetManager)
    : _assetManager(assetManager) {}

bool utility::AndroidAssetManager::loadDirectory(const std::string &directory) {
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

std::shared_ptr<utility::FileAsset>
utility::AndroidAssetManager::add(const std::string &path) {
  const std::string key = NormalizePath(path);
  if (this->exists(key)) {
    return this->open(key);
  }

  AAsset *file =
      AAssetManager_open(_assetManager, key.c_str(), AASSET_MODE_UNKNOWN);
  if (file == nullptr) {
    return nullptr;
  }

  off_t fileLength = AAsset_getLength(file);
  if (fileLength < 0) {
    AAsset_close(file);
    return nullptr;
  }

  std::string content(static_cast<size_t>(fileLength), '\0');
  if (!content.empty()) {
    const int bytesRead =
        AAsset_read(file, content.data(), static_cast<size_t>(fileLength));
    if (bytesRead < 0 || static_cast<off_t>(bytesRead) != fileLength) {
      AAsset_close(file);
      return nullptr;
    }
  }
  AAsset_close(file);

  auto asset = std::make_shared<utility::FileAsset>(path, content);
  _assets[key] = asset;
  return asset;
}

void utility::AndroidAssetManager::remove(const std::string &path, bool save) {
  const std::string key = NormalizePath(path);
  auto it = _assets.find(key);
  if (it != _assets.end()) {
    if (save) {
      this->save(key);
    }
    _assets.erase(it);
  } else {
    std::cerr << "Asset not found: " << key << std::endl;
  }
}

bool utility::AndroidAssetManager::save(const std::string &path,
                                        const std::string &newPath) {
  const std::string key = NormalizePath(path);
  auto it = _assets.find(key);
  if (it == _assets.end()) {
    std::cerr << "Asset not found: " << key << std::endl;
    return false;
  }
  // Android assets are read-only from the APK. Saving to a new path must be
  // provided.
  if (newPath.empty()) {
    std::cerr
        << "Cannot save Android asset to original path. Provide a newPath."
        << std::endl;
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