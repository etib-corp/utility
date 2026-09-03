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

#include <cmath>
#include <numbers>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <ostream>

namespace utility::graphic
{

	/**
	 * @brief Concept to constrain field-of-view component type.
	 * @tparam Type Candidate component type.
	 */
	template<typename Type>
	concept CanBeFieldOfViewComponent = std::is_floating_point_v<Type>;

	/**
	 * @brief Field of view representation in radians for up, down, left, and
	 * right directions.
	 * @tparam Type Floating-point component type used for stored angles.
	 * @note We store in radians internally for efficient calculations, but the
	 * interface uses radians for ease of use.
	 */
	template<CanBeFieldOfViewComponent Type> class FieldOfView
	{
		private:
		Type _up;	 ///< Vertical FOV above the forward direction in
					 ///< radians
		Type _down;	   ///< Vertical FOV below the forward direction in
					   ///< radians
		Type _left;	   ///< Horizontal FOV to the left of the forward
					   ///< direction in radians
		Type _right;	///< Horizontal FOV to the right of the forward
						///< direction in radians

		public:
		/**
		 * @brief Default constructor initializing all FOV angles to 0 radians.
		 */
		FieldOfView(void)
			: FieldOfView(Type { 0 }, Type { 0 }, Type { 0 }, Type { 0 })
		{
		}

		/**
		 * @brief Constructor to initialize field of view angles in radians.
		 * @param up Vertical FOV above the forward direction in radians.
		 * @param down Vertical FOV below the forward direction in radians.
		 * @param left Horizontal FOV to the left of the forward direction in
		 * radians.
		 * @param right Horizontal FOV to the right of the forward direction in
		 * radians.
		 */
		FieldOfView(Type up, Type down, Type left, Type right)
			: _up(up)
			, _down(down)
			, _left(left)
			, _right(right)
		{
		}

		/**
		 * @brief Copy constructor.
		 * @param other The FieldOfView object to copy from.
		 */
		FieldOfView(const FieldOfView &other) = default;

		/**
		 * @brief Move constructor.
		 * @param other The FieldOfView object to move from.
		 */
		FieldOfView(FieldOfView &&other) noexcept = default;

		/**
		 * @brief Copy assignment operator.
		 * @param other The FieldOfView object to copy from.
		 * @return A reference to this FieldOfView object.
		 */
		FieldOfView &operator=(const FieldOfView &other) = default;

		/**
		 * @brief Move assignment operator.
		 * @param other The FieldOfView object to move from.
		 * @return A reference to this FieldOfView object.
		 */
		FieldOfView &operator=(FieldOfView &&other) noexcept = default;

		/**
		 * @brief Default destructor for FieldOfView.
		 */
		~FieldOfView(void) = default;

		/**
		 * @brief Set up field-of-view in radians.
		 * @param up Up angle in radians.
		 * @return Reference to this FieldOfView.
		 */
		FieldOfView &setUp(const Type up)
		{
			_up = up;
			return *this;
		}

		/**
		 * @brief Get up field-of-view in radians.
		 * @return Up angle in radians.
		 */
		Type getUp(void) const noexcept
		{
			return _up;
		}

		/**
		 * @brief Set down field-of-view in radians.
		 * @param down Down angle in radians.
		 * @return Reference to this FieldOfView.
		 */
		FieldOfView &setDown(const Type down)
		{
			_down = down;
			return *this;
		}

		/**
		 * @brief Get down field-of-view in radians.
		 * @return Down angle in radians.
		 */
		Type getDown(void) const noexcept
		{
			return _down;
		}

		/**
		 * @brief Set left field-of-view in radians.
		 * @param left Left angle in radians.
		 * @return Reference to this FieldOfView.
		 */
		FieldOfView &setLeft(const Type left)
		{
			_left = left;
			return *this;
		}

		/**
		 * @brief Get left field-of-view in radians.
		 * @return Left angle in radians.
		 */
		Type getLeft(void) const noexcept
		{
			return _left;
		}

		/**
		 * @brief Set right field-of-view in radians.
		 * @param right Right angle in radians.
		 * @return Reference to this FieldOfView.
		 */
		FieldOfView &setRight(const Type right)
		{
			_right = right;
			return *this;
		}

		/**
		 * @brief Get right field-of-view in radians.
		 * @return Right angle in radians.
		 */
		Type getRight(void) const noexcept
		{
			return _right;
		}

		/**
		 * @brief Check if this FOV is symmetric around vertical and horizontal
		 * axes.
		 * @param epsilon Absolute tolerance used for comparison.
		 * @return True if up~=down and left~=right.
		 */
		bool isSymmetric(Type epsilon = Type { 1e-6 }) const noexcept
		{
			return std::abs(_up - _down) <= epsilon
				&& std::abs(_left - _right) <= epsilon;
		}
	};

	/**
	 * @brief Type alias for single-precision field-of-view component.
	 */
	using FieldOfViewF = FieldOfView<float>;

	/**
	 * @brief Type alias for double-precision field-of-view component.
	 */
	using FieldOfViewD = FieldOfView<double>;

	/**
	 * @brief Stream insertion operator for FieldOfView.
	 * @param stream Output stream.
	 * @param fov Field of view to output.
	 * @return Reference to the output stream.
	 */
	std::ostream &operator<<(std::ostream &stream, const FieldOfViewF &fov);

	/**
	 * @brief Stream insertion operator for FieldOfView.
	 * @param stream Output stream.
	 * @param fov Field of view to output.
	 * @return Reference to the output stream.
	 */
	std::ostream &operator<<(std::ostream &stream, const FieldOfViewD &fov);

}	 // namespace utility::graphic
