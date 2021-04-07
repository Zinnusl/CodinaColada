#pragma once 

#include "../../engine/Engine.h"
#include "../../engine/RectangleShape.h"
#include "../../engine/ShapeComponent.h"
#include "../../engine/SpriteComponent.h"
#include "../../engine/RigidbodyComponent.h"
#include "../../engine/opengl/OpenGLSprite.h"
#include "../../engine/opengl/OpenGLRenderer.h"

#include "tower/Tower.h"

#include "HoverTile.h"
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
	ImGui::Separator();
	ImGui::Text("HoverTile");
	ImGui::Text("Position %f %f", currentPosition_.GetX(), currentPosition_.GetY());

	Vector2 worldMousePos = engine_->GetRenderer().ScreenToWorld(engine_->GetInput().GetMousePosition());
	
	ImGui::Text("worldMousePos Position %f %f", worldMousePos.GetX(), worldMousePos.GetY());
	ImGui::Text("worldMousePos MOD Position %f %f", fmod(worldMousePos.GetX(), grid_.GetCellSize()), fmod(worldMousePos.GetY(), grid_.GetCellSize()));

	ImGui::Separator();
}

void HoverTile::OnDraw(float subframe, float deltaTime)
{
	GameObject::OnDraw(subframe, deltaTime);

	//TODO an object like this should probably not be smooth moved (this movement is dependend on physic ticks.. really dont want this here)
	Vector2 worldMousePos = engine_->GetRenderer().ScreenToWorld(engine_->GetInput().GetMousePosition());

	Vector2 newPos;

	if (worldMousePos.GetX() < 0)
	{
		newPos.SetX(worldMousePos.GetX() - fmod(worldMousePos.GetX(), grid_.GetCellSize()) - grid_.GetCellSize());
	}
	else
	{
		newPos.SetX(worldMousePos.GetX() - fmod(worldMousePos.GetX(), grid_.GetCellSize()));
	}

	if(worldMousePos.GetY() < 0)
	{
		newPos.SetY(worldMousePos.GetY() - fmod(worldMousePos.GetY(), grid_.GetCellSize()) - grid_.GetCellSize());
	}
	else
	{
		newPos.SetY(worldMousePos.GetY() - fmod(worldMousePos.GetY(), grid_.GetCellSize()));
	}

	currentPosition_ = newPos;
}