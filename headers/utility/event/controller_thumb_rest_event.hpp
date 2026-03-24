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

#include <memory>

#include "utility/event/controller_event.hpp"

namespace utility::event {

/**
 * @brief Controller thumb rest event.
 */
class ControllerThumbRestEvent : public ControllerEvent {
public:
  /**
   * @brief Factory for creating ControllerThumbRestEvent instances.
   */
  class Factory : public Event::AbstractFactory {
  public:
    ~Factory(void) override = default;

    /**
     * @brief Create a ControllerThumbRestEvent as base Event pointer.
     * @return Newly created ControllerThumbRestEvent.
     */
    std::unique_ptr<Event> create(void) const override {
      return std::make_unique<ControllerThumbRestEvent>();
    }

    /**
     * @brief Create a strongly-typed ControllerThumbRestEvent.
     * @return Newly created ControllerThumbRestEvent.
     */
    std::unique_ptr<ControllerThumbRestEvent> createTyped(void) const {
      return std::make_unique<ControllerThumbRestEvent>();
    }
  };

private:
  /** @brief True when thumb rest is touched. */
  bool _isTouched{false};

  /** @brief True when thumb is in thumb-rest proximity region. */
  bool _isProximity{false};

public:
  /**
   * @brief Default constructor.
   */
  explicit ControllerThumbRestEvent(void) = default;

  /**
   * @brief Default destructor.
   */
  ~ControllerThumbRestEvent(void) override = default;
  /**
   * @brief Set touched state.
   * @param touched True if touched.
   * @return Reference to this ControllerThumbRestEvent.
   */
  ControllerThumbRestEvent &setTouched(const bool touched) noexcept {
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
   * @return Reference to this ControllerThumbRestEvent.
   */
  ControllerThumbRestEvent &setProximity(const bool proximity) noexcept {
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
