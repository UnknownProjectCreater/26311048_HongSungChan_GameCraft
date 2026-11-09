#include <cmath>
#include "Player.h"
#include "TileManager.h"
#include <iostream>

static const float PLAYER_SPEED = 200.0f;
static const float FRAME_SIZE = 32.0f;

int Player::Init(const std::string& key)
{
	if (0 > GameObject::Init(key))
		return -1;

	for (int row = 0; row <= (int)EntityDir::LEFT; row++)
	{
		std::string suffix = "_" + std::to_string(row);

		if (0 > m_animator.Add("Idle" + suffix, GetAnimationManager()->LoadClip("Player_Idle" + suffix, 32, 32, 2, 0.3f, true, row)))
			return -1;
		if (0 > m_animator.Add("Run" + suffix, GetAnimationManager()->LoadClip("Player_Walk" + suffix, 32, 32, 4, 0.1f, true, row)))
			return -1;
	}

	return 0;
}

int Player::Update(float deltaTime)
{
	UpdateTileMove(deltaTime);

	return Entity::Update(deltaTime);
}

void Player::SetStartTile(int tile)
{
	nowTile = tile;
	nextTile = tile;
	SetPosition(GetStandPosition(tile));
}

void Player::UpdateTileMove(float deltaTime)
{
	if (nextTile != nowTile)
	{
		VEC2 target = GetStandPosition(nextTile);
		float remaining = fabsf(target.x - m_position.x) + fabsf(target.y - m_position.y);
		if (remaining > PLAYER_SPEED * deltaTime)
			return;

		SetPosition(target);
		SetVelocity(VEC2(0.0f, 0.0f));
		nowTile = nextTile;
	}

	if (direction[0] > 0)
		SetEntityDir(EntityDir::RIGHT);
	else if (direction[0] < 0)
		SetEntityDir(EntityDir::LEFT);
	else if (direction[1] < 0)
		SetEntityDir(EntityDir::BACK);
	else if (direction[1] > 0)
		SetEntityDir(EntityDir::FRONT);
	else
		return;

	int width = GetTileManager()->GetWidth();
	int tile = GetTileManager()->GetTileIndex(nowTile % width + direction[0], nowTile / width + direction[1]);
	if (0 > tile || GetTileManager()->IsInLimit(GetTileManager()->GetTileCenter(tile)))
		return;

	nextTile = tile;
	SetVelocity(VEC2(direction[0] * PLAYER_SPEED, direction[1] * PLAYER_SPEED));
}

// m_position is the sprite's top-left corner: offset it so the character's feet (bottom of the frame) sit on the tile's center
VEC2 Player::GetStandPosition(int tile) const
{
	VEC2 center = GetTileManager()->GetTileCenter(tile);
	VEC2 scaling = GetScaling();

	return VEC2(center.x - FRAME_SIZE * scaling.x / 2.0f, center.y - FRAME_SIZE * scaling.y);
}

std::string Player::GetClipKey(const std::string& name) const
{
	return name + "_" + std::to_string((int)GetEntityDir());
}

void Player::ChangeState(State state)
{
	m_state = state;
}

void Player::UpdateMoveState()
{
	VEC2 velocity = GetVelocity();
	bool isMoving = velocity.x != 0.0f || velocity.y != 0.0f;

	ChangeState(isMoving ? State::Run : State::Idle);

	m_image.m_texture = GetTextureManager()->GetTexture(isMoving ? "Player_Walk" : "Player_Idle").m_texture;
	m_animator.Play(GetClipKey(isMoving ? "Run" : "Idle"));
}

int Player::UpdateState(float deltaTime)
{
	switch (m_state)
	{
	case State::Idle:
	case State::Run:
		UpdateMoveState();
		break;
	case State::Attack:
		m_animator.Play("Attack");
		if (m_animator.IsFinished())
			UpdateMoveState();
		break;
	case State::Death:
		m_animator.Play("Death");
		break;
	}

	return 0;
}
