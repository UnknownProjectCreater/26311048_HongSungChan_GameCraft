#pragma once
#include <vector>
#include <unordered_map>
#include "GameObject.h"

class GameManager
{
private:
	std::vector<GameObject*> m_sceneObjects;
	std::vector<GameObject*> m_persistentObjects;

	void DestroyObjects(std::vector<GameObject*>& objects);

	template<typename T>
	T* CreateObject(std::vector<GameObject*>& objects)
	{
		T* object = new T();
		object->SetActive(true);
		objects.push_back(object);

		return object;
	}

public:
	~GameManager();

	int Update(float deltaTime);
	int Render(const Camera& camera);

	template <typename T>
	T* CreateSceneObject() { return CreateObject<T>(m_sceneObjects); };

	template <typename T>
	T* CreatePersistentObject() { return CreateObject<T>(m_persistentObjects); };

	void DestroySceneObjects();
};