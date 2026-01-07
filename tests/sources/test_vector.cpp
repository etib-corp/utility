/*
 Copyright (c) 2026 ETIB Corporation

 Permission is hereby granted, free of charge, to any person obtaining vectorA
 copy of this software and associated documentation files (the "Software"), to
 deal in the Software without restriction, including without limitation the
 rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

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

#include "test_vector.hpp"

#include "vector.hpp"

#include <cmath>
#include <sstream>
#include <stdexcept>

using utility::Vector;

namespace utility::tests {

TEST_F(TestVector, DefaultConstructsToZero) {
  const Vector<int, 3> vector;
  EXPECT_EQ(vector[0], 0);
  EXPECT_EQ(vector[1], 0);
  EXPECT_EQ(vector[2], 0);
}

TEST_F(TestVector, InitializerListConstructsValues) {
  const Vector<double, 3> vector{1.0, 2.0, 3.0};
  EXPECT_DOUBLE_EQ(vector[0], 1.0);
  EXPECT_DOUBLE_EQ(vector[1], 2.0);
  EXPECT_DOUBLE_EQ(vector[2], 3.0);
}

TEST_F(TestVector, ArithmeticOperations) {
  const Vector<int, 3> vectorA{1, 2, 3};
  const Vector<int, 3> vectorB{4, 5, 6};

  EXPECT_EQ(vectorA + vectorB, (Vector<int, 3>{5, 7, 9}));
  EXPECT_EQ(vectorB - vectorA, (Vector<int, 3>{3, 3, 3}));
  EXPECT_EQ(vectorA * 2, (Vector<int, 3>{2, 4, 6}));
  EXPECT_EQ(3 * vectorA, (Vector<int, 3>{3, 6, 9}));
}

TEST_F(TestVector, DotAndMagnitude) {
  const Vector<double, 3> vectorA{1.0, 2.0, 3.0};
  const Vector<double, 3> vectorB{4.0, -5.0, 6.0};

  EXPECT_DOUBLE_EQ(vectorA.dot(vectorB), 12.0);
  EXPECT_NEAR(vectorA.magnitude(), std::sqrt(14.0), 1e-12);
  EXPECT_DOUBLE_EQ(vectorA.magnitudeSquared(), 14.0);
}

TEST_F(TestVector, NormalizeAndDistance) {
  Vector<double, 3> vectorA{3.0, 0.0, 4.0};
  const auto normalized = vectorA.normalized();

  EXPECT_NEAR(normalized.magnitude(), 1.0, 1e-12);
  EXPECT_NEAR(vectorA.distance(Vector<double, 3>{0.0, 0.0, 0.0}), 5.0, 1e-12);
  EXPECT_DOUBLE_EQ(vectorA.distanceSquared(Vector<double, 3>{0.0, 0.0, 0.0}),
                   25.0);

  EXPECT_THROW((Vector<double, 3>{0.0, 0.0, 0.0}.normalized()),
               std::runtime_error);
  EXPECT_THROW((Vector<double, 3>{0.0, 0.0, 0.0}.normalize()),
               std::runtime_error);

  vectorA.normalize();
  EXPECT_NEAR(vectorA.magnitude(), 1.0, 1e-12);
}

TEST_F(TestVector, CrossProduct) {
  const Vector<double, 3> vectorA{1.0, 0.0, 0.0};
  const Vector<double, 3> vectorB{0.0, 1.0, 0.0};

  const auto cross = vectorA.cross(vectorB);
  EXPECT_DOUBLE_EQ(cross[0], 0.0);
  EXPECT_DOUBLE_EQ(cross[1], 0.0);
  EXPECT_DOUBLE_EQ(cross[2], 1.0);
}

TEST_F(TestVector, BoundsChecking) {
  Vector<int, 2> vector;
  EXPECT_THROW(vector[2], std::out_of_range);
  const Vector<int, 2> cvec;
  EXPECT_THROW(cvec[2], std::out_of_range);
}

TEST_F(TestVector, StreamOutputFormatting) {
  const Vector<int, 3> vector{1, 2, 3};
  std::ostringstream oss;
  oss << vector;
  EXPECT_EQ(oss.str(), "(1, 2, 3)");
}

} // namespace utility::tests