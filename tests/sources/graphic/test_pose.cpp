#include "graphic/test_pose.hpp"

#include "utility/graphic/pose.hpp"

using namespace utility::graphic;
using namespace tests::utility::graphic;

TEST_F(TestPose, DefaultConstructor) {
  PoseF pose;
  EXPECT_FLOAT_EQ(pose.getPosition().getX(), 0.0f);
  EXPECT_FLOAT_EQ(pose.getPosition().getY(), 0.0f);
  EXPECT_FLOAT_EQ(pose.getPosition().getZ(), 0.0f);
}

TEST_F(TestPose, SetPositionAndOrientation) {
  PoseF pose;
  PositionF position(1.0f, 2.0f, 3.0f);
  OrientationF orientation(0.0f, 0.0f, 0.0f, 1.0f);

  pose.setPosition(position).setOrientation(orientation);

  EXPECT_FLOAT_EQ(pose.getPosition().getX(), 1.0f);
  EXPECT_FLOAT_EQ(pose.getPosition().getY(), 2.0f);
  EXPECT_FLOAT_EQ(pose.getPosition().getZ(), 3.0f);
  EXPECT_FLOAT_EQ(pose.getOrientation().x, orientation.x);
  EXPECT_FLOAT_EQ(pose.getOrientation().y, orientation.y);
  EXPECT_FLOAT_EQ(pose.getOrientation().z, orientation.z);
  EXPECT_FLOAT_EQ(pose.getOrientation().w, orientation.w);
}

TEST_F(TestPose, TranslateAndCompare) {
  PoseF poseA;
  PoseF poseB;

  EXPECT_TRUE(poseA == poseB);

  poseA.translate(PositionF(1.0f, 2.0f, 3.0f));
  EXPECT_FALSE(poseA == poseB);
  EXPECT_TRUE(poseA != poseB);

  PoseF moved = poseB.translated(PositionF(1.0f, 2.0f, 3.0f));
  EXPECT_TRUE(poseA == moved);
}
