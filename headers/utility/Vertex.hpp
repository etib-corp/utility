/*
** ETIB PROJECT, 2025
** evan
** File description:
** Vertex
*/

#pragma once

#include "math/vector.hpp"

namespace utility
{
	/**
	 * @brief Vertex structure.
	 *
	 * This structure represents a vertex in the 3D space. It contains the
	 * position, color, and texture coordinates of the vertex. It is used to
	 * define the vertex data for rendering.
	 *
	 */
	struct Vertex {
		math::Vector<float, 3> pos;	  // Position of the vertex
		math::Vector<float, 4> color;	  // Color of the vertex
		math::Vector<float, 2> texCoord;	   // Texture coordinates of the vertex

		/*
		 * @brief Equality operator for the Vertex structure.
		 *
		 * This operator compares two Vertex objects for equality based on
		 * their position, color, and texture coordinates.
		 *
		 * @param other The other Vertex object to compare with.
		 * @return true if the two Vertex objects are equal, false otherwise.
		 *
		 */
		bool operator==(const Vertex &other) const
		{
			return pos == other.pos && color == other.color
				&& texCoord == other.texCoord;
		}
	};
}	 // namespace evan
