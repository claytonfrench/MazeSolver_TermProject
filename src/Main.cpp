#include <iostream>
#include "BFSMaze.h"

using namespace std;

int main(int argc, char **argv)
{
	try {
		BFSMaze maze(5, 5);
		maze.generate();
		maze.print_maze();
		maze.to_bitmap()->write_file();
		return 0;
	} catch (string e) {
		cout << "Error : " << e << endl;
	}
}
