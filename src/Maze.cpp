#include <iostream>
#include <cstdlib>
#include "Maze.h"

/**
 * @brief gets the width of the maze
 * @return the width as represented by number of tiles
 */
int Maze::get_width()
{
	return this->width;
}

/**
 * @brief gets the height of the maze
 * @return the height as represented by number of tiles
 */
int Maze::get_height()
{
	return this->height;
}

/**
 * @brief gets a tile from the maze
 * @param x is the x-coordinate of the maze by tile number
 * @param y is the y-coordinate of the maze by tile number
 * @return the maze tile
 */
MazeTile *Maze::get_tile(int x, int y)
{
	return grid[x][y];
}

/**
 * @brief prints the maze to stdout
 * @return void
 */
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


/**
 * @brief fills the maze tiles based on data found in a bmp file
 * @return void
 */
void Maze::from_bitmap(Bitmap* bitmap)
{
	// TODO: Implement
}

/**
 * @brief draws the maze to a bitmap file
 * @return the bitmap file
 */
Bitmap *Maze::to_bitmap()
{
	int w = this->width * 2 + 1;
	int h = this->height * 2 + 1;
	Bitmap *img = new Bitmap("out.bmp", w, h);
	int x, y, tileX, tileY;
	for (x = 1, tileY = 0; tileY < this->width; tileY++, x += 2) {
		for (y = 1, tileX = 0; tileX < this->height; tileX++, y += 2) {
			MazeTile *t = this->get_tile(tileX, tileY);
			if (! t->north) {
				img->set_pixel_white(x, y - 1);
			}
			if (! t->south) {
				img->set_pixel_white(x, y + 1);
			}
			if (! t->east) {
				img->set_pixel_white(x + 1, y);
			}
			if (! t->west) {
			 	img->set_pixel_white(x - 1, y);
			}
			img->set_pixel_white(x, y);
		}
	}
	return img;
}

/**
 * @brief randomly generates the maze
 * @return void
 */
void Maze::generate()
{
}

/**
 * @brief creates a new maze with the specified number of tiles
 * @param width is the number of tiles per row
 * @param height is the number of tiles per column
 */
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

/**
 * @brief frees the memory held by the maze tiles
 */
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

/**
 * @brief determines if the specified cell is in the range of the maze
 * @param x is the x-coordinate of the maze by tile number
 * @param y is the y-coordinate of the maze by tile number
 * @return true if the cell is in range, false if not
 */
bool Maze::valid_cell(int x, int y)
{
	if (x >= 0 && x < height && y >= 0 && y < width) {
		return true;
	}
	return false;
}

/**
 * @brief constructs a maze based off a bitmap image
 */
Maze::Maze(Bitmap *bitmap)
{
	this->from_bitmap(bitmap);
}
