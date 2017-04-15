#include<iostream>
#include<algorithm>

using namespace std;

struct Tile {
			bool passed;
			bool north, south, east, west;
			bool removeNorthWall, removeSouthWall, removeEastWall, removeWestWall;
		};

class BacktrackMaze {
	int size;
	int startingRow = (rand() % (int)(size));
	int startingCol = (rand() % (int)(size));
	Tile** maze = new Tile*[size];
	
	public:
		void init_maze();
		char find_available_neighbor(int, int);
		void print_grid();
		void generate_maze(int, int);	
};