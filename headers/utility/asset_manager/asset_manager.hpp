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

#include <iostream>
#include <filesystem>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "utility/asset_manager/file_asset.hpp"
#include "utility/math/vertex.hpp"

#include <tiny_obj_loader.h>

/**
 * @namespace utility
 * @brief The utility namespace contains classes and functions for the utility
 * project.
 */
namespace utility {
/**
 * @class AssetManager
 * @brief The AssetManager class is an abstract base class for managing
 * file assets.
 */
class AssetManager {
public:
  /**
  * @brief Default destructor for AssetManager.
   */
  virtual ~AssetManager() = default;

  /**
   * @brief Loads assets from a directory.
   * @param directory The path to the directory containing the assets.
   * @return True if the assets were loaded successfully, false otherwise.
   *
   * This method is pure virtual and must be implemented by derived
   * classes. It is responsible for loading all assets from the specified
   * directory by reading the file content and storing it in the _assets
   * map.
   */
  virtual bool loadDirectory(const std::string &directory) = 0;

  /**
   * @brief Loads assets from a directory.
   * @param directory The filesystem path to the directory containing assets.
   * @return True if the assets were loaded successfully, false otherwise.
   */
  bool loadDirectory(const std::filesystem::path &directory) {
    return loadDirectory(directory.string());
  }

  /**
   * @brief Adds an asset to the manager.
   * @param path The path to the asset.
   * @return A shared pointer to the FileAsset object.
   *
   * This method is pure virtual and must be implemented by derived
   * classes. This method is responsible for loading the asset from the
   * specified path by reading the file content and storing it in the
   * _assets map.
   */
  virtual std::shared_ptr<utility::FileAsset> add(const std::string &path) = 0;

  /**
   * @brief Adds an asset to the manager.
   * @param path The filesystem path to the asset.
   * @return A shared pointer to the FileAsset object.
   */
  std::shared_ptr<utility::FileAsset> add(const std::filesystem::path &path) {
    return add(path.string());
  }

  /**
   * @brief Removes an asset from the manager.
   * @param path The path to the asset.
   * @param save Whether to save the asset before removing it (default is
   * true).
   *
   * This method removes the asset from the _assets map.
   * When removing an asset, the asset file will not be deleted from the
   * disk. When removing an asset, its content is updated on the disk if
   * save is true. If save is false, the asset will be removed from the
   * _assets map without saving its content on the disk. Using a deleted
   * asset will result in undefined behavior.
   */
  virtual void remove(const std::string &path, bool save = true) = 0;

  /**
   * @brief Removes an asset from the manager.
   * @param path The filesystem path to the asset.
   * @param save Whether to save the asset before removing it.
   */
  void remove(const std::filesystem::path &path, bool save = true) {
    remove(path.string(), save);
  }

  /**
   * @brief Saves an asset to the disk.
   * @param path The path to the asset.
   * @param newPath The new path to save the asset to (optional).
   * @return True if the asset was saved successfully, false otherwise.
   *
   * This method is pure virtual and must be implemented by derived
   * classes. It is responsible for saving the content of the asset to the
   * specified path. If newPath is provided, it will save the asset to
   * that path and will not update the original path. If newPath is not
   * provided, it will save the asset to the original path.
   */
  virtual bool save(const std::string &path,
                    const std::string &newPath = "") = 0;

  /**
   * @brief Saves an asset to the disk.
   * @param path The filesystem path to the managed asset.
   * @param newPath The target filesystem path where the asset is written.
   * @return True if the asset was saved successfully, false otherwise.
   */
  bool save(const std::filesystem::path &path,
            const std::filesystem::path &newPath) {
    return save(path.string(), newPath.string());
  }

  /**
   * @brief Saves an asset to its original path.
   * @param path The filesystem path to the managed asset.
   * @return True if the asset was saved successfully, false otherwise.
   */
  bool save(const std::filesystem::path &path) {
    return save(path.string());
  }

  /**
   * @brief Checks if an asset exists in the manager.
   * @param path The path to the asset.
   * @return True if the asset exists, false otherwise.
   *
   * This method checks if the asset is present in the _assets map.
   */
  bool exists(const std::string &path) const;

  /**
   * @brief Checks if an asset exists in the manager.
   * @param path The filesystem path to the asset.
   * @return True if the asset exists, false otherwise.
   */
  bool exists(const std::filesystem::path &path) const {
    return exists(path.string());
  }

  /**
   * @brief Opens an asset from the manager.
   * @param path The path to the asset.
   * @return A shared pointer to the FileAsset object.
   *
   * This method retrieves the asset from the _assets map.
   * If the asset does not exist, it returns a nullptr.
   */
  std::shared_ptr<utility::FileAsset> open(const std::string &path) const;

  /**
   * @brief Opens an asset from the manager.
   * @param path The filesystem path to the asset.
   * @return A shared pointer to the FileAsset object.
   */
  std::shared_ptr<utility::FileAsset> open(const std::filesystem::path &path) const {
    return open(path.string());
  }

  /**
   * @brief Loads a model from a file.
   * @param path The path to the model file.
   * @return A vector of Vertex objects representing the model.
   *
   * This method is responsible for loading a model from the specified
   * file and returning its vertices as a vector of Vertex objects.
   */
  std::vector<utility::math::Vertex<float, float>>
  loadModel(const std::string &path);

  /**
   * @brief Loads a model from a file.
   * @param path The filesystem path to the model file.
   * @return A vector of Vertex objects representing the model.
   */
  std::vector<utility::math::Vertex<float, float>>
  loadModel(const std::filesystem::path &path) {
    return loadModel(path.string());
  }

protected:
  /**
   * @brief Map of loaded assets.
   *
   * Key: asset path.
   * Value: shared pointer to the corresponding FileAsset.
   */
  std::map<std::string, std::shared_ptr<utility::FileAsset>> _assets;
};
} // namespace utility
