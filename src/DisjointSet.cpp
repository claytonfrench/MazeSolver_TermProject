#include "DisjointSet.h"

/**
 * @brief finds representative element of the set that contains element
 * @param element is the integer we want to search for
 * @return integer that represents the set that contains element
 */
int DisjointSet::find(int element)
{
	return set[element];
}

/**
 * @brief combines two disjoint sets
 * @param cur is an element of a set that we want to combine with tar
 * @param tar is an element of a set that we want to combine with cur
 * @return false only when the elements are in the same set
 */
bool DisjointSet::combine(int cur, int tar)
{
	// Find representative element for set with cur and tar
	int a = find(cur);
	int b = find(tar);

	if (set[a] == set[b])
		return false;

	// Changes representative of elements in the set a with the representative b
	for (unsigned int i = 0; i < set.size(); i++) {
		if (set[i] == a)
			set[i] = b;
	}

	num_of_sets--;

	return true;
}

/**
 * @brief gets the number of disjoint sets
 * @return number of disjoint sets
 */
int DisjointSet::size()
{
	return num_of_sets;
}

/**
 * @brief initializes DisjointSet object with a specified size
 * @param size represents the initial number of disjoint sets
 */
DisjointSet::DisjointSet(int size)
{
	num_of_sets = size;

	for (int i=0; i < size; i++) {
		set[i] = i;
	}
}

/**
 * @brief default constructor for DisjointSet
 */
DisjointSet::DisjointSet()
{

}

/**
 * @brief destructor for DisjointSet
 */
DisjointSet::~DisjointSet()
{

}
