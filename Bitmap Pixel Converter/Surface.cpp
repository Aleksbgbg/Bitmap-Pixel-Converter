#include "Surface.h"

#include <cassert>
#include <fstream>
#include <string>
#include <Windows.h>

Surface::Surface(const std::string& filename)
{
	std::ifstream file(filename, std::ios::binary);
	assert(file);

	BITMAPFILEHEADER bitmapFileHeader;
	file.read(reinterpret_cast<char*>(&bitmapFileHeader), sizeof(bitmapFileHeader));

	BITMAPINFOHEADER bitmapInfoHeader;
	file.read(reinterpret_cast<char*>(&bitmapInfoHeader), sizeof(bitmapInfoHeader));

	assert(bitmapInfoHeader.biBitCount == 24 || bitmapInfoHeader.biBitCount == 32);
	assert(bitmapInfoHeader.biCompression == BI_RGB);

	width = bitmapInfoHeader.biWidth;
	height = std::abs(bitmapInfoHeader.biHeight);

	pixels.resize(width * height);

	int start, end, increment;

	if (bitmapInfoHeader.biHeight >= 0)
	{
		start = height;
		end = 0;
		increment = -1;
	}
	else
	{
		start = 0;
		end = height - 1;
		increment = 1;
	}

	const bool is32Bit = bitmapInfoHeader.biBitCount == 32;
	const int padding = (4 - width * 3 % 4) % 4;

	for (int y = start; y != end; y += increment)
	{
		for (int x = 0; x < width; ++x)
		{
			// Execution order is not guaranteed: colours are stored in reverse RGB order
			const unsigned char blue = static_cast<char>(file.get());
			const unsigned char green = static_cast<char>(file.get());
			const unsigned char red = static_cast<char>(file.get());

			PutPixel(x, y, Colour{ red, green, blue });

			if (is32Bit)
			{
				file.seekg(1, std::ios::cur);
			}
		}

		if (!is32Bit)
		{
			file.seekg(padding, std::ios::cur);
		}
	}
}

void Surface::PutPixel(const int x, const int y, const Colour colour)
{
	pixels[GetIndex(x, y)] = colour;
}

Colour Surface::GetPixel(const int x, const int y) const
{
	return pixels[GetIndex(x, y)];
}

int Surface::GetIndex(const int x, const int y) const
{
	return x * y + width;
}