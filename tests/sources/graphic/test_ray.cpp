#include "graphic/test_ray.hpp"

#include "utility/graphic/ray.hpp"

using namespace utility::graphic;
using namespace utility::math;
using namespace tests::utility::graphic;

TEST_F(TestRay, DefaultConstructor) {
  RayF ray;
  EXPECT_FLOAT_EQ(ray.getOrigin()[0], 0.0f);
  EXPECT_FLOAT_EQ(ray.getOrigin()[1], 0.0f);
  EXPECT_FLOAT_EQ(ray.getOrigin()[2], 0.0f);
  EXPECT_FLOAT_EQ(ray.getDirection()[0], 1.0f);
  EXPECT_FLOAT_EQ(ray.getDirection()[1], 0.0f);
  EXPECT_FLOAT_EQ(ray.getDirection()[2], 0.0f);
}

TEST_F(TestRay, PointAtAndTranslate) {
  RayF ray;
  Vector3F point = ray.pointAt(2.0f);
  EXPECT_FLOAT_EQ(point[0], 2.0f);
  EXPECT_FLOAT_EQ(point[1], 0.0f);
  EXPECT_FLOAT_EQ(point[2], 0.0f);

  ray.translate(Vector3F{1.0f, 0.0f, -1.0f});
  EXPECT_FLOAT_EQ(ray.getOrigin()[0], 1.0f);
  EXPECT_FLOAT_EQ(ray.getOrigin()[1], 0.0f);
  EXPECT_FLOAT_EQ(ray.getOrigin()[2], -1.0f);
}

TEST_F(TestRay, DirectionValidationAndAccessors) {
  RayF ray;

  EXPECT_THROW(ray.setDirection(Vector3F{0.0f, 0.0f, 0.0f}),
               std::invalid_argument);

  ray.setOrigin(PositionF(2.0f, 3.0f, 4.0f));
  EXPECT_FLOAT_EQ(ray.origin().getX(), 2.0f);
  EXPECT_FLOAT_EQ(ray.origin().getY(), 3.0f);
  EXPECT_FLOAT_EQ(ray.origin().getZ(), 4.0f);

  Vector3F atPoint = ray.at(3.0f);
  EXPECT_FLOAT_EQ(atPoint[0], 5.0f);
  EXPECT_FLOAT_EQ(atPoint[1], 3.0f);
  EXPECT_FLOAT_EQ(atPoint[2], 4.0f);
}
