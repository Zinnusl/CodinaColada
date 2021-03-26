#pragma once

#include "IComponent.h"
#include "Vector2.h"

/*
* Disclaimer: Collisions are buggy
*/
class RigidbodyComponent : public IComponent
{
protected:
	GameObject* gameobject_;
	Vector2 offset_; //distance from GameObject
	Vector2 size_;

public:
	RigidbodyComponent(Vector2 size);

	void OnUpdate(IEngine& engine, float deltaTime) override;
	void OnAdded(IEngine& engine, GameObject& gameobject) override;
	void OnRemove(IEngine& engine) override;
	void OnDraw(IEngine& engine, float subframe) override;
	GameObject& GetGameobject() override;

	bool CollidesWith(RigidbodyComponent& other);
};