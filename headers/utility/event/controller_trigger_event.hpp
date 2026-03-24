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

#include <algorithm>
#include <memory>

#include "utility/event/controller_event.hpp"

namespace utility::event {

/**
 * @brief Controller trigger event.
 */
class ControllerTriggerEvent : public ControllerEvent {
public:
  /**
   * @brief Factory for creating ControllerTriggerEvent instances.
   */
  class Factory : public Event::AbstractFactory {
  public:
    ~Factory(void) override = default;

    /**
     * @brief Create a ControllerTriggerEvent as base Event pointer.
     * @return Newly created ControllerTriggerEvent.
     */
    std::unique_ptr<Event> create(void) const override {
      return std::make_unique<ControllerTriggerEvent>();
    }

    /**
     * @brief Create a strongly-typed ControllerTriggerEvent.
     * @return Newly created ControllerTriggerEvent.
     */
    std::unique_ptr<ControllerTriggerEvent> createTyped(void) const {
      return std::make_unique<ControllerTriggerEvent>();
    }
  };

private:
  /** @brief Trigger value in range [0, 1]. */
  float _value{0.0F};

  /** @brief True when trigger is touched. */
  bool _isTouched{false};

  /** @brief True when finger is in trigger proximity region. */
  bool _isProximity{false};

  /**
   * @brief Clamp trigger value to the expected range.
   * @param value Input trigger value.
   * @return Clamped value in [0, 1].
   */
  static float clampValue(const float value) noexcept {
    return std::clamp(value, 0.0F, 1.0F);
  }

public:
  /**
   * @brief Default constructor.
   */
  explicit ControllerTriggerEvent(void) = default;

  /**
   * @brief Default destructor.
   */
  ~ControllerTriggerEvent(void) override = default;

  /**
   * @brief Set trigger value.
   * @param value Trigger value.
   * @return Reference to this ControllerTriggerEvent.
   */
  ControllerTriggerEvent &setValue(const float value) noexcept {
    _value = clampValue(value);
    return *this;
  }

  /**
   * @brief Get trigger value.
   * @return Value in [0, 1].
   */
  float getValue(void) const noexcept { return _value; }

  /**
   * @brief Set touched state.
   * @param touched True if touched.
   * @return Reference to this ControllerTriggerEvent.
   */
  ControllerTriggerEvent &setTouched(const bool touched) noexcept {
    _isTouched = touched;
    return *this;
  }

  /**
   * @brief Get touched state.
   * @return True if touched.
   */
  bool isTouched(void) const noexcept { return _isTouched; }

  /**
   * @brief Set proximity state.
   * @param proximity True if in proximity.
   * @return Reference to this ControllerTriggerEvent.
   */
  ControllerTriggerEvent &setProximity(const bool proximity) noexcept {
    _isProximity = proximity;
    return *this;
  }

  /**
   * @brief Get proximity state.
   * @return True if in proximity.
   */
  bool isProximity(void) const noexcept { return _isProximity; }
};

} // namespace utility::event
