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
	std::vector<Tile> Search(const Tile& start, const Tile& goal) const;
};
