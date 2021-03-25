#pragma once 

#include "HoverTile.h"

#include "../Engine.h"
#include "imgui.h"


HoverTile::HoverTile(Vector2 size)
	: size_(size)
{

}

void HoverTile::OnUpdate(float deltaTime)
{
	//TODO critical.. forgetting to call "super" method results in nasty buggs.. maybe we need update_internal so the engine can handle internal stuff
	GameObject::OnUpdate(deltaTime);

	//TODO an object like this should probably not be smooth moved (this movement is dependend on physic ticks.. really dont want this here)
	Vector2 mousePos = engine_->GetInput().GetMousePosition();
	//TODO really shouldnt need to substract screen resolution.. check coordinate systems
	float halfScreenHeight = engine_->GetRenderer().GetWindow().GetResolution().GetY() / 2;
	float delta = mousePos.GetY() - halfScreenHeight;
	float newPosY = mousePos.GetY() - delta * 2;
	mousePos.SetY(newPosY - fmod(newPosY, size_.GetY()));


	mousePos.SetX(mousePos.GetX() - fmod(mousePos.GetX(), size_.GetX()));
	currentPosition_ = mousePos;
}

void HoverTile::OnDebugTreeNode()
{
	ImGui::Text("Position %f %f", currentPosition_.GetX(), currentPosition_.GetY());
}