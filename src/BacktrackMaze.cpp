#include "BacktrackMaze.h"


void BacktrackMaze::init_maze() {
	for(int x = 0; x < this->size; x++) {
		for(int y = 0; x < this->size; x++) {
			maze[x][y].passed = false;
			maze[x][y].north = false;
			maze[x][y].south = false;
			maze[x][y].east = false;
			maze[x][y].west = false;
		}
	}
}

char BacktrackMaze::find_available_neighbor(int row, int col) {
	
	char tilesAround = {'N', 'S', 'E', 'W');
	random_shuffle(&tilesAround[0], &tilesAround[3]);
	
	for(int i = 0; i < 3; ++i) {
		if(tilesAround[i] == 'N' && maze[row-1][col].passed == false && row > 0)
			return 'N';
		else if(tilesAround[i] == 'S' && maze[row+1][col].passed == false && row+1 < size)
			return 'S';
		else if(tilesAround[i] == 'E' && maze[row][col+1].passed == false && col < size-1)
			return 'E';
		else if(tilesAround[i] == 'W' && maze[row][col-1].passed == false && col > 0)
			return 'W';
	}
	return 'Q'
}

void BacktrackMaze::generate_maze(int row, int col) {
	
	maze[row][col].passed = true;
	bool quit = false;
	
	while(!quit) {
		char nextTile = find_available_neighbor(row, col);
		
		switch(nextTile) {
			case 'N':
				maze[row][col].north = true;
				maze[row-1][col].south = true;
				generate_maze(row-1, col);
				break;
			case 'S':
				maze[row]col].south = true;
				maze[row+1][col].north = true;
				generate_maze(row+1, col);
				break;
			case 'E':
				maze[row][col].east = true;
				maze[row][col+1].west = true;
				generate_maze(row, col+1);
				break;
			case 'W':
				maze[row][col].west = true;
				maze[row][col-1].east = true;
				generate_maze(row, col-1);
				break;
			default:
				quit = true;
				break;
		}
	}
}