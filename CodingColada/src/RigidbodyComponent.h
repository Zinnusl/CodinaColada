#pragma once

#include "IComponent.h"
#include "Vector2.h"

/*
* Disclaimer: Collisions are buggy
*/
class RigidbodyComponent : public IComponent
{
protected:
	//TODO this really shouldnt be a raw pointer
	GameObject* gameobject_;
	Vector2 offset_; //distance from GameObject
	Vector2 size_;

public:
	RigidbodyComponent(Vector2 size);

	void OnUpdate(Engine& engine, float deltaTime) override;
	void OnAdded(Engine& engine, GameObject& gameobject) override;
	void OnRemove(Engine& engine) override;
	void OnDraw(Engine& engine) override;
	GameObject& GetGameobject() override;

	bool CheckCollision(RigidbodyComponent& other);
};