#include "Surface.h"

#include <fstream>
#include <iostream>
#include <string>

std::ifstream get_bitmap_stream()
{
	while (true)
	{
		std::cout << "Enter bitmap path: ";

		std::string bitmapPath;

		std::getline(std::cin, bitmapPath);

		std::ifstream bitmapFile{ bitmapPath, std::ios::binary };

		if (bitmapFile)
		{
			return bitmapFile;
		}

		std::cout << "File is not good.\n\n";
	}
}

int main()
{
	const Surface image{ get_bitmap_stream() };

	return 0;
}