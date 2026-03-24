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

#include "graphics/test_position_rotation.hpp"

#include <cmath>

TEST_F(TestPositionRotation, PositionTranslateAndTranslatedWork) {
  utility::graphics::Position position{1.0F, 2.0F, 3.0F};
  const utility::graphics::Position offset{-2.0F, 0.5F, 4.0F};

  const auto translatedCopy = position.translated(offset);
  EXPECT_FLOAT_EQ(position.getX(), 1.0F);
  EXPECT_FLOAT_EQ(position.getY(), 2.0F);
  EXPECT_FLOAT_EQ(position.getZ(), 3.0F);

  EXPECT_FLOAT_EQ(translatedCopy.getX(), -1.0F);
  EXPECT_FLOAT_EQ(translatedCopy.getY(), 2.5F);
  EXPECT_FLOAT_EQ(translatedCopy.getZ(), 7.0F);

  position.translate(offset);
  EXPECT_FLOAT_EQ(position.getX(), -1.0F);
  EXPECT_FLOAT_EQ(position.getY(), 2.5F);
  EXPECT_FLOAT_EQ(position.getZ(), 7.0F);
}

TEST_F(TestPositionRotation, PositionDistanceToComputesEuclideanDistance) {
  const utility::graphics::Position left{1.0F, 2.0F, 3.0F};
  const utility::graphics::Position right{4.0F, 6.0F, 3.0F};

  EXPECT_NEAR(left.distanceTo(right), 5.0F, 1e-5F);
  EXPECT_NEAR(right.distanceTo(left), 5.0F, 1e-5F);
}

TEST_F(TestPositionRotation, RotationRotateAndRotatedWork) {
  utility::graphics::Rotation rotation{0.0F, 0.0F, 0.0F, 1.0F};
  const utility::graphics::Rotation delta =
      utility::graphics::Rotation::fromEulerDegrees(0.0F, 90.0F, 0.0F);

  const auto rotatedCopy = rotation.rotated(delta);
  EXPECT_FLOAT_EQ(rotation.getX(), 0.0F);
  EXPECT_FLOAT_EQ(rotation.getY(), 0.0F);
  EXPECT_FLOAT_EQ(rotation.getZ(), 0.0F);
  EXPECT_FLOAT_EQ(rotation.getW(), 1.0F);

  EXPECT_NEAR(rotatedCopy.getX(), delta.getX(), 1e-5F);
  EXPECT_NEAR(rotatedCopy.getY(), delta.getY(), 1e-5F);
  EXPECT_NEAR(rotatedCopy.getZ(), delta.getZ(), 1e-5F);
  EXPECT_NEAR(rotatedCopy.getW(), delta.getW(), 1e-5F);

  rotation.rotate(delta);
  EXPECT_NEAR(rotation.getX(), delta.getX(), 1e-5F);
  EXPECT_NEAR(rotation.getY(), delta.getY(), 1e-5F);
  EXPECT_NEAR(rotation.getZ(), delta.getZ(), 1e-5F);
  EXPECT_NEAR(rotation.getW(), delta.getW(), 1e-5F);
}

TEST_F(TestPositionRotation, RotationDefaultAndNormalizationAreQuaternionBased) {
  utility::graphics::Rotation identity;
  EXPECT_FLOAT_EQ(identity.getX(), 0.0F);
  EXPECT_FLOAT_EQ(identity.getY(), 0.0F);
  EXPECT_FLOAT_EQ(identity.getZ(), 0.0F);
  EXPECT_FLOAT_EQ(identity.getW(), 1.0F);

  utility::graphics::Rotation quaternion{0.0F, 2.0F, 0.0F, 2.0F};
  const auto normalized = quaternion.normalizedQuaternion();
  EXPECT_NEAR(normalized.magnitude(), 1.0F, 1e-5F);

  quaternion.normalizeQuaternion();
  EXPECT_NEAR(quaternion.magnitude(), 1.0F, 1e-5F);
}

TEST_F(TestPositionRotation, RotationInverseProducesIdentityWithMultiplication) {
  const auto quaternion =
      utility::graphics::Rotation::fromEulerDegrees(15.0F, -40.0F, 90.0F)
          .normalizedQuaternion();
  const auto inverse = quaternion.inversed();

  const auto product = quaternion * inverse;
  EXPECT_NEAR(product.getX(), 0.0F, 1e-5F);
  EXPECT_NEAR(product.getY(), 0.0F, 1e-5F);
  EXPECT_NEAR(product.getZ(), 0.0F, 1e-5F);
  EXPECT_NEAR(product.getW(), 1.0F, 1e-5F);
}
