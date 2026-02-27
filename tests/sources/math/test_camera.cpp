/*
 Copyright (c) 2026 ETIB Corporation

 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include "math/test_camera.hpp"

TEST_F(TestCamera, DefaultConstructorInitializesExpectedValues) {
  utility::math::Camera<float> camera;

  const auto position = camera.getPosition();
  const auto forward = camera.getForward();
  const auto up = camera.getUp();

  EXPECT_FLOAT_EQ(position[0], 0.0F);
  EXPECT_FLOAT_EQ(position[1], 0.0F);
  EXPECT_FLOAT_EQ(position[2], 0.0F);
  EXPECT_FLOAT_EQ(forward[0], 0.0F);
  EXPECT_FLOAT_EQ(forward[1], 0.0F);
  EXPECT_FLOAT_EQ(forward[2], -1.0F);
  EXPECT_FLOAT_EQ(up[0], 0.0F);
  EXPECT_FLOAT_EQ(up[1], 1.0F);
  EXPECT_FLOAT_EQ(up[2], 0.0F);

  EXPECT_FLOAT_EQ(camera.getVerticalFovDegrees(), 60.0F);
  EXPECT_FLOAT_EQ(camera.getAspectRatio(), 16.0F / 9.0F);
  EXPECT_FLOAT_EQ(camera.getNearPlane(), 0.1F);
  EXPECT_FLOAT_EQ(camera.getFarPlane(), 1000.0F);
}

TEST_F(TestCamera, ConstructorValidationRejectsInvalidValues) {
  const utility::math::Vector<float, 3> position{0.0F, 0.0F, 0.0F};
  const utility::math::Vector<float, 3> forward{0.0F, 0.0F, -1.0F};
  const utility::math::Vector<float, 3> up{0.0F, 1.0F, 0.0F};

  EXPECT_THROW((utility::math::Camera<float>(position, forward, up, 0.0F,
                                             16.0F / 9.0F, 0.1F, 1000.0F)),
               std::invalid_argument);
  EXPECT_THROW((utility::math::Camera<float>(position, forward, up, 60.0F, 0.0F,
                                             0.1F, 1000.0F)),
               std::invalid_argument);
  EXPECT_THROW((utility::math::Camera<float>(position, forward, up, 60.0F,
                                             16.0F / 9.0F, 0.0F, 1000.0F)),
               std::invalid_argument);
  EXPECT_THROW((utility::math::Camera<float>(position, forward, up, 60.0F,
                                             16.0F / 9.0F, 1.0F, 1.0F)),
               std::invalid_argument);
  EXPECT_THROW(
      (utility::math::Camera<float>(position, {0.0F, 0.0F, 0.0F}, up, 60.0F,
                                    16.0F / 9.0F, 0.1F, 1000.0F)),
      std::invalid_argument);
  EXPECT_THROW(
      (utility::math::Camera<float>(position, forward, {0.0F, 0.0F, 0.0F},
                                    60.0F, 16.0F / 9.0F, 0.1F, 1000.0F)),
      std::invalid_argument);
}

TEST_F(TestCamera, ViewRayAtCenterAlignsWithForward) {
  utility::math::Camera<float> camera;

  const auto ray = camera.viewRay(0.0F, 0.0F);
  const auto direction = ray.getDirection();

  EXPECT_FLOAT_EQ(ray.getOrigin()[0], 0.0F);
  EXPECT_FLOAT_EQ(ray.getOrigin()[1], 0.0F);
  EXPECT_FLOAT_EQ(ray.getOrigin()[2], 0.0F);

  EXPECT_NEAR(direction[0], 0.0F, 1e-5F);
  EXPECT_NEAR(direction[1], 0.0F, 1e-5F);
  EXPECT_NEAR(direction[2], -1.0F, 1e-5F);
}

TEST_F(TestCamera, MoveLookAtAndSetPerspectiveWork) {
  utility::math::Camera<float> camera;

  camera.move({1.0F, 2.0F, 3.0F});
  camera.lookAt({1.0F, 2.0F, 2.0F});
  camera.setPerspective(75.0F, 4.0F / 3.0F, 0.2F, 500.0F);

  const auto moved = camera.moved({1.0F, -1.0F, 0.5F});

  EXPECT_FLOAT_EQ(camera.getPosition()[0], 1.0F);
  EXPECT_FLOAT_EQ(camera.getPosition()[1], 2.0F);
  EXPECT_FLOAT_EQ(camera.getPosition()[2], 3.0F);

  EXPECT_NEAR(camera.getForward()[0], 0.0F, 1e-5F);
  EXPECT_NEAR(camera.getForward()[1], 0.0F, 1e-5F);
  EXPECT_NEAR(camera.getForward()[2], -1.0F, 1e-5F);

  EXPECT_FLOAT_EQ(camera.getVerticalFovDegrees(), 75.0F);
  EXPECT_FLOAT_EQ(camera.getAspectRatio(), 4.0F / 3.0F);
  EXPECT_FLOAT_EQ(camera.getNearPlane(), 0.2F);
  EXPECT_FLOAT_EQ(camera.getFarPlane(), 500.0F);

  EXPECT_FLOAT_EQ(moved.getPosition()[0], 2.0F);
  EXPECT_FLOAT_EQ(moved.getPosition()[1], 1.0F);
  EXPECT_FLOAT_EQ(moved.getPosition()[2], 3.5F);

  EXPECT_THROW(camera.lookAt({1.0F, 2.0F, 3.0F}), std::runtime_error);
  EXPECT_THROW(camera.setPerspective(181.0F, 4.0F / 3.0F, 0.2F, 500.0F),
               std::invalid_argument);
}
