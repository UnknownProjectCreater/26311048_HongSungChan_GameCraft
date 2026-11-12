#include <algorithm>
#include <functional>
#include <queue>
#include "FindPath.h"
#include "TileManager.h"

static const int DIRECTION_R[4] = { -1, 1, 0, 0 };
static const int DIRECTION_C[4] = { 0, 0, -1, 1 };

std::vector<Tile> FindPath::Search(const Tile& start, const Tile& goal) const
{
	TileManager* tileManager = GetTileManager();

	Tile::arrayPos startPos = start.GetArrayPos();
	Tile::arrayPos goalPos = goal.GetArrayPos();

	int startIndex = tileManager->GetTileIndex(startPos.x, startPos.y);
	int goalIndex = tileManager->GetTileIndex(goalPos.x, goalPos.y);
	if (0 > startIndex || 0 > goalIndex)
		return {};

	int tileCount = tileManager->GetWidth() * tileManager->GetHeight();
	std::vector<int> distance(tileCount, INF);
	std::vector<int> previous(tileCount, -1);

	// std::greater	   - descending order sorting
	// priority_queue  - 
	std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openList;

	distance[startIndex] = 0;
	openList.push({ startPos.y, startPos.x, 0 });

	while (!openList.empty())
	{
		Node current = openList.top();
		openList.pop();

		int currentIndex = tileManager->GetTileIndex(current.c, current.r);
		if (current.cost > distance[currentIndex])
			continue;

		if (currentIndex == goalIndex)
			break;

		for (int i = 0; i < 4; i++)
		{
			int r = current.r + DIRECTION_R[i];
			int c = current.c + DIRECTION_C[i];

			Tile* next = tileManager->GetTile(c, r);
			if (next == nullptr || !next->IsWalkable())
				continue;

			int nextIndex = tileManager->GetTileIndex(c, r);
			int cost = current.cost + next->GetCost();
			if (cost >= distance[nextIndex])
				continue;

			distance[nextIndex] = cost;
			previous[nextIndex] = currentIndex;
			openList.push({ r, c, cost });
		}
	}

	if (distance[goalIndex] == INF)
		return {};

	std::vector<Tile> path;
	for (int index = goalIndex; index != -1; index = previous[index])
		path.push_back(*tileManager->GetTile(index));

	std::reverse(path.begin(), path.end());

	return path;
}