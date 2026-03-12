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

#pragma once

#include "utility/asset_manager/asset_manager.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace utility {

/**
 * @class DefaultAssetManager
 * @brief The DefaultAssetManager class is a concrete implementation of the
 * AssetManager interface that loads assets from the file system.
 */
class DefaultAssetManager : public AssetManager {
public:
  /**
   * @brief Constructs a DefaultAssetManager.
   */
  DefaultAssetManager() = default;

  /**
   * @brief Default destructor for DefaultAssetManager.
   * @param directory The path to the directory containing the assets.
   * @return True if the assets were loaded successfully, false otherwise.
   */
  bool loadDirectory(const std::string &directory) override;

  /**
   * @brief Adds an asset to the manager by loading it from the file system.
   * @param path The path to the asset file.
   * @return A shared pointer to the loaded FileAsset, or nullptr if loading
   * failed.
   */
  std::shared_ptr<utility::FileAsset> add(const std::string &path) override;

  /**
   * @brief Removes an asset from the manager.
   * @param path The path to the asset to remove.
   * @param save Whether to save the asset before removing it.
   */
  void remove(const std::string &path, bool save = true) override;

  /**
   * @brief Saves an asset to the file system.
   * @param path The path to the asset to save.
   * @param newPath An optional new path to save the asset to. If not provided,
   * the asset will be saved to its original path.
   * @return True if the asset was saved successfully, false otherwise.
   */
  bool save(const std::string &path, const std::string &newPath = "") override;
};
} // namespace utility