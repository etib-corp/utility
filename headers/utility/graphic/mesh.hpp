/*
** ETIB PROJECT, 2026
** utility
** File description:
** mesh
*/

#pragma once

#include <utility/graphic/vertex.hpp>

namespace utility::graphic
{
	/**
	 * @brief The Mesh class represents a 3D mesh used for rendering in a
	 * graphics application.
	 *
	 * The Mesh class encapsulates the vertex and index data required to render
	 * a 3D object. It provides methods to add vertices and indices, as well as
	 * retrieve the current vertex and index data. The Mesh class is designed to
	 * be used in conjunction with rendering systems that require vertex and
	 * index buffers for efficient rendering of 3D geometry.
	 */
	class Mesh
	{
		public:
		/**
		 * @brief Constructs a Mesh object with the specified vertices and
		 * indices.
		 *
		 * @param vertices A vector of VertexF objects representing the vertices
		 * of the mesh.
		 * @param indices A vector of uint32_t values representing the indices
		 * for indexed drawing of the mesh.
		 */
		Mesh(const std::vector<VertexF> &vertices,
			 const std::vector<uint32_t> &indices);

		/**
		 * @brief Destructs the Mesh object, releasing any allocated resources.
		 */
		~Mesh();

		/**
		 * @brief Add a vertex to the mesh.
		 *
		 * @param vertex The VertexF object representing the vertex to be added
		 * to the mesh.
		 *
		 * This method appends the provided vertex to the internal vertex list
		 * of the mesh, allowing for dynamic construction of the mesh geometry.
		 */
		void addVertex(const VertexF &vertex);

		/**
		 * @brief Add an index to the mesh.
		 *
		 * @param index The uint32_t value representing the index to be added to
		 * the mesh.
		 *
		 * This method appends the provided index to the internal index list of
		 * the mesh, enabling indexed drawing of the mesh geometry.
		 */
		void addIndex(uint32_t index);

		/**
		 * @brief Get the vertices of the mesh.
		 *
		 * @return A const reference to a vector of VertexF objects representing
		 * the vertices of the mesh.
		 *
		 * This method allows retrieval of the current vertex data of the mesh,
		 * which can be used for rendering or further processing.
		 */
		const std::vector<VertexF> &getVertices() const;

		/**
		 * @brief Get the indices of the mesh.
		 *
		 * @return A const reference to a vector of uint32_t values representing
		 * the indices of the mesh.
		 *
		 * This method allows retrieval of the current index data of the mesh,
		 * which can be used for indexed drawing or further processing.
		 */
		const std::vector<uint32_t> &getIndices() const;

		/**
		 * @brief Reset the mesh by clearing all vertices and indices.
		 *
		 * This method removes all vertex and index data from the mesh,
		 * effectively resetting it to an empty state. This can be useful for
		 * reusing a Mesh object without needing to create a new instance.
		 */
		void reset(void);

		/**
		 * @brief Equality comparison.
		 * @param other Mesh object to compare with.
		 * @return True when vertices and indices are equal.
		 */
		bool operator==(const Mesh &other) const
		{
			return _vertices == other._vertices && _indices == other._indices;
		}

		/**
		 * @brief Inequality comparison.
		 * @param other Mesh object to compare with.
		 * @return True when vertices or indices differ.
		 */
		bool operator!=(const Mesh &other) const
		{
			return !(*this == other);
		}

		private:
		/**
		 * @brief Internal storage for the vertices and indices of the mesh.
		 */
		std::vector<VertexF> _vertices;

		/**
		 * @brief Internal storage for the indices of the mesh.
		 */
		std::vector<uint32_t> _indices;
	};
}	 // namespace utility::graphic