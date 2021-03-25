#include "Tile.h"

#include "imgui.h"


Tile::Tile(Vector2 position)
{
	currentPosition_ = position;
}

void Tile::OnUpdate(float deltaTime)
{
	GameObject::OnUpdate(deltaTime);
}

void Tile::OnDebugTreeNode()
{
	ImGui::Text("Tile %f %f", currentPosition_.GetX(), currentPosition_.GetY());
}