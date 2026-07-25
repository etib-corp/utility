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

#include <memory>

#include "utility/math/vector.hpp"

#include "utility/event/event.hpp"

namespace utility::event
{

	/**
	 * @brief Mouse wheel event.
	 *
	 * Represents mouse wheel scroll with offset values.
	 */
	class MouseWheelEvent: public Event
	{
		public:
		/**
		 * @brief Factory for creating MouseWheelEvent instances.
		 */
		class Factory: public Event::AbstractFactory
		{
			public:
			~Factory(void) override;

			/**
			 * @brief Create a MouseWheelEvent as a base Event pointer.
			 * @return Newly created MouseWheelEvent as std::shared_ptr<Event>.
			 */
			std::shared_ptr<Event> create(void) const override;

			/**
			 * @brief Create a strongly-typed MouseWheelEvent.
			 * @return Newly created MouseWheelEvent as
			 * std::shared_ptr<MouseWheelEvent>.
			 */
			std::shared_ptr<MouseWheelEvent> createTyped(void) const;
		};

		private:
		math::Vector2F _offset { 0.0f, 0.0f };	  ///< Scroll offset (x, y)

		public:
		/**
		 * @brief Default constructor.
		 */
		explicit MouseWheelEvent(void);

		/**
		 * @brief Default destructor.
		 */
		~MouseWheelEvent(void) override;

		/**
		 * @brief Set the scroll offset.
		 * @param offset The scroll offset as a 2D vector (x, y).
		 * Positive y typically means scroll up/away from user.
		 * Positive x typically means scroll right.
		 * @return Reference to this MouseWheelEvent for method chaining.
		 */
		MouseWheelEvent &setOffset(const math::Vector2F &offset) noexcept;

		/**
		 * @brief Get the scroll offset.
		 * @return The scroll offset as a 2D vector (x, y).
		 */
		math::Vector2F getOffset(void) const noexcept;
	};

}	 // namespace utility::event
