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

#include "utility/event/hand_trigger_event.hpp"

#include "utility/math/common.hpp"

namespace utility::event {

HandTriggerEvent::Factory::~Factory(void) = default;

std::unique_ptr<Event> HandTriggerEvent::Factory::create(void) const {
  return std::make_unique<HandTriggerEvent>();
}

std::unique_ptr<HandTriggerEvent> HandTriggerEvent::Factory::createTyped(void) const {
  return std::make_unique<HandTriggerEvent>();
}

HandTriggerEvent::HandTriggerEvent(void) = default;

HandTriggerEvent::~HandTriggerEvent(void) = default;

HandTriggerEvent &HandTriggerEvent::setValue(const float value) noexcept {
  _value = utility::math::clamp(value, 0.0F, 1.0F);
  return *this;
}

float HandTriggerEvent::getValue(void) const noexcept { return _value; }

HandTriggerEvent &HandTriggerEvent::setTouched(const bool touched) noexcept {
  _isTouched = touched;
  return *this;
}

bool HandTriggerEvent::isTouched(void) const noexcept { return _isTouched; }

HandTriggerEvent &HandTriggerEvent::setProximity(const bool proximity) noexcept {
  _isProximity = proximity;
  return *this;
}

bool HandTriggerEvent::isProximity(void) const noexcept { return _isProximity; }

} // namespace utility::event
