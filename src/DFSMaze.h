#ifndef DFSMAZE_H
#define DFSMAZE_H

#include "Maze.h"

using namespace std;

class DFSMaze : public Maze {
private:
	int startingRow;
	int startingCol;
public:
	char find_available_neighbor(int, int);
	void generate_maze(int, int);
	DFSMaze(int, int);
};

#endif
