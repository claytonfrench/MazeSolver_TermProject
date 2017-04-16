#include "DFSMaze.h"

//Maze constructor takes in values for maze parameters
DFSMaze::DFSMaze(int width, int length) : Maze(width, length)
{
	srand(time(NULL));

	startingRow = rand() % width;		//randomize maze generating parameters
	startingCol = rand() % length;

	generate_maze(startingRow, startingCol);	//generate maze starting at random cell
}

//randomly selects next cell to travel to during maze generation
char DFSMaze::find_available_neighbor(int row, int col) {

	char tilesAround[4] = {'N', 'S', 'E', 'W'};				//array holds possible neighbors
	random_shuffle(&tilesAround[0], &tilesAround[4]);		//randomizes array


	for(int i = 0; i < 4; ++i) {																	//traverse randomized array to find next neighbor
		if(row > 0 && tilesAround[i] == 'N' && !grid[row-1][col]->passed)					//if north neighbor was not passed and current row != 0
			return 'N';
		else if(row+1 < height && tilesAround[i] == 'S' && !grid[row+1][col]->passed)			//if south neighbor was not passed and current row is not the last one
			return 'S';
		else if(col < width-1 && tilesAround[i] == 'E' && !grid[row][col+1]->passed)		//if east neighbor was not passed and current column is not the last
			return 'E';
		else if(col > 0 && tilesAround[i] == 'W' && !grid[row][col-1]->passed)				//if west neighbor was not passed and current column != 0
			return 'W';
	}

	return 'Q'; 																					//returns 'Q' when all cells in maze have been visited
}

void DFSMaze::generate_maze(int row, int col) {

	grid[row][col]->passed = true;
	bool quit = false;

	while(!quit) {
		char nextTile = find_available_neighbor(row, col);	//determines which cell to travel to next

		switch(nextTile) {
			case 'N':							//Removes wall between current cell and northern neighbor
				grid[row][col]->north = false;
				grid[row-1][col]->south = false;
				generate_maze(row-1, col);
				break;
			case 'S':							//Removes wall between current cell and southern neighbor
				grid[row][col]->south = false;
				grid[row+1][col]->north = false;
				generate_maze(row+1, col);
				break;
			case 'E':							//Removes wall between current cell and eastern neighbor
				grid[row][col]->east = false;
				grid[row][col+1]->west = false;
				generate_maze(row, col+1);
				break;
			case 'W':							//Removes wall between current cell and western neighbor
				grid[row][col]->west = false;
				grid[row][col-1]->east = false;
				generate_maze(row, col-1);
				break;
			default:
				quit = true;
				break;
		}
	}
}
