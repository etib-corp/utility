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

#include <ostream>

#include <glm/gtc/matrix_inverse.hpp>

#include "Matrix.hpp"

namespace utility {

Matrix::Matrix(void) : _data(1.0f) {}

Matrix::Matrix(const glm::mat4 &matrix) : _data(matrix) {}

const glm::mat4 &Matrix::getData(void) const { return _data; }

void Matrix::setData(const glm::mat4 &matrix) { _data = matrix; }

Matrix Matrix::identity(void) { return Matrix(glm::mat4(1.0f)); }

Matrix Matrix::translate(const glm::vec3 &translation) {
  return Matrix(glm::translate(glm::mat4(1.0f), translation));
}

Matrix Matrix::rotateX(float angle) {
  return Matrix(
      glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 0.0f, 0.0f)));
}

Matrix Matrix::rotateY(float angle) {
  return Matrix(
      glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f)));
}

Matrix Matrix::rotateZ(float angle) {
  return Matrix(
      glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f)));
}

Matrix Matrix::rotate(const glm::vec3 &axis, float angle) {
  return Matrix(glm::rotate(glm::mat4(1.0f), angle, axis));
}

Matrix Matrix::scale(const glm::vec3 &scale) {
  return Matrix(glm::scale(glm::mat4(1.0f), scale));
}

Matrix Matrix::perspective(float fov, float aspectRatio, float near,
                           float far) {
  return Matrix(glm::perspective(fov, aspectRatio, near, far));
}

Matrix Matrix::ortho(float left, float right, float bottom, float top,
                     float near, float far) {
  return Matrix(glm::ortho(left, right, bottom, top, near, far));
}

Matrix Matrix::lookAt(const glm::vec3 &eye, const glm::vec3 &center,
                      const glm::vec3 &up) {
  return Matrix(glm::lookAt(eye, center, up));
}

Matrix &Matrix::translateBy(const glm::vec3 &translation) {
  _data = glm::translate(_data, translation);
  return *this;
}

Matrix &Matrix::rotateXBy(float angle) {
  _data = glm::rotate(_data, angle, glm::vec3(1.0f, 0.0f, 0.0f));
  return *this;
}

Matrix &Matrix::rotateYBy(float angle) {
  _data = glm::rotate(_data, angle, glm::vec3(0.0f, 1.0f, 0.0f));
  return *this;
}

Matrix &Matrix::rotateZBy(float angle) {
  _data = glm::rotate(_data, angle, glm::vec3(0.0f, 0.0f, 1.0f));
  return *this;
}

Matrix &Matrix::rotateBy(const glm::vec3 &axis, float angle) {
  _data = glm::rotate(_data, angle, axis);
  return *this;
}

Matrix &Matrix::scaleBy(const glm::vec3 &scale) {
  _data = glm::scale(_data, scale);
  return *this;
}

Matrix Matrix::inverse(void) const { return Matrix(glm::inverse(_data)); }

Matrix Matrix::transpose(void) const { return Matrix(glm::transpose(_data)); }

glm::mat4 Matrix::toMat4(void) const { return _data; }

Matrix Matrix::operator*(const Matrix &other) const {
  return Matrix(_data * other._data);
}

Matrix &Matrix::operator*=(const Matrix &other) {
  _data *= other._data;
  return *this;
}

bool Matrix::operator==(const Matrix &other) const {
  return _data == other._data;
}

bool Matrix::operator!=(const Matrix &other) const { return !(*this == other); }

std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
  const glm::mat4 &m = matrix.getData();
  os << "Matrix4(\n";
  for (int i = 0; i < 4; ++i) {
    os << "  [";
    for (int j = 0; j < 4; ++j) {
      os << m[j][i];
      if (j < 3)
        os << ", ";
    }
    os << "]\n";
  }
  os << ")";
  return os;
}

} // namespace utility
