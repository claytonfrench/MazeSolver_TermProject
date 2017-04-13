#include "MazeTile.h"

MazeTile::MazeTile(bool north, bool south, bool east,
				   bool west, bool is_start, bool is_end)
{
	this->north = north;
	this->south = south;
	this->east = east;
	this->west = west;
	this->is_start = is_start;
	this->is_end = is_end;
}
