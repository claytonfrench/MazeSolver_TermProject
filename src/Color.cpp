#include "Color.h"

Color::Color()
{
	this->red = 0;
	this->green = 0;
	this->blue = 0;
}

Color::Color(byte r, byte g, byte b)
{
	this->red = r;
	this->green = r;
	this->blue = b;		
}

// returns average of each color channel
byte Color::grayscale_average()
{
	return (this->red + this->green + this->blue) / 3;
}

// checks if it is `close enough` to black
bool Color::is_black()
{
	return this->grayscale_average() < 127;
}

// checks if it is `close enough` to white
bool Color::is_white()
{
	return this->grayscale_average() > 127;
}
