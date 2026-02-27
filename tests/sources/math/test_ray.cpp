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

#include "math/test_ray.hpp"

TEST_F(TestRay, DefaultConstructorInitializesExpectedValues) {
  utility::math::Ray<float, 3> ray;

  const auto origin = ray.getOrigin();
  const auto direction = ray.getDirection();

  EXPECT_FLOAT_EQ(origin[0], 0.0F);
  EXPECT_FLOAT_EQ(origin[1], 0.0F);
  EXPECT_FLOAT_EQ(origin[2], 0.0F);
  EXPECT_FLOAT_EQ(direction[0], 1.0F);
  EXPECT_FLOAT_EQ(direction[1], 0.0F);
  EXPECT_FLOAT_EQ(direction[2], 0.0F);
}

TEST_F(TestRay, ZeroDirectionIsRejected) {
  const utility::math::Vector<float, 3> zeroDirection{0.0F, 0.0F, 0.0F};
  EXPECT_THROW(
      (utility::math::Ray<float, 3>({0.0F, 0.0F, 0.0F}, zeroDirection)),
      std::invalid_argument);

  utility::math::Ray<float, 3> ray;
  EXPECT_THROW(ray.setDirection({0.0F, 0.0F, 0.0F}), std::invalid_argument);
}

TEST_F(TestRay, PointEvaluationAndNormalizationWork) {
  utility::math::Ray<float, 3> ray({1.0F, 2.0F, 3.0F}, {2.0F, 0.0F, 0.0F});

  const auto point = ray.pointAt(3.0F);
  const auto unitDirection = ray.normalizedDirection();

  EXPECT_FLOAT_EQ(point[0], 7.0F);
  EXPECT_FLOAT_EQ(point[1], 2.0F);
  EXPECT_FLOAT_EQ(point[2], 3.0F);
  EXPECT_NEAR(unitDirection.magnitude(), 1.0F, 1e-5F);
  EXPECT_FLOAT_EQ(unitDirection[0], 1.0F);
  EXPECT_FLOAT_EQ(unitDirection[1], 0.0F);
  EXPECT_FLOAT_EQ(unitDirection[2], 0.0F);
}

TEST_F(TestRay, TranslateAndTranslatedCopyWork) {
  utility::math::Ray<float, 2> ray({1.0F, 2.0F}, {0.0F, 1.0F});

  const auto moved = ray.translated({5.0F, -1.0F});
  ray.translate({-1.0F, 3.0F});

  EXPECT_FLOAT_EQ(moved.getOrigin()[0], 6.0F);
  EXPECT_FLOAT_EQ(moved.getOrigin()[1], 1.0F);
  EXPECT_FLOAT_EQ(moved.getDirection()[0], 0.0F);
  EXPECT_FLOAT_EQ(moved.getDirection()[1], 1.0F);

  EXPECT_FLOAT_EQ(ray.getOrigin()[0], 0.0F);
  EXPECT_FLOAT_EQ(ray.getOrigin()[1], 5.0F);
  EXPECT_FLOAT_EQ(ray.getDirection()[0], 0.0F);
  EXPECT_FLOAT_EQ(ray.getDirection()[1], 1.0F);
}
