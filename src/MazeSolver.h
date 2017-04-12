#ifndef MAZESOLVER_H
#define MAZESOLVER_H

#include "Maze.h"

using namespace std;

class MazeSolver {
 private:
	int x;
	int y;
	bool *visited_tile;
	Maze *maze;
 public:
	void solve_maze();
	void move_to_next_tile();
	bool is_solved();
	MazeSolver(Maze*);
};

#endif
