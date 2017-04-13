#ifndef BITMAP_H
#define BITMAP_H

#include "Color.h"
#include <string>
#include <istream>

using namespace std;

class Bitmap {
 private:
	Color *pixels;
	string filename;
	int width;
	int height;
	int read_int(istream*);
	int read_short(istream*);
	void write_int(ostream*, int);
	void write_short(ostream*, int);
 public:
	Bitmap(string);
	Bitmap(string, int, int);
	~Bitmap();
	int get_width();
	int get_height();
	void set_size(int, int);
	Color *get_pixel(int, int);
	void set_pixel(int, int, byte, byte, byte);
	void read_file();
	void write_file();
};

#endif
