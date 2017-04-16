#include "Color.h"

/**
 * @brief creates a black color / pixel
 */
Color::Color()
{
	this->red = 0;
	this->green = 0;
	this->blue = 0;
}

/**
 * @brief creates specified color
 * @param r is the red value for the color
 * @param g is the green value for the color
 * @param b is the blue value for the color
 */
Color::Color(byte r, byte g, byte b)
{
	this->red = r;
	this->green = r;
	this->blue = b;		
}

/**
 * @brief gets the average of each color channel
 * @return the arithmetic mean of the color channels
 */
byte Color::grayscale_average()
{
	return (this->red + this->green + this->blue) / 3;
}

/**
 * @brief checks if the color is darker than medium gray
 * @return true if the color is darker than gray, or else false
 */
bool Color::is_black()
{
	return this->grayscale_average() < 127;
}

/**
 * @brief checks if the color is lighter than medium gray
 * @return true if the color is lighter than gray, or else false
 */
bool Color::is_white()
{
	return this->grayscale_average() > 127;
}
