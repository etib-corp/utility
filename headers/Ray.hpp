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

#include "Vector.hpp"

namespace utility {

/**
 * @brief Ray class for ray-casting and intersection testing
 *
 * Represents a ray defined by an origin point and a direction vector.
 */
class Ray {
private:
  Vector<float, 3> _origin;
  Vector<float, 3> _direction;

public:
  /**
   * @brief Construct a ray with origin at (0,0,0) and direction (0,0,1)
   */
  Ray(void);

  /**
   * @brief Construct a ray with specified origin and direction
   *
   * @param origin The ray origin point
   * @param direction The ray direction (will be normalized)
   */
  Ray(const Vector<float, 3> &origin, const Vector<float, 3> &direction);

  /**
   * @brief Default destructor
   */
  ~Ray(void) = default;

  /**
   * @brief Set the origin of the ray
   *
   * @param origin The new origin point
   */
  void setOrigin(const Vector<float, 3> &origin);

  /**
   * @brief Get the origin of the ray
   *
   * @return const Vector<float, 3>& The origin point
   */
  const Vector<float, 3> &getOrigin(void) const;

  /**
   * @brief Set the direction of the ray (will be normalized)
   *
   * @param direction The new direction
   */
  void setDirection(const Vector<float, 3> &direction);

  /**
   * @brief Get the direction of the ray (normalized)
   *
   * @return const Vector<float, 3>& The normalized direction
   */
  const Vector<float, 3> &getDirection(void) const;

  /**
   * @brief Get a point on the ray at a given distance from the origin
   *
   * @param distance The distance along the ray
   * @return Vector<float, 3> The point at the given distance
   */
  Vector<float, 3> getPointAtDistance(float distance) const;

  /**
   * @brief Test intersection with a sphere
   *
   * @param sphereCenter The center of the sphere
   * @param sphereRadius The radius of the sphere
   * @param outDistance Output parameter for the distance to intersection
   * (optional)
   * @return bool True if the ray intersects the sphere
   */
  bool intersectSphere(const Vector<float, 3> &sphereCenter, float sphereRadius,
                       float *outDistance = nullptr) const;

  /**
   * @brief Test intersection with a plane
   *
   * @param planeNormal The normal vector of the plane
   * @param planePoint A point on the plane
   * @param outDistance Output parameter for the distance to intersection
   * (optional)
   * @return bool True if the ray intersects the plane
   */
  bool intersectPlane(const Vector<float, 3> &planeNormal,
                      const Vector<float, 3> &planePoint,
                      float *outDistance = nullptr) const;

  /**
   * @brief Test intersection with a triangle
   *
   * @param v1 First vertex of the triangle
   * @param v2 Second vertex of the triangle
   * @param v3 Third vertex of the triangle
   * @param outDistance Output parameter for the distance to intersection
   * (optional)
   * @return bool True if the ray intersects the triangle
   */
  bool intersectTriangle(const Vector<float, 3> &v1, const Vector<float, 3> &v2,
                         const Vector<float, 3> &v3,
                         float *outDistance = nullptr) const;

  /**
   * @brief Equality operator
   *
   * @param other The other ray
   * @return bool True if equal
   */
  bool operator==(const Ray &other) const;

  /**
   * @brief Inequality operator
   *
   * @param other The other ray
   * @return bool True if not equal
   */
  bool operator!=(const Ray &other) const;
};

/**
 * @brief Stream insertion operator for Ray
 */
std::ostream &operator<<(std::ostream &os, const Ray &ray);

} // namespace utility

#include <iostream>
