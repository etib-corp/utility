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

#include "utility/event/hand_squeeze_event.hpp"

#include "utility/math/common.hpp"

namespace utility::event {

HandSqueezeEvent::Factory::~Factory(void) = default;

std::unique_ptr<Event> HandSqueezeEvent::Factory::create(void) const {
  return std::make_unique<HandSqueezeEvent>();
}

std::unique_ptr<HandSqueezeEvent> HandSqueezeEvent::Factory::createTyped(void) const {
  return std::make_unique<HandSqueezeEvent>();
}

HandSqueezeEvent::HandSqueezeEvent(void) = default;

HandSqueezeEvent::~HandSqueezeEvent(void) = default;

HandSqueezeEvent &HandSqueezeEvent::setValue(const float value) noexcept {
  _value = utility::math::clamp(value, 0.0F, 1.0F);
  return *this;
}

float HandSqueezeEvent::getValue(void) const noexcept { return _value; }

HandSqueezeEvent &HandSqueezeEvent::setForce(const float force) noexcept {
  _force = utility::math::clamp(force, 0.0F, 1.0F);
  return *this;
}

float HandSqueezeEvent::getForce(void) const noexcept { return _force; }

HandSqueezeEvent &HandSqueezeEvent::setTouched(const bool touched) noexcept {
  _isTouched = touched;
  return *this;
}

bool HandSqueezeEvent::isTouched(void) const noexcept { return _isTouched; }

HandSqueezeEvent &HandSqueezeEvent::setClicked(const bool clicked) noexcept {
  _isClicked = clicked;
  return *this;
}

bool HandSqueezeEvent::isClicked(void) const noexcept { return _isClicked; }

} // namespace utility::event
