#include "Paddle.h"

#include "../../engine/Engine.h"

#include "imgui.h"

Paddle::Paddle()
{
}

Paddle::Paddle(Vector2 position)
	: GameObject(position)
{
}

void Paddle::OnPhysicsUpdate(float deltaTime)
{
	GameObject::OnPhysicsUpdate(deltaTime);

	#define 	GLFW_KEY_DOWN   264
	#define 	GLFW_KEY_UP   265

	const int maxMove = engine_->GetRenderer().GetResolution().GetY() - 200;
	if (GameObject::engine_->GetInput().GetKey(GLFW_KEY_DOWN))
	{
		float yPos = currentPosition_.GetY();
		if (currentPosition_.GetY() > 0)
		{
			float newPos = currentPosition_.GetY() - speed * deltaTime;
			if (newPos < 0)
			{
				newPos = 0;
			}
			currentPosition_.SetY(newPos);
		}
	}
	if (GameObject::engine_->GetInput().GetKey(GLFW_KEY_UP))
	{
		float yPos = currentPosition_.GetY();
		if (currentPosition_.GetY() < maxMove)
		{
			float newPos = currentPosition_.GetY() + speed * deltaTime;
			if (newPos > maxMove)
			{
				newPos = maxMove;
			}
			currentPosition_.SetY(newPos);
		}
	}
}

void Paddle::OnDebugTreeNode()
{
	ImGui::Text("Paddle");
}