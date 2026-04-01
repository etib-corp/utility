#include "graphic/test_color.hpp"

#include "utility/graphic/color.hpp"

using namespace utility::graphic;
using namespace tests::utility::graphic;

TEST_F(TestColor, DefaultConstructor) {
  Color32Bit color;
  EXPECT_EQ(color.getRed(), 0);
  EXPECT_EQ(color.getGreen(), 0);
  EXPECT_EQ(color.getBlue(), 0);
  EXPECT_EQ(color.getAlpha(), 255);
}

TEST_F(TestColor, ClampFloatingPointComponents) {
  ColorFloat color(2.0f, -1.0f, 0.5f, 2.0f);
  EXPECT_FLOAT_EQ(color.getRed(), 1.0f);
  EXPECT_FLOAT_EQ(color.getGreen(), 0.0f);
  EXPECT_FLOAT_EQ(color.getBlue(), 0.5f);
  EXPECT_FLOAT_EQ(color.getAlpha(), 1.0f);
}

TEST_F(TestColor, GrayscaleAndInverted) {
  Color32Bit color(100, 150, 200, 255);
  Color32Bit gray = color.grayscale();
  Color32Bit inverted = color.inverted();

  EXPECT_EQ(gray.getRed(), gray.getGreen());
  EXPECT_EQ(gray.getGreen(), gray.getBlue());
  EXPECT_EQ(inverted.getRed(), 155);
  EXPECT_EQ(inverted.getGreen(), 105);
  EXPECT_EQ(inverted.getBlue(), 55);
  EXPECT_EQ(inverted.getAlpha(), 255);
}

TEST_F(TestColor, AlphaHelpers) {
  Color32Bit color(10, 20, 30, 255);
  Color32Bit transparent = color.withAlpha(0);

  EXPECT_TRUE(color.isOpaque());
  EXPECT_FALSE(color.isTransparent());
  EXPECT_TRUE(transparent.isTransparent());
  EXPECT_NEAR(transparent.alpha01(), 0.0, 1e-9);
  EXPECT_NEAR(color.alpha01(), 1.0, 1e-9);
}
