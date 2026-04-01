#include "graphic/test_view.hpp"

#include "utility/graphic/view.hpp"

using namespace utility::graphic;
using namespace tests::utility::graphic;

TEST_F(TestView, SetPerspectiveAndAspectRatio) {
  ViewF view;
  view.setPerspective(90.0f, 2.0f);
  EXPECT_NEAR(view.getAspectRatio(), 2.0f, 1e-4f);
}

TEST_F(TestView, RejectInvalidPerspective) {
  ViewF view;
  EXPECT_THROW(view.setPerspective(0.0f, 1.0f), std::invalid_argument);
  EXPECT_THROW(view.setPerspective(181.0f, 1.0f), std::invalid_argument);
  EXPECT_THROW(view.setPerspective(90.0f, 0.0f), std::invalid_argument);
}

TEST_F(TestView, RejectInvalidFieldOfView) {
  ViewF view;
  EXPECT_THROW(view.setFieldOfView(FieldOfViewF(100.0f, 90.0f, 45.0f, 45.0f)),
               std::invalid_argument);
}

TEST_F(TestView, FovDegreeAggregates) {
  ViewF view;
  FieldOfViewF fov(60.0f, 80.0f, 45.0f, 35.0f);
  view.setFieldOfView(fov);

  EXPECT_NEAR(view.getVerticalFovDegrees(), 60.0f + 80.0f, 1e-4f);
  EXPECT_NEAR(view.getHorizontalFovDegrees(), 45.0f + 35.0f, 1e-4f);
}

TEST_F(TestView, IsFieldOfViewSymmetric) {
  ViewF view;

  FieldOfViewF symmetric(45.0f, 45.0f, 60.0f, 60.0f);
  view.setFieldOfView(symmetric);
  EXPECT_TRUE(view.isFieldOfViewSymmetric());

  FieldOfViewF asymmetric(45.0f, 50.0f, 60.0f, 70.0f);
  view.setFieldOfView(asymmetric);
  EXPECT_FALSE(view.isFieldOfViewSymmetric());
}

TEST_F(TestView, ComparisonOperators) {
  ViewF view1;
  ViewF view2;

  EXPECT_TRUE(view1 == view2);
  EXPECT_FALSE(view1 != view2);

  view1.setPerspective(90.0f, 2.0f);
  EXPECT_FALSE(view1 == view2);
  EXPECT_TRUE(view1 != view2);

  view2.setPerspective(90.0f, 2.0f);
  EXPECT_TRUE(view1 == view2);
  EXPECT_FALSE(view1 != view2);
}

TEST_F(TestView, PoseManagement) {
  ViewF view;
  Pose<float> initialPose;
  view.setPose(initialPose);

  Pose<float> retrievedPose = view.getPose();
  EXPECT_TRUE(retrievedPose == initialPose);

  Pose<float> newPose;
  newPose.setPosition(Position<float>(1.0f, 2.0f, 3.0f));
  view.setPose(newPose);
  
  Pose<float> updated = view.getPose();
  EXPECT_NEAR(updated.getPosition()[0], 1.0f, 1e-5f);
  EXPECT_NEAR(updated.getPosition()[1], 2.0f, 1e-5f);
  EXPECT_NEAR(updated.getPosition()[2], 3.0f, 1e-5f);
}
