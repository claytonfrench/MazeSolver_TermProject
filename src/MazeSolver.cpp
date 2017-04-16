#include <cstdlib>
#include <iostream>
#include <vector>
#include "MazeSolver.h"

/**
 * @brief solves maze using a depth-first approach
 * @return void
 */
void MazeSolver::solve_maze()
{

	bool **visited = new bool*[maze->get_height()];
	unordered_set<MazeTile*> solution;

	// Initialize cells visited to false
	for (int i = 0; i < maze->get_height(); i++) {
		visited[i] = new bool[maze->get_width()];
		for (int j = 0; j < maze->get_width(); j++) {
			visited[i][j] = false;
		}
	}

	// Start solver at start of maze
	MazeTile *start = maze->get_tile(start_x, start_y);
	solution.insert(start);
	solve(start, solution, visited);

	// Store solution
	this->solution = solution;

	// Deallocate visited array
	for (int i = 0; i < maze->get_height(); i++) {
		delete[] visited[i];
	}

	delete[] visited;
}

/**
 * @brief solves maze using a depth-first approach
 * @param cur is the current cell
 * @param solution is the current valid path of maze
 * @param visited is an array of which tiles have been visited
 * @return true if a valid path exists, or false if it's a dead end
 */
bool MazeSolver::solve(MazeTile *cur, unordered_set<MazeTile*> &solution, bool **visited)
{
	int x = cur->x;
	int y = cur->y;

	if (x == end_x && y == end_y) { return true; }
	if (visited[x][y]) { return false; }

	visited[x][y] = true;

	// Checks if cell is in grid and can access cell from current cell
	if (maze->valid_cell(x+1, y) && !maze->get_tile(x+1,y)->north && !cur->south) {
		if (solve(maze->get_tile(x+1, y), solution, visited)) {
			solution.insert(maze->get_tile(x+1, y));
			return true;
		}
	}

	if (maze->valid_cell(x-1, y) && !maze->get_tile(x-1,y)->south && !cur->north) {
		if (solve(maze->get_tile(x-1, y), solution, visited)) {
			solution.insert(maze->get_tile(x-1, y));
			return true;
		}
	}

	if (maze->valid_cell(x, y+1) && !maze->get_tile(x,y+1)->west && !cur->east) {
		if (solve(maze->get_tile(x, y+1), solution, visited)) {
			solution.insert(maze->get_tile(x, y+1));
			return true;
		}
	}

	if (maze->valid_cell(x, y-1) && !maze->get_tile(x,y-1)->east && !cur->west) {
		if (solve(maze->get_tile(x, y-1), solution, visited)) {
			solution.insert(maze->get_tile(x, y-1));
			return true;
		}
	}

	return false;
}

/**
 * @brief randomly chooses two points on perimeter and designates
 * one as START, and one as END
 * Note: START is always on the left vertical axis and END is
 * always on the right vertical axis
 * @param random should be false if the start and end should be in
 * top-left and bottom-right corners respectivly, otherwise the
 * start and end point will be placed randomly on the edge
 * @return void
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

/**
 * @brief prints the solution to the maze to stdout on top of the maze
 * @return void
 */
void MazeSolver::print_maze()
{
	for (int i = 0; i < maze->get_height(); i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < maze->get_width(); k++) {
				if (j == 0) {
					if (maze->get_tile(i, k)->north) {
						cout << "-----";
					} else {
						cout << "     ";
					}
				} else {
					if (maze->get_tile(i, k)->west) {
						cout << "| ";
					} else if (!maze->get_tile(i, k)->west) {
						cout << "  ";
					}

					if (solution.find(maze->get_tile(i, k)) != solution.end()) {
						cout << "*";
					} else {
						cout << "X";
					}

					if (maze->get_tile(i, k)->east) {
						if (k == maze->get_width() - 1) {
							cout << " |";
						} else {
							cout << "  ";
						}
					} else if (!maze->get_tile(i, k)->east) {
						cout << "  ";
					}
				}
			}
			cout << endl;
		}
	}

	for (int i = 0; i < maze->get_width(); i++) {
		if (maze->get_tile(maze->get_height() - 1, i)->south) {
			cout << "-----";
		} else {
			cout << "     ";
		}
	}
	cout << endl;
}

/**
 * @brief draws the solution to the maze to a bitmap on top of the maze
 * @return void
 */
Bitmap *MazeSolver::to_bitmap()
{
	int w = maze->get_width() * 2 + 1;
	int h = maze->get_height() * 2 + 1;
	Bitmap *img = new Bitmap("solved.bmp", w, h);
	int x, y, tileX, tileY;
	for (x = 1, tileY = 0; tileY < maze->get_width(); tileY++, x += 2) {
		for (y = 1, tileX = 0; tileX < maze->get_height(); tileX++, y += 2) {
			MazeTile *t = maze->get_tile(tileX, tileY);
			if (!t->north) {
				img->set_pixel_white(x, y - 1);
			}
			if (!t->south) {
				img->set_pixel_white(x, y + 1);
			}
			if (!t->east) {
				img->set_pixel_white(x + 1, y);
			}
			if (!t->west) {
				img->set_pixel_white(x - 1, y);
			}
			if (solution.find(t) != solution.end()) {
				img->set_pixel(x, y, 0xFF, 0x00, 0x00);
			} else {
				img->set_pixel_white(x, y);
			}
		}
	}
	return img;
}

/**
 * @brief gets x-coordinate of the starting location of the maze
 * @return the column of the starting location
 */
int MazeSolver::get_start_x()
{
	return this->start_x;
}

/**
 * @brief gets y-coordinate of the starting location of the maze
 * @return the row of the starting location
 */
int MazeSolver::get_start_y()
{
	return this->start_y;
}

/**
 * @brief gets x-coordinate of the end of the maze
 * @return the column of the end location
 */
int MazeSolver::get_end_x()
{
	return this->end_x;
}

/**
 * @brief gets y-coordinate of the end of the maze
 * @return the row of the end location
 */
int MazeSolver::get_end_y()
{
	return this->end_y;
}

/**
 * @brief creates an instance of the maze solver for a specific maze
 * @param maze is the maze to solve
 */
MazeSolver::MazeSolver(Maze* maze)
{
	this->maze = maze;
	set_positions(true);
}

/**
 * @brief creates an instance of the maze solver for a specific maze,
 * specifying where the start and end points should be
 * @param maze is the maze to solve
 * @param random should be false if the start and end should be in
 * top-left and bottom-right corners respectivly, otherwise the
 * start and end point will be placed randomly on the edge
 */
MazeSolver::MazeSolver(Maze* maze, bool random)
{
	this->maze = maze;
	set_positions(random);
}
