#include <iostream>
#include "BFSMaze.h"
#include "MazeSolver.h"

using namespace std;

int main(int argc, char **argv)
{
	try {
		Maze *maze = new BFSMaze(5, 5);
		MazeSolver solver(maze);
		solver.solve_maze();
		solver.print_maze();
		solver.to_bitmap()->write_file();
		return 0;
	} catch (string e) {
		cout << "Error : " << e << endl;
	}
}
