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
	Vector2 size_;

public:
	RigidbodyComponent() = delete;
	RigidbodyComponent(Vector2 size);

<<<<<<< HEAD:CodingColada/engine/RigidbodyComponent.h
	void OnUpdate(Engine& engine, float deltaTime) override;
	void OnAdded(Engine& engine, GameObject& gameobject) override;
	void OnRemove(Engine& engine) override;
	GameObject& GetGameobject() override;

	bool CheckCollision(RigidbodyComponent& other);

	// Inherited via IComponent
	virtual void OnDraw(Engine& engine, float subframe, float deltaTime) override;
=======
	void OnUpdate(IEngine& engine, float deltaTime) override;
	void OnAdded(IEngine& engine, GameObject& gameobject) override;
	void OnRemove(IEngine& engine) override;
	void OnDraw(IEngine& engine, float subframe) override;
	GameObject& GetGameobject() override;

	bool CollidesWith(RigidbodyComponent& other);
>>>>>>> origin:CodingColada/src/RigidbodyComponent.h
};