#include <iostream>
#include "BFSMaze.h"
#include "MazeSolver.h"
#include "DFSMaze.h"
#include "KruskalMaze.h"

using namespace std;

int main(int argc, char **argv)
{
	try {
		int width, height;

		cout << endl;
		cout << "Enter the dimensions of the maze." << endl;
		cout << "Width: ";
		cin >> width;
		cout << "Height: ";
		cin >> height;
		while (width < 1 || height < 1)
		{
			cout << "Width and height must be positive integers." << endl;
			cout << "Width: ";
			cin >> width;
			cout << "Height: ";
			cin >> height;
		}

		Maze *maze;

		if (argc > 1)
		{
			string arg = argv[1];
			if (arg == "bfs")
				maze = new BFSMaze(width, height);

			else if (arg == "dfs")
				maze = new DFSMaze(width, height);

			else if (arg == "kruskal")
				maze = new KruskalMaze(width, height);
		}

		// Uses Depth-First Search by default
		else
		{
			maze = new DFSMaze(width, height);
		}

		MazeSolver solver(maze);
		maze->print_maze();
		maze->to_bitmap()->write_file();
		solver.solve_maze();
		solver.print_maze();
		solver.to_bitmap()->write_file();

		return 0;

	} catch (string e) {
		cout << "Error : " << e << endl;
	}

}
