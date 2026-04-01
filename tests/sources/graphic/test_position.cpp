#include "graphic/test_position.hpp"

#include "utility/graphic/position.hpp"

using namespace utility::graphic;
using namespace tests::utility::graphic;

TEST_F(TestPosition, ConstructAndAccessComponents) {
  PositionF position(1.0f, 2.0f, 3.0f);
  EXPECT_FLOAT_EQ(position.getX(), 1.0f);
  EXPECT_FLOAT_EQ(position.getY(), 2.0f);
  EXPECT_FLOAT_EQ(position.getZ(), 3.0f);
}

TEST_F(TestPosition, TranslateAndTranslated) {
  PositionF start(1.0f, 2.0f, 3.0f);
  PositionF offset(4.0f, -2.0f, 1.0f);

  PositionF translated = start.translated(offset);
  EXPECT_FLOAT_EQ(translated.getX(), 5.0f);
  EXPECT_FLOAT_EQ(translated.getY(), 0.0f);
  EXPECT_FLOAT_EQ(translated.getZ(), 4.0f);

  start.translate(offset);
  EXPECT_FLOAT_EQ(start.getX(), 5.0f);
  EXPECT_FLOAT_EQ(start.getY(), 0.0f);
  EXPECT_FLOAT_EQ(start.getZ(), 4.0f);
}

TEST_F(TestPosition, SetterChaining) {
  PositionF position;
  position.setX(3.0f).setY(4.0f).setZ(5.0f);

  EXPECT_FLOAT_EQ(position.getX(), 3.0f);
  EXPECT_FLOAT_EQ(position.getY(), 4.0f);
  EXPECT_FLOAT_EQ(position.getZ(), 5.0f);
}

TEST_F(TestPosition, DistanceMidpointAndOrigin) {
  PositionF a(0.0f, 0.0f, 0.0f);
  PositionF b(3.0f, 4.0f, 0.0f);

  EXPECT_FLOAT_EQ(a.distanceSquaredTo(b), 25.0f);
  EXPECT_FLOAT_EQ(a.distanceTo(b), 5.0f);
  EXPECT_TRUE(a.isOrigin());
  EXPECT_FALSE(b.isOrigin());

  PositionF mid = a.midpoint(b);
  EXPECT_FLOAT_EQ(mid.getX(), 1.5f);
  EXPECT_FLOAT_EQ(mid.getY(), 2.0f);
  EXPECT_FLOAT_EQ(mid.getZ(), 0.0f);
}
