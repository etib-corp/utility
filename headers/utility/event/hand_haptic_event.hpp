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

#pragma once

#include <cstdint>
#include <memory>

#include "utility/event/hand_event.hpp"

namespace utility::event {

/**
 * @brief Shared behavior for hand haptic output events.
 */
class HandHapticEvent : public HandEvent {
private:
  /** @brief Amplitude of the vibration between 0.0 and 1.0. */
  float _amplitude{1.0F};

  /** @brief Frequency of the vibration in Hz. */
  float _frequencyHz{0.0F};

  /** @brief Number of nanoseconds the vibration should last. */
  std::int64_t _durationNs{0};

public:
  /**
   * @brief Factory for creating HandHapticEvent instances.
   */
  class Factory : public Event::AbstractFactory {
  public:
    ~Factory(void) override;

    /**
     * @brief Create a HandHapticEvent as base Event pointer.
     * @return Newly created HandHapticEvent.
     */
    std::unique_ptr<Event> create(void) const override;

    /**
     * @brief Create a strongly-typed HandHapticEvent.
     * @return Newly created HandHapticEvent.
     */
    std::unique_ptr<HandHapticEvent> createTyped(void) const;
  };

  /**
   * @brief Default constructor.
   */
  explicit HandHapticEvent(void);

  /**
   * @brief Default destructor.
   */
  ~HandHapticEvent(void) override;

  /**
   * @brief Set haptic amplitude.
   * @param amplitude Amplitude in [0, 1].
   * @return Reference to this event.
   */
  HandHapticEvent &setAmplitude(const float amplitude) noexcept;

  /**
   * @brief Get haptic amplitude.
   * @return Amplitude in [0, 1].
   */
  float getAmplitude(void) const noexcept;

  /**
   * @brief Set the frequency of the vibration in Hz.
   * @param frequency Frequency in Hz.
   * @return Reference to this event.
   */
  HandHapticEvent &setFrequency(const float frequency) noexcept;

  /**
   * @brief Get the frequency of the vibration in Hz.
   * @return Frequency in Hz.
   */
  float getFrequency(void) const noexcept;

  /**
   * @brief Set the number of nanoseconds the vibration should last.
   * @param duration Duration in nanoseconds.
   * @return Reference to this event.
   */
  HandHapticEvent &setDuration(const std::int64_t duration) noexcept;

  /**
   * @brief Get the number of nanoseconds the vibration should last.
   * @return Duration in nanoseconds.
   */
  std::int64_t getDuration(void) const noexcept;

  /**
   * @brief Backward-compatible alias for setFrequency.
   * @param frequencyHz Frequency in Hz.
   * @return Reference to this event.
   */
  HandHapticEvent &setFrequencyHz(const float frequencyHz) noexcept;

  /**
   * @brief Backward-compatible alias for getFrequency.
   * @return Frequency in Hz.
   */
  float getFrequencyHz(void) const noexcept;

  /**
   * @brief Backward-compatible alias for setDuration.
   * @param durationNs Duration in nanoseconds.
   * @return Reference to this event.
   */
  HandHapticEvent &setDurationNs(const std::int64_t durationNs) noexcept;

  /**
   * @brief Backward-compatible alias for getDuration.
   * @return Duration in nanoseconds.
   */
  std::int64_t getDurationNs(void) const noexcept;
};

} // namespace utility::event
