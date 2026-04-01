#include "graphic/test_orientation.hpp"

#include "utility/graphic/orientation.hpp"

using namespace utility::graphic;
using namespace utility::math;
using namespace tests::utility::graphic;

TEST_F(TestOrientation, ConstructFromQuaternion) {
  QuaternionF q(1.0f, 2.0f, 3.0f, 4.0f);
  OrientationF orientation(q);

  EXPECT_FLOAT_EQ(orientation.x, q.x);
  EXPECT_FLOAT_EQ(orientation.y, q.y);
  EXPECT_FLOAT_EQ(orientation.z, q.z);
  EXPECT_FLOAT_EQ(orientation.w, q.w);
}

TEST_F(TestOrientation, ConstructFromComponents) {
  OrientationF orientation(1.0f, 2.0f, 3.0f, 4.0f);
  EXPECT_FLOAT_EQ(orientation.x, 1.0f);
  EXPECT_FLOAT_EQ(orientation.y, 2.0f);
  EXPECT_FLOAT_EQ(orientation.z, 3.0f);
  EXPECT_FLOAT_EQ(orientation.w, 4.0f);
}

TEST_F(TestOrientation, IsIdentity) {
  OrientationF identity;
  EXPECT_TRUE(identity.isIdentity());

  OrientationF nonIdentity(1.0f, 0.0f, 0.0f, 0.0f);
  EXPECT_FALSE(nonIdentity.isIdentity());

  OrientationF nearIdentity(1e-6f, 1e-6f, 1e-6f, 1.0f);
  EXPECT_TRUE(nearIdentity.isIdentity());
}

TEST_F(TestOrientation, Normalized) {
  OrientationF orient(0.5f, 0.5f, 0.5f, 0.5f);
  OrientationF normalized = orient.normalized();

  float length = std::sqrt(normalized.x * normalized.x +
                           normalized.y * normalized.y +
                           normalized.z * normalized.z +
                           normalized.w * normalized.w);
  EXPECT_NEAR(length, 1.0f, 1e-5f);
}

TEST_F(TestOrientation, Inversed) {
  OrientationF orient(1.0f, 0.0f, 0.0f, 0.0f);
  OrientationF inverse = orient.inversed();

  QuaternionF mult = static_cast<QuaternionF>(orient) * static_cast<QuaternionF>(inverse);
  EXPECT_NEAR(mult.x, 0.0f, 1e-5f);
  EXPECT_NEAR(mult.y, 0.0f, 1e-5f);
  EXPECT_NEAR(mult.z, 0.0f, 1e-5f);
  EXPECT_NEAR(mult.w, 1.0f, 1e-5f);
}

TEST_F(TestOrientation, RotateVector) {
  OrientationF identity;
  Vector3F vec{1.0f, 0.0f, 0.0f};

  Vector3F rotated = identity.rotateVector(vec);
  EXPECT_NEAR(rotated[0], vec[0], 1e-5f);
  EXPECT_NEAR(rotated[1], vec[1], 1e-5f);
  EXPECT_NEAR(rotated[2], vec[2], 1e-5f);
}
