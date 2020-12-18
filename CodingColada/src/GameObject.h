#pragma once

#include "Vector2.h"

#include "IComponent.h"

#include <vector>
#include <memory>

class Engine;
class GameObject
{
protected:
	Engine& engine_;
	Vector2 position_;
	Vector2 rotation_;

	std::vector<std::unique_ptr<IComponent>> components_;

public:
	GameObject(Engine& engine);
	virtual void OnUpdate(Engine& engine, float deltaTime);
	
	void AddComponent(std::unique_ptr <IComponent> component);
	void RemoveComponent(std::unique_ptr <IComponent> component);
};