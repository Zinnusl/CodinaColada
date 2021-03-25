#pragma once 

#include "Grid.h"

#include "../Engine.h"
#include "Tile.h"
#include "../opengl/OpenGLRectangleShape.h"
#include "../ShapeComponent.h"
#include "../RigidbodyComponent.h"

#include "imgui.h"

#include <memory>


Grid::Grid(int32_t rows, int32_t columns)
	: rows_(rows), columns_(columns)
{
	for (int32_t row = 0; row < rows_; row++)
	{
		for (int32_t column = 0; column < columns_; column++)
		{
			auto tile = std::make_unique<Tile>(Vector2(row * 100, column * 100));
			tile->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(Vector2(64), Color(1, 0, 0, 1))));
			tile->AddComponent(std::make_unique<RigidbodyComponent>(Vector2(64)));
			GameObject::engine_->AddGameObject(std::move(tile));
		}
	}
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