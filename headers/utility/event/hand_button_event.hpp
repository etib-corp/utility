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
 * @brief Hand button event.
 */
class HandButtonEvent : public HandEvent {
public:
  /**
   * @brief Hand button identifier.
   */
  enum class Button {
    Unknown = 0, /**< Unknown button */
    X = 0,      /**< X button */
    Y = 1,      /**< Y button */
    A = 2,      /**< A button */
    B = 3,      /**< B button */
    Menu = 4,   /**< Menu button */
    System = 5, /**< System button */
  };

  /**
   * @brief Check whether a button is valid for a given hand path.
   * @param handType Hand side.
   * @param button Button identifier.
   * @return True when the button is valid for that hand.
   */
  static bool isButtonValidForHand(const HandType handType,
                                   const Button button) noexcept;

  /**
   * @brief Factory for creating HandButtonEvent instances.
   */
  class Factory : public Event::AbstractFactory {
  public:
    ~Factory(void) override;

    /**
     * @brief Create a HandButtonEvent as base Event pointer.
     * @return Newly created HandButtonEvent.
     */
    std::unique_ptr<Event> create(void) const override;

    /**
     * @brief Create a strongly-typed HandButtonEvent.
     * @return Newly created HandButtonEvent.
     */
    std::unique_ptr<HandButtonEvent> createTyped(void) const;
  };

private:
  /** @brief Selected hand button. */
  Button _button{Button::Unknown};

  /** @brief True when the button is touched. */
  bool _isTouched{false};

  /** @brief True when the button is clicked. */
  bool _isClicked{false};

public:
  /**
   * @brief Default constructor.
   */
  explicit HandButtonEvent(void);

  /**
   * @brief Default destructor.
   */
  ~HandButtonEvent(void) override;

  /**
   * @brief Set button value.
   * @param button Hand button.
   * @return Reference to this HandButtonEvent.
   */
  HandButtonEvent &setButton(const Button button) noexcept;

  /**
   * @brief Get button value.
   * @return Current button.
   */
  Button getButton(void) const noexcept;

  /**
   * @brief Check whether current hand/button combination is valid.
   * @return True when current button is valid for current hand type.
   */
  bool isValidForCurrentHand(void) const noexcept;

  /**
   * @brief Set touched state.
   * @param touched True if touched.
   * @return Reference to this HandButtonEvent.
   */
  HandButtonEvent &setTouched(const bool touched) noexcept;

  /**
   * @brief Get touched state.
   * @return True if touched.
   */
  bool isTouched(void) const noexcept;

  /**
   * @brief Set clicked state.
   * @param clicked True if clicked.
   * @return Reference to this HandButtonEvent.
   */
  HandButtonEvent &setClicked(const bool clicked) noexcept;

  /**
   * @brief Get clicked state.
   * @return True if clicked.
   */
  bool isClicked(void) const noexcept;
};

} // namespace utility::event