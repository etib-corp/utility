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
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

#include <glm/matrix.hpp>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include <glm/mat2x2.hpp>
#include <glm/mat2x3.hpp>
#include <glm/mat2x4.hpp>
#include <glm/mat3x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat3x4.hpp>
#include <glm/mat4x2.hpp>
#include <glm/mat4x3.hpp>
#include <glm/mat4x4.hpp>

namespace utility::math {

using glm::determinant;
using glm::inverse;
using glm::matrixCompMult;
using glm::outerProduct;
using glm::transpose;

using glm::frustum;
using glm::infinitePerspective;
using glm::ortho;
using glm::perspective;
using glm::perspectiveFov;
using glm::perspectiveLH;
using glm::perspectiveRH;
using glm::tweakedInfinitePerspective;

using glm::identity;
using glm::lookAt;
using glm::lookAtLH;
using glm::lookAtRH;
using glm::rotate;
using glm::scale;
using glm::translate;

/**
 * @brief Concept to constrain matrix component type.
 * @tparam Type Candidate component type.
 */
template <typename Type>
concept CanBeMatrixComponent = std::is_floating_point_v<Type>;

/**
 * @brief M x N matrix class inheriting from glm::mat<Cols, Rows, Type>.
 *
 * @tparam MatrixComponentType Floating-point type for matrix components.
 * @tparam Cols Number of columns (must be 2, 3, or 4).
 * @tparam Rows Number of rows (must be 2, 3, or 4).
 */
template <CanBeMatrixComponent MatrixComponentType, std::size_t Cols,
          std::size_t Rows,
          typename = std::enable_if_t<(Cols >= 2) && (Cols <= 4) &&
                                      (Rows >= 2) && (Rows <= 4)>>
class Matrix : public glm::mat<Cols, Rows, MatrixComponentType> {
public:
  /**
   * @brief Default constructor initializing matrix to identity (if square) or
   * zero (if not square).
   */
  Matrix(void)
      : glm::mat<Cols, Rows, MatrixComponentType>(Cols == Rows ? 1 : 0) {}

  /**
   * @brief Construct from initializer list of Cols*Rows values (column-major
   * order).
   * @param values The initializer list containing matrix components.
   * @throws std::invalid_argument if the list size is not Cols*Rows.
   */
  Matrix(std::initializer_list<MatrixComponentType> values) {
    if (values.size() != Cols * Rows) {
      throw std::invalid_argument("Matrix requires exactly " +
                                  std::to_string(Cols * Rows) + " components");
    }
    const auto it = values.begin();
    for (std::size_t col = 0; col < Cols; ++col) {
      for (std::size_t row = 0; row < Rows; ++row) {
        (*this)[col][row] = *(it + col * Rows + row);
      }
    }
  }

  /**
   * @brief Construct by filling all components with the same value.
   * @param value The value to fill all components with.
   */
  explicit Matrix(MatrixComponentType value)
      : glm::mat<Cols, Rows, MatrixComponentType>(value) {}

  /**
   * @brief Construct from a GLM matrix.
   * @param value Source matrix.
   */
  Matrix(const glm::mat<Cols, Rows, MatrixComponentType> &value)
      : glm::mat<Cols, Rows, MatrixComponentType>(value) {}

  /**
   * @brief Copy constructor.
   * @param other The Matrix object to copy from.
   */
  Matrix(const Matrix &other) = default;

  /**
   * @brief Move constructor.
   * @param other The Matrix object to move from.
   */
  Matrix(Matrix &&other) noexcept = default;

  /**
   * @brief Copy assignment operator.
   * @param other The Matrix object to copy from.
   * @return A reference to this Matrix object.
   */
  Matrix &operator=(const Matrix &other) = default;

  /**
   * @brief Move assignment operator.
   * @param other The Matrix object to move from.
   * @return A reference to this Matrix object.
   */
  Matrix &operator=(Matrix &&other) noexcept = default;

  /**
   * @brief Default destructor for Matrix.
   */
  ~Matrix(void) = default;
};

/**
 * @brief Type alias for 2x2 single-precision matrix.
 */
using Matrix2x2F = Matrix<float, 2, 2>;

/**
 * @brief Type alias for 2x2 double-precision matrix.
 */
using Matrix2x2D = Matrix<double, 2, 2>;

/**
 * @brief Type alias for 2x3 single-precision matrix.
 */
using Matrix2x3F = Matrix<float, 2, 3>;

/**
 * @brief Type alias for 2x3 double-precision matrix.
 */
using Matrix2x3D = Matrix<double, 2, 3>;

/**
 * @brief Type alias for 2x4 single-precision matrix.
 */
using Matrix2x4F = Matrix<float, 2, 4>;

/**
 * @brief Type alias for 2x4 double-precision matrix.
 */
using Matrix2x4D = Matrix<double, 2, 4>;

/**
 * @brief Type alias for 3x2 single-precision matrix.
 */
using Matrix3x2F = Matrix<float, 3, 2>;

/**
 * @brief Type alias for 3x2 double-precision matrix.
 */
using Matrix3x2D = Matrix<double, 3, 2>;

/**
 * @brief Type alias for 3x3 single-precision matrix.
 */
using Matrix3x3F = Matrix<float, 3, 3>;

/**
 * @brief Type alias for 3x3 double-precision matrix.
 */
using Matrix3x3D = Matrix<double, 3, 3>;

/**
 * @brief Type alias for 3x4 single-precision matrix.
 */
using Matrix3x4F = Matrix<float, 3, 4>;

/**
 * @brief Type alias for 3x4 double-precision matrix.
 */
using Matrix3x4D = Matrix<double, 3, 4>;

/**
 * @brief Type alias for 4x2 single-precision matrix.
 */
using Matrix4x2F = Matrix<float, 4, 2>;

/**
 * @brief Type alias for 4x2 double-precision matrix.
 */
using Matrix4x2D = Matrix<double, 4, 2>;

/**
 * @brief Type alias for 4x3 single-precision matrix.
 */
using Matrix4x3F = Matrix<float, 4, 3>;

/**
 * @brief Type alias for 4x3 double-precision matrix.
 */
using Matrix4x3D = Matrix<double, 4, 3>;

/**
 * @brief Type alias for 4x4 single-precision matrix.
 */
using Matrix4x4F = Matrix<float, 4, 4>;

/**
 * @brief Type alias for 4x4 double-precision matrix.
 */
using Matrix4x4D = Matrix<double, 4, 4>;

} // namespace utility::math
