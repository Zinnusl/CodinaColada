#include "GameManager.h"

#include "imgui.h"

#include "../../engine/Engine.h"
#include "../../engine/SpriteComponent.h"
#include "../../engine/AnimatedSpriteComponent.h"

#include "Player.h"

GameManager::GameManager() 
{
}

void GameManager::OnDraw(float subframe, float deltaTime)
{
	GameObject::OnDraw(subframe, deltaTime);

	static float lifeTime = 0;
	lifeTime += deltaTime;

	//if (lifeTime > 32000000)
	{
		RemoveComponent(*splashScreen_);
		RemoveComponent(*loadingAnimation_);
	}

	int GLFW_KEY_ESCAPE = 256;
	int GLFW_KEY_F5 = 294;
	int GLFW_KEY_F2 = 291;
	if (engine_->GetInput().GetKey(GLFW_KEY_F2))
	{
		engine_->StopGame();
	}
	ImGui::Begin("Perfect Path");
	ImGui::Text("Round %d", 10);
	ImGui::Text("Time Left %d", 100);
	ImGui::Text("Player1: %s", "M310nm4n");
	ImGui::Text("Player2: %s", "Zinnusl is love; Zinnusl is life");
	ImGui::End();

}

void GameManager::OnDebugTreeNode()
{
	ImGui::Text("GameManager");
}

void GameManager::OnStart()
{
	splashScreen_ = GetFirstComponentOfType<SpriteComponent>();
	loadingAnimation_ = GetFirstComponentOfType<AnimatedSpriteComponent>();
	engine_->GetAudio().Loop("..\\..\\..\\..\\CodingColada\\game\\common\\resources\\audio\\background_music.mp3", 1, true);
}
