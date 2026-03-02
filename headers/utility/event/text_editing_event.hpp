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

#include <string>

#include "utility/event/event.hpp"

namespace utility::event {

/**
 * @brief Text editing event for IME/dead-key preedit state.
 */
class TextEditingEvent : public Event {
private:
  std::string _text{};
  int _start{0};
  int _length{0};

public:
  /**
   * @brief Default constructor.
   */
  explicit TextEditingEvent(void) = default;

  /**
   * @brief Default destructor.
   */
  ~TextEditingEvent(void) override = default;

  /**
   * @brief Set preedit UTF-8 text.
   * @param text The preedit text.
   */
  void setText(const std::string &text) { _text = text; }

  /**
   * @brief Get preedit UTF-8 text.
   * @return The preedit text.
   */
  std::string getText(void) const { return _text; }

  /**
   * @brief Set cursor start position in preedit text.
   * @param start Cursor start position.
   */
  void setStart(const int start) noexcept { _start = start; }

  /**
   * @brief Get cursor start position in preedit text.
   * @return Cursor start position.
   */
  int getStart(void) const noexcept { return _start; }

  /**
   * @brief Set selection length in preedit text.
   * @param length Selection length.
   */
  void setLength(const int length) noexcept { _length = length; }

  /**
   * @brief Get selection length in preedit text.
   * @return Selection length.
   */
  int getLength(void) const noexcept { return _length; }
};

} // namespace utility::event
