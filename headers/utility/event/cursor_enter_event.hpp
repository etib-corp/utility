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

#include "utility/event/event.hpp"

namespace utility::event
{

	/**
	 * @brief Cursor enter/leave event.
	 *
	 * Represents the cursor entering or leaving the content area of a window.
	 * This event is triggered when the cursor crosses the boundary of the
	 * window's content area.
	 */
	class CursorEnterEvent: public Event
	{
		public:
		/**
		 * @brief Factory for creating CursorEnterEvent instances.
		 */
		class Factory: public Event::AbstractFactory
		{
			public:
			~Factory(void) override;

			/**
			 * @brief Create a CursorEnterEvent as a base Event pointer.
			 * @return Newly created CursorEnterEvent as std::shared_ptr<Event>.
			 */
			std::shared_ptr<Event> create(void) const override;

			/**
			 * @brief Create a strongly-typed CursorEnterEvent.
			 * @return Newly created CursorEnterEvent as
			 * std::shared_ptr<CursorEnterEvent>.
			 */
			std::shared_ptr<CursorEnterEvent> createTyped(void) const;
		};

		private:
		bool _entered { false }; /**< True if cursor entered, false if left */

		public:
		/**
		 * @brief Default constructor.
		 */
		explicit CursorEnterEvent(void);

		/**
		 * @brief Default destructor.
		 */
		~CursorEnterEvent(void) override;

		/**
		 * @brief Set whether the cursor entered or left the content area.
		 * @param entered True if the cursor entered the content area, false if
		 * it left.
		 * @return Reference to this CursorEnterEvent for method chaining.
		 */
		CursorEnterEvent &setEntered(const bool entered) noexcept;

		/**
		 * @brief Check if the cursor entered the content area.
		 * @return True if the cursor entered, false if it left.
		 */
		bool isEntered(void) const noexcept;
	};

}	 // namespace utility::event
