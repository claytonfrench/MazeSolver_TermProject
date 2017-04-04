#ifndef COLOR_H
#define COLOR_H

typedef unsigned char byte;

class Color {
 private:
	byte grayscale_average();
 public:
	Color();
	Color (byte, byte, byte);
	byte red;
	byte green;
	byte blue;
	bool is_black();
	bool is_white();
};

#endif
