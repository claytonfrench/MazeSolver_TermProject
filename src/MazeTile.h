#ifndef MAZETILE_H
#define MAZETILE_H

class MazeTile {
public:
	bool north;
	bool south;
	bool east;
	bool west;
	int x;
	int y;
	MazeTile(bool, bool, bool, bool, int, int);
	MazeTile(int, int);
};

#endif
