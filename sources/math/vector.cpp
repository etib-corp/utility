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

#include "utility/math/vector.hpp"

namespace utility::math
{
	std::ostream &operator<<(std::ostream &stream, const Vector2F &vector)
	{
		stream << "Vector2F(" << vector[VEC_X] << ", " << vector[VEC_Y] << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, const Vector2D &vector)
	{
		stream << "Vector2D(" << vector[VEC_X] << ", " << vector[VEC_Y] << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, const Vector2I &vector)
	{
		stream << "Vector2I(" << vector[VEC_X] << ", " << vector[VEC_Y] << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, const Vector2UI &vector)
	{
		stream << "Vector2UI(" << vector[VEC_X] << ", " << vector[VEC_Y] << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, const Vector3F &vector)
	{
		stream << "Vector3F(" << vector[VEC_X] << ", " << vector[VEC_Y] << ", "
			   << vector[VEC_Z] << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, const Vector3D &vector)
	{
		stream << "Vector3D(" << vector[VEC_X] << ", " << vector[VEC_Y] << ", "
			   << vector[VEC_Z] << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, const Vector3I &vector)
	{
		stream << "Vector3I(" << vector[VEC_X] << ", " << vector[VEC_Y] << ", "
			   << vector[VEC_Z] << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, const Vector3UI &vector)
	{
		stream << "Vector3UI(" << vector[VEC_X] << ", " << vector[VEC_Y] << ", "
			   << vector[VEC_Z] << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, const Vector4F &vector)
	{
		stream << "Vector4F(" << vector[VEC_X] << ", " << vector[VEC_Y] << ", "
			   << vector[VEC_Z] << ", " << vector[VEC_W] << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, const Vector4D &vector)
	{
		stream << "Vector4D(" << vector[VEC_X] << ", " << vector[VEC_Y] << ", "
			   << vector[VEC_Z] << ", " << vector[VEC_W] << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, const Vector4I &vector)
	{
		stream << "Vector4I(" << vector[VEC_X] << ", " << vector[VEC_Y] << ", "
			   << vector[VEC_Z] << ", " << vector[VEC_W] << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, const Vector4UI &vector)
	{
		stream << "Vector4UI(" << vector[VEC_X] << ", " << vector[VEC_Y] << ", "
			   << vector[VEC_Z] << ", " << vector[VEC_W] << ")";
		return stream;
	}
}	 // namespace utility::math