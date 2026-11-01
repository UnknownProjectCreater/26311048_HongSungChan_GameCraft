#pragma once
#include <string>
#include "Camera.h"
#include "glc2d.h"

enum class GamePhase
{
	BEGIN = 0,
	START,
	PLAY,
	RESULT
};

class Scene
{
protected:
	int m_font1{ -1 };
	GamePhase m_sceneType;

public:
	Scene();
	virtual ~Scene() = default;

	virtual int Init();
	virtual void Destroy();
	virtual int Render(const Camera& camera);
	virtual int Update(float deltaTime);
};