#include "Ball.h"

#include "../../engine/Engine.h"

#include "imgui.h"

Ball::Ball(Vector2 position, Vector2 velocity)
	: GameObject(position), velocity_(velocity)
{
}

void Ball::OnDraw(float subframe, float deltaTime)
{
	GameObject::OnDraw(subframe, deltaTime);
	currentPosition_ = engine_->GetRenderer().ScreenToWorld(engine_->GetInput().GetMousePosition());
}

void Ball::OnPhysicsUpdate(float deltaTime)
{
	GameObject::OnPhysicsUpdate(deltaTime);

	static float runtime = 0;
	runtime += deltaTime;
	Vector2 newPos = currentPosition_ + velocity_ * deltaTime;

	if (newPos.GetY() <= 0)
	{
		newPos.SetY(0);
		velocity_.SetY(-velocity_.GetY());
	}

	if (newPos.GetX() <= 0)
	{
		newPos.SetX(0);
		velocity_.SetX(-velocity_.GetX());
	}
	
	//currentPosition_ = newPos;
}

void Ball::OnDebugTreeNode()
{
	ImGui::Text("Ball");
	ImGui::Text("Position %f %f", currentPosition_.GetX(), currentPosition_.GetY());
	ImGui::Text("Velocity %f %f", velocity_.GetX(), velocity_.GetY());

	ImGui::Text("camera position x: %f y: %f", engine_->GetRenderer().GetCameraPosition().GetX(), engine_->GetRenderer().GetCameraPosition().GetY());
	ImGui::Text("screen mouse x: %f y: %f", engine_->GetInput().GetMousePosition().GetX(), engine_->GetInput().GetMousePosition().GetY());

	auto x = engine_->GetRenderer().ScreenToWorld(engine_->GetInput().GetMousePosition()).GetX();
	auto y = engine_->GetRenderer().ScreenToWorld(engine_->GetInput().GetMousePosition()).GetY();
	ImGui::Text("ScreenToWorld mouse x: %f y: %f", x, y);
	ImGui::Text("WorldToScreen mouse x: %f y: %f", engine_->GetRenderer().WorldToScreen(x).GetX(), engine_->GetRenderer().WorldToScreen(y).GetY());
}

void Ball::OnCollision(RigidbodyComponent& other)
{
	velocity_.SetX(-velocity_.GetX());
}