#pragma once

#include "Vector2.h"
#include "IComponent.h"

#include <vector>
#include <memory>

class GameObject
{
protected:
	Vector2 position;
	Vector2 rotation;

	std::vector<std::unique_ptr<IComponent>> components;

public:
	virtual void OnUpdate(float deltaTime);
	virtual void AddComponent(std::unique_ptr <IComponent> component);
	virtual void RemoveComponent(std::unique_ptr <IComponent> component);
};