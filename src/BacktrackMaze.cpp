#include "BacktrackMaze.h"

//Maze constructor takes in values for maze parameters
BacktrackMaze::BacktrackMaze(int width, int length) {
	
	this->width = width;						//initialize maze width and length
	this->length = length;
	
	startingRow = (rand() % (int)(width));		//randomize maze generating parameters
	startingCol = (rand() % (int)(length));
	
	maze = new Tile*[width];					//create 2-D array based on parameters
	for(int x = 0 ; x < width; x++)
		maze[x] = new Tile[length];
	
	init_maze();
	
	generate_maze(startingRow, startingCol);	//generate maze starting at random cell
}

//initialize maze
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

//randomly selects next cell to travel to during maze generation
char BacktrackMaze::find_available_neighbor(int row, int col) {
	
	char tilesAround[4] = {'N', 'S', 'E', 'W'};				//array holds possible neighbors
	random_shuffle(&tilesAround[0], &tilesAround[4]);		//randomizes array
	
	
	for(int i = 0; i < 4; ++i) {																	//traverse randomized array to find next neighbor
		if(row > 0 && tilesAround[i] == 'N' && maze[row-1][col].passed == false)					//if north neighbor was not passed and current row != 0 
			return 'N';
		else if(row+1 < width && tilesAround[i] == 'S' && maze[row+1][col].passed == false)			//if south neighbor was not passed and current row is not the last one 
			return 'S';
		else if(col < length-1 && tilesAround[i] == 'E' && maze[row][col+1].passed == false)		//if east neighbor was not passed and current column is not the last 
			return 'E';
		else if(col > 0 && tilesAround[i] == 'W' && maze[row][col-1].passed == false)				//if west neighbor was not passed and current column != 0 
			return 'W';
	} 
	
	return 'Q'; 																					//returns 'Q' when all cells in maze have been visited
}

void BacktrackMaze::generate_maze(int row, int col) {
	
	maze[row][col].passed = true;
	bool quit = false;
	
	while(!quit) {
		char nextTile = find_available_neighbor(row, col);	//determines which cell to travel to next
		
		switch(nextTile) {
			case 'N':							//Removes wall between current cell and northern neighbor										
				maze[row][col].north = true;				
				maze[row-1][col].south = true;				
				generate_maze(row-1, col);
				break;
			case 'S':							//Removes wall between current cell and southern neighbor
				maze[row][col].south = true;
				maze[row+1][col].north = true;
				generate_maze(row+1, col);
				break;
			case 'E':							//Removes wall between current cell and eastern neighbor
				maze[row][col].east = true;
				maze[row][col+1].west = true;
				generate_maze(row, col+1);
				break;
			case 'W':							//Removes wall between current cell and western neighbor
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
	
	for(int col = 0; col < length; ++col) {				//Print top row
		cout << "---";
	}
	cout << "\n";
	
	for(int row = 0; row < width; ++row) {				//Print inner rows
		for(int col = 0; col < length; ++col) {
			
			if(maze[row][col].west) {					//Print "|" if cell doesn't connect to left neighbor
				cout << " ";
			} else
				cout << "|";
			
			cout << " ";
			
			if(maze[row][col].east) {							//Prints "|" if cell doesn't connect to right neighbor
				cout << " ";
			} else {									
				if(col < length-1 && !maze[row][col+1].west) {	//Prevents double printing of "|" for walls
					cout << " ";
				} else
					cout << "|";
			}
		}
		cout << "\n";
		
		for(int col = 0; col < length; ++col) {		//Prints bottom border for cells
			if(maze[row][col].south) {
				cout << "   ";
			} else
				cout << "---";
		}
		cout << "\n";
	}
	
}