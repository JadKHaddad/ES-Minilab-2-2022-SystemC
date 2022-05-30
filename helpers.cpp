#include <systemc.h>
#include "helpers.hpp"

Pos::Pos()
{
	row=0;
	col=0;
}

void print_(std::string s) 
{
  const char* name = sc_core::sc_get_current_process_b()->get_parent()->basename();
  cout << "[" << sc_time_stamp() << "/" << sc_delta_count() << "](" << name << "):" << s << endl;
}

int min_distance(int grid[N][N], Pos from, Pos to)
{
    QItem source(from.row, from.col, 0);

	// To keep track of visited QItems. Marking
	// blocked cells as visited.
	bool visited[N][N];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
		{
			if(i == to.row && j == to.col)
			{
				visited[i][j] = false;
				continue;
			}
			if (grid[i][j] == 0 || grid[i][j] == 99 || grid[i][j] == 2 || grid[i][j] == 3) //cant visit 0 is unknown, 99 is wall, 2 to be discovered, 3 a drone is there
			{
				visited[i][j] = true;
				continue;
			}
			visited[i][j] = false; //1 can visit is discovered
		}
	}

	// applying BFS on matrix cells starting from source
	queue<QItem> q;
	q.push(source);
	visited[source.row][source.col] = true;
	while (!q.empty()) {
		QItem p = q.front();
		q.pop();

		// Destination found;
		if (p.row == to.row && p.col == to.col)
			return p.dist;

		// moving up
		if (p.row - 1 >= 0 &&
			visited[p.row - 1][p.col] == false) {
			q.push(QItem(p.row - 1, p.col, p.dist + 1));
			visited[p.row - 1][p.col] = true;
		}

		// moving down
		if (p.row + 1 < N &&
			visited[p.row + 1][p.col] == false) {
			q.push(QItem(p.row + 1, p.col, p.dist + 1));
			visited[p.row + 1][p.col] = true;
		}

		// moving left
		if (p.col - 1 >= 0 &&
			visited[p.row][p.col - 1] == false) {
			q.push(QItem(p.row, p.col - 1, p.dist + 1));
			visited[p.row][p.col - 1] = true;
		}

		// moving right
		if (p.col + 1 < N &&
			visited[p.row][p.col + 1] == false) {
			q.push(QItem(p.row, p.col + 1, p.dist + 1));
			visited[p.row][p.col + 1] = true;
		}
	}
	return -1;
}