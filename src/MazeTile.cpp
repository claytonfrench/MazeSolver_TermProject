#include "MazeTile.h"

MazeTile::MazeTile(bool north, bool south, bool east,
				   bool west, int x, int y)
{
	this->north = north;
	this->south = south;
	this->east = east;
	this->west = west;
	this->passed = false;
	this->x = x;
	this->y = y;
}

MazeTile::MazeTile(int x, int y)
{
	this->north = true;
	this->south = true;
	this->east = true;
	this->west = true;
	this->passed = false;
	this->x = x;
	this->y = y;
}
