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
            utility::event::KeyboardEvent::ScanCode::Unknown);
  EXPECT_EQ(event.getKeycode(),
            utility::event::KeyboardEvent::KeyCode::Unknown);
  EXPECT_TRUE(event.getIsDownEvent());
  EXPECT_FALSE(event.getIsRepeatEvent());
}

TEST_F(TestKeyboardEvent, KeyCodeAndFlagsCanBeUpdated) {
  utility::event::KeyboardEvent event;

  event.setKeycode(utility::event::KeyboardEvent::KeyCode::Return);
  event.setIsDownEvent(false);
  event.setIsRepeatEvent(true);

  EXPECT_EQ(event.getKeycode(), utility::event::KeyboardEvent::KeyCode::Return);
  EXPECT_FALSE(event.getIsDownEvent());
  EXPECT_TRUE(event.getIsRepeatEvent());
}

TEST_F(TestKeyboardEvent, ModifierMasksSupportGroupedAndHighBitValues) {
  using KeyModifiers = utility::event::KeyboardEvent::KeyModifiers;

  utility::event::KeyboardEvent event;

  EXPECT_TRUE(event.isModifierSet(KeyModifiers::None));

  event.setModifiers(KeyModifiers::LeftShift);
  EXPECT_TRUE(event.isModifierSet(KeyModifiers::LeftShift));
  EXPECT_TRUE(event.isModifierSet(KeyModifiers::Shift));
  EXPECT_FALSE(event.isModifierSet(KeyModifiers::RightShift));
  EXPECT_FALSE(event.isModifierSet(KeyModifiers::None));

  event.setModifiers(KeyModifiers::RightAlt);
  EXPECT_TRUE(event.isModifierSet(KeyModifiers::RightAlt));
  EXPECT_TRUE(event.isModifierSet(KeyModifiers::Alt));
  EXPECT_FALSE(event.isModifierSet(KeyModifiers::LeftAlt));

  event.setModifiers(KeyModifiers::None);
  EXPECT_TRUE(event.isModifierSet(KeyModifiers::None));
  EXPECT_FALSE(event.isModifierSet(KeyModifiers::Alt));
}

TEST_F(TestKeyboardEvent, FactoryCreatesKeyboardEventThroughAbstractInterface) {
  utility::event::KeyboardEvent::Factory factory;
  const auto event = factory.create();

  EXPECT_NE(event, nullptr);
  EXPECT_NE(dynamic_cast<utility::event::KeyboardEvent *>(event.get()),
            nullptr);
}
