#ifndef BFSMAZE_H
#define BFSMAZE_H

#include "Maze.h"

using namespace std;

class BFSMaze : public Maze {
private:
    void add_neighbors(int, int, vector<MazeTile*>&, bool**);
    void remove_wall(MazeTile*, MazeTile*);
public:
    void generate();
	BFSMaze(int, int);
	BFSMaze(Bitmap*);
};

#endif
