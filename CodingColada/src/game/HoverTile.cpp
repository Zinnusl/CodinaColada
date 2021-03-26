#pragma once 

#include "HoverTile.h"

#include "../Engine.h"
#include "tower/Tower.h"
#include "../SpriteComponent.h"
#include "../RigidbodyComponent.h"
#include "../opengl/OpenGLSprite.h"
#include "../opengl/OpenGLRenderer.h"

#include "Grid.h"

#include "imgui.h"


HoverTile::HoverTile(Grid& grid)
	: grid_(grid)
{

}

void HoverTile::OnPhysicsUpdate(float deltaTime)
{
	//TODO critical.. forgetting to call "super" method results in nasty buggs.. maybe we need update_internal so the engine can handle internal stuff
	GameObject::OnPhysicsUpdate(deltaTime);
}

void HoverTile::OnDebugTreeNode()
{
	ImGui::Text("HoverTile Position %f %f", currentPosition_.GetX(), currentPosition_.GetY());
}

void HoverTile::OnDraw(float subframe)
{
	GameObject::OnDraw(subframe);

	//TODO an object like this should probably not be smooth moved (this movement is dependend on physic ticks.. really dont want this here)
	Vector2 mousePos = engine_->GetInput().GetMousePosition();
	//TODO really shouldnt need to substract screen resolution.. check coordinate systems
	float halfScreenHeight = engine_->GetRenderer().GetWindow().GetResolution().GetY() / 2;
	float delta = mousePos.GetY() - halfScreenHeight;
	float newPosY = mousePos.GetY() - delta * 2;
	mousePos.SetY(newPosY - fmod(newPosY, grid_.GetCellSize()));

	mousePos.SetX(mousePos.GetX() - fmod(mousePos.GetX(), grid_.GetCellSize()));
	currentPosition_ = mousePos;

	if (GameObject::engine_->GetInput().GetMouseDown(0))
	{
		auto tower = std::make_unique<Tower>(currentPosition_);
		tower->AddComponent(std::make_unique<SpriteComponent>(std::make_unique<OpenGLSprite>(glm::vec2(64, 64), OpenGLRenderer::shaders_["sprite"], OpenGLRenderer::textures_["tower_canon"])));
		tower->AddComponent(std::make_unique<RigidbodyComponent>(Vector2(64)));
		engine_->AddGameObject(std::move(tower));
	}
	if (GameObject::engine_->GetInput().GetMouseDown(1))
	{
		auto stone = std::make_unique<Tower>(currentPosition_);
		stone->AddComponent(std::make_unique<SpriteComponent>(std::make_unique<OpenGLSprite>(glm::vec2(64, 64), OpenGLRenderer::shaders_["sprite"], OpenGLRenderer::textures_["stone"])));
		stone->AddComponent(std::make_unique<RigidbodyComponent>(Vector2(64)));
		engine_->AddGameObject(std::move(stone));
	}
}