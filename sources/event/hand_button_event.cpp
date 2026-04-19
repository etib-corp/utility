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

#include "utility/event/hand_button_event.hpp"

namespace utility::event {

bool HandButtonEvent::isButtonValidForHand(const HandType handType,
																					 const Button button) noexcept {
	switch (handType) {
	case HandType::Left:
		return button == Button::X || button == Button::Y || button == Button::Menu;
	case HandType::Right:
		return button == Button::A || button == Button::B || button == Button::System;
	default:
		return false;
	}
}

HandButtonEvent::Factory::~Factory(void) = default;

std::unique_ptr<Event> HandButtonEvent::Factory::create(void) const {
	return std::make_unique<HandButtonEvent>();
}

std::unique_ptr<HandButtonEvent>
HandButtonEvent::Factory::createTyped(void) const {
	return std::make_unique<HandButtonEvent>();
}

HandButtonEvent::HandButtonEvent(void) = default;

HandButtonEvent::~HandButtonEvent(void) = default;

HandButtonEvent &HandButtonEvent::setButton(const Button button) noexcept {
	_button = button;
	return *this;
}

HandButtonEvent::Button HandButtonEvent::getButton(void) const noexcept {
	return _button;
}

bool HandButtonEvent::isValidForCurrentHand(void) const noexcept {
	return isButtonValidForHand(getHandType(), _button);
}

HandButtonEvent &HandButtonEvent::setTouched(const bool touched) noexcept {
	_isTouched = touched;
	return *this;
}

bool HandButtonEvent::isTouched(void) const noexcept { return _isTouched; }

HandButtonEvent &HandButtonEvent::setClicked(const bool clicked) noexcept {
	_isClicked = clicked;
	return *this;
}

bool HandButtonEvent::isClicked(void) const noexcept { return _isClicked; }

} // namespace utility::event