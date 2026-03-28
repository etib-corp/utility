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
#include <stdexcept>
#include <string>
#include <type_traits>

namespace utility::graphic {

/**
 * @brief Concept to constrain field-of-view component type.
 * @tparam Type Candidate component type.
 */
template <typename Type>
concept CanBeFieldOfViewComponent = std::is_floating_point_v<Type>;

/**
 * @brief Field of view representation in degrees for up, down, left, and right
 * directions.
 * @tparam Type Floating-point component type used for stored angles.
 * @note We store in radians internally for efficient calculations, but the
 * interface uses degrees for ease of use.
 */
template <CanBeFieldOfViewComponent Type> class FieldOfView {
private:
  Type _upDegrees;    ///< Vertical FOV above the forward direction in degrees
  Type _upRadians;    ///< Vertical FOV above the forward direction in radians
  Type _downDegrees;  ///< Vertical FOV below the forward direction in degrees
  Type _downRadians;  ///< Vertical FOV below the forward direction in radians
  Type _leftDegrees;  ///< Horizontal FOV to the left of the forward direction
                      ///< in degrees
  Type _leftRadians;  ///< Horizontal FOV to the left of the forward direction
                      ///< in radians
  Type _rightDegrees; ///< Horizontal FOV to the right of the forward direction
                      ///< in degrees
  Type _rightRadians; ///< Horizontal FOV to the right of the forward direction
                      ///< in radians

  /**
   * @brief Validate a field-of-view angle value.
   * @param value Angle value to validate.
   * @param name Angle name used in error messages.
   * @throws std::invalid_argument if angle is negative or not finite.
   */
  static void validateAngle(const Type value, const char *name) {
    if (!std::isfinite(value)) {
      throw std::invalid_argument(std::string(name) + " angle must be finite");
    }
    if (value < Type{0}) {
      throw std::invalid_argument(std::string(name) + " angle must be >= 0");
    }
  }

  /**
   * @brief Convert degrees to radians.
   * @param degrees Angle in degrees.
   * @return Angle in radians.
   */
  static Type toRadians(const Type degrees) {
    return degrees * std::numbers::pi_v<Type> / Type{180};
  }

  /**
   * @brief Convert radians to degrees.
   * @param radians Angle in radians.
   * @return Angle in degrees.
   */
  static Type toDegrees(const Type radians) {
    return radians * Type{180} / std::numbers::pi_v<Type>;
  }

  /**
   * @brief Set one angle from degrees and update radians cache.
   * @param degrees Storage slot for degrees.
   * @param radians Storage slot for radians.
   * @param value Value in degrees.
   * @param name Angle name used in validation errors.
   */
  static void setFromDegrees(Type &degrees, Type &radians, const Type value,
                             const char *name) {
    validateAngle(value, name);
    degrees = value;
    radians = toRadians(value);
  }

  /**
   * @brief Set one angle from radians and update degrees cache.
   * @param degrees Storage slot for degrees.
   * @param radians Storage slot for radians.
   * @param value Value in radians.
   * @param name Angle name used in validation errors.
   */
  static void setFromRadians(Type &degrees, Type &radians, const Type value,
                             const char *name) {
    validateAngle(value, name);
    radians = value;
    degrees = toDegrees(value);
  }

public:
  /**
   * @brief Default constructor initializing all FOV angles to 0 degrees.
   */
  FieldOfView(void) : FieldOfView(Type{0}, Type{0}, Type{0}, Type{0}) {}

  /**
   * @brief Constructor to initialize field of view angles in degrees.
   * @param upDegrees Vertical FOV above the forward direction in degrees.
   * @param downDegrees Vertical FOV below the forward direction in degrees.
   * @param leftDegrees Horizontal FOV to the left of the forward direction in
   * degrees.
   * @param rightDegrees Horizontal FOV to the right of the forward direction in
   * degrees.
   */
  FieldOfView(Type upDegrees, Type downDegrees, Type leftDegrees,
              Type rightDegrees)
      : _upDegrees(upDegrees), _downDegrees(downDegrees),
        _leftDegrees(leftDegrees), _rightDegrees(rightDegrees) {
    setFromDegrees(_upDegrees, _upRadians, upDegrees, "up");
    setFromDegrees(_downDegrees, _downRadians, downDegrees, "down");
    setFromDegrees(_leftDegrees, _leftRadians, leftDegrees, "left");
    setFromDegrees(_rightDegrees, _rightRadians, rightDegrees, "right");
  }

  /**
   * @brief Copy constructor.
   * @param other The FieldOfView object to copy from.
   */
  FieldOfView(const FieldOfView &other) = default;

  /**
   * @brief Move constructor.
   * @param other The FieldOfView object to move from.
   */
  FieldOfView(FieldOfView &&other) noexcept = default;

  /**
   * @brief Copy assignment operator.
   * @param other The FieldOfView object to copy from.
   * @return A reference to this FieldOfView object.
   */
  FieldOfView &operator=(const FieldOfView &other) = default;

  /**
   * @brief Move assignment operator.
   * @param other The FieldOfView object to move from.
   * @return A reference to this FieldOfView object.
   */
  FieldOfView &operator=(FieldOfView &&other) noexcept = default;

  /**
   * @brief Default destructor for FieldOfView.
   */
  ~FieldOfView(void) = default;

  /**
   * @brief Set up field-of-view in degrees.
   * @param upDegrees Up angle in degrees.
   * @return Reference to this FieldOfView.
   */
  FieldOfView &setUpDegrees(const Type upDegrees) {
    setFromDegrees(_upDegrees, _upRadians, upDegrees, "up");
    return *this;
  }

  /**
   * @brief Get up field-of-view in degrees.
   * @return Up angle in degrees.
   */
  Type getUpDegrees(void) const noexcept { return _upDegrees; }

  /**
   * @brief Set up field-of-view in radians.
   * @param upRadians Up angle in radians.
   * @return Reference to this FieldOfView.
   */
  FieldOfView &setUpRadians(const Type upRadians) {
    setFromRadians(_upDegrees, _upRadians, upRadians, "up");
    return *this;
  }

  /**
   * @brief Get up field-of-view in radians.
   * @return Up angle in radians.
   */
  Type getUpRadians(void) const noexcept { return _upRadians; }

  /**
   * @brief Set down field-of-view in degrees.
   * @param downDegrees Down angle in degrees.
   * @return Reference to this FieldOfView.
   */
  FieldOfView &setDownDegrees(const Type downDegrees) {
    setFromDegrees(_downDegrees, _downRadians, downDegrees, "down");
    return *this;
  }

  /**
   * @brief Get down field-of-view in degrees.
   * @return Down angle in degrees.
   */
  Type getDownDegrees(void) const noexcept { return _downDegrees; }

  /**
   * @brief Set down field-of-view in radians.
   * @param downRadians Down angle in radians.
   * @return Reference to this FieldOfView.
   */
  FieldOfView &setDownRadians(const Type downRadians) {
    setFromRadians(_downDegrees, _downRadians, downRadians, "down");
    return *this;
  }

  /**
   * @brief Get down field-of-view in radians.
   * @return Down angle in radians.
   */
  Type getDownRadians(void) const noexcept { return _downRadians; }

  /**
   * @brief Set left field-of-view in degrees.
   * @param leftDegrees Left angle in degrees.
   * @return Reference to this FieldOfView.
   */
  FieldOfView &setLeftDegrees(const Type leftDegrees) {
    setFromDegrees(_leftDegrees, _leftRadians, leftDegrees, "left");
    return *this;
  }

  /**
   * @brief Get left field-of-view in degrees.
   * @return Left angle in degrees.
   */
  Type getLeftDegrees(void) const noexcept { return _leftDegrees; }

  /**
   * @brief Set left field-of-view in radians.
   * @param leftRadians Left angle in radians.
   * @return Reference to this FieldOfView.
   */
  FieldOfView &setLeftRadians(const Type leftRadians) {
    setFromRadians(_leftDegrees, _leftRadians, leftRadians, "left");
    return *this;
  }

  /**
   * @brief Get left field-of-view in radians.
   * @return Left angle in radians.
   */
  Type getLeftRadians(void) const noexcept { return _leftRadians; }

  /**
   * @brief Set right field-of-view in degrees.
   * @param rightDegrees Right angle in degrees.
   * @return Reference to this FieldOfView.
   */
  FieldOfView &setRightDegrees(const Type rightDegrees) {
    setFromDegrees(_rightDegrees, _rightRadians, rightDegrees, "right");
    return *this;
  }

  /**
   * @brief Get right field-of-view in degrees.
   * @return Right angle in degrees.
   */
  Type getRightDegrees(void) const noexcept { return _rightDegrees; }

  /**
   * @brief Set right field-of-view in radians.
   * @param rightRadians Right angle in radians.
   * @return Reference to this FieldOfView.
   */
  FieldOfView &setRightRadians(const Type rightRadians) {
    setFromRadians(_rightDegrees, _rightRadians, rightRadians, "right");
    return *this;
  }

  /**
   * @brief Get right field-of-view in radians.
   * @return Right angle in radians.
   */
  Type getRightRadians(void) const noexcept { return _rightRadians; }

  /**
   * @brief Set all directions from degrees.
   * @param upDegrees Up angle in degrees.
   * @param downDegrees Down angle in degrees.
   * @param leftDegrees Left angle in degrees.
   * @param rightDegrees Right angle in degrees.
   * @return Reference to this FieldOfView.
   */
  FieldOfView &setDegrees(const Type upDegrees, const Type downDegrees,
                          const Type leftDegrees, const Type rightDegrees) {
    setUpDegrees(upDegrees);
    setDownDegrees(downDegrees);
    setLeftDegrees(leftDegrees);
    setRightDegrees(rightDegrees);
    return *this;
  }

  /**
   * @brief Set all directions from radians.
   * @param upRadians Up angle in radians.
   * @param downRadians Down angle in radians.
   * @param leftRadians Left angle in radians.
   * @param rightRadians Right angle in radians.
   * @return Reference to this FieldOfView.
   */
  FieldOfView &setRadians(const Type upRadians, const Type downRadians,
                          const Type leftRadians, const Type rightRadians) {
    setUpRadians(upRadians);
    setDownRadians(downRadians);
    setLeftRadians(leftRadians);
    setRightRadians(rightRadians);
    return *this;
  }
};

/**
 * @brief Type alias for single-precision field-of-view component.
 */
using FieldOfViewF = FieldOfView<float>;

/**
 * @brief Type alias for double-precision field-of-view component.
 */
using FieldOfViewD = FieldOfView<double>;

} // namespace utility::graphic
