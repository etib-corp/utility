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

namespace {
std::string NormalizePath(const std::string &path) {
  return std::filesystem::path(path).lexically_normal().generic_string();
}
} // namespace

bool utility::AssetManager::exists(const std::string &path) const {
  return _assets.find(NormalizePath(path)) != _assets.end();
}

std::shared_ptr<utility::FileAsset>
utility::AssetManager::open(const std::string &path) const {
  const auto it = _assets.find(NormalizePath(path));
  if (it == _assets.end()) {
    return nullptr;
  }
  return it->second;
}

std::vector<utility::graphic::Vertex<float>>
utility::AssetManager::loadModel(const std::string &path) {
  std::vector<utility::graphic::Vertex<float>> vertices;
  auto asset = open(path);
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
      if (index.vertex_index < 0) {
        continue;
      }

      const size_t vertexBase = static_cast<size_t>(index.vertex_index) * 3;
      if (vertexBase + 2 >= attrib.vertices.size()) {
        continue;
      }

      utility::graphic::Vertex<float> vertex{};
      vertex.setPosition(utility::graphic::Position<float>(
          attrib.vertices[vertexBase + 0], attrib.vertices[vertexBase + 1],
          attrib.vertices[vertexBase + 2]));

      if (index.texcoord_index >= 0) {
        const size_t texcoordBase =
            static_cast<size_t>(index.texcoord_index) * 2;
        if (texcoordBase + 1 < attrib.texcoords.size()) {
          vertex.setTextureCoordinates(utility::math::Vector<float, 2>(
              {attrib.texcoords[texcoordBase + 0],
               attrib.texcoords[texcoordBase + 1]}));
        }
      }

      if (index.normal_index >= 0) {
        const size_t normalBase = static_cast<size_t>(index.normal_index) * 3;
        if (normalBase + 2 < attrib.normals.size()) {
          vertex.setColor(utility::graphic::Color32Bit(
              static_cast<std::uint8_t>(attrib.normals[normalBase + 0]),
              static_cast<std::uint8_t>(attrib.normals[normalBase + 1]),
              static_cast<std::uint8_t>(attrib.normals[normalBase + 2]), 255));
        } else {
          vertex.setColor(utility::graphic::Color32Bit(255, 255, 255, 255));
        }
      } else {
        vertex.setColor(utility::graphic::Color32Bit(255, 255, 255, 255));
      }
      vertices.push_back(vertex);
    }
  }
  return vertices;
}