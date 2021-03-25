#pragma once 

#include "Grid.h"

#include "../Engine.h"
#include "Tile.h"
#include "../opengl/OpenGLRectangleShape.h"
#include "../ShapeComponent.h"
#include "../RigidbodyComponent.h"

#include "imgui.h"

#include <memory>


Grid::Grid(int32_t rows, int32_t columns, int32_t tileSize, int32_t tileOffset)
	: rows_(rows), columns_(columns), tileSize_(tileSize), tileOffset_(tileOffset)
{
	/*
	for (int32_t row = 0; row < rows_; row++)
	{
		for (int32_t column = 0; column < columns_; column++)
		{
			auto tile = std::make_unique<Tile>(Vector2(row * tileOffset_, column * tileOffset_));
			tile->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(Vector2(tileSize_), Color(0.3, 0.3, 0.3, 0.1))));
			//tile->AddComponent(std::make_unique<RigidbodyComponent>(std::make_unique<OpenGLRectangleShape>(Vector2(tileSize_), Color(0, 1, 0, 0.2))));
			GameObject::engine_->AddGameObject(std::move(tile));
		}
	}
	*/
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