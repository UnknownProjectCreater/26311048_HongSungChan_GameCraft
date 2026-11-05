#pragma once
#include <vector>
#include <limits>

class FindPath
{
private:
	struct Node
	{
		int r, c, cost;

		bool operator>(const Node& other) const
		{
			return cost > other.cost;
		}
	};

	const int INF = INFINITY;
	int nodeCount;
	int connectionCount;
	int startNode;

public:
	FindPath(int nodeCount, int connectionCount);
};