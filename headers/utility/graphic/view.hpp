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
#include <ostream>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <ostream>

#include "utility/graphic/field_of_view.hpp"
#include "utility/graphic/pose.hpp"
#include "utility/graphic/ray.hpp"

namespace utility::graphic
{

	/**
	 * @brief Concept to ensure the type can be used as a view component.
	 * @tparam ViewComponentType The type to check.
	 */
	template<typename ViewComponentType>
	concept CanBeViewComponent = CanBeFieldOfViewComponent<ViewComponentType>
		&& CanBePoseComponent<ViewComponentType>
		&& CanBeRayComponent<ViewComponentType>;

	/**
	 * @brief 3D perspective view with floating-point components.
	 * @tparam ViewComponentType Floating-point type for view parameters and
	 * vectors.
	 */
	template<CanBeViewComponent ViewComponentType> class View
	{
		private:
		Pose<ViewComponentType> _pose;	  //< View position and orientation

		FieldOfView<ViewComponentType>
			_fieldOfView;	 ///< View field-of-view parameters

		math::Vector<ViewComponentType, 2>
			_viewportSize;	  ///< Viewport size in pixels (width, height)

		ViewComponentType _nearPlane;	 ///< Near clipping plane distance
		ViewComponentType _farPlane;	 ///< Far clipping plane distance

		/**
		 * @brief Validate perspective parameter constraints.
		 * @param verticalFovDegrees Vertical field-of-view in degrees.
		 * @param aspectRatio Aspect ratio (width/height).
		 * @throws std::invalid_argument if any perspective parameter is
		 * invalid.
		 */
		static void validatePerspective(ViewComponentType verticalFovRadians,
										ViewComponentType aspectRatio)
		{
			if (verticalFovRadians <= ViewComponentType {}
				|| verticalFovRadians
					>= std::numbers::pi_v<ViewComponentType>) {
				throw std::invalid_argument(
					"View vertical FOV must be in range (0, pi) radians");
			}

			if (aspectRatio <= ViewComponentType {}) {
				throw std::invalid_argument(
					"View aspect ratio must be positive");
			}
		}

		/**
		 * @brief Build symmetric per-direction FOV from vertical angle and
		 * aspect.
		 * @param verticalFovDegrees Vertical field-of-view in degrees.
		 * @param aspectRatio Aspect ratio (width/height).
		 * @return Symmetric field-of-view values for all directions.
		 */
		static FieldOfView<ViewComponentType>
			makeSymmetricFieldOfView(ViewComponentType verticalFovRadians,
									 ViewComponentType aspectRatio)
		{
			const ViewComponentType halfVertical =
				verticalFovRadians / ViewComponentType { 2 };

			const ViewComponentType halfHorizontal =
				std::atan(std::tan(halfVertical) * aspectRatio);

			return FieldOfView<ViewComponentType>(
				-halfVertical, halfVertical, -halfHorizontal, halfHorizontal);
		}

		/**
		 * @brief Validate orientation vectors for use as view basis.
		 * @param forward Forward direction candidate.
		 * @param up Up direction candidate.
		 * @throws std::invalid_argument if vectors are zero or collinear.
		 */
		static void validateOrientation(
			const math::Vector<ViewComponentType, 3> &forward,
			const math::Vector<ViewComponentType, 3> &up)
		{
			if (math::dot(forward, forward) == ViewComponentType {}) {
				throw std::invalid_argument(
					"View forward vector must be non-zero");
			}
			if (math::dot(up, up) == ViewComponentType {}) {
				throw std::invalid_argument("View up vector must be non-zero");
			}
			if (math::dot(math::cross(forward, up), math::cross(forward, up))
				== ViewComponentType {}) {
				throw std::invalid_argument(
					"View forward and up vectors must not be collinear");
			}
		}

		/**
		 * @brief Convert and normalize stored quaternion components to view
		 * type.
		 * @return Normalized quaternion components in xyzw order.
		 */
		math::Vector<ViewComponentType, 4> normalizedRotationComponents() const
		{
			const auto normalized = _pose.getOrientation().normalized();
			return math::Vector<ViewComponentType, 4> {
				static_cast<ViewComponentType>(normalized.x),
				static_cast<ViewComponentType>(normalized.y),
				static_cast<ViewComponentType>(normalized.z),
				static_cast<ViewComponentType>(normalized.w)
			};
		}

		/**
		 * @brief Rotate a vector by the view quaternion.
		 * @param vector Input vector.
		 * @return Rotated vector.
		 */
		math::Vector<ViewComponentType, 3> rotateVectorByRotation(
			const math::Vector<ViewComponentType, 3> &vector) const
		{
			const auto q = normalizedRotationComponents();
			const math::Vector<ViewComponentType, 3> u { q[0], q[1], q[2] };
			const ViewComponentType s = q[3];

			return u * (ViewComponentType { 2 } * math::dot(u, vector))
				+ vector.operator*(s * s - math::dot(u, u))
				+ math::cross(u, vector) * (ViewComponentType { 2 } * s);
		}

		public:
		/**
		 * @brief Default constructor with common perspective defaults.
		 */
		View(void)
			: _pose()
			, _fieldOfView()
			, _viewportSize()
			, _nearPlane(ViewComponentType { 1.0 })
			, _farPlane(ViewComponentType { 1000.0 })
		{
		}

		/**
		 * @brief Construct view from explicit quaternion orientation.
		 * @param pose View world-space position and orientation.
		 * @param fov View field-of-view parameters.
		 * @param viewportSize Viewport size in pixels (width, height).
		 * @param nearPlane Near clipping plane distance.
		 * @param farPlane Far clipping plane distance.
		 * @throws std::invalid_argument if perspective values or quaternion are
		 * invalid.
		 */
		View(Pose<ViewComponentType> pose,
			 utility::graphic::FieldOfView<ViewComponentType> fov,
			 math::Vector<ViewComponentType, 2> viewportSize,
			 ViewComponentType nearPlane, ViewComponentType farPlane)
			: _pose(std::move(pose))
			, _fieldOfView(std::move(fov))
			, _viewportSize(std::move(viewportSize))
			, _nearPlane(nearPlane)
			, _farPlane(farPlane)
		{
		}

		/**
		 * @brief Copy constructor.
		 * @param other View instance to copy from.
		 */
		View(const View &other) = default;

		/**
		 * @brief Move constructor.
		 * @param other View instance to move from.
		 */
		View(View &&other) noexcept = default;

		/**
		 * @brief Copy assignment operator.
		 * @param other View instance to copy from.
		 * @return Reference to this view.
		 */
		View &operator=(const View &other) = default;

		/**
		 * @brief Move assignment operator.
		 * @param other View instance to move from.
		 * @return Reference to this view.
		 */
		View &operator=(View &&other) noexcept = default;

		/**
		 * @brief Destructor.
		 */
		~View(void) = default;

		/**
		 * @brief Set view world-space pose.
		 * @param pose New view pose (position and orientation).
		 */
		void setPose(const Pose<ViewComponentType> &pose)
		{
			_pose = pose;
		}

		/**
		 * @brief Get view world-space pose.
		 * @return Pose object containing position and orientation.
		 */
		Pose<ViewComponentType> getPose(void) const
		{
			return _pose;
		}

		/**
		 * @brief Get normalized forward direction.
		 * @return Forward direction vector.
		 */
		math::Vector<ViewComponentType, 3> getForward(void) const
		{
			return math::normalize(
				rotateVectorByRotation(math::Vector<ViewComponentType, 3> {
					ViewComponentType {}, ViewComponentType {},
					ViewComponentType { -1 } }));
		}

		/**
		 * @brief Get normalized up direction.
		 * @return Up direction vector.
		 */
		math::Vector<ViewComponentType, 3> getUp(void) const
		{
			return math::normalize(rotateVectorByRotation(
				math::Vector<ViewComponentType, 3> { ViewComponentType {},
													 ViewComponentType { 1 },
													 ViewComponentType {} }));
		}

		/**
		 * @brief Set perspective projection parameters.
		 * @param verticalFovRadians Total vertical field-of-view in radians.
		 * @param aspectRatio Aspect ratio (width / height).
		 * @throws std::invalid_argument if any perspective parameter is
		 * invalid.
		 */
		void setPerspective(ViewComponentType verticalFovRadians,
							ViewComponentType aspectRatio)
		{
			validatePerspective(verticalFovRadians, aspectRatio);
			_fieldOfView =
				makeSymmetricFieldOfView(verticalFovRadians, aspectRatio);
		}

		/**
		 * @brief Get aspect ratio (width/height).
		 * @return Aspect ratio.
		 */
		ViewComponentType getAspectRatio() const
		{
			const ViewComponentType vertical = std::tan(_fieldOfView.getUp())
				- std::tan(_fieldOfView.getDown());
			const ViewComponentType horizontal =
				std::tan(_fieldOfView.getRight())
				- std::tan(_fieldOfView.getLeft());
			if (vertical == ViewComponentType {}) {
				return ViewComponentType {};
			}
			return horizontal / vertical;
		}

		/**
		 * @brief Set per-direction field-of-view values.
		 * @param fieldOfView Field-of-view values.
		 */
		void setFieldOfView(const FieldOfView<ViewComponentType> &fieldOfView)
		{
			_fieldOfView = fieldOfView;
		}

		/**
		 * @brief Get field-of-view values.
		 * @return Field-of-view object.
		 */
		FieldOfView<ViewComponentType> getFieldOfView(void) const
		{
			return _fieldOfView;
		}

		/**
		 * @brief Compute view right direction from orientation basis.
		 * @return Normalized right direction vector.
		 */
		math::Vector<ViewComponentType, 3> getRight(void) const
		{
			return math::normalize(rotateVectorByRotation(
				math::Vector<ViewComponentType, 3> { ViewComponentType { 1 },
													 ViewComponentType {},
													 ViewComponentType {} }));
		}

		/**
		 * @brief Set near and far clipping plane distances.
		 * @param nearDistance Near clipping plane distance.
		 * @param farDistance Far clipping plane distance.
		 */

		void setClippingPlanes(ViewComponentType nearDistance,
							   ViewComponentType farDistance)
		{
			if (nearDistance <= ViewComponentType { 0 }) {
				throw std::invalid_argument("Near plane must be > 0");
			}
			if (farDistance <= nearDistance) {
				throw std::invalid_argument("Far plane must be > near plane");
			}

			_nearPlane = nearDistance;
			_farPlane  = farDistance;
		}

		/**
		 * @brief Get near clipping plane distance.
		 * @return Near clipping plane distance.
		 */
		ViewComponentType getNearPlane() const noexcept
		{
			return _nearPlane;
		}

		/**
		 * @brief Get far clipping plane distance.
		 * @return Far clipping plane distance.
		 */
		ViewComponentType getFarPlane() const noexcept
		{
			return _farPlane;
		}

		/**
		 * @brief Translate view position by an offset.
		 * @param offset Translation vector.
		 */
		void move(const math::Vector<ViewComponentType, 3> &offset)
		{
			_pose.translate(Position<ViewComponentType>(offset));
		}

		/**
		 * @brief Return translated view copy.
		 * @param offset Translation vector.
		 * @return View copy with updated position.
		 */
		View moved(const math::Vector<ViewComponentType, 3> &offset) const
		{
			View result(*this);
			result.move(offset);
			return result;
		}

		/**
		 * @brief Create a world-space ray from normalized device coordinates.
		 * @param ndcX Horizontal coordinate in range [-1, 1].
		 * @param ndcY Vertical coordinate in range [-1, 1].
		 * @return Ray originating at view position toward projected direction.
		 */
		Ray<ViewComponentType> viewRay(ViewComponentType ndcX,
									   ViewComponentType ndcY) const
		{
			const auto tx0 = std::tan(_fieldOfView.getLeft());
			const auto tx1 = std::tan(_fieldOfView.getRight());
			const auto ty0 = std::tan(_fieldOfView.getDown());
			const auto ty1 = std::tan(_fieldOfView.getUp());

			const ViewComponentType horizontalOffset =
				((ndcX + ViewComponentType { 1 }) * ViewComponentType { 0.5 })
					* (tx1 - tx0)
				+ tx0;

			const ViewComponentType verticalOffset =
				((ndcY + ViewComponentType { 1 }) * ViewComponentType { 0.5 })
					* (ty1 - ty0)
				+ ty0;

			const auto rayDirection = getForward()
				+ getRight() * horizontalOffset + getUp() * verticalOffset;

			return Ray<ViewComponentType>(_pose.getPosition(),
										  math::normalize(rayDirection));
		}

		/**
		 * @brief Create a world-space ray from viewport pixel coordinates.
		 * @param point Viewport coordinate in pixels (origin at top-left).
		 * @return Ray originating at view position toward projected direction.
		 * @throws std::out_of_range if point is outside of viewport bounds.
		 */
		Ray<ViewComponentType> viewPointToRay(
			const math::Vector<ViewComponentType, 2> &point) const
		{
			if (point.x < 0 || point.y < 0 || point.x >= _viewportSize.x
				|| point.y >= _viewportSize.y) {
				throw std::out_of_range(
					"View point is outside of viewport bounds");
			}

			const ViewComponentType ndcX =
				(static_cast<ViewComponentType>(point.x) / _viewportSize.x)
					* ViewComponentType { 2 }
				- ViewComponentType { 1 };

			const ViewComponentType ndcY = ViewComponentType { 1 }
				- (static_cast<ViewComponentType>(point.y) / _viewportSize.y)
					* ViewComponentType { 2 };

			return viewRay(ndcX, ndcY);
		}

		/**
		 * @brief Get total vertical field-of-view in radians.
		 * @return Vertical FOV in radians.
		 */

		ViewComponentType getVerticalFovRadians() const noexcept
		{
			return _fieldOfView.getUp() - _fieldOfView.getDown();
		}

		/**
		 * @brief Get total horizontal field-of-view in radians.
		 * @return Horizontal FOV in radians.
		 */
		ViewComponentType getHorizontalFovRadians() const noexcept
		{
			return _fieldOfView.getRight() - _fieldOfView.getLeft();
		}
		/**
		 * @brief Check whether current field-of-view is symmetric.
		 * @param epsilon Absolute tolerance.
		 * @return True when up/down and left/right are approximately equal.
		 */
		bool isFieldOfViewSymmetric(
			ViewComponentType epsilon = ViewComponentType {
				1e-6 }) const noexcept
		{
			return _fieldOfView.isSymmetric(epsilon);
		}

		/**
		 * @brief Create a ray going through the center of the viewport.
		 * @return Center view ray.
		 */
		Ray<ViewComponentType> centerRay(void) const
		{
			return viewRay(0, 0);
		}

		/**
		 * @brief Equality comparison.
		 * @param other View to compare with.
		 * @return True when pose and field-of-view are equal.
		 */
		bool operator==(const View &other) const noexcept
		{
			return _pose == other._pose
				&& _fieldOfView.getUp() == other._fieldOfView.getUp()
				&& _fieldOfView.getDown() == other._fieldOfView.getDown()
				&& _fieldOfView.getLeft() == other._fieldOfView.getLeft()
				&& _fieldOfView.getRight() == other._fieldOfView.getRight();
		}

		/**
		 * @brief Inequality comparison.
		 * @param other View to compare with.
		 * @return True when pose or field-of-view differ.
		 */
		bool operator!=(const View &other) const noexcept
		{
			return !(*this == other);
		}

		/**
		 * @brief Set viewport size in pixels.
		 * @param viewportSize Viewport size (width, height).
		 */
		void setViewportSize(
			const math::Vector<ViewComponentType, 2> &viewportSize)
		{
			_viewportSize = viewportSize;
		}

		/**
		 * @brief Get viewport size in pixels.
		 * @return Viewport size (width, height).
		 */
		math::Vector<ViewComponentType, 2> getViewportSize(void) const
		{
			return _viewportSize;
		}

		/**
		 * @brief Convert view to a GLM-compatible 4x4 view matrix.
		 * @return 4x4 view matrix in column-major order.
		 */
		utility::math::Matrix<ViewComponentType, 4, 4> toViewMatrix(void) const
		{
			const auto orientation = _pose.getOrientation();
			const auto position	   = _pose.getPosition();

			utility::math::Matrix<ViewComponentType, 4, 4> view = glm::inverse(
				glm::translate(glm::identity<glm::mat4>(),
							   glm::vec3(position.x, position.y, position.z))
				* glm::mat4_cast(glm::quat(orientation.w, orientation.x,
										   orientation.y, orientation.z)));

			// GLM is column-major: view[col][row]
			// view[0][0] = static_cast<ViewComponentType>(right[0]);
			// view[0][1] = static_cast<ViewComponentType>(up[0]);
			// view[0][2] = static_cast<ViewComponentType>(-forward[0]);
			// view[0][3] = static_cast<ViewComponentType>(0);

			// view[1][0] = static_cast<ViewComponentType>(right[1]);
			// view[1][1] = static_cast<ViewComponentType>(up[1]);
			// view[1][2] = static_cast<ViewComponentType>(-forward[1]);
			// view[1][3] = static_cast<ViewComponentType>(0);

			// view[2][0] = static_cast<ViewComponentType>(right[2]);
			// view[2][1] = static_cast<ViewComponentType>(up[2]);
			// view[2][2] = static_cast<ViewComponentType>(-forward[2]);
			// view[2][3] = static_cast<ViewComponentType>(0);

			// view[3][0] =
			// 	-static_cast<ViewComponentType>(math::dot(right, position));
			// view[3][1] =
			// 	-static_cast<ViewComponentType>(math::dot(up, position));
			// view[3][2] =
			// 	static_cast<ViewComponentType>(math::dot(forward, position));
			// view[3][3] = static_cast<ViewComponentType>(1);

			return view;
		}

		/**
		 * @brief Build a perspective projection matrix from per-side field of
		 * view angles.
		 * @return 4x4 projection matrix in column-major order.
		 * @throws std::invalid_argument if clipping planes are invalid or FOV
		 * produces a degenerate frustum.
		 */
		utility::math::Matrix<ViewComponentType, 4, 4>
			getProjectionMatrix() const
		{
			const ViewComponentType tanLeft = std::tan(_fieldOfView.getLeft());
			const ViewComponentType tanRight =
				std::tan(_fieldOfView.getRight());
			const ViewComponentType tanUp	= std::tan(_fieldOfView.getUp());
			const ViewComponentType tanDown = std::tan(_fieldOfView.getDown());

			const ViewComponentType width  = tanRight - tanLeft;
			const ViewComponentType height = tanUp - tanDown;

			utility::math::Matrix<ViewComponentType, 4, 4> projection = {};

			projection[0][0] = static_cast<ViewComponentType>(2) / width;
			projection[1][1] = static_cast<ViewComponentType>(2) / height;
			projection[2][0] = (tanRight + tanLeft) / width;
			projection[2][1] = (tanUp + tanDown) / height;
			projection[2][2] = -_farPlane / (_farPlane - _nearPlane);
			projection[2][3] = -static_cast<ViewComponentType>(1);
			projection[3][2] =
				-(_farPlane * _nearPlane) / (_farPlane - _nearPlane);
			projection[3][3] = static_cast<ViewComponentType>(0);

			projection[1][1] *=
				static_cast<ViewComponentType>(-1);	   // Invert Y for Vulkan

			return projection;
		}
	};

	/**
	 * @brief Type alias for single-precision view component.
	 */
	using ViewF = View<float>;

	/**
	 * @brief Type alias for double-precision view component.
	 */
	using ViewD = View<double>;

	/**
	 * @brief Stream insertion operator for View.
	 * @param stream Output stream.
	 * @param view View to output.
	 * @return Reference to the output stream.
	 */
	std::ostream &operator<<(std::ostream &stream, const ViewF &view);

	/**
	 * @brief Stream insertion operator for View.
	 * @param stream Output stream.
	 * @param view View to output.
	 * @return Reference to the output stream.
	 */
	std::ostream &operator<<(std::ostream &stream, const ViewD &view);

}	 // namespace utility::graphic
