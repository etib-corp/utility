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

/**
 * @file camera.hpp
 * @brief 3D perspective camera template declaration.
 *
 * Declares `utility::graphics::Camera<Type>`, a lightweight camera model
 * storing position/orientation and perspective parameters, with utility methods
 * to generate world-space view rays.
 */

#pragma once

#include <cmath>
#include <numbers>
#include <ostream>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "utility/graphics/ray.hpp"
#include "utility/graphics/rotation.hpp"
#include "utility/math/vector.hpp"

namespace utility::graphics {

using utility::math::Vector;

/**
 * @brief Concept to ensure the type can be used as a camera component.
 * @tparam Type The type to check.
 */
template <typename Type>
concept CanBeCameraComponent = std::is_floating_point<Type>::value;

/**
 * @brief 3D perspective camera with floating-point components.
 * @tparam Type Floating-point type for camera parameters and vectors.
 */
template <CanBeCameraComponent Type> class Camera {
private:
protected:
  /**
   * @brief Camera world-space position.
   */
  Vector<Type, 3> _position;

  /**
   * @brief Camera orientation quaternion.
   */
  Rotation _rotation;

  /**
   * @brief Vertical field-of-view angle in degrees.
   */
  Type _verticalFovDegrees;

  /**
   * @brief Aspect ratio (width/height).
   */
  Type _aspectRatio;

  /**
   * @brief Near clipping plane distance.
   */
  Type _nearPlane;

  /**
   * @brief Far clipping plane distance.
   */
  Type _farPlane;

  /**
   * @brief Validate perspective parameter constraints.
   * @param verticalFovDegrees Vertical field-of-view in degrees.
   * @param aspectRatio Aspect ratio (width/height).
   * @param nearPlane Near clipping plane distance.
   * @param farPlane Far clipping plane distance.
   * @throws std::invalid_argument if any perspective parameter is invalid.
   */
  static void validatePerspective(Type verticalFovDegrees, Type aspectRatio,
                                  Type nearPlane, Type farPlane) {
    if (verticalFovDegrees <= Type{} || verticalFovDegrees >= Type{180}) {
      throw std::invalid_argument(
          "Camera vertical FOV must be in range (0, 180)");
    }
    if (aspectRatio <= Type{}) {
      throw std::invalid_argument("Camera aspect ratio must be positive");
    }
    if (nearPlane <= Type{}) {
      throw std::invalid_argument("Camera near plane must be positive");
    }
    if (farPlane <= nearPlane) {
      throw std::invalid_argument(
          "Camera far plane must be greater than near plane");
    }
  }

  /**
   * @brief Validate orientation vectors for use as camera basis.
   * @param forward Forward direction candidate.
   * @param up Up direction candidate.
   * @throws std::invalid_argument if vectors are zero or collinear.
   */
  static void validateOrientation(const Vector<Type, 3> &forward,
                                  const Vector<Type, 3> &up) {
    if (forward.magnitudeSquared() == Type{}) {
      throw std::invalid_argument("Camera forward vector must be non-zero");
    }
    if (up.magnitudeSquared() == Type{}) {
      throw std::invalid_argument("Camera up vector must be non-zero");
    }
    if (forward.cross(up).magnitudeSquared() == Type{}) {
      throw std::invalid_argument(
          "Camera forward and up vectors must not be collinear");
    }
  }

  /**
   * @brief Convert and normalize stored quaternion components to camera type.
   * @return Normalized quaternion components in xyzw order.
   */
  Vector<Type, 4> normalizedRotationComponents() const {
    const auto normalized = _rotation.normalizedQuaternion();
    return Vector<Type, 4>({static_cast<Type>(normalized.getX()),
                            static_cast<Type>(normalized.getY()),
                            static_cast<Type>(normalized.getZ()),
                            static_cast<Type>(normalized.getW())});
  }

  /**
   * @brief Rotate a vector by the camera quaternion.
   * @param vector Input vector.
   * @return Rotated vector.
   */
  Vector<Type, 3> rotateVectorByRotation(const Vector<Type, 3> &vector) const {
    const auto q = normalizedRotationComponents();
    const Vector<Type, 3> u{q[0], q[1], q[2]};
    const Type s = q[3];

    return u * (Type{2} * u.dot(vector)) + vector * (s * s - u.dot(u)) +
           u.cross(vector) * (Type{2} * s);
  }

  /**
   * @brief Build and set quaternion orientation from forward/up basis vectors.
   * @param forward Forward direction candidate.
   * @param up Up direction candidate.
   * @throws std::invalid_argument if orientation constraints are violated.
   */
  void setOrientationFromBasis(const Vector<Type, 3> &forward,
                               const Vector<Type, 3> &up) {
    validateOrientation(forward, up);

    const auto normalizedForward = forward.normalized();
    const auto right = normalizedForward.cross(up).normalized();
    const auto correctedUp = right.cross(normalizedForward).normalized();
    const auto back = -normalizedForward;

    const Type m00 = right[0];
    const Type m01 = correctedUp[0];
    const Type m02 = back[0];
    const Type m10 = right[1];
    const Type m11 = correctedUp[1];
    const Type m12 = back[1];
    const Type m20 = right[2];
    const Type m21 = correctedUp[2];
    const Type m22 = back[2];

    Type qx{};
    Type qy{};
    Type qz{};
    Type qw{};
    const Type trace = m00 + m11 + m22;

    if (trace > Type{}) {
      const Type s = std::sqrt(trace + Type{1}) * Type{2};
      qw = Type{0.25} * s;
      qx = (m21 - m12) / s;
      qy = (m02 - m20) / s;
      qz = (m10 - m01) / s;
    } else if (m00 > m11 && m00 > m22) {
      const Type s = std::sqrt(Type{1} + m00 - m11 - m22) * Type{2};
      qw = (m21 - m12) / s;
      qx = Type{0.25} * s;
      qy = (m01 + m10) / s;
      qz = (m02 + m20) / s;
    } else if (m11 > m22) {
      const Type s = std::sqrt(Type{1} + m11 - m00 - m22) * Type{2};
      qw = (m02 - m20) / s;
      qx = (m01 + m10) / s;
      qy = Type{0.25} * s;
      qz = (m12 + m21) / s;
    } else {
      const Type s = std::sqrt(Type{1} + m22 - m00 - m11) * Type{2};
      qw = (m10 - m01) / s;
      qx = (m02 + m20) / s;
      qy = (m12 + m21) / s;
      qz = Type{0.25} * s;
    }

    setRotation(
        Rotation(static_cast<std::float_t>(qx), static_cast<std::float_t>(qy),
                 static_cast<std::float_t>(qz), static_cast<std::float_t>(qw)));
  }

public:
  /**
   * @brief Default constructor with common perspective defaults.
   */
  Camera()
      : _position(), _rotation(), _verticalFovDegrees(Type{60}),
        _aspectRatio(Type{16} / Type{9}), _nearPlane(Type{0.1}),
        _farPlane(Type{1000}) {}

  /**
   * @brief Construct camera from explicit parameters.
   * @param position Camera world-space position.
   * @param forward Forward direction (non-zero, not collinear with up).
   * @param up Up direction (non-zero, not collinear with forward).
   * @param verticalFovDegrees Vertical field-of-view in degrees.
   * @param aspectRatio Aspect ratio (width/height).
   * @param nearPlane Near clipping plane distance.
   * @param farPlane Far clipping plane distance.
   */
  Camera(Vector<Type, 3> position, Vector<Type, 3> forward, Vector<Type, 3> up,
         Type verticalFovDegrees, Type aspectRatio, Type nearPlane,
         Type farPlane)
      : _position(std::move(position)), _rotation(),
        _verticalFovDegrees(verticalFovDegrees), _aspectRatio(aspectRatio),
        _nearPlane(nearPlane), _farPlane(farPlane) {
    setOrientationFromBasis(forward, up);
    validatePerspective(_verticalFovDegrees, _aspectRatio, _nearPlane,
                        _farPlane);
  }

  /**
   * @brief Construct camera from explicit quaternion orientation.
   * @param position Camera world-space position.
   * @param rotation Camera orientation quaternion.
   * @param verticalFovDegrees Vertical field-of-view in degrees.
   * @param aspectRatio Aspect ratio (width/height).
   * @param nearPlane Near clipping plane distance.
   * @param farPlane Far clipping plane distance.
   * @throws std::invalid_argument if perspective values or quaternion are
   * invalid.
   */
  Camera(Vector<Type, 3> position, Rotation rotation, Type verticalFovDegrees,
         Type aspectRatio, Type nearPlane, Type farPlane)
      : _position(std::move(position)), _rotation(std::move(rotation)),
        _verticalFovDegrees(verticalFovDegrees), _aspectRatio(aspectRatio),
        _nearPlane(nearPlane), _farPlane(farPlane) {
    setRotation(_rotation);
    validatePerspective(_verticalFovDegrees, _aspectRatio, _nearPlane,
                        _farPlane);
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
  ~Camera() = default;

  /**
   * @brief Get camera world-space position.
   * @return Position vector.
   */
  Vector<Type, 3> getPosition() const { return _position; }

  /**
   * @brief Get normalized forward direction.
   * @return Forward direction vector.
   */
  Vector<Type, 3> getForward() const {
    return rotateVectorByRotation(Vector<Type, 3>({Type{}, Type{}, Type{-1}}))
        .normalized();
  }

  /**
   * @brief Get normalized up direction.
   * @return Up direction vector.
   */
  Vector<Type, 3> getUp() const {
    return rotateVectorByRotation(Vector<Type, 3>({Type{}, Type{1}, Type{}}))
        .normalized();
  }

  /**
   * @brief Get camera orientation quaternion.
   * @return Rotation quaternion.
   */
  Rotation getRotation() const { return _rotation; }

  /**
   * @brief Get vertical field-of-view in degrees.
   * @return Vertical field-of-view angle.
   */
  Type getVerticalFovDegrees() const { return _verticalFovDegrees; }

  /**
   * @brief Get aspect ratio (width/height).
   * @return Aspect ratio.
   */
  Type getAspectRatio() const { return _aspectRatio; }

  /**
   * @brief Get near clipping plane distance.
   * @return Near plane distance.
   */
  Type getNearPlane() const { return _nearPlane; }

  /**
   * @brief Get far clipping plane distance.
   * @return Far plane distance.
   */
  Type getFarPlane() const { return _farPlane; }

  /**
   * @brief Set camera world-space position.
   * @param position New camera position.
   */
  void setPosition(const Vector<Type, 3> &position) { _position = position; }

  /**
   * @brief Set camera orientation quaternion.
   * @param rotation New orientation quaternion.
   * @throws std::invalid_argument if quaternion has zero norm.
   */
  void setRotation(const Rotation &rotation) {
    try {
      _rotation = rotation.normalizedQuaternion();
    } catch (const std::runtime_error &) {
      throw std::invalid_argument(
          "Camera rotation quaternion must be non-zero");
    }
  }

  /**
   * @brief Set and normalize forward direction.
   * @param forward New forward direction (non-zero, not collinear with up).
   * @throws std::invalid_argument if orientation constraints are violated.
   */
  void setForward(const Vector<Type, 3> &forward) {
    setOrientationFromBasis(forward, getUp());
  }

  /**
   * @brief Set and normalize up direction.
   * @param up New up direction (non-zero, not collinear with forward).
   * @throws std::invalid_argument if orientation constraints are violated.
   */
  void setUp(const Vector<Type, 3> &up) {
    setOrientationFromBasis(getForward(), up);
  }

  /**
   * @brief Set perspective projection parameters.
   * @param verticalFovDegrees Vertical field-of-view in degrees.
   * @param aspectRatio Aspect ratio (width/height).
   * @param nearPlane Near clipping plane distance.
   * @param farPlane Far clipping plane distance.
   * @throws std::invalid_argument if any perspective parameter is invalid.
   */
  void setPerspective(Type verticalFovDegrees, Type aspectRatio, Type nearPlane,
                      Type farPlane) {
    validatePerspective(verticalFovDegrees, aspectRatio, nearPlane, farPlane);
    _verticalFovDegrees = verticalFovDegrees;
    _aspectRatio = aspectRatio;
    _nearPlane = nearPlane;
    _farPlane = farPlane;
  }

  /**
   * @brief Compute camera right direction from orientation basis.
   * @return Normalized right direction vector.
   */
  Vector<Type, 3> right() const {
    return rotateVectorByRotation(Vector<Type, 3>({Type{1}, Type{}, Type{}}))
        .normalized();
  }

  /**
   * @brief Translate camera position by an offset.
   * @param offset Translation vector.
   */
  void move(const Vector<Type, 3> &offset) { _position += offset; }

  /**
   * @brief Return translated camera copy.
   * @param offset Translation vector.
   * @return Camera copy with updated position.
   */
  Camera moved(const Vector<Type, 3> &offset) const {
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
  void lookAt(const Vector<Type, 3> &target,
              const Vector<Type, 3> &worldUp = Vector<Type, 3>({Type{}, Type{1},
                                                                Type{}})) {
    const auto newForward = (target - _position).normalized();
    setOrientationFromBasis(newForward, worldUp);
  }

  /**
   * @brief Create a world-space ray from normalized device coordinates.
   * @param ndcX Horizontal coordinate in range [-1, 1].
   * @param ndcY Vertical coordinate in range [-1, 1].
   * @return Ray originating at camera position toward projected direction.
   */
  Ray<Type, 3> viewRay(Type ndcX, Type ndcY) const {
    const Type halfFovRadians =
        _verticalFovDegrees * std::numbers::pi_v<Type> / Type{360};
    const Type halfHeight = std::tan(halfFovRadians);
    const Type halfWidth = halfHeight * _aspectRatio;

    const auto rayDirection = (getForward() + right() * (ndcX * halfWidth) +
                               getUp() * (ndcY * halfHeight))
                                  .normalized();

    return Ray<Type, 3>(_position, rayDirection);
  }
};

/**
 * @brief Stream output as
 * "Camera(position=..., forward=..., up=..., verticalFovDegrees=...,
 * aspectRatio=..., nearPlane=..., farPlane=...)".
 * @tparam Type Floating-point component type of the camera.
 * @param outputStream Output stream.
 * @param camera Camera to output.
 * @return Reference to output stream.
 */
template <typename Type>
std::ostream &operator<<(std::ostream &outputStream,
                         const Camera<Type> &camera) {
  outputStream << "Camera(position=" << camera.getPosition()
               << ", forward=" << camera.getForward()
               << ", up=" << camera.getUp()
               << ", verticalFovDegrees=" << camera.getVerticalFovDegrees()
               << ", aspectRatio=" << camera.getAspectRatio()
               << ", nearPlane=" << camera.getNearPlane()
               << ", farPlane=" << camera.getFarPlane() << ')';
  return outputStream;
}

} // namespace utility::graphics
