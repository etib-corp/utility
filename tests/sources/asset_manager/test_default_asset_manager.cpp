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

#include "asset_manager/test_default_asset_manager.hpp"

#include <filesystem>
#include <string>

namespace {
const std::string kTestAssetDirectory =
  std::string(UTILITY_TEST_ASSETS_DIR) + "/testAsset";
} // namespace

TEST_F(TestDefaultAssetManager, LoadDirectory) {
  utility::DefaultAssetManager assetManager;
  assetManager.loadDirectory(kTestAssetDirectory);
  EXPECT_TRUE(assetManager.exists(kTestAssetDirectory + "/file1"));
}

TEST_F(TestDefaultAssetManager, AddAsset) {
  utility::DefaultAssetManager assetManager;
  auto asset = assetManager.add(kTestAssetDirectory + "/file2");
  EXPECT_TRUE(assetManager.exists(kTestAssetDirectory + "/file2"));
  EXPECT_NE(asset, nullptr);
}

TEST_F(TestDefaultAssetManager, AddAssetCachesInstance) {
  utility::DefaultAssetManager assetManager;
  auto first = assetManager.add(kTestAssetDirectory + "/file2");
  auto second = assetManager.add(kTestAssetDirectory + "/file2");
  ASSERT_NE(first, nullptr);
  EXPECT_EQ(first, second);
}

TEST_F(TestDefaultAssetManager, FilesystemPathOverloads) {
  utility::DefaultAssetManager assetManager;
  const std::filesystem::path directoryPath(kTestAssetDirectory);
  const std::filesystem::path filePath = directoryPath / "file2";

  EXPECT_TRUE(assetManager.loadDirectory(directoryPath));
  EXPECT_TRUE(assetManager.exists(filePath));

  auto fromGet = assetManager.get(filePath);
  auto fromAdd = assetManager.add(filePath);

  ASSERT_NE(fromGet, nullptr);
  EXPECT_EQ(fromGet, fromAdd);
}

TEST_F(TestDefaultAssetManager, RemoveAsset) {
  utility::DefaultAssetManager assetManager;
  assetManager.loadDirectory(kTestAssetDirectory);
  assetManager.remove(kTestAssetDirectory + "/file1");
  EXPECT_FALSE(assetManager.exists(kTestAssetDirectory + "/file1"));
}

TEST_F(TestDefaultAssetManager, SaveAsset) {
  utility::DefaultAssetManager assetManager;
  auto asset = assetManager.add(kTestAssetDirectory + "/file2");
  ASSERT_NE(asset, nullptr);
  assetManager.save(kTestAssetDirectory + "/file2");
  EXPECT_TRUE(assetManager.exists(kTestAssetDirectory + "/file2"));
}

TEST_F(TestDefaultAssetManager, SaveUnknownAssetFails) {
  utility::DefaultAssetManager assetManager;
  EXPECT_FALSE(assetManager.save(kTestAssetDirectory + "/missing"));
}

TEST_F(TestDefaultAssetManager, GetAsset) {
  utility::DefaultAssetManager assetManager;
  assetManager.loadDirectory(kTestAssetDirectory);
  auto asset = assetManager.get(kTestAssetDirectory + "/file1");
  EXPECT_NE(asset, nullptr);
}

TEST_F(TestDefaultAssetManager, GetNonExistentAsset) {
  utility::DefaultAssetManager assetManager;
  auto asset = assetManager.get(kTestAssetDirectory + "/nonexistent");
  EXPECT_EQ(asset, nullptr);
}

TEST_F(TestDefaultAssetManager, WriteAndReadAsset) {
  utility::DefaultAssetManager assetManager;
  auto asset = assetManager.add(kTestAssetDirectory + "/file3");
  ASSERT_NE(asset, nullptr);
  std::string data = "Hello, World!";
  asset->write(data.c_str(), sizeof(char), data.size());
  assetManager.save(kTestAssetDirectory + "/file3");
  asset->seek(0, utility::FileAsset::Seek::SET);
  std::string readData(data.size(), '\0');
  asset->read(readData, sizeof(char), data.size());
  EXPECT_EQ(data, readData);
  asset->clear();
  assetManager.save(kTestAssetDirectory + "/file3");
  asset->seek(0, utility::FileAsset::Seek::SET);
}

TEST_F(TestDefaultAssetManager, ReadStringWithoutPreSizing) {
  utility::DefaultAssetManager assetManager;
  auto asset = assetManager.add(kTestAssetDirectory + "/file2");
  ASSERT_NE(asset, nullptr);
  asset->seek(0, utility::FileAsset::Seek::SET);

  std::string data;
  const auto readCount = asset->read(data, sizeof(char), 5);

  EXPECT_EQ(readCount, 5);
  EXPECT_EQ(data.size(), 5);
}

TEST_F(TestDefaultAssetManager, LoadDirectoryInvalidPath) {
  utility::DefaultAssetManager assetManager;
  const auto invalidPath =
      (std::filesystem::path(kTestAssetDirectory) / "missing_directory").string();
  EXPECT_FALSE(assetManager.loadDirectory(invalidPath));
}

TEST_F(TestDefaultAssetManager, LoadModel) {
  utility::DefaultAssetManager assetManager;
  assetManager.loadDirectory(kTestAssetDirectory);
  auto vertices = assetManager.loadModel(kTestAssetDirectory + "/model.obj");
  EXPECT_EQ(vertices.size(), 11484);
}
