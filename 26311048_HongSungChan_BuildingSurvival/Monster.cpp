#include <cmath>
#include "Monster.h"
#include "Player.h"
#include "TileManager.h"

static const float MONSTER_SPEED = 200.0f;
static const float FRAME_SIZE = 32.0f;

int Monster::Update(float deltaTime)
{
	UpdatePath(deltaTime);
	UpdateTileMove(deltaTime);

	Entity::Update(deltaTime);

	return 1;
}

void Monster::SetStartTile(int tile)
{
	nowTile = tile;
	nextTile = tile;
	SetPosition(GetStandPosition(tile));
}

void Monster::UpdatePath(float deltaTime)
{
	m_pathTimer += deltaTime;
	if (m_pathTimer < PATH_INTERVAL || m_target == nullptr)
		return;

	m_pathTimer -= PATH_INTERVAL;

	Tile* start = GetTileManager()->GetTile(nextTile);
	Tile* goal = GetTileManager()->GetTile(m_target->GetNowTile());
	if (start == nullptr || goal == nullptr)
		return;

	m_path = m_findPath.Search(*start, *goal);
	m_pathStep = 0;
}

void Monster::UpdateTileMove(float deltaTime)
{
	if (nextTile != nowTile)
	{
		VEC2 target = GetStandPosition(nextTile);
		float remaining = fabsf(target.x - m_position.x) + fabsf(target.y - m_position.y);
		if (remaining > MONSTER_SPEED * deltaTime)
			return;

		SetPosition(target);
		SetVelocity(VEC2(0.0f, 0.0f));
		nowTile = nextTile;
	}

	if (m_pathStep + 1 >= m_path.size())
		return;

	m_pathStep++;

	Tile::arrayPos next = m_path[m_pathStep].GetArrayPos();
	nextTile = GetTileManager()->GetTileIndex(next.x, next.y);

	int width = GetTileManager()->GetWidth();
	int directionX = next.x - nowTile % width;
	int directionY = next.y - nowTile / width;

	if (directionX > 0)
		SetEntityDir(EntityDir::RIGHT);
	else if (directionX < 0)
		SetEntityDir(EntityDir::LEFT);
	else if (directionY < 0)
		SetEntityDir(EntityDir::BACK);
	else if (directionY > 0)
		SetEntityDir(EntityDir::FRONT);

	SetVelocity(VEC2(directionX * MONSTER_SPEED, directionY * MONSTER_SPEED));
}

// m_position is the sprite's top-left corner: offset it so the character's feet (bottom of the frame) sit on the tile's center
VEC2 Monster::GetStandPosition(int tile) const
{
	VEC2 center = GetTileManager()->GetTileCenter(tile);
	VEC2 scaling = GetScaling();

	return VEC2(center.x - FRAME_SIZE * scaling.x / 2.0f, center.y - FRAME_SIZE * scaling.y);
}
