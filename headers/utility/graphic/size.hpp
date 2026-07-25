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

#include <concepts>
#include <ostream>

namespace utility::graphic
{

	/**
	 * @brief Concept to constrain size component type.
	 * @tparam Type Candidate component type.
	 */
	template<typename Type>
	concept CanBeSizeComponent =
		std::is_floating_point_v<Type> || std::is_integral_v<Type>;

	/**
	 * @brief Template class representing a size (width, height).
	 *
	 * A size encodes both the spatial width and the height of an object in 2D
	 * space.
	 *
	 * @tparam SizeComponentType Floating-point or integral type for size
	 * components.
	 */
	template<CanBeSizeComponent SizeComponentType> class Size
	{
		private:
		SizeComponentType _width;	  ///< Width component of the size
		SizeComponentType _height;	  ///< Height component of the size
		SizeComponentType _depth;	  ///< Depth component of the size

		public:
		/**
		 * @brief Default constructor (zero position, identity orientation).
		 */
		Size()
			: _width(SizeComponentType { 0 })
			, _height(SizeComponentType { 0 })
			, _depth(SizeComponentType { 0 })
		{
		}
		/**
		 * @brief Construct a size from width and height.
		 * @param width The width component.
		 * @param height The height component.
		 * @param depth The depth component (default is 0).
		 */
		Size(SizeComponentType width, SizeComponentType height,
			 SizeComponentType depth = SizeComponentType { 0 })
			: _width(width)
			, _height(height)
			, _depth(depth)
		{
		}

		/**
		 * @brief Copy constructor.
		 * @param other The Size object to copy from.
		 */
		Size(const Size &other) = default;

		/**
		 * @brief Move constructor.
		 * @param other The Size object to move from.
		 */
		Size(Size &&other) noexcept = default;

		/**
		 * @brief Copy assignment operator.
		 * @param other The Size object to copy from.
		 * @return A reference to this Size object.
		 */
		Size &operator=(const Size &other) = default;

		/**
		 * @brief Move assignment operator.
		 * @param other The Size object to move from.
		 * @return A reference to this Size object.
		 */
		Size &operator=(Size &&other) noexcept = default;

		/**
		 * @brief Default destructor for Size.
		 */
		~Size(void) = default;

		/**
		 * @brief Set the width component.
		 * @param width New width value.
		 * @return Reference to this object for chaining.
		 */
		Size &setWidth(SizeComponentType width) noexcept
		{
			_width = width;
			return *this;
		}

		/**
		 * @brief Get the position component.
		 * @return Const reference to the position.
		 */
		const SizeComponentType &getWidth(void) const noexcept
		{
			return _width;
		}

		/**
		 * @brief Set the height component.
		 * @param height New height value.
		 * @return Reference to this object for chaining.
		 */
		Size &setHeight(SizeComponentType height) noexcept
		{
			_height = height;
			return *this;
		}

		/**
		 * @brief Get the height component.
		 * @return Const reference to the height.
		 */
		const SizeComponentType &getHeight(void) const noexcept
		{
			return _height;
		}

		/**
		 * @brief Set the depth component.
		 * @param depth New depth value.
		 * @return Reference to this object for chaining.
		 */
		Size &setDepth(SizeComponentType depth) noexcept
		{
			_depth = depth;
			return *this;
		}

		/**
		 * @brief Get the depth component.
		 * @return Const reference to the depth.
		 */
		const SizeComponentType &getDepth(void) const noexcept
		{
			return _depth;
		}

		/**
		 * @brief Equality comparison.
		 * @param other Size to compare with.
		 * @return True when position and orientation are equal.
		 */
		bool operator==(const Size &other) const noexcept
		{
			return _width == other._width && _height == other._height
				&& _depth == other._depth;
		}

		/**
		 * @brief Inequality comparison.
		 * @param other Size to compare with.
		 * @return True when either position or orientation differs.
		 */
		bool operator!=(const Size &other) const noexcept
		{
			return !(*this == other);
		}

		/**
		 * @brief Less-than comparison for ordering.
		 * @param other Size to compare with.
		 * @return True when this size is less than the other size.
		 */
		bool operator<(const Size &other) const noexcept
		{
			if (_width != other._width) {
				return _width < other._width;
			}
			if (_height != other._height) {
				return _height < other._height;
			}
			return false;
		}
	};

	/**
	 * @brief Type alias for single-precision size component.
	 */
	using SizeF = Size<float>;

	/**
	 * @brief Type alias for double-precision size component.
	 */
	using SizeD = Size<double>;

	/**
	 * @brief Type alias for integral size component.
	 */
	using SizeI = Size<int>;

	/**
	 * @brief Type alias for unsigned integral size component.
	 */
	using SizeUI = Size<unsigned int>;

	/**
	 * @brief Stream insertion operator for Size.
	 * @param stream Output stream to write to.
	 * @param size Size object to insert into the stream.
	 * @return Reference to the output stream.
	 */
	std::ostream &operator<<(std::ostream &stream, const SizeF &size);

	/**
	 * @brief Stream insertion operator for Size.
	 * @param stream Output stream to write to.
	 * @param size Size object to insert into the stream.
	 * @return Reference to the output stream.
	 */
	std::ostream &operator<<(std::ostream &stream, const SizeD &size);

	/**
	 * @brief Stream insertion operator for Size.
	 * @param stream Output stream to write to.
	 * @param size Size object to insert into the stream.
	 * @return Reference to the output stream.
	 */
	std::ostream &operator<<(std::ostream &stream, const SizeI &size);

	/**
	 * @brief Stream insertion operator for Size.
	 * @param stream Output stream to write to.
	 * @param size Size object to insert into the stream.
	 * @return Reference to the output stream.
	 */
	std::ostream &operator<<(std::ostream &stream, const SizeUI &size);

}	 // namespace utility::graphic
