#pragma once 

#include "../GameObject.h"

#include <cstdint>
#include <vector>
#include <memory>


class HoverTile;
class Grid : public GameObject
{
	int32_t cellSize_;
	std::unique_ptr<HoverTile> hoverTile_;
	std::vector<std::shared_ptr<GameObject>> buildings_;

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
};