#include "BacktrackMaze.h"


BacktrackMaze::BacktrackMaze(int width, int length) {
	this->width = width;
	this->length = length;
	startingRow = (rand() % (int)(width));
	startingCol = (rand() % (int)(length));
	
	 maze = new Tile*[width];
	 for(int x = 0 ; x < width; x++)
		 maze[x] = new Tile[length];
	
	init_maze();
	generate_maze(startingRow, startingCol);
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
	random_shuffle(&tilesAround[0], &tilesAround[4]);
	
	for(int i = 0; i < 4; ++i) {
		if(row > 0 && tilesAround[i] == 'N' && maze[row-1][col].passed == false)
			return 'N';
		else if(row+1 < width && tilesAround[i] == 'S' && maze[row+1][col].passed == false)
			return 'S';
		else if(col < length-1 && tilesAround[i] == 'E' && maze[row][col+1].passed == false)
			return 'E';
		else if(col > 0 && tilesAround[i] == 'W' && maze[row][col-1].passed == false)
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

void BacktrackMaze::print_maze() {
	for(int col = 0; col < length; ++col) {
		cout << "---";
	}
	cout << "\n";
	
	for(int row = 0; row < width; ++row) {
		for(int col = 0; col < length; ++col) {
			
			if(maze[row][col].west) {
				cout << " ";
			} else
				cout << "|";
			
			cout << " ";
			
			if(maze[row][col].east) {
				cout << " ";
			} else {
				if(col < length-1 && !maze[row][col+1].west) {
					cout << " ";
				} else
					cout << "|";
			}
		}
		cout << "\n";
		
		for(int col = 0; col < length; ++col) {
			if(maze[row][col].south) {
				cout << "   ";
			} else
				cout << "---";
		}
		cout << "\n";
	}
	
}