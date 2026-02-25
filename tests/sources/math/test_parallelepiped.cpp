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

#include "math/test_parallelepiped.hpp"

TEST_F(TestParallelepiped, DefaultConstructorInitializesToZero) {
	utility::math::Parallelepiped<float> shape;

	const auto position = shape.getPosition();
	const auto origin = shape.getOrigin();
	const auto size = shape.getSize();

	EXPECT_FLOAT_EQ(position[0], 0.0F);
	EXPECT_FLOAT_EQ(position[1], 0.0F);
	EXPECT_FLOAT_EQ(position[2], 0.0F);
	EXPECT_FLOAT_EQ(origin[0], 0.0F);
	EXPECT_FLOAT_EQ(origin[1], 0.0F);
	EXPECT_FLOAT_EQ(origin[2], 0.0F);
	EXPECT_FLOAT_EQ(size[0], 0.0F);
	EXPECT_FLOAT_EQ(size[1], 0.0F);
	EXPECT_FLOAT_EQ(size[2], 0.0F);
}

TEST_F(TestParallelepiped, SettersAndGettersWork) {
	utility::math::Parallelepiped<float> shape;
	const utility::math::Vector<float, 3> position{1.0F, 2.0F, 3.0F};
	const utility::math::Vector<float, 3> origin{0.5F, 0.5F, 0.5F};
	const utility::math::Vector<float, 3> size{10.0F, 20.0F, 30.0F};

	shape.setPosition(position);
	shape.setOrigin(origin);
	shape.setSize(size);

	EXPECT_EQ(shape.getPosition(), position);
	EXPECT_EQ(shape.getOrigin(), origin);
	EXPECT_EQ(shape.getSize(), size);
}