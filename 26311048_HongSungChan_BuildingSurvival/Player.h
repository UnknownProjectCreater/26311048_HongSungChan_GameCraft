#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	enum class State
	{
		Idle,
		Run,
		Attack,
		Death
	};

private:
	State m_state = State::Idle;
	bool m_isInvincible = false;

	void UpdateMoveState();
	std::string GetClipKey(const std::string& name) const;

	int m_footstepSound;

	// Indices into TileManager::m_tiles. nextTile == nowTile means standing still
	int nowTile = 0;
	int nextTile = 0;
	int direction[2] = { 0, 0 };

	void UpdateTileMove(float deltaTime);
	VEC2 GetStandPosition(int tile) const;

protected:
	int UpdateState(float deltaTime) override;

public:
	int Init(const std::string& key) override;
	int Update(float deltaTime) override;

	void ChangeState(State state);

	void SetStartTile(int tile);
	void SetDirection(int x, int y) { direction[0] = x; direction[1] = y; };

	int GetNowTile() const { return nowTile; };
	int GetNextTile() const { return nextTile; };

	State GetState() const { return m_state; };
};