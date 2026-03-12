/*
** ETIB PROJECT, 2025
** utility
** File description:
** AAssetManager
*/

#include "utility/AssetManager/AAssetManager.hpp"

bool utility::AAssetManager::exists(const std::string &path) const
{
	return _assets.find(path) != _assets.end();
}

std::shared_ptr<utility::FileAsset>
	utility::AAssetManager::get(const std::string &path)
{
	if (exists(path)) {
		return _assets[path];
	}
	return nullptr;
}

std::vector<utility::Vertex> utility::AAssetManager::loadModel(const std::string &path)
{
	std::vector<utility::Vertex> vertices;
	auto asset = get(path);
	if (asset == nullptr) {
		return vertices;
	}
	std::string content = asset->content();
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;
	std::istringstream input(content);
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, &input, nullptr, true);
	if (!ret) {
		std::cerr << "Failed to load/parse .obj." << std::endl;
		return vertices;
	}
	for (const auto &shape : shapes) {
		for (const auto &index : shape.mesh.indices) {
			utility::Vertex vertex{};
			vertex.pos = {attrib.vertices[3 * index.vertex_index + 0],
						  attrib.vertices[3 * index.vertex_index + 1],
						  attrib.vertices[3 * index.vertex_index + 2]};
			if (index.texcoord_index >= 0) {
				vertex.texCoord = {attrib.texcoords[2 * index.texcoord_index + 0],
								   attrib.texcoords[2 * index.texcoord_index + 1]};
			}
			if (index.normal_index >= 0) {
				vertex.color = {attrib.normals[3 * index.normal_index + 0],
								attrib.normals[3 * index.normal_index + 1],
								attrib.normals[3 * index.normal_index + 2], 1.0f};
			} else {
				vertex.color = {1.0f, 1.0f, 1.0f, 1.0f};
			}
			vertices.push_back(vertex);
		}
	}
	return vertices;
}