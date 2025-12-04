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

#include "Ray.hpp"
#include <cmath>

namespace utility {

Ray::Ray(void) : _origin(0.0f, 0.0f, 0.0f), _direction(0.0f, 0.0f, 1.0f) {}

Ray::Ray(const Vector<float, 3> &origin, const Vector<float, 3> &direction)
    : _origin(origin), _direction(direction) {
  _direction.normalize();
}

void Ray::setOrigin(const Vector<float, 3> &origin) { _origin = origin; }

const Vector<float, 3> &Ray::getOrigin(void) const { return _origin; }

void Ray::setDirection(const Vector<float, 3> &direction) {
  _direction = direction;
  _direction.normalize();
}

const Vector<float, 3> &Ray::getDirection(void) const { return _direction; }

Vector<float, 3> Ray::getPointAtDistance(float distance) const {
  Vector<float, 3> result = _origin;
  result += _direction * distance;
  return result;
}

bool Ray::intersectSphere(const Vector<float, 3> &sphereCenter,
                          float sphereRadius, float *outDistance) const {
  Vector<float, 3> oc = _origin - sphereCenter;

  float a = _direction.dot(_direction);
  float b = 2.0f * oc.dot(_direction);
  float c = oc.dot(oc) - sphereRadius * sphereRadius;

  float discriminant = b * b - 4.0f * a * c;

  if (discriminant < 0.0f) {
    return false;
  }

  float t = (-b - std::sqrt(discriminant)) / (2.0f * a);

  if (t < 0.0f) {
    t = (-b + std::sqrt(discriminant)) / (2.0f * a);
  }

  if (t < 0.0f) {
    return false;
  }

  if (outDistance != nullptr) {
    *outDistance = t;
  }

  return true;
}

bool Ray::intersectPlane(const Vector<float, 3> &planeNormal,
                         const Vector<float, 3> &planePoint,
                         float *outDistance) const {
  float denom = planeNormal.dot(_direction);

  if (std::abs(denom) < 1e-6f) {
    return false; // Ray is parallel to plane
  }

  Vector<float, 3> diff = planePoint - _origin;
  float t = diff.dot(planeNormal) / denom;

  if (t < 0.0f) {
    return false;
  }

  if (outDistance != nullptr) {
    *outDistance = t;
  }

  return true;
}

bool Ray::intersectTriangle(const Vector<float, 3> &v1,
                            const Vector<float, 3> &v2,
                            const Vector<float, 3> &v3,
                            float *outDistance) const {
  const float EPSILON = 1e-6f;

  Vector<float, 3> edge1 = v2 - v1;
  Vector<float, 3> edge2 = v3 - v1;

  Vector<float, 3> h = _direction.cross(edge2);
  float a = edge1.dot(h);

  if (std::abs(a) < EPSILON) {
    return false; // Ray is parallel to triangle
  }

  float f = 1.0f / a;
  Vector<float, 3> s = _origin - v1;
  float u = f * s.dot(h);

  if (u < 0.0f || u > 1.0f) {
    return false;
  }

  Vector<float, 3> q = s.cross(edge1);
  float v = f * _direction.dot(q);

  if (v < 0.0f || u + v > 1.0f) {
    return false;
  }

  float t = f * edge2.dot(q);

  if (t < 0.0f) {
    return false;
  }

  if (outDistance != nullptr) {
    *outDistance = t;
  }

  return true;
}

bool Ray::operator==(const Ray &other) const {
  return _origin == other._origin && _direction == other._direction;
}

bool Ray::operator!=(const Ray &other) const { return !(*this == other); }

std::ostream &operator<<(std::ostream &os, const Ray &ray) {
  os << "Ray(Origin:" << ray.getOrigin() << ", Direction:" << ray.getDirection()
     << ")";
  return os;
}

} // namespace utility
