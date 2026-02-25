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

#include "math/test_color.hpp"

TEST_F(TestColor, ConstructorAndSettersClampValues) {
	utility::math::Color<float> color(2.0F, -1.0F, 0.5F, 4.0F);

	EXPECT_FLOAT_EQ(color.red(), 1.0F);
	EXPECT_FLOAT_EQ(color.green(), 0.0F);
	EXPECT_FLOAT_EQ(color.blue(), 0.5F);
	EXPECT_FLOAT_EQ(color.alpha(), 1.0F);

	color.setRGBA(-0.5F, 0.25F, 2.0F, -2.0F);
	EXPECT_FLOAT_EQ(color.red(), 0.0F);
	EXPECT_FLOAT_EQ(color.green(), 0.25F);
	EXPECT_FLOAT_EQ(color.blue(), 1.0F);
	EXPECT_FLOAT_EQ(color.alpha(), 0.0F);
}

TEST_F(TestColor, ArithmeticAndTransformationsWork) {
	utility::math::Color<float> base(0.2F, 0.4F, 0.6F, 1.0F);
	utility::math::Color<float> delta(0.3F, 0.3F, 0.3F, 1.0F);

	const auto added = base + delta;
	const auto subtracted = base - delta;
	const auto grayscale = base.grayscale();
	const auto inverted = base.inverted();

	EXPECT_FLOAT_EQ(added.red(), 0.5F);
	EXPECT_FLOAT_EQ(added.green(), 0.7F);
	EXPECT_FLOAT_EQ(added.blue(), 0.9F);

	EXPECT_FLOAT_EQ(subtracted.red(), 0.0F);
	EXPECT_FLOAT_EQ(subtracted.green(), 0.1F);
	EXPECT_FLOAT_EQ(subtracted.blue(), 0.3F);

	EXPECT_NEAR(grayscale.red(), grayscale.green(), 1e-5F);
	EXPECT_NEAR(grayscale.green(), grayscale.blue(), 1e-5F);
	EXPECT_FLOAT_EQ(inverted.red(), 0.8F);
}

TEST_F(TestColor, LerpBlendAndNamedColorsWork) {
	const auto red = utility::math::Color<float>::Red();
	const auto blue = utility::math::Color<float>::Blue();
	const auto middle = red.lerp(blue, 0.5F);

	EXPECT_NEAR(middle.red(), 0.5F, 1e-5F);
	EXPECT_NEAR(middle.blue(), 0.5F, 1e-5F);

	utility::math::Color<float> foreground(1.0F, 0.0F, 0.0F, 0.5F);
	utility::math::Color<float> background(0.0F, 0.0F, 1.0F, 1.0F);
	const auto blended = foreground.blendOver(background);

	EXPECT_NEAR(blended.red(), 0.5F, 1e-5F);
	EXPECT_NEAR(blended.blue(), 0.5F, 1e-5F);

	const auto white = utility::math::Color<std::uint8_t>::White();
	EXPECT_EQ(white.red(), 255);
	EXPECT_EQ(white.green(), 255);
	EXPECT_EQ(white.blue(), 255);
}