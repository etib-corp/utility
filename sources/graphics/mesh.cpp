/*
** ETIB PROJECT, 2026
** utility
** File description:
** mesh
*/

#include "utility/graphics/mesh.hpp"

namespace utility::graphics {
    Mesh::Mesh(const std::vector<Vertex<float, float>> &vertices, const std::vector<uint32_t> &indices)
        : _vertices(vertices), _indices(indices)
    {
    }

    Mesh::~Mesh()
    {
    }

    void Mesh::addVertex(const Vertex<float, float> &vertex)
    {
        _vertices.push_back(vertex);
    }

    void Mesh::addIndex(uint32_t index)
    {
        _indices.push_back(index);
    }

    const std::vector<Vertex<float, float>> &Mesh::getVertices() const
    {
        return _vertices;
    }

    const std::vector<uint32_t> &Mesh::getIndices() const
    {
        return _indices;
    }
} // namespace utility::graphics
