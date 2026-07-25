/*
** ETIB PROJECT, 2026
** xider
** File description:
** model
*/

#include <utility/graphic/model.hpp>

namespace utility::graphic
{
	Model::Model(std::shared_ptr<utility::File> modelAsset, const PoseF &pose, uint32_t materialID)
		: Renderable(pose, Color32Bit())
		, _materialID(materialID)
	{
		std::string extension =
			modelAsset->path().substr(modelAsset->path().find_last_of(".") + 1);

		if (extension == "obj") {
			loadOBJ(modelAsset);
			_type = ModelType::OBJ;
		} else if (extension == "fbx") {
			getLogger().warning()
				<< "FBX loading not implemented yet. Skipping model loading.";
			// loadFBX(modelAsset); // Not implemented yet
			_type = ModelType::FBX;
		} else if (extension == "gltf" || extension == "glb") {
			getLogger().warning()
				<< "GLTF loading not implemented yet. Skipping model loading.";
			// loadGLTF(modelAsset); // Not implemented yet
			_type = ModelType::GLTF;
		} else {
			throw std::runtime_error("Unsupported model format: " + extension);
		}
	}

	Model::Model(std::shared_ptr<utility::File> modelAsset, ModelType modelType,
				 const PoseF &pose, uint32_t materialID)
		: Renderable(pose, Color32Bit())
		, _materialID(materialID)
	{
		_type = modelType;

		switch (modelType) {
			case ModelType::OBJ:
				loadOBJ(modelAsset);
				break;
			case ModelType::FBX:
				getLogger().warning() << "FBX loading not implemented yet. "
										 "Skipping model loading.";
				// loadFBX(modelAsset); // Not implemented yet
				break;
			case ModelType::GLTF:
				getLogger().warning() << "GLTF loading not implemented yet. "
										 "Skipping model loading.";
				// loadGLTF(modelAsset); // Not implemented yet
				break;
			default:
				throw std::runtime_error("Unsupported model type");
		}
	}

	////////////////////
	// Public methods //
	////////////////////

	Model::ModelType Model::type() const
	{
		return _type;
	}

	utility::graphic::SizeF Model::computeBoundingSize(void)
	{
		return _boundingBox;
	}

	uint32_t Model::getMaterialID(void) const
	{
		return _materialID;
	}

	///////////////////////
	// Protected methods //
	///////////////////////

	void Model::loadOBJ(std::shared_ptr<utility::File> modelAsset)
	{
		float x = getPose().getPosition().getX();
		float y = getPose().getPosition().getY();
		float z = getPose().getPosition().getZ();

		std::vector<VertexF> vertices;
		std::vector<uint32_t> indices;

		// Bounding box calculation
		float minX = std::numeric_limits<float>::max();
		float minY = std::numeric_limits<float>::max();
		float minZ = std::numeric_limits<float>::max();
		float maxX = std::numeric_limits<float>::lowest();
		float maxY = std::numeric_limits<float>::lowest();
		float maxZ = std::numeric_limits<float>::lowest();

		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn;
		std::string err;
		std::istringstream input(modelAsset->content());

		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err,
									&input, nullptr, true);

		if (!ret) {
			throw std::runtime_error("Failed to load/parse .obj. " + err);
		}
		for (const auto &shape: shapes) {
			for (const auto &index: shape.mesh.indices) {
				if (index.vertex_index < 0) {
					continue;
				}

				const size_t vertexBase =
					static_cast<size_t>(index.vertex_index) * 3;
				if (vertexBase + 2 >= attrib.vertices.size()) {
					continue;
				}

				utility::graphic::VertexF vertex {};
				vertex.setPosition(utility::graphic::PositionF(
					attrib.vertices[vertexBase + 0] + x,
					attrib.vertices[vertexBase + 1] + y,
					attrib.vertices[vertexBase + 2] + z));

				if (index.texcoord_index >= 0) {
					const size_t texcoordBase =
						static_cast<size_t>(index.texcoord_index) * 2;
					if (texcoordBase + 1 < attrib.texcoords.size()) {
						vertex.setTextureCoordinates(utility::math::Vector2F(
							{ attrib.texcoords[texcoordBase + 0],
							  attrib.texcoords[texcoordBase + 1] }));
					}
				}

				if (index.normal_index >= 0) {
					const size_t normalBase =
						static_cast<size_t>(index.normal_index) * 3;
					if (normalBase + 2 < attrib.normals.size()) {
						vertex.setColor(utility::graphic::Color32Bit(
							static_cast<std::uint8_t>(
								attrib.normals[normalBase + 0]),
							static_cast<std::uint8_t>(
								attrib.normals[normalBase + 1]),
							static_cast<std::uint8_t>(
								attrib.normals[normalBase + 2]),
							255));
					} else {
						vertex.setColor(
							utility::graphic::Color32Bit(255, 255, 255, 255));
					}
				} else {
					vertex.setColor(
						utility::graphic::Color32Bit(255, 255, 255, 255));
				}

				if (vertices.size() >= static_cast<size_t>(
						std::numeric_limits<uint32_t>::max())) {
					throw std::runtime_error(
						"Too many vertices for uint32_t indices");
				}

				minX = std::min(minX, attrib.vertices[vertexBase + 0]);
				minY = std::min(minY, attrib.vertices[vertexBase + 1]);
				minZ = std::min(minZ, attrib.vertices[vertexBase + 2]);
				maxX = std::max(maxX, attrib.vertices[vertexBase + 0]);
				maxY = std::max(maxY, attrib.vertices[vertexBase + 1]);
				maxZ = std::max(maxZ, attrib.vertices[vertexBase + 2]);

				const uint32_t newIndex =
					static_cast<uint32_t>(vertices.size());
				vertices.push_back(vertex);
				indices.push_back(newIndex);
			}
		}

		_meshes.clear();
		if (!vertices.empty() && !indices.empty()) {
			_meshes.push_back(std::make_shared<Mesh>(vertices, indices));
		}
		_boundingBox = SizeF(maxX - minX, maxY - minY, maxZ - minZ);
	}
}	 // namespace utility::graphic
