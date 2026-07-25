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
#include <ostream>

#include "utility/event/hand_event.hpp"

#include "utility/graphic/pose.hpp"

namespace utility::event
{

	/**
	 * @brief Hand motion event containing aim/grip/grip_surface poses.
	 */
	class HandMotionEvent: public HandEvent
	{
		public:
		/**
		 * @brief Factory for creating HandMotionEvent instances.
		 */
		class Factory: public Event::AbstractFactory
		{
			public:
			~Factory(void) override;

			/**
			 * @brief Create a HandMotionEvent as base Event pointer.
			 * @return Newly created HandMotionEvent.
			 */
			std::shared_ptr<Event> create(void) const override;

			/**
			 * @brief Create a strongly-typed HandMotionEvent.
			 * @return Newly created HandMotionEvent.
			 */
			std::shared_ptr<HandMotionEvent> createTyped(void) const;
		};

		public:
		/**
		 * @brief Default constructor.
		 */
		explicit HandMotionEvent(void);

		/**
		 * @brief Default destructor.
		 */
		~HandMotionEvent(void) override;
	};

	/**
	 * @brief Stream insertion operator for HandMotionEvent.
	 * @param stream The output stream.
	 * @param handMotionEvent The HandMotionEvent to output.
	 * @return Reference to the output stream.
	 */
	std::ostream &operator<<(std::ostream &stream,
							 const HandMotionEvent &handMotionEvent);

}	 // namespace utility::event
