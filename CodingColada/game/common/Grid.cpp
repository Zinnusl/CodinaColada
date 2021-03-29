#pragma once 

#include "Grid.h"

#include "../../engine/Engine.h"
#include "../../engine/opengl/OpenGLRenderer.h"
#include "../../engine/opengl/OpenGLRectangleShape.h"
#include "../../engine/ShapeComponent.h"
#include "../../engine/SpriteComponent.h"
#include "../../engine/opengl/OpenGLSprite.h"
#include "../../engine/RigidbodyComponent.h"

#include "HoverTile.h"
#include "PathTile.h"
#include "tower/Tower.h"

#include "imgui.h"

#include <chrono>


Grid::Grid(int32_t cellSize)
	: cellSize_(cellSize), hoverTile_(std::make_unique<HoverTile>(*this))
{

	for (int x = 0; x < 64; x++)
	{
		for (int y = 0; y < 64; y++)
		{
			nodes_[x][y] = new Node(x, y);
		}
	}
	Vector2 hoverTileSize = Vector2(64, 64);
	hoverTile_->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(hoverTileSize, Color(0, 0, 1, 0.1), &OpenGLRenderer::shaders_["hover"])));
	hoverTile_->AddComponent(std::make_unique<SpriteComponent>(std::make_unique<OpenGLSprite>(glm::vec2(64, 64), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["hovertile"])));

	//TODO The grid is now responsible for calling the callbacks of the hovertile.. is this soemthing we want? Or does this go against the goal of the engine?
	//Pro: We can avoid invoking callbacks that we know we wont need
	//Contra: Could introduce buggs because we forget to handle callbacks. Especially when new callbacks are introduced. Also OnCollision won't work with override since the parent has to collide for the callback to run..
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
	for (auto& pathNode : pathVisualisation_)
	{
		pathNode->OnPhysicsUpdate(deltaTime);
	}

	pathVisualisation_.clear();
	FindPath(Vector2(100, 100), hoverTile_->GetPosition());
}

void Grid::OnDebugTreeNode()
{
	GameObject::OnDebugTreeNode();
	ImGui::Text("Grid");
	ImGui::Text("PixelSize %d", cellSize_);
	ImGui::Text("A* Pathtime %dms", timeToFindPath_);

	ImGui::Text("PATH");
	for (auto& node : path_)
	{
		ImGui::Text("%d %d", node->gridX_, node->gridY_);
	}

	for (auto& building : buildings_)
	{
		building->OnDebugTreeNode();
	}
	hoverTile_->OnDebugTreeNode();
}

void Grid::OnDraw(float subframe)
{
	GameObject::OnDraw(subframe);

	//draw path visualisation
	for (auto& pathNode : pathVisualisation_)
	{
		pathNode->OnDraw(subframe);
	}

	for (auto& building : buildings_)
	{
		building->OnDraw(subframe);
	}
	hoverTile_->OnDraw(subframe);
	
	bool isCellFree = IsCellFree(hoverTile_->GetPosition());
	if (isCellFree)
	{
		//TODO API: this is bad.. how can I change the color of a shape with logic on the parent gameobject??
		((RectangleShape*)(shapeComponent_->GetShape().get()))->SetColor(Color(0, 255, 0, 255));
		spriteComponent_->GetSprite().get()->SetColor(Color(255, 255, 255, 255));
	}
	else
	{
		//TODO API: this is bad.. how can I change the color of a shape with logic on the parent gameobject??
		((RectangleShape*)(shapeComponent_->GetShape().get()))->SetColor(Color(255, 0, 0, 255));
		spriteComponent_->GetSprite().get()->SetColor(Color(255, 0, 0, 255));
	}
	
	if (GameObject::engine_->GetInput().GetMouseDown(0) && isCellFree)
	{
		auto tower = std::make_shared<Tower>(hoverTile_->GetPosition());
		tower->AddComponent(std::make_unique<SpriteComponent>(std::make_unique<OpenGLSprite>(glm::vec2(64, 64), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["tower_canon"])));
		tower->AddComponent(std::make_unique<RigidbodyComponent>(Vector2(64)));
		buildings_.push_back(std::move(tower));
	}
	if (GameObject::engine_->GetInput().GetMouse(1) && isCellFree)
	{
		auto stone = std::make_unique<Tower>(hoverTile_->GetPosition());
		stone->AddComponent(std::make_unique<SpriteComponent>(std::make_unique<OpenGLSprite>(glm::vec2(64, 64), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["stone"])));
		stone->AddComponent(std::make_unique<RigidbodyComponent>(Vector2(64)));
		buildings_.push_back(std::move(stone));
		auto hoveredNode = GetNodeFromPosition(hoverTile_->GetPosition());
		if (hoveredNode)
		{
			hoveredNode->walkable_ = false;
		}
	}
}

void Grid::OnCollision(RigidbodyComponent& other)
{
	GameObject::OnCollision(other);

	//TODO critical. This doesnt work! Because in order for this to run, the grid has to collide!
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

void Grid::OnStart()
{
	shapeComponent_ = hoverTile_->GetFirstComponentOfType<ShapeComponent>();
	spriteComponent_ = hoverTile_->GetFirstComponentOfType<SpriteComponent>();
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

void Grid::FindPath(Vector2 start, Vector2 end)
{
	auto startTime = std::chrono::steady_clock::now();

	Node* startNode = GetNodeFromPosition(start);
	Node* targetNode = GetNodeFromPosition(end);

	if (!startNode || !startNode->walkable_ || !targetNode || !targetNode->walkable_)
	{
		return;
	}

	std::vector<Node*> openSet;
	std::vector<Node*> closedSet;

 	openSet.push_back(startNode);

	while (!openSet.empty())
	{
		//find node with lowest f-cost
		Node* currentNode = openSet[0];
		for (int i = 1; i < openSet.size(); i++) {
			if (openSet[i]->fCost() < currentNode->fCost() || openSet[i]->fCost() == currentNode->fCost() && openSet[i]->hCost_ < currentNode->hCost_)
			{
				currentNode = openSet[i];
			}
		}
		//remove lowest cost node from openSet
		openSet.erase(std::remove(openSet.begin(), openSet.end(), currentNode), openSet.end());
		closedSet.push_back(currentNode);

		if (currentNode == targetNode) 
		{
			RetracePath(startNode, targetNode);
			auto endTime = std::chrono::steady_clock::now();
			timeToFindPath_ = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
			return;
		}

		for (Node* neighbour : GetNeighbours(currentNode))
		{
			auto neighbours = GetNeighbours(currentNode);
			if (!neighbour)
			{
				continue;
			}
			if (!neighbour->walkable_ || std::find(closedSet.begin(), closedSet.end(), neighbour) != closedSet.end())
			{
				continue;
			}

			int newMovementCostToNeighbour = currentNode->gCost_ + GetDistance(currentNode, neighbour);
			if (newMovementCostToNeighbour < neighbour->gCost_ || std::find(openSet.begin(), openSet.end(), neighbour) == openSet.end())
			{
				neighbour->gCost_ = newMovementCostToNeighbour;
				neighbour->hCost_ = GetDistance(neighbour, targetNode);
				neighbour->parent = currentNode;

				if (std::find(openSet.begin(), openSet.end(), neighbour) == openSet.end())
				{
					openSet.push_back(neighbour);
				}
			}
		}
	}
}

std::vector<Grid::Node*> Grid::GetNeighbours(Node* node)
{
	std::vector<Node*> neighbours;

	for (int x = -1; x <= 1;  x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			if (x == 0 && y == 0)
			{
				//skip the node itself
				continue;
			}

			int checkX = node->gridX_ + x;
			int checkY = node->gridY_ + y;

			if (checkX >= 0 && checkX < gridSize_.GetX() && checkY >= 0 && checkY < gridSize_.GetY())
			{
				neighbours.push_back(nodes_[checkX][checkY]);
			}
		}
	}

	return neighbours;
}

int Grid::GetDistance(Node* a, Node* b)
{
	int dstX = abs(a->gridX_ - b->gridX_);
	int dstY = abs(a->gridY_ - b->gridY_);

	if (dstX > dstY)
	{
		return 14 * dstY + 10 * (dstX - dstY);
	}
	return 14 * dstX + 10 * (dstY - dstX);
}

void Grid::RetracePath(Node* startNode, Node* endNode)
{
	std::vector<Node*> path;
	Node* currentNode = endNode;
	
	while (currentNode != startNode)
	{
		path.push_back(currentNode);
		currentNode = currentNode->parent;
	}
	std::reverse(std::begin(path), std::end(path));
	path_ = path;

	for (auto& node : path_)
	{
		Vector2 pathTileSize = Vector2(64, 64);
		std::unique_ptr<PathTile> pathTile = std::make_unique<PathTile>(Vector2(node->gridX_ * 64, node->gridY_ * 64));
		pathTile->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(pathTileSize, Color(0, 0, 1, 1))));
		pathVisualisation_.push_back(std::move(pathTile));
	}
}

Grid::Node* Grid::GetNodeFromPosition(Vector2 position)
{
	if (position.GetX() < 0 || position.GetY() < 0  || position.GetX() > 64*64 || position.GetY() > 64 * 64)
	{
		return nullptr;
	}
	return nodes_[(int)position.GetX() / 64][(int)position.GetY() / 64];
}