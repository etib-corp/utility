#include <iostream>

#include <utility/math/matrix.hpp>

int main(void)
{
	utility::math::Matrix2x2F matrix { 4.0f, 7.0f, 2.0f, 6.0f };
	const auto inverse = utility::math::inverse(matrix);

	std::cout << "matrix:\n" << matrix << "\n";
	std::cout << "determinant: " << utility::math::determinant(matrix)
			  << "\n";
	std::cout << "inverse:\n"
			  << inverse[0][0] << ' ' << inverse[1][0] << '\n'
			  << inverse[0][1] << ' ' << inverse[1][1] << '\n';

	return 0;
}