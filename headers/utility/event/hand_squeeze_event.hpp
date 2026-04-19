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

namespace utility::event {

/**
 * @brief Hand squeeze event.
 *
 * Models .../input/squeeze/value and optional related squeeze components.
 */
class HandSqueezeEvent : public HandEvent {
public:
  /**
   * @brief Factory for creating HandSqueezeEvent instances.
   */
  class Factory : public Event::AbstractFactory {
  public:
    ~Factory(void) override;

    /**
     * @brief Create a HandSqueezeEvent as base Event pointer.
     * @return Newly created HandSqueezeEvent.
     */
    std::unique_ptr<Event> create(void) const override;

    /**
     * @brief Create a strongly-typed HandSqueezeEvent.
     * @return Newly created HandSqueezeEvent.
     */
    std::unique_ptr<HandSqueezeEvent> createTyped(void) const;
  };

private:
  /** @brief Squeeze value in range [0, 1]. */
  float _value{0.0F};

  /** @brief Optional force value in range [0, 1]. */
  float _force{0.0F};

  /** @brief True when squeeze source is touched. */
  bool _isTouched{false};

  /** @brief True when squeeze source is clicked. */
  bool _isClicked{false};

public:
  /**
   * @brief Default constructor.
   */
  explicit HandSqueezeEvent(void);

  /**
   * @brief Default destructor.
   */
  ~HandSqueezeEvent(void) override;

  /**
   * @brief Set squeeze value.
   * @param value Squeeze value.
   * @return Reference to this HandSqueezeEvent.
   */
  HandSqueezeEvent &setValue(const float value) noexcept;

  /**
   * @brief Get squeeze value.
   * @return Squeeze value in [0, 1].
   */
  float getValue(void) const noexcept;

  /**
   * @brief Set squeeze force value.
   * @param force Force value.
   * @return Reference to this HandSqueezeEvent.
   */
  HandSqueezeEvent &setForce(const float force) noexcept;

  /**
   * @brief Get squeeze force value.
   * @return Force value in [0, 1].
   */
  float getForce(void) const noexcept;

  /**
   * @brief Set touched state.
   * @param touched True if touched.
   * @return Reference to this HandSqueezeEvent.
   */
  HandSqueezeEvent &setTouched(const bool touched) noexcept;

  /**
   * @brief Get touched state.
   * @return True if touched.
   */
  bool isTouched(void) const noexcept;

  /**
   * @brief Set clicked state.
   * @param clicked True if clicked.
   * @return Reference to this HandSqueezeEvent.
   */
  HandSqueezeEvent &setClicked(const bool clicked) noexcept;

  /**
   * @brief Get clicked state.
   * @return True if clicked.
   */
  bool isClicked(void) const noexcept;
};

} // namespace utility::event
