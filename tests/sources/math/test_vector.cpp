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

#include "math/test_vector.hpp"

TEST_F(TestVector, DefaultConstructorInitializesToZero) {
  utility::math::Vector<int, 3> vector;

  EXPECT_EQ(vector.size(), 3U);
  EXPECT_EQ(vector[0], 0);
  EXPECT_EQ(vector[1], 0);
  EXPECT_EQ(vector[2], 0);
}

TEST_F(TestVector, InitializerListSizeMismatchThrows) {
  EXPECT_THROW((utility::math::Vector<int, 3>{1, 2}), std::invalid_argument);
}

TEST_F(TestVector, ArithmeticAndDotProductWork) {
  utility::math::Vector<float, 3> left{1.0F, 2.0F, 3.0F};
  utility::math::Vector<float, 3> right{4.0F, 5.0F, 6.0F};

  const auto sum = left + right;
  const auto diff = right - left;
  const auto scaled = left * 2.0F;

  EXPECT_FLOAT_EQ(sum[0], 5.0F);
  EXPECT_FLOAT_EQ(sum[1], 7.0F);
  EXPECT_FLOAT_EQ(sum[2], 9.0F);

  EXPECT_FLOAT_EQ(diff[0], 3.0F);
  EXPECT_FLOAT_EQ(diff[1], 3.0F);
  EXPECT_FLOAT_EQ(diff[2], 3.0F);

  EXPECT_FLOAT_EQ(scaled[0], 2.0F);
  EXPECT_FLOAT_EQ(scaled[1], 4.0F);
  EXPECT_FLOAT_EQ(scaled[2], 6.0F);

  EXPECT_FLOAT_EQ(left.dot(right), 32.0F);
}

TEST_F(TestVector, NormalizeCrossAndDistanceWork) {
  utility::math::Vector<float, 3> vector{3.0F, 4.0F, 0.0F};
  utility::math::Vector<float, 3> xAxis{1.0F, 0.0F, 0.0F};
  utility::math::Vector<float, 3> yAxis{0.0F, 1.0F, 0.0F};

  const auto normalized = vector.normalized();
  const auto cross = xAxis.cross(yAxis);

  EXPECT_NEAR(normalized.magnitude(), 1.0F, 1e-5F);
  EXPECT_FLOAT_EQ(cross[0], 0.0F);
  EXPECT_FLOAT_EQ(cross[1], 0.0F);
  EXPECT_FLOAT_EQ(cross[2], 1.0F);
  EXPECT_NEAR(xAxis.distance(yAxis), std::sqrt(2.0F), 1e-5F);

  utility::math::Vector<float, 3> zero;
  EXPECT_THROW(zero.normalized(), std::runtime_error);
}