#pragma once

#include "../GameObject.h"

#include "imgui.h"

class Ball : public GameObject
{
	Vector2 velocity_;
public:
	Ball(Vector2 position, Vector2 velocity = { 0.0005,0.0005 });

	void OnUpdate(float deltaTime) override;

	void OnDebugTreeNode() override;

	void OnCollision(RigidbodyComponent& other) override;
};