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

#include "utility/asset_manager/asset_manager.hpp"

bool utility::AssetManager::exists(const std::string &path) const {
  return _assets.find(path) != _assets.end();
}

std::shared_ptr<utility::FileAsset>
utility::AssetManager::get(const std::string &path) {
  if (exists(path)) {
    return _assets[path];
  }
  return nullptr;
}

std::vector<utility::math::Vertex<float, float>>
utility::AssetManager::loadModel(const std::string &path) {
  std::vector<utility::math::Vertex<float, float>> vertices;
  auto asset = get(path);
  if (asset == nullptr) {
    return vertices;
  }
  std::string content = asset->content();
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string warn;
  std::string err;
  std::istringstream input(content);
  bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, &input,
                              nullptr, true);
  if (!ret) {
    std::cerr << "Failed to load/parse .obj." << std::endl;
    return vertices;
  }
  for (const auto &shape : shapes) {
    for (const auto &index : shape.mesh.indices) {
      utility::math::Vertex<float, float> vertex{};
      vertex.setPosition({attrib.vertices[3 * index.vertex_index + 0],
                          attrib.vertices[3 * index.vertex_index + 1],
                          attrib.vertices[3 * index.vertex_index + 2]});
      if (index.texcoord_index >= 0) {
        vertex.setTextureCoordinates(
            {attrib.texcoords[2 * index.texcoord_index + 0],
             attrib.texcoords[2 * index.texcoord_index + 1]});
      }
      if (index.normal_index >= 0) {
        vertex.setColor({attrib.normals[3 * index.normal_index + 0],
                         attrib.normals[3 * index.normal_index + 1],
                         attrib.normals[3 * index.normal_index + 2], 1.0f});
      } else {
        vertex.setColor({1.0f, 1.0f, 1.0f, 1.0f});
      }
      vertices.push_back(vertex);
    }
  }
  return vertices;
}