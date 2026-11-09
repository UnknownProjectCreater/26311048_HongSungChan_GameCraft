#pragma once
#include <vector>
#include <limits>
#include "Tile.h"

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

	static constexpr int INF = (std::numeric_limits<int>::max)();

public:
	// Tiles from start to goal in order, empty when the goal can't be reached
	std::vector<Tile> Search(const Tile& start, const Tile& goal) const;
};
