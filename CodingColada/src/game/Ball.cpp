#include "Ball.h"

#include "../Engine.h"
#include "../CodinaColadaWindow.h"

#include "imgui.h"

Ball::Ball(Vector2 position, Vector2 velocity)
	: GameObject(position), velocity_(velocity)
{
}

void Ball::OnUpdate(float deltaTime)
{
	GameObject::OnUpdate(deltaTime);

	static float runtime = 0;
	runtime += deltaTime;
	Vector2 newPos = currentPosition_ + velocity_ * deltaTime;

	if (newPos.GetY() <= 0)
	{
		newPos.SetY(0);
		velocity_.SetY(-velocity_.GetY());
	}
	if (newPos.GetY() >= engine_->GetRenderer().GetWindow().GetResolution().GetY()) //size nicht vergessen
	{
		newPos.SetY(engine_->GetRenderer().GetWindow().GetResolution().GetY());
		velocity_.SetY(-velocity_.GetY());
	}

	if (newPos.GetX() <= 0)
	{
		newPos.SetX(0);
		velocity_.SetX(-velocity_.GetX());
	}
	if (newPos.GetX() >= engine_->GetRenderer().GetWindow().GetResolution().GetX()) //size nicht vergessen
	{
		newPos.SetX(engine_->GetRenderer().GetWindow().GetResolution().GetX());
		velocity_.SetX(-velocity_.GetX());
	}
	currentPosition_ = newPos;
}

void Ball::OnDebugTreeNode()
{
	ImGui::Text("Ball");
	ImGui::Text("Velocity %f %f", velocity_.GetX(), velocity_.GetY());
}

void Ball::OnCollision(RigidbodyComponent& other)
{
	velocity_.SetX(-velocity_.GetX());
}