#include<iostream>
#include<algorithm>

using namespace std;

class BacktrackMaze {
	int size;
	int startingRow = (rand() % (int)(size));
	int startingCol = (rand() % (int)(size));
	Tile maze[size][size];
	
	public:
		struct Tile {
			bool passed;
			bool north, south, east, west;
			bool removeNorthWall, removeSouthWall, removeEastWall, removeWestWall;
		}
		
		void init_maze();
		int find_available_neighbor(int);
		void print_grid();
		void generate_maze(int);	
};