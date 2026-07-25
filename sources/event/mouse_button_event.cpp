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

#include "utility/event/mouse_button_event.hpp"

namespace utility::event
{

	MouseButtonEvent::Factory::~Factory(void) = default;

	std::shared_ptr<Event> MouseButtonEvent::Factory::create(void) const
	{
		return std::make_unique<MouseButtonEvent>();
	}

	std::shared_ptr<MouseButtonEvent>
		MouseButtonEvent::Factory::createTyped(void) const
	{
		return std::make_unique<MouseButtonEvent>();
	}

	MouseButtonEvent::MouseButtonEvent(void) = default;

	MouseButtonEvent::~MouseButtonEvent(void) = default;

	MouseButtonEvent &
		MouseButtonEvent::setPosition(const MousePosition &position) noexcept
	{
		_position = position;
		return *this;
	}

	MouseButtonEvent::MousePosition
		MouseButtonEvent::getPosition(void) const noexcept
	{
		return _position;
	}

	MouseButtonEvent &MouseButtonEvent::setButton(const Button button) noexcept
	{
		_button = button;
		return *this;
	}

	MouseButtonEvent::Button MouseButtonEvent::getButton(void) const noexcept
	{
		return _button;
	}

	MouseButtonEvent &MouseButtonEvent::setPressed(const bool pressed) noexcept
	{
		_pressed = pressed;
		return *this;
	}

	bool MouseButtonEvent::isButtonPressed(void) const noexcept
	{
		return _pressed;
	}

	std::ostream &operator<<(std::ostream &stream,
							 const MouseButtonEvent::Button button)
	{
		switch (button) {
			case MouseButtonEvent::Button::Unknown:
				stream << "Unknown";
				break;
			case MouseButtonEvent::Button::Left:
				stream << "Left";
				break;
			case MouseButtonEvent::Button::Right:
				stream << "Right";
				break;
			case MouseButtonEvent::Button::Middle:
				stream << "Middle";
				break;
			case MouseButtonEvent::Button::X1:
				stream << "X1";
				break;
			case MouseButtonEvent::Button::X2:
				stream << "X2";
				break;
		}
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream,
							 const MouseButtonEvent &mouseButtonEvent)
	{
		stream << "MouseButtonEvent("
			   << "Position: " << mouseButtonEvent.getPosition()
			   << ", Button: " << mouseButtonEvent.getButton()
			   << ", Pressed: " << std::boolalpha
			   << mouseButtonEvent.isButtonPressed() << ")";
		return stream;
	}

}	 // namespace utility::event