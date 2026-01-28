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
    LEFT = 1,
    MIDDLE = 2,
    RIGHT = 3,
    X1 = 4,
    X2 = 5
  };

private:
  MousePosition _position{0, 0};
  std::bitset<sizeof(std::uint8_t) * 8> _buttonStates;

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
   */
  void setPosition(const MousePosition &position) noexcept {
    _position = position;
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
   */
  void setButtonState(const MouseButton button, const bool pressed) noexcept {
    _buttonStates.set(static_cast<std::size_t>(button), pressed);
  }

  /**
   * @brief Check if a mouse button is currently pressed.
   * @param button The mouse button to check.
   * @return True if the button is pressed, false otherwise.
   */
  bool isButtonPressed(const MouseButton button) const noexcept {
    return _buttonStates.test(static_cast<std::size_t>(button));
  }
};

} // namespace utility::event