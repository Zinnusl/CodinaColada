#pragma once 

#include "Grid.h"

#include "../Engine.h"
#include "../opengl/OpenGLRenderer.h"
#include "../opengl/OpenGLRectangleShape.h"
#include "../ShapeComponent.h"
#include "../SpriteComponent.h"
#include "../opengl/OpenGLSprite.h"
#include "../RigidbodyComponent.h"

#include "HoverTile.h"

#include "imgui.h"

#include <memory>


Grid::Grid(int32_t cellSize)
	: cellSize_(cellSize)
{
	Vector2 hoverTileSize = Vector2(64, 64);
	auto hoverTile = std::make_unique<HoverTile>(*this);
	hoverTile->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(hoverTileSize, Color(0, 0, 1, 0.1), &OpenGLRenderer::shaders_["hover"])));
	hoverTile->AddComponent(std::make_unique<SpriteComponent>(std::make_unique<OpenGLSprite>(glm::vec2(64, 64), OpenGLRenderer::shaders_["sprite"], OpenGLRenderer::textures_["hovertile"])));

	//TODO The grid is now responsible for calling the callbacks of the hovertile.. is this soemthing we want? Or does this go against the goal of the engine?
	//Pro: We can avoid invoking callbacks that we know we wont need
	//Contra: Could introduce buggs because we forget to handle callbacks. Especially when new callbacks are introduced.
	buildings_.push_back(std::move(hoverTile));
}

void Grid::OnPhysicsUpdate(float deltaTime)
{
	GameObject::OnPhysicsUpdate(deltaTime);
	for (auto& building : buildings_)
	{
		building->OnPhysicsUpdate(deltaTime);
	}
}

void Grid::OnDebugTreeNode()
{
	GameObject::OnDebugTreeNode();
	ImGui::Text("Grid");
	ImGui::Text("PixelSize %d", cellSize_);

	//TODO also nice about this taking responsiblity is that it can render stuff for its children
	for (auto& building : buildings_)
	{
		building->OnDebugTreeNode();
	}
}

void Grid::OnDraw(float subframe)
{
	GameObject::OnDraw(subframe);
	for (auto& building : buildings_)
	{
		building->OnDraw(subframe);
	}
}

void Grid::OnCollision(RigidbodyComponent& other)
{
	GameObject::OnCollision(other);
	for (auto& building : buildings_)
	{
		building->OnCollision(other);
	}
}

int32_t Grid::GetCellSize()
{
	return cellSize_;
}