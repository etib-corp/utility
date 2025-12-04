/*
 Copyright (c) 2025 ETIB Corporation

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

#include <ostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace utility {

/**
 * @brief Wrapper class for transformation matrices
 *
 * Provides convenient methods for common transformations (translation,
 * rotation, scaling) and conversion to/from glm matrices.
 */
class Matrix {
private:
  glm::mat4 _data;

public:
  /**
   * @brief Construct an identity matrix
   */
  Matrix(void);

  /**
   * @brief Construct from a glm::mat4
   *
   * @param matrix The glm::mat4 to copy
   */
  Matrix(const glm::mat4 &matrix);

  /**
   * @brief Default destructor
   */
  ~Matrix(void) = default;

  /**
   * @brief Get the matrix data
   *
   * @return const glm::mat4& The matrix
   */
  const glm::mat4 &getData(void) const;

  /**
   * @brief Set the matrix data
   *
   * @param matrix The new matrix
   */
  void setData(const glm::mat4 &matrix);

  /**
   * @brief Create an identity matrix
   *
   * @return Matrix An identity matrix
   */
  static Matrix identity(void);

  /**
   * @brief Create a translation matrix
   *
   * @param translation The translation vector
   * @return Matrix A translation matrix
   */
  static Matrix translate(const glm::vec3 &translation);

  /**
   * @brief Create a rotation matrix around the X axis
   *
   * @param angle The rotation angle in radians
   * @return Matrix A rotation matrix
   */
  static Matrix rotateX(float angle);

  /**
   * @brief Create a rotation matrix around the Y axis
   *
   * @param angle The rotation angle in radians
   * @return Matrix A rotation matrix
   */
  static Matrix rotateY(float angle);

  /**
   * @brief Create a rotation matrix around the Z axis
   *
   * @param angle The rotation angle in radians
   * @return Matrix A rotation matrix
   */
  static Matrix rotateZ(float angle);

  /**
   * @brief Create a rotation matrix around an arbitrary axis
   *
   * @param axis The rotation axis
   * @param angle The rotation angle in radians
   * @return Matrix A rotation matrix
   */
  static Matrix rotate(const glm::vec3 &axis, float angle);

  /**
   * @brief Create a scale matrix
   *
   * @param scale The scale vector
   * @return Matrix A scale matrix
   */
  static Matrix scale(const glm::vec3 &scale);

  /**
   * @brief Create a perspective projection matrix
   *
   * @param fov Field of view in radians
   * @param aspectRatio The aspect ratio (width / height)
   * @param near The near clipping plane
   * @param far The far clipping plane
   * @return Matrix A perspective projection matrix
   */
  static Matrix perspective(float fov, float aspectRatio, float near,
                            float far);

  /**
   * @brief Create an orthographic projection matrix
   *
   * @param left The left boundary
   * @param right The right boundary
   * @param bottom The bottom boundary
   * @param top The top boundary
   * @param near The near clipping plane
   * @param far The far clipping plane
   * @return Matrix An orthographic projection matrix
   */
  static Matrix ortho(float left, float right, float bottom, float top,
                      float near, float far);

  /**
   * @brief Create a look-at matrix
   *
   * @param eye The eye position
   * @param center The point to look at
   * @param up The up direction
   * @return Matrix A view matrix
   */
  static Matrix lookAt(const glm::vec3 &eye, const glm::vec3 &center,
                       const glm::vec3 &up);

  /**
   * @brief Apply a translation to this matrix
   *
   * @param translation The translation vector
   * @return Matrix& Reference to this matrix
   */
  Matrix &translateBy(const glm::vec3 &translation);

  /**
   * @brief Apply a rotation around X axis to this matrix
   *
   * @param angle The rotation angle in radians
   * @return Matrix& Reference to this matrix
   */
  Matrix &rotateXBy(float angle);

  /**
   * @brief Apply a rotation around Y axis to this matrix
   *
   * @param angle The rotation angle in radians
   * @return Matrix& Reference to this matrix
   */
  Matrix &rotateYBy(float angle);

  /**
   * @brief Apply a rotation around Z axis to this matrix
   *
   * @param angle The rotation angle in radians
   * @return Matrix& Reference to this matrix
   */
  Matrix &rotateZBy(float angle);

  /**
   * @brief Apply a rotation to this matrix
   *
   * @param axis The rotation axis
   * @param angle The rotation angle in radians
   * @return Matrix& Reference to this matrix
   */
  Matrix &rotateBy(const glm::vec3 &axis, float angle);

  /**
   * @brief Apply a scale to this matrix
   *
   * @param scale The scale vector
   * @return Matrix& Reference to this matrix
   */
  Matrix &scaleBy(const glm::vec3 &scale);

  /**
   * @brief Get the inverse of this matrix
   *
   * @return Matrix The inverse matrix
   */
  Matrix inverse(void) const;

  /**
   * @brief Get the transpose of this matrix
   *
   * @return Matrix The transposed matrix
   */
  Matrix transpose(void) const;

  /**
   * @brief Convert to a glm::mat4
   *
   * @return glm::mat4 The matrix
   */
  glm::mat4 toMat4(void) const;

  /**
   * @brief Matrix multiplication operator
   *
   * @param other The other matrix
   * @return Matrix The result of the multiplication
   */
  Matrix operator*(const Matrix &other) const;

  /**
   * @brief Matrix multiplication assignment operator
   *
   * @param other The other matrix
   * @return Matrix& Reference to this matrix
   */
  Matrix &operator*=(const Matrix &other);

  /**
   * @brief Equality operator
   *
   * @param other The other matrix
   * @return bool True if equal
   */
  bool operator==(const Matrix &other) const;

  /**
   * @brief Inequality operator
   *
   * @param other The other matrix
   * @return bool True if not equal
   */
  bool operator!=(const Matrix &other) const;
};

/**
 * @brief Stream insertion operator for Matrix
 */
std::ostream &operator<<(std::ostream &os, const Matrix &matrix);

} // namespace utility

#include <iostream>
