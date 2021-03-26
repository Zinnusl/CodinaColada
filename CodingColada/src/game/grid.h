#pragma once 

#include "../GameObject.h"

#include <cstdint>
#include <vector>

class Grid : public GameObject
{
	int32_t cellSize_;

	std::vector<std::unique_ptr<GameObject>> buildings_;

public:
	Grid() = delete;
	Grid(int32_t cellSize);

	void OnPhysicsUpdate(float deltaTime) override;
	void OnDebugTreeNode() override;

	void OnDraw(float subframe) override;
	void OnCollision(RigidbodyComponent& other) override;


	int32_t GetCellSize();
};