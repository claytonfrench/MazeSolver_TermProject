#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "MazeTile.h"
#include "Bitmap.h"

using namespace std;

class Maze {
protected:
    MazeTile ***grid; // 2d array of MazeTile pointers
	int width;
	int height;
public:
    // Accessors
    int get_width();
    int get_height();
    MazeTile *get_tile(int, int);

    // Maze generation methods
    virtual void generate();
	bool valid_cell(int, int);
    void remove_wall(MazeTile*, MazeTile*);

    // Formatting
    void print_maze();
	Bitmap *to_bitmap();

    // Constructors/Destructors
	Maze(int, int);
    ~Maze();
};

#endif
