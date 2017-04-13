#ifndef MAZETILE_H
#define MAZETILE_H

class MazeTile {
public:
	bool north;
	bool south;
	bool east;
	bool west;
	bool is_start;
	bool is_end;
	MazeTile(bool, bool, bool, bool, bool, bool);
};

#endif
