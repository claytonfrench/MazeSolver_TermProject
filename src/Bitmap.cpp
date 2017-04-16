#include "Color.h"
#include "Bitmap.h"
#include <string>
#include <fstream>

using namespace std;

/**
 * @brief constructs empty bitmap with no pixels defined
 * @param filename is the name of the file to read or write from
 */
Bitmap::Bitmap(string filename)
{
	this->filename = filename;
	this->pixels = NULL;
	this->set_size(0, 0);
}

/**
 * @brief constructs empty bitmap with no pixels defined
 * @param filename is the name of the file to read or write from
 */
Bitmap::Bitmap(string filename, int width, int height)
{
	this->filename = filename;
	this->pixels = NULL;
	this->set_size(width, height);
}

/**
 * @brief deletes all pixel data
 */
Bitmap::~Bitmap()
{
	if (this->pixels != NULL)
		delete [] this->pixels;
}

/**
 * @brief gets the width of the bitmap
 * @return width of bitmap in pixels
 */
int Bitmap::get_width()
{
	return this->width;
}

/**
 * @brief gets the height of the bitmap
 * @return heigt of bitmap in pixels
 */
int Bitmap::get_height()
{
	return this->height;
}

Color *Bitmap::get_pixel(int x, int y)
{
	return &this->pixels[y * this->width + x];
}


/**
 * @brief sets the dimensions of the bitmap, resets all pixels
 * @param width is the new width of the bitmap in pixels
 * @param height is the new height of the bitmap in pixels
 * @return void
 */
void Bitmap::set_size(int width, int height)
{
	this->width = width;
	this->height = height;
	int num_pixels = this->width * this->height;
	if (this->pixels != NULL)
		delete [] this->pixels;
	this->pixels = new Color[num_pixels];
}

/**
 * @brief sets a pixel's color in the bitmap
 * @param x is the x-coordinate in pixels
 * @param y is the y-coordinate in pixels
 * @param r is amount of red
 * @param g is amount of green
 * @param b is amount of blue
 * @return void
 */
void Bitmap::set_pixel(int x, int y, byte r, byte g, byte b)
{
	int index = y * this->width + x;
	this->pixels[index].red = r;
	this->pixels[index].green = g;
	this->pixels[index].blue = b;
}

/**
 * @brief sets a pixel to black
 * @param x is the x-coordinate in pixels
 * @param y is the y-coordinate in pixels
 * @return void
 */
void Bitmap::set_pixel_black(int x, int y)
{
	this->set_pixel(x, y, 0, 0, 0);
}

/**
 * @brief sets a pixel to white
 * @param x is the x-coordinate in pixels
 * @param y is the y-coordinate in pixels
 * @return void
 */
void Bitmap::set_pixel_white(int x, int y)
{
	this->set_pixel(x, y, 255, 255, 255);
}

/**
 * @brief read a little endian 4 byte integer from stream
 * @param stream is the stream to read from
 * @return the integer value read
 */
int Bitmap::read_int(istream *stream)
{
	byte a = stream->get();
	byte b = stream->get();
	byte c = stream->get();
	byte d = stream->get();
	return a | (b << 8) | (c << 16) | (d << 24);
}

/**
 * @brief read a little endian 2 byte integer from stream
 * @param stream is the stream to read from
 * @return the integer value read
 */
int Bitmap::read_short(istream *stream)
{
	byte a = stream->get();
	byte b = stream->get();
	return a | (b << 8);
}

/**
 * @brief write a little endian 4 byte integer to stream
 * @param stream is the stream to write to
 * @param v is the integer value to write
 * @return void
 */
void Bitmap::write_int(ostream *stream, int v)
{
	stream->put(v & 0xff);
	stream->put(v >> 8 & 0xff);
	stream->put(v >> 16 & 0xff);
	stream->put(v >> 24 & 0xff);
}

/**
 * @brief write a little endian 2 byte integer to stream
 * @param stream is the stream to write to
 * @param v is the integer value to write
 * @return void
 */
void Bitmap::write_short(ostream *stream, int v)
{
	stream->put(v & 0xff);
	stream->put(v >> 8 & 0xff);
}

/**
 * @brief reads the bitmap data from a Windows NT .bmp file
 * @return void
 */
void Bitmap::read_file()
{
	ifstream file(this->filename.c_str(), ios_base::in | ios_base::binary);
	if (! file.is_open()) {
		throw string("File can't be opened !");
	}
	byte magic_b = file.get();
	byte magic_m = file.get();
	if (magic_b != 'B' || magic_m != 'M')
		throw string("File is not a windows bitmap file !");
	// file size
	this->read_int(&file);
	// useless 4 bytes
	this->read_int(&file);
	int start_offset = this->read_int(&file);
	// header size
	this->read_int(&file);
	int w = read_int(&file);
	int h = read_int(&file);
	if (read_short(&file) != 1)
		throw string("Incorrect number of color planes");
	if (read_short(&file) != 24)
		throw string("Must be 24 bit colors");
	if (read_int(&file) != 0)
		throw string("Image is compressed !");
	// jump to pixel data
	file.seekg(start_offset);
	this->set_size(w, h);
	// each row is padded to be divisible by 4 bytes
	// this is accounting for that
	int extra_bytes = this->width * 3 % 4;
	if (extra_bytes > 0)
		extra_bytes = 4 - extra_bytes;
	// read the data
	// we count backwards because that is how it is encoded
	for (int y = this->height - 1; y >= 0; y--) {
		for (int x = 0; x < this->width; x++) {
			int index = y * this->width + x;
			// is little endian
			this->pixels[index].blue = file.get();
			this->pixels[index].green = file.get();
			this->pixels[index].red = file.get();
		}
		// move onto next row
		for (int i = 0; i < extra_bytes; i++) {
			file.get();
		}
	}
	file.close();
}

/**
 * @brief writes the bitmap data to a file, in the Windows NT .bmp file format
 * @return void
 */
void Bitmap::write_file()
{
	ofstream file(this->filename.c_str(), ios_base::out | ios_base::binary);
	if (! file.is_open()) {
		throw string("File can't be opened !");
	}
	file.put('B');
	file.put('M');
	int extra_bytes = this->width * 3 % 4;
	if (extra_bytes > 0)
		extra_bytes = 4 - extra_bytes;
	// expected file size
	// (54 is the size of the headers)
	int image_data_size = (this->width * 3 + extra_bytes) * this->height;
	this->write_int(&file, image_data_size + 54);
	// useless bytes
	this->write_int(&file, 0);
	// entry point for pixel data
	this->write_int(&file, 54);
	// size of windows nt header
	this->write_int(&file, 40);
	this->write_int(&file, this->width);
	this->write_int(&file, this->height);
	// number of color planes
	this->write_short(&file, 1);
	// bits per pixel
	this->write_short(&file, 24);
	// compression level (zero = none)
	this->write_int(&file, 0);
	this->write_int(&file, image_data_size);
	// palette info, zero uses default
	this->write_int(&file, 0);
	this->write_int(&file, 0);
	this->write_int(&file, 0);
	this->write_int(&file, 0);

	for (int y = this->height - 1; y >= 0; y--) {
		for (int x = 0; x < this->width; x++) {
			int index = y * this->width + x;
			file.put(this->pixels[index].blue);
			file.put(this->pixels[index].green);
			file.put(this->pixels[index].red);
		}
		// pad extra space in row with zeros
		for (int i = 0; i < extra_bytes; i++) {
			file.put(0);
		}
	}
	file.close();
}
