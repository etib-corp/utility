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
 * Declares `utility::math::Camera<Type>`, a lightweight camera model storing
 * position/orientation and perspective parameters, with utility methods to
 * generate world-space view rays.
 */

#pragma once

#include <cmath>
#include <numbers>
#include <ostream>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "utility/math/ray.hpp"
#include "utility/math/vector.hpp"

namespace utility::math {

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
  Vector<Type, 3> _position;
  Vector<Type, 3> _forward;
  Vector<Type, 3> _up;
  Type _verticalFovDegrees;
  Type _aspectRatio;
  Type _nearPlane;
  Type _farPlane;

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

public:
  /**
   * @brief Default constructor with common perspective defaults.
   */
  Camera()
      : _position(), _forward({Type{}, Type{}, Type{-1}}),
        _up({Type{}, Type{1}, Type{}}), _verticalFovDegrees(Type{60}),
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
      : _position(std::move(position)), _forward(std::move(forward)),
        _up(std::move(up)), _verticalFovDegrees(verticalFovDegrees),
        _aspectRatio(aspectRatio), _nearPlane(nearPlane), _farPlane(farPlane) {
    validateOrientation(_forward, _up);
    _forward.normalize();
    _up.normalize();
    validatePerspective(_verticalFovDegrees, _aspectRatio, _nearPlane,
                        _farPlane);
  }

  Camera(const Camera &other) = default;
  Camera(Camera &&other) noexcept = default;
  Camera &operator=(const Camera &other) = default;
  Camera &operator=(Camera &&other) noexcept = default;

  ~Camera() = default;

  Vector<Type, 3> getPosition() const { return _position; }
  Vector<Type, 3> getForward() const { return _forward; }
  Vector<Type, 3> getUp() const { return _up; }

  Type getVerticalFovDegrees() const { return _verticalFovDegrees; }
  Type getAspectRatio() const { return _aspectRatio; }
  Type getNearPlane() const { return _nearPlane; }
  Type getFarPlane() const { return _farPlane; }

  void setPosition(const Vector<Type, 3> &position) { _position = position; }

  void setForward(const Vector<Type, 3> &forward) {
    validateOrientation(forward, _up);
    _forward = forward.normalized();
  }

  void setUp(const Vector<Type, 3> &up) {
    validateOrientation(_forward, up);
    _up = up.normalized();
  }

  void setPerspective(Type verticalFovDegrees, Type aspectRatio, Type nearPlane,
                      Type farPlane) {
    validatePerspective(verticalFovDegrees, aspectRatio, nearPlane, farPlane);
    _verticalFovDegrees = verticalFovDegrees;
    _aspectRatio = aspectRatio;
    _nearPlane = nearPlane;
    _farPlane = farPlane;
  }

  Vector<Type, 3> right() const { return _forward.cross(_up).normalized(); }

  void move(const Vector<Type, 3> &offset) { _position += offset; }

  Camera moved(const Vector<Type, 3> &offset) const {
    Camera result(*this);
    result.move(offset);
    return result;
  }

  void lookAt(const Vector<Type, 3> &target,
              const Vector<Type, 3> &worldUp =
                  Vector<Type, 3>({Type{}, Type{1}, Type{}})) {
    const auto newForward = (target - _position).normalized();
    validateOrientation(newForward, worldUp);

    _forward = newForward;
    _up = worldUp.normalized();
  }

  /**
   * @brief Create a world-space ray from normalized device coordinates.
   * @param ndcX Horizontal coordinate in range [-1, 1].
   * @param ndcY Vertical coordinate in range [-1, 1].
   * @return Ray originating at camera position toward projected direction.
   */
  Ray<Type, 3> viewRay(Type ndcX, Type ndcY) const {
    const Type halfFovRadians = _verticalFovDegrees * std::numbers::pi_v<Type> /
                                Type{360};
    const Type halfHeight = std::tan(halfFovRadians);
    const Type halfWidth = halfHeight * _aspectRatio;

    const auto rayDirection =
        (_forward + right() * (ndcX * halfWidth) + _up * (ndcY * halfHeight))
            .normalized();

    return Ray<Type, 3>(_position, rayDirection);
  }
};

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

} // namespace utility::math
