#include <iostream>
#include <cstdlib>
#include "BFSMaze.h"

/**
 * @brief generates a maze using a randomized breadth-first search
 * @return void
 */
void BFSMaze::generate()
{
	bool **visited = new bool*[height];
	vector<MazeTile*> toVisit;

	// Initialize cells visited to false
	for (int i = 0; i < height; i++) {
		visited[i] = new bool[width];
		for (int j = 0; j < width; j++) {
			visited[i][j] = false;
		}
	}

	// Seed RNG
	srand(time(NULL));

	// Pick random cell
	int x = rand() % height;
	int y = rand() % width;
	visited[x][y] = true;
	toVisit.push_back(grid[x][y]);

	while (!toVisit.empty()) {
		// Randomly choose cell to visited
		int size = toVisit.size();
		random_shuffle(toVisit.begin(), toVisit.end());
		MazeTile *cur = toVisit[size-1];
		toVisit.pop_back();

		vector<MazeTile*> neighbors;
		add_neighbors(cur->x, cur->y, neighbors, visited);
		random_shuffle(neighbors.begin(), neighbors.end());

		for (auto next : neighbors) {
			visited[next->x][next->y] = true;
			remove_wall(cur, next);
			toVisit.push_back(next);
		}
	}

	// Deallocate visited array
	for (int i = 0; i < height; i++) {
		delete[] visited[i];
	}

	delete[] visited;
}

/**
 * @brief finds the unvisited cells that surrond a tile, and pushes them to a vector
 * @param x is the x-coordinate of the cell in units of tiles
 * @param y is the x-coordinate of the cell in units of tiles
 * @param neighbors is the list of neighbors to push to
 * @param visited is the array of visited tiles
 * @return void
 */
void BFSMaze::add_neighbors(int x, int y, std::vector<MazeTile*> &neighbors, bool **visited)
{
	if (valid_cell(x+1, y) && !visited[x+1][y]) {
		neighbors.push_back(grid[x+1][y]);
	}

	if (valid_cell(x-1, y) && !visited[x-1][y]) {
		neighbors.push_back(grid[x-1][y]);
	}

	if (valid_cell(x, y+1) && !visited[x][y+1]) {
		neighbors.push_back(grid[x][y+1]);
	}

	if (valid_cell(x, y-1) && !visited[x][y-1]) {
		neighbors.push_back(grid[x][y-1]);
	}
}

/**
 * @brief creates a maze of a specified size that is generated using
 * a randomized breadth-first search
 * @param w is the number of tiles per row
 * @param y is the number of rows
 */
BFSMaze::BFSMaze(int w, int h)
	: Maze(w, h)
{
	this->generate();
}
