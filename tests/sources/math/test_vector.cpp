#include "math/test_vector.hpp"

#include "utility/math/vector.hpp"

using namespace utility::math;
using namespace tests::utility::math;

TEST_F(TestVector, Addition) {
  Vector3F a{1.0f, 2.0f, 3.0f};
  Vector3F b{4.0f, 5.0f, 6.0f};
  Vector3F c = a + b;
  EXPECT_FLOAT_EQ(c[0], 5.0f);
  EXPECT_FLOAT_EQ(c[1], 7.0f);
  EXPECT_FLOAT_EQ(c[2], 9.0f);
}

TEST_F(TestVector, Subtraction) {
  Vector3F a{4.0f, 5.0f, 6.0f};
  Vector3F b{1.0f, 2.0f, 3.0f};
  Vector3F c = a - b;
  EXPECT_FLOAT_EQ(c[0], 3.0f);
  EXPECT_FLOAT_EQ(c[1], 3.0f);
  EXPECT_FLOAT_EQ(c[2], 3.0f);
}

TEST_F(TestVector, ScalarMultiplication) {
  Vector3F a{1.0f, 2.0f, 3.0f};
  Vector3F c = a * 2.0f;
  EXPECT_FLOAT_EQ(c[0], 2.0f);
  EXPECT_FLOAT_EQ(c[1], 4.0f);
  EXPECT_FLOAT_EQ(c[2], 6.0f);
}

TEST_F(TestVector, ScalarDivision) {
  Vector3F a{2.0f, 4.0f, 6.0f};
  Vector3F c = a / 2.0f;
  EXPECT_FLOAT_EQ(c[0], 1.0f);
  EXPECT_FLOAT_EQ(c[1], 2.0f);
  EXPECT_FLOAT_EQ(c[2], 3.0f);
}

TEST_F(TestVector, ElementwiseMultiplication) {
  Vector3F a{1.0f, 2.0f, 3.0f};
  Vector3F b{4.0f, 5.0f, 6.0f};
  Vector3F c = a * b;
  EXPECT_FLOAT_EQ(c[0], 4.0f);
  EXPECT_FLOAT_EQ(c[1], 10.0f);
  EXPECT_FLOAT_EQ(c[2], 18.0f);
}

TEST_F(TestVector, ElementwiseDivision) {
  Vector3F a{4.0f, 9.0f, 16.0f};
  Vector3F b{2.0f, 3.0f, 4.0f};
  Vector3F c = a / b;
  EXPECT_FLOAT_EQ(c[0], 2.0f);
  EXPECT_FLOAT_EQ(c[1], 3.0f);
  EXPECT_FLOAT_EQ(c[2], 4.0f);
}

TEST_F(TestVector, Negation) {
  Vector3F a{1.0f, -2.0f, 3.0f};
  Vector3F c = -a;
  EXPECT_FLOAT_EQ(c[0], -1.0f);
  EXPECT_FLOAT_EQ(c[1], 2.0f);
  EXPECT_FLOAT_EQ(c[2], -3.0f);
}

TEST_F(TestVector, Equality) {
  Vector3F a{1.0f, 2.0f, 3.0f};
  Vector3F b{1.0f, 2.0f, 3.0f};
  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a != b);
}
