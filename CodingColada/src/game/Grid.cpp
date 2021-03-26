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
#include "tower/Tower.h"

#include "imgui.h"



Grid::Grid(int32_t cellSize)
	: cellSize_(cellSize), hoverTile_(std::make_unique<HoverTile>(*this))
{
	Vector2 hoverTileSize = Vector2(64, 64);
	hoverTile_->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(hoverTileSize, Color(0, 0, 1, 0.1), &OpenGLRenderer::shaders_["hover"])));
	hoverTile_->AddComponent(std::make_unique<SpriteComponent>(std::make_unique<OpenGLSprite>(glm::vec2(64, 64), OpenGLRenderer::shaders_["sprite"], OpenGLRenderer::textures_["hovertile"])));

	//TODO The grid is now responsible for calling the callbacks of the hovertile.. is this soemthing we want? Or does this go against the goal of the engine?
	//Pro: We can avoid invoking callbacks that we know we wont need
	//Contra: Could introduce buggs because we forget to handle callbacks. Especially when new callbacks are introduced.
	//buildings_.push_back(std::move(hoverTile));
}

void Grid::OnPhysicsUpdate(float deltaTime)
{
	GameObject::OnPhysicsUpdate(deltaTime);
	for (auto& building : buildings_)
	{
		building->OnPhysicsUpdate(deltaTime);
	}
	hoverTile_->OnPhysicsUpdate(deltaTime);
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
	hoverTile_->OnDebugTreeNode();
}

void Grid::OnDraw(float subframe)
{
	GameObject::OnDraw(subframe);
	for (auto& building : buildings_)
	{
		building->OnDraw(subframe);
	}
	hoverTile_->OnDraw(subframe);


	
	ShapeComponent* shapeComponent = hoverTile_->GetFirstComponentOfType<ShapeComponent>();
	SpriteComponent* spriteComponent = hoverTile_->GetFirstComponentOfType<SpriteComponent>();
	bool isCellFree = IsCellFree(hoverTile_->GetPosition());
	if (isCellFree)
	{
		//TODO API: this is bad.. how can I change the color of a shape with logic on the parent gameobject??
		((RectangleShape*)(shapeComponent->GetShape().get()))->SetColor(Color(0, 255, 0, 255));
		spriteComponent->GetSprite().get()->SetColor(Color(255, 255, 255, 255));
	}
	else
	{
		//TODO API: this is bad.. how can I change the color of a shape with logic on the parent gameobject??
		((RectangleShape*)(shapeComponent->GetShape().get()))->SetColor(Color(255, 0, 0, 255));
		spriteComponent->GetSprite().get()->SetColor(Color(255, 0, 0, 255));
	}
	


	if (GameObject::engine_->GetInput().GetMouseDown(0) && isCellFree)
	{
		auto tower = std::make_shared<Tower>(hoverTile_->GetPosition());
		tower->AddComponent(std::make_unique<SpriteComponent>(std::make_unique<OpenGLSprite>(glm::vec2(64, 64), OpenGLRenderer::shaders_["sprite"], OpenGLRenderer::textures_["tower_canon"])));
		tower->AddComponent(std::make_unique<RigidbodyComponent>(Vector2(64)));
		buildings_.push_back(std::move(tower));
	}
	if (GameObject::engine_->GetInput().GetMouseDown(1) && isCellFree)
	{
		auto stone = std::make_unique<Tower>(hoverTile_->GetPosition());
		stone->AddComponent(std::make_unique<SpriteComponent>(std::make_unique<OpenGLSprite>(glm::vec2(64, 64), OpenGLRenderer::shaders_["sprite"], OpenGLRenderer::textures_["stone"])));
		stone->AddComponent(std::make_unique<RigidbodyComponent>(Vector2(64)));
		buildings_.push_back(std::move(stone));
	}
}

void Grid::OnCollision(RigidbodyComponent& other)
{
	GameObject::OnCollision(other);

	for (auto& building : buildings_)
	{
		building->OnCollision(other);
	}
	hoverTile_->OnCollision(other);
}

int32_t Grid::GetCellSize()
{
	return cellSize_;
}

bool Grid::IsCellFree(Vector2 position)
{
	bool free = true;
	for (auto& building : buildings_)
	{
		if (building->GetPosition() == position)
		{
			free = false;
			break;
		}
	}
	return free;
}