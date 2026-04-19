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

#include "utility/event/hand_haptic_event.hpp"

#include <algorithm>

#include "utility/math/common.hpp"

namespace utility::event {

HandHapticEvent::Factory::~Factory(void) = default;

std::unique_ptr<Event> HandHapticEvent::Factory::create(void) const {
  return std::make_unique<HandHapticEvent>();
}

std::unique_ptr<HandHapticEvent> HandHapticEvent::Factory::createTyped(void) const {
  return std::make_unique<HandHapticEvent>();
}

HandHapticEvent::HandHapticEvent(void) = default;

HandHapticEvent::~HandHapticEvent(void) = default;

HandHapticEvent &HandHapticEvent::setAmplitude(const float amplitude) noexcept {
  _amplitude = utility::math::clamp(amplitude, 0.0F, 1.0F);
  return *this;
}

float HandHapticEvent::getAmplitude(void) const noexcept { return _amplitude; }

HandHapticEvent &HandHapticEvent::setFrequency(const float frequency) noexcept {
  _frequencyHz = std::max(0.0F, frequency);
  return *this;
}

float HandHapticEvent::getFrequency(void) const noexcept { return _frequencyHz; }

HandHapticEvent &
HandHapticEvent::setDuration(const std::int64_t duration) noexcept {
  _durationNs = std::max<std::int64_t>(0, duration);
  return *this;
}

std::int64_t HandHapticEvent::getDuration(void) const noexcept {
  return _durationNs;
}

HandHapticEvent &
HandHapticEvent::setFrequencyHz(const float frequencyHz) noexcept {
  return setFrequency(frequencyHz);
}

float HandHapticEvent::getFrequencyHz(void) const noexcept {
  return getFrequency();
}

HandHapticEvent &
HandHapticEvent::setDurationNs(const std::int64_t durationNs) noexcept {
  return setDuration(durationNs);
}

std::int64_t HandHapticEvent::getDurationNs(void) const noexcept {
  return getDuration();
}

} // namespace utility::event
