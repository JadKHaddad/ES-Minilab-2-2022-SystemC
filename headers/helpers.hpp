#ifndef HELPERS
#define HELPERS

#include <bits/stdc++.h>
#include "const.hpp"
using namespace std;

//custom classes and functions

//QItem for current location and distance
class QItem {
public:
	int row;
	int col;
	int dist;
	QItem(int x, int y, int w)
		: row(x), col(y), dist(w)
	{
	}
};

class Pos{
public:
    int row;
    int col;
    Pos(int x, int y)
        : row(x), col(y)
    {
    }
	Pos();
};

class IndexDist{
public:
    int index;
    int dist;
    IndexDist(int x, int y)
        : index(x), dist(y)
    {
    }
};

//calculates the minimal distance between two gevin positions - returns -1 if there is no path between the gevin positions
int min_distance(int grid[N][N], Pos from, Pos to);

#endif