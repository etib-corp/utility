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

#include "utility/event/text_editing_event.hpp"

namespace utility::event {

TextEditingEvent::Factory::~Factory(void) = default;

std::unique_ptr<Event> TextEditingEvent::Factory::create(void) const {
	return std::make_unique<TextEditingEvent>();
}

std::unique_ptr<TextEditingEvent>
TextEditingEvent::Factory::createTyped(void) const {
	return std::make_unique<TextEditingEvent>();
}

TextEditingEvent::TextEditingEvent(void) = default;

TextEditingEvent::~TextEditingEvent(void) = default;

TextEditingEvent &TextEditingEvent::setText(const std::string &text) {
	_text = text;
	return *this;
}

std::string TextEditingEvent::getText(void) const { return _text; }

TextEditingEvent &TextEditingEvent::setStart(const int start) noexcept {
	_start = start;
	return *this;
}

int TextEditingEvent::getStart(void) const noexcept { return _start; }

TextEditingEvent &TextEditingEvent::setLength(const int length) noexcept {
	_length = length;
	return *this;
}

int TextEditingEvent::getLength(void) const noexcept { return _length; }

} // namespace utility::event
