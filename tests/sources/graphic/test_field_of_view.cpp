#include "graphic/test_field_of_view.hpp"

#include "utility/graphic/field_of_view.hpp"

using namespace utility::graphic;
using namespace tests::utility::graphic;

TEST_F(TestFieldOfView, ConstructFromDegrees) {
  FieldOfViewF fov(45.0f, 30.0f, 60.0f, 60.0f);

  EXPECT_FLOAT_EQ(fov.getUpDegrees(), 45.0f);
  EXPECT_FLOAT_EQ(fov.getDownDegrees(), 30.0f);
  EXPECT_FLOAT_EQ(fov.getLeftDegrees(), 60.0f);
  EXPECT_FLOAT_EQ(fov.getRightDegrees(), 60.0f);
  EXPECT_NEAR(fov.getUpRadians(), 0.78539816f, 1e-6f);
}

TEST_F(TestFieldOfView, SetRadiansUpdatesDegrees) {
  FieldOfViewF fov;
  fov.setUpRadians(1.57079633f);
  EXPECT_NEAR(fov.getUpDegrees(), 90.0f, 1e-4f);
}

TEST_F(TestFieldOfView, RejectNegativeAngle) {
  EXPECT_THROW(FieldOfViewF(-1.0f, 10.0f, 10.0f, 10.0f), std::invalid_argument);
}

TEST_F(TestFieldOfView, AggregateAndSymmetryHelpers) {
  FieldOfViewF symmetric(45.0f, 45.0f, 60.0f, 60.0f);
  FieldOfViewF asymmetric(40.0f, 45.0f, 55.0f, 60.0f);

  EXPECT_FLOAT_EQ(symmetric.getVerticalDegrees(), 90.0f);
  EXPECT_FLOAT_EQ(symmetric.getHorizontalDegrees(), 120.0f);
  EXPECT_NEAR(symmetric.getVerticalRadians(), 1.5707963f, 1e-6f);
  EXPECT_TRUE(symmetric.isSymmetric());
  EXPECT_FALSE(asymmetric.isSymmetric());
}
