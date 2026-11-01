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

protected:
	int UpdateState(float deltaTime) override;

public:
	int Init(const std::string& key) override;

	void ChangeState(State state);

	State GetState() const { return m_state; };
	bool IsInvincible() const { return m_isInvincible; };
};