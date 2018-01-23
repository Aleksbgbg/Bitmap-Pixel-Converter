#pragma once

class Colour
{
public:
	Colour() = default;
	explicit Colour(const unsigned int value);
	Colour(const unsigned char alpha, const unsigned char red, const unsigned char green, const unsigned char blue);
	Colour(const unsigned char red, const unsigned char green, const unsigned char blue);
	
public:
	bool operator ==(const Colour& source) const;

public:
	bool CompareIgnoreAlpha(const Colour& source) const;
	
	unsigned int GetAlpha() const;
	unsigned int GetRed() const;
	unsigned int GetGreen() const;
	unsigned int GetBlue() const;

private:
	const unsigned int value = 0;
};