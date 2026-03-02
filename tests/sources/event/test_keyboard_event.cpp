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

#include "event/test_keyboard_event.hpp"

TEST_F(TestKeyboardEvent, DefaultStateIsConsistent) {
  utility::event::KeyboardEvent event;

  EXPECT_EQ(event.getScancode(),
            utility::event::KeyboardEvent::ScanCode::UNKNOWN);
  EXPECT_EQ(event.getKeycode(),
            utility::event::KeyboardEvent::KeyCode::UNKNOWN);
  EXPECT_TRUE(event.getIsDownEvent());
  EXPECT_FALSE(event.getIsRepeatEvent());
}

TEST_F(TestKeyboardEvent, KeyCodeAndFlagsCanBeUpdated) {
  utility::event::KeyboardEvent event;

  event.setKeycode(utility::event::KeyboardEvent::KeyCode::RETURN);
  event.setIsDownEvent(false);
  event.setIsRepeatEvent(true);

  EXPECT_EQ(event.getKeycode(), utility::event::KeyboardEvent::KeyCode::RETURN);
  EXPECT_FALSE(event.getIsDownEvent());
  EXPECT_TRUE(event.getIsRepeatEvent());
}

TEST_F(TestKeyboardEvent, ModifierMasksSupportGroupedAndHighBitValues) {
  using KeyModifiers = utility::event::KeyboardEvent::KeyModifiers;

  utility::event::KeyboardEvent event;

  EXPECT_TRUE(event.isModifierSet(KeyModifiers::NONE));

  event.setModifiers(KeyModifiers::LSHIFT);
  EXPECT_TRUE(event.isModifierSet(KeyModifiers::LSHIFT));
  EXPECT_TRUE(event.isModifierSet(KeyModifiers::SHIFT));
  EXPECT_FALSE(event.isModifierSet(KeyModifiers::RSHIFT));
  EXPECT_FALSE(event.isModifierSet(KeyModifiers::NONE));

  event.setModifiers(KeyModifiers::RALT);
  EXPECT_TRUE(event.isModifierSet(KeyModifiers::RALT));
  EXPECT_TRUE(event.isModifierSet(KeyModifiers::ALT));
  EXPECT_FALSE(event.isModifierSet(KeyModifiers::LALT));

  event.setModifiers(KeyModifiers::MODE);
  EXPECT_TRUE(event.isModifierSet(KeyModifiers::MODE));
  EXPECT_FALSE(event.isModifierSet(KeyModifiers::ALT));
}
