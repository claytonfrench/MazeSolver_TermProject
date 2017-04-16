#include <iostream>
#include "BFSMaze.h"
#include "MazeSolver.h"
#include "DFSMaze.h"
#include "KruskalMaze.h"

using namespace std;

int main(int argc, char **argv)
{
	try {
		Maze *maze = new KruskalMaze(40, 40);
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
