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

#include "utility/event/hand_motion_event.hpp"

namespace utility::event {

HandMotionEvent::Factory::~Factory(void) = default;

std::unique_ptr<Event> HandMotionEvent::Factory::create(void) const {
  return std::make_unique<HandMotionEvent>();
}

std::unique_ptr<HandMotionEvent> HandMotionEvent::Factory::createTyped(void) const {
  return std::make_unique<HandMotionEvent>();
}

HandMotionEvent::HandMotionEvent(void) = default;

HandMotionEvent::~HandMotionEvent(void) = default;

HandMotionEvent &HandMotionEvent::setAim(const graphic::PoseF &aim) noexcept {
  _aim = aim;
  return *this;
}

graphic::PoseF HandMotionEvent::getAim(void) const noexcept { return _aim; }

HandMotionEvent &HandMotionEvent::setGrip(const graphic::PoseF &grip) noexcept {
  _grip = grip;
  return *this;
}

graphic::PoseF HandMotionEvent::getGrip(void) const noexcept { return _grip; }

HandMotionEvent &
HandMotionEvent::setGripSurface(const graphic::PoseF &gripSurface) noexcept {
  _gripSurface = gripSurface;
  return *this;
}

graphic::PoseF HandMotionEvent::getGripSurface(void) const noexcept {
  return _gripSurface;
}

} // namespace utility::event
