#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include "GameObject.h"

class GameManager
{
private:
	std::vector<std::unique_ptr<GameObject>> m_sceneObjects;
	std::vector<std::unique_ptr<GameObject>> m_persistentObjects;

	void DestroyObjects(std::vector<std::unique_ptr<GameObject>>& objects);

	template<typename T>
	T* CreateObject(std::vector<std::unique_ptr<GameObject>>& objects)
	{
		auto object = std::make_unique<T>();
		T* observer = object.get();

		observer->SetActive(true);
		objects.push_back(std::move(object));

		return observer;
	}

public:
	~GameManager();

	int Update(float deltaTime);
	int Render(Camera& camera);

	template <typename T>
	T* CreateSceneObject() { return CreateObject<T>(m_sceneObjects); };

	template <typename T>
	T* CreatePersistentObject() { return CreateObject<T>(m_persistentObjects); };

	void DestroySceneObjects();
};