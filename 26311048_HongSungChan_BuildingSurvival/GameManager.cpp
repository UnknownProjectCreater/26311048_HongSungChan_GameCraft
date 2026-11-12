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

void GameManager::CheckCollision()
{
	for (const auto& object : m_sceneObjects)
		object->BeginCollisionUpdate();

	for (auto object1 = m_sceneObjects.begin(); object1 != m_sceneObjects.end(); object1++)
	{
		GameObject* pObject1 = object1->get();

		if (pObject1 == nullptr || !pObject1->IsActive())
			continue;

		auto object2 = object1;
		++object2;

		for (; object2 != m_sceneObjects.end(); ++object2)
		{
			GameObject* pObject2 = object2->get();

			if (pObject2 == nullptr || !pObject2->IsActive())
				continue;

			CheckAABBCollision(pObject1, pObject2);
		}
	}

	for (const auto& object : m_sceneObjects)
	{
		if (object)
			object->ProcessCollision();
	}
}

bool GameManager::CheckAABBCollision(GameObject* a, GameObject* b)
{
	if (a->GetRight() <= b->GetLeft() || a->GetLeft() >= b->GetRight())
		return false;

	if (a->GetBottom() <= b->GetTop() || a->GetTop() >= b->GetBottom())
		return false;

	float overlapX = min(a->GetRight(), b->GetRight()) - max(a->GetLeft(), b->GetLeft());
	float overlapY = min(a->GetBottom(), b->GetBottom()) - max(a->GetTop(), b->GetTop());

	float aCenterX = (a->GetLeft() + a->GetRight()) * 0.5f;
	float aCenterY = (a->GetTop() + a->GetBottom()) * 0.5f;

	float bCenterX = (b->GetLeft() + b->GetRight()) * 0.5f;
	float bCenterY = (b->GetTop() + b->GetBottom()) * 0.5f;

	if (overlapY < overlapX)
	{
		if (aCenterY < bCenterY)
		{
			a->AddCollider(b, CollisionDirection::Bottom);
			b->AddCollider(a, CollisionDirection::Top);
		}
		else
		{
			a->AddCollider(b, CollisionDirection::Top);
			b->AddCollider(a, CollisionDirection::Bottom);
		}
	}
	else
	{
		if (aCenterX < bCenterX)
		{
			a->AddCollider(b, CollisionDirection::Right);
			b->AddCollider(a, CollisionDirection::Left);
		}
		else
		{
			a->AddCollider(b, CollisionDirection::Left);
			b->AddCollider(a, CollisionDirection::Right);
		}
	}

	return true;
}
