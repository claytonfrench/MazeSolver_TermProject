#include "Color.h"
#include "Bitmap.h"
#include <string>
#include <fstream>

using namespace std;

Bitmap::Bitmap(string filename)
{
	this->filename = filename;
	this->set_size(0, 0);
}

Bitmap::Bitmap(string filename, int width, int height)
{
	this->filename = filename;
	this->set_size(width, height);
}

Bitmap::~Bitmap()
{
	delete [] this->pixels;
}

int Bitmap::get_width()
{
	return this->width;
}

int Bitmap::get_height()
{
	return this->height;
}

Color *Bitmap::get_pixel(int x, int y)
{
	return &this->pixels[y * this->width + x];
}

void Bitmap::set_size(int width, int height)
{
	this->width = width;
	this->height = height;
	int num_pixels = this->width * this->height;
	if (this->pixels != NULL)
		delete [] this->pixels;
	this->pixels = new Color[num_pixels];
}

void Bitmap::set_pixel(int x, int y, byte r, byte g, byte b)
{
	int index = y * this->width + x;
	this->pixels[index].red = r;
	this->pixels[index].green = g;
	this->pixels[index].blue = b;
}

void Bitmap::set_pixel_black(int x, int y)
{
	this->set_pixel(x, y, 0, 0, 0);
}

void Bitmap::set_pixel_white(int x, int y)
{
	this->set_pixel(x, y, 255, 255, 255);
}

// read a little endian 4 byte integer from stream
int Bitmap::read_int(istream *stream)
{
	byte a = stream->get();
	byte b = stream->get();
	byte c = stream->get();
	byte d = stream->get();
	return a | (b << 8) | (c << 16) | (d << 24);
}

// read a little endian 2 byte integer from stream
int Bitmap::read_short(istream *stream)
{
	byte a = stream->get();
	byte b = stream->get();
	return a | (b << 8);
}

// write a little endian 4 byte integer to stream
void Bitmap::write_int(ostream *stream, int v)
{
	stream->put(v & 0xff);
	stream->put(v >> 8 & 0xff);
	stream->put(v >> 16 & 0xff);
	stream->put(v >> 24 & 0xff);
}

// write a little endian 2 byte integer to stream
void Bitmap::write_short(ostream *stream, int v)
{
	stream->put(v & 0xff);
	stream->put(v >> 8 & 0xff);
}

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
