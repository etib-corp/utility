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

#include <concepts>
#include <memory>
#include <type_traits>

#include "utility/event/event.hpp"

#include "utility/graphic/pose.hpp"

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
    Unknown = 0, /**< Unknown hand */
    Left = 0,    /**< Left hand */
    Right = 1,   /**< Right hand */
  };

private:
  HandType _handType{HandType::Unknown}; /**< Type of hand involved in the event */
  graphic::PoseF
      _pose{}; /**< Pose of the hand, including position and orientation */

public:
  /**
   * @brief Default constructor.
   */
  explicit HandEvent(void);

  /**
   * @brief Default destructor.
   */
  virtual ~HandEvent(void) override;

  /**
   * @brief Set the type of hand involved in the event.
   * @param handType The type of hand (left or right).
   * @return Reference to this HandEvent for method chaining.
   */
  HandEvent &setHandType(const HandType handType) noexcept;

  /**
   * @brief Get the type of hand involved in the event.
   * @return The type of hand (left or right).
   */
  HandType getHandType(void) const noexcept;

  /**
   * @brief Set the pose of the hand involved in the event.
   * @param pose The new pose of the hand, including position and orientation.
   * @return Reference to this HandEvent for method chaining.
   */
  HandEvent &setPose(const graphic::PoseF &pose) noexcept;

  /**
   * @brief Get the pose of the hand involved in the event.
   * @return The pose of the hand, including position and orientation.
   */
  graphic::PoseF getPose(void) const noexcept;
};

/**
 * @brief Concept to ensure a type inherits from HandEvent.
 * @tparam Type The type to check.
 */
template <typename Type>
concept InheritFromHandEvent = std::is_base_of_v<HandEvent, Type>;

} // namespace utility::event
