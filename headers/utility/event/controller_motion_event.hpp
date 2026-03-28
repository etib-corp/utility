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

#include "utility/graphic/pose.hpp"

namespace utility::event {

/**
 * @brief Controller motion event containing aim and grip poses.
 */
class ControllerMotionEvent : public ControllerEvent {
public:
  /**
   * @brief Factory for creating ControllerMotionEvent instances.
   */
  class Factory : public Event::AbstractFactory {
  public:
    ~Factory(void) override = default;

    /**
     * @brief Create a ControllerMotionEvent as base Event pointer.
     * @return Newly created ControllerMotionEvent.
     */
    std::unique_ptr<Event> create(void) const override {
      return std::make_unique<ControllerMotionEvent>();
    }

    /**
     * @brief Create a strongly-typed ControllerMotionEvent.
     * @return Newly created ControllerMotionEvent.
     */
    std::unique_ptr<ControllerMotionEvent> createTyped(void) const {
      return std::make_unique<ControllerMotionEvent>();
    }
  };

private:
  graphic::PoseF _aim;  /**< Aim pose of the controller */
  graphic::PoseF _grip; /**< Grip pose of the controller */

public:
  /**
   * @brief Default constructor.
   */
  explicit ControllerMotionEvent(void) = default;

  /**
   * @brief Default destructor.
   */
  ~ControllerMotionEvent(void) override = default;

  /**
   * @brief Set aim pose.
   * @param aim Aim pose.
   * @return Reference to this ControllerMotionEvent.
   */
  ControllerMotionEvent &setAim(const graphic::PoseF &aim) noexcept {
    _aim = aim;
    return *this;
  }

  /**
   * @brief Get aim pose.
   * @return Aim pose.
   */
  graphic::PoseF getAim(void) const noexcept { return _aim; }

  /**
   * @brief Set grip pose.
   * @param grip Grip pose.
   * @return Reference to this ControllerMotionEvent.
   */
  ControllerMotionEvent &setGrip(const graphic::PoseF &grip) noexcept {
    _grip = grip;
    return *this;
  }

  /**
   * @brief Get grip pose.
   * @return Grip pose.
   */
  graphic::PoseF getGrip(void) const noexcept { return _grip; }
};

} // namespace utility::event
