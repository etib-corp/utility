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

#include "utility/event/hand_thumb_rest_event.hpp"

namespace utility::event {

HandThumbRestEvent::Factory::~Factory(void) = default;

std::unique_ptr<Event> HandThumbRestEvent::Factory::create(void) const {
  return std::make_unique<HandThumbRestEvent>();
}

std::unique_ptr<HandThumbRestEvent>
HandThumbRestEvent::Factory::createTyped(void) const {
  return std::make_unique<HandThumbRestEvent>();
}

HandThumbRestEvent::HandThumbRestEvent(void) = default;

HandThumbRestEvent::~HandThumbRestEvent(void) = default;

HandThumbRestEvent &
HandThumbRestEvent::setTouched(const bool touched) noexcept {
  _isTouched = touched;
  return *this;
}

bool HandThumbRestEvent::isTouched(void) const noexcept { return _isTouched; }

HandThumbRestEvent &
HandThumbRestEvent::setProximity(const bool proximity) noexcept {
  _isProximity = proximity;
  return *this;
}

bool HandThumbRestEvent::isProximity(void) const noexcept {
  return _isProximity;
}

} // namespace utility::event
