#ifndef MAZE_H
#define MAZE_H

#include "MazeTile.h"
#include "Bitmap.h"

using namespace std;

class Maze {
private:
    MazeTile ***grid; //2d array of MazeTile pointers
	int width;
	int height;
public:
	int get_width();
	int get_height();
	MazeTile *get_tile(int, int);
	void generate();
	void from_bitmap(Bitmap*);
	Bitmap *to_bitmap();
	Maze(int, int);
    ~Maze();
	Maze(Bitmap*);
};

#endif
