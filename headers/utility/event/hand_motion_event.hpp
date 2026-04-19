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

#include "utility/event/hand_event.hpp"

#include "utility/graphic/pose.hpp"

namespace utility::event {

/**
 * @brief Hand motion event containing aim/grip/grip_surface poses.
 */
class HandMotionEvent : public HandEvent {
public:
  /**
   * @brief Factory for creating HandMotionEvent instances.
   */
  class Factory : public Event::AbstractFactory {
  public:
    ~Factory(void) override;

    /**
     * @brief Create a HandMotionEvent as base Event pointer.
     * @return Newly created HandMotionEvent.
     */
    std::unique_ptr<Event> create(void) const override;

    /**
     * @brief Create a strongly-typed HandMotionEvent.
     * @return Newly created HandMotionEvent.
     */
    std::unique_ptr<HandMotionEvent> createTyped(void) const;
  };

private:
  graphic::PoseF _aim{};         /**< Aim pose of the hand */
  graphic::PoseF _grip{};        /**< Grip pose of the hand */
  graphic::PoseF _gripSurface{}; /**< Grip-surface pose */

public:
  /**
   * @brief Default constructor.
   */
  explicit HandMotionEvent(void);
  ~HandMotionEvent(void) override;

  /**
   * @brief Set aim pose.
   * @param aim Aim pose.
   * @return Reference to this HandMotionEvent.
   */
  HandMotionEvent &setAim(const graphic::PoseF &aim) noexcept;

  /**
   * @brief Get aim pose.
   * @return Aim pose.
   */
  graphic::PoseF getAim(void) const noexcept;

  /**
   * @brief Set grip pose.
   * @param grip Grip pose.
   * @return Reference to this HandMotionEvent.
   */
  HandMotionEvent &setGrip(const graphic::PoseF &grip) noexcept;

  /**
   * @brief Get grip pose.
   * @return Grip pose.
   */
  graphic::PoseF getGrip(void) const noexcept;

  /**
   * @brief Set grip_surface pose.
   * @param gripSurface Grip-surface pose.
   * @return Reference to this HandMotionEvent.
   */
  HandMotionEvent &setGripSurface(const graphic::PoseF &gripSurface) noexcept;

  /**
   * @brief Get grip_surface pose.
   * @return Grip-surface pose.
   */
  graphic::PoseF getGripSurface(void) const noexcept;
};

} // namespace utility::event
