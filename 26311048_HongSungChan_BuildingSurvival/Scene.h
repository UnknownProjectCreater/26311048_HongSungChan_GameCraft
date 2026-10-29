#pragma once
#include <string>
#include "App.h"

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

	virtual int Init();
	virtual void Destroy();
	virtual int Render();
	virtual int Update();

	
};