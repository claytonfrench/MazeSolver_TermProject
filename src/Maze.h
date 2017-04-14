#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <iostream>
#include "MazeTile.h"
#include "Bitmap.h"
#include <time.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

class Maze {
private:
    MazeTile ***grid; // 2d array of MazeTile pointers
	int width;
	int height;
public:
    // Accessors
	int get_width();
	int get_height();
	MazeTile *get_tile(int, int);

    // Maze generation methods
	void generate();
    bool valid_cell(int, int);
    void add_neighbors(int, int, vector<MazeTile*>&, bool**);
    void remove_wall(MazeTile*, MazeTile*);

    // Formatting
    void print_maze();
	void from_bitmap(Bitmap*);
	Bitmap *to_bitmap();

    // Constructors/Destructors
	Maze(int, int);
    ~Maze();
	Maze(Bitmap*);
};

#endif
