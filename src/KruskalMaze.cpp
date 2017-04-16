#include <algorithm>
#include <iostream>
#include <random>
#include <ctime>
#include "KruskalMaze.h"


KruskalMaze::KruskalMaze(int w, int h) : Maze(w, h)
{
	set = DisjointSet(w*h);

	for (int i=0; i < height; i++) {
		for (int j=0; j < width; j++) {

			MazeTile *cur = grid[i][j];

			if (i > 0) {
				MazeTile *adj = grid[i-1][j];
				Pair e = {cur, adj};
				edges.push_back(e);
			}

			if (i + 1 < height) {
				MazeTile *adj = grid[i+1][j];
				Pair e = {cur, adj};
				edges.push_back(e);
			}

			if (j > 0) {
				MazeTile *adj = grid[i][j-1];
				Pair e = {cur, adj};
				edges.push_back(e);
			}

			if (j + 1 < width) {
				MazeTile *adj = grid[i][j+1];
				Pair e = {cur, adj};
				edges.push_back(e);
			}
		}
	}

	generate();
}

void KruskalMaze::generate()
{
	srand(time(NULL));

	Pair e;

	while (set.get_num_of_sets() > 1)
	{
		random_shuffle(edges.begin(), edges.end());
		e = edges[0];
		MazeTile *u = e.u;
		MazeTile *v = e.v;

		int m = u->x*width + u->y;
		int n = v->x*width + v->y;

		if (set.combine(m, n))
		{
			remove_wall(u, v);
			edges.erase(edges.begin());
		}
	}
}
