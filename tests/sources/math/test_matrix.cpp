#include "math/test_matrix.hpp"

#include "utility/math/matrix.hpp"

using namespace utility::math;
using namespace tests::utility::math;

TEST_F(TestMatrix, Addition) {
  Matrix3x3F a{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
  Matrix3x3F b{9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
  Matrix3x3F c = a + b;
  EXPECT_FLOAT_EQ(c[0][0], 10.0f);
  EXPECT_FLOAT_EQ(c[1][1], 10.0f);
  EXPECT_FLOAT_EQ(c[2][2], 10.0f);
}

TEST_F(TestMatrix, Subtraction) {
  Matrix3x3F a{9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
  Matrix3x3F b{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
  Matrix3x3F c = a - b;
  EXPECT_FLOAT_EQ(c[0][0], 8.0f);
  EXPECT_FLOAT_EQ(c[1][1], 0.0f);
  EXPECT_FLOAT_EQ(c[2][2], -8.0f);
}

TEST_F(TestMatrix, ScalarMultiplication) {
  Matrix3x3F a{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
  Matrix3x3F c = a * 2.0f;
  EXPECT_FLOAT_EQ(c[0][0], 2.0f);
  EXPECT_FLOAT_EQ(c[1][1], 10.0f);
  EXPECT_FLOAT_EQ(c[2][2], 18.0f);
}

TEST_F(TestMatrix, ScalarDivision) {
  Matrix3x3F a{2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f};
  Matrix3x3F c = a / 2.0f;
  EXPECT_FLOAT_EQ(c[0][0], 1.0f);
  EXPECT_FLOAT_EQ(c[1][1], 5.0f);
  EXPECT_FLOAT_EQ(c[2][2], 9.0f);
}

TEST_F(TestMatrix, MatrixMultiplication) {
  Matrix3x3F a{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
  Matrix3x3F b{9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
  Matrix3x3F c = a * b;
  EXPECT_NEAR(c[0][0], 30.0f, 1e-5f);
  EXPECT_NEAR(c[1][1], 69.0f, 1e-5f);
  EXPECT_NEAR(c[2][2], 90.0f, 1e-5f);
}

TEST_F(TestMatrix, Negation) {
  Matrix3x3F a{1.0f, -2.0f, 3.0f, -4.0f, 5.0f, -6.0f, 7.0f, -8.0f, 9.0f};
  Matrix3x3F c = -a;
  EXPECT_FLOAT_EQ(c[0][0], -1.0f);
  EXPECT_FLOAT_EQ(c[1][1], -5.0f);
  EXPECT_FLOAT_EQ(c[2][2], -9.0f);
}

TEST_F(TestMatrix, Equality) {
  Matrix3x3F a{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
  Matrix3x3F b{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a != b);
}
