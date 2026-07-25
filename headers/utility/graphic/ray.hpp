/*
 Copyright (c) 2026 ETIB Corporation

 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

/**
 * @file ray.hpp
 * @brief Geometric ray template declaration.
 *
 * Declares `graphic::Ray<Type, Dimension>`, a fixed-dimension ray
 * defined by an origin and a non-zero direction vector. Provides accessors,
 * mutators, translation utilities, and point evaluation along the ray.
 */

#pragma once

#include <ostream>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <ostream>

#include "utility/graphic/position.hpp"

#include "utility/math/vector.hpp"

#include "utility/graphic/mesh.hpp"

namespace utility::graphic
{
	/**
	 * @brief Concept to ensure the type can be used as a ray component.
	 * @tparam Type The type to check.
	 */
	template<typename Type>
	concept CanBeRayComponent =
		CanBePositionComponent<Type> && math::CanBeVectorComponent<Type>;
	/**
	 * @brief Geometric ray with arithmetic component type and fixed dimension.
	 * @tparam Type Arithmetic type for origin and direction components.
	 * @tparam Dimension Compile-time dimension of the ray vectors.
	 */
	template<CanBeRayComponent RayComponentType> class Ray
	{
		private:
		protected:
		/**
		 * @brief Origin point of the ray.
		 */
		Position<RayComponentType> _origin;

		/**
		 * @brief Direction vector of the ray (must be non-zero).
		 */
		math::Vector<RayComponentType, 3> _direction;

		/**
		 * @brief Validate that a direction vector is non-zero.
		 * @param direction Direction vector to validate.
		 * @throws std::invalid_argument if direction is the zero vector.
		 */
		static void validateDirection(
			const math::Vector<RayComponentType, 3> &direction)
		{
			const RayComponentType squaredLength = direction[0] * direction[0]
				+ direction[1] * direction[1] + direction[2] * direction[2];
			if (squaredLength == RayComponentType {}) {
				throw std::invalid_argument("Ray direction must be non-zero");
			}
		}

		public:
		/**
		 * @brief Default constructor creating a ray at origin along the first
		 * axis.
		 */
		Ray(void)
			: _origin()
		{
			_direction	  = math::Vector<RayComponentType, 3>();
			_direction[0] = RayComponentType { 1 };
		}

		/**
		 * @brief Construct ray from origin and direction.
		 * @param origin Origin point.
		 * @param direction Direction vector (must be non-zero).
		 * @throws std::invalid_argument if direction is the zero vector.
		 */
		Ray(math::Vector<RayComponentType, 3> origin,
			math::Vector<RayComponentType, 3> direction)
			: _origin(std::move(origin))
			, _direction(std::move(direction))
		{
			validateDirection(_direction);
		}

		/**
		 * @brief Copy constructor.
		 * @param other The ray to copy from.
		 */
		Ray(const Ray &other)
			: _origin(other._origin)
			, _direction(other._direction)
		{
		}

		/**
		 * @brief Move constructor.
		 * @param other The ray to move from.
		 */
		Ray(Ray &&other) noexcept
			: _origin(std::move(other._origin))
			, _direction(std::move(other._direction))
		{
		}

		/**
		 * @brief Copy assignment operator.
		 * @param other The ray to copy from.
		 * @return Reference to this ray.
		 */
		Ray &operator=(const Ray &other)
		{
			if (this != &other) {
				_origin	   = other._origin;
				_direction = other._direction;
			}
			return *this;
		}

		/**
		 * @brief Move assignment operator.
		 * @param other The ray to move from.
		 * @return Reference to this ray.
		 */
		Ray &operator=(Ray &&other) noexcept
		{
			if (this != &other) {
				_origin	   = std::move(other._origin);
				_direction = std::move(other._direction);
			}
			return *this;
		}

		// Destructor
		~Ray(void) = default;

		/**
		 * @brief Set the ray origin.
		 * @param origin New origin vector.
		 */
		void setOrigin(const math::Vector<RayComponentType, 3> &origin)
		{
			_origin = Position<RayComponentType>(origin);
		}

		/**
		 * @brief Set the ray origin using a Position value.
		 * @param origin New origin position.
		 */
		void setOrigin(const Position<RayComponentType> &origin)
		{
			_origin = origin;
		}

		/**
		 * @brief Get the ray origin.
		 * @return Origin vector.
		 */
		math::Vector<RayComponentType, 3> getOrigin() const
		{
			return _origin;
		}

		/**
		 * @brief Set the ray direction.
		 * @param direction New direction vector (must be non-zero).
		 * @throws std::invalid_argument if direction is the zero vector.
		 */
		void setDirection(const math::Vector<RayComponentType, 3> &direction)
		{
			validateDirection(direction);
			_direction = direction;
		}

		/**
		 * @brief Get the ray direction.
		 * @return Direction vector.
		 */
		math::Vector<RayComponentType, 3> getDirection(void) const
		{
			return _direction;
		}

		/**
		 * @brief Access the ray origin by const reference.
		 * @return Const reference to origin.
		 */
		const Position<RayComponentType> &origin(void) const noexcept
		{
			return _origin;
		}

		/**
		 * @brief Access the ray direction by const reference.
		 * @return Const reference to direction.
		 */
		const math::Vector<RayComponentType, 3> &direction(void) const noexcept
		{
			return _direction;
		}

		/**
		 * @brief Get a normalized copy of the ray direction.
		 * @return Unit-length direction vector.
		 */
		math::Vector<RayComponentType, 3> normalizedDirection() const
		{
			return math::normalize(_direction);
		}

		/**
		 * @brief Evaluate a point on the ray at the provided parameter.
		 * @param distanceParameter Parameter value measured along direction.
		 * @return Point computed as origin + direction * parameter.
		 */
		math::Vector<RayComponentType, 3>
			pointAt(RayComponentType distanceParameter) const
		{
			return _origin + (_direction * distanceParameter);
		}

		/**
		 * @brief Alias for pointAt to match common ray APIs.
		 * @param distanceParameter Parameter value measured along direction.
		 * @return Point computed as origin + direction * parameter.
		 */
		math::Vector<RayComponentType, 3>
			at(RayComponentType distanceParameter) const
		{
			return pointAt(distanceParameter);
		}

		/**
		 * @brief Translate ray origin by the provided offset.
		 * @param offset Translation vector.
		 */
		void translate(const math::Vector<RayComponentType, 3> &offset)
		{
			_origin += offset;
		}

		/**
		 * @brief Get translated ray copy.
		 * @param offset Translation vector.
		 * @return Ray copy with translated origin.
		 */
		Ray translated(const math::Vector<RayComponentType, 3> &offset) const
		{
			return Ray(_origin + offset, _direction);
		}

		/**
		 * @brief Equality comparison.
		 * @param other Ray to compare with.
		 * @return True when origin and direction are equal.
		 */
		bool operator==(const Ray &other) const
		{
			return _origin == other._origin && _direction == other._direction;
		}

		/**
		 * @brief Inequality comparison.
		 * @param other Ray to compare with.
		 * @return True when origin or direction differ.
		 */
		bool operator!=(const Ray &other) const
		{
			return !(*this == other);
		}

		/**
		 * @brief Check for intersection with an axis-aligned rectangle
		 * plane.
		 * @param rectanglePose Pose-like object providing position and
		 * orientation accessors.
		 * @param rectangleSize Size of the rectangle (width, height).
		 * @return True if the ray intersects the rectangle, false if it misses
		 * or is parallel. Note that rays originating inside the rectangle are
		 * considered intersecting. Rays parallel to the rectangle plane that
		 * lie in the plane are also considered intersecting, while those that
		 * do not lie in the plane are considered non-intersecting.
		 */
		template<typename RectanglePoseType>
		bool intersectRectangle(const RectanglePoseType &rectanglePose,
								const math::Vector2F &rectangleSize) const
		{
			const auto rectangleOrientation = rectanglePose.getOrientation();

			const math::Vector<RayComponentType, 3> right =
				rectangleOrientation.getRight();
			const math::Vector<RayComponentType, 3> up =
				rectangleOrientation.getUp();
			const math::Vector<RayComponentType, 3> planeNormal =
				rectangleOrientation.getForward();

			const RayComponentType halfWidth =
				static_cast<RayComponentType>(rectangleSize[0])
				/ RayComponentType { 2 };
			const RayComponentType halfHeight =
				static_cast<RayComponentType>(rectangleSize[1])
				/ RayComponentType { 2 };

			const math::Vector<RayComponentType, 3> topLeft =
				math::Vector<RayComponentType, 3>(rectanglePose.getPosition());

			// Top-left -> center
			// Use -up because your UI placement appears to grow downward in Y
			const math::Vector<RayComponentType, 3> rectangleCenter =
				topLeft + right * halfWidth + up * halfHeight;

			const RayComponentType denominator =
				math::dot(_direction, planeNormal);

			if (denominator == RayComponentType {}) {
				const math::Vector<RayComponentType, 3> toOrigin =
					math::Vector<RayComponentType, 3>(_origin)
					- rectangleCenter;

				if (math::dot(toOrigin, planeNormal) == RayComponentType {}) {
					return true;
				}
				return false;
			}

			const math::Vector<RayComponentType, 3> toCenter =
				rectangleCenter - math::Vector<RayComponentType, 3>(_origin);

			const RayComponentType t =
				math::dot(toCenter, planeNormal) / denominator;

			if (t < RayComponentType {}) {
				return false;
			}

			const math::Vector<RayComponentType, 3> intersectionPoint =
				pointAt(t);
			const math::Vector<RayComponentType, 3> localPoint =
				intersectionPoint - rectangleCenter;

			const RayComponentType rightCoord = math::dot(localPoint, right);
			const RayComponentType upCoord	  = math::dot(localPoint, up);

			return (rightCoord >= -halfWidth && rightCoord <= halfWidth
					&& upCoord >= -halfHeight && upCoord <= halfHeight);
		}

		/**
		 * @brief Convert the ray into a mesh representation for visualization.
		 * @param length Length of the ray mesh.
		 * @param radius Radius of the ray mesh.
		 * @param segments Number of segments around the circumference.
		 * @param color Color of the mesh vertices.
		 * @return Mesh representing the ray as a cylinder.
		 */
		utility::graphic::Mesh convertToMesh(
			float length, float radius, int segments,
			utility::graphic::Color32Bit color = { 255, 255, 255, 255 }) const
		{
			utility::graphic::Mesh mesh({}, {});

			auto dir = utility::math::normalize(_direction);

			utility::math::Vector3F up { 0.0f, 1.0f, 0.0f };

			// If the ray is almost parallel to Up, choose another axis.
			if (std::abs(utility::math::dot(dir, up)) > 0.99f)
				up = utility::math::Vector3F { 1.0f, 0.0f, 0.0f };

			auto right =
				utility::math::normalize(utility::math::cross(dir, up));
			auto realUp = utility::math::cross(right, dir);

			utility::math::Vector3F start = _origin;
			utility::math::Vector3F end	  = start + dir * length;

			for (int i = 0; i < segments; ++i) {
				float a0 = 2.0f * M_PI * i / segments;
				float a1 = 2.0f * M_PI * (i + 1) / segments;

				auto offset0 = right * (std::cos(a0) * radius)
					+ realUp * (std::sin(a0) * radius);

				auto offset1 = right * (std::cos(a1) * radius)
					+ realUp * (std::sin(a1) * radius);

				uint32_t base =
					static_cast<uint32_t>(mesh.getVertices().size());

				utility::graphic::VertexF vertex;

				vertex.setColor(color);

				auto p0 = start + offset0;
				auto p1 = start + offset1;
				auto p2 = end + offset0;
				auto p3 = end + offset1;

				vertex.setPosition(
					utility::graphic::PositionF(p0.x, p0.y, p0.z));
				mesh.addVertex(vertex);

				vertex.setPosition(
					utility::graphic::PositionF(p1.x, p1.y, p1.z));
				mesh.addVertex(vertex);

				vertex.setPosition(
					utility::graphic::PositionF(p2.x, p2.y, p2.z));
				mesh.addVertex(vertex);

				vertex.setPosition(
					utility::graphic::PositionF(p3.x, p3.y, p3.z));
				mesh.addVertex(vertex);

				mesh.addIndex(base + 0);
				mesh.addIndex(base + 1);
				mesh.addIndex(base + 2);

				mesh.addIndex(base + 2);
				mesh.addIndex(base + 1);
				mesh.addIndex(base + 3);
			}

			return mesh;
		}
	};

	/**
	 * @brief Type alias for single-precision ray component.
	 */
	using RayF = Ray<float>;

	/**
	 * @brief Type alias for double-precision ray component.
	 */
	using RayD = Ray<double>;

	/**
	 * @brief Stream insertion operator for Ray.
	 * @param stream Output stream.
	 * @param ray Ray to output.
	 * @return Reference to the output stream.
	 */
	std::ostream &operator<<(std::ostream &stream, const RayF &ray);

	/**
	 * @brief Stream insertion operator for Ray.
	 * @param stream Output stream.
	 * @param ray Ray to output.
	 * @return Reference to the output stream.
	 */
	std::ostream &operator<<(std::ostream &stream, const RayD &ray);

}	 // namespace utility::graphic
