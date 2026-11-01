#include "Player.h"

int Player::Init(const std::string& key)
{
	if (0 > GameObject::Init(key))
		return -1;

	// Idle.png: 32x32, 2 frames per row (3rd column is a text label), row 0 = FRONT
	if (0 > m_animator.Add("Idle", GetAnimationManager()->LoadClip(key, 32, 32, 2, 0.3f, true)))
		return -1;

	return 0;
}

void Player::ChangeState(State state)
{
	m_state = state;
}

void Player::UpdateMoveState()
{
	VEC2 velocity = GetVelocity();
	bool isMoving = velocity.x != 0.0f;

	ChangeState(isMoving ? State::Run : State::Idle);
	m_animator.Play(isMoving ? "Run" : "Idle");
}

int Player::UpdateState(float deltaTime)
{
	switch (m_state)
	{
	case State::Idle:
		m_animator.Play("Idle");
		break;
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
