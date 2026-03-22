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

#include "test_text.hpp"

TEST_F(TestText, DefaultConstructorInitializesWithDefaults) {
  utility::graphics::Text text;

  EXPECT_EQ(text.getContent(), "");
  EXPECT_EQ(text.getFontPath(), "");
  EXPECT_EQ(text.getFontSize(), 12.0f);
  EXPECT_EQ(text.getPosition()[0], 0.0f);
  EXPECT_EQ(text.getPosition()[1], 0.0f);
  EXPECT_EQ(text.getPosition()[2], 0.0f);
  EXPECT_EQ(text.getRotation()[0], 0.0f);
  EXPECT_EQ(text.getRotation()[1], 0.0f);
  EXPECT_EQ(text.getRotation()[2], 0.0f);
  EXPECT_EQ(text.getScale()[0], 1.0f);
  EXPECT_EQ(text.getScale()[1], 1.0f);
  EXPECT_EQ(text.getScale()[2], 1.0f);
}

TEST_F(TestText, ParameterizedConstructorSetsValues) {
  utility::graphics::Text text("Hello World", "/path/to/font.ttf", 24.0f);

  EXPECT_EQ(text.getContent(), "Hello World");
  EXPECT_EQ(text.getFontPath(), "/path/to/font.ttf");
  EXPECT_EQ(text.getFontSize(), 24.0f);
}

TEST_F(TestText, SetContentModifiesContent) {
  utility::graphics::Text text;

  text.setContent("Test content");

  EXPECT_EQ(text.getContent(), "Test content");
}

TEST_F(TestText, SetContentSupportsChaining) {
  utility::graphics::Text text;

  auto &result = text.setContent("Chained");

  EXPECT_EQ(&result, &text);
  EXPECT_EQ(text.getContent(), "Chained");
}

TEST_F(TestText, SetFontPathModifiesFontPath) {
  utility::graphics::Text text;

  text.setFontPath("/fonts/Arial.ttf");

  EXPECT_EQ(text.getFontPath(), "/fonts/Arial.ttf");
}

TEST_F(TestText, SetFontPathSupportsChaining) {
  utility::graphics::Text text;

  auto &result = text.setFontPath("/fonts/Courier.ttf");

  EXPECT_EQ(&result, &text);
  EXPECT_EQ(text.getFontPath(), "/fonts/Courier.ttf");
}

TEST_F(TestText, SetFontSizeModifiesFontSize) {
  utility::graphics::Text text;

  text.setFontSize(18.5f);

  EXPECT_EQ(text.getFontSize(), 18.5f);
}

TEST_F(TestText, SetFontSizeSupportsChaining) {
  utility::graphics::Text text;

  auto &result = text.setFontSize(32.0f);

  EXPECT_EQ(&result, &text);
  EXPECT_EQ(text.getFontSize(), 32.0f);
}

TEST_F(TestText, MethodChainingWorks) {
  utility::graphics::Text text;
  utility::math::Vector<std::float_t, 3> position{1.0f, 2.0f, 3.0f};
  utility::math::Vector<std::float_t, 3> rotation{10.0f, 20.0f, 30.0f};
  utility::math::Vector<std::float_t, 3> scale{2.0f, 2.0f, 2.0f};

  text.setContent("Chained text")
      .setFontPath("/fonts/custom.ttf")
      .setFontSize(16.0f)
      .setPosition(position)
      .setRotation(rotation)
      .setScale(scale);

  EXPECT_EQ(text.getContent(), "Chained text");
  EXPECT_EQ(text.getFontPath(), "/fonts/custom.ttf");
  EXPECT_EQ(text.getFontSize(), 16.0f);
  EXPECT_EQ(text.getPosition()[0], 1.0f);
  EXPECT_EQ(text.getPosition()[1], 2.0f);
  EXPECT_EQ(text.getPosition()[2], 3.0f);
  EXPECT_EQ(text.getRotation()[0], 10.0f);
  EXPECT_EQ(text.getRotation()[1], 20.0f);
  EXPECT_EQ(text.getRotation()[2], 30.0f);
  EXPECT_EQ(text.getScale()[0], 2.0f);
  EXPECT_EQ(text.getScale()[1], 2.0f);
  EXPECT_EQ(text.getScale()[2], 2.0f);
}

TEST_F(TestText, SetPositionSupportsChaining) {
  utility::graphics::Text text;
  utility::math::Vector<std::float_t, 3> position{4.0f, 5.0f, 6.0f};

  auto &result = text.setPosition(position);

  EXPECT_EQ(&result, &text);
  EXPECT_EQ(text.getPosition()[0], 4.0f);
  EXPECT_EQ(text.getPosition()[1], 5.0f);
  EXPECT_EQ(text.getPosition()[2], 6.0f);
}

TEST_F(TestText, SetRotationSupportsChaining) {
  utility::graphics::Text text;
  utility::math::Vector<std::float_t, 3> rotation{7.0f, 8.0f, 9.0f};

  auto &result = text.setRotation(rotation);

  EXPECT_EQ(&result, &text);
  EXPECT_EQ(text.getRotation()[0], 7.0f);
  EXPECT_EQ(text.getRotation()[1], 8.0f);
  EXPECT_EQ(text.getRotation()[2], 9.0f);
}

TEST_F(TestText, SetScaleSupportsChaining) {
  utility::graphics::Text text;
  utility::math::Vector<std::float_t, 3> scale{1.5f, 1.0f, 0.5f};

  auto &result = text.setScale(scale);

  EXPECT_EQ(&result, &text);
  EXPECT_EQ(text.getScale()[0], 1.5f);
  EXPECT_EQ(text.getScale()[1], 1.0f);
  EXPECT_EQ(text.getScale()[2], 0.5f);
}

TEST_F(TestText, MultipleSetOperationsWork) {
  utility::graphics::Text text("Initial", "/path/font.ttf", 14.0f);

  text.setContent("Updated");
  text.setFontPath("/new/path/font.ttf");
  text.setFontSize(28.0f);

  EXPECT_EQ(text.getContent(), "Updated");
  EXPECT_EQ(text.getFontPath(), "/new/path/font.ttf");
  EXPECT_EQ(text.getFontSize(), 28.0f);
}

TEST_F(TestText, EmptyStringsAreValid) {
  utility::graphics::Text text("", "", 10.0f);

  EXPECT_EQ(text.getContent(), "");
  EXPECT_EQ(text.getFontPath(), "");
  EXPECT_EQ(text.getFontSize(), 10.0f);
}

TEST_F(TestText, LargeValuesAreHandled) {
  utility::graphics::Text text;

  text.setFontSize(999.0f);

  EXPECT_EQ(text.getFontSize(), 999.0f);
}

TEST_F(TestText, SmallFloatValuesAreHandled) {
  utility::graphics::Text text;

  text.setFontSize(0.5f);

  EXPECT_EQ(text.getFontSize(), 0.5f);
}
