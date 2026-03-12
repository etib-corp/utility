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

utility::AndroidAssetManager::AndroidAssetManager(AssetManager *assetManager)
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
  AAsset *file =
      AAssetManager_open(_assetManager, path.c_str(), AASSET_MODE_UNKNOWN);
  if (file == nullptr) {
    return nullptr;
  }
  off_t fileLength = AAsset_getLength(file);
  std::string content(fileLength, '\0');
  AAsset_read(file, &content[0], fileLength);
  AAsset_close(file);
  return std::make_shared<utility::FileAsset>(content);
}

void utility::AndroidAssetManager::remove(const std::string &path, bool save) {
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

bool utility::AndroidAssetManager::save(const std::string &path,
                                        const std::string &newPath) {
  auto it = _assets.find(path);
  if (it == _assets.end()) {
    std::cerr << "Asset not found: " << path << std::endl;
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