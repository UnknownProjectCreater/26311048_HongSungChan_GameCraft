#pragma once
class Scene
{
public:
	virtual int Init();
	virtual void Destroy();
	virtual int Render();
	virtual int Update();
};