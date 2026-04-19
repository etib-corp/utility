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

#include "utility/event/hand_thumb_stick_event.hpp"

#include "utility/math/common.hpp"

namespace utility::event {

HandThumbStickEvent::Factory::~Factory(void) = default;

std::unique_ptr<Event> HandThumbStickEvent::Factory::create(void) const {
  return std::make_unique<HandThumbStickEvent>();
}

std::unique_ptr<HandThumbStickEvent>
HandThumbStickEvent::Factory::createTyped(void) const {
  return std::make_unique<HandThumbStickEvent>();
}

HandThumbStickEvent::HandThumbStickEvent(void) = default;

HandThumbStickEvent::~HandThumbStickEvent(void) = default;

HandThumbStickEvent &HandThumbStickEvent::setX(const float x) noexcept {
  _x = utility::math::clamp(x, -1.0F, 1.0F);
  return *this;
}

float HandThumbStickEvent::getX(void) const noexcept { return _x; }

HandThumbStickEvent &HandThumbStickEvent::setY(const float y) noexcept {
  _y = utility::math::clamp(y, -1.0F, 1.0F);
  return *this;
}

float HandThumbStickEvent::getY(void) const noexcept { return _y; }

HandThumbStickEvent &HandThumbStickEvent::setAxis(const float x,
                                                   const float y) noexcept {
  _x = utility::math::clamp(x, -1.0F, 1.0F);
  _y = utility::math::clamp(y, -1.0F, 1.0F);
  return *this;
}

HandThumbStickEvent &
HandThumbStickEvent::setTouched(const bool touched) noexcept {
  _isTouched = touched;
  return *this;
}

bool HandThumbStickEvent::isTouched(void) const noexcept { return _isTouched; }

HandThumbStickEvent &
HandThumbStickEvent::setClicked(const bool clicked) noexcept {
  _isClicked = clicked;
  return *this;
}

bool HandThumbStickEvent::isClicked(void) const noexcept { return _isClicked; }

} // namespace utility::event
