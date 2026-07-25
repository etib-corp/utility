/*
** ETIB PROJECT, 2026
** xider
** File description:
** primitive
*/

#pragma once

#include <utility/graphic/renderable.hpp>

namespace utility::graphic
{
	/**
	 * @class Primitive
	 * @brief The Primitive class represents a basic geometric shape that can be
	 * rendered in the graphics application.
	 *
	 * The Primitive class serves as a base class for simple geometric shapes
	 * such as cubes, spheres, and planes. It provides a common interface and
	 * properties for these shapes, allowing for consistent handling and
	 * rendering within the graphics application. The Primitive class can be
	 * extended to create specific types of primitives with additional
	 * properties and behaviors as needed.
	 */
	class Primitive: public Renderable
	{
		public:
		/**
		 * @brief Constructs a Primitive object with the specified meshes.
		 *
		 * @param meshes A vector of Mesh objects representing the geometry of
		 * the primitive.
		 *
		 * This constructor initializes the Primitive object with the provided
		 * meshes, which define the geometry of the primitive for rendering. The
		 * meshes are stored internally and can be accessed or modified as
		 * needed for rendering or further processing.
		 */
		Primitive(const std::vector<Mesh> &meshes);

		/**
		 * @brief Deleted copy constructor for Primitive.
		 */
		Primitive(const Primitive &) = delete;

		/**
		 * @brief Default destructor for Primitive.
		 */
		~Primitive() = default;

		/**
		 * @brief Add a mesh to the primitive.
		 *
		 * @param mesh The Mesh object representing the geometry to be added to
		 * the primitive.
		 *
		 * This method appends the provided mesh to the internal list of meshes
		 * of the primitive, allowing for dynamic construction of the primitive
		 * geometry. The added mesh will be included in the rendering of the
		 * primitive, and it can be used to create more complex shapes by
		 * combining multiple meshes together.
		 */
		void addMesh(const Mesh &mesh);

		/**
		 * @brief Deleted copy assignment operator for Primitive.
		 */
		Primitive &operator=(const Primitive &) = delete;
	};
}	 // namespace utility::graphic