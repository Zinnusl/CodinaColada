#pragma once 

#include "Grid.h"

#include "../Engine.h"
#include "../opengl/OpenGLRectangleShape.h"
#include "../ShapeComponent.h"
#include "../RigidbodyComponent.h"

#include "imgui.h"

#include <memory>


Grid::Grid(int32_t rows, int32_t columns, int32_t tileSize, int32_t tileOffset)
	: rows_(rows), columns_(columns), tileSize_(tileSize), tileOffset_(tileOffset)
{

}

void Grid::OnUpdate(float deltaTime)
{
	GameObject::OnUpdate(deltaTime);

	leftClicked_ = GameObject::engine_->GetInput().GetMouseDown(0);
}

void Grid::OnDebugTreeNode()
{
	ImGui::Text("Grid");
	ImGui::Checkbox("LeftClicked", &leftClicked_);
}