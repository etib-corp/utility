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

#include "assetmanager/test_default_asset_manager.hpp"

TEST_F(TestDefaultAssetManager, LoadDirectory) {
  utility::DefaultAssetManager assetManager;
  assetManager.loadDirectory("../tests/sources/assetmanager/testAsset");
  EXPECT_TRUE(assetManager.exists("../tests/sources/assetmanager/testAsset/file1"));
}

TEST_F(TestDefaultAssetManager, AddAsset) {
  utility::DefaultAssetManager assetManager;
  auto asset = assetManager.add("../tests/sources/assetmanager/testAsset/file2");
  EXPECT_TRUE(assetManager.exists("../tests/sources/assetmanager/testAsset/file2"));
  EXPECT_NE(asset, nullptr);
}

TEST_F(TestDefaultAssetManager, RemoveAsset) {
  utility::DefaultAssetManager assetManager;
  assetManager.loadDirectory("../tests/sources/assetmanager/testAsset");
  assetManager.remove("../tests/sources/assetmanager/testAsset/file1");
  EXPECT_FALSE(assetManager.exists("../tests/sources/assetmanager/testAsset/file1"));
}

TEST_F(TestDefaultAssetManager, SaveAsset) {
  utility::DefaultAssetManager assetManager;
  auto asset = assetManager.add("../tests/sources/assetmanager/testAsset/file2");
  assetManager.save("../tests/sources/assetmanager/testAsset/file2");
  EXPECT_TRUE(assetManager.exists("../tests/sources/assetmanager/testAsset/file2"));
}

TEST_F(TestDefaultAssetManager, GetAsset) {
  utility::DefaultAssetManager assetManager;
  assetManager.loadDirectory("../tests/sources/assetmanager/testAsset");
  auto asset = assetManager.get("../tests/sources/assetmanager/testAsset/file1");
  EXPECT_NE(asset, nullptr);
}

TEST_F(TestDefaultAssetManager, GetNonExistentAsset) {
  utility::DefaultAssetManager assetManager;
  auto asset = assetManager.get("../tests/sources/assetmanager/testAsset/nonexistent");
  EXPECT_EQ(asset, nullptr);
}

// Test the writing and reading of an asset
TEST_F(TestDefaultAssetManager, WriteAndReadAsset) {
  utility::DefaultAssetManager assetManager;
  auto asset = assetManager.add("../tests/sources/assetmanager/testAsset/file3");
  std::string data = "Hello, World!";
  asset->write(data.c_str(), sizeof(char), data.size());
  asset->seek(0, utility::FileAsset::Seek::SET);
  std::string readData;
  asset->read(readData, sizeof(char), data.size());
  EXPECT_EQ(data, readData);
}
