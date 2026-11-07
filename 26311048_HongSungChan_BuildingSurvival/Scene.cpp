#include "Scene.h"

Scene::Scene()
{
	
}

int Scene::Init()
{
	m_font1 = g2_FontCreate("깍두기 도면체", 100);

	return 0;
}

int Scene::Update(float deltaTime)
{
	return 0;
}

int Scene::Render(Camera& camera)
{
	return 0;
}

void Scene::Destroy()
{
	g2_SoundStop(m_currentBGM);
}