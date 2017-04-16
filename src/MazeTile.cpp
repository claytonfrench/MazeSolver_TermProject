#include "MazeTile.h"

/**
 * @brief defines a cell for a tile in a maze
 * @param north is false if there is a wall above the cell
 * @param south is false if there is a wall below the cell
 * @param east is false if there is a wall to the right of the cell
 * @param west is false if there is a wall to the left of the cell
 * @param x is the x-coordinate of the cell in terms of tiles
 * @param y is the y-coordinate of the cell in terms of tiles
 */
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

/**
 * @brief defines a cell for a tile in a maze, setting default values
 * for walls
 * @param x is the x-coordinate of the cell in terms of tiles
 * @param y is the y-coordinate of the cell in terms of tiles
 */
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
