#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <map>
#include <vector>

using namespace std;

class DisjointSet
{
private:
	int num_of_sets;
	map<int,int> set;

public:
	DisjointSet();
	DisjointSet(int);
	~DisjointSet();
	int find(int);
	bool combine(int, int);
	int get_num_of_sets();
};

#endif
