#include "graphic/test_color.hpp"

#include "utility/graphic/color.hpp"

using namespace utility::graphic;
using namespace tests::utility::graphic;

TEST_F(TestColor, DefaultConstructor)
{
	Color32Bit color;
	EXPECT_EQ(color.getRed(), 0);
	EXPECT_EQ(color.getGreen(), 0);
	EXPECT_EQ(color.getBlue(), 0);
	EXPECT_EQ(color.getAlpha(), 255);
}

TEST_F(TestColor, ClampFloatingPointComponents)
{
	ColorFloat color(2.0f, -1.0f, 0.5f, 2.0f);
	EXPECT_FLOAT_EQ(color.getRed(), 1.0f);
	EXPECT_FLOAT_EQ(color.getGreen(), 0.0f);
	EXPECT_FLOAT_EQ(color.getBlue(), 0.5f);
	EXPECT_FLOAT_EQ(color.getAlpha(), 1.0f);
}

TEST_F(TestColor, GrayscaleAndInverted)
{
	Color32Bit color(100, 150, 200, 255);
	Color32Bit gray		= color.grayscale();
	Color32Bit inverted = color.inverted();

	EXPECT_EQ(gray.getRed(), gray.getGreen());
	EXPECT_EQ(gray.getGreen(), gray.getBlue());
	EXPECT_EQ(inverted.getRed(), 155);
	EXPECT_EQ(inverted.getGreen(), 105);
	EXPECT_EQ(inverted.getBlue(), 55);
	EXPECT_EQ(inverted.getAlpha(), 255);
}

TEST_F(TestColor, AlphaHelpers)
{
	Color32Bit color(10, 20, 30, 255);
	Color32Bit transparent = color.withAlpha(0);

	EXPECT_TRUE(color.isOpaque());
	EXPECT_FALSE(color.isTransparent());
	EXPECT_TRUE(transparent.isTransparent());
	EXPECT_NEAR(transparent.alpha01(), 0.0, 1e-9);
	EXPECT_NEAR(color.alpha01(), 1.0, 1e-9);
}

TEST_F(TestColor, IntegerAdditionSaturates)
{
	Color32Bit color(200, 200, 50, 255);
	Color32Bit other(100, 100, 50, 255);
	Color32Bit result = color + other;
	EXPECT_EQ(result.getRed(), 255);
	EXPECT_EQ(result.getGreen(), 255);
	EXPECT_EQ(result.getBlue(), 100);
}

TEST_F(TestColor, IntegerSubtractionSaturates)
{
	Color32Bit color(50, 50, 50, 255);
	Color32Bit other(200, 100, 10, 255);
	Color32Bit result = color - other;
	EXPECT_EQ(result.getRed(), 0);
	EXPECT_EQ(result.getGreen(), 0);
	EXPECT_EQ(result.getBlue(), 40);
}

TEST_F(TestColor, IntegerScalarMultiplicationSaturates)
{
	Color32Bit color(200, 200, 10, 255);
	Color32Bit result = color * 3;
	EXPECT_EQ(result.getRed(), 255);
	EXPECT_EQ(result.getGreen(), 255);
	EXPECT_EQ(result.getBlue(), 30);
}
