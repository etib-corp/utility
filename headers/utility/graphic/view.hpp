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
 * @brief Concept to ensure the type can be used as a view component.
 * @tparam ViewComponentType The type to check.
 */
template <typename ViewComponentType>
concept CanBeViewComponent = CanBeFieldOfViewComponent<ViewComponentType> &&
                             CanBePoseComponent<ViewComponentType> &&
                             CanBeRayComponent<ViewComponentType>;

/**
 * @brief 3D perspective view with floating-point components.
 * @tparam ViewComponentType Floating-point type for view parameters and
 * vectors.
 */
template <CanBeViewComponent ViewComponentType> class View {
private:
protected:
  /**
   * @brief View pose (position + orientation).
   */
  Pose<ViewComponentType> _pose;

  /**
   * @brief View field-of-view angles.
   */
  FieldOfView<ViewComponentType> _fieldOfView;

  /**
   * @brief Validate perspective parameter constraints.
   * @param verticalFovDegrees Vertical field-of-view in degrees.
   * @param aspectRatio Aspect ratio (width/height).
   * @throws std::invalid_argument if any perspective parameter is invalid.
   */
  static void validatePerspective(ViewComponentType verticalFovDegrees,
                                  ViewComponentType aspectRatio) {
    if (verticalFovDegrees <= ViewComponentType{} ||
        verticalFovDegrees >= ViewComponentType{180}) {
      throw std::invalid_argument(
          "View vertical FOV must be in range (0, 180)");
    }
    if (aspectRatio <= ViewComponentType{}) {
      throw std::invalid_argument("View aspect ratio must be positive");
    }
  }

  /**
   * @brief Build symmetric per-direction FOV from vertical angle and aspect.
   * @param verticalFovDegrees Vertical field-of-view in degrees.
   * @param aspectRatio Aspect ratio (width/height).
   * @return Symmetric field-of-view values for all directions.
   */
  static FieldOfView<ViewComponentType>
  makeSymmetricFieldOfView(ViewComponentType verticalFovDegrees,
                           ViewComponentType aspectRatio) {
    const ViewComponentType halfVertical =
        verticalFovDegrees / ViewComponentType{2};
    const ViewComponentType halfVerticalRad =
        halfVertical * std::numbers::pi_v<ViewComponentType> /
        ViewComponentType{180};
    const ViewComponentType halfHorizontalRad =
        std::atan(std::tan(halfVerticalRad) * aspectRatio);
    const ViewComponentType halfHorizontal =
        halfHorizontalRad * ViewComponentType{180} /
        std::numbers::pi_v<ViewComponentType>;

    return FieldOfView<ViewComponentType>(halfVertical, halfVertical,
                                          halfHorizontal, halfHorizontal);
  }

  /**
   * @brief Validate orientation vectors for use as view basis.
   * @param forward Forward direction candidate.
   * @param up Up direction candidate.
   * @throws std::invalid_argument if vectors are zero or collinear.
   */
  static void
  validateOrientation(const math::Vector<ViewComponentType, 3> &forward,
                      const math::Vector<ViewComponentType, 3> &up) {
    if (math::dot(forward, forward) == ViewComponentType{}) {
      throw std::invalid_argument("View forward vector must be non-zero");
    }
    if (math::dot(up, up) == ViewComponentType{}) {
      throw std::invalid_argument("View up vector must be non-zero");
    }
    if (math::dot(math::cross(forward, up), math::cross(forward, up)) ==
        ViewComponentType{}) {
      throw std::invalid_argument(
          "View forward and up vectors must not be collinear");
    }
  }

  /**
   * @brief Convert and normalize stored quaternion components to view type.
   * @return Normalized quaternion components in xyzw order.
   */
  math::Vector<ViewComponentType, 4> normalizedRotationComponents() const {
    const auto normalized = _pose.getOrientation().normalizedQuaternion();
    return math::Vector<ViewComponentType, 4>(
        static_cast<ViewComponentType>(normalized.getX()),
        static_cast<ViewComponentType>(normalized.getY()),
        static_cast<ViewComponentType>(normalized.getZ()),
        static_cast<ViewComponentType>(normalized.getW()));
  }

  /**
   * @brief Rotate a vector by the view quaternion.
   * @param vector Input vector.
   * @return Rotated vector.
   */
  math::Vector<ViewComponentType, 3> rotateVectorByRotation(
      const math::Vector<ViewComponentType, 3> &vector) const {
    const auto q = normalizedRotationComponents();
    const math::Vector<ViewComponentType, 3> u{q[0], q[1], q[2]};
    const ViewComponentType s = q[3];

    return u * (ViewComponentType{2} * math::dot(u, vector)) +
           vector * (s * s - math::dot(u, u)) +
           math::cross(u, vector) * (ViewComponentType{2} * s);
  }

  /**
   * @brief Build and set quaternion orientation from forward/up basis vectors.
   * @param forward Forward direction candidate.
   * @param up Up direction candidate.
   * @throws std::invalid_argument if orientation constraints are violated.
   */
  void
  setOrientationFromBasis(const math::Vector<ViewComponentType, 3> &forward,
                          const math::Vector<ViewComponentType, 3> &up) {
    validateOrientation(forward, up);

    const auto normalizedForward = math::normalize(forward);
    const auto right = math::normalize(math::cross(normalizedForward, up));
    const auto correctedUp =
        math::normalize(math::cross(right, normalizedForward));
    const auto back = -normalizedForward;

    const ViewComponentType m00 = right[0];
    const ViewComponentType m01 = correctedUp[0];
    const ViewComponentType m02 = back[0];
    const ViewComponentType m10 = right[1];
    const ViewComponentType m11 = correctedUp[1];
    const ViewComponentType m12 = back[1];
    const ViewComponentType m20 = right[2];
    const ViewComponentType m21 = correctedUp[2];
    const ViewComponentType m22 = back[2];

    ViewComponentType qx{};
    ViewComponentType qy{};
    ViewComponentType qz{};
    ViewComponentType qw{};
    const ViewComponentType trace = m00 + m11 + m22;

    if (trace > ViewComponentType{}) {
      const ViewComponentType s =
          std::sqrt(trace + ViewComponentType{1}) * ViewComponentType{2};
      qw = ViewComponentType{0.25} * s;
      qx = (m21 - m12) / s;
      qy = (m02 - m20) / s;
      qz = (m10 - m01) / s;
    } else if (m00 > m11 && m00 > m22) {
      const ViewComponentType s =
          std::sqrt(ViewComponentType{1} + m00 - m11 - m22) *
          ViewComponentType{2};
      qw = (m21 - m12) / s;
      qx = ViewComponentType{0.25} * s;
      qy = (m01 + m10) / s;
      qz = (m02 + m20) / s;
    } else if (m11 > m22) {
      const ViewComponentType s =
          std::sqrt(ViewComponentType{1} + m11 - m00 - m22) *
          ViewComponentType{2};
      qw = (m02 - m20) / s;
      qx = (m01 + m10) / s;
      qy = ViewComponentType{0.25} * s;
      qz = (m12 + m21) / s;
    } else {
      const ViewComponentType s =
          std::sqrt(ViewComponentType{1} + m22 - m00 - m11) *
          ViewComponentType{2};
      qw = (m10 - m01) / s;
      qx = (m02 + m20) / s;
      qy = (m12 + m21) / s;
      qz = ViewComponentType{0.25} * s;
    }

    _pose.getOrientation(Orientation(
        static_cast<std::float_t>(qx), static_cast<std::float_t>(qy),
        static_cast<std::float_t>(qz), static_cast<std::float_t>(qw)));
  }

public:
  /**
   * @brief Default constructor with common perspective defaults.
   */
  View(void) : _pose(), _fieldOfView() {}

  /**
   * @brief Construct view from explicit quaternion orientation.
   * @param pose View world-space position and orientation.
   * @param verticalFovDegrees Vertical field-of-view in degrees.
   * @param aspectRatio Aspect ratio (width/height).
   * @throws std::invalid_argument if perspective values or quaternion are
   * invalid.
   */
  View(Pose<ViewComponentType> pose, ViewComponentType verticalFovDegrees,
       ViewComponentType aspectRatio)
      : _pose(std::move(pose)), _fieldOfView() {
    setPerspective(verticalFovDegrees, aspectRatio);
  }

  /**
   * @brief Copy constructor.
   * @param other View instance to copy from.
   */
  View(const View &other) = default;

  /**
   * @brief Move constructor.
   * @param other View instance to move from.
   */
  View(View &&other) noexcept = default;

  /**
   * @brief Copy assignment operator.
   * @param other View instance to copy from.
   * @return Reference to this view.
   */
  View &operator=(const View &other) = default;

  /**
   * @brief Move assignment operator.
   * @param other View instance to move from.
   * @return Reference to this view.
   */
  View &operator=(View &&other) noexcept = default;

  /**
   * @brief Destructor.
   */
  ~View(void) = default;

  /**
   * @brief Set view world-space pose.
   * @param pose New view pose (position and orientation).
   */
  void setPose(const Pose<ViewComponentType> &pose) { _pose = pose; }

  /**
   * @brief Get view world-space pose.
   * @return Pose object containing position and orientation.
   */
  Pose<ViewComponentType> getPose(void) const { return _pose; }

  /**
   * @brief Set and normalize forward direction.
   * @param forward New forward direction (non-zero, not collinear with up).
   * @throws std::invalid_argument if orientation constraints are violated.
   */
  void setForward(const math::Vector<ViewComponentType, 3> &forward) {
    setOrientationFromBasis(forward, getUp());
  }

  /**
   * @brief Get normalized forward direction.
   * @return Forward direction vector.
   */
  math::Vector<ViewComponentType, 3> getForward(void) const {
    return math::normalize(
        rotateVectorByRotation(math::Vector<ViewComponentType, 3>(
            ViewComponentType{}, ViewComponentType{}, ViewComponentType{-1})));
  }

  /**
   * @brief Set and normalize up direction.
   * @param up New up direction (non-zero, not collinear with forward).
   * @throws std::invalid_argument if orientation constraints are violated.
   */
  void setUp(const math::Vector<ViewComponentType, 3> &up) {
    setOrientationFromBasis(getForward(), up);
  }

  /**
   * @brief Get normalized up direction.
   * @return Up direction vector.
   */
  math::Vector<ViewComponentType, 3> getUp(void) const {
    return math::normalize(
        rotateVectorByRotation(math::Vector<ViewComponentType, 3>(
            ViewComponentType{}, ViewComponentType{1}, ViewComponentType{})));
  }

  /**
   * @brief Set perspective projection parameters.
   * @param verticalFovDegrees Vertical field-of-view in degrees.
   * @param aspectRatio Aspect ratio (width/height).
   * @throws std::invalid_argument if any perspective parameter is invalid.
   */
  void setPerspective(ViewComponentType verticalFovDegrees,
                      ViewComponentType aspectRatio) {
    validatePerspective(verticalFovDegrees, aspectRatio);
    _fieldOfView = makeSymmetricFieldOfView(verticalFovDegrees, aspectRatio);
  }

  /**
   * @brief Get aspect ratio (width/height).
   * @return Aspect ratio.
   */
  ViewComponentType getAspectRatio(void) const {
    const ViewComponentType vertical = std::tan(_fieldOfView.getUpRadians()) +
                                       std::tan(_fieldOfView.getDownRadians());
    if (vertical == ViewComponentType{}) {
      return ViewComponentType{};
    }
    const ViewComponentType horizontal =
        std::tan(_fieldOfView.getLeftRadians()) +
        std::tan(_fieldOfView.getRightRadians());
    return horizontal / vertical;
  }

  /**
   * @brief Set per-direction field-of-view values.
   * @param fieldOfView Field-of-view values.
   */
  void setFieldOfView(const FieldOfView<ViewComponentType> &fieldOfView) {
    const ViewComponentType vertical =
        fieldOfView.getUpDegrees() + fieldOfView.getDownDegrees();
    if (vertical <= ViewComponentType{} || vertical >= ViewComponentType{180}) {
      throw std::invalid_argument(
          "View vertical FOV must be in range (0, 180)");
    }
    _fieldOfView = fieldOfView;
  }

  /**
   * @brief Get field-of-view values.
   * @return Field-of-view object.
   */
  FieldOfView<ViewComponentType> getFieldOfView(void) const {
    return _fieldOfView;
  }

  /**
   * @brief Compute view right direction from orientation basis.
   * @return Normalized right direction vector.
   */
  math::Vector<ViewComponentType, 3> right(void) const {
    return math::normalize(
        rotateVectorByRotation(math::Vector<ViewComponentType, 3>(
            ViewComponentType{1}, ViewComponentType{}, ViewComponentType{})));
  }

  /**
   * @brief Translate view position by an offset.
   * @param offset Translation vector.
   */
  void move(const math::Vector<ViewComponentType, 3> &offset) {
    _pose.position() += offset;
  }

  /**
   * @brief Return translated view copy.
   * @param offset Translation vector.
   * @return View copy with updated position.
   */
  View moved(const math::Vector<ViewComponentType, 3> &offset) const {
    View result(*this);
    result.move(offset);
    return result;
  }

  /**
   * @brief Orient view to face a target position.
   * @param target World-space point to look at.
   * @param worldUp World-space up direction used to stabilize orientation.
   * @throws std::runtime_error if target equals current position.
   * @throws std::invalid_argument if resulting orientation is invalid.
   */
  void lookAt(const math::Vector<ViewComponentType, 3> &target,
              const math::Vector<ViewComponentType, 3> &worldUp =
                  math::Vector<ViewComponentType, 3>(ViewComponentType{},
                                                     ViewComponentType{1},
                                                     ViewComponentType{})) {
    const auto targetVector = target - _pose.position();
    if (math::dot(targetVector, targetVector) == ViewComponentType{}) {
      throw std::runtime_error("View lookAt target must differ from position");
    }
    const auto newForward = math::normalize(targetVector);
    setOrientationFromBasis(newForward, worldUp);
  }

  /**
   * @brief Create a world-space ray from normalized device coordinates.
   * @param ndcX Horizontal coordinate in range [-1, 1].
   * @param ndcY Vertical coordinate in range [-1, 1].
   * @return Ray originating at view position toward projected direction.
   */
  Ray<ViewComponentType> viewRay(ViewComponentType ndcX,
                                 ViewComponentType ndcY) const {
    const ViewComponentType horizontalOffset =
        ndcX >= ViewComponentType{}
            ? ndcX * std::tan(_fieldOfView.getRightRadians())
            : ndcX * std::tan(_fieldOfView.getLeftRadians());
    const ViewComponentType verticalOffset =
        ndcY >= ViewComponentType{}
            ? ndcY * std::tan(_fieldOfView.getUpRadians())
            : ndcY * std::tan(_fieldOfView.getDownRadians());

    const auto rayDirection =
        (getForward() + right() * horizontalOffset + getUp() * verticalOffset);

    return Ray<ViewComponentType>(_pose.position(),
                                  math::normalize(rayDirection));
  }
};

/**
 * @brief Type alias for single-precision view component.
 */
using ViewF = View<float>;

/**
 * @brief Type alias for double-precision view component.
 */
using ViewD = View<double>;

} // namespace utility::graphic
