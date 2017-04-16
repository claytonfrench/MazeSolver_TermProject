#include "DisjointSet.h"

int DisjointSet::find(int element)
{
	return set[element];
}

bool DisjointSet::combine(int cur, int tar)
{
	int a = find(cur);
	int b = find(tar);

	if (set[a] == set[b])
		return false;

	for (unsigned int i=0; i < set.size(); i++) {
		if (set[i] == a)
			set[i] = b;
	}

	num_of_sets--;

	return true;
}

int DisjointSet::get_num_of_sets()
{
	return num_of_sets;
}

DisjointSet::DisjointSet()
{

}

DisjointSet::DisjointSet(int num_of_nodes)
{
	num_of_sets = num_of_nodes;

	for (int i=0; i < num_of_nodes; i++) {
		set[i] = i;
	}
}

DisjointSet::~DisjointSet()
{

}
