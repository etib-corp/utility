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

#include "math/test_rectangle.hpp"

TEST_F(TestRectangle, ConstructionValidationAndBasicProperties) {
	EXPECT_THROW((utility::math::Rectangle<float>(0.0F, 0.0F, -1.0F, 1.0F)),
							 std::invalid_argument);

	utility::math::Rectangle<float> rectangle(1.0F, 2.0F, 3.0F, 4.0F);
	EXPECT_FLOAT_EQ(rectangle.x(), 1.0F);
	EXPECT_FLOAT_EQ(rectangle.y(), 2.0F);
	EXPECT_FLOAT_EQ(rectangle.width(), 3.0F);
	EXPECT_FLOAT_EQ(rectangle.height(), 4.0F);
	EXPECT_FLOAT_EQ(rectangle.area(), 12.0F);
	EXPECT_FLOAT_EQ(rectangle.perimeter(), 14.0F);
}

TEST_F(TestRectangle, ContainsIntersectsAndContainsRectangle) {
	utility::math::Rectangle<float> outer(0.0F, 0.0F, 10.0F, 10.0F);
	utility::math::Rectangle<float> inner(2.0F, 2.0F, 3.0F, 3.0F);
	utility::math::Rectangle<float> separate(20.0F, 20.0F, 5.0F, 5.0F);

	EXPECT_TRUE(outer.contains({5.0F, 5.0F}));
	EXPECT_FALSE(outer.contains({11.0F, 5.0F}));
	EXPECT_TRUE(outer.intersects(inner));
	EXPECT_FALSE(outer.intersects(separate));
	EXPECT_TRUE(outer.containsRectangle(inner));
}

TEST_F(TestRectangle, TranslateScaleAndScaledCopyWork) {
	utility::math::Rectangle<float> rectangle(0.0F, 0.0F, 4.0F, 6.0F);

	rectangle.translate(2.0F, 3.0F);
	EXPECT_FLOAT_EQ(rectangle.x(), 2.0F);
	EXPECT_FLOAT_EQ(rectangle.y(), 3.0F);

	const auto scaled = rectangle.scaled(0.5F);
	EXPECT_FLOAT_EQ(scaled.width(), 2.0F);
	EXPECT_FLOAT_EQ(scaled.height(), 3.0F);

	rectangle.scale(2.0F);
	EXPECT_FLOAT_EQ(rectangle.width(), 8.0F);
	EXPECT_FLOAT_EQ(rectangle.height(), 12.0F);

	EXPECT_THROW(rectangle.scale(-1.0F), std::invalid_argument);
}