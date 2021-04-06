#pragma once

#include "../../engine/GameObject.h"

#include "imgui.h"

class Ball : public GameObject
{
	Vector2 velocity_;
public:
	Ball(Vector2 position, Vector2 velocity = { 0.0005,0.0005 });

	virtual void OnDraw(float subframe, float deltaTime) override;
	void OnPhysicsUpdate(float deltaTime) override;

	void OnDebugTreeNode() override;

	void OnCollision(RigidbodyComponent& other) override;
};