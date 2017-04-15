#include "DisjointSet.h"




DisjointSet::DisjointSet()
{

}

DisjointSet::DisjointSet(int numOfNodes)
{
	numOfSets = numOfNodes;

	for (int i=0; i < numOfNodes; i++)
	{
		set[i] = i;
	}
}

DisjointSet::~DisjointSet()
{

}

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

	for (int i=0; i < set.size(); i++)
	{
		if (set[i] == a)
			set[i] = b;
	}

	numOfSets--;

	return true;
}

int DisjointSet::getNumOfSets()
{
	return numOfSets;
}