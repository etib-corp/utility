/*
** ETIB PROJECT, 2026
** utility
** File description:
** mesh
*/

#pragma once

#include <utility/graphic/vertex.hpp>

namespace utility::graphic {
    class Mesh {
    public:
        Mesh(const std::vector<VertexD> &vertices, const std::vector<uint32_t> &indices);
        ~Mesh();

        void addVertex(const VertexD &vertex);
        void addIndex(uint32_t index);

        const std::vector<VertexD> &getVertices() const;
        const std::vector<uint32_t> &getIndices() const;

    private:
        std::vector<VertexD> _vertices;
        std::vector<uint32_t> _indices;
    };
} // namespace utility::graphic