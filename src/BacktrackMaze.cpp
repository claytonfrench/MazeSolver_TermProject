#include "BacktrackMaze.h"


BacktrackMaze::BacktrackMaze(int width, int length) {
	this->width = width;
	this->length = length;
	startingRow = (rand() % (int)(width));
	startingCol = (rand() % (int)(length));
	
	maze = new Tile*[width];
	for(int x = 0 ; x < width; x++)
		maze[x] = new Tile[length];
	
	
}

void BacktrackMaze::init_maze() {
	for(int row = 0; row < this->width; row++) {
		for(int col = 0; col < this->length; col++) {
			maze[row][col].passed = false;
			maze[row][col].north = false;
			maze[row][col].south = false;
			maze[row][col].east = false;
			maze[row][col].west = false;
		}
	}
}

char BacktrackMaze::find_available_neighbor(int row, int col) {
	
	char tilesAround[4] = {'N', 'S', 'E', 'W'};
	random_shuffle(&tilesAround[0], &tilesAround[3]);
	
	for(int i = 0; i < 3; ++i) {
		if(tilesAround[i] == 'N' && maze[row-1][col].passed == false && row > 0)
			return 'N';
		else if(tilesAround[i] == 'S' && maze[row+1][col].passed == false && row+1 < width)
			return 'S';
		else if(tilesAround[i] == 'E' && maze[row][col+1].passed == false && col < length-1)
			return 'E';
		else if(tilesAround[i] == 'W' && maze[row][col-1].passed == false && col > 0)
			return 'W';
	} 
	return 'Q';
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
				maze[row][col].south = true;
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