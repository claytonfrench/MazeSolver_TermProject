#include <iostream>
#include <algorithm>
#include "Maze.h"

using namespace std;

class BacktrackMaze : public Maze {
private:
	int startingRow;
	int startingCol;
public:
	char find_available_neighbor(int, int);
	void generate_maze(int, int);
	BacktrackMaze(int, int);
};
