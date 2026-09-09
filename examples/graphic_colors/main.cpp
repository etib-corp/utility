#include <iostream>

#include <utility/graphic/color.hpp>

int main(void)
{
	using utility::graphic::ColorFloat;

	const ColorFloat foreground { 1.0f, 0.25f, 0.0f, 0.5f };
	const ColorFloat background { 0.0f, 0.25f, 1.0f };
	const auto blended = foreground.blendOver(background);
	const auto gray	   = blended.grayscale();

	std::cout << "blended color: " << blended << "\n";
	std::cout << "grayscale color: " << gray << "\n";

	return 0;
}