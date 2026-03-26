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

#include <bitset>
#include <cstdint>
#include <memory>

#include "utility/event/event.hpp"

#include "utility/math/vector.hpp"

namespace utility::event {

/**
 * @brief Mouse button event.
 *
 * Represents mouse button presses/releases with position and button states.
 */
class MouseButtonEvent : public Event {
public:
  using MousePosition = math::Vector<float, 2>; /**< 2D mouse position type */

  /**
   * @brief Mouse buttons enumeration.
   */
  enum class MouseButton : const std::uint8_t {
    Left = 1,
    Middle = 2,
    Right = 3,
    X1 = 4,
    X2 = 5,
    Last = 6 // Sentinel value to indicate the number of buttons, not an actual
             // button
  };

  using MouseButtonsState =
      std::bitset<sizeof(std::uint8_t) *
                  static_cast<std::size_t>(
                      MouseButton::Last)>; /**< Bitset for button states */

  /**
   * @brief Factory for creating MouseButtonEvent instances.
   */
  class Factory : public Event::AbstractFactory {
  public:
    ~Factory(void) override = default;

    /**
     * @brief Create a MouseButtonEvent as a base Event pointer.
     * @return Newly created MouseButtonEvent as std::unique_ptr<Event>.
     */
    std::unique_ptr<Event> create(void) const override {
      return std::make_unique<MouseButtonEvent>();
    }

    /**
     * @brief Create a strongly-typed MouseButtonEvent.
     * @return Newly created MouseButtonEvent as
     * std::unique_ptr<MouseButtonEvent>.
     */
    std::unique_ptr<MouseButtonEvent> createTyped(void) const {
      return std::make_unique<MouseButtonEvent>();
    }
  };

private:
  MousePosition _position{0, 0}; /**< Current mouse position (x, y) */
  MouseButtonsState
      _buttonStates; /**< Bitset to track the state of mouse buttons */

public:
  /**
   * @brief Default constructor.
   */
  explicit MouseButtonEvent(void) = default;

  /**
   * @brief Default destructor.
   */
  ~MouseButtonEvent(void) override = default;

  /**
   * @brief Set the current mouse position.
   * @param position The mouse position as a 2D vector (x, y).
   * @return Reference to this MouseButtonEvent for method chaining.
   */
  MouseButtonEvent &setPosition(const MousePosition &position) noexcept {
    _position = position;
    return *this;
  }

  /**
   * @brief Get the current mouse position.
   * @return The mouse position as a 2D vector (x, y).
   */
  MousePosition getPosition(void) const noexcept { return _position; }

  /**
   * @brief Set the state of a mouse button.
   * @param button The mouse button to set.
   * @param pressed True if the button is pressed, false if released.
   * @return Reference to this MouseButtonEvent for method chaining.
   */
  MouseButtonEvent &setButtonState(const MouseButton button,
                                   const bool pressed) noexcept {
    _buttonStates.set(static_cast<std::size_t>(button), pressed);
    return *this;
  }

  /**
   * @brief Check if a mouse button is currently pressed.
   * @param button The mouse button to check.
   * @return True if the button is pressed, false otherwise.
   */
  bool isButtonPressed(const MouseButton button) const noexcept {
    return _buttonStates.test(static_cast<std::size_t>(button));
  }

  /**
   * @brief Get the current state of all mouse buttons.
   * @return A bitset representing the state of all mouse buttons.
   */
  const MouseButtonsState &getButtonsState(void) const noexcept {
    return _buttonStates;
  }
};

} // namespace utility::event