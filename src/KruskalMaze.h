#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include "DisjointSet.h"
#include "MazeTile.h"
#include "Maze.h"

using namespace std;

class KruskalMaze : public Maze {
private:
	struct Pair
	{
		MazeTile *u;
		MazeTile *v;
	};
	vector<Pair> edges;
	DisjointSet set;

public:
	KruskalMaze(int, int);
	void generate();
};
