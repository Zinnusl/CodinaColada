#include "GameManager.h"

#include "../../engine/Engine.h"
#include "imgui.h"

GameManager::GameManager() 
{
}

void GameManager::OnDraw(float subframe, float deltaTime)
{
	GameObject::OnDraw(subframe, deltaTime);

	int GLFW_KEY_ESCAPE = 256;
	int GLFW_KEY_F5 = 294;
	int GLFW_KEY_F2 = 291;
	if (engine_->GetInput().GetKey(GLFW_KEY_F2))
	{
		engine_->StopGame();
	}
}

void GameManager::OnDebugTreeNode()
{
	ImGui::Text("GameManager");
}