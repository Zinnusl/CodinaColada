#include "GameManager.h"

#include "../Engine.h"
#include "imgui.h"

GameManager::GameManager() 
{
}

void GameManager::OnUpdate(float deltaTime)
{
	GameObject::OnUpdate(deltaTime);

	int GLFW_KEY_ESCAPE = 256;
	if (engine_->GetInput().GetKey(GLFW_KEY_ESCAPE))
	{
		if (components_.size() > 0)
		{
			RemoveComponent(*components_[0]);
		}
		else
		{
			engine_->StopGame();
		}
	}
}

void GameManager::OnDebugTreeNode()
{
	ImGui::Text("GameManager");
}