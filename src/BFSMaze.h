#ifndef BFSMAZE_H
#define BFSMAZE_H

#include "Maze.h"

using namespace std;

class BFSMaze : public Maze {
private:
    void add_neighbors(int, int, vector<MazeTile*>&, bool**);
public:
    void generate();
	BFSMaze(int, int);
	BFSMaze(Bitmap*);
};

#endif
