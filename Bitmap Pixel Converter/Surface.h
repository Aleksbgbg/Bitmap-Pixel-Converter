#pragma once

#include "Colour.h"

#include <string>
#include <vector>

class Surface
{
public:
	explicit Surface(const std::string& filename);
	explicit Surface(std::ifstream file);

public:
	void PutPixel(const int x, const int y, const Colour colour);
	Colour GetPixel(const int x, const int y) const;

	int GetWidth() const;
	int GetHeight() const;
	
private:
	int GetIndex(const int x, const int y) const;

private:
	std::vector<Colour> pixels;

	int width = 0;
	int height = 0;
};