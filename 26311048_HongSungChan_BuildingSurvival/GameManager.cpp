#include <algorithm>
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

int GameManager::Render(Camera& camera)
{
	std::vector<GameObject*> m_renderObjects{};

	m_renderObjects.reserve(m_sceneObjects.size() + m_persistentObjects.size());

	for (auto& obj : m_sceneObjects) m_renderObjects.push_back(obj.get());
	for (auto& obj : m_persistentObjects) m_renderObjects.push_back(obj.get());

	std::sort(m_renderObjects.begin(), m_renderObjects.end(), [](GameObject* a, GameObject* b) {return a->GetPosition().y < b->GetPosition().y;});

	for (auto* obj : m_renderObjects) {
		obj->Render(camera);
	}

	return 0;
}

void GameManager::DestroyObjects(std::vector<std::unique_ptr<GameObject>>& objects)
{
	for (const auto& object : objects)
		object->Destroy();

	objects.clear();
}

void GameManager::DestroySceneObjects()
{
	DestroyObjects(m_sceneObjects);
}