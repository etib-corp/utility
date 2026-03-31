/*
** ETIB PROJECT, 2026
** utility
** File description:
** mesh
*/

#include <utility/graphic/mesh.hpp>

namespace utility::graphic {
    Mesh::Mesh(const std::vector<VertexD> &vertices, const std::vector<uint32_t> &indices)
    : _vertices(vertices), _indices(indices)
    {
    }

    Mesh::~Mesh()
    {
    }

    void Mesh::addVertex(const VertexD &vertex)
    {
        _vertices.push_back(vertex);
    }

    void Mesh::addIndex(uint32_t index)
    {
        _indices.push_back(index);
    }

    const std::vector<VertexD> &Mesh::getVertices() const
    {
        return _vertices;
    }

    const std::vector<uint32_t> &Mesh::getIndices() const
    {
        return _indices;
    }
} // namespace utility::graphic
