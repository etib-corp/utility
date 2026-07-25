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

#include <cstdint>
#include <memory>
#include <ostream>

#include "utility/math/vector.hpp"

#include "utility/event/event.hpp"

namespace utility::event
{

	/**
	 * @brief Mouse button event.
	 *
	 * Represents mouse button presses/releases with position and button states.
	 */
	class MouseButtonEvent: public Event
	{
		public:
		using MousePosition =
			math::Vector2F; /**< Type alias for mouse position as a 2D unsigned
								integer vector (x, y) */

		/**
		 * @brief Mouse buttons enumeration.
		 */
		enum class Button : std::uint8_t {
			Unknown = 0,
			Left	= 1,
			Middle	= 2,
			Right	= 3,
			X1		= 4,
			X2		= 5,
		};

		/**
		 * @brief Factory for creating MouseButtonEvent instances.
		 */
		class Factory: public Event::AbstractFactory
		{
			public:
			~Factory(void) override;

			/**
			 * @brief Create a MouseButtonEvent as a base Event pointer.
			 * @return Newly created MouseButtonEvent as std::shared_ptr<Event>.
			 */
			std::shared_ptr<Event> create(void) const override;

			/**
			 * @brief Create a strongly-typed MouseButtonEvent.
			 * @return Newly created MouseButtonEvent as
			 * std::shared_ptr<MouseButtonEvent>.
			 */
			std::shared_ptr<MouseButtonEvent> createTyped(void) const;
		};

		private:
		MousePosition _position { 0, 0 }; /**< Current mouse position (x, y) */
		Button _button {
			Button::Unknown
		}; /**< Currently active mouse button */
		bool _pressed { false }; /**< True when the button is pressed */

		public:
		/**
		 * @brief Default constructor.
		 */
		explicit MouseButtonEvent(void);

		/**
		 * @brief Default destructor.
		 */
		~MouseButtonEvent(void) override;

		/**
		 * @brief Set the current mouse position.
		 * @param position The mouse position as a 2D vector (x, y).
		 * @return Reference to this MouseButtonEvent for method chaining.
		 */
		MouseButtonEvent &setPosition(const MousePosition &position) noexcept;

		/**
		 * @brief Get the current mouse position.
		 * @return The mouse position as a 2D vector (x, y).
		 */
		MousePosition getPosition(void) const noexcept;

		/**
		 * @brief Set the state of a mouse button.
		 * @param button The mouse button to set.
		 * @return Reference to this MouseButtonEvent for method chaining.
		 */
		MouseButtonEvent &setButton(const Button button) noexcept;

		/**
		 * @brief Get the current mouse button.
		 * @return The current button.
		 */
		Button getButton(void) const noexcept;

		/**
		 * @brief Set the pressed state of the button.
		 * @param pressed True if the button is pressed, false if released.
		 * @return Reference to this MouseButtonEvent for method chaining.
		 */
		MouseButtonEvent &setPressed(const bool pressed) noexcept;

		/**
		 * @brief Get the pressed state of the button.
		 * @return True if the button is pressed, false otherwise.
		 */
		bool isButtonPressed(void) const noexcept;
	};

	/**
	 * @brief Stream insertion operator for MouseButtonEvent::Button.
	 * @param stream The output stream.
	 * @param button The mouse button to output.
	 * @return Reference to the output stream.
	 */
	std::ostream &operator<<(std::ostream &stream,
							 const MouseButtonEvent::Button button);

	/**
	 * @brief Stream insertion operator for MouseButtonEvent.
	 * @param stream The output stream.
	 * @param mouseButtonEvent The MouseButtonEvent to output.
	 * @return Reference to the output stream.
	 */
	std::ostream &operator<<(std::ostream &stream,
							 const MouseButtonEvent &mouseButtonEvent);

}	 // namespace utility::event