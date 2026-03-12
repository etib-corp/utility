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

#include "utility/asset_manager/default_asset_manager.hpp"

bool utility::DefaultAssetManager::loadDirectory(const std::string &directory) {
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

std::shared_ptr<utility::FileAsset>
utility::DefaultAssetManager::add(const std::string &path) {
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

void utility::DefaultAssetManager::remove(const std::string &path, bool save) {
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

bool utility::DefaultAssetManager::save(const std::string &path,
                                        const std::string &newPath) {
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