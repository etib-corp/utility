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
#include <string>

#include "utility/event/event.hpp"

namespace utility::event {

/**
 * @brief Text input event for committed UTF-8 text.
 */
class TextInputEvent : public Event {
private:
  std::string _text{};

public:
  /**
   * @brief Factory for creating TextInputEvent instances.
   */
  class Factory : public Event::AbstractFactory {
  public:
    ~Factory(void) override = default;

    /**
     * @brief Create a TextInputEvent as a base Event pointer.
     * @return Newly created TextInputEvent as std::unique_ptr<Event>.
     */
    std::unique_ptr<Event> create(void) const override {
      return std::make_unique<TextInputEvent>();
    }

    /**
     * @brief Create a strongly-typed TextInputEvent.
     * @return Newly created TextInputEvent as std::unique_ptr<TextInputEvent>.
     */
    std::unique_ptr<TextInputEvent> createTyped(void) const {
      return std::make_unique<TextInputEvent>();
    }
  };

  /**
   * @brief Default constructor.
   */
  explicit TextInputEvent(void) = default;

  /**
   * @brief Default destructor.
   */
  ~TextInputEvent(void) override = default;

  /**
   * @brief Set committed UTF-8 text.
   * @param text The committed text.
   */
  void setText(const std::string &text) { _text = text; }

  /**
   * @brief Get committed UTF-8 text.
   * @return The committed text.
   */
  std::string getText(void) const { return _text; }
};

} // namespace utility::event
