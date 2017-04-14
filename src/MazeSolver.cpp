#include <cstdlib>
#include <iostream>
#include "MazeSolver.h"

void MazeSolver::solve_maze()
{
	// ToDo: Implement
}

void MazeSolver::move_to_next_tile()
{
	// ToDo: Implement
}

bool MazeSolver::is_solved()
{
	// ToDo: Implement
	return false;
}

/*
* Randomly chooses two points on perimeter
* and designates one as START, and one as END
* Note: START is always on the left vertical axis
* and END is always on the right vertical axis
*/
void MazeSolver::set_positions(bool random)
{
	if (random) {
		// Seed RNG
		srand(time(NULL));

		// START on left vertical axis
		this->start_x = rand() % maze->get_height();
		this->start_y = 0;

		// END on right vertical axis
		this->end_x = rand() % maze->get_height();
		this->end_y = maze->get_width() - 1;

		// Break walls for start and end (this is purely cosmetic)
		maze->get_tile(start_x, start_y)->west = false;
		maze->get_tile(end_x, end_y)->east = false;

	} else {
		this->start_x = 0;
		this->start_y = 0;

		this->end_x = maze->get_height() - 1;
		this->end_y = maze->get_width() - 1;

		maze->get_tile(start_x, start_y)->west = false;
		maze->get_tile(end_x, end_y)->east = false;
	}
}

int MazeSolver::get_start_x()
{
	return this->start_x;
}

int MazeSolver::get_start_y()
{
	return this->start_y;
}

int MazeSolver::get_end_x()
{
	return this->end_x;
}

int MazeSolver::get_end_y()
{
	return this->end_y;
}

void MazeSolver::print_maze()
{
	this->maze->print_maze();
}

MazeSolver::MazeSolver(Maze* maze)
{
	this->maze = maze;
}
