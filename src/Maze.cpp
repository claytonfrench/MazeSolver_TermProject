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

void Maze::generate()
{
	// ToDo: Implement
}

void Maze::from_bitmap(Bitmap* bitmap)
{
	// ToDo: Implement
}

Bitmap *Maze::to_bitmap()
{
	// ToDo: Implement
	return NULL;
}

Maze::Maze(int height, int width)
{
	this->height = height;
	this->width = width;
	grid = new MazeTile**[height];

	for (int i = 0; i < height; i++) {
		grid[i] = new MazeTile*[width];
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			grid[i][j] = NULL;
		}
	}
}

Maze::~Maze()
{
	//Deletes MazeTile pointers
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < height; j++) {
			delete grid[i][j];
		}
	}

	//Deletes row entries (1D array of MazeTile pointers)
	for (int i = 0; i < height; i++) {
		delete[] grid[i];
	}

	delete[] grid;
}

Maze::Maze(Bitmap *bitmap)
{
	height = bitmap->get_height();
	width = bitmap->get_width();
	// ToDo: Implement
}
