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
 * @brief Controller thumbstick event.
 */
class ControllerThumbStickEvent : public ControllerEvent {
public:
  /**
   * @brief Factory for creating ControllerThumbStickEvent instances.
   */
  class Factory : public Event::AbstractFactory {
  public:
    ~Factory(void) override = default;

    /**
     * @brief Create a ControllerThumbStickEvent as base Event pointer.
     * @return Newly created ControllerThumbStickEvent.
     */
    std::unique_ptr<Event> create(void) const override {
      return std::make_unique<ControllerThumbStickEvent>();
    }

    /**
     * @brief Create a strongly-typed ControllerThumbStickEvent.
     * @return Newly created ControllerThumbStickEvent.
     */
    std::unique_ptr<ControllerThumbStickEvent> createTyped(void) const {
      return std::make_unique<ControllerThumbStickEvent>();
    }
  };

private:
  /** @brief X axis value in range [-1, 1]. */
  float _x{0.0F};

  /** @brief Y axis value in range [-1, 1]. */
  float _y{0.0F};

  /** @brief True when the thumbstick surface is touched. */
  bool _isTouched{false};

  /** @brief True when the thumbstick is clicked. */
  bool _isClicked{false};

  /**
   * @brief Clamp axis value to the expected thumbstick range.
   * @param value Input axis value.
   * @return Clamped value in [-1, 1].
   */
  static float clampAxis(const float value) noexcept {
    return std::clamp(value, -1.0F, 1.0F);
  }

public:
  /**
   * @brief Default constructor.
   */
  explicit ControllerThumbStickEvent(void) = default;

  /**
   * @brief Default destructor.
   */
  ~ControllerThumbStickEvent(void) override = default;

  /**
   * @brief Set X axis value.
   * @param x Axis value.
   * @return Reference to this ControllerThumbStickEvent.
   */
  ControllerThumbStickEvent &setX(const float x) noexcept {
    _x = clampAxis(x);
    return *this;
  }

  /**
   * @brief Get X axis value.
   * @return Axis value in [-1, 1].
   */
  float getX(void) const noexcept { return _x; }

  /**
   * @brief Set Y axis value.
   * @param y Axis value.
   * @return Reference to this ControllerThumbStickEvent.
   */
  ControllerThumbStickEvent &setY(const float y) noexcept {
    _y = clampAxis(y);
    return *this;
  }

  /**
   * @brief Get Y axis value.
   * @return Axis value in [-1, 1].
   */
  float getY(void) const noexcept { return _y; }

  /**
   * @brief Set both axis values.
   * @param x X axis value.
   * @param y Y axis value.
   * @return Reference to this ControllerThumbStickEvent.
   */
  ControllerThumbStickEvent &setAxis(const float x, const float y) noexcept {
    _x = clampAxis(x);
    _y = clampAxis(y);
    return *this;
  }

  /**
   * @brief Set touched state.
   * @param touched True if touched.
   * @return Reference to this ControllerThumbStickEvent.
   */
  ControllerThumbStickEvent &setTouched(const bool touched) noexcept {
    _isTouched = touched;
    return *this;
  }

  /**
   * @brief Get touched state.
   * @return True if touched.
   */
  bool isTouched(void) const noexcept { return _isTouched; }

  /**
   * @brief Set clicked state.
   * @param clicked True if clicked.
   * @return Reference to this ControllerThumbStickEvent.
   */
  ControllerThumbStickEvent &setClicked(const bool clicked) noexcept {
    _isClicked = clicked;
    return *this;
  }

  /**
   * @brief Get clicked state.
   * @return True if clicked.
   */
  bool isClicked(void) const noexcept { return _isClicked; }
};

} // namespace utility::event
