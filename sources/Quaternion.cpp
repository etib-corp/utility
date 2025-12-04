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

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Quaternion.hpp"

namespace utility {

Quaternion::Quaternion(void) : _data(1.0f, 0.0f, 0.0f, 0.0f) {}

Quaternion::Quaternion(float w, float x, float y, float z)
    : _data(w, x, y, z) {}

Quaternion::Quaternion(const glm::vec3 &axis, float angle) {
  _data = glm::angleAxis(angle, glm::normalize(axis));
}

Quaternion::Quaternion(const glm::quat &quaternion) : _data(quaternion) {}

const glm::quat &Quaternion::getData(void) const { return _data; }

void Quaternion::setData(const glm::quat &quaternion) { _data = quaternion; }

float Quaternion::getW(void) const { return _data.w; }

float Quaternion::getX(void) const { return _data.x; }

float Quaternion::getY(void) const { return _data.y; }

float Quaternion::getZ(void) const { return _data.z; }

void Quaternion::normalize(void) { _data = glm::normalize(_data); }

Quaternion Quaternion::getNormalized(void) const {
  return Quaternion(glm::normalize(_data));
}

Quaternion Quaternion::conjugate(void) const {
  return Quaternion(glm::conjugate(_data));
}

Quaternion Quaternion::inverse(void) const {
  return Quaternion(glm::inverse(_data));
}

glm::mat4 Quaternion::toMatrix(void) const { return glm::toMat4(_data); }

Quaternion Quaternion::slerp(const Quaternion &other, float t) const {
  return Quaternion(glm::slerp(_data, other._data, t));
}

Quaternion Quaternion::operator*(const Quaternion &other) const {
  return Quaternion(_data * other._data);
}

Quaternion &Quaternion::operator*=(const Quaternion &other) {
  _data *= other._data;
  return *this;
}

bool Quaternion::operator==(const Quaternion &other) const {
  return _data == other._data;
}

bool Quaternion::operator!=(const Quaternion &other) const {
  return !(*this == other);
}

std::ostream &operator<<(std::ostream &os, const Quaternion &quat) {
  os << "Quaternion(W:" << quat.getW() << ", X:" << quat.getX()
     << ", Y:" << quat.getY() << ", Z:" << quat.getZ() << ")";
  return os;
}

} // namespace utility
