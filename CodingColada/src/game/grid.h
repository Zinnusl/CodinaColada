#pragma once 

#include "../GameObject.h"

#include <cstdint>
#include <vector>
#include <memory>


class HoverTile;
class Grid : public GameObject
{
	struct Node
	{
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
	std::unique_ptr<HoverTile> hoverTile_;
	std::vector<std::shared_ptr<GameObject>> buildings_;
	std::vector<std::shared_ptr<GameObject>> pathVisualisation_;

	Vector2 gridSize_ = Vector2(64,64);
	Node* nodes_[64][64];
	std::vector<Node*> path_;

	std::vector<Node*> GetNeighbours(Node* node);
	int GetDistance(Node* a, Node* b);
	void RetracePath(Node* startNode, Node* endNode);
	Node* GetNodeFromPosition(Vector2 position);

public:
	Grid() = delete;
	Grid(int32_t cellSize);

	void OnPhysicsUpdate(float deltaTime) override;
	void OnDebugTreeNode() override;
	void OnDraw(float subframe) override;
	void OnCollision(RigidbodyComponent& other) override;

	int32_t GetCellSize();

	//This is expensive
	bool IsCellFree(Vector2 position);

	void FindPath(Vector2 start, Vector2 end);
};