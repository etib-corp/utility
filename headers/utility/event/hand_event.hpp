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

#include "utility/event/event.hpp"

#include "utility/graphics/position.hpp"
#include "utility/graphics/rotation.hpp"

namespace utility::event {

/**
 * @brief Abstract base class for hand events.
 *
 * Represents events related to hand tracking, such as gesture recognition or
 * hand pose updates. Specific hand event types should derive from this class.
 */
class HandEvent : public Event {
public:
  /**
   * @brief Hand types for hand events.
   * Defines the type of hand involved in the event (e.g., left or right).
   */
  enum class HandType {
    Left, /**< Left hand */
    Right /**< Right hand */
  };

private:
  HandType _handType; /**< Type of hand involved in the event */
  utility::graphics::Position _position; /**< Position of the hand */
  utility::graphics::Rotation _rotation; /**< Rotation of the hand */

public:
  /**
   * @brief Default constructor.
   */
  explicit HandEvent(void) = default;

  /**
   * @brief Default destructor.
   */
  virtual ~HandEvent(void) override = default;

  /**
   * @brief Set the type of hand involved in the event.
   * @param handType The type of hand (left or right).
   * @return Reference to this HandEvent for method chaining.
   */
  HandEvent &setHandType(const HandType handType) noexcept {
    _handType = handType;
    return *this;
  }

  /**
   * @brief Get the type of hand involved in the event.
   * @return The type of hand (left or right).
   */
  HandType getHandType(void) const noexcept { return _handType; }

  /**
   * @brief Set the position of the hand.
   * @param position The new position of the hand.
   * @return Reference to this HandEvent for method chaining.
   */
  HandEvent &setPosition(const utility::graphics::Position &position) noexcept {
    _position = position;
    return *this;
  }

  /**
   * @brief Get the position of the hand.
   * @return The position of the hand.
   */
  utility::graphics::Position getPosition(void) const noexcept {
    return _position;
  }

  /**
   * @brief Set the rotation of the hand.
   * @param rotation The new rotation of the hand.
   * @return Reference to this HandEvent for method chaining.
   */
  HandEvent &setRotation(const utility::graphics::Rotation &rotation) noexcept {
    _rotation = rotation;
    return *this;
  }

  /**
   * @brief Get the rotation of the hand.
   * @return The rotation of the hand.
   */
  utility::graphics::Rotation getRotation(void) const noexcept {
    return _rotation;
  }
};

} // namespace utility::event
