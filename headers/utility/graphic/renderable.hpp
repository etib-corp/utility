/*
** ETIB PROJECT, 2026
** xider
** File description:
** renderable
*/

#pragma once

#include <memory>

#include <utility/graphic/color.hpp>
#include <utility/graphic/pose.hpp>
#include <utility/graphic/mesh.hpp>

namespace utility::graphic
{
	/**
	 * @class Renderable
	 * @brief The Renderable class represents an object that can be rendered in
	 * the graphics application.
	 *
	 * The Renderable class serves as a base class for objects that can be
	 * rendered, such as models, sprites, or other graphical entities. It
	 * provides a common interface and properties for renderable objects,
	 * allowing for consistent handling and rendering within the graphics
	 * application.
	 */
	class Renderable
	{
		public:
		/**
		 * @brief Default constructor for Renderable.
		 * @param pose The initial pose (position and orientation) of the
		 * renderable object. Defaults to the origin with no rotation.
		 * @param color The initial color of the renderable object. Defaults to
		 * opaque white.
		 */
		Renderable(const PoseF &pose, const Color32Bit &color);

		/**
		 * @brief Virtual destructor for Renderable.
		 */
		virtual ~Renderable() = default;

		/**
		 * @brief Set the text pose
		 *
		 * @param pose Text world pose (position and orientation).
		 *
		 * @return Reference to this Text instance for chaining.
		 */
		Renderable &setPose(const PoseF &pose);

		/**
		 * @brief Set the text pose
		 *
		 * @param pose Text world pose (position and orientation).
		 */
		void setPose(PoseF &&pose);

		/**
		 * @brief Get the text pose
		 *
		 * @return Const reference to the text pose (position and orientation).
		 */
		const PoseF &getPose(void) const;

		/**
		 * @brief Set the text color.
		 *
		 * @param color Text RGBA color.
		 *
		 * @return Reference to this Text instance for chaining.
		 */
		Renderable &setColor(const graphic::Color32Bit &color);

		/**
		 * @brief Set the text color.
		 *
		 * @param color Text RGBA color.
		 */
		void setColor(graphic::Color32Bit &&color);

		/**
		 * @brief Get the text color.]
		 *
		 * @return Const reference to the text color.
		 */
		const graphic::Color32Bit &getColor(void) const;

		/**
		 * @brief Get the meshes associated with this renderable object.
		 *
		 * This method returns a vector of shared pointers to Mesh objects that
		 * are associated with this renderable object. Each Mesh represents a
		 * part of the geometry that can be rendered, and the shared pointers
		 * allow for efficient memory management and sharing of mesh data across
		 * multiple renderable objects if needed. The returned vector can be
		 * used by the rendering system to access the mesh data for rendering
		 * this object in the scene.
		 *
		 * @return A vector of shared pointers to Mesh objects associated with
		 * this renderable object.
		 */
		[[nodiscard]] std::vector<std::shared_ptr<Mesh>> getMeshes() const;

		protected:
		std::vector<std::shared_ptr<Mesh>>
			_meshes;		  ///< Meshes associated with this renderable object
		Color32Bit _color;	  ///< Text RGBA color
		PoseF _pose;	///< World pose (position and orientation) of the text
	};
}	 // namespace utility::graphic