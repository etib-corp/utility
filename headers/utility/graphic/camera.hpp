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

#pragma once

#include <cmath>
#include <numbers>
#include <ostream>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "utility/graphic/field_of_view.hpp"
#include "utility/graphic/pose.hpp"
#include "utility/graphic/ray.hpp"

namespace utility::graphic {

/**
 * @brief Concept to ensure the type can be used as a camera component.
 * @tparam CameraComponentType The type to check.
 */
template <typename CameraComponentType>
concept CanBeCameraComponent = CanBeFieldOfViewComponent<CameraComponentType> &&
                               CanBePoseComponent<CameraComponentType> &&
                               CanBeRayComponent<CameraComponentType>;

/**
 * @brief 3D perspective camera with floating-point components.
 * @tparam CameraComponentType Floating-point type for camera parameters and
 * vectors.
 */
template <CanBeCameraComponent CameraComponentType> class Camera {
private:
protected:
  /**
   * @brief Camera pose (position + orientation).
   */
  Pose<CameraComponentType> _pose;

  /**
   * @brief Camera field-of-view angles.
   */
  FieldOfView<CameraComponentType> _fieldOfView;

  /**
   * @brief Validate perspective parameter constraints.
   * @param verticalFovDegrees Vertical field-of-view in degrees.
   * @param aspectRatio Aspect ratio (width/height).
   * @throws std::invalid_argument if any perspective parameter is invalid.
   */
  static void validatePerspective(CameraComponentType verticalFovDegrees,
                                  CameraComponentType aspectRatio) {
    if (verticalFovDegrees <= CameraComponentType{} ||
        verticalFovDegrees >= CameraComponentType{180}) {
      throw std::invalid_argument(
          "Camera vertical FOV must be in range (0, 180)");
    }
    if (aspectRatio <= CameraComponentType{}) {
      throw std::invalid_argument("Camera aspect ratio must be positive");
    }
  }

  /**
   * @brief Build symmetric per-direction FOV from vertical angle and aspect.
   * @param verticalFovDegrees Vertical field-of-view in degrees.
   * @param aspectRatio Aspect ratio (width/height).
   * @return Symmetric field-of-view values for all directions.
   */
  static FieldOfView<CameraComponentType>
  makeSymmetricFieldOfView(CameraComponentType verticalFovDegrees,
                           CameraComponentType aspectRatio) {
    const CameraComponentType halfVertical =
        verticalFovDegrees / CameraComponentType{2};
    const CameraComponentType halfVerticalRad =
        halfVertical * std::numbers::pi_v<CameraComponentType> /
        CameraComponentType{180};
    const CameraComponentType halfHorizontalRad =
        std::atan(std::tan(halfVerticalRad) * aspectRatio);
    const CameraComponentType halfHorizontal =
        halfHorizontalRad * CameraComponentType{180} /
        std::numbers::pi_v<CameraComponentType>;

    return FieldOfView<CameraComponentType>(halfVertical, halfVertical,
                                            halfHorizontal, halfHorizontal);
  }

  /**
   * @brief Validate orientation vectors for use as camera basis.
   * @param forward Forward direction candidate.
   * @param up Up direction candidate.
   * @throws std::invalid_argument if vectors are zero or collinear.
   */
  static void
  validateOrientation(const math::Vector<CameraComponentType, 3> &forward,
                      const math::Vector<CameraComponentType, 3> &up) {
    if (math::dot(forward, forward) == CameraComponentType{}) {
      throw std::invalid_argument("Camera forward vector must be non-zero");
    }
    if (math::dot(up, up) == CameraComponentType{}) {
      throw std::invalid_argument("Camera up vector must be non-zero");
    }
    if (math::dot(math::cross(forward, up), math::cross(forward, up)) ==
        CameraComponentType{}) {
      throw std::invalid_argument(
          "Camera forward and up vectors must not be collinear");
    }
  }

  /**
   * @brief Convert and normalize stored quaternion components to camera type.
   * @return Normalized quaternion components in xyzw order.
   */
  math::Vector<CameraComponentType, 4> normalizedRotationComponents() const {
    const auto normalized = _pose.getOrientation().normalizedQuaternion();
    return math::Vector<CameraComponentType, 4>(
        static_cast<CameraComponentType>(normalized.getX()),
        static_cast<CameraComponentType>(normalized.getY()),
        static_cast<CameraComponentType>(normalized.getZ()),
        static_cast<CameraComponentType>(normalized.getW()));
  }

  /**
   * @brief Rotate a vector by the camera quaternion.
   * @param vector Input vector.
   * @return Rotated vector.
   */
  math::Vector<CameraComponentType, 3> rotateVectorByRotation(
      const math::Vector<CameraComponentType, 3> &vector) const {
    const auto q = normalizedRotationComponents();
    const math::Vector<CameraComponentType, 3> u{q[0], q[1], q[2]};
    const CameraComponentType s = q[3];

    return u * (CameraComponentType{2} * math::dot(u, vector)) +
           vector * (s * s - math::dot(u, u)) +
           math::cross(u, vector) * (CameraComponentType{2} * s);
  }

  /**
   * @brief Build and set quaternion orientation from forward/up basis vectors.
   * @param forward Forward direction candidate.
   * @param up Up direction candidate.
   * @throws std::invalid_argument if orientation constraints are violated.
   */
  void
  setOrientationFromBasis(const math::Vector<CameraComponentType, 3> &forward,
                          const math::Vector<CameraComponentType, 3> &up) {
    validateOrientation(forward, up);

    const auto normalizedForward = math::normalize(forward);
    const auto right = math::normalize(math::cross(normalizedForward, up));
    const auto correctedUp =
        math::normalize(math::cross(right, normalizedForward));
    const auto back = -normalizedForward;

    const CameraComponentType m00 = right[0];
    const CameraComponentType m01 = correctedUp[0];
    const CameraComponentType m02 = back[0];
    const CameraComponentType m10 = right[1];
    const CameraComponentType m11 = correctedUp[1];
    const CameraComponentType m12 = back[1];
    const CameraComponentType m20 = right[2];
    const CameraComponentType m21 = correctedUp[2];
    const CameraComponentType m22 = back[2];

    CameraComponentType qx{};
    CameraComponentType qy{};
    CameraComponentType qz{};
    CameraComponentType qw{};
    const CameraComponentType trace = m00 + m11 + m22;

    if (trace > CameraComponentType{}) {
      const CameraComponentType s =
          std::sqrt(trace + CameraComponentType{1}) * CameraComponentType{2};
      qw = CameraComponentType{0.25} * s;
      qx = (m21 - m12) / s;
      qy = (m02 - m20) / s;
      qz = (m10 - m01) / s;
    } else if (m00 > m11 && m00 > m22) {
      const CameraComponentType s =
          std::sqrt(CameraComponentType{1} + m00 - m11 - m22) *
          CameraComponentType{2};
      qw = (m21 - m12) / s;
      qx = CameraComponentType{0.25} * s;
      qy = (m01 + m10) / s;
      qz = (m02 + m20) / s;
    } else if (m11 > m22) {
      const CameraComponentType s =
          std::sqrt(CameraComponentType{1} + m11 - m00 - m22) *
          CameraComponentType{2};
      qw = (m02 - m20) / s;
      qx = (m01 + m10) / s;
      qy = CameraComponentType{0.25} * s;
      qz = (m12 + m21) / s;
    } else {
      const CameraComponentType s =
          std::sqrt(CameraComponentType{1} + m22 - m00 - m11) *
          CameraComponentType{2};
      qw = (m10 - m01) / s;
      qx = (m02 + m20) / s;
      qy = (m12 + m21) / s;
      qz = CameraComponentType{0.25} * s;
    }

    _pose.getOrientation(Orientation(
        static_cast<std::float_t>(qx), static_cast<std::float_t>(qy),
        static_cast<std::float_t>(qz), static_cast<std::float_t>(qw)));
  }

public:
  /**
   * @brief Default constructor with common perspective defaults.
   */
  Camera(void) : _pose(), _fieldOfView() {}

  /**
   * @brief Construct camera from explicit quaternion orientation.
   * @param pose Camera world-space position and orientation.
   * @param verticalFovDegrees Vertical field-of-view in degrees.
   * @param aspectRatio Aspect ratio (width/height).
   * @throws std::invalid_argument if perspective values or quaternion are
   * invalid.
   */
  Camera(Pose<CameraComponentType> pose, CameraComponentType verticalFovDegrees,
         CameraComponentType aspectRatio)
      : _pose(std::move(pose)), _fieldOfView() {
    setPerspective(verticalFovDegrees, aspectRatio);
  }

  /**
   * @brief Copy constructor.
   * @param other Camera instance to copy from.
   */
  Camera(const Camera &other) = default;

  /**
   * @brief Move constructor.
   * @param other Camera instance to move from.
   */
  Camera(Camera &&other) noexcept = default;

  /**
   * @brief Copy assignment operator.
   * @param other Camera instance to copy from.
   * @return Reference to this camera.
   */
  Camera &operator=(const Camera &other) = default;

  /**
   * @brief Move assignment operator.
   * @param other Camera instance to move from.
   * @return Reference to this camera.
   */
  Camera &operator=(Camera &&other) noexcept = default;

  /**
   * @brief Destructor.
   */
  ~Camera(void) = default;

  /**
   * @brief Set camera world-space pose.
   * @param pose New camera pose (position and orientation).
   */
  void setPose(const Pose<CameraComponentType> &pose) { _pose = pose; }

  /**
   * @brief Get camera world-space pose.
   * @return Pose object containing position and orientation.
   */
  Pose<CameraComponentType> getPose(void) const { return _pose; }

  /**
   * @brief Set and normalize forward direction.
   * @param forward New forward direction (non-zero, not collinear with up).
   * @throws std::invalid_argument if orientation constraints are violated.
   */
  void setForward(const math::Vector<CameraComponentType, 3> &forward) {
    setOrientationFromBasis(forward, getUp());
  }

  /**
   * @brief Get normalized forward direction.
   * @return Forward direction vector.
   */
  math::Vector<CameraComponentType, 3> getForward(void) const {
    return math::normalize(rotateVectorByRotation(
        math::Vector<CameraComponentType, 3>(CameraComponentType{},
                                             CameraComponentType{},
                                             CameraComponentType{-1})));
  }

  /**
   * @brief Set and normalize up direction.
   * @param up New up direction (non-zero, not collinear with forward).
   * @throws std::invalid_argument if orientation constraints are violated.
   */
  void setUp(const math::Vector<CameraComponentType, 3> &up) {
    setOrientationFromBasis(getForward(), up);
  }

  /**
   * @brief Get normalized up direction.
   * @return Up direction vector.
   */
  math::Vector<CameraComponentType, 3> getUp(void) const {
    return math::normalize(rotateVectorByRotation(
        math::Vector<CameraComponentType, 3>(CameraComponentType{},
                                             CameraComponentType{1},
                                             CameraComponentType{})));
  }

  /**
   * @brief Set perspective projection parameters.
   * @param verticalFovDegrees Vertical field-of-view in degrees.
   * @param aspectRatio Aspect ratio (width/height).
   * @throws std::invalid_argument if any perspective parameter is invalid.
   */
  void setPerspective(CameraComponentType verticalFovDegrees,
                      CameraComponentType aspectRatio) {
    validatePerspective(verticalFovDegrees, aspectRatio);
    _fieldOfView = makeSymmetricFieldOfView(verticalFovDegrees, aspectRatio);
  }

  /**
   * @brief Get aspect ratio (width/height).
   * @return Aspect ratio.
   */
  CameraComponentType getAspectRatio(void) const {
    const CameraComponentType vertical =
        std::tan(_fieldOfView.getUpRadians()) +
        std::tan(_fieldOfView.getDownRadians());
    if (vertical == CameraComponentType{}) {
      return CameraComponentType{};
    }
    const CameraComponentType horizontal =
        std::tan(_fieldOfView.getLeftRadians()) +
        std::tan(_fieldOfView.getRightRadians());
    return horizontal / vertical;
  }

  /**
   * @brief Set per-direction field-of-view values.
   * @param fieldOfView Field-of-view values.
   */
  void setFieldOfView(const FieldOfView<CameraComponentType> &fieldOfView) {
    const CameraComponentType vertical =
        fieldOfView.getUpDegrees() + fieldOfView.getDownDegrees();
    if (vertical <= CameraComponentType{} ||
        vertical >= CameraComponentType{180}) {
      throw std::invalid_argument(
          "Camera vertical FOV must be in range (0, 180)");
    }
    _fieldOfView = fieldOfView;
  }

  /**
   * @brief Get field-of-view values.
   * @return Field-of-view object.
   */
  FieldOfView<CameraComponentType> getFieldOfView(void) const {
    return _fieldOfView;
  }

  /**
   * @brief Compute camera right direction from orientation basis.
   * @return Normalized right direction vector.
   */
  math::Vector<CameraComponentType, 3> right(void) const {
    return math::normalize(rotateVectorByRotation(
        math::Vector<CameraComponentType, 3>(CameraComponentType{1},
                                             CameraComponentType{},
                                             CameraComponentType{})));
  }

  /**
   * @brief Translate camera position by an offset.
   * @param offset Translation vector.
   */
  void move(const math::Vector<CameraComponentType, 3> &offset) {
    _pose.position() += offset;
  }

  /**
   * @brief Return translated camera copy.
   * @param offset Translation vector.
   * @return Camera copy with updated position.
   */
  Camera moved(const math::Vector<CameraComponentType, 3> &offset) const {
    Camera result(*this);
    result.move(offset);
    return result;
  }

  /**
   * @brief Orient camera to face a target position.
   * @param target World-space point to look at.
   * @param worldUp World-space up direction used to stabilize orientation.
   * @throws std::runtime_error if target equals current position.
   * @throws std::invalid_argument if resulting orientation is invalid.
   */
  void lookAt(const math::Vector<CameraComponentType, 3> &target,
              const math::Vector<CameraComponentType, 3> &worldUp =
                  math::Vector<CameraComponentType, 3>(CameraComponentType{},
                                                       CameraComponentType{1},
                                                       CameraComponentType{})) {
    const auto targetVector = target - _pose.position();
    if (math::dot(targetVector, targetVector) == CameraComponentType{}) {
      throw std::runtime_error(
          "Camera lookAt target must differ from position");
    }
    const auto newForward = math::normalize(targetVector);
    setOrientationFromBasis(newForward, worldUp);
  }

  /**
   * @brief Create a world-space ray from normalized device coordinates.
   * @param ndcX Horizontal coordinate in range [-1, 1].
   * @param ndcY Vertical coordinate in range [-1, 1].
   * @return Ray originating at camera position toward projected direction.
   */
  Ray<CameraComponentType> viewRay(CameraComponentType ndcX,
                                   CameraComponentType ndcY) const {
    const CameraComponentType horizontalOffset =
        ndcX >= CameraComponentType{}
            ? ndcX * std::tan(_fieldOfView.getRightRadians())
            : ndcX * std::tan(_fieldOfView.getLeftRadians());
    const CameraComponentType verticalOffset =
        ndcY >= CameraComponentType{}
            ? ndcY * std::tan(_fieldOfView.getUpRadians())
            : ndcY * std::tan(_fieldOfView.getDownRadians());

    const auto rayDirection =
        (getForward() + right() * horizontalOffset + getUp() * verticalOffset);

    return Ray<CameraComponentType>(_pose.position(),
                                    math::normalize(rayDirection));
  }
};

/**
 * @brief Type alias for single-precision camera component.
 */
using CameraF = Camera<float>;

/**
 * @brief Type alias for double-precision camera component.
 */
using CameraD = Camera<double>;

} // namespace utility::graphic
