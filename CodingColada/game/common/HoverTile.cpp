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
}