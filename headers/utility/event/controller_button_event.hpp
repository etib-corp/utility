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
 * @brief Controller button event.
 */
class ControllerButtonEvent : public ControllerEvent {
public:
  /**
   * @brief Controller button identifier.
   */
  enum class Button {
    X,      /**< X button */
    Y,      /**< Y button */
    A,      /**< A button */
    B,      /**< B button */
    Menu,   /**< Menu button */
    System, /**< System button */
    None    /**< No button */
  };

  /**
   * @brief Factory for creating ControllerButtonEvent instances.
   */
  class Factory : public Event::AbstractFactory {
  public:
    ~Factory(void) override = default;

    /**
     * @brief Create a ControllerButtonEvent as base Event pointer.
     * @return Newly created ControllerButtonEvent.
     */
    std::unique_ptr<Event> create(void) const override {
      return std::make_unique<ControllerButtonEvent>();
    }

    /**
     * @brief Create a strongly-typed ControllerButtonEvent.
     * @return Newly created ControllerButtonEvent.
     */
    std::unique_ptr<ControllerButtonEvent> createTyped(void) const {
      return std::make_unique<ControllerButtonEvent>();
    }
  };

private:
  /** @brief Selected controller button. */
  Button _button{Button::None};

  /** @brief True when the button is touched. */
  bool _isTouched{false};

  /** @brief True when the button is clicked. */
  bool _isClicked{false};

public:
  /**
   * @brief Default constructor.
   */
  explicit ControllerButtonEvent(void) = default;

  /**
   * @brief Default destructor.
   */
  ~ControllerButtonEvent(void) override = default;

  /**
   * @brief Set button value.
   * @param button Controller button.
   * @return Reference to this ControllerButtonEvent.
   */
  ControllerButtonEvent &setButton(const Button button) noexcept {
    _button = button;
    return *this;
  }

  /**
   * @brief Get button value.
   * @return Current button.
   */
  Button getButton(void) const noexcept { return _button; }

  /**
   * @brief Set touched state.
   * @param touched True if touched.
   * @return Reference to this ControllerButtonEvent.
   */
  ControllerButtonEvent &setTouched(const bool touched) noexcept {
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
   * @return Reference to this ControllerButtonEvent.
   */
  ControllerButtonEvent &setClicked(const bool clicked) noexcept {
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
