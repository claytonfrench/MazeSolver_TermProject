#include <iostream>
#include <cstdlib>
#include "Maze.h"

int Maze::get_width()
{
	return this->width;
}

int Maze::get_height()
{
	return this->height;
}

MazeTile *Maze::get_tile(int x, int y)
{
	return grid[x][y];
}

void Maze::generate()
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

void Maze::remove_wall(MazeTile *cur, MazeTile *target)
{
	int dx = target->x - cur->x;
	int dy = target->y - cur->y;

	if (dx == -1) { // dy HAS to be 0, since we only consider something adjacent IFF its either N, S, E, W
		target->south = false;
		cur->north = false;
	} else if (dx == 1) {
		target->north = false;
		cur->south = false;
	} else if (dy == 1) {
		target->west = false;
		cur->east = false;
	} else if (dy == -1) {
		target->east = false;
		cur->west = false;
	}
}

void Maze::add_neighbors(int x, int y, std::vector<MazeTile*> &neighbors, bool **visited)
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

bool Maze::valid_cell(int x, int y)
{
	if (x >= 0 && x < height && y >= 0 && y < width) {
		return true;
	}
	return false;
}

void Maze::print_maze()
{
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < width; k++) {
				if (j == 0) {
					if (grid[i][k]->north) {
						cout << "-----";
					} else {
						cout << "     ";
					}
				} else {
					if (grid[i][k]->west) {
						cout << "| ";
					} else if (!grid[i][k]->west) {
						cout << "  ";
					}
					cout << "X";
					if (grid[i][k]->east) {
						cout << " |";
					} else if (!grid[i][k]->east) {
						cout << "  ";
					}
				}
			}
			cout << endl;
		}
	}

	for (int i = 0; i < width; i++) {
		if (grid[height-1][i]->south) {
			cout << "-----";
		} else {
			cout << "     ";
		}
	}
	cout << endl;

	// TODO: Fix double walls for interior cells
}

void Maze::from_bitmap(Bitmap* bitmap)
{
	// TODO: Implement
}

Bitmap *Maze::to_bitmap()
{
	// TODO: Implement
	return NULL;
}

Maze::Maze(int height, int width)
{
	this->height = height;
	this->width = width;
	grid = new MazeTile**[height];

	for (int i = 0; i < height; i++) {
		grid[i] = new MazeTile*[width];
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			grid[i][j] = new MazeTile(i, j);
		}
	}

	generate();
}

Maze::~Maze()
{
	//Deletes MazeTile pointers
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			delete grid[i][j];
		}
	}

	//Deletes row entries (1D array of MazeTile pointers)
	for (int i = 0; i < height; i++) {
		delete[] grid[i];
	}

	delete[] grid;
}

Maze::Maze(Bitmap *bitmap)
{
	height = bitmap->get_height();
	width = bitmap->get_width();
	// TODO: Implement
}
