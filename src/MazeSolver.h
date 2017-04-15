#ifndef MAZESOLVER_H
#define MAZESOLVER_H

#include "Maze.h"

using namespace std;

class MazeSolver {
private:
	int start_x;
	int start_y;
	int end_x;
	int end_y;
	bool *visited_tile;
	Maze *maze;
public:
	int get_start_x();
	int get_start_y();
	int get_end_x();
	int get_end_y();

	void set_positions(bool);
	void solve_maze();
	void move_to_next_tile();
	void print_maze();
	bool is_solved();

	MazeSolver(Maze*);
};

#endif
