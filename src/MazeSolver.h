#ifndef MAZESOLVER_H
#define MAZESOLVER_H

#include "Maze.h"
#include <unordered_set>

using namespace std;

class MazeSolver {
private:
	int start_x;
	int start_y;
	int end_x;
	int end_y;
	Maze *maze;
	unordered_set<MazeTile*> solution;
public:
	int get_start_x();
	int get_start_y();
	int get_end_x();
	int get_end_y();

	void set_positions(bool);
	void solve_maze();
	bool solve(MazeTile*, unordered_set<MazeTile*>&, bool**);
	void print_maze();

	MazeSolver(Maze*);
	MazeSolver(Maze*, bool);
};

#endif
