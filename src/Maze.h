#ifndef MAZE_H
#define MAZE_H

#include "MazeTile.h"
#include "Bitmap.h"

using namespace std;

class Maze {
 private:
	MazeTile *tiles;
	int width;
	int height;
 public:
	int get_width();
	int get_height();
	MazeTile *get_tile(int, int);
	void generate();
	void from_bitmap(Bitmap*);
	Bitmap* to_bitmap();
	Maze(int, int);
	Maze(Bitmap*);
};

#endif
