#include <iostream>
#include <cstring>
#include "BFSMaze.h"
#include "MazeSolver.h"
#include "DFSMaze.h"
#include "KruskalMaze.h"

using namespace std;

/**
* @brief Takes arguments from command line and produces a specified maze
* argv[1] = width (integer)
* argv[2] = height (integer)
* argv[3] =  algorithm to generate maze (DFS, BFS, or Kruskal)
*/
int main(int argc, char **argv)
{
	Maze *maze;
	if (argc != 7) {
		cout << "Invalid number of arguments. Usage: -w <width> -h <height> -a <algorithm>" << endl;
		return 1;
	} else {
		int width, height;

		for (int i = 1; i < argc; i++) {
			if (strcmp(argv[i], "-w") == 0) {
				width = atoi(argv[i+1]);

				// Check if width is an integer
				if (argv[i+1] != to_string(width)) {
					cout << "Invalid width. Only use integers." << endl;
					return 1;
				}
				i++;
			} else if (strcmp(argv[i], "-h") == 0) {
				height = atoi(argv[i+1]);

				// Check if height is an integer
				if (argv[i+1] != to_string(height)) {
					cout << "Invalid width. Only use integers." << endl;
					return 1;
				}
				i++;
			} else if (strcmp(argv[i], "-a") == 0) {
				string alg = argv[i+1];
				if (alg == "BFS") {
					if (height > 500 || width > 500) {
						cout << "Height/width need to be less than 500." << endl;
						return 1;
					}
					maze = new BFSMaze(width, height);
				} else if (alg == "DFS") {
					if (height > 250 || width > 250) {
						cout << "Height/width need to be less than 250." << endl;
						return 1;
					}
					maze = new DFSMaze(width, height);
				} else if (alg == "Kruskal") {
					if (height > 100 || width > 100) {
						cout << "Height/width need to be less than 100." << endl;
						return 1;
					}
					maze = new KruskalMaze(width, height);
				} else {
					cout << "Invalid algorithm. Use: BFS, DFS, or Kruskal" << endl;
					return 1;
				}
				i++;
			} else {
				cout << "Invalid arguments." << endl;
			}
		}
	}

	MazeSolver solver(maze);

	cout << "Generated maze (out.bmp): " << endl;
	maze->print_maze();
	maze->to_bitmap()->write_file();
	cout << "Solved maze (solved.bmp): " << endl;
	solver.solve_maze();
	solver.print_maze();
	solver.to_bitmap()->write_file();

	return 0;
}
