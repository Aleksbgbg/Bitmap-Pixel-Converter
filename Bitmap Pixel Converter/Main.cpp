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

int main()
{
	std::string bitmapPath;
	const Surface image{ get_bitmap_stream(bitmapPath) };

	std::ofstream putpixelFile{ bitmapPath.substr(0, bitmapPath.find_last_of('.')) + ".cpp" };

	return 0;
}