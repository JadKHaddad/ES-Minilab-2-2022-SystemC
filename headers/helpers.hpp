#ifndef HELPERS
#define HELPERS

#include <bits/stdc++.h>
#include "const.hpp"
using namespace std;


// QItem for current location and distance
// from source location
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

int min_distance(int grid[N][N], Pos from, Pos to);

void print_(std::string s);

#endif