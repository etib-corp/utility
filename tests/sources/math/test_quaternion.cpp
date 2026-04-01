#include "math/test_quaternion.hpp"

#include "utility/math/quaternion.hpp"

using namespace utility::math;
using namespace tests::utility::math;

TEST_F(TestQuaternion, Addition) {
  QuaternionF a{1.0f, 2.0f, 3.0f, 4.0f};
  QuaternionF b{4.0f, 3.0f, 2.0f, 1.0f};
  QuaternionF c = a + b;
  EXPECT_FLOAT_EQ(c.x, 5.0f);
  EXPECT_FLOAT_EQ(c.y, 5.0f);
  EXPECT_FLOAT_EQ(c.z, 5.0f);
  EXPECT_FLOAT_EQ(c.w, 5.0f);
}

TEST_F(TestQuaternion, Subtraction) {
  QuaternionF a{4.0f, 3.0f, 2.0f, 1.0f};
  QuaternionF b{1.0f, 2.0f, 3.0f, 4.0f};
  QuaternionF c = a - b;
  EXPECT_FLOAT_EQ(c.x, 3.0f);
  EXPECT_FLOAT_EQ(c.y, 1.0f);
  EXPECT_FLOAT_EQ(c.z, -1.0f);
  EXPECT_FLOAT_EQ(c.w, -3.0f);
}

TEST_F(TestQuaternion, ScalarMultiplication) {
  QuaternionF a{1.0f, 2.0f, 3.0f, 4.0f};
  QuaternionF c = a * 2.0f;
  EXPECT_FLOAT_EQ(c.x, 2.0f);
  EXPECT_FLOAT_EQ(c.y, 4.0f);
  EXPECT_FLOAT_EQ(c.z, 6.0f);
  EXPECT_FLOAT_EQ(c.w, 8.0f);
}

TEST_F(TestQuaternion, Negation) {
  QuaternionF a{1.0f, -2.0f, 3.0f, -4.0f};
  QuaternionF c = -a;
  EXPECT_FLOAT_EQ(c.x, -1.0f);
  EXPECT_FLOAT_EQ(c.y, 2.0f);
  EXPECT_FLOAT_EQ(c.z, -3.0f);
  EXPECT_FLOAT_EQ(c.w, 4.0f);
}

TEST_F(TestQuaternion, Equality) {
  QuaternionF a{1.0f, 2.0f, 3.0f, 4.0f};
  QuaternionF b{1.0f, 2.0f, 3.0f, 4.0f};
  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a != b);
}
