#pragma once

#include "Vector2.h"

#include "IComponent.h"
#include "IEngine.h"

#include <vector>
#include <memory>

class GameObject
{
protected:
	IEngine& engine_;
	Vector2 position_;
	Vector2 rotation_;

	std::vector<std::unique_ptr<IComponent>> components_;

public:
	GameObject(IEngine& engine);
	virtual void OnUpdate(IEngine& engine, float deltaTime);
	
	void AddComponent(std::unique_ptr <IComponent> component);
	void RemoveComponent(std::unique_ptr <IComponent> component);
};