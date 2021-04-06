#pragma once

#include "Vector2.h"

#include "IComponent.h"
#include "IEngine.h"
#include "RigidbodyComponent.h"

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
	GameObject(IEngine& engine, Vector2 position);

	virtual void OnUpdate(float deltaTime);
	virtual void OnDraw(float subframe);
	virtual void OnCollision(RigidbodyComponent& other); // WTF GameObject <> RigidbodyComponent sollten nicht interagieren... (besser zu collisiion subscriben)
	
	Vector2 GetPreviousPosition();
	Vector2 GetPosition();
	Vector2 GetDrawPosition(float t);

	void AddComponent(std::unique_ptr <IComponent> component);
	void RemoveComponent(IComponent& component);
};