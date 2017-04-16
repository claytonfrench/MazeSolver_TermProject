#include <iostream>
#include <cstdlib>
#include "Maze.h"

int Maze::get_width()
{
	return this->width;
}

int Maze::get_height()
{
	return this->height;
}

MazeTile *Maze::get_tile(int x, int y)
{
	return grid[x][y];
}

void Maze::print_maze()
{
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < width; k++) {
				if (j == 0) {
					if (grid[i][k]->north) {
						cout << "-----";
					} else {
						cout << "     ";
					}
				} else {
					if (grid[i][k]->west) {
						cout << "| ";
					} else if (!grid[i][k]->west) {
						cout << "  ";
					}
					cout << "X";
					if (grid[i][k]->east) {
						if (k == width - 1) {
							cout << " |";
						} else {
							cout << "  ";
						}
					} else if (!grid[i][k]->east) {
						cout << "  ";
					}
				}
			}
			cout << endl;
		}
	}

	for (int i = 0; i < width; i++) {
		if (grid[height-1][i]->south) {
			cout << "-----";
		} else {
			cout << "     ";
		}
	}
	cout << endl;
}

void Maze::from_bitmap(Bitmap* bitmap)
{
	// TODO: Implement
}

Bitmap *Maze::to_bitmap()
{
	int w = this->width * 12 + 5;
	int h = this->height * 12 + 5;
	Bitmap *img = new Bitmap("out.bmp", w, h);
	int x, y, tileX, tileY;
	for (x = 0; x < w; x++) {
		for (y = 0; y < h; y++) {
			img->set_pixel(x, y, 0xbb, 0xbb, 0xbb);
		}
	}
	for (y = 1, tileY = 0; tileY < this->height; tileY++, y += 3) {
		for (x = 1, tileX = 0; tileX < this->width; tileX++, x += 3) {
			MazeTile *t = this->get_tile(tileX, tileY);
			if (t->north) {
				img->set_pixel_white(x, y - 1);
			}
			if (t->south) {
				img->set_pixel_white(x, y + 1);
			}
			if (t->east) {
				img->set_pixel_white(x - 1, y);
			}
			if (t->west) {
				img->set_pixel_white(x - 1, y);
			}
			img->set_pixel(x, y, 0x7f, 0x00, 0x7f);
		}
	}
	return img;
}

void Maze::generate()
{
}

Maze::Maze(int width, int height)
{
	this->height = height;
	this->width = width;
	grid = new MazeTile**[height];

	for (int i = 0; i < height; i++) {
		grid[i] = new MazeTile*[width];
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			grid[i][j] = new MazeTile(i, j);
		}
	}

	generate();
}

Maze::~Maze()
{
	//Deletes MazeTile pointers
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			delete grid[i][j];
		}
	}

	//Deletes row entries (1D array of MazeTile pointers)
	for (int i = 0; i < height; i++) {
		delete[] grid[i];
	}

	delete[] grid;
}

bool Maze::valid_cell(int x, int y)
{
	if (x >= 0 && x < height && y >= 0 && y < width) {
		return true;
	}
	return false;
}

Maze::Maze(Bitmap *bitmap)
{
	this->from_bitmap(bitmap);
}
