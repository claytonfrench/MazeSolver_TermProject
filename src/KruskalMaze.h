#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include "DisjointSet.h"
#include "MazeTile.h"

using namespace std;


struct Pair
{
	int u;
	int v;
};


class KruskalMaze
{
private:
	int width;
	int height;
	vector<MazeTile> grid;
	vector<Pair> edges;
	DisjointSet set;

public:
	KruskalMaze(int w, int h);
	void generate();
	void removeEdge(int cur, int tar);
	void print_maze();
};