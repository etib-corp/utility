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

#include "utility/event/keyboard_event.hpp"

namespace utility::event {

KeyboardEvent::Factory::~Factory(void) = default;

std::unique_ptr<Event> KeyboardEvent::Factory::create(void) const {
	return std::make_unique<KeyboardEvent>();
}

std::unique_ptr<KeyboardEvent> KeyboardEvent::Factory::createTyped(void) const {
	return std::make_unique<KeyboardEvent>();
}

KeyboardEvent::KeyboardEvent(void) = default;

KeyboardEvent::~KeyboardEvent(void) = default;

KeyboardEvent::ScanCode KeyboardEvent::getScancode(void) const noexcept {
	return _scancode;
}

KeyboardEvent &KeyboardEvent::setScancode(const ScanCode scancode) noexcept {
	_scancode = scancode;
	return *this;
}

KeyboardEvent &KeyboardEvent::setKeycode(const KeyCode keycode) noexcept {
	_keycode = keycode;
	return *this;
}

KeyboardEvent::KeyCode KeyboardEvent::getKeycode(void) const noexcept {
	return _keycode;
}

KeyboardEvent &
KeyboardEvent::setModifiers(const KeyModifiers modifiers) noexcept {
	_modifiers = std::bitset<sizeof(KeyModifiers) * 8>(
			static_cast<std::size_t>(modifiers));
	return *this;
}

bool KeyboardEvent::isModifierSet(const KeyModifiers modifier) const noexcept {
	const auto mask = static_cast<std::size_t>(modifier);
	if (mask == 0) {
		return _modifiers.none();
	}
	return (_modifiers.to_ulong() & mask) != 0;
}

KeyboardEvent &KeyboardEvent::setIsDownEvent(const bool isDown) noexcept {
	isDownEvent = isDown;
	return *this;
}

bool KeyboardEvent::getIsDownEvent(void) const noexcept { return isDownEvent; }

KeyboardEvent &
KeyboardEvent::setIsRepeatEvent(const bool isRepeat) noexcept {
	isRepeatEvent = isRepeat;
	return *this;
}

bool KeyboardEvent::getIsRepeatEvent(void) const noexcept {
	return isRepeatEvent;
}

} // namespace utility::event