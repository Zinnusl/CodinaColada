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
#include "Ball.h"

#include "imgui.h"

#include <chrono>



Grid::Grid(int x, int y, int32_t cellSize, Vector2 position)
	: x_(x), y_(y), cellSize_(cellSize), hoverTile_(std::make_unique<HoverTile>(*this)), GameObject(position)
{
	//first column, second column
	//Zeile1, Column 3
	// nodes_[col * col.size + row)
	for (int x = 0; x < x_; x++)
	{
		for (int y = 0; y < y_; y++)
		{
			nodes_.push_back(Node(x, y));
		}
	}

	Vector2 hoverTileSize = Vector2(cellSize, cellSize);
	hoverTile_->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(hoverTileSize, Color(0, 0, 1, 0.1), &OpenGLRenderer::shaders_["hover"])));
	hoverTile_->AddComponent(std::make_unique<SpriteComponent>(std::make_unique<OpenGLSprite>(glm::vec2(cellSize, cellSize), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["hovertile"])));

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
	FindPath(pathStart_, pathEnd_);
}

void Grid::OnDebugTreeNode()
{
	GameObject::OnDebugTreeNode();
	ImGui::Text("Grid");
	if (ImGui::Button("Clear"))
	{
		Clear();
	}
	ImGui::Text("PixelSize %f", cellSize_ * engine_->GetRenderer().GetZoom());
	ImGui::Text("A* Pathtime %dms", timeToFindPath_);
	ImGui::Text("camera position x: %f y: %f", engine_->GetRenderer().GetCameraPosition().GetX(), engine_->GetRenderer().GetCameraPosition().GetY());
	ImGui::Text("screen mouse x: %f y: %f", engine_->GetInput().GetMousePosition().GetX(), engine_->GetInput().GetMousePosition().GetY());

	auto x = engine_->GetRenderer().ScreenToWorld(engine_->GetInput().GetMousePosition()).GetX();
	auto y = engine_->GetRenderer().ScreenToWorld(engine_->GetInput().GetMousePosition()).GetY();
	ImGui::Text("ScreenToWorld mouse x: %f y: %f", x, y);
	ImGui::Text("WorldToScreen mouse x: %f y: %f", engine_->GetRenderer().WorldToScreen(x).GetX(), engine_->GetRenderer().WorldToScreen(y).GetY());

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

void Grid::OnDraw(float subframe, float deltaTime)
{
	GameObject::OnDraw(subframe, deltaTime);

	//draw path visualisation
	for (auto& pathNode : pathVisualisation_)
	{
		pathNode->OnDraw(subframe, deltaTime);
	}

	for (auto& building : buildings_)
	{
		building->OnDraw(subframe, deltaTime);
	}

	Vector2 mouseWorldPos = engine_->GetRenderer().ScreenToWorld(engine_->GetInput().GetMousePosition());

	if (Vector2::isPointInRectangle(mouseWorldPos, GetPosition(), Vector2(cellSize_ * x_, cellSize_ * y_)))
	{
		hoverTile_->OnDraw(subframe, deltaTime);
	}
	else
	{
		//Do nothing when mouse is not within grid
		return;
	}
	
	int column = (mouseWorldPos.GetX() - GetPosition().GetX()) / cellSize_;
	int row = (mouseWorldPos.GetY() - GetPosition().GetY()) / cellSize_;

	if (column >= x_ || row >= y_)
	{
		return;
	}

	//TODO WIP
	bool isCellFree = IsCellFree(column,row);

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
		//tower->AddComponent(std::make_unique<SpriteComponent>(std::make_unique<OpenGLSprite>(glm::vec2(cellSize_, cellSize_), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["tower_canon"])));
		tower->AddComponent(std::make_unique<SpriteComponent>(std::make_unique<OpenGLSprite>(glm::vec2(cellSize_, cellSize_), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["blocker_red"])));
		GetNode(column, row).building = tower;
		GetNode(column, row).walkable_ = false;
		buildings_.push_back(std::move(tower));
		engine_->GetAudio().Play("..\\..\\..\\..\\CodingColada\\game\\common\\resources\\audio\\build2.wav", 1, false);
	}
	if (GameObject::engine_->GetInput().GetMouse(1) && isCellFree)
	{
		auto stone = std::make_shared<Tower>(hoverTile_->GetPosition());
		stone->AddComponent(std::make_unique<SpriteComponent>(std::make_unique<OpenGLSprite>(glm::vec2(cellSize_, cellSize_), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["blocker"])));
		//stone->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(Vector2{ (float)cellSize_ }, Color(1, 0, 0, 0.3), &OpenGLRenderer::shaders_["neon_pulse"])));

		GetNode(column, row).building = stone;
		buildings_.push_back(std::move(stone));
		GetNode(column, row).walkable_ = false;
	}
}

void Grid::OnCollision(RigidbodyComponent& other)
{
	GameObject::OnCollision(other);
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

bool Grid::IsCellFree(int x, int y)
{
	if (GetNode(x, y).building)
	{
		return false;
	}
	return true;
}

bool Grid::AddBuilding(int row, int column, std::shared_ptr<GameObject> building)
{
	if (!IsCellFree(row, column))
	{
		return false;
	}
	auto node = GetNode(column, row);
	node.building = building;
	node.walkable_ = false;
	buildings_.push_back(building);
	return true;
}


void Grid::FindPath(Vector2 start, Vector2 end)
{
	auto startTime = std::chrono::steady_clock::now();

	Node* startNode = &GetNode(start.GetX(), start.GetY());
	Node* targetNode = &GetNode(end.GetX(), end.GetY());

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

void Grid::SetupLevel(Vector2 pathStart, Vector2 pathEnd, std::vector<Vector2> blockers)
{
	Clear();
	pathStart_ = pathStart;
	pathEnd_ = pathEnd;
	for (auto& blockerPosition : blockers)
	{
		auto blocker = std::make_shared<Tower>(GetPosition() + blockerPosition * cellSize_);
		blocker->AddComponent(std::make_unique<SpriteComponent>(std::make_unique<OpenGLSprite>(glm::vec2(cellSize_, cellSize_), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["blocker"])));

		GetNode(blockerPosition.GetX(), blockerPosition.GetY()).building = blocker;
		buildings_.push_back(std::move(blocker));
		GetNode(blockerPosition.GetX(), blockerPosition.GetY()).walkable_ = false;
	}
}

Grid::Node& Grid::GetNode(int row, int column)
{
	auto index = column + row * y_;
	if (index < 0 || index >= nodes_.size())
	{
		printf("Error trying to oacces wrong index %d\n", index);
	}
	return nodes_[index];
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

			if (checkX >= 0 && checkX < x_ && checkY >= 0 && checkY < y_)
			{
				neighbours.push_back(&GetNode(checkX, checkY));
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
		Vector2 pathTileSize = Vector2(cellSize_, cellSize_);
		std::unique_ptr<PathTile> pathTile = std::make_unique<PathTile>(Vector2(GetPosition().GetX() + node->gridX_ * cellSize_, GetPosition().GetY() + node->gridY_ * cellSize_));
		pathTile->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(pathTileSize, Color(0, 0, 1, 1))));
		pathVisualisation_.push_back(std::move(pathTile));
	}
}

Grid::Node* Grid::GetNodeFromPosition(Vector2 position)
{
	int tmpX = (position.GetX() - GetPosition().GetX()) / cellSize_;
	int tmpY = (position.GetY() - GetPosition().GetY()) / cellSize_;

	if (tmpX >= x_ || tmpY >= y_)
	{
		return nullptr;
	}
	return &GetNode(tmpX, tmpY);
}

void Grid::Clear()
{
	buildings_.clear();
	for (auto& node : nodes_)
	{
		node.walkable_ = true;
	}
}