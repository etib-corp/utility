/*
** ETIB PROJECT, 2026
** utility
** File description:
** mesh
*/

#include <utility/graphic/mesh.hpp>

namespace utility::graphic
{
	Mesh::Mesh(const std::vector<VertexF> &vertices,
			   const std::vector<uint32_t> &indices)
		: _vertices(vertices)
		, _indices(indices)
	{
	}

	Mesh::~Mesh()
	{
	}

	void Mesh::addVertex(const VertexF &vertex)
	{
		_vertices.push_back(vertex);
	}

	void Mesh::addIndex(uint32_t index)
	{
		_indices.push_back(index);
	}

	const std::vector<VertexF> &Mesh::getVertices() const
	{
		return _vertices;
	}

	const std::vector<uint32_t> &Mesh::getIndices() const
	{
		return _indices;
	}

	void Mesh::reset(void)
	{
		_vertices.clear();
		_indices.clear();
	}
}	 // namespace utility::graphic
