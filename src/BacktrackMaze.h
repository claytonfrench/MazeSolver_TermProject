#include<iostream>
#include<algorithm>

using namespace std;

struct Tile 
{
	bool passed;
	bool north, south, east, west;
	bool removeNorthWall, removeSouthWall, removeEastWall, removeWestWall;
};

class BacktrackMaze 
{
	int width, length;
	int startingRow;
	int startingCol;
	Tile** maze;
	
	public:
		void init_maze();
		char find_available_neighbor(int, int);
		void print_grid();
		void generate_maze(int, int);	
		BacktrackMaze(int, int);
};