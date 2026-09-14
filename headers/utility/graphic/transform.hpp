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

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include <utility/graphic/orientation.hpp>
#include <utility/graphic/pose.hpp>
#include <utility/graphic/scale.hpp>

namespace utility::graphic
{
	/**
	 * @brief Convert an orientation (quaternion) to a rotation matrix.
	 *
	 * The conversion goes through the underlying `glm::qua` base class so the
	 * component order of `utility::math::Quaternion` (x, y, z, w) can never be
	 * confused with glm's `(w, x, y, z)` constructor order.
	 *
	 * @param orientation Rotation to convert.
	 * @return The corresponding 4x4 rotation matrix.
	 */
	inline glm::mat4 orientationToMatrix(const OrientationF &orientation)
	{
		return glm::mat4_cast(
			static_cast<const glm::qua<float> &>(orientation));
	}

	/**
	 * @brief Convert a pose (position + orientation) to a model matrix.
	 *
	 * The returned matrix is `T * R` (no scale) and matches the `glm::mat4`
	 * expected by the per-instance model matrix consumed by `evan`
	 * (`evan::GPUInstance`).
	 *
	 * @param pose World pose of the object.
	 * @return The corresponding model matrix.
	 */
	inline glm::mat4 poseToMatrix(const PoseF &pose)
	{
		const PositionF &position = pose.getPosition();

		return glm::translate(
				   glm::mat4(1.0f),
				   glm::vec3(position.getX(), position.getY(), position.getZ()))
			* orientationToMatrix(pose.getOrientation());
	}

	/**
	 * @brief Build a full model matrix from a pose and a scale.
	 *
	 * The composition order is `T * R * S`: the scale is applied first in
	 * local space, then the rotation, then the translation.
	 *
	 * @param pose World pose of the object.
	 * @param scale Per-axis local scale.
	 * @return The corresponding model matrix.
	 */
	inline glm::mat4 modelMatrix(const PoseF &pose, const ScaleF &scale)
	{
		const PositionF &position = pose.getPosition();

		return glm::translate(
				   glm::mat4(1.0f),
				   glm::vec3(position.getX(), position.getY(), position.getZ()))
			* orientationToMatrix(pose.getOrientation())
			* glm::scale(glm::mat4(1.0f),
						 glm::vec3(scale.getX(), scale.getY(), scale.getZ()));
	}
}	 // namespace utility::graphic
