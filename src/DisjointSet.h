#ifndef DISJOINTSET_H
#define DISJOINTSET_H
#endif

#include <map>
#include <vector>
#include "MazeTile.h"

using namespace std;

class DisjointSet
{
private:
	int numOfSets;
	map<int,int> set; 

public:
	DisjointSet();
	DisjointSet(int numOfNodes);
	~DisjointSet();
	int find(int element);
	bool combine(int a, int b);
	int getNumOfSets();
};