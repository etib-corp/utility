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

namespace utility::event {

/**
 * @brief Quit event.
 *
 * Represents a request to quit the application.
 */
class QuitEvent : public Event {
public:
  /**
   * @brief Factory for creating QuitEvent instances.
   */
  class Factory : public Event::AbstractFactory {
  public:
    ~Factory(void) override = default;

    /**
     * @brief Create a QuitEvent as a base Event pointer.
     * @return Newly created QuitEvent as std::unique_ptr<Event>.
     */
    std::unique_ptr<Event> create(void) const override {
      return std::make_unique<QuitEvent>();
    }

    /**
     * @brief Create a strongly-typed QuitEvent.
     * @return Newly created QuitEvent as std::unique_ptr<QuitEvent>.
     */
    std::unique_ptr<QuitEvent> createTyped(void) const {
      return std::make_unique<QuitEvent>();
    }
  };

  /**
   * @brief Default constructor.
   */
  explicit QuitEvent(void) = default;

  /**
   * @brief Default destructor.
   */
  ~QuitEvent(void) override = default;
};

} // namespace utility::event