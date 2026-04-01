#include "graphic/test_scale.hpp"

#include "utility/graphic/scale.hpp"

using namespace utility::graphic;
using namespace tests::utility::graphic;

TEST_F(TestScale, DefaultAndComponentAccess) {
  ScaleF scale;
  EXPECT_FLOAT_EQ(scale.getX(), 1.0f);
  EXPECT_FLOAT_EQ(scale.getY(), 1.0f);
  EXPECT_FLOAT_EQ(scale.getZ(), 1.0f);
}

TEST_F(TestScale, ScaleByAndScaled) {
  ScaleF a(2.0f, 3.0f, 4.0f);
  ScaleF b(0.5f, 2.0f, 0.25f);

  ScaleF c = a.scaled(b);
  EXPECT_FLOAT_EQ(c.getX(), 1.0f);
  EXPECT_FLOAT_EQ(c.getY(), 6.0f);
  EXPECT_FLOAT_EQ(c.getZ(), 1.0f);

  a.scaleBy(b);
  EXPECT_FLOAT_EQ(a.getX(), 1.0f);
  EXPECT_FLOAT_EQ(a.getY(), 6.0f);
  EXPECT_FLOAT_EQ(a.getZ(), 1.0f);
}

TEST_F(TestScale, UniformAndNegativeHelpers) {
  ScaleF scale;
  scale.setUniform(2.0f);

  EXPECT_TRUE(scale.isUniform());
  EXPECT_FALSE(scale.hasNegativeComponent());

  scale.setZ(-1.0f);
  EXPECT_FALSE(scale.isUniform());
  EXPECT_TRUE(scale.hasNegativeComponent());
}
