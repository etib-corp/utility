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

#include "utility/math/matrix.hpp"

namespace utility::math
{
	std::ostream &operator<<(std::ostream &stream, const Matrix2x2F &matrix)
	{
		stream << "Matrix2x2F(";
		for (std::size_t row = 0; row < 2; ++row) {
			stream << "[";
			for (std::size_t col = 0; col < 2; ++col) {
				stream << matrix[col][row];
				if (col < 1) {
					stream << ", ";
				}
			}
			stream << "]";
			if (row < 1) {
				stream << ", ";
			}
		}
		stream << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, const Matrix2x2D &matrix)
	{
		stream << "Matrix2x2D(";
		for (std::size_t row = 0; row < 2; ++row) {
			stream << "[";
			for (std::size_t col = 0; col < 2; ++col) {
				stream << matrix[col][row];
				if (col < 1) {
					stream << ", ";
				}
			}
			stream << "]";
			if (row < 1) {
				stream << ", ";
			}
		}
		stream << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, const Matrix2x3F &matrix)
	{
		stream << "Matrix2x3F(";
		for (std::size_t row = 0; row < 2; ++row) {
			stream << "[";
			for (std::size_t col = 0; col < 3; ++col) {
				stream << matrix[col][row];
				if (col < 2) {
					stream << ", ";
				}
			}
			stream << "]";
			if (row < 1) {
				stream << ", ";
			}
		}
		stream << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, const Matrix2x3D &matrix)
	{
		stream << "Matrix2x3D(";
		for (std::size_t row = 0; row < 2; ++row) {
			stream << "[";
			for (std::size_t col = 0; col < 3; ++col) {
				stream << matrix[col][row];
				if (col < 2) {
					stream << ", ";
				}
			}
			stream << "]";
			if (row < 1) {
				stream << ", ";
			}
		}
		stream << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, const Matrix3x2F &matrix)
	{
		stream << "Matrix3x2F(";
		for (std::size_t row = 0; row < 3; ++row) {
			stream << "[";
			for (std::size_t col = 0; col < 2; ++col) {
				stream << matrix[col][row];
				if (col < 1) {
					stream << ", ";
				}
			}
			stream << "]";
			if (row < 2) {
				stream << ", ";
			}
		}
		stream << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, const Matrix3x2D &matrix)
	{
		stream << "Matrix3x2D(";
		for (std::size_t row = 0; row < 3; ++row) {
			stream << "[";
			for (std::size_t col = 0; col < 2; ++col) {
				stream << matrix[col][row];
				if (col < 1) {
					stream << ", ";
				}
			}
			stream << "]";
			if (row < 2) {
				stream << ", ";
			}
		}
		stream << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, const Matrix3x3F &matrix)
	{
		stream << "Matrix3x3F(";
		for (std::size_t row = 0; row < 3; ++row) {
			stream << "[";
			for (std::size_t col = 0; col < 3; ++col) {
				stream << matrix[col][row];
				if (col < 2) {
					stream << ", ";
				}
			}
			stream << "]";
			if (row < 2) {
				stream << ", ";
			}
		}
		stream << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, const Matrix3x3D &matrix)
	{
		stream << "Matrix3x3D(";
		for (std::size_t row = 0; row < 3; ++row) {
			stream << "[";
			for (std::size_t col = 0; col < 3; ++col) {
				stream << matrix[col][row];
				if (col < 2) {
					stream << ", ";
				}
			}
			stream << "]";
			if (row < 2) {
				stream << ", ";
			}
		}
		stream << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, const Matrix3x4F &matrix)
	{
		stream << "Matrix3x4F(";
		for (std::size_t row = 0; row < 3; ++row) {
			stream << "[";
			for (std::size_t col = 0; col < 4; ++col) {
				stream << matrix[col][row];
				if (col < 3) {
					stream << ", ";
				}
			}
			stream << "]";
			if (row < 2) {
				stream << ", ";
			}
		}
		stream << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, const Matrix3x4D &matrix)
	{
		stream << "Matrix3x4D(";
		for (std::size_t row = 0; row < 3; ++row) {
			stream << "[";
			for (std::size_t col = 0; col < 4; ++col) {
				stream << matrix[col][row];
				if (col < 3) {
					stream << ", ";
				}
			}
			stream << "]";
			if (row < 2) {
				stream << ", ";
			}
		}
		stream << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, const Matrix4x2F &matrix)
	{
		stream << "Matrix4x2F(";
		for (std::size_t row = 0; row < 4; ++row) {
			stream << "[";
			for (std::size_t col = 0; col < 2; ++col) {
				stream << matrix[col][row];
				if (col < 1) {
					stream << ", ";
				}
			}
			stream << "]";
			if (row < 3) {
				stream << ", ";
			}
		}
		stream << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, const Matrix4x2D &matrix)
	{
		stream << "Matrix4x2D(";
		for (std::size_t row = 0; row < 4; ++row) {
			stream << "[";
			for (std::size_t col = 0; col < 2; ++col) {
				stream << matrix[col][row];
				if (col < 1) {
					stream << ", ";
				}
			}
			stream << "]";
			if (row < 3) {
				stream << ", ";
			}
		}
		stream << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, const Matrix4x3F &matrix)
	{
		stream << "Matrix4x3F(";
		for (std::size_t row = 0; row < 4; ++row) {
			stream << "[";
			for (std::size_t col = 0; col < 3; ++col) {
				stream << matrix[col][row];
				if (col < 2) {
					stream << ", ";
				}
			}
			stream << "]";
			if (row < 3) {
				stream << ", ";
			}
		}
		stream << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, const Matrix4x3D &matrix)
	{
		stream << "Matrix4x3D(";
		for (std::size_t row = 0; row < 4; ++row) {
			stream << "[";
			for (std::size_t col = 0; col < 3; ++col) {
				stream << matrix[col][row];
				if (col < 2) {
					stream << ", ";
				}
			}
			stream << "]";
			if (row < 3) {
				stream << ", ";
			}
		}
		stream << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, const Matrix4x4F &matrix)
	{
		stream << "Matrix4x4F(";
		for (std::size_t row = 0; row < 4; ++row) {
			stream << "[";
			for (std::size_t col = 0; col < 4; ++col) {
				stream << matrix[col][row];
				if (col < 3) {
					stream << ", ";
				}
			}
			stream << "]";
			if (row < 3) {
				stream << ", ";
			}
		}
		stream << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, const Matrix4x4D &matrix)
	{
		stream << "Matrix4x4D(";
		for (std::size_t row = 0; row < 4; ++row) {
			stream << "[";
			for (std::size_t col = 0; col < 4; ++col) {
				stream << matrix[col][row];
				if (col < 3) {
					stream << ", ";
				}
			}
			stream << "]";
			if (row < 3) {
				stream << ", ";
			}
		}
		stream << ")";
		return stream;
	}

}	 // namespace utility::math
