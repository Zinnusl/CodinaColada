#pragma once 

#include "../../engine/GameObject.h"

#include <cstdint>
#include <vector>
#include <memory>


class HoverTile;
class ShapeComponent;
class SpriteComponent;
class Grid : public GameObject
{
	struct Node
	{
		std::shared_ptr<GameObject> building;

		int gCost_;
		int hCost_;

		int gridX_;
		int gridY_;

		bool walkable_;

		Node* parent;

		Node(int gridX, int gridY)
			: gridX_(gridX), gridY_(gridY), walkable_(true), gCost_(0), hCost_(0)
		{

		}

		int fCost()
		{
			return gCost_ + hCost_;
		}
	};

	int32_t cellSize_;
	int x_;
	int y_;
	std::unique_ptr<HoverTile> hoverTile_;
	std::vector<std::shared_ptr<GameObject>> buildings_;
	std::vector<std::shared_ptr<GameObject>> pathVisualisation_;

	int64_t timeToFindPath_ = 0;

	std::vector<Node> nodes_;
	Node& GetNode(int row, int column);

	std::vector<Node*> path_;

	ShapeComponent* shapeComponent_;
	SpriteComponent* spriteComponent_;
	std::vector<Node*> GetNeighbours(Node* node);
	int GetDistance(Node* a, Node* b);
	void RetracePath(Node* startNode, Node* endNode);
	Node* GetNodeFromPosition(Vector2 position);

	void Clear();

public:
	Grid() = delete;
	Grid(int x, int y, int32_t cellSize, Vector2 position = {0, 0});

	void OnStart() override;
	void OnPhysicsUpdate(float deltaTime) override;
	void OnDebugTreeNode() override;
	void OnDraw(float subframe, float deltaTime) override;
	void OnCollision(RigidbodyComponent& other) override;

	int32_t GetCellSize();

	//This is expensive
	bool IsCellFree(int x, int y);
	bool AddBuilding(int row, int column, std::shared_ptr<GameObject> building);

	void FindPath(Vector2 start, Vector2 end);
};