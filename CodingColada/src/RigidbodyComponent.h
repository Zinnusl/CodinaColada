#pragma once

#include "IComponent.h"
#include "Vector2.h"

#include "RectangleShape.h"
/*
* Disclaimer: Collisions are buggy
*/
class RigidbodyComponent : public IComponent
{
protected:
	//TODO this really shouldnt be a raw pointer
	GameObject* gameobject_;
	std::shared_ptr<RectangleShape> shape_;

public:
	RigidbodyComponent(std::unique_ptr<RectangleShape> shape);

	void OnUpdate(Engine& engine, float deltaTime) override;
	void OnAdded(Engine& engine, GameObject& gameobject) override;
	void OnRemove(Engine& engine) override;
	void OnDraw(Engine& engine, float subframe) override;
	GameObject& GetGameobject() override;

	bool CheckCollision(RigidbodyComponent& other);
};