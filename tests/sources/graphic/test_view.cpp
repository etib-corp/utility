#include "graphic/test_view.hpp"

#include "utility/graphic/view.hpp"

using namespace utility::graphic;
using namespace tests::utility::graphic;

TEST_F(TestView, SetPerspectiveAndAspectRatio)
{
	ViewF view;
	view.setPerspective(3.14159265f / 2.0f, 2.0f);
	EXPECT_NEAR(view.getAspectRatio(), 2.0f, 1e-4f);
}

TEST_F(TestView, RejectInvalidPerspective)
{
	ViewF view;
	EXPECT_THROW(view.setPerspective(0.0f, 1.0f), std::invalid_argument);
	EXPECT_THROW(view.setPerspective(4.0f, 1.0f), std::invalid_argument);
	EXPECT_THROW(view.setPerspective(1.5f, 0.0f), std::invalid_argument);
}

TEST_F(TestView, ComparisonOperators)
{
	ViewF view1;
	ViewF view2;

	EXPECT_TRUE(view1 == view2);
	EXPECT_FALSE(view1 != view2);

	view1.setPerspective(3.14159265f / 2.0f, 2.0f);
	EXPECT_FALSE(view1 == view2);
	EXPECT_TRUE(view1 != view2);

	view2.setPerspective(3.14159265f / 2.0f, 2.0f);
	EXPECT_TRUE(view1 == view2);
	EXPECT_FALSE(view1 != view2);
}

TEST_F(TestView, RejectDegenerateFrustum)
{
	// Symmetric zero-width/zero-height frustum yields a degenerate projection.
	ViewF view;
	FieldOfView<float> degenerate { 0.0f, 0.0f, 0.0f, 0.0f };
	view.setFieldOfView(degenerate);
	EXPECT_THROW(view.getProjectionMatrix(), std::invalid_argument);
}

TEST_F(TestView, FlipYDefaultsToTrue)
{
	ViewF view;
	EXPECT_TRUE(view.isFlipY());
}

TEST_F(TestView, SetFlipY)
{
	ViewF view;
	view.setFlipY(false);
	EXPECT_FALSE(view.isFlipY());
	view.setFlipY(true);
	EXPECT_TRUE(view.isFlipY());
}

TEST_F(TestView, PoseManagement)
{
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
