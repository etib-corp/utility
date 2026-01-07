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

#include "test_color.hpp"
#include "color.hpp"
#include <gtest/gtest.h>

namespace utility {

// Test default constructor
TEST(ColorTest, DefaultConstructor) {
  Color<float> color;
  EXPECT_EQ(color.red(), 0.0f);
  EXPECT_EQ(color.green(), 0.0f);
  EXPECT_EQ(color.blue(), 0.0f);
  EXPECT_EQ(color.alpha(), 1.0f);
}

// Test RGB constructor
TEST(ColorTest, RGBConstructor) {
  Color<float> color(1.0f, 0.5f, 0.0f);
  EXPECT_EQ(color.red(), 1.0f);
  EXPECT_EQ(color.green(), 0.5f);
  EXPECT_EQ(color.blue(), 0.0f);
  EXPECT_EQ(color.alpha(), 1.0f);
}

// Test RGBA constructor
TEST(ColorTest, RGBAConstructor) {
  Color<float> color(0.2f, 0.4f, 0.6f, 0.8f);
  EXPECT_EQ(color.red(), 0.2f);
  EXPECT_EQ(color.green(), 0.4f);
  EXPECT_EQ(color.blue(), 0.6f);
  EXPECT_EQ(color.alpha(), 0.8f);
}

// Test clamping
TEST(ColorTest, Clamping) {
  Color<float> color(1.5f, -0.5f, 0.5f, 2.0f);
  EXPECT_EQ(color.red(), 1.0f);
  EXPECT_EQ(color.green(), 0.0f);
  EXPECT_EQ(color.blue(), 0.5f);
  EXPECT_EQ(color.alpha(), 1.0f);
}

// Test integer type
TEST(ColorTest, IntegerType) {
  Color<uint8_t> color(255, 128, 0, 200);
  EXPECT_EQ(color.red(), 255);
  EXPECT_EQ(color.green(), 128);
  EXPECT_EQ(color.blue(), 0);
  EXPECT_EQ(color.alpha(), 200);
}

// Test copy constructor
TEST(ColorTest, CopyConstructor) {
  Color<float> original(0.5f, 0.6f, 0.7f, 0.8f);
  Color<float> copy(original);
  EXPECT_EQ(copy.red(), 0.5f);
  EXPECT_EQ(copy.green(), 0.6f);
  EXPECT_EQ(copy.blue(), 0.7f);
  EXPECT_EQ(copy.alpha(), 0.8f);
}

// Test setters
TEST(ColorTest, Setters) {
  Color<float> color;
  color.setRed(0.3f);
  color.setGreen(0.4f);
  color.setBlue(0.5f);
  color.setAlpha(0.6f);
  EXPECT_EQ(color.red(), 0.3f);
  EXPECT_EQ(color.green(), 0.4f);
  EXPECT_EQ(color.blue(), 0.5f);
  EXPECT_EQ(color.alpha(), 0.6f);
}

// Test setRGBA
TEST(ColorTest, SetRGBA) {
  Color<float> color;
  color.setRGBA(0.1f, 0.2f, 0.3f, 0.4f);
  EXPECT_EQ(color.red(), 0.1f);
  EXPECT_EQ(color.green(), 0.2f);
  EXPECT_EQ(color.blue(), 0.3f);
  EXPECT_EQ(color.alpha(), 0.4f);
}

// Test equality
TEST(ColorTest, Equality) {
  Color<float> color1(0.5f, 0.5f, 0.5f, 1.0f);
  Color<float> color2(0.5f, 0.5f, 0.5f, 1.0f);
  Color<float> color3(0.6f, 0.5f, 0.5f, 1.0f);
  EXPECT_TRUE(color1 == color2);
  EXPECT_FALSE(color1 == color3);
  EXPECT_TRUE(color1 != color3);
}

// Test color addition
TEST(ColorTest, Addition) {
  Color<float> color1(0.3f, 0.4f, 0.5f);
  Color<float> color2(0.2f, 0.3f, 0.1f);
  Color<float> result = color1 + color2;
  EXPECT_NEAR(result.red(), 0.5f, 0.0001f);
  EXPECT_NEAR(result.green(), 0.7f, 0.0001f);
  EXPECT_NEAR(result.blue(), 0.6f, 0.0001f);
}

// Test color subtraction
TEST(ColorTest, Subtraction) {
  Color<float> color1(0.8f, 0.6f, 0.4f);
  Color<float> color2(0.3f, 0.2f, 0.1f);
  Color<float> result = color1 - color2;
  EXPECT_NEAR(result.red(), 0.5f, 0.0001f);
  EXPECT_NEAR(result.green(), 0.4f, 0.0001f);
  EXPECT_NEAR(result.blue(), 0.3f, 0.0001f);
}

// Test scalar multiplication
TEST(ColorTest, ScalarMultiplication) {
  Color<float> color(0.4f, 0.6f, 0.8f);
  Color<float> result = color * 0.5f;
  EXPECT_EQ(result.red(), 0.2f);
  EXPECT_EQ(result.green(), 0.3f);
  EXPECT_EQ(result.blue(), 0.4f);
}

// Test grayscale conversion
TEST(ColorTest, Grayscale) {
  Color<float> color(1.0f, 0.0f, 0.0f);
  Color<float> gray = color.grayscale();
  // Luminance of red is 0.299
  EXPECT_NEAR(gray.red(), 0.299f, 0.001f);
  EXPECT_NEAR(gray.green(), 0.299f, 0.001f);
  EXPECT_NEAR(gray.blue(), 0.299f, 0.001f);
}

// Test color inversion
TEST(ColorTest, Inverted) {
  Color<float> color(0.3f, 0.6f, 0.9f, 0.5f);
  Color<float> inverted = color.inverted();
  EXPECT_NEAR(inverted.red(), 0.7f, 0.0001f);
  EXPECT_NEAR(inverted.green(), 0.4f, 0.0001f);
  EXPECT_NEAR(inverted.blue(), 0.1f, 0.0001f);
  EXPECT_EQ(inverted.alpha(), 0.5f); // Alpha unchanged
}

// Test linear interpolation
TEST(ColorTest, Lerp) {
  Color<float> color1(0.0f, 0.0f, 0.0f);
  Color<float> color2(1.0f, 1.0f, 1.0f);
  Color<float> mid = color1.lerp(color2, 0.5f);
  EXPECT_EQ(mid.red(), 0.5f);
  EXPECT_EQ(mid.green(), 0.5f);
  EXPECT_EQ(mid.blue(), 0.5f);
}

// Test lighter
TEST(ColorTest, Lighter) {
  Color<float> color(0.5f, 0.5f, 0.5f);
  Color<float> lighter = color.lighter(0.5f);
  EXPECT_GT(lighter.red(), color.red());
  EXPECT_GT(lighter.green(), color.green());
  EXPECT_GT(lighter.blue(), color.blue());
}

// Test darker
TEST(ColorTest, Darker) {
  Color<float> color(0.5f, 0.5f, 0.5f);
  Color<float> darker = color.darker(0.5f);
  EXPECT_LT(darker.red(), color.red());
  EXPECT_LT(darker.green(), color.green());
  EXPECT_LT(darker.blue(), color.blue());
}

// Test color constants (floating-point)
TEST(ColorTest, ConstantsFloat) {
  auto black = Color<float>::Black();
  EXPECT_EQ(black.red(), 0.0f);
  EXPECT_EQ(black.green(), 0.0f);
  EXPECT_EQ(black.blue(), 0.0f);

  auto white = Color<float>::White();
  EXPECT_EQ(white.red(), 1.0f);
  EXPECT_EQ(white.green(), 1.0f);
  EXPECT_EQ(white.blue(), 1.0f);

  auto red = Color<float>::Red();
  EXPECT_EQ(red.red(), 1.0f);
  EXPECT_EQ(red.green(), 0.0f);
  EXPECT_EQ(red.blue(), 0.0f);

  auto green = Color<float>::Green();
  EXPECT_EQ(green.red(), 0.0f);
  EXPECT_EQ(green.green(), 1.0f);
  EXPECT_EQ(green.blue(), 0.0f);

  auto blue = Color<float>::Blue();
  EXPECT_EQ(blue.red(), 0.0f);
  EXPECT_EQ(blue.green(), 0.0f);
  EXPECT_EQ(blue.blue(), 1.0f);
}

// Test color constants (integral)
TEST(ColorTest, ConstantsInt) {
  auto black = Color<uint8_t>::Black();
  EXPECT_EQ(black.red(), 0);
  EXPECT_EQ(black.green(), 0);
  EXPECT_EQ(black.blue(), 0);

  auto white = Color<uint8_t>::White();
  EXPECT_EQ(white.red(), 255);
  EXPECT_EQ(white.green(), 255);
  EXPECT_EQ(white.blue(), 255);

  auto red = Color<uint8_t>::Red();
  EXPECT_EQ(red.red(), 255);
  EXPECT_EQ(red.green(), 0);
  EXPECT_EQ(red.blue(), 0);
}

// Test alpha blending
TEST(ColorTest, BlendOver) {
  Color<float> foreground(1.0f, 0.0f, 0.0f, 0.5f); // Semi-transparent red
  Color<float> background(0.0f, 0.0f, 1.0f, 1.0f); // Opaque blue
  Color<float> blended = foreground.blendOver(background);

  // Result should be purple-ish
  EXPECT_GT(blended.red(), 0.0f);
  EXPECT_GT(blended.blue(), 0.0f);
  EXPECT_EQ(blended.green(), 0.0f);
}

void TestColor::runTests() {
  // Tests are registered with Google Test framework
}

} // namespace utility
