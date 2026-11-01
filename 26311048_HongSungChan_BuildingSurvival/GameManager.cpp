#include "GameManager.h"

GameManager::~GameManager()
{
	DestroyObjects(m_sceneObjects);
	DestroyObjects(m_persistentObjects);
}

int GameManager::Update(float deltaTime)
{
	for (const auto& object : m_sceneObjects)
		object->Update(deltaTime);

	for (const auto& object : m_persistentObjects)
		object->Update(deltaTime);

	return 0;
}

int GameManager::Render(const Camera& camera)
{
	for (const auto& object : m_sceneObjects)
		object->Render(camera);

	for (const auto& object : m_persistentObjects)
		object->Render(camera);

	return 0;
}

void GameManager::DestroyObjects(std::vector<GameObject*>& objects)
{
	for (GameObject* object : objects)
	{
		object->Destroy();
		delete object;
	}

	objects.clear();
}

void GameManager::DestroySceneObjects()
{
	DestroyObjects(m_sceneObjects);
}