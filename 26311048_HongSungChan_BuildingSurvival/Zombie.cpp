#include "Zombie.h"

int Zombie::Init(const std::string& key)
{
	if (0 > GameObject::Init(key))
		return -1;

	// One clip per direction: row = EntityDir. The last column of each sheet is a text label
	for (int row = 0; row <= (int)EntityDir::LEFT; row++)
	{
		std::string suffix = "_" + std::to_string(row);

		if (0 > m_animator.Add("Idle" + suffix, GetAnimationManager()->LoadClip("Zombie_Idle" + suffix, 32, 32, 2, 0.3f, true, row)))
			return -1;
		if (0 > m_animator.Add("Run" + suffix, GetAnimationManager()->LoadClip("Zombie_Walk" + suffix, 32, 32, 4, 0.1f, true, row)))
			return -1;
	}

	return 0;
}

std::string Zombie::GetClipKey(const std::string& name) const
{
	return name + "_" + std::to_string((int)GetEntityDir());
}

void Zombie::ChangeState(State state)
{
	m_state = state;
}

void Zombie::UpdateMoveState()
{
	VEC2 velocity = GetVelocity();
	bool isMoving = velocity.x != 0.0f || velocity.y != 0.0f;

	ChangeState(isMoving ? State::Run : State::Idle);

	// Only swap the sheet: SetTexture would also overwrite m_scaling
	m_image.m_texture = GetTextureManager()->GetTexture(isMoving ? "Zombie_Walk" : "Zombie_Idle").m_texture;
	m_animator.Play(GetClipKey(isMoving ? "Run" : "Idle"));
}

int Zombie::UpdateState(float deltaTime)
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
