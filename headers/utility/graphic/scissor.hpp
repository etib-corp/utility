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

namespace utility::graphic
{

	/**
	 * @brief Axis-aligned scissor (clip) rectangle.
	 *
	 * Coordinates are expressed in framebuffer pixels, with the origin at the
	 * top-left corner of the render target. Engines are expected to clamp the
	 * rectangle to their render target extent.
	 */
	struct ScissorRect {
		float x { 0.0f };		  ///< Rectangle origin along X, in pixels.
		float y { 0.0f };		  ///< Rectangle origin along Y, in pixels.
		float width { 0.0f };	  ///< Rectangle width, in pixels.
		float height { 0.0f };	  ///< Rectangle height, in pixels.

		/**
		 * @brief Equality operator.
		 * @param other The other rectangle to compare with.
		 * @return True when both rectangles have identical components.
		 */
		bool operator==(const ScissorRect &other) const
		{
			return x == other.x && y == other.y && width == other.width
				&& height == other.height;
		}

		/**
		 * @brief Inequality operator.
		 * @param other The other rectangle to compare with.
		 * @return True when the rectangles differ.
		 */
		bool operator!=(const ScissorRect &other) const
		{
			return !(*this == other);
		}
	};

}	 // namespace utility::graphic
