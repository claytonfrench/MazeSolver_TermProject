#include "KruskalMaze.h"


KruskalMaze::KruskalMaze(int w, int h)
{
	width = w;
	height = h;
	set = DisjointSet(w*h);

	int cur;

	for (int i=0; i < h; i++)
	{
		for (int j=0; j < w; j++)
		{
			cur = i*width + j;
			if (i > 0)
			{
				int adj = (i-1)*width + j;
				Pair e = {cur,adj};
				edges.push_back(e);
			}

			if (j > 0)
			{
				int adj = (i)*width + (j-1);
				Pair e = {cur,adj};
				edges.push_back(e);
			}

			grid.push_back(MazeTile(j,i));
		}
	}

	generate();
}

void KruskalMaze::generate()
{
	srand(time(NULL));

	Pair e;

	while (set.getNumOfSets() > 1)
	{
		random_shuffle(edges.begin(), edges.end());
		e = edges[0];
		int m = e.u;
		int n = e.v;

		if (set.combine(m,n))
		{
			removeEdge(m,n);
			edges.erase(edges.begin());
		}
	}
}

void KruskalMaze::removeEdge(int cur, int tar)
{
	int cx = cur % width;
	int cy = cur / width;
	int tx = tar % width;
	int ty = tar / width;

	if (cx < tx)
	{
		grid[cur].east = false;
		grid[tar].west = false;
	}

	else if (cx > tx)
	{
		grid[cur].west = false;
		grid[tar].east = false;
	}

	else if (cy < ty)
	{
		grid[cur].south = false;
		grid[tar].north = false;
	}

	else if (cy > ty)
	{
		grid[cur].north = false;
		grid[tar].south = false;
	}
}

void KruskalMaze::print_maze()
{
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < width; k++) {
				int cur = i*width + k;
				if (j == 0) {
					if (grid[cur].north) {
						cout << "-----";
					} else {
						cout << "     ";
					}
				} else {
					if (grid[cur].west) {
						cout << "| ";
					} else if (!grid[cur].west) {
						cout << "  ";
					}
					cout << " ";
					if (grid[cur].east) {
						cout << " |";
					} else if (!grid[cur].east) {
						cout << "  ";
					}
				}
			}
			cout << endl;
		}
	}

	for (int i = 0; i < width; i++) {
		if (grid[(height-1)*width + i].south) {
			cout << "-----";
		} else {
			cout << "     ";
		}
	}

	cout << endl << endl;

	// TODO: Fix double walls for interior cells
}