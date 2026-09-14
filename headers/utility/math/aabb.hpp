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

#pragma once

#include <algorithm>
#include <concepts>
#include <cstddef>
#include <iterator>
#include <limits>
#include <ostream>
#include <span>
#include <type_traits>

#include <glm/geometric.hpp>
#include <glm/vec3.hpp>

#include <utility/math/vector.hpp>

namespace utility::math
{
	/**
	 * @brief Axis-aligned bounding box (AABB) in 3D space.
	 *
	 * Stores the two opposite corners of a box whose faces are aligned with
	 * the coordinate axes. The default-constructed box is "empty" (inverted,
	 * `min > max` on at least one axis) so that it can be grown with
	 * `include()`; consumers must check `isEmpty()` before treating an
	 * instance as a valid bound.
	 *
	 * @tparam T Floating-point component type (e.g. `float` or `double`).
	 */
	template<CanBeVectorComponent T>
	class Aabb
	{
		static_assert(
			std::is_floating_point_v<T>,
			"Aabb requires a floating-point component type (float or double)");

		public:
		/**
		 * @brief Default constructor creating an empty (inverted) box.
		 *
		 * The box has no valid bounds until `include()` or assignment from
		 * `fromPoints()`. `isEmpty()` returns true.
		 */
		Aabb(void)
			: _min(std::numeric_limits<T>::max())
			, _max(std::numeric_limits<T>::lowest())
		{
		}

		/**
		 * @brief Construct from explicit minimum and maximum corners.
		 * @param min The minimum corner.
		 * @param max The maximum corner.
		 */
		Aabb(const Vector<T, 3> &min, const Vector<T, 3> &max)
			: _min(min)
			, _max(max)
		{
		}

		/**
		 * @brief Build the tightest box containing a range of 3D points.
		 *
		 * If the range is empty, the resulting box is empty (`isEmpty()`).
		 * @tparam Iterator Input iterator type.
		 * @tparam Sentinel Sentinel type matching @p Iterator.
		 * @param first Iterator to the first point.
		 * @param last Sentinel marking the end of the range.
		 * @return The bounding box of all points in the range.
		 */
		template<std::input_iterator Iterator,
				 std::sentinel_for<Iterator> Sentinel>
		static Aabb fromPoints(Iterator first, Sentinel last)
		{
			Aabb box;
			for (; first != last; ++first) {
				box.include(*first);
			}
			return box;
		}

		/**
		 * @brief Build the tightest box containing a contiguous range of
		 * points.
		 *
		 * Accepts any contiguous range implicitly convertible to
		 * `std::span<const Vector<T, 3>>` (e.g. `std::vector`, `std::array`).
		 * If the range is empty, the resulting box is empty.
		 * @param points The points to bound.
		 * @return The bounding box of all points.
		 */
		static Aabb fromPoints(std::span<const Vector<T, 3>> points)
		{
			return fromPoints(points.begin(), points.end());
		}

		/**
		 * @brief Grow the box to contain a point.
		 * @param point The point that must be contained.
		 */
		void include(const Vector<T, 3> &point) noexcept
		{
			for (std::size_t i = 0; i < 3; ++i) {
				_min[i] = std::min(_min[i], point[i]);
				_max[i] = std::max(_max[i], point[i]);
			}
		}

		/**
		 * @brief Grow the box to contain another box (union).
		 *
		 * Including an empty box is a no-op.
		 * @param other The box that must be contained.
		 */
		void include(const Aabb &other) noexcept
		{
			if (other.isEmpty()) {
				return;
			}
			include(other._min);
			include(other._max);
		}

		/**
		 * @brief Get the center of the box.
		 *
		 * Computed by halving each corner before summing so that boxes with
		 * very large coordinates do not overflow.
		 * @return The center point.
		 */
		[[nodiscard]] Vector<T, 3> center(void) const noexcept
		{
			return _min * T { 0.5 } + _max * T { 0.5 };
		}

		/**
		 * @brief Get the full size of the box along each axis.
		 * @return `max - min`, or a zero vector when the box is empty.
		 */
		[[nodiscard]] Vector<T, 3> extents(void) const noexcept
		{
			return isEmpty() ? Vector<T, 3>(T { 0 }) : (_max - _min);
		}

		/**
		 * @brief Get half the size of the box along each axis.
		 * @return `extents() * 0.5`.
		 */
		[[nodiscard]] Vector<T, 3> halfSize(void) const noexcept
		{
			return extents() * T { 0.5 };
		}

		/**
		 * @brief Get the radius of the bounding sphere around the box.
		 *
		 * Useful for cheap distance culling.
		 * @return The length of `halfSize()` (zero for an empty box).
		 */
		[[nodiscard]] T radius(void) const noexcept
		{
			return static_cast<T>(glm::length(
				static_cast<const glm::vec<3, T> &>(halfSize())));
		}

		/**
		 * @brief Get the corner farthest along a direction (the "p-vertex").
		 *
		 * For each axis the component of @p normal selects the maximum when
		 * non-negative and the minimum otherwise. This is the support point
		 * used by the standard AABB-vs-plane frustum test.
		 * @param normal The direction to search along.
		 * @return The corner of the box farthest along @p normal.
		 */
		[[nodiscard]] Vector<T, 3>
			positiveVertex(const Vector<T, 3> &normal) const noexcept
		{
			Vector<T, 3> result;
			for (std::size_t i = 0; i < 3; ++i) {
				result[i] = (normal[i] >= T { 0 }) ? _max[i] : _min[i];
			}
			return result;
		}

		/**
		 * @brief Test whether a point lies inside the box (boundaries
		 * included).
		 * @param point The point to test.
		 * @return True if the point is contained, false otherwise (also false
		 * for an empty box).
		 */
		[[nodiscard]] bool contains(const Vector<T, 3> &point) const noexcept
		{
			if (isEmpty()) {
				return false;
			}
			for (std::size_t i = 0; i < 3; ++i) {
				if (point[i] < _min[i] || point[i] > _max[i]) {
					return false;
				}
			}
			return true;
		}

		/**
		 * @brief Test whether two boxes overlap (touching counts).
		 * @param other The box to test against.
		 * @return True if the boxes intersect, false otherwise (also false if
		 * either box is empty).
		 */
		[[nodiscard]] bool intersects(const Aabb &other) const noexcept
		{
			if (isEmpty() || other.isEmpty()) {
				return false;
			}
			for (std::size_t i = 0; i < 3; ++i) {
				if (_min[i] > other._max[i] || other._min[i] > _max[i]) {
					return false;
				}
			}
			return true;
		}

		/**
		 * @brief Test whether the box is empty (inverted).
		 * @return True if `min > max` on at least one axis.
		 */
		[[nodiscard]] bool isEmpty(void) const noexcept
		{
			for (std::size_t i = 0; i < 3; ++i) {
				if (_min[i] > _max[i]) {
					return true;
				}
			}
			return false;
		}

		/**
		 * @brief Get the minimum corner.
		 * @return The minimum corner.
		 */
		[[nodiscard]] Vector<T, 3> getMin(void) const noexcept
		{
			return _min;
		}

		/**
		 * @brief Get the maximum corner.
		 * @return The maximum corner.
		 */
		[[nodiscard]] Vector<T, 3> getMax(void) const noexcept
		{
			return _max;
		}

		private:
		Vector<T, 3> _min;	///< The minimum corner.
		Vector<T, 3> _max;	///< The maximum corner.
	};

	/**
	 * @brief Type alias for a single-precision axis-aligned bounding box.
	 */
	using AabbF = Aabb<float>;

	/**
	 * @brief Type alias for a double-precision axis-aligned bounding box.
	 */
	using AabbD = Aabb<double>;

	/**
	 * @brief Stream insertion operator for Aabb.
	 * @param stream Output stream.
	 * @param box Box to output.
	 * @return Reference to the output stream.
	 */
	std::ostream &operator<<(std::ostream &stream, const AabbF &box);

	/**
	 * @brief Stream insertion operator for Aabb.
	 * @param stream Output stream.
	 * @param box Box to output.
	 * @return Reference to the output stream.
	 */
	std::ostream &operator<<(std::ostream &stream, const AabbD &box);

}	 // namespace utility::math
