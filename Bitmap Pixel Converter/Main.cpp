#include "Surface.h"

#include <fstream>
#include <iostream>
#include <string>

std::ifstream get_bitmap_stream(std::string& bitmapPath)
{
	while (true)
	{
		std::cout << "Enter bitmap path: ";

		std::getline(std::cin, bitmapPath);

		if (bitmapPath.find('.') != std::string::npos && bitmapPath.substr(bitmapPath.find_last_of('.')) == ".bmp")
		{
			std::ifstream bitmapFile{ bitmapPath, std::ios::binary };

			if (bitmapFile)
			{
				return bitmapFile;
			}
		}

		std::cout << "File is not good.\n\n";
	}
}

Colour get_ignore_colour()
{
	std::cout << "Enter colour to ignore (0 == black (none); FF00FF == magenta): ";

	std::string ignoreColourString;

	std::cin >> ignoreColourString;
	
	return Colour{ std::stoul(ignoreColourString, nullptr, 16) };
}

int main()
{
	std::string bitmapPath;
	const Surface image{ get_bitmap_stream(bitmapPath) };

	const Colour ignoreColour{ get_ignore_colour() };

	std::ofstream putpixelFile{ bitmapPath.substr(0, bitmapPath.find_last_of('.')) + ".cpp" };

	for (int y = 0; y < image.GetHeight(); ++y)
	{
		for (int x = 0; x < image.GetWidth(); ++x)
		{
			Colour pixel = image.GetPixel(x, y);

			if (ignoreColour.CompareIgnoreAlpha(pixel))
			{
				continue;
			}

			putpixelFile
				<< "gfx.PutPixel("
				<< (x == 0 ? "x" : "x + " + std::to_string(x))
				<< ", "
				<< (y == 0 ? "y" : "y + " + std::to_string(y))
				<< ", Color{ "
				<< pixel.GetRed()
				<< ", "
				<< pixel.GetGreen()
				<< ", "
				<< pixel.GetBlue()
				<< " });\n";
		}
	}

	return 0;
}