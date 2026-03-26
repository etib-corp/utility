/*
** ETIB PROJECT, 2026
** utility
** File description:
** mesh
*/

#pragma once

#include "utility/graphics/vertex.hpp"

namespace utility::graphics {
    class Mesh {
    public:
        Mesh(const std::vector<Vertex<float, uint8_t>> &vertices, const std::vector<uint32_t> &indices);
        ~Mesh();

        void addVertex(const Vertex<float, uint8_t> &vertex);
        void addIndex(uint32_t index);

        const std::vector<Vertex<float, uint8_t>> &getVertices() const;
        const std::vector<uint32_t> &getIndices() const;

    private:
        std::vector<Vertex<float, uint8_t>> _vertices;
        std::vector<uint32_t> _indices;
    };
} // namespace utility::graphics